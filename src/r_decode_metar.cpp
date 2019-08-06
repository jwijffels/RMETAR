
#include <Rcpp.h>
#include <string>
#include <cstring>
using namespace Rcpp;

extern "C" {
#define R_NO_REMAP
#include <R.h>
#include <Rinternals.h>
#include "../include/metar.h"

} // end extern "C"



// Workaround for Rcpp limit of max 20 elements in list
// https://stackoverflow.com/a/27371771/602276
class ListBuilder {
  
public:
  
  ListBuilder() {};
  ~ListBuilder() {};
  
  inline ListBuilder& add(std::string const& name, SEXP x) {
    names.push_back(name);
    
    // NOTE: we need to protect the SEXPs we pass in; there is
    // probably a nicer way to handle this but ...
    elements.push_back(PROTECT(x));
    
    return *this;
  }
  
  inline operator List() const {
    List result(elements.size());
    for (size_t i = 0; i < elements.size(); ++i) {
      result[i] = elements[i];
    }
    result.attr("names") = wrap(names);
    UNPROTECT(elements.size());
    return result;
  }
  
  inline operator DataFrame() const {
    List result = static_cast<List>(*this);
    result.attr("class") = "data.frame";
    result.attr("row.names") = IntegerVector::create(NA_INTEGER, XLENGTH(elements[0]));
    return result;
  }
  
private:
  
  std::vector<std::string> names;
  std::vector<SEXP> elements;
  
  ListBuilder(ListBuilder const&) {}; // not safe to copy
  
};


// CharacterVector string_or_na(char * x) {
//   Rcpp::String z;
//   std::string y(x);
//   if (x == '\0') {
//     z = NA_STRING;
//   } else {
//     z = Rcpp::String(y);
//   }
//   return CharacterVector::create(z);
// }


CharacterVector string_or_na(char* x) {
  if(x[0] == '\0') return CharacterVector::create(NA_STRING);
  if (strlen(x)) {
    return Rf_mkString(x);
  } else {
    return CharacterVector::create(NA_STRING);
  }
}


CharacterVector clouds(char low, char med, char high) {
  char lmh[3];
  lmh[0] = low;
  lmh[1] = med;
  lmh[2] = high; 
  if((low != '\0') | (med != '\0') | (high != '\0')) {
    return CharacterVector::create(Rf_mkChar(lmh));
  } else {
    return CharacterVector::create(NA_STRING);
  }
}





