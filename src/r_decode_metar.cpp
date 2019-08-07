
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

#include "r_helpers.h"



// [[Rcpp::export]]
Rcpp::DataFrame r_decode_metar_(std::string metarcode) {
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
    .add("TS_MOVMNT",  string_or_na(Mptr->TS_MOVMNT));
  
  
  // Compute boolean values ----------------------------------------------------
  
  
  
  z
    .add("Indeterminant3_6HrPrecip", logical_vector(Mptr->Indeterminant3_6HrPrecip))
    .add("Indeterminant_24HrPrecip", logical_vector(Mptr->Indeterminant_24HrPrecip))
    .add("CIGNO",                    logical_vector(Mptr->CIGNO))
    .add("SLPNO",                    logical_vector(Mptr->SLPNO))
    .add("ACFTMSHP",                 logical_vector(Mptr->ACFTMSHP))
    .add("NOSPECI",                  logical_vector(Mptr->NOSPECI))
    .add("FIRST",                    logical_vector(Mptr->FIRST))
    .add("LAST",                     logical_vector(Mptr->LAST))
    .add("SunSensorOut",             logical_vector(Mptr->SunSensorOut))
    .add("AUTO",                     logical_vector(Mptr->AUTO))
    .add("COR",                      logical_vector(Mptr->COR))
    .add("NIL_rpt",                  logical_vector(Mptr->NIL_rpt))
    .add("CAVOK",                    logical_vector(Mptr->CAVOK))
    .add("RVRNO",                    logical_vector(Mptr->RVRNO))
    .add("A_altstng",                logical_vector(Mptr->A_altstng))
    .add("Q_altstng",                logical_vector(Mptr->Q_altstng))
    .add("VIRGA",                    logical_vector(Mptr->VIRGA))
    .add("VOLCASH",                  logical_vector(Mptr->VOLCASH))
    .add("GR",                       logical_vector(Mptr->GR))
    .add("CHINO",                    logical_vector(Mptr->CHINO))
    .add("VISNO",                    logical_vector(Mptr->VISNO))
    .add("PNO",                      logical_vector(Mptr->PNO))
    .add("PWINO",                    logical_vector(Mptr->PWINO))
    .add("FZRANO",                   logical_vector(Mptr->FZRANO))
    .add("TSNO",                     logical_vector(Mptr->TSNO))
    .add("DollarSign",               logical_vector(Mptr->DollarSign))
    .add("PRESRR",                   logical_vector(Mptr->PRESRR))
    .add("PRESFR",                   logical_vector(Mptr->PRESFR))
    .add("Wshft_FROPA",              logical_vector(Mptr->Wshft_FROPA))
    .add("OCNL_LTG",                 logical_vector(Mptr->OCNL_LTG))
    .add("FRQ_LTG",                  logical_vector(Mptr->FRQ_LTG))
    .add("CNS_LTG",                  logical_vector(Mptr->CNS_LTG))
    .add("CG_LTG",                   logical_vector(Mptr->CG_LTG))
    .add("IC_LTG",                   logical_vector(Mptr->IC_LTG))
    .add("CC_LTG",                   logical_vector(Mptr->CC_LTG))
    .add("CA_LTG",                   logical_vector(Mptr->CA_LTG))
    .add("DSNT_LTG",                 logical_vector(Mptr->DSNT_LTG))
    .add("AP_LTG",                   logical_vector(Mptr->AP_LTG))
    .add("VcyStn_LTG",               logical_vector(Mptr->VcyStn_LTG))
    .add("OVHD_LTG",                 logical_vector(Mptr->OVHD_LTG))
    .add("LightningVCTS",            logical_vector(Mptr->LightningVCTS))
    .add("LightningTS",              logical_vector(Mptr->LightningTS))
    .add("visibilityIsUpperBound",   logical_vector(Mptr->visibilityIsUpperBound));
  
  // Compute integer values ----------------------------------------------------

  z
    .add("TornadicDistance",   integer_vector(Mptr->TornadicDistance))
    .add("ob_hour",            integer_vector(Mptr->ob_hour))
    .add("ob_minute",          integer_vector(Mptr->ob_minute))
    .add("ob_date",            integer_vector(Mptr->ob_date))
    .add("minWnDir",           integer_vector(Mptr->minWnDir))
    .add("maxWnDir",           integer_vector(Mptr->maxWnDir))
    .add("VertVsby",           integer_vector(Mptr->VertVsby))
    .add("temp",               integer_vector(Mptr->temp))
    .add("dew_pt_temp",        integer_vector(Mptr->dew_pt_temp))
    .add("QFE",                integer_vector(Mptr->QFE))
    .add("hectoPasc_altstng",  integer_vector(Mptr->hectoPasc_altstng))
    .add("char_prestndcy",     integer_vector(Mptr->char_prestndcy))
    .add("minCeiling",         integer_vector(Mptr->minCeiling))
    .add("maxCeiling",         integer_vector(Mptr->maxCeiling))
    .add("WshfTime_hour",      integer_vector(Mptr->WshfTime_hour))
    .add("WshfTime_minute",    integer_vector(Mptr->WshfTime_minute))
    .add("min_vrbl_wind_dir",  integer_vector(Mptr->min_vrbl_wind_dir))
    .add("max_vrbl_wind_dir",  integer_vector(Mptr->max_vrbl_wind_dir))
    .add("PKWND_dir",          integer_vector(Mptr->PKWND_dir))
    .add("PKWND_speed",        integer_vector(Mptr->PKWND_speed))
    .add("PKWND_hour",         integer_vector(Mptr->PKWND_hour))
    .add("PKWND_minute",       integer_vector(Mptr->PKWND_minute))
    .add("SKY_2ndSite_Meters", integer_vector(Mptr->SKY_2ndSite_Meters))
    .add("Ceiling",            integer_vector(Mptr->Ceiling))
    .add("Estimated_Ceiling",  integer_vector(Mptr->Estimated_Ceiling))
    .add("SNINCR",             integer_vector(Mptr->SNINCR))
    .add("SNINCR_TotalDepth",  integer_vector(Mptr->SNINCR_TotalDepth))
    .add("SunshineDur",        integer_vector(Mptr->SunshineDur))
    .add("ObscurAloftHgt",     integer_vector(Mptr->ObscurAloftHgt))
    .add("VrbSkyLayerHgt",     integer_vector(Mptr->VrbSkyLayerHgt))
    .add("Num8thsSkyObscured", integer_vector(Mptr->Num8thsSkyObscured))
    .add("CIG_2ndSite_Meters", integer_vector(Mptr->CIG_2ndSite_Meters))
    .add("snow_depth",         integer_vector(Mptr->snow_depth))
    .add("BTornadicHour",      integer_vector(Mptr->BTornadicHour))
    .add("BTornadicMinute",    integer_vector(Mptr->BTornadicMinute))
    .add("ETornadicHour",      integer_vector(Mptr->ETornadicHour))
    .add("ETornadicMinute",    integer_vector(Mptr->ETornadicMinute));
  
  // Compute numeric values ----------------------------------------------------
  
  z
    .add("SectorVsby",       numeric_vector(Mptr->SectorVsby))
    .add("WaterEquivSnow",   numeric_vector(Mptr->WaterEquivSnow))
    .add("VSBY_2ndSite",     numeric_vector(Mptr->VSBY_2ndSite))
    .add("prevail_vsbySM",   numeric_vector(Mptr->prevail_vsbySM))
    .add("prevail_vsbyM",    numeric_vector(Mptr->prevail_vsbyM))
    .add("prevail_vsbyKM",   numeric_vector(Mptr->prevail_vsbyKM))
    .add("prestndcy",        numeric_vector(Mptr->prestndcy))
    .add("precip_amt",       numeric_vector(Mptr->precip_amt))
    .add("precip_24_amt",    numeric_vector(Mptr->precip_24_amt))
    .add("maxtemp",          numeric_vector(Mptr->maxtemp))
    .add("mintemp",          numeric_vector(Mptr->mintemp))
    .add("max24temp",        numeric_vector(Mptr->max24temp))
    .add("min24temp",        numeric_vector(Mptr->min24temp))
    .add("minVsby",          numeric_vector(Mptr->minVsby))
    .add("maxVsby",          numeric_vector(Mptr->maxVsby))
    .add("hourlyPrecip",     numeric_vector(Mptr->hourlyPrecip))
    .add("TWR_VSBY",         numeric_vector(Mptr->TWR_VSBY))
    .add("SFC_VSBY",         numeric_vector(Mptr->SFC_VSBY))
    .add("Temp_2_tenths",    numeric_vector(Mptr->Temp_2_tenths))
    .add("DP_Temp_2_tenths", numeric_vector(Mptr->DP_Temp_2_tenths))
    .add("SLP",              numeric_vector(Mptr->SLP))
    .add("GR_Size",          numeric_vector(Mptr->GR_Size));
  
  z
  .add("inches_altstng", numeric_vector(Mptr->inches_altstng));
  
  
    
  
  // Decode printed string using sprint_metar() --------------------------------
  char printout[5000];
  sprint_metar(printout, Mptr);

  z
    .add("METAR", Rf_mkString(invec))
    .add("printout", Rf_mkString(printout));
  
  // Add runway visual range ---------------------------------------------------
  
  z
    .add("result_Runway_VisRange_0", Rcpp::List::create(r_extract_runway_visrange_(Mptr, 0)));
    
  
  
  return z.convert_to_dataframe();
}
