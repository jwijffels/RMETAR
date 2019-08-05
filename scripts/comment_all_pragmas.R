c_files <- list.files("src", pattern = "\\.[ch]$", full.names = TRUE)

library(magrittr)
for (f in c_files) {
  message(f)
  f %>% 
    readLines() %>% 
    gsub("^#pragma page", "//#pragma page", .) %>% 
    gsub("^#pragma linkage", "//#pragma linkage", .) %>% 
    gsub("^#pragma title", "//#pragma title", .) %>% 
    gsub("^#pragma subtitle", "//#pragma subtitle", .) %>% 
    gsub("^#pragma comment", "//#pragma comment", .) %>% 
    
    writeLines(con = f)
}
