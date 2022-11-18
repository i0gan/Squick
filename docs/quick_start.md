# 快速开始

注：该项目不支持Windows、MacOS，请采用Linux系统进行编译，推荐采用Ubuntu20.04。

## 下载编译

### 物理机编译

#### 编译squick

克隆代码

```
git clone https://github.com/pwnsky/Squick.git
```

或者直接点击 https://github.com/i0gan/Squick/archive/refs/heads/main.zip 下载代码。

下载之后，解压进入，执行

```bash
cd Squick
bash install.sh
```

install.sh脚本会自动下载编译工具，并且编译，如果出现不能编译，可能是缺少是依赖，linux依赖包如下：

```
gcc
g++
cmake
automake
unzip
libtool
libreadline
libncurses
pkg-config
node
```

#### 编译vue

```
cd Squick
bash install.sh
```





### 通过docker 编译 (推荐)

只需一步就可以搭建编译环境。

```
```







请采用手动进行安装以上工具包。

编译完成后，在`{project_path}/deploy/bin` 下会出现编译好的二进制文件。如下

```
deploy/bin/
├── lib
│   ├── libprotobuf.so.32
│   ├── squick_core.so
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
│   └── server
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
│       ├── misc
│       │   ├── chat.so
│       │   ├── consume_manager.so
│       │   └── inventory.so
│       ├── proxy
│       │   ├── client.so
│       │   ├── logic.so
│       │   └── server.so
│       └── world
│           ├── client.so
│           └── server.so
└── squick
```

编译成功后，可执行文件是在 ./deploy/bin/squick

在执行install.sh编译成功后，后续不用执行install.sh进行编译了，只需执行`{project_path}/build.sh` 脚本

```bash
./build.sh
```

编译方式，默认编译的是debug版本，如果想编译为release版本，请打开{project_path}/build.sh，在第8行的Version改为release即可。在编译的时候，会在项目根目录下创建一个cache文件夹来存储编译时生产的临时中间文件。


## 搭建Redis

这里采用docker来进行搭建，如果没有安装docker，请通过你分支下的包管理命令进行安装，Debian分支安装命令执行如下：

```
sudo apt install docker
```

拥有docker之后，需要得启动一下docker

```
sudo systemctl start docker
```

拉取redis镜像并创建运行redis容器

```
sudo docker pull redis
sudo docker run --name squick-cache -p 22222:6379  -d redis --requirepass pwnsky # pwnsky 是密码
```

## 修改数据库配置文件

采用Office软件打开{project_path}/deploy/config/excel/side/NoSqlServer.xlsx，修改里面的IP为你搭建redis的ip，默认为127.0.0.1。修改完毕之后，需要重新生产配置文件，需执行一个脚本进行生成。执行如下：

```
cd {project_path}/deploy/config/tools
bash gen_config.sh
```

需注意，一点要在{project_path}/deploy/config/tools目录下执行gen_config.sh，不然生成配置文件时可能有错误。



## 启动squick服务器

最后一步，可以通过前台启动或者后台启动方式来启动服务器，前台启动是将输出实时的输出到控制台，后台启动在控制台上是没有调试日志输出的。

在 {project_path}/deploy 目录下，`debug.sh`脚本是前台启动服务器，`start.sh`脚本是后台启动，这里采用前台启动。如果你想停止服务器，只需执行`stop.sh`脚本即可

```bash
bash ./debug.sh
```

在搭建完服务端之后，想要测试demo，请查看[Uquick](https://github.com/i0gan/Uquick)的快速开始教程。

