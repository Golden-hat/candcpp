process0=$(ps>example0.txt)
process1=$(awk '{if(NR!=1) print $1}' example0.txt>example1.txt)
process2=$(awk 'BEGIN {ORS =" "} {print $1}' example1.txt>example2.txt)
process3=$(cat example2.txt)

echo $process0 $process1 $process2 $process3