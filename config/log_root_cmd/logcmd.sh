function cmd2syslog
{
   declare command
   command=$(fc -ln -0)

   if [ `id -u` -ne 0 ]; then
       return
   fi

   if [ "${last_cmd}" == "${command}" ]; then
       return
   fi

   if [ ! -z "${command}" ]; then
       logger -p local1.notice -t bash -i -- "[${USER}@`echo ${HOSTNAME} | cut -d'.' -f1` ${PWD}]#" ${command}
   fi

   export last_cmd=$command
}

trap cmd2syslog DEBUG
