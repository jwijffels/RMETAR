RMETAR
======

A METAR decoder for R users, connecting to mdsplib (METAR Decoder Software Package Library - http://mdsplib.sourceforge.net/) 

# Installation
To start up building recommendation engines, install the R packages Myrrixjars and Myrrix as follows.

    library(devtools)
    install_github("RMETAR", "jwijffels", subdir="/pkg")   

# Running RMETAR
The following example shows the basic usage on how to extract weather information.

    library(RMETAR)
    
    metarcode <- "KSUU 240858Z AUTO 24018KT 10SM CLR 18/12 A2988 RMK AO2 SLPNO T01750124 58003 RVRNO"
    result <- decodemetar(x = metarcode)
    str(result)
    result <- decodemetar(x = metarcode, printdecodedmetar=TRUE)
 
