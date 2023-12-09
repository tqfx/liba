set key reverse
set terminal pngcairo
set output sprintf("%s.png", ARGV[1][:strlen(ARGV[1])-4])
set multiplot layout 2,2
plot ARGV[1] using 1:2 with lines title 'q'
plot ARGV[1] using 1:3 with lines title 'v'
plot ARGV[1] using 1:4 with lines title 'a'
