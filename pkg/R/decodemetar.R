#' @title Decode a METAR report.
#'
#' @description Decode a METAR report.
#'
#' @useDynLib RMETAR
#' @param x a character string with the METAR (Meteorological Aerodrome Report) report
#' @param printdecodedmetar a logical, indicating to print out the report in human readable format as decoded
#' by the mdsplib library
#' @return 
#' a list of elements with information contained in the METAR string. 
#' The list contains data of a similar structure as the decoded_METAR structure in /src/metar.h.
#' See the examples.
#' @export 
#' @examples
#' metarcode <- "KSUU 240858Z AUTO 24018KT 10SM CLR 18/12 A2988 RMK AO2 SLPNO T01750124 58003 RVRNO"
#' result <- decodemetar(x = metarcode)
#' str(result)
#' result <- decodemetar(x = metarcode, printdecodedmetar=TRUE)
decodemetar <- function(x, printdecodedmetar=FALSE){
  x <- as.character(x)
  printdecodedmetar <- as.logical(printdecodedmetar)
  result <- .Call("decodeMETAR", x, printdecodedmetar, PACKAGE="RMETAR")
  names(result) <- c("characters","mdspbool","integers","numerics",
                     "runway.visualrange","dispatch.visualrange","recent.weather","wind","cloud.conditions",
                     "printout.mdsplib")
  make_underscore_names <- function(x){
    names(x) <- make.names(tolower(names(x)), allow_=FALSE)
    x
  }
  names(result$characters) <- tolower(c("single","WxObstruct",
                                        "PartialObscurationAmt","PartialObscurationPhenom","SfcObscuration"))
  names(result$characters$single) <- tolower(c("synoptic_cloud_type", "snow_depth_group", "codeName", "stnid", "horiz_vsby", "dir_min_horiz_vsby", 
                                               "vsby_Dir", "autoIndicator", "VSBY_2ndSite_LOC", "SKY_2ndSite_LOC", "SKY_2ndSite", "ObscurAloft", 
                                               "ObscurAloftSkyCond", "VrbSkyBelow", "VrbSkyAbove", "LTG_DIR", "CloudLowMediumHigh", "CIG_2ndSite_LOC", 
                                               "VIRGA_DIR", "TornadicType", "TornadicLOC", "TornadicDIR", "TornadicMovDir", "CHINO_LOC", "VISNO_LOC", 
                                               "charPrevailVsby", "charVertVsby", "TS_LOC", "TS_MOVMNT"))
  names(result$mdspbool) <- tolower(c("Indeterminant3_6HrPrecip", "Indeterminant_24HrPrecip", "CIGNO", "SLPNO", "ACFTMSHP", "NOSPECI", "FIRST", "LAST", 
                                      "SunSensorOut", "AUTO", "COR", "NIL_rpt", "CAVOK", "RVRNO", "A_altstng", "Q_altstng", "VIRGA", "VOLCASH", 
                                      "GR", "CHINO", "VISNO", "PNO", "PWINO", "FZRANO", "TSNO", "DollarSign", "PRESRR", "PRESFR", "Wshft_FROPA", 
                                      "OCNL_LTG", "FRQ_LTG", "CNS_LTG", "CG_LTG", "IC_LTG", "CC_LTG", "CA_LTG", "DSNT_LTG", "AP_LTG", "VcyStn_LTG", 
                                      "OVHD_LTG", "LightningVCTS", "LightningTS"))
  names(result$integers) <- tolower(c("TornadicDistance", "ob_hour", "ob_minute", "ob_date", "minWnDir", "maxWnDir", "VertVsby", "temp", 
                                      "dew_pt_temp", "QFE", "hectoPasc_altstng", "char_prestndcy", "minCeiling", 
                                      "maxCeiling", "WshfTime_hour", "WshfTime_minute", "min_vrbl_wind_dir", "max_vrbl_wind_dir", 
                                      "PKWND_dir", "PKWND_speed", "PKWND_hour", "PKWND_minute", "SKY_2ndSite_Meters", "Ceiling", 
                                      "Estimated_Ceiling", "SNINCR", "SNINCR_TotalDepth", "SunshineDur", "ObscurAloftHgt", 
                                      "VrbSkyLayerHgt", "Num8thsSkyObscured", "CIG_2ndSite_Meters", "snow_depth", "BTornadicHour", 
                                      "BTornadicMinute", "ETornadicHour", "ETornadicMinute"))
  names(result$numerics) <- tolower(c("SectorVsby", "WaterEquivSnow", "VSBY_2ndSite", "prevail_vsbySM", "prevail_vsbyM", "prevail_vsbyKM", 
                                      "prestndcy", "precip_amt", "precip_24_amt", "maxtemp", "mintemp", "max24temp", "min24temp", 
                                      "minVsby", "maxVsby", "hourlyPrecip", "TWR_VSBY", "SFC_VSBY", "Temp_2_tenths", "DP_Temp_2_tenths", 
                                      "SLP", "GR_Size", "inches_altstng"))
  result$runway.visualrange <- lapply(result$runway.visualrange, FUN=make_underscore_names)
  result$recent.weather <- lapply(result$recent.weather, FUN=make_underscore_names)
  result$cloud.conditions <- lapply(result$cloud.conditions, FUN=make_underscore_names)
  result$dispatch.visualrange <- make_underscore_names(result$dispatch.visualrange)
  result$wind <- make_underscore_names(result$wind)
  result$metar <- x
  if(printdecodedmetar){
    cat(result$printout.mdsplib)
  }
  class(result) <- c("decodedMETAR", "list")
  result
}


