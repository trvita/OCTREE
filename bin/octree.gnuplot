#! /usr/bin/gnuplot
reset session
set title 'points in octree'
set xyplane relative 0
set view equal xyz
set view 80, 70, 1.2
set xtics 100
set ytics 100
set ztics 100
set xlabel "X"
set ylabel "Y"
set zlabel "Z"
set key noautotitle
set pointsize "-2"
set xrange [0:400]
set yrange [0:400]
set zrange [0:400]
set terminal png size 800, 600
set output "bin/result.png"
splot for [i=0:3]       'src/dat/data.dat' u 1:i/2+3:i%2+5:($2-$1):(0):(0):0 w vec lc var nohead, \
      for [i=0:3]       'src/dat/data.dat' u i/2+1:3:i%2+5:(0):($4-$3):(0):0 w vec lc var nohead, \
      for [i=0:3]       'src/dat/data.dat' u i/2+1:i%2+3:5:(0):(0):($6-$5):0 w vec lc var nohead, \
      'src/dat/points.dat' w points lc rgb 'black' pt 0
