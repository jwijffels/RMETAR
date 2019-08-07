#' Decode a METAR report.
#'
#' @param x a character string with the METAR (Meteorological Aerodrome Report)
#'   report
#' @param printdecodedmetar a logical, indicating to print out the report in
#'   human readable format as decoded by the mdsplib library
#' @return a list of elements with information contained in the METAR string.
#' The list contains data of a similar structure as the decoded_METAR structure
#' in /src/metar.h. See the examples.
#' @export
#' @example inst/examples/example_decodemetar.R
decodemetar <- function(x, printdecodedmetar = FALSE){
  x <- as.character(x)
  printdecodedmetar <- as.logical(printdecodedmetar)
  result <- r_decode_metar_(x)
  class(result) <- c("decodedMETAR", class(result))
  if(printdecodedmetar){
    cat(result$printout)
    invisible(result)
  } else {
    result
  }
}


