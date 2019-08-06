c_files <- c(
  list.files("src", pattern = "\\.[ch]$", full.names = TRUE),
  list.files("include", pattern = "\\.[ch]$", full.names = TRUE)
)

comment_lines <- function(x) {
  paste0("// ", x)
}

gsub_comment <- function(x, pattern) {
  gsub(
    glue::glue("^{pattern}"), 
    glue::glue("// {pattern}"), 
    x)
}

mdsp_bool <- "
#ifndef mdsp_bool
#define mdsp_bool
typedef unsigned short int MDSP_BOOL;
#endif
"

library(magrittr)
for (f in c_files) {
  message(f)
  f %>% 
    readLines() %>% 
    gsub_comment("#pragma page") %>% 
    gsub_comment("#pragma linkage") %>% 
    gsub_comment("#pragma title") %>% 
    gsub_comment("#pragma subtitle") %>% 
    gsub_comment("#pragma comment") %>% 
    gsub_comment("MDSP_BOOL itoa") %>% 
    gsub_comment("int strcmpi") %>% 
    gsub("typedef unsigned short int MDSP_BOOL;", mdsp_bool, fixed=TRUE, .) %>% 
    writeLines(con = f)
}


