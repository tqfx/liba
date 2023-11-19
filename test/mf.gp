set key reverse
set terminal pngcairo
set yrange [-0.05:1.05]
set output sprintf("%s.png", ARGV[1][:strlen(ARGV[1])-4])
plot ARGV[1] using 1:2 with lines title '0'
