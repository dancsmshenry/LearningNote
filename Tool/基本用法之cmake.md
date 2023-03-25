常用指令

- cmake -B build
- make -C build

<br/>

`cmake_minimum_required(VERSION 3.16 FATAL_ERROR)` ，用于设置需要的最低版本的 cmake（如果低于这个版本就会报错）

- `FATAL_ERROR` 会被 CMake 2.6 及更高版本接受但被忽略（accepted but ignored）

<br/>

`project(ara-apd VERSION 1.0.0 LANGUAGES CXX)`

- 第一个 slot 用于指定项目的名称
- 第二个 slot （VERSION）用于指定项目的版本号
- 第三个 slot （DESCRIPTION）用于补充项目的具体信息
- 第四个 slot （LANGUAGES）用于指定项目使用的语言

<br/>

`list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")`

- 为了防止 cmakelists.txt 文件过长，因此将其分为几个模块，同时也方便平台的组件共用该 cmake 文件，cmake 模块文件一般用 .cmake 表示
- `CMAKE_CURRENT_LIST_DIR` 是用分号分隔的目录列表（是一个 list ，也就是说可以有多个路径），cmake 使用该路径检查附带的 .cmake 文件模块；默认为空
- `list(APPEND <list><element> [<element>...])` 向 list 中添加数据 element
- PS：这里给 .cmake 模块指定了文件夹以后，后续的子模块可以直接 include 对应的 .cmake 文件并使用，而不要指定路径

<br/>

`option(ARA_CXX_STANDARD_EXTENSIONS "Description" OFF)`

- 一般用于控制编译流程，可以理解为 c 语言里面的宏，即条件编译
- `option(<variable> "<help_text>" [value])`
  - `variable`：定义选项名称
  - `help_text`：说明选项的含义
  - `value`:定义选项默认状态，一般是 OFF 或者 ON，除去 ON 之外，其他所有值都为认为是 OFF
  - PS：如果主目录的 cmakelists 和子目录的 cmakelists 中定义的变量值不同，比如主目录中定义为 ON，子目录中定义为 OFF，那么遵循主目录中的内容
- 这里看到主目录定义了 ARA_CXX_STANDARD_EXTENSIONS ，后面的子目录就会用这个宏，来判断是否要加上 c++ 的编译拓展

<br/>

`if (CMAKE_BINARY_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)` 正文 `endif()`

- 即 cmake 中的 if 语句
- `STREQUAL` 用于比较字符串，相同的话返回 true

<br/>

一些特定的宏

- `CMAKE_BINARY_DIR` 指的是存放二进制文件的文件夹
- `CMAKE_CURRENT_SOURCE_DIR` 指的是当前处理的 CMakeLists.txt 所在的路径
  - ara 项目里面的意思是说，如果没有将存放二进制的文件和源码分开，就需要报错终止执行

<br/>

`message(FATAL_ERROR "Building in-source is not supported. Create a build dir and remove CMakeFiles and CMakeCache.txt")`

- message 一般用于输出，而输出也分为不同的等级（第一个 slot 写输出语句的等级，第二个 slot 写输出的具体内容）
- NONE 通知信息，就是直接输出数据（结果： NONE/home/hengrui.shen/Project/test/build）
- STATUS 输出状态信息，在前面会有 -- （结果：-- /home/hengrui.shen/Project/test/build）
- SEND_ERROR，FATAL_ERROR 生成的是错误信息（SEND_ERROR 会继续执行，FATAL_ERROR 会终止程序执行）
- message("test without grade") ，直接输出信息，没有等级

<br/>

`add_subdirectory(ara-api/core)`

- 添加一个子目录并构建该子目录
- `add_subdirectory (source_dir [binary_dir] [EXCLUDE_FROM_ALL])`
- 必选参数：`source_dir` 指定一个子目录，子目录下应该包含 CMakeLists.txt 文件和代码文件（可以是相对路径或绝对路径）
- 可选参数：`binary_dir` 指定一个子目录，用于存放输出文件（如果不指明的话，那么生成的可执行文件都会在build下的同名目录中）

<br/>

`add_library(ara-com-commom OBJECT ${COM_COMMON_SOURCES})`

- `add_library(<name> OBJECT <src>...)` 类型，是指库的类型固定为 OBJECT，将源文件进行了编译但是没有链接

<br/>

`set_target_properties(ara-com-common PROPERTIES POSITION_INDEPENDENT_CODE ON)`

<br/>
<br/>

记录一个之前遇到的小bug

- `set(CMAKE_EXPORT_COMPILE_COMMANDS ON)` 这句话不起作用，感觉是版本的原因
- 需要修改为`set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")`，这样才能生成 json 文件，以便 clang 实现代码跳转

- cmake之前老是抽风，明明用了set(CMAKE_EXPORT_COMPILE_COMMANDS ON)的指令，但还是没有生成json文件
- 解决办法：经过了网上的指导以后，我发现可以使用set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")来解决
  https://gitlab.kitware.com/cmake/cmake/-/issues/16588（有一条回答就是这个）