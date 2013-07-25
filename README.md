RMETAR
======

A METAR decoder for R users, connecting to mdsplib (METAR Decoder Software Package Library - http://mdsplib.sourceforge.net/) 

# Installation
To install the package, do as follows.

    library(devtools)
    install_github("RMETAR", "jwijffels", subdir="/pkg")   

# Running RMETAR
The following example shows the basic usage on how to extract weather information.

    library(RMETAR)
    
    metarcode <- "KSUU 240858Z AUTO 24018KT 10SM CLR 18/12 A2988 RMK AO2 SLPNO T01750124 58003 RVRNO"
    result <- decodemetar(x = metarcode)
    str(result)
    result <- decodemetar(x = metarcode, printdecodedmetar=TRUE)
 

# Current METAR reports
Current and historical METAR data can be obtained from various places. The current METAR report for a given airport is available at the following URL where '$station$' is the four-letter ICAO airport station code.

    http://weather.noaa.gov/pub/data/observations/metar/stations/$station$.TXT

The METAR reports for all stations (worldwide) for any "cycle" (i.e., hour)  in the last 24 hours are available in a single file at the following URL where '$cycle$' is a 2-digit cycle number (e.g., "00", "05" or "23").  

    http://weather.noaa.gov/pub/data/observations/metar/cycles/$cycle$Z.TXT


# METAR specifications
The Federal Meteorological Handbook No.1. (FMH-1 1995), which describes the U.S. standards, is available online at http://www.ofcm.gov/fmh-1/fmh1.htm