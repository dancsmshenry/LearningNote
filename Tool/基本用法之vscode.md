# 指令

## 复制上一行的数据

`alt + shift + 上或下键`，复制当前行的数据到下一行

<br/>

## 切换到终端

ctrl + `

<br/>

## 查找文件

`ctrl + p`

<br/>

## 查找字符

`ctrl + f`

<br/>

## 运行代码

`ctrl + alt + n`

<br/>

## 选取某一列的数据

`alt + shift + 鼠标下拉或上拉`

<br/>

## 折叠代码行

折叠所有代码行：按住 ctrl （始终不要松开），再按 k，松开 k，再按 0，即 `ctrl+k+0`

打开所有代码行：按住 ctrl （始终不要松开），再按 k，松开 k，再按 j，即 `ctrl+k+j`

<br/>

## 集体移动代码

`ctrl + {` 将选中的代码左移

`ctrl + }` 将选中的代码右移

注：一般用于格式的控制

<br/>

## 注释代码

`ctrl + /` 将当前行的代码注释

<br/>

## 删除代码

`ctrl + shift + k` 将当前行的代码全部删掉

<br/>

<br/>

<br/>

# 插件

## clangd

因为 clangd 既可以对 c 进行跳转，也可以对 c++，所以建议每次最好添加配置文件 `./vscode/settings.json`

```json
{
    "clangd.fallbackFlags": [
        "-std=c++17",
        // "-xc"
    ],
    "editor.tabSize": 2, // 重新设定tabsize
}
```

<br/>

并且，对于 `json` 文件的配置，我习惯将 json 放到 build 中，所以在配置 clangd 的时候，后面加上这句话

`--compile-commands-dir=${workspaceFolder}/build/`

<br/>

## Vscode-icons

可以控制vscode中的文件管理的树目录显示图标，即改变文件显示的图标

<br/>

## Rainbow Brackets

可以将同一对花括号给定相同的颜色，可以一眼就看出配对的两个花括号

<br/>

## Polacode

将代码变为照片存储，便于分享

使用方法：ctrl+shift+p，然后输入polacode

<br/>

## One Dark Pro

one dark pro 背景主题

<br/>

## Astyle

- 格式化代码

<br/>

## C/C++

- 又名 cpptools，提供Debug和Format功能

<br/>

## Language Support for Java(TM) by Red Hat

- java的配置（也没有必要一定要这样配置，但是这样配置会更舒服）
  - 方法参考日志2021.04.15

<br/>

## Markdown in all one

- 能够给markdown创建目录
  - 虽然[toc]也可以，但是上传到github就不行了
  - 用法：
    - ctrl+shift+p，进入命令行，输入ctoc，找到markdown目录，点击即可

<br/>

## Setting sync

- 多端同步配置

<br/>



# vscode下配置gcc

创建一个.vscode的文件夹，里面放两个文件一个是 task.json，另一个是 launch.json

```json
// task.json
{
    "version": "2.0.0",
    "tasks": [
        {
            "label": "g++",
            "command": "g++",
            "args": [
                "-g",
                "${file}",
                "-o",
                "${fileDirname}/${fileBasenameNoExtension}.exe",
                "-finput-charest=UTF-8",
                "-fexec-charest=UTF-8",
                "-std=c++11"
            ],
            "problemMatcher": {
                "owner": "cpp",
                "fileLocation": [
                    "relative",
                    "${workspaceRoot}"
                ],
                "pattern": {
                    "regexp": "^(.*):(\\d+):(\\d+):\\s+(warning|error):\\s+(.*)$",
                    "file": 1,
                    "line": 2,
                    "column": 3,
                    "severity": 4,
                    "message": 5
                }
            },
            "group": {
                "kind": "build",
                "isDefault": true
            }
        }
    ]
}
```



```json
// launch.json
{
    "version": "0.2.0",
    "configurations": [

        {
            "name": "(gdb) Launch",    // 配置名称，将会在启动配置的下拉菜单中显示
            "type": "cppdbg",         // 配置类型，这里只能为cppdbg
            "request": "launch",    // 请求配置类型，可以为launch（启动）或attach（附加）
            "program": "${fileDirname}/${fileBasenameNoExtension}.exe",// 将要进行调试的程序的路径
            "args": [],                // 程序调试时传递给程序的命令行参数，一般设为空即可
            "stopAtEntry": false,     // 设为true时程序将暂停在程序入口处，一般设置为false
            "cwd": "${workspaceRoot}",// 调试程序时的工作目录，一般为${workspaceRoot}即代码所在目录
            "environment": [],
            "externalConsole": true,// 调试时是否显示控制台窗口，一般设置为true显示控制台
            "MIMode": "gdb",
            "miDebuggerPath": "D:\\Cpp\\TDM-GCC-64\\bin\\gdb64.exe",// miDebugger的路径，注意这里要与MinGw的路径对应
            "preLaunchTask": "g++",    // 调试会话开始前执行的任务，一般为编译程序，c++为g++, c为gcc
            "setupCommands": [
                {
                    "description": "Enable pretty-printing for gdb",
                    "text": "-enable-pretty-printing",
                    "ignoreFailures": true
                }
            ]
        }
    ]
}
```

<br/>

<br/>

<br/>

# settings

whitespace ，提交代码中需要将空格给删掉（选项：trim trailing whirespace）

<br/>

<br/>

<br/>

# to do list

https://blog.csdn.net/m0_46548070/article/details/105116420

https://blog.csdn.net/weixin_44263973/article/details/120998615

https://www.baidu.com/s?ie=UTF-8&wd=The%20authenticity%20of%20host%20%27github.com%20(20.205.243.166)%27%20can%27t%20be%20established

https://blog.csdn.net/m0_56257585/article/details/125322437

vscode 终端消息太多，导致显示消息量有限：https://blog.csdn.net/weixin_42429288/article/details/109359724
