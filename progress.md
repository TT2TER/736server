# 首先整一下语言，将系统语言换成英文，使得桌面等路径变为Desktop等英文路径

# 安装openssh 
[安装openssh](https://zhuanlan.zhihu.com/p/442023386)

# 设置校园网登陆脚本
[脚本源代码](https://github.com/vouv/srun)

先登陆一次，按照配置设置好用户名和密码

记得赋予权限`sudo chmod +x srun`

然后写运行脚本

```bash
$ vim loginsrun.sh

#!/bin/sh
cd /your_srun_place && ./srun login
```

`sudo chmod +x loginsrun.sh`

检查脚本运行情况`./loginsrun.sh`

设置自启动

实测所有办法里最好用的就这一种，其他的反正没整出来，我是废物

[按照教程来就好](https://www.linuxprobe.com/linux-rc-local.html)

还是rc-local好用

# 设置clash代理，用来上github以及终端代理
仓库 clash for windows

运行后添加开机自启动

设置中设置对应端口

终端代理设置
[教程](https://www.zhihu.com/question/472418041)

利用如下命令查看代理开启情况
```
curl ip.gs
```

# 去掉图形化界面启动（减少内存占用）

# 设置来电自启动

# 安装codeserver服务

## 安装docker docker-compose portainer
### 安装 docker docker-compose
请完全按照[官方文档](https://docs.docker.com/engine/install/)安装

建议使用从repository安装

注意配置非root用户组，配置自启动

### 安装portainer

请完全按照[官方文档](https://docs.portainer.io/start/install)安装
# 自动汇报端口