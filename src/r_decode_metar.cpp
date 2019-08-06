
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
    
  z = ListBuilder()
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
  
  
  // Decode printed string using sprint_metar()
  char printout[5000];
  sprint_metar(printout, Mptr);
  z.add("printout", Rf_mkString(printout));
    
  
  
  return z;
}
