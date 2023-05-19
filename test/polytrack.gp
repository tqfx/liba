set key reverse
set terminal pngcairo

set output sprintf("%s3.png", ARGV[2])
set multiplot layout 3,1
plot ARGV[1] using 1:2 with lines title 'q' smooth csplines
plot ARGV[1] using 1:3 with lines title 'v' smooth csplines
plot ARGV[1] using 1:4 with lines title 'a' smooth csplines

unset multiplot
set output sprintf("%s5.png", ARGV[2])
set multiplot layout 3,1
plot ARGV[1] using 1:5 with lines title 'q' smooth csplines
plot ARGV[1] using 1:6 with lines title 'v' smooth csplines
plot ARGV[1] using 1:7 with lines title 'a' smooth csplines

unset multiplot
set output sprintf("%s7.png", ARGV[2])
set multiplot layout 4,1
plot ARGV[1] using 1:8 with lines title 'q' smooth csplines
plot ARGV[1] using 1:9 with lines title 'v' smooth csplines
plot ARGV[1] using 1:10 with lines title 'a' smooth csplines
plot ARGV[1] using 1:11 with lines title 'j' smooth csplines
unset multiplot
