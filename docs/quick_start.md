# 快速开始

注：该项目不支持Windows、MacOS，请采用Linux系统进行编译，推荐Ubuntu20.04。

## 下载编译

[直接编译](#直接编译)

[一键docker编译](#一键docker编译)

[共享docker编译 ](#共享docker编译 ) (推荐)



### 直接编译

采用物理机编译是为了开发以及测试更加方便。但可能需要你们自己手动配置各种搭建环境时出现的问题。

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
nodejs
npm
```

请采用手动进行安装以上工具包。

#### 编译后台前端代码

```
cd admin
npm install
bash build.sh
```



### 一键docker编译

采用的是ubuntu:20.04环境来进行编译的。采用该方法，是为了验证编译环境或快速部署。编译的工程文件是从github中新下载下来的，下载到容器里的/root目录。

docker安装方法，这里就不用说了，只需一步就可以搭建编译环境以及编译。一键编译。

```sh
cd docker/dev/build/ && docker build -t squick .
```

编译完成后

```sh
cd {project_path}
docker run -it --name=squick --net=host -v `pwd`:/mnt squick
```

进入容器

```sh
cd ~/Squick/deploy
./single.sh # 运行
```

如果运行成功，那么编译没问题，ctrl + c 退出。



### 共享docker编译

**推荐**

这种是方式编译，为了方便开发，让编译文件与开发文件直接映射，采用的是ubuntu:20.04环境来进行编译的。

```sh
cd {project_path}/docker/dev/ && bash creat.sh
```

进入容器后

```sh
# 编译squick
cd /mnt && chmod +x build.sh && chmod +x third_party/build.sh
cd /mnt/third_party && bash ./build.sh
cd /mnt/ bash ./build.sh

# 编译vue
git config --global url."https://".insteadOf git://
cd /mnt/admin
npm install
bash ./build.sh
```



### 编译后

编译完成后，在`{project_path}/deploy/bin` 下会出现编译好的二进制文件。如下

```
deploy/bin/
├── lib
...
│   ├── squick_core.so
├── plugin
│   ├── core
│   │   ├── actor.so
...
│   └── server
...
└── squick
```

编译成功后，可执行文件是在 ./deploy/bin/squick

在执行install.sh或其他方式编译成功后，后续不用执行之前的方式进行编译了，只需执行`{project_path}/build.sh` 脚本，采用docker编译的，在容器里执行即可。

```bash
./build.sh
```

### 编译方式

默认编译的是debug版本，如果想编译为release版本，请打开{project_path}/build.sh，在第8行的Version改为release即可。在编译的时候，会在项目根目录下创建一个cache文件夹来存储编译时生产的临时中间文件。



## 搭建数据库

### 搭建Redis

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



### 搭建Mysql

更新中...







## 修改配置文件

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

