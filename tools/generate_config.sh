#! /bin/bash
# Author: i0gan
# Email: l418894113@gmail.com
# Date: 2022-11-27
# Github: https://github.com/i0gan/Squick
# Description: Generate configuration files

config_path="../config"
struct_path="../src/squick/struct"
client_config_path="../client"
excel_path='../resource/excel'
bash clean.sh
# 生成配置文件
mkdir -p $config_path/proto
mkdir -p $config_path/struct
mkdir -p $config_path/ini

./xlsx2need $excel_path $config_path
cp -a $config_path/proto/protocol_define.h $struct_path

mkdir -p $client_config_path/ini
mkdir -p $client_config_path/proto
mkdir -p $client_config_path/struct

cp -a $config_path/ini $client_config_path
cp -a $config_path/struct $client_config_path
rm -rf $config_path/proto
