#! /bin/bash
docker build -t squick_dev .

cd ../../
project_path=`pwd`
#cd ./docker/dev

docker rm squick
docker run -it --name=squick -v $project_path:/mnt --net=host squick_dev bash 
