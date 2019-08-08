#include "r_listbuilder.h"
#include <Rcpp.h>
using namespace Rcpp;


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
