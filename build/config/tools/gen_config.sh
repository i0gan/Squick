# 生成配置文件
mkdir -p ../proto
mkdir -p ../struct
mkdir -p ../ini

./config_generator

mkdir -p ../client
mkdir -p ../client/ini
mkdir -p ../client/proto
mkdir -p ../client/struct

cp -a ../proto/protocol_define.h ../../../src/squick/struct
cp -a ../../../src/squick/struct/*.cs ../client/proto/

cp -a ../ini ../client/
cp    ../proto/*.cs ../client/
cp -a ../struct ../client/
