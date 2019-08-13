metarcode <- "KSUU 240858Z AUTO 24018KT 10SM CLR 18/12 A2988 RMK AO2 SLPNO T01750124 58003 RVRNO"

z <- decodemetar(x = metarcode)

expect_true(is.data.frame(z))
expect_true(inherits(z, "decodedMETAR"))
expect_equal(ncol(z), 268L)
expect_equal(nrow(z), 1L)
expect_equal(z$METAR, metarcode)
