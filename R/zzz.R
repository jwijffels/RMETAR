.onUnload <- function (libpath) {
  library.dynam.unload("RMETAR", libpath)
}