#' @keywords internal
#' @useDynLib RMETAR, .registration = TRUE
#' @importFrom Rcpp sourceCpp
#' @importFrom fasttime fastPOSIXct 
#' @importFrom utils read.csv
"_PACKAGE"

# The following block is used by usethis to automatically manage
# roxygen namespace tags. Modify with care!
## usethis namespace: start
## usethis namespace: end
NULL


#' A data frame with 55,345 airports.
#'
#' A dataset containing airport information, downloaded using the
#' [download_airports()] function. This is a snapshot of August, 2019.
#'
#' @format A data frame with 55,345 rows and 17 variables.  See Details.
#' @template airport-columns
#'
#'
#' @source <http://ourairports.com/data>
"airports"



#' A data frame with 9,149 METAR reports.
#'
#' A dataset containing airport weather reports, downloaded using the
#' [download_metar()] function. This is a snapshot of August, 2019.
#'
#' @format A data frame with 9,149 rows and 2 variables (`time` and `metar`).
#' @template airport-columns
#'
#'
#' @source <http://ourairports.com/data>
"airport_weather"