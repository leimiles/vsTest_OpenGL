# vsTest_OpenGL
## 一，配置开发环境
1，配置 vscode 的 c++ 开发环境，首先需要配置 gcc 和 g++ 的编译器，可以在 [https://sourceforge.net/projects/mingw-w64/files/] 下载自己系统对应的版本(往列表下面看)，我是 [win10_X64] 下载的是 *x86_64_win32-seh* (47.8 MB)。

2，下载完成后解到固定目录，注意文件夹中有一个 \bin 目录，将这个 \bin 目录的完整路径添加到系统变量的 Path 中，打开 [git bash] 或者 [window powershell]，输入 **gcc --version**，**g++ --version** 和 **gdb --version** 命令，如果配置成功会显示编译器信息，注意 \bin 目录中还有一个 *mingw32-make.exe* 文件，复制它，重命名为 *make.exe*，后面会用到

3，为 vscode 安装必要插件 [C/C++ By Microsoft]， [C/C++ Project Generator By danielpinto8zz6]，[Code Runner By Jun Han]，到这一步可以实验一段 c++ 代码看看是否能运行。使用 Ctrl + Shift + P 呼出 vscode 命令行，选择 Create Project ，选择自己的工程目录文件夹，插件会自动创建所需的 \lib, \include, 等文件夹，可以使用 make run 运行程序

4，下载 glfw 框架，[https://www.glfw.org/download.html](要下载与自己的 minGW 对应的版本)，