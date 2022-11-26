#! /bin/bash
config_path="../config"
struct_path="../../src/squick/struct"
bash clean.sh
# 生成配置文件
mkdir -p $config_path/proto
mkdir -p $config_path/struct
mkdir -p $config_path/ini

./config_generator $config_path

mkdir -p $config_path/client
mkdir -p $config_path/client/ini
mkdir -p $config_path/client/proto
mkdir -p $config_path/client/struct

cp -a $config_path/proto/protocol_define.h $struct_path
cp -a $struct_path/*.cs ../client/proto/

cp -a $config_path/ini $config_path/client/
cp    $config_path/proto/*.cs $config_path/client/proto
cp -a $config_path/struct $config_path/client/
rm -rf $config_path/proto
