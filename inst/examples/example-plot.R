library(ggplot2)
library(mapproj)

# decode metar in airport_weather
decoded <- lapply(airport_weather$metar, decodemetar)

# extract stnid and temperature
summary <- lapply(
  decoded, 
  function(x)x[, c("stnid", "temp")]
)

# rbind into a data frame
summary <- do.call(rbind, summary)

# merge with airports
dat <- merge(airports, summary, by.x = "gps", by.y = "stnid", all.y = TRUE)

# discard airports with missing values for lat and lon
dat <- dat[!is.na(dat$longitude) & !is.na(dat$latitude) & dat$latitude > -80, ]

# plot
ggplot(dat, aes(x = longitude, y = latitude, col = temp)) +
  geom_point(size = 1) +
  scale_color_gradient2(low = "blue", high = "red", mid = "lightblue") +
  coord_map()
