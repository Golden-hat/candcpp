processes=$(ps)
processes=$(echo "$processes"|grep -v 'ps'|awk '{print $1}')

for i in $processes
do
    if test $i != "PID"
    then
        ./ej13.sh "$i"
    fi
done
