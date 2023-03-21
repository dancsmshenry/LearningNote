背景：

- cmake之前老是抽风，明明用了set(CMAKE_EXPORT_COMPILE_COMMANDS ON)的指令，但还是没有生成json文件
- 解决办法：经过了网上的指导以后，我发现可以使用set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")来解决
  https://gitlab.kitware.com/cmake/cmake/-/issues/16588（有一条回答就是这个）

<br/>

常用指令

- cmake -B build
- make -C build