# bazel 的安装

前置安装：

```shell
# 需要g++
apt install g++ unzip zip
```

<br/>

<br/>

去官方仓库中 https://github.com/bazelbuild/bazel/releases 找到需要的版本或 `latest` ，根据系统和系统位数下载对应的版本

![](image/bazel安装.png)

然后将下载得到的文件先重命名为 bazel，然后移动到 `/usr/local/bin/` 中，同时需要给该文件添加权限

最后使用 `bazel version` 检查是否安装成功

<br/>

<br/>

具体的指令

```shell
wget https://github.com/bazelbuild/bazel/releases/download/6.2.0/bazel-6.2.0-linux-x86_64
mv bazel-6.2.0-linux-x86_64 /usr/local/bin/bazel
# 切换目录至 /usr/local/bin/
chmod +x bazel
bazel version # 查询 bazel 版本
```





