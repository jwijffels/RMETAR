lib_url <- "https://github.com/flightaware/mdsplib/archive/master.zip"

if (!exists("tf")) tf <- tempfile(fileext = ".zip")
if (!file.exists(tf)) download.file(lib_url, destfile = tf)

local({
  local_files <- list.files("src", full.names = TRUE)
  exclude <- c(
    "src/Makevars",
    "src/METAR_R_extraction.c"
  )
  to_delete <- setdiff(local_files, exclude)
  file.remove(to_delete)
})

extract_folder <- function(folder){
  files <- unzip(tf, list = TRUE)$Name
  idx <- grep(
    glue::glue(".*?/{folder}/.*?\\.[ch]$"), 
    files)
  extract <- files[idx]
  # extract
  # files
  unzip(tf, files = extract, exdir = folder, junkpaths = TRUE)
}

extract_folder("src")
extract_folder("include")

