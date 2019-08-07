metarcode <- "KSUU 240858Z AUTO 24018KT 10SM CLR 18/12 A2988 RMK AO2 SLPNO T01750124 58003 RVRNO"
expect_true(is.data.frame(decodemetar(x = metarcode)))
expect_true(inherits(decodemetar(x = metarcode), "decodedMETAR"))
expect_equal(decodemetar(x = metarcode)$METAR, metarcode)
