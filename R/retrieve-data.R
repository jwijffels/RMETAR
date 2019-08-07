

#' @title Retrieve current METAR data from NOAA
#' @description Retrieve hourly cycles of METAR data from \url{https://tgftp.nws.noaa.gov/data/observations/metar/cycles}
#' @param hour an hour, either one of 0, 1, 2, up to 23
#' @return a data.frame with columns time and metar containing the METARS from the selected hour currently at \url{https://tgftp.nws.noaa.gov/data/observations/metar/cycles}
#' @export
#' @examples 
#' x <- download_current_metar_cycle(hour = 12)
#' \dontrun{
#' x <- download_current_metar_cycle(hour = 0)
#' x <- download_current_metar_cycle(hour = 7)
#' x <- download_current_metar_cycle(hour = 12)
#' x <- download_current_metar_cycle(hour = 16)
#' x <- download_current_metar_cycle(hour = 23)
#' x <- lapply(0:23, download_current_metar_cycle)
#' }
download_current_metar_cycle <- function(hour){
  ftpurl <- "https://tgftp.nws.noaa.gov/data/observations/metar/cycles"
  url <- sprintf("%s/%02dZ.TXT", ftpurl, hour)
  
  x <- readLines(url)
  
  idx_time    <- seq.int(from = 1, to = length(x), by = 3)
  idx_metar   <- seq.int(from = 2, to = length(x), by = 3)
  metars      <- data.frame(time = x[idx_time], metar = x[idx_metar], stringsAsFactors = FALSE)
  metars      <- unique(metars)
  metars$time <- gsub("/", "-", metars$time)
  metars$time <- fasttime::fastPOSIXct(metars$time, tz = "GMT", required.components = 5)
  metars
}
  

#' @title Fetch a list of airports
#' @description Fetch a list of airports from \url{http://ourairports.com/data}. This data is Public Domain.
#' @return a data.frame with columns id, continent, country, country_name, region, region_name, municipality, name, type, latitude, longitude, elevation, gps, iata, local_code, link, link_wikipedia
#' @export
#' @examples 
#' \dontrun{
#' x <- download_airports()
#' }
download_airports <- function(){
  cat("Started importing http://ourairports.com/data/regions.csv", sep = "\n")
  regions    <- utils::read.csv("http://ourairports.com/data/regions.csv", encoding = "UTF-8", na.strings = "", stringsAsFactors = FALSE)
  cat("Started importing http://ourairports.com/data/countries.csv", sep = "\n")
  countries  <- utils::read.csv("http://ourairports.com/data/countries.csv", encoding = "UTF-8", na.strings = "", stringsAsFactors = FALSE)
  cat("Started importing http://ourairports.com/data/regions.csv", sep = "\n")
  airports   <- utils::read.csv("http://ourairports.com/data/regions.csv", encoding = "UTF-8", na.strings = "", stringsAsFactors = FALSE, 
                         col.names = c("id", "ident", "type", "name", "latitude_deg", "longitude_deg", "elevation_ft", "continent", "iso_country", "iso_region", "municipality", "scheduled_service", "gps_code", "iata_code", "local_code", "home_link", "wikipedia_link", "keywords"), 
                         colClasses = c("integer", "character", "character", "character", "numeric", "numeric", "integer", "character", "character", "character", "character", "character", "character", "character", "character", "character", "character", "character"))
  x <- merge(airports, countries[, c("code", "name")], by.x = "iso_country", by.y = "code", suffixes = c("", "_country"), order = FALSE)
  x <- merge(x, regions[, c("code", "name")], by.x = "iso_region", by.y = "code", suffixes = c("", "_region"), order = FALSE)
  x <- x[, c("ident", "continent", "iso_country", "name_country", "iso_region", "name_region", "municipality", "name", "type", 
             "latitude_deg", "longitude_deg", "elevation_ft",  
             "gps_code", "iata_code", "local_code", "home_link", "wikipedia_link")]
  colnames(x) <- c("id", "continent", "country", "country_name", "region", "region_name", "municipality", "name", "type", 
                   "latitude", "longitude", "elevation", "gps", "iata", "local_code", "link", "link_wikipedia")
  x
}

