# Squick

## Squick是什么?

Squick是一款可快速开发拓展的游戏服务器开发框架，轻量，插件化，易拓展，支持lua脚本。目前正在极速开发Unity客户端SDK中，客户端Demo: [Uquick](https://github.com/i0gan/Uquick)



**讨论QQ群：729054809**

## 特性

- 易使用，采用。
- 采用动态连链接库方式动态加载插件，开发拓展插件，让开发服务器变成开发插件。 
- 遵守谷歌C++编程规范
- 事件和属性驱动，让开发变得更简单。
- Excel实现服务端配置
- 日志捕获系统
- 支持Lua脚本开发
- 支持部分不用停服即可热更
- 默认拥有服务器插件：代理服务器、世界服务器、导航系统、数据库服务器、中心服务器、登录服务器

## 将来要做

- 增加KCP协议的支持
- 拓展lua脚本库
- 增加世界服务器的逻辑判断
- 接入腾讯云SDK
- 增加后台管理插件



## 工程结构

```
build:       // 编译文件
    cache:   // 编译时的中间文件
    config:  // 服务端配置文件
    data:    // 服务程序储存数据目录
    script:  // lua脚本目录
    server:  // 服务端程序目录
src:         // 源码
    server:  // 各服务器源码
    squick:  // suiqck核心源码
    tools:   // 工具源码
    tutorial: // 教学源码
docs:         // 文档
third_party:  // 第三方源码
```

脚本说明
```
项目目录下
    install.sh  // 用于第一次下载源码后，需要安装的依赖工具
    build.sh    // 用于编译工程文件，也可以加入参数单独编译模块，需要在CMakefile.txt中加入相关模块，比如：编译lua模块， `./build.sh lua`
    clean.sh    // 用于清除工程编译所产生的文件
    upload.sh   // 采用rsync方式进行文件同步，方便同步编译的资源到部署的服务器中

build目录下
debug.sh      // 用于前台打印方式启动服务器，可以方便查看实时输出情况
start.sh      // 用于后台启动服务器
stop.sh       // 用于停止服务器
```


## 快速开始

```bash
git clone https://github.com/pwnsky/squick.git

cd squick
bash install.sh
```


如果不能编译，可能是缺少依赖，打开third_party/install.sh 里查看需要安装的依赖。

编译

```bash
./build.sh

```
编译成功后，可执行文件在 ./build/server/squick


### 搭建Redis
这里采用docker来进行搭建
```
docker pull redis
docker run --name squick-cache -p 22222:6379  -d redis --requirepass pwnsky # pwnsky 是密码
```

测试

```bash
cd ./build
./debug.sh
```

### 客户端SDK

进入 https://github.com/i0gan/Uquick 查看详情安装

## 第三方依赖库
- minzip
- zlib
- easylogging++
- libevent
- hiredis
- protobuf
- RapidXML
- ajson
- concurrentqueue
- LuaIntf
- lua
- navigation
- nlohmann



## 本项目开发环境

### Arch linux
    gcc/g++ version 12.2.0 (GCC)
    cmake version 3.24.2
    Docker version 20.10.18, build b40c2f6b5d
    git version 2.37.3
    /lib/libc.so.6: GNU C Library (GNU libc) stable release version 2.36.

### Ubuntu 20.04
    gcc/g++ version 9.4.0
    cmake version 3.16.3
    /lib/x86_64-linux-gnu/libc.so.6: GNU C Library (Ubuntu GLIBC 2.31-0ubuntu9.9) stable release version 2.31