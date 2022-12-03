#! /bin/bash
# Author: i0gan
# Email : l418894113@gmail.com
# Date  : 2022-11-27
# Github: https://github.com/i0gan/Squick
# Description: Start servers for devlopment debug

#export LC_ALL="C"
#ulimit -c unlimited
#source /etc/profile
squick_bin_path=../bin
cd $squick_bin_path
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

sleep 1
./www &

sleep 5

ps -A|grep squick