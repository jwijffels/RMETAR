// Generated by using Rcpp::compileAttributes() -> do not edit by hand
// Generator token: 10BE3573-1514-4C36-9D1C-5A225CD40393

#include <Rcpp.h>

using namespace Rcpp;

// r_decode_metar_
List r_decode_metar_(std::string metarcode);
RcppExport SEXP _RMETAR_r_decode_metar_(SEXP metarcodeSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< std::string >::type metarcode(metarcodeSEXP);
    rcpp_result_gen = Rcpp::wrap(r_decode_metar_(metarcode));
    return rcpp_result_gen;
END_RCPP
}

static const R_CallMethodDef CallEntries[] = {
    {"_RMETAR_r_decode_metar_", (DL_FUNC) &_RMETAR_r_decode_metar_, 1},
    {NULL, NULL, 0}
};

RcppExport void R_init_RMETAR(DllInfo *dll) {
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
}
