# tcpserver

一个简单的tcpserver例子。

测试环境：Ubuntu18.04

## build and run

```bash
$ mkdir build
$ cd build
$ cmake ..
$ make
$ ./tcpserver
```

## test

可以使用 telnet 进行连接，测试：

```bash
$ telnet 127.0.0.1 6789
```

关闭 telnet ：

1. 键入 CTRL + ]
2. 输入 quit

或者使用 Putty ，connect type 选择 Raw 。这个方法也适用于 windows 平台。
