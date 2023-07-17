# Gdb 调试

start 或者 r 进入 main 函数

n 继续往下运行代码

bt 当遇到段错误时，使用该指令查看当前的栈帧错误

shell clear 清理 gdb 的控制台

info threads 显示当前线程的 id 及其栈帧

thread id 切换到对应 id 的线程及其栈帧上

<br/>

<br/>

# 利用 gdb 对 coredump 进行分析

发生 coredump 后，执行 generate-core-file 指令，会在当前文件下生成 coredump 文件

接着，将可执行文件和 coredump 文件放到一起，执行 gdb dds_client core.4737

最后，执行 r 指令，回到报错的栈帧，检查是什么函数出现了错误