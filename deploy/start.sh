#!/bin/bash

#export LC_ALL="C"
#ulimit -c unlimited
#source /etc/profile

cd cd

chmod -R 777  squick

./squick -d plugin=plugin.xml server=MasterServer ID=3

sleep 1

./squick -d plugin=plugin.xml server=WorldServer ID=7

sleep 1

./squick -d plugin=plugin.xml server=DBServer ID=8

sleep 1

./squick -d plugin=plugin.xml server=LoginServer ID=4

sleep 1

./squick -d plugin=plugin.xml server=GameServer ID=16001

sleep 1

./squick -d plugin=plugin.xml server=ProxyServer ID=5

sleep 1
./www &

sleep 2

ps -A|grep squick
