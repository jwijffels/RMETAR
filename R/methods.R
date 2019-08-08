#' @export
str.decodedMETAR <- function(x, list.len = 500, ...){
  NextMethod("str", x, list.len = list.len, ...)
}



#' @export
print.decodedMETAR <- function(x, ...){
  cat(x$printout)
}
