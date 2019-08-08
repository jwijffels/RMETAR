
<!-- README.md is generated from README.Rmd. Please edit that file -->

# RMETAR

<!-- badges: start -->

[![Travis build
status](https://travis-ci.org/jwijffels/RMETAR.svg?branch=master)](https://travis-ci.org/jwijffels/RMETAR)
[![CRAN
status](https://www.r-pkg.org/badges/version/RMETAR)](https://CRAN.R-project.org/package=RMETAR)
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
#> Classes 'decodedMETAR' and 'data.frame': 1 obs. of  193 variables:
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
#>  $ SKY_2ndSite_LOC            : chr NA
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
#>  $ Indeterminant3_6HrPrecip   : logi FALSE
#>  $ Indeterminant_24HrPrecip   : logi FALSE
#>  $ CIGNO                      : logi FALSE
#>  $ SLPNO                      : logi TRUE
#>  $ ACFTMSHP                   : logi TRUE
#>  $ NOSPECI                    : logi FALSE
#>  $ FIRST                      : logi FALSE
#>  $ LAST                       : logi FALSE
#>  $ SunSensorOut               : logi FALSE
#>  $ AUTO                       : logi TRUE
#>  $ COR                        : logi FALSE
#>  $ NIL_rpt                    : logi FALSE
#>  $ CAVOK                      : logi FALSE
#>  $ RVRNO                      : logi TRUE
#>  $ A_altstng                  : logi TRUE
#>  $ Q_altstng                  : logi FALSE
#>  $ VIRGA                      : logi FALSE
#>  $ VOLCASH                    : logi FALSE
#>  $ GR                         : logi FALSE
#>  $ CHINO                      : logi FALSE
#>  $ VISNO                      : logi FALSE
#>  $ PNO                        : logi FALSE
#>  $ PWINO                      : logi FALSE
#>  $ FZRANO                     : logi FALSE
#>  $ TSNO                       : logi FALSE
#>  $ DollarSign                 : logi FALSE
#>  $ PRESRR                     : logi FALSE
#>  $ PRESFR                     : logi FALSE
#>  $ Wshft_FROPA                : logi FALSE
#>  $ OCNL_LTG                   : logi FALSE
#>  $ FRQ_LTG                    : logi FALSE
#>  $ CNS_LTG                    : logi FALSE
#>  $ CG_LTG                     : logi FALSE
#>  $ IC_LTG                     : logi FALSE
#>  $ CC_LTG                     : logi FALSE
#>  $ CA_LTG                     : logi FALSE
#>  $ DSNT_LTG                   : logi FALSE
#>  $ AP_LTG                     : logi FALSE
#>  $ VcyStn_LTG                 : logi FALSE
#>  $ OVHD_LTG                   : logi FALSE
#>  $ LightningVCTS              : logi FALSE
#>  $ LightningTS                : logi FALSE
#>  $ visibilityIsUpperBound     : logi FALSE
#>  $ TornadicDistance           : int NA
#>  $ ob_hour                    : int 8
#>  $ ob_minute                  : int 58
#>  $ ob_date                    : int 24
#>  $ minWnDir                   : int NA
#>  $ maxWnDir                   : int NA
#>  $ VertVsby                   : int NA
#>  $ temp                       : int 18
#>  $ dew_pt_temp                : int 12
#>  $ QFE                        : int NA
#>  $ hectoPasc_altstng          : int NA
#>  $ char_prestndcy             : int 8
#>  $ minCeiling                 : int NA
#>  $ maxCeiling                 : int NA
#>  $ WshfTime_hour              : int NA
#>  $ WshfTime_minute            : int NA
#>  $ min_vrbl_wind_dir          : int NA
#>  $ max_vrbl_wind_dir          : int NA
#>  $ PKWND_dir                  : int NA
#>  $ PKWND_speed                : int NA
#>  $ PKWND_hour                 : int NA
#>  $ PKWND_minute               : int NA
#>  $ SKY_2ndSite_Meters         : int 1851303080
#>  $ Ceiling                    : int NA
#>  $ Estimated_Ceiling          : int NA
#>  $ SNINCR                     : int NA
#>  $ SNINCR_TotalDepth          : int NA
#>  $ SunshineDur                : int NA
#>  $ ObscurAloftHgt             : int NA
#>  $ VrbSkyLayerHgt             : int NA
#>  $ Num8thsSkyObscured         : int NA
#>  $ CIG_2ndSite_Meters         : int NA
#>  $ snow_depth                 : int NA
#>  $ BTornadicHour              : int NA
#>  $ BTornadicMinute            : int NA
#>  $ ETornadicHour              : int NA
#>  $ ETornadicMinute            : int NA
#>  $ SectorVsby                 : num NA
#>  $ WaterEquivSnow             : num NA
#>  $ VSBY_2ndSite               : num NA
#>  $ prevail_vsbySM             : num 10
#>  $ prevail_vsbyM              : num NA
#>  $ prevail_vsbyKM             : num NA
#>  $ prestndcy                  : num 0.3
#>  $ precip_amt                 : num NA
#>  $ precip_24_amt              : num NA
#>  $ maxtemp                    : num NA
#>  $ mintemp                    : num NA
#>  $ max24temp                  : num NA
#>  $ min24temp                  : num NA
#>  $ minVsby                    : num NA
#>  $ maxVsby                    : num NA
#>  $ hourlyPrecip               : num NA
#>  $ TWR_VSBY                   : num NA
#>  $ SFC_VSBY                   : num NA
#>  $ Temp_2_tenths              : num 17.5
#>  $ DP_Temp_2_tenths           : num 12.4
#>  $ SLP                        : num NA
#>  $ GR_Size                    : num NA
#>  $ inches_altstng             : num 29.9
#>  $ Runway_VisRange_0          :List of 8
#>   ..$ runway_designator: chr NA
#>   ..$ vrbl_visRange    : logi FALSE
#>   ..$ below_min_RVR    : logi FALSE
#>   ..$ above_max_RVR    : logi FALSE
#>   ..$ visRange         : int NA
#>   ..$ Max_visRange     : int NA
#>   ..$ Min_visRange     : int NA
#>   ..$ Distance_Unit    : chr "meters"
#>  $ Runway_VisRange_1          :List of 8
#>   ..$ runway_designator: chr NA
#>   ..$ vrbl_visRange    : logi FALSE
#>   ..$ below_min_RVR    : logi FALSE
#>   ..$ above_max_RVR    : logi FALSE
#>   ..$ visRange         : int NA
#>   ..$ Max_visRange     : int NA
#>   ..$ Min_visRange     : int NA
#>   ..$ Distance_Unit    : chr "meters"
#>  $ Runway_VisRange_2          :List of 8
#>   ..$ runway_designator: chr NA
#>   ..$ vrbl_visRange    : logi FALSE
#>   ..$ below_min_RVR    : logi FALSE
#>   ..$ above_max_RVR    : logi FALSE
#>   ..$ visRange         : int NA
#>   ..$ Max_visRange     : int NA
#>   ..$ Min_visRange     : int NA
#>   ..$ Distance_Unit    : chr "meters"
#>  $ Runway_VisRange_3          :List of 8
#>   ..$ runway_designator: chr NA
#>   ..$ vrbl_visRange    : logi FALSE
#>   ..$ below_min_RVR    : logi FALSE
#>   ..$ above_max_RVR    : logi FALSE
#>   ..$ visRange         : int NA
#>   ..$ Max_visRange     : int NA
#>   ..$ Min_visRange     : int NA
#>   ..$ Distance_Unit    : chr "meters"
#>  $ Runway_VisRange_4          :List of 8
#>   ..$ runway_designator: chr NA
#>   ..$ vrbl_visRange    : logi FALSE
#>   ..$ below_min_RVR    : logi FALSE
#>   ..$ above_max_RVR    : logi FALSE
#>   ..$ visRange         : int NA
#>   ..$ Max_visRange     : int NA
#>   ..$ Min_visRange     : int NA
#>   ..$ Distance_Unit    : chr "meters"
#>  $ Runway_VisRange_5          :List of 8
#>   ..$ runway_designator: chr NA
#>   ..$ vrbl_visRange    : logi FALSE
#>   ..$ below_min_RVR    : logi FALSE
#>   ..$ above_max_RVR    : logi FALSE
#>   ..$ visRange         : int NA
#>   ..$ Max_visRange     : int NA
#>   ..$ Min_visRange     : int NA
#>   ..$ Distance_Unit    : chr "meters"
#>  $ Runway_VisRange_6          :List of 8
#>   ..$ runway_designator: chr NA
#>   ..$ vrbl_visRange    : logi FALSE
#>   ..$ below_min_RVR    : logi FALSE
#>   ..$ above_max_RVR    : logi FALSE
#>   ..$ visRange         : int NA
#>   ..$ Max_visRange     : int NA
#>   ..$ Min_visRange     : int NA
#>   ..$ Distance_Unit    : chr "meters"
#>  $ Runway_VisRange_7          :List of 8
#>   ..$ runway_designator: chr NA
#>   ..$ vrbl_visRange    : logi FALSE
#>   ..$ below_min_RVR    : logi FALSE
#>   ..$ above_max_RVR    : logi FALSE
#>   ..$ visRange         : int NA
#>   ..$ Max_visRange     : int NA
#>   ..$ Min_visRange     : int NA
#>   ..$ Distance_Unit    : chr "meters"
#>  $ Runway_VisRange_8          :List of 8
#>   ..$ runway_designator: chr NA
#>   ..$ vrbl_visRange    : logi FALSE
#>   ..$ below_min_RVR    : logi FALSE
#>   ..$ above_max_RVR    : logi FALSE
#>   ..$ visRange         : int NA
#>   ..$ Max_visRange     : int NA
#>   ..$ Min_visRange     : int NA
#>   ..$ Distance_Unit    : chr "meters"
#>  $ Runway_VisRange_9          :List of 8
#>   ..$ runway_designator: chr NA
#>   ..$ vrbl_visRange    : logi FALSE
#>   ..$ below_min_RVR    : logi FALSE
#>   ..$ above_max_RVR    : logi FALSE
#>   ..$ visRange         : int NA
#>   ..$ Max_visRange     : int NA
#>   ..$ Min_visRange     : int NA
#>   ..$ Distance_Unit    : chr "meters"
#>  $ Runway_VisRange_10         :List of 8
#>   ..$ runway_designator: chr NA
#>   ..$ vrbl_visRange    : logi FALSE
#>   ..$ below_min_RVR    : logi FALSE
#>   ..$ above_max_RVR    : logi FALSE
#>   ..$ visRange         : int NA
#>   ..$ Max_visRange     : int NA
#>   ..$ Min_visRange     : int NA
#>   ..$ Distance_Unit    : chr "meters"
#>  $ Runway_VisRange_11         :List of 8
#>   ..$ runway_designator: chr NA
#>   ..$ vrbl_visRange    : logi FALSE
#>   ..$ below_min_RVR    : logi FALSE
#>   ..$ above_max_RVR    : logi FALSE
#>   ..$ visRange         : int NA
#>   ..$ Max_visRange     : int NA
#>   ..$ Min_visRange     : int NA
#>   ..$ Distance_Unit    : chr "meters"
#>  $ Dispatch_VisRange          :List of 6
#>   ..$ vrbl_visRange: logi FALSE
#>   ..$ below_min_DVR: logi FALSE
#>   ..$ above_max_DVR: logi FALSE
#>   ..$ visRange     : int NA
#>   ..$ Max_visRange : int NA
#>   ..$ Min_visRange : int NA
#>  $ Recent_Wx_0                :List of 5
#>   ..$ Recent_weather: chr NA
#>   ..$ Bhh           : int NA
#>   ..$ Bmm           : int NA
#>   ..$ Ehh           : int NA
#>   ..$ Emm           : int NA
#>  $ Recent_Wx_1                :List of 5
#>   ..$ Recent_weather: chr NA
#>   ..$ Bhh           : int NA
#>   ..$ Bmm           : int NA
#>   ..$ Ehh           : int NA
#>   ..$ Emm           : int NA
#>  $ Recent_Wx_2                :List of 5
#>   ..$ Recent_weather: chr NA
#>   ..$ Bhh           : int NA
#>   ..$ Bmm           : int NA
#>   ..$ Ehh           : int NA
#>   ..$ Emm           : int NA
#>  $ windstruct                 :List of 5
#>   ..$ windUnits: chr "KT"
#>   ..$ windVRB  : logi FALSE
#>   ..$ windDir  : int 240
#>   ..$ windSpeed: int 18
#>   ..$ windGust : int NA
#>  $ Cloud_Conditions_0         :List of 4
#>   ..$ cloud_type      : chr "CLR"
#>   ..$ cloud_hgt_char  : chr NA
#>   ..$ other_cld_phenom: chr NA
#>   ..$ cloud_hgt_meters: int NA
#>  $ Cloud_Conditions_1         :List of 4
#>   ..$ cloud_type      : chr NA
#>   ..$ cloud_hgt_char  : chr NA
#>   ..$ other_cld_phenom: chr NA
#>   ..$ cloud_hgt_meters: int NA
#>  $ Cloud_Conditions_2         :List of 4
#>   ..$ cloud_type      : chr NA
#>   ..$ cloud_hgt_char  : chr NA
#>   ..$ other_cld_phenom: chr NA
#>   ..$ cloud_hgt_meters: int NA
#>  $ Cloud_Conditions_3         :List of 4
#>   ..$ cloud_type      : chr NA
#>   ..$ cloud_hgt_char  : chr NA
#>   ..$ other_cld_phenom: chr NA
#>   ..$ cloud_hgt_meters: int NA
#>  $ Cloud_Conditions_4         :List of 4
#>   ..$ cloud_type      : chr NA
#>   ..$ cloud_hgt_char  : chr NA
#>   ..$ other_cld_phenom: chr NA
#>   ..$ cloud_hgt_meters: int NA
#>  $ Cloud_Conditions_5         :List of 4
#>   ..$ cloud_type      : chr NA
#>   ..$ cloud_hgt_char  : chr NA
#>   ..$ other_cld_phenom: chr NA
#>   ..$ cloud_hgt_meters: int NA
#>  $ METAR                      : chr "KSUU 240858Z AUTO 24018KT 10SM CLR 18/12 A2988 RMK AO2 SLPNO T01750124 58003 RVRNO"
#>  $ printout                   : chr "\n\n\n/*******************************************/\n/*    THE DECODED METAR REPORT FOLLOWS     */\n/**********"| __truncated__
```
