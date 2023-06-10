set key reverse
set terminal pngcairo

set output sprintf("%s3.png", ARGV[2])
set multiplot layout 2,2
plot ARGV[1] using 1:2 with lines title 'q'
plot ARGV[1] using 1:3 with lines title 'v'
plot ARGV[1] using 1:4 with lines title 'a'
unset multiplot

set output sprintf("%s5.png", ARGV[2])
set multiplot layout 2,2
plot ARGV[1] using 1:5 with lines title 'q'
plot ARGV[1] using 1:6 with lines title 'v'
plot ARGV[1] using 1:7 with lines title 'a'
unset multiplot

set output sprintf("%s7.png", ARGV[2])
set multiplot layout 2,2
plot ARGV[1] using 1:8 with lines title 'q'
plot ARGV[1] using 1:9 with lines title 'v'
plot ARGV[1] using 1:10 with lines title 'a'
plot ARGV[1] using 1:11 with lines title 'j'
unset multiplot
