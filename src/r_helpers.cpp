#include "r_helpers.h"
#include <Rcpp.h>
using namespace Rcpp;

extern "C" {
#define R_NO_REMAP
#include <R.h>
#include <Rinternals.h>
#include "../include/metar.h"
  
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
  if (x == 2147483647) {
    return IntegerVector::create(NA_INTEGER);
  } else {
    return IntegerVector::create(x);
  }
}

Rcpp::NumericVector numeric_vector(float x){
  if (x == 2147483648) {
    return NumericVector::create(NA_REAL);
  } else {
    return NumericVector::create(x);
  }
}

