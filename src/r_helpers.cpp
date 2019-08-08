#include "r_helpers.h"
#include <Rcpp.h>
#include "metar_structs.h" 
using namespace Rcpp;

extern "C" {
#define R_NO_REMAP
#include <R.h>
#include <Rinternals.h>
#include "metar.h"
  
} // end extern "C"


  


Rcpp::CharacterVector string_or_na(char* x) {
  if(x[0] == '\0') return CharacterVector::create(NA_STRING);
  if (strlen(x)) {
    return Rf_mkString(x);
  } else {
    return CharacterVector::create(NA_STRING);
  }
}


Rcpp::CharacterVector clouds(char low, char med, char high) {
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


Rcpp::LogicalVector logical_vector(MDSP_BOOL x){
  return LogicalVector::create(x);
}

Rcpp::IntegerVector integer_vector(int x){
  if (x == MAXINT ) {
    return IntegerVector::create(NA_INTEGER);
  } else {
    return IntegerVector::create(x);
  }
}

Rcpp::NumericVector numeric_vector(float x){
  if (x == ((float) MAXINT)) {
    return NumericVector::create(NA_REAL);
  } else {
    return NumericVector::create(x);
  }
}


Rcpp::List r_extract_runway_visrange_(Decoded_METAR *Mptr, int element) {
  Rcpp::CharacterVector Distance_Unit;
  switch(Mptr->RRVR[element].distance_unit) {
    case DIST_FEET:
      Distance_Unit = "feet";
    case DIST_METERS:
      Distance_Unit = "meters";
  };
  Rcpp::List output = Rcpp::List::create(
    Rcpp::Named("runway_designator")  = string_or_na(Mptr->RRVR[element].runway_designator),
    Rcpp::Named("vrbl_visRange")      = logical_vector(Mptr->RRVR[element].vrbl_visRange), 
    Rcpp::Named("below_min_RVR")      = logical_vector(Mptr->RRVR[element].below_min_RVR), 
    Rcpp::Named("above_max_RVR")      = logical_vector(Mptr->RRVR[element].above_max_RVR), 
    Rcpp::Named("visRange")           = integer_vector(Mptr->RRVR[element].visRange), 
    Rcpp::Named("Max_visRange")       = integer_vector(Mptr->RRVR[element].Max_visRange),
    Rcpp::Named("Min_visRange")       = integer_vector(Mptr->RRVR[element].Min_visRange), 
    Rcpp::Named("Distance_Unit")      = Distance_Unit);
  return output;
}

Rcpp::List r_extract_dispatch_visrange_(Decoded_METAR *Mptr) {
  Rcpp::List output = Rcpp::List::create(
    Rcpp::Named("vrbl_visRange")  = logical_vector(Mptr->DVR.vrbl_visRange),
    Rcpp::Named("below_min_DVR")  = logical_vector(Mptr->DVR.below_min_DVR), 
    Rcpp::Named("above_max_DVR")  = logical_vector(Mptr->DVR.above_max_DVR), 
    Rcpp::Named("visRange")       = integer_vector(Mptr->DVR.visRange), 
    Rcpp::Named("Max_visRange")   = integer_vector(Mptr->DVR.Max_visRange),
    Rcpp::Named("Min_visRange")   = integer_vector(Mptr->DVR.Min_visRange));
  return output;
}

Rcpp::List r_extract_recent_wx_(Decoded_METAR *Mptr, int element) {
  Rcpp::List output = Rcpp::List::create(
    Rcpp::Named("Recent_weather") = string_or_na(Mptr->ReWx[element].Recent_weather),
    Rcpp::Named("Bhh")            = integer_vector(Mptr->ReWx[element].Bhh), 
    Rcpp::Named("Bmm")            = integer_vector(Mptr->ReWx[element].Bmm), 
    Rcpp::Named("Ehh")            = integer_vector(Mptr->ReWx[element].Ehh), 
    Rcpp::Named("Emm")            = integer_vector(Mptr->ReWx[element].Emm));
  return output;
}

Rcpp::List r_extract_cloud_conditions_(Decoded_METAR *Mptr, int element) {
  Rcpp::List output = Rcpp::List::create(
    Rcpp::Named("cloud_type")       = string_or_na(Mptr->cloudGroup[element].cloud_type),
    Rcpp::Named("cloud_hgt_char")   = string_or_na(Mptr->cloudGroup[element].cloud_hgt_char), 
    Rcpp::Named("other_cld_phenom") = string_or_na(Mptr->cloudGroup[element].other_cld_phenom), 
    Rcpp::Named("cloud_hgt_meters") = integer_vector(Mptr->cloudGroup[element].cloud_hgt_meters));
  return output;
}

Rcpp::List r_extract_wind_(Decoded_METAR *Mptr) {
  Rcpp::List output = Rcpp::List::create(
    Rcpp::Named("windUnits")  = string_or_na(Mptr->winData.windUnits),
    Rcpp::Named("windVRB")    = logical_vector(Mptr->winData.windVRB), 
    Rcpp::Named("windDir")    = integer_vector(Mptr->winData.windDir), 
    Rcpp::Named("windSpeed")  = integer_vector(Mptr->winData.windSpeed), 
    Rcpp::Named("windGust")   = integer_vector(Mptr->winData.windGust));
  return output;
}
