set key reverse
set terminal pngcairo
set datafile separator ','
set output sprintf("%s.png", ARGV[1][:strlen(ARGV[1])-4])
set y2tics
plot ARGV[1] using 1:2 with lines axis x1y1 title 'f',\
          '' using 1:3 with lines axis x1y2 title 'f^{-1}'
