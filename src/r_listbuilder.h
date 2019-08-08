#ifndef GUARD_r_listbuilder_h
#define GUARD_r_listbuilder_h
#include <Rcpp.h>

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