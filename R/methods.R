#' @export
str.decodedMETAR <- function(object, list.len = 500, ...){
  NextMethod("str", object, list.len = list.len, ...)
}



#' @export
print.decodedMETAR <- function(x, ...){
  cat(x$printout)
}
