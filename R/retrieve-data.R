#' Retrieve current METAR data from NOAA.
#' 
#' Retrieve hourly cycles of METAR data from \url{https://tgftp.nws.noaa.gov/data/observations/metar/cycles}
#' 
#' @param hour an hour, either one of 0, 1, 2, up to 23
#' @return a data.frame with columns time and metar containing the METARS from the selected hour currently at \url{https://tgftp.nws.noaa.gov/data/observations/metar/cycles}
#' @export
#' @examples
#' x <- download_metar(hour = 12)
#' \dontrun{
#' x <- download_metar(hour = 0)
#' x <- download_metar(hour = 7)
#' x <- download_metar(hour = 12)
#' x <- download_metar(hour = 16)
#' x <- download_metar(hour = 23)
#' x <- lapply(0:23, download_metar)
#' }
download_metar <- function(hour) {
  ftpurl <- "https://tgftp.nws.noaa.gov/data/observations/metar/cycles"
  url <- sprintf("%s/%02dZ.TXT", ftpurl, hour)

  x <- readLines(url)

  idx_time <- seq.int(from = 1, to = length(x), by = 3)
  idx_metar <- seq.int(from = 2, to = length(x), by = 3)
  metars <- data.frame(
    time = x[idx_time], 
    metar = x[idx_metar], 
    stringsAsFactors = FALSE
    )
  metars <- unique(metars)
  metars$time <- gsub("/", "-", metars$time)
  metars$time <- fasttime::fastPOSIXct(metars$time, tz = "GMT", required.components = 5)
  metars
}


#' Fetch a list of airports.
#' 
#' Fetch a list of airports from \url{http://ourairports.com/data}. This data is Public Domain.
#' 
#' @return a data.frame with columns id, continent, country, country_name, region, region_name, municipality, name, type, latitude (in degrees), longitude (in degrees), elevation (in feet), gps, iata, local_code, link, link_wikipedia
#' @export
#' @examples
#' \dontrun{
#' x <- download_airports()
#' }
download_airports <- function() {
  message("Started importing http://ourairports.com/data/regions.csv")
  regions <- utils::read.csv(
    "http://ourairports.com/data/regions.csv", 
    encoding = "UTF-8", 
    na.strings = "", 
    stringsAsFactors = FALSE
    )
  
  message("Started importing http://ourairports.com/data/countries.csv")
  countries <- utils::read.csv(
    "http://ourairports.com/data/countries.csv", 
    encoding = "UTF-8", 
    na.strings = "", 
    stringsAsFactors = FALSE
    )
  
  message("Started importing http://ourairports.com/data/airports.csv")
  airports <- utils::read.csv(
    "http://ourairports.com/data/airports.csv",
    encoding = "UTF-8", 
    na.strings = "", 
    stringsAsFactors = FALSE,
    col.names = c("id", "ident", "type", "name", "latitude_deg", 
                  "longitude_deg", "elevation_ft", "continent", "iso_country", 
                  "iso_region", "municipality", "scheduled_service", "gps_code",
                  "iata_code", "local_code", "home_link", "wikipedia_link", 
                  "keywords"),
    colClasses = c("integer", "character", "character", "character", "numeric",
                   "numeric", "integer", "character", "character", "character",
                   "character", "character", "character", "character",
                   "character", "character", "character", "character")
  )
  
  message("Merging airports and countries...")
  x <- merge(airports, countries[, c("code", "name")], 
             by.x = "iso_country", 
             by.y = "code", 
             suffixes = c("", "_country"), 
             order = FALSE
             )

  message("...and regions")
  x <- merge(x, regions[, c("code", "name")], 
             by.x = "iso_region", 
             by.y = "code", 
             suffixes = c("", "_region"), 
             order = FALSE
             )
  x <- x[, c(
    "ident", "iata_code", "continent", "iso_country", "name_country", "iso_region", 
    "name_region", "municipality", "name", "type",
    "latitude_deg", "longitude_deg", "elevation_ft",
    "gps_code", "local_code", "home_link", "wikipedia_link"
  )]
  colnames(x) <- c(
    "id", "continent", "country", "country_name", "region", "region_name", 
    "municipality", "name", "type", "latitude", "longitude", "elevation", "gps",
    "iata", "local_code", "link", "link_wikipedia"
  )
  message("Done")
  x
}
