#!/bin/bash

export LC_ALL="C"

ulimit -c unlimited
source /etc/profile


cd server
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:`pwd`/lib
#echo $LD_LIBRARY_PATH

chmod -R 777  squick
./squick plugin=plugin.xml server=Masterserver id=3

ps -A|grep squick
