context("decode")
test_that("decoding works", {
  metarcode <- "KSUU 240858Z AUTO 24018KT 10SM CLR 18/12 A2988 RMK AO2 SLPNO T01750124 58003 RVRNO"
  result <- decodemetar(x = metarcode)
  
  expect_is(result, "list")
  expect_equal(result$metar, metarcode)
})
