set key reverse
set output ARGV[2]
set terminal pngcairo
plot ARGV[1] using 1:2 with lines title '0',\
    '' using 1:3 with lines title '1' smooth csplines,\
    '' using 1:4 with lines title '1' smooth csplines,\
    '' using 1:5 with lines title '2' smooth csplines,\
    '' using 1:6 with lines title '3' smooth csplines
