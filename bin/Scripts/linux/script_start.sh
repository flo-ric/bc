#!/bin/bash


#Load all secondary views
for i in 2 3 4 
do
    echo "--------------------------------------------------------------------------------"
    echo "--------------------------------------------------------------------------------"
    echo "-------------------------Load Secondaries rpi5-somos-$i-----------------------"
    echo "--------------------------------------------------------------------------------"
    echo "--------------------------------------------------------------------------------"

    sshpass -p "linuxRPIpwd" ssh -o StrictHostKeyChecking=no flo@rpi5-somos-$i.local "ps aux | grep \"[./]bridgecommand-bc\" > ~/bcStatus-rpi5-somos-$i.log"
    sshpass -p "linuxRPIpwd" scp flo@rpi5-somos-$i.local:~/bcStatus-rpi5-somos-$i.log .

    if [ -s bcStatus-rpi5-somos-$i.log ]; then
        # BC is already running
	echo ">>>>>> BC is already running on rpi5-somos-$i"
    else
        # BC is not running
	echo ">>>>>> Start BC on rpi5-somos-$i"
        sshpass -p "linuxRPIpwd" ssh -o StrictHostKeyChecking=no flo@rpi5-somos-$i.local "export DISPLAY=:0;cd bc/bin/;nohup ./bridgecommand-bc > foo.log 2> foo.err < /dev/null &"
    fi
    rm -rf bcStatus-rpi5-somos-$i.log
    
done
