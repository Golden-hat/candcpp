echo -e "PID\tPPID\tSTATE\tCOMMAND"
echo -e $(awk '{printf $1,"\t"$4,"\t"$3"\t"}' /proc/$1/stat) $(awk '{printf $1}' /proc/$1/cmdline)
