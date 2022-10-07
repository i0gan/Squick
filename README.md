# Squick

## Squick是什么?

Squick是一款可快速开发拓展的游戏服务器开发框架，轻量，插件化，易拓展，支持lua脚本。目前正在极速开发Unity客户端SDK中，客户端Demo: [Uquick](https://github.com/i0gan/Uquick)



**讨论QQ群：729054809**

Bilibili: https://www.bilibili.com/video/BV1kR4y197Xf



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



## 编译程序文件结构

```
build/server/
├── lib
│   ├── libprotobuf.so.32
│   ├── skcore.so
│   ├── squick_plugin_loader.so
│   └── squick_struct.so
├── plugin
│   ├── core
│   │   ├── actor.so
│   │   ├── config.so
│   │   ├── kernel.so
│   │   ├── log.so
│   │   ├── lua.so
│   │   ├── navigation.so
│   │   ├── net.so
│   │   ├── nosql.so
│   │   ├── security.so
│   │   └── test.so
│   └── extend
│       ├── db
│       │   ├── client.so
│       │   ├── logic.so
│       │   └── server.so
│       ├── game
│       │   ├── client.so
│       │   ├── logic.so
│       │   └── server.so
│       ├── login
│       │   ├── client.so
│       │   ├── http_server.so
│       │   ├── logic.so
│       │   └── server.so
│       ├── master
│       │   ├── http_server.so
│       │   ├── logic.so
│       │   └── server.so
│       ├── others
│       │   ├── chat.so
│       │   ├── consume_manager.so
│       │   ├── inventory.so
│       │   └── tutorial
│       │       ├── hello_async.so
│       │       ├── hello_event.so
│       │       ├── hello_http_server.so
│       │       ├── hello_navigation.so
│       │       ├── hello_plugin.so
│       │       ├── hello_property.so
│       │       └── hello_redis.so
│       ├── proxy
│       │   ├── client.so
│       │   ├── logic.so
│       │   └── server.so
│       └── world
│           ├── client.so
│           └── server.so
└── squick
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



## 开发教学

文档正在极速更新中

### 快速开始

[下载编译]

[快速搭建]

### 知识概念

[基本介绍]

[代码风格]

[代码格式]

[插件和模块]

[热数据属性]

[数据驱动编程]

[异步机制]

[服务器架构]

[聊天服务器]

[主服务器]

[代理服务器/网关服务器]

[登录服务器]

[数据库服务器]

[游戏服务器]

[世界服务器]



### 代码实例

[如何编写新的插件]

[如何使用属性机制]

[如何使用事件机制]

[如何使用异步机制]

[如何写http服务器]

[如何调用redis接口]





### 客户端SDK

进入 https://github.com/i0gan/Uquick 查看详情安装



## 第三方库

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

 ```
 gcc/g++ version 9.4.0 (Ubuntu 9.4.0-1ubuntu1~20.04.1)
 cmake version 3.16.3
 /lib/x86_64-linux-gnu/libc.so.6: GNU C Library (Ubuntu GLIBC 2.31-0ubuntu9.9) stable release version 2.31.
 ```

