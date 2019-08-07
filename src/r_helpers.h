#ifndef GUARD_r_helper_h
#define GUARD_r_helper_h
#include <Rcpp.h>

extern "C" {
#define R_NO_REMAP
#include <R.h>
#include <Rinternals.h>
#include "../include/metar.h"
  
} // end extern "C"


Rcpp::CharacterVector string_or_na(char* x);
Rcpp::CharacterVector clouds(char low, char med, char high);
Rcpp::LogicalVector logical_vector(MDSP_BOOL x);
Rcpp::IntegerVector integer_vector(int x);
Rcpp::NumericVector numeric_vector(float x);

#endif