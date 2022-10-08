#!/bin/bash

#export LC_ALL="C"
#ulimit -c unlimited
#source /etc/profile


cd bin
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:`pwd`/lib
#echo $LD_LIBRARY_PATH

chmod -R 777  squick

./squick plugin=master_server.xml server=Masterserver id=3 &

sleep 1

./squick plugin=world_server.xml server=Worldserver id=7 &

sleep 1

./squick plugin=db_server.xml server=DBserver id=8 &

sleep 1

./squick plugin=login_server.xml server=Loginserver id=4 &

sleep 1

./squick plugin=game_server.xml server=Gameserver id=16001 &

sleep 1

./squick plugin=proxy_server.xml server=Proxyserver id=5 &

sleep 5

ps -A|grep squick
