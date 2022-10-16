#!/bin/bash

export LC_ALL="C"

ulimit -c unlimited
source /etc/profile


cd server
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:`pwd`/lib
#echo $LD_LIBRARY_PATH

chmod -R 777  squick
./squick plugin=plugin.xml server=Masterserver id=3
#./squick plugin=plugin.xml server=Worldserver id=7
#./squick plugin=plugin.xml server=DBserver id=8
#./squick plugin=plugin.xml server=Loginserver id=4
#./squick plugin=plugin.xml server=Gameserver id=16001
#./squick plugin=plugin.xml server=Proxyserver id=5

ps -A|grep squick
