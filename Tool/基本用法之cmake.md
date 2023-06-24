# 0、通用的 CMakeLists 模板

```cmake
# 指定 cmake 所需的最小版本
cmake_minimum_required(VERSION 3.16)

# 指定 cpp 编译的版本
set(CMAKE_CXX_STANDARD 17)
# 是否一定要支持上述指定的 cpp 标准
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 项目的基本信息，名字版本号
project(learningcpp LANGUAGES C CXX)

# 编译得到的二进制文件是否和当前源码是在同一目录下，如果是的话就需要警告
if (PROJECT_BINARY_DIR STREQUAL PROJECT_SOURCE_DIR)
	message(WARNING "The binary directory of CMake cannot be the same as source directory!")

# 设置项目的编译模式（可以理解为项目的优化程度）
if (NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Release)
endif()
```

<br/>

<br/>

<br/>

# 1、cmake 命令行使用方法

```shell
# PS：当时是在项目的主路径下

# 通过 cmakelists 生成对应的 makefile 或者 ninja 文件，其中路径被设置为 build（也可以设置为别的），后续的则是设置一些编译参数，比如这里就是设置项目生成的版本，cmake_export_compile_commands 用于生成 json 文件，方便使用 clangd 实现代码跳转
cmake -B build -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=./build/release -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
# 编译，编译的目录也被指定为了 build，而 --parallel 4 则是设置编译的线程数
cmake --build build --parallel 4
# 安装，将项目安装到指定目录下，这里指定了安装的目录为 build 目录下的 release 目录
cmake --build build --target install
```

<br/>

<br/>

cmake 编译主要分为两个阶段：

第一步是 cmake -B build，称为配置阶段（configure），这时只检测环境并生成构建规则，会在 build 目录下生成本地构建系统能识别的项目文件（Makefile 或是 .sln）

在配置阶段，可以利用 -D 指定配置变量（即一些缓存变量），这些变量会被在本地缓存，即使后续只是 cmake -B build ，前面的缓存也会被使用到

第二步是 cmake --build build，称为构建阶段（build），这时才实际调用编译器来编译代码

<br/>

<br/>

可以通过 -G 选择，来控制通过 cmakelists 的生成器

```shell
# 选择 ninja 作为后续的生成构建器
cmaek -GNinja -B build
```

挖个坑，后续还想要学一下 ninja 和 bazel

ninja：实践来看编译的速度无论是首次编译还是二次编译，效率都高于 makefile

bazel：很多开源的自动驾驶项目都使用这个来进行编译

<br/>

<br/>

<br/>



# 2、cmake 的基本语法

## list

```cmake
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")
```

背景：为了防止 cmakelists.txt 文件过长，因此将其分为几个模块，同时也方便平台的组件共用该 cmake 文件，cmake 模块文件一般是后缀名为 .cmake

`CMAKE_CURRENT_LIST_DIR` 是用分号分隔的目录列表（是一个 list ，也就是说可以有多个路径），cmake 使用该路径检查附带的 .cmake 文件模块；默认为空

`list(APPEND <list><element> [<element>...])` 向 list 中添加数据 element

PS：这里给 .cmake 模块指定了文件夹以后，后续的子模块可以直接 include 对应的 .cmake 文件并使用，而不需要重新指定路径

<br/>

<br/>

## option

```cmake
option(ARA_CXX_STANDARD_EXTENSIONS "Description" OFF)
```

一般用于控制编译流程，可以理解为 c 语言里面的宏，即条件编译

`option(<variable> "<help_text>" [value])`

- `variable`：定义选项名称
- `help_text`：说明选项的含义
- `value`:定义选项默认状态，一般是 OFF 或者 ON，除去 ON 之外，其他所有值都为认为是 OFF
- PS：如果主目录的 cmakelists 和子目录的 cmakelists 中定义的变量值不同，比如主目录中定义为 ON，子目录中定义为 OFF，那么遵循主目录中的内容

这里看到主目录定义了 ARA_CXX_STANDARD_EXTENSIONS ，后面的子目录就会用这个宏，来判断是否要加上 c++ 的编译拓展

<br/>

<br/>

## if

```cmake
if (CMAKE_BINARY_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
	#正文 
	# STREQUAL 用于比较字符串，相同的话返回 true
endif()
```

<br/>

<br/>

## message

message 一般用于输出，而输出也分为不同的等级（第一个 slot 写输出语句的等级，第二个 slot 写输出的具体内容）

```cmake
# 输出语句字符串
message("hello world!") # hello world!

# STATUS 输出状态信息，会带有 -- 前缀
message(STATUS "hello world!") # -- hello world!

# NONE 输出通知信息
message(NONE "test message in cmake!") # NONEtest message in cmake!

# FATAL_ERROR 输出错误信息并终止程序执行
message(FATAL_ERROR "Building in-source is not supported. Create a build dir and remove CMakeFiles and CMakeCache.txt")

# SEND_ERROR 输出错误信息并继续执行
message(SEND_ERROR "Building in-source is not supported. Create a build dir and remove CMakeFiles and CMakeCache.txt")

# WARNING 输出警告信息，继续执行
message(WARNING "test in warning")
```

<br/>

<br/>

<br/>

# 3、cmake 项目的基本配置

```cmake
# 指定最低所需的 cmake 版本，当用户使用的 cmake 小于这个版本的时候，就会报错
cmake_minimum_required(VERSION 3.16 FATAL_ERROR) # 在2.6以后的版本会被接受但是忽略
cmake_minimum_required(VERSION 3.15...3.20) # 指定使用 cmake 的版本范围

# 用于控制编译模式，分为 debug，release，minsizerel，relwithdebinfo 几种模式
set(CMAKE_BUILD_TYPE Release)

# project 初始化项目信息，并把当前 cmakelists.txt 所在位置作为根目录
# 第一个 slot （NAME）用于指定项目的名称
# 第二个 slot （VERSION）用于指定项目的版本号（可以把当前项目的版本号设定为 x.y.z；再通过一些宏可以获得具体的版本号）
# 第三个 slot （DESCRIPTION）用于补充项目的具体信息
# 第四个 slot （LANGUAGES）用于指定项目使用的语言（可以同时写多种语言）
project(LearningCpp VERSION 1.0.0 LANGUAGES CXX)
project(LearningC
	VERSION 1.0.0
	DESCRIPTION "a free open-source"
	HOMEPAGE_URL http://www.baidu.com
	LANGUAGES CXX C
	)

# 一些常用的宏
# CMAKE_CURRENT_SOURCE_DIR 表示当前源码目录的位置，例如 ~/hellocmake
# CMAKE_CURRENT_BINARY_DIR 表示当前输出目录的位置，例如 ~/hellocmake/build
# PROJECT_SOURCE_DIR 表示最近一次调用 project 的 CMakeLists.txt 所在的源码目录（我理解为就是根目录的路径）
# CMAKE_CURRENT_SOURCE_DIR 表示当前 CMakeLists.txt 所在的源码目录
# CMAKE_SOURCE_DIR 表示最为外层 CMakeLists.txt 的源码根目录
# CMAKE_BINARY_DIR 指的是存放二进制文件的文件夹

# 设置 cpp 的编译选项
set(CMAKE_CXX_STANDARD 17) # 选择 cpp 的编译版本；因此不要用 -std=17 指定版本，因为这样跨平台就会出问题
set(CMAKE_CXX_STANDARD_REQUIRED ON) # bool 类型，表示是否一定要支持上述指定的 cpp 标准，off 表示 CMake 检测到编译器不支持 C++17 时不报错，而是默默调低到 C++14 给你用；on 则发现不支持报错，更安全
set(CMAKE_CXX_EXTENSIONS ON) # 设为 ON 表示启用 GCC 特有的一些扩展功能；OFF 则关闭 GCC 的扩展功能，只使用标准的 C++；要兼容其他编译器（如 MSVC）的项目，都会设为 OFF 防止不小心用了 GCC 才有的特性；此外，最好是在 project 指令前设置 CMAKE_CXX_STANDARD 这一系列变量，这样 CMake 可以在 project 函数里对编译器进行一些检测，看看他能不能支持 C++17 的特性
```

<br/>

<br/>

<br/>

# 4、如何在项目中添加新的.cc文件

```cmake
# add_executable用于设置最终编译得到的文件以及需要编译的文件
add_executable(main main.cc)

# 先创建编译得到的目标文件，再添加源文件
add_executable(main)
target_sources(main PUBLIC main.cc other.cc)

# 先创建编译得到的目标文件，再用一个变量存储源文件，最后添加源文件
add_executable(main)
set(sources main.cc other.cc)
target_sources(main PUBLIC ${sources})

# 使用 GLOB 自动查找指定拓展名的文件
add_executable(main)
file(GLOB sources *.cc)
file(GLOB sources CONFIGURE_DEPENDS *.cpp *.h) # 可以自动将新的文件添加
file(GLOB sources CONFIGURE_DEPENDS *.cpp *.h mylib/*.cpp mylib/*.h) # 将子文件夹里的文件一起添加进来
target_sources(main PUBLIC ${sources})

# 使用 aux_source_directory 自动搜集需要文件的后缀名（我个人比较认同的使用方式）
add_executable(main)
aux_source_directory(. sources)
aux_source_directory(mylib sources)
target_sources(main PUBLIC ${sources})

# 使用 GLOB_RECURSE 自动包含所有子文件夹下的文件（但是缺点就是可能会将build里面的文件一同加进来，所以我觉得这种比较差，就不用了...）
add_executable(main)
file(GLOB_RECURSE sources CONFIGURE_DEPENDS *.cc *.h)
target_sources(main PUBLIC ${sources})
```

<br/>

<br/>

<br/>



# 5、如何将代码编译成库

把文件编译成一个静态库

```cmake
# 第一个是库的名字，第二个表示要将当前库编译成静态、动态还是对象库，最后是要编译的文件
add_library(mylib STATIC mylib.cc)
add_library(mylib SHARED mylib.cc)
add_library(mylib OBJECT mylib.cc) # 对象库类似于静态库，但不生成 .a 文件，只由 CMake 记住该库生成了哪些对象文件
# 对象库不生成 .a 文件，只由 CMake 记住该库生成了哪些对象文件，因此就有人推荐用对象库代替静态库，避免跨平台的麻烦

add_executable(main main.cc)

target_link_libraries(main PUBLIC mylib)
```

<br/>

一个比较坑的问题，动态库无法连接静态库，解决办法就是设置 `set(CMAKE_POSITION_INDEPENDENT_CODE ON)`

```cmake
# 设置全体库为 PIC
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_library(otherlib STATIC otherlib.cc)

add_library(mylib SHARED mylib.cc)
target_link_libraries(mylib PUBLIC otherlib)

add_executable(main main.cc)
target_link_libraries(main PUBLIC mylib)
```

<br/>

<br/>

<br/>

# 6、如何引用第三方库

<br/>

<br/>

<br/>

# 7、如何设置头文件的搜索路径

`include_directories`用于将给定的目录添加到编译器，便于搜索包含文件的目录

```cmake
# 将当前目录下的 include 目录添加到后续 .h 文件的搜索路径中
include_directories($CMAKE_CURRENT_SOURCE_DIR}/include)
```

也就是说，后续在 .cc 文件中填写的如果是相对路径，那么就会被解释为在当前这个源目录下的路径

比如说我们想要引入 include 文件夹下的 test.h 文件，文件真实路径为 include/test.h

那么在主目录中的 main.cc 就只需要 `#include test.h"`即可引入

<br/>

<br/>

`target_link_directories`则更加细粒度的规定了头文件的引用范围，作用和`include_directories`几乎相同

```cmake
# PRIVATE 表示这个目录下的头文件是不允许当前项目外的使用者使用的
target_include_directories(ara-com PRIVATE ${CMAKE_CURRENT_SOURCE_DIRP}/include/private)

# 假设当前的库需要依赖内部库的头文件但是却不需要依赖该库的.a或者.so文件 (比如说可能只需要弓入其头文件的部分结构体，而不需要调用其具体的函数) ，但是该内部的库还是需要对外提供功能，就是说外部的使用者还是需要使用该内部库 (即需要使用其头文件)，那么此时就需要设为INTERFACE
target_include_directories(ara-com INTERFACE ${CMAKE_CURRENT_SOURCE_DIRP}/include/public)

# PUBLIC 则表示该库的头文件是可以被外界使用的
target_include_directories(ara-com PUBLIC ${CMAKE_CURRENT_SOURCE_DIRP}/include/public)
```

<br/>

<br/>

<br/>

# 8、如何添加并构建子模块

```cmake
add_subdirectory(ara-api/core)
```

具体格式：`add_subdirectory (source_dir [binary_dir] [EXCLUDE_FROM_ALL])`

必选参数：`source_dir` 指定一个子目录，子目录下应该包含 CMakeLists.txt 文件和代码文件（可以是相对路径或绝对路径）

可选参数：`binary_dir` 指定一个子目录，用于存放输出的二进制文件（如果不指明的话，那么生成的可执行文件都会在build下的同名目录中）

<br/>

<br/>

<br/>

# 9、如何配置编译对象的属性

`set_target_properties(ara-com-common PROPERTIES POSITION_INDEPENDENT_CODE ON)`

<br/>

<br/>

<br/>

# 其他

记录一个之前遇到的小bug：

`set(CMAKE_EXPORT_COMPILE_COMMANDS ON)` 这句话不起作用，感觉是版本的原因

需要修改为`set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")`，这样才能生成 json 文件，以便 clang 实现代码跳转