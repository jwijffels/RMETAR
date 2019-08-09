
local({
  # download mdsplib and unzip
  if (isNamespaceLoaded("RMETAR")) unloadNamespace("RMETAR")
  lib_url <- "https://github.com/flightaware/mdsplib/archive/master.zip"
  
  if (!exists("tf")) tf <- tempfile(fileext = ".zip")
  if (!file.exists(tf)) download.file(lib_url, destfile = tf)
  
  # delete local files
  local_files <- list.files("src", full.names = TRUE)
  exclude <- c(
    "src/Makevars",
    "src/METAR_R_extraction.c",
    "src/METAR_R_extraction.cold",
    file.path("src", list.files("src", pattern = "^r_.*\\.[c|cpp|h]")),
    file.path("src", list.files("src", pattern = "^METAR_R.*\\.[c|cpp|h]"))
  )
  to_delete <- setdiff(local_files, exclude)
  file.remove(to_delete)
  
  # function to extract necessary mdsplib files
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
    unzip(tf, files = extract, exdir = "src", junkpaths = TRUE)
  }
  
  # extract src and include into src/
  extract_folder("src")
  extract_folder("include")
  
  
  # fix for having moved metar.h from include/ into src/
  c_files <- list.files("src", pattern = "\\.[ch]$", full.names = TRUE)
  
  for (f in c_files) {
    message(f)
    f %>% 
      readLines() %>% 
      gsub('#include "../include/metar.h"', '#include "metar.h"', fixed=TRUE, .) %>% 
      writeLines(con = f)
  }
  
})

