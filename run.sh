#!/bin/bash
# execute as ./run.sh

  echo "Please provide the year that H1B data are corresponding to (2014, 2015, 2016) "
  read year
  args=(year)
  data_year=${args[0]}
  filename="input/H1B_FY_${year}.csv"
  yearlabel="${year}"
  lines=( "filename           $filename"
          "label              $yearlabel" 
  )
  out=""
  for line in "${lines[@]}" ; do
    out="$out$line\n"
  done
  echo -e "$out" | column -t > pars.txt
  cmds=( "g++ src/H1B_breakdown.cpp -o H1B -std=c++11"
         "./H1B pars.txt"
       )
  for cmd in "${cmds[@]}"
    do
  eval $cmd
  done
