local({
  lib_url <- "https://github.com/flightaware/mdsplib/archive/master.zip"
  
  if (!exists("tf")) tf <- tempfile(fileext = ".zip")
  if (!file.exists(tf)) download.file(lib_url, destfile = tf)
  
  local_files <- list.files("src", full.names = TRUE)
  exclude <- c(
    "src/Makevars",
    "src/METAR_R_extraction.c",
    "src/METAR_R_extraction.cold"
  )
  exclude <- c(
    exclude, 
    file.path("src",list.files("src", pattern = "^r_.*\\.[c|cpp]")),
    file.path("src",list.files("src", pattern = "^METAR_R.*\\.[c|cpp]"))
  )
  to_delete <- setdiff(local_files, exclude)
  file.remove(to_delete)
  
  extract_folder <- function(folder){
    files <- unzip(tf, list = TRUE)$Name
    idx <- grep(
      glue::glue(".*?/{folder}/.*?\\.[ch]$"), 
      files)
    extract <- files[idx]
    exclude <- c(
      "mdsplib-master/src/metar_test.h",
      "mdsplib-master/src/metar_test.c"
    )
    extract <- setdiff(extract, exclude)
    # files
    unzip(tf, files = extract, exdir = folder, junkpaths = TRUE)
  }
  
  # folder <- "src"
  extract_folder("src")
  extract_folder("include")
  
  
  # source("scripts/comment_all_pragmas.R")
})

