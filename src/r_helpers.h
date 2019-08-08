#ifndef GUARD_r_helper_h
#define GUARD_r_helper_h
#include <Rcpp.h>

extern "C" {
#define R_NO_REMAP
#include <R.h>
#include <Rinternals.h>
#include "metar.h"
  
} // end extern "C"


Rcpp::CharacterVector string_or_na(char* x);
Rcpp::CharacterVector clouds(char low, char med, char high);
Rcpp::LogicalVector logical_vector(MDSP_BOOL x);
Rcpp::IntegerVector integer_vector(int x);
Rcpp::NumericVector numeric_vector(float x);


Rcpp::List r_extract_runway_visrange_(Decoded_METAR *Mptr, int element);
Rcpp::List r_extract_dispatch_visrange_(Decoded_METAR *Mptr);
Rcpp::List r_extract_recent_wx_(Decoded_METAR *Mptr, int element);
Rcpp::List r_extract_wind_(Decoded_METAR *Mptr);
Rcpp::List r_extract_cloud_conditions_(Decoded_METAR *Mptr, int element);

#endif