// [[Rcpp::export]]
List r_decode_metar_(std::string metarcode) {
  Decoded_METAR Metar;
  Decoded_METAR *Mptr = &Metar;
  int decoded_error;

  char *invec = &(metarcode[0]);
  decoded_error = decode_metar(invec, Mptr);

  if (decoded_error != 0) {
    //throw std::range_error("Error in decoding METAR string");
    printf("METAR decoding error");
  }
  
  ListBuilder z;
  std::string var;
 
  // Rcpp::Rcout << "The value of SKY_2ndSite_LOC is : " << Mptr->SKY_2ndSite_LOC << std::endl;
    
  z = ListBuilder();
    
    
    // compute character values ------------------------------------------------
    
  z
    .add("synoptic_cloud_type", string_or_na(Mptr->synoptic_cloud_type))
    .add("snow_depth_group",    string_or_na(Mptr->snow_depth_group))
    .add("codeName",            string_or_na(Mptr->codeName))
    .add("stnid",               string_or_na(Mptr->stnid))
    .add("horiz_vsby",          string_or_na(Mptr->horiz_vsby))
    .add("dir_min_horiz_vsby",  string_or_na(Mptr->dir_min_horiz_vsby))
    .add("vsby_Dir",            string_or_na(Mptr->vsby_Dir));
  
  for(int i=0; i<8; i++){
    var = "WxObstruct_"  + std::to_string(i);
    z.add(var,  string_or_na(Mptr->WxObstruct[i]));
  }
  
  z
    .add("autoIndicator",       string_or_na(Mptr->autoIndicator))
    .add("VSBY_2ndSite_LOC",    string_or_na(Mptr->VSBY_2ndSite_LOC))
    .add("SKY_2ndSite_LOC",     string_or_na(Mptr->SKY_2ndSite_LOC))
    .add("SKY_2ndSite",         string_or_na(Mptr->SKY_2ndSite))
    .add("SectorVsby_Dir",      string_or_na(Mptr->SectorVsby_Dir))
    .add("ObscurAloft",         string_or_na(Mptr->ObscurAloft))
    .add("ObscurAloftSkyCond",  string_or_na(Mptr->ObscurAloftSkyCond))
    .add("VrbSkyBelow",         string_or_na(Mptr->VrbSkyBelow))
    .add("VrbSkyAbove",         string_or_na(Mptr->VrbSkyAbove))
    .add("LTG_DIR",             string_or_na(Mptr->LTG_DIR))
  
    .add("CloudLowMediumHigh",  clouds(Mptr->CloudLow, Mptr->CloudMedium, Mptr->CloudHigh))
  
    .add("CIG_2ndSite_LOC", string_or_na(Mptr->CIG_2ndSite_LOC))
    .add("VIRGA_DIR",       string_or_na(Mptr->VIRGA_DIR))
    .add("TornadicType",    string_or_na(Mptr->TornadicType))
    .add("TornadicLOC",     string_or_na(Mptr->TornadicLOC))
    .add("TornadicDIR",     string_or_na(Mptr->TornadicDIR))
    .add("TornadicMovDir",  string_or_na(Mptr->TornadicMovDir))
    .add("CHINO_LOC",       string_or_na(Mptr->CHINO_LOC))
    .add("VISNO_LOC",       string_or_na(Mptr->VISNO_LOC));
  
  for(int i=0; i<7; i++){
    var = "PartialObscurationAmt_"  + std::to_string(i);
    z.add(var,  string_or_na(Mptr->PartialObscurationAmt[i]));
  }
  for(int i=0; i<12; i++){
    var = "PartialObscurationPhenom_"  + std::to_string(i);
    z.add(var,  string_or_na(Mptr->PartialObscurationPhenom[i]));
  }
  for(int i=0; i<10; i++){
    var = "SfcObscuration_"  + std::to_string(i);
    z.add(var,  string_or_na(Mptr->SfcObscuration[i]));
  }
  
  z
    .add("TS_LOC",     string_or_na(Mptr->TS_LOC))
    .add("TS_MOVMNT",  string_or_na(Mptr->TS_MOVMNT))
  
  .add("METAR", Rf_mkString(invec));
  
  // Compute boolean values ----------------------------------------------------
  
  z
    .add("Indeterminant3_6HrPrecip", LogicalVector::create(Mptr->Indeterminant3_6HrPrecip))
    .add("Indeterminant_24HrPrecip", LogicalVector::create(Mptr->Indeterminant_24HrPrecip))
    .add("CIGNO",                    LogicalVector::create(Mptr->CIGNO))
    .add("SLPNO",                    LogicalVector::create(Mptr->SLPNO))
    .add("ACFTMSHP",                 LogicalVector::create(Mptr->ACFTMSHP))
    .add("NOSPECI",                  LogicalVector::create(Mptr->NOSPECI))
    .add("FIRST",                    LogicalVector::create(Mptr->FIRST))
    .add("LAST",                     LogicalVector::create(Mptr->LAST))
    .add("SunSensorOut",             LogicalVector::create(Mptr->SunSensorOut))
    .add("AUTO",                     LogicalVector::create(Mptr->AUTO))
    .add("COR",                      LogicalVector::create(Mptr->COR))
    .add("NIL_rpt",                  LogicalVector::create(Mptr->NIL_rpt))
    .add("CAVOK",                    LogicalVector::create(Mptr->CAVOK))
    .add("RVRNO",                    LogicalVector::create(Mptr->RVRNO))
    .add("A_altstng",                LogicalVector::create(Mptr->A_altstng))
    .add("Q_altstng",                LogicalVector::create(Mptr->Q_altstng))
    .add("VIRGA",                    LogicalVector::create(Mptr->VIRGA))
    .add("VOLCASH",                  LogicalVector::create(Mptr->VOLCASH))
    .add("GR",                       LogicalVector::create(Mptr->GR))
    .add("CHINO",                    LogicalVector::create(Mptr->CHINO))
    .add("VISNO",                    LogicalVector::create(Mptr->VISNO))
    .add("PNO",                      LogicalVector::create(Mptr->PNO))
    .add("PWINO",                    LogicalVector::create(Mptr->PWINO))
    .add("FZRANO",                   LogicalVector::create(Mptr->FZRANO))
    .add("TSNO",                     LogicalVector::create(Mptr->TSNO))
    .add("DollarSign",               LogicalVector::create(Mptr->DollarSign))
    .add("PRESRR",                   LogicalVector::create(Mptr->PRESRR))
    .add("PRESFR",                   LogicalVector::create(Mptr->PRESFR))
    .add("Wshft_FROPA",              LogicalVector::create(Mptr->Wshft_FROPA))
    .add("OCNL_LTG",                 LogicalVector::create(Mptr->OCNL_LTG))
    .add("FRQ_LTG",                  LogicalVector::create(Mptr->FRQ_LTG))
    .add("CNS_LTG",                  LogicalVector::create(Mptr->CNS_LTG))
    .add("CG_LTG",                   LogicalVector::create(Mptr->CG_LTG))
    .add("IC_LTG",                   LogicalVector::create(Mptr->IC_LTG))
    .add("CC_LTG",                   LogicalVector::create(Mptr->CC_LTG))
    .add("CA_LTG",                   LogicalVector::create(Mptr->CA_LTG))
    .add("DSNT_LTG",                 LogicalVector::create(Mptr->DSNT_LTG))
    .add("AP_LTG",                   LogicalVector::create(Mptr->AP_LTG))
    .add("VcyStn_LTG",               LogicalVector::create(Mptr->VcyStn_LTG))
    .add("OVHD_LTG",                 LogicalVector::create(Mptr->OVHD_LTG))
    .add("LightningVCTS",            LogicalVector::create(Mptr->LightningVCTS))
    .add("LightningTS",              LogicalVector::create(Mptr->LightningTS))
    .add("visibilityIsUpperBound",  LogicalVector::create(Mptr->visibilityIsUpperBound));
  
  // Compute integer values ----------------------------------------------------

  z
    .add("TornadicDistance",   IntegerVector::create(int(Mptr->TornadicDistance)))
    .add("ob_hour",            IntegerVector::create(Mptr->ob_hour))
    .add("ob_minute",          IntegerVector::create(Mptr->ob_minute))
    .add("ob_date",            IntegerVector::create(Mptr->ob_date))
    .add("minWnDir",           IntegerVector::create(Mptr->minWnDir))
    .add("maxWnDir",           IntegerVector::create(Mptr->maxWnDir))
    .add("VertVsby",           IntegerVector::create(Mptr->VertVsby))
    .add("temp",               IntegerVector::create(Mptr->temp))
    .add("dew_pt_temp",        IntegerVector::create(Mptr->dew_pt_temp))
    .add("QFE",                IntegerVector::create(Mptr->QFE))
    .add("hectoPasc_altstng",  IntegerVector::create(Mptr->hectoPasc_altstng))
    .add("char_prestndcy",     IntegerVector::create(Mptr->char_prestndcy))
    .add("minCeiling",         IntegerVector::create(Mptr->minCeiling))
    .add("maxCeiling",         IntegerVector::create(Mptr->maxCeiling))
    .add("WshfTime_hour",      IntegerVector::create(Mptr->WshfTime_hour))
    .add("WshfTime_minute",    IntegerVector::create(Mptr->WshfTime_minute))
    .add("min_vrbl_wind_dir",  IntegerVector::create(Mptr->min_vrbl_wind_dir))
    .add("max_vrbl_wind_dir",  IntegerVector::create(Mptr->max_vrbl_wind_dir))
    .add("PKWND_dir",          IntegerVector::create(Mptr->PKWND_dir))
    .add("PKWND_speed",        IntegerVector::create(Mptr->PKWND_speed))
    .add("PKWND_hour",         IntegerVector::create(Mptr->PKWND_hour))
    .add("PKWND_minute",       IntegerVector::create(Mptr->PKWND_minute))
    .add("SKY_2ndSite_Meters", IntegerVector::create(Mptr->SKY_2ndSite_Meters))
    .add("Ceiling",            IntegerVector::create(Mptr->Ceiling))
    .add("Estimated_Ceiling",  IntegerVector::create(Mptr->Estimated_Ceiling))
    .add("SNINCR",             IntegerVector::create(Mptr->SNINCR))
    .add("SNINCR_TotalDepth",  IntegerVector::create(Mptr->SNINCR_TotalDepth))
    .add("SunshineDur",        IntegerVector::create(Mptr->SunshineDur))
    .add("ObscurAloftHgt",     IntegerVector::create(Mptr->ObscurAloftHgt))
    .add("VrbSkyLayerHgt",     IntegerVector::create(Mptr->VrbSkyLayerHgt))
    .add("Num8thsSkyObscured", IntegerVector::create(Mptr->Num8thsSkyObscured))
    .add("CIG_2ndSite_Meters", IntegerVector::create(Mptr->CIG_2ndSite_Meters))
    .add("snow_depth",         IntegerVector::create(Mptr->snow_depth))
    .add("BTornadicHour",      IntegerVector::create(Mptr->BTornadicHour))
    .add("BTornadicMinute",    IntegerVector::create(Mptr->BTornadicMinute))
    .add("ETornadicHour",      IntegerVector::create(Mptr->ETornadicHour))
    .add("ETornadicMinute",    IntegerVector::create(Mptr->ETornadicMinute));
  
  
  // Decode printed string using sprint_metar() --------------------------------
  char printout[5000];
  sprint_metar(printout, Mptr);
  z.add("printout", Rf_mkString(printout));
    
  
  
  return z;
}
