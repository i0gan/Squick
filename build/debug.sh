#!/bin/bash

#export LC_ALL="C"
#ulimit -c unlimited
#source /etc/profile


cd bin
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:`pwd`/lib
#echo $LD_LIBRARY_PATH

chmod -R 777  squick

./squick plugin=master.xml server=master id=3 &

sleep 1

./squick plugin=world.xml server=world id=7 &

sleep 1

./squick plugin=db.xml server=db id=8 &

sleep 1

./squick plugin=login.xml server=login id=4 &

sleep 1

./squick plugin=game.xml server=game id=16001 &

sleep 1

./squick plugin=proxy.xml server=proxy id=5 &

sleep 5

ps -A|grep squick
