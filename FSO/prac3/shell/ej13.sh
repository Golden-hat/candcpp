echo -e "PID PPID STATE COMMAND"
for var in "$@"
do
echo -e $(awk '{print $1,$4,$3}' /proc/$var/stat) $(awk '{print $1}' /proc/$var/cmdline)
done
