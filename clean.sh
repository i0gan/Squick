#! /bin/bash
rm -rf ./cache
rm -rf ./deploy/bin
rm -rf ./deploy/config/tools/config_generator
rm -rf ./deploy/config/client/*
rm -rf ./deploy/config/struct/*
rm -rf ./deploy/config/proto/*
#rm -rf ./deploy/config/ini/*
rm -rf ./deploy/*.log
rm -rf ./deploy/data/logs
rm -rf ./deploy/data/www
rm -rf ./src/squick/struct/*.cs
rm -rf ./src/squick/struct/*.pb.h
rm -rf ./src/squick/struct/*.pb.cc
rm -rf ./src/squick/struct/protocol_define.h
cd ./third_party
bash clean.sh
cd ..

cd ./www/admin
bash clean.sh
cd ..
