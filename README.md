
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
```

The decoded data is in a nested list:

``` r
str(result, max.level = 2)
#> List of 66
#>  $ synoptic_cloud_type        : chr NA
#>  $ snow_depth_group           : chr NA
#>  $ codeName                   : chr NA
#>  $ stnid                      : chr "KSUU"
#>  $ horiz_vsby                 : chr NA
#>  $ dir_min_horiz_vsby         : chr NA
#>  $ vsby_Dir                   : chr NA
#>  $ WxObstruct_0               : chr NA
#>  $ WxObstruct_1               : chr NA
#>  $ WxObstruct_2               : chr NA
#>  $ WxObstruct_3               : chr NA
#>  $ WxObstruct_4               : chr NA
#>  $ WxObstruct_5               : chr NA
#>  $ WxObstruct_6               : chr NA
#>  $ WxObstruct_7               : chr NA
#>  $ autoIndicator              : chr "AO2"
#>  $ VSBY_2ndSite_LOC           : chr NA
#>  $ SKY_2ndSite_LOC            : chr "\035C\004"
#>  $ SKY_2ndSite                : chr NA
#>  $ SectorVsby_Dir             : chr NA
#>  $ ObscurAloft                : chr NA
#>  $ ObscurAloftSkyCond         : chr NA
#>  $ VrbSkyBelow                : chr NA
#>  $ VrbSkyAbove                : chr NA
#>  $ LTG_DIR                    : chr NA
#>  $ CloudLowMediumHigh         : chr NA
#>  $ CIG_2ndSite_LOC            : chr NA
#>  $ VIRGA_DIR                  : chr NA
#>  $ TornadicType               : chr NA
#>  $ TornadicLOC                : chr NA
#>  $ TornadicDIR                : chr NA
#>  $ TornadicMovDir             : chr NA
#>  $ CHINO_LOC                  : chr NA
#>  $ VISNO_LOC                  : chr NA
#>  $ PartialObscurationAmt_0    : chr NA
#>  $ PartialObscurationAmt_1    : chr NA
#>  $ PartialObscurationAmt_2    : chr NA
#>  $ PartialObscurationAmt_3    : chr NA
#>  $ PartialObscurationAmt_4    : chr NA
#>  $ PartialObscurationAmt_5    : chr NA
#>  $ PartialObscurationAmt_6    : chr NA
#>  $ PartialObscurationPhenom_0 : chr NA
#>  $ PartialObscurationPhenom_1 : chr NA
#>  $ PartialObscurationPhenom_2 : chr NA
#>  $ PartialObscurationPhenom_3 : chr NA
#>  $ PartialObscurationPhenom_4 : chr NA
#>  $ PartialObscurationPhenom_5 : chr NA
#>  $ PartialObscurationPhenom_6 : chr NA
#>  $ PartialObscurationPhenom_7 : chr NA
#>  $ PartialObscurationPhenom_8 : chr NA
#>  $ PartialObscurationPhenom_9 : chr NA
#>  $ PartialObscurationPhenom_10: chr NA
#>  $ PartialObscurationPhenom_11: chr NA
#>  $ SfcObscuration_0           : chr NA
#>  $ SfcObscuration_1           : chr NA
#>  $ SfcObscuration_2           : chr NA
#>  $ SfcObscuration_3           : chr NA
#>  $ SfcObscuration_4           : chr NA
#>  $ SfcObscuration_5           : chr NA
#>  $ SfcObscuration_6           : chr NA
#>  $ SfcObscuration_7           : chr NA
#>  $ SfcObscuration_8           : chr NA
#>  $ SfcObscuration_9           : chr NA
#>  $ TS_LOC                     : chr NA
#>  $ TS_MOVMNT                  : chr NA
#>  $ METAR                      : chr "KSUU 240858Z AUTO 24018KT 10SM CLR 18/12 A2988 RMK AO2 SLPNO T01750124 58003 RVRNO"
#>  - attr(*, "class")= chr [1:2] "decodedMETAR" "list"
```
