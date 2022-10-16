#! /bin/bash

# 编译protobuf
#cd protobuf-21.6
third_party_path=`pwd`
rm -rf build/protobuf
rm -rf build/include
rm -rf build/lib
rm -rf build/libevent
rm -rf build/zlib
rm -rf build/navigation

mkdir -p build/include
mkdir -p build/lib
mkdir -p build/protobuf
mkdir -p build/libevent
mkdir -p build/zlib
mkdir -p build/navigation

# build libevent
cd build/libevent
cmake  ../../libevent-2.1.12-stable
make -j $(nproc)
mkdir -p ./install && make install DESTDIR=./install
cp -r install/usr/local/include/* ../include
#cp -r ./include/* ../include
cd ./lib
cp *.a ../../lib
cp *.so ../../lib
cd $third_party_path



# build protobuf
cd build/protobuf
cmake ../../protobuf-21.6 -Dprotobuf_BUILD_TESTS=OFF -DBUILD_SHARED_LIBS=true
make -j $(nproc)
mkdir -p ./install && make install DESTDIR=./install
cp -r install/usr/local/include/* ../include
cp libprotobuf.so.3.21.6.0 ../lib/libprotobuf.so
cd $third_party_path


# build lua
cd lua-5.3.6
make linux
cp ./src/*.h ../build/include/
cp ./src/*.hpp ../build/include/
cp ./src/*.a ../build/lib
cp ./src/*.so ../build/lib
cd $third_party_path



# build redis database
cd hiredis
make clean
make
cp *.a $third_party_path/build/lib
cp *.so $third_party_path/build/lib
cp *.h $third_party_path/build/include
cd $third_party_path

# build zlib
cd build/zlib
cmake  ../../zlib
make -j $(nproc)
cp *.a $third_party_path/build/lib
cp *.so $third_party_path/build/lib
cp *.h $third_party_path/build/include
cd $third_party_path


# build navigation
cd build/navigation
cmake  ../../navigation
make -j $(nproc)
cp *.a $third_party_path/build/lib
cp *.so $third_party_path/build/lib
#cp *.h $third_party_path/build/include
cd $third_party_path

