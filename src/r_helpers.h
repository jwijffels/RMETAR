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


Rcpp::List r_extract_runway_visrange_(Decoded_METAR *Mptr, int element);
Rcpp::List r_extract_dispatch_visrange_(Decoded_METAR *Mptr);


class ListBuilder {
  
public:
  
  ListBuilder() {};
  ~ListBuilder() {};
  
  ListBuilder& add(std::string const& name, SEXP x);
  Rcpp::List convert_to_list() const;
  Rcpp::DataFrame convert_to_dataframe() const;

  private:
  
  std::vector<std::string> names;
  std::vector<SEXP> elements;
  
  ListBuilder(ListBuilder const&) {}; // not safe to copy
};


#endif