set key reverse
set terminal pngcairo
set output sprintf("%s.png", ARGV[1][:strlen(ARGV[1])-4])
plot ARGV[1] using 1:2 with lines title '0',\
          '' using 1:3 with lines title '1'
