#! /bin/bash
docker build -t squick_dev .

cd ../
project_path=`pwd`
cd ./env/squick

docker rm squick
docker run -it --name=squick -v $project_path:/mnt squick_dev bash 
