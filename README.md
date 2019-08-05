
<!-- README.md is generated from README.Rmd. Please edit that file -->

# RMETAR

<!-- badges: start -->

<!-- badges: end -->

The goal of RMETAR is to provide a METAR decoder for R users, connecting
to `mdsplib` (METAR Decoder Software Package Library -
<https://github.com/flightaware/mdsplib>)

## Installation

~~You can install the released version of RMETAR from
[CRAN](https://CRAN.R-project.org) with:~~

``` r
install.packages("RMETAR")
```

And the development version from [GitHub](https://github.com/) with:

``` r
# install.packages("remotes")
remotes::install_github("jwijffels/RMETAR")
```

## Obtaining METAR reports

Current and historical METAR data can be obtained from various places.
The current METAR report for a given airport is available at the
following URL where ‘{station}’ is the four-letter ICAO airport station
code.

    https://aviationweather.gov/metar/data?ids={station}

For example, you can find the METAR for London Heathrow (ICAO EGLL) at
<https://aviationweather.gov/metar/data?ids=egll>

You can also query the NOAA data service at
<https://aviationweather.gov/dataserver/example?datatype=metar>, where
you can access METARS using search strings to retrieve data in XML
format

## METAR specifications

The Federal Meteorological Handbook No.1. (FMH-1 1995), which describes
the U.S. standards, is available online at
<http://www.ofcm.gov/fmh-1/fmh1.htm>

## Example

``` r
library(RMETAR)
```

``` r
metarcode <- "KSUU 240858Z AUTO 24018KT 10SM CLR 18/12 A2988 RMK AO2 SLPNO T01750124 58003 RVRNO"
result <- decodemetar(x = metarcode, printdecodedmetar=TRUE)
#> 
#> 
#> 
#> /*******************************************/
#> /*    THE DECODED METAR REPORT FOLLOWS     */
#> /*******************************************/
#> 
#> STATION ID          : KSUU
#> OBSERVATION DAY     : 24
#> OBSERVATION HOUR    : 8
#> OBSERVATION MINUTE  : 58
#> AUTO REPORT         : TRUE
#> WIND DIRECTION      : 240
#> WIND SPEED          : 18
#> WIND UNITS          : KT
#> PREVAIL VSBY (SM)   : 10.000
#> RVRNO               : TRUE
#> CLOUD COVER         : CLR
#> TEMP. (CELSIUS)     : 18
#> D.P. TEMP. (CELSIUS): 12
#> ALTIMETER (INCHES)  : 29.88
#> AUTO INDICATOR      : AO2
#> SLPNO               : TRUE
#> TMP2TENTHS (CELSIUS): 17.5
#> DPT2TENTHS (CELSIUS): 12.4
#> CHAR PRESS TENDENCY : 8
#> PRES. TENDENCY (hPa): 0.3
```

The decoded data is in a nested list:

``` r
str(result, max.level = 2)
#> List of 11
#>  $ characters          :List of 5
#>   ..$ single                  : Named chr [1:30] NA NA NA "KSUU" ...
#>   .. ..- attr(*, "names")= chr [1:30] "synoptic_cloud_type" "snow_depth_group" "codename" "stnid" ...
#>   ..$ wxobstruct              : chr [1:10] NA NA NA NA ...
#>   ..$ partialobscurationamt   : chr [1:2] NA NA
#>   ..$ partialobscurationphenom: chr [1:2] NA NA
#>   ..$ sfcobscuration          : chr [1:6] NA NA NA NA ...
#>  $ mdspbool            : Named int [1:42] 0 0 0 1 0 0 28248 0 0 1 ...
#>   ..- attr(*, "names")= chr [1:42] "indeterminant3_6hrprecip" "indeterminant_24hrprecip" "cigno" "slpno" ...
#>  $ integers            : Named int [1:37] NA 8 58 24 NA NA NA 18 12 NA ...
#>   ..- attr(*, "names")= chr [1:37] "tornadicdistance" "ob_hour" "ob_minute" "ob_date" ...
#>  $ numerics            : Named num [1:23] 4.24e-313 NA NA NA 1.00e+01 ...
#>   ..- attr(*, "names")= chr [1:23] "sectorvsby" "waterequivsnow" "vsby_2ndsite" "prevail_vsbysm" ...
#>  $ runway.visualrange  :List of 12
#>   ..$ :List of 7
#>   ..$ :List of 7
#>   ..$ :List of 7
#>   ..$ :List of 7
#>   ..$ :List of 7
#>   ..$ :List of 7
#>   ..$ :List of 7
#>   ..$ :List of 7
#>   ..$ :List of 7
#>   ..$ :List of 7
#>   ..$ :List of 7
#>   ..$ :List of 7
#>  $ dispatch.visualrange:List of 6
#>   ..$ vrbl.visrange: int 0
#>   ..$ below.min.dvr: int 0
#>   ..$ above.max.dvr: int 0
#>   ..$ visrange     : int NA
#>   ..$ max.visrange : int NA
#>   ..$ min.visrange : int NA
#>  $ recent.weather      :List of 3
#>   ..$ :List of 5
#>   ..$ :List of 5
#>   ..$ :List of 5
#>  $ wind                :List of 5
#>   ..$ windunits: chr "KT"
#>   ..$ windvrb  : int 0
#>   ..$ winddir  : int 240
#>   ..$ windspeed: int 18
#>   ..$ windgust : int NA
#>  $ cloud.conditions    :List of 6
#>   ..$ :List of 4
#>   ..$ :List of 4
#>   ..$ :List of 4
#>   ..$ :List of 4
#>   ..$ :List of 4
#>   ..$ :List of 4
#>  $ printout.mdsplib    : chr "\n\n\n/*******************************************/\n/*    THE DECODED METAR REPORT FOLLOWS     */\n/**********"| __truncated__
#>  $ metar               : chr "KSUU 240858Z AUTO 24018KT 10SM CLR 18/12 A2988 RMK AO2 SLPNO T01750124 58003 RVRNO"
#>  - attr(*, "class")= chr [1:2] "decodedMETAR" "list"
```
