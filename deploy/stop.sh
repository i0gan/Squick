#!/bin/bash

ps -A|grep squick
#pgrep squick | xargs kill -s 9
kill -9 $(ps -ef|grep squick |awk '$0 !~/grep/ {print $2}' |tr -s '\n' ' ')
sleep 1.5

ps -A|grep squick
