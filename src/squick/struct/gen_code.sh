#!/bin/bash

#ln -s ../../../third_party/build/protobuf/protoc
ln -s ../../../third_party/build/protobuf/protoc
#chmod 777 protoc
# 生成C++
./protoc -I=./ --cpp_out=./ ./define.proto
./protoc -I=./ --cpp_out=./ ./msg_base.proto
./protoc -I=./ --cpp_out=./ ./msg_pre_game.proto
./protoc -I=./ --cpp_out=./ ./msg_share.proto

# 生成csharp
./protoc --csharp_out="./" --proto_path="./" define.proto
./protoc --csharp_out="./" --proto_path="./" msg_base.proto
./protoc --csharp_out="./" --proto_path="./" msg_pre_game.proto
./protoc --csharp_out="./" --proto_path="./" msg_share.proto

