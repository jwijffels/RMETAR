#include "r_helpers.h"
#include <Rcpp.h>
using namespace Rcpp;

extern "C" {
#define R_NO_REMAP
#include <R.h>
#include <Rinternals.h>
#include "../include/metar.h"
  
} // end extern "C"


// Workaround for Rcpp limit of max 20 elements in list
// https://stackoverflow.com/a/27371771/602276

  ListBuilder& ListBuilder::add(std::string const& name, SEXP x) {
    names.push_back(name);
    
    // NOTE: we need to protect the SEXPs we pass in; there is
    // probably a nicer way to handle this but ...
    elements.push_back(PROTECT(x));
    
    return *this;
  }
  
  Rcpp::List ListBuilder::convert_to_list() const {
    List result(elements.size());
    for (size_t i = 0; i < elements.size(); ++i) {
      result[i] = elements[i];
    }
    result.attr("names") = wrap(names);
    UNPROTECT(elements.size());
    return result;
  }
  
  Rcpp::DataFrame ListBuilder::convert_to_dataframe() const {
    List result = convert_to_list();
    result.attr("class") = "data.frame";
    result.attr("row.names") = IntegerVector::create(NA_INTEGER, XLENGTH(elements[0]));
    return result;
  }
  


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

// -----------------------------------------------------------------------------


Rcpp::List r_extract_runway_visrange_(Decoded_METAR *Mptr, int element) {
  Rcpp::List z;
  z = List::create(
    Named("runway_designator", string_or_na  (Mptr->RRVR[element].runway_designator)),
    Named("vrbl_visRange",     logical_vector(Mptr->RRVR[element].vrbl_visRange)),
    Named("below_min_RVR",     logical_vector(Mptr->RRVR[element].below_min_RVR)),
    Named("above_max_RVR",     logical_vector(Mptr->RRVR[element].above_max_RVR)),
    Named("visRange",          integer_vector(Mptr->RRVR[element].visRange)),
    Named("Max_visRange",      integer_vector(Mptr->RRVR[element].Max_visRange)),
    Named("Min_visRange",      integer_vector(Mptr->RRVR[element].Min_visRange))
  );
    // .add("distance_unit ",    (Mptr->RRVR[element].distance_unit));

    // Distance_Unit distance_unit;

  return z;
}
