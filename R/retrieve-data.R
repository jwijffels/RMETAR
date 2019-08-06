

#' @title Retrieve current METAR data from NOAA
#' @description Retrieve hourly cycles of METAR data from \url{https://tgftp.nws.noaa.gov/data/observations/metar/cycles}
#' @param hour an hour, either one of 0, 1, 2, up to 23
#' @return a data.frame with columns time and metar containing the METARS from the selected hour currently at \url{https://tgftp.nws.noaa.gov/data/observations/metar/cycles}
#' @export
#' @examples 
#' x <- download_current_metar_cycle(hour = 0)
#' x <- download_current_metar_cycle(hour = 7)
#' x <- download_current_metar_cycle(hour = 12)
#' x <- download_current_metar_cycle(hour = 16)
#' x <- download_current_metar_cycle(hour = 23)
#' \dontrun{
#' x <- lapply(0:23, download_current_metar_cycle)
#' }
download_current_metar_cycle <- function(hour){
  ftpurl <- "https://tgftp.nws.noaa.gov/data/observations/metar/cycles"
  url <- sprintf("%s/%02dZ.TXT", ftpurl, hour)
  
  x <- readLines(url)
  
  idx_time    <- seq.int(from = 1, to = length(x), by = 3)
  idx_metar   <- seq.int(from = 2, to = length(x), by = 3)
  metars      <- data.frame(time = x[idx_time], metar = x[idx_metar], stringsAsFactors = FALSE)
  metars$time <- gsub("/", "-", metars$time)
  metars$time <- fasttime::fastPOSIXct(metars$time, tz = "GMT", required.components = 5)
  metars
}
  

