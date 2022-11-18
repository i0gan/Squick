# Squick的基本知识

## 项目结构

该工程项目结构如下：

```
deploy:       // 服务端部署文件夹    
    config:   // 服务端配置文件
    data:     // 服务程序储存数据目录
    bin:      // 服务端程序目录
    lua:      // lua脚本目录
src:          // 源码
    server:   // 各服务器代码
    squick:   // suiqck核心代码
    tools:    // 工具代码
    tutorial: // 教学示例代码
docs:         // 文档
third_party:  // 第三方代码
cache:        // 编译时的临时文件
admin:        // 后台客户端vue源码
others:       // 其他
```



## 代码命名规范

遵循google c++开发规范。





## 插件系统

Squick当前所有重要插件如下：



![img](./images/plugins.png)



插件与模块的关系

![img](./images/plugin_and_module.png)

每一个插件为一个动态链接库文件（.so文件），将功能代码封装为插件的模块，可通过插件来加载各个插件的功能模块。

每个插件可以包含一个或多个模块



## 服务器架构

![img](./images/servers_architecture.png)



## 热重载基本原理









## 插件状态调用顺序

``` 
SquickPluginLoad -> Install -> Uninstall -> SquickPluginUnload
```

## 模块状态调用顺序

```
构造函数 -> Start -> AfterStart -> Update -> Destory -> 析构函数
```





## 概念

### Module(模块)

表示一类逻辑业务的合集, 相对来说功能比较集中, 可以做到低耦合, 并且可以通过`IOP`(面向接口编程)的方式来给其他模块提供耦合功能.例如LogModule等.

### Plugin(插件)

表示一系列Module的集合, 按照更大的业务来分类, 例如GameLogic插件, Navimesh插件等.

### Application(应用)

表示一个独立的完整功能的进程, 可以包含大量插件, 例如squick等.

### DataNode

表示一维数据, 通常用来表示Entity附带的任意一维数据结构, 当前可以为常用内置数据类型(`bool` `int` `int64` `double` `float` `string` `GUID`). 例如`PlayerEnity`附带的HP MP等数据.

### DataTable

表示二维数据, 通常用来表示Entity附带的任意二维数据结构,结构与Microsoft Excel的二维结构类似, 包含`Row`和`Column`, 并且结构可以通过Excel动态传入, Table中任意Cell可以为常用内置数据类型(`bool` `int` `int64` `double` `float` `string` `GUID`). 例如`PlayerEnity`附带的`ItemTable`.

### Entity(实体)

表示游戏内动态创建的任意实体对象, 该实体对象通常携带大量`DataNode`和`DataTable`, 例如：PlayerEntity、MonsterEntity、NPCEntity等.

### GUID

表示游戏内唯一ID, 并且全区全服不重复, 可以用来做`EntityID`等游戏内有唯一性需求的ID.

### Event(事件)

游戏逻辑监听和产生事件, 用来解耦游戏逻辑.
