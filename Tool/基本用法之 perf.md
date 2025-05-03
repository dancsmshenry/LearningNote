```Shell
perf report -i perf.data # 查看生成的 .data 文件

perf record ./vector_test # 采样
```



Flamegraph 的 常用指令

```Shell
# 主要记录当生成了 .data 文件后的操作
# 参考文章 https://zhuanlan.zhihu.com/p/717125245

# 把 .data 的数据，转化为 .perf 后缀名的文件
perf script -i perf.data > out.perf 

# 把 .perf 文件转化为 .flode 后缀名的文件
/home/dev/FlameGraph-master/stackcollapse-perf.pl out.perf > out.flode 

# 把 .flode 文件转化为 .svg 后缀名的文件
/home/dev/FlameGraph-master/flamegraph.pl out.flode > flame.svg
```

Cmake 使用 install 的时候，需要指定安装软件包的目录，一般使用下述路径