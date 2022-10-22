echo -e "PID\tPPID\tSTATE\tCOMMAND"
echo "$(awk '{print $1,"\t"$4,"\t"$3"\t"}' /proc/$1/stat)$(awk '{print $1}' /proc/$1/cmdline)"
