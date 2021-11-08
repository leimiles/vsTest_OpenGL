# vsTest_OpenGL
## 一，配置开发环境
1，配置 vscode 的 c++ 开发环境，首先需要配置 gcc 和 g++ 的编译器，可以在 [https://sourceforge.net/projects/mingw-w64/files/] 下载自己系统对应的版本(往列表下面看)，我是 [win10_X64] 下载的是 *x86_64_win32-seh* (47.8 MB)。

<img src="./Pics/pic01.png" width = 50%>


2，下载完成后解到固定目录，注意文件夹中有一个 \bin 目录，将这个 \bin 目录的完整路径添加到系统变量的 Path 中，打开 [git bash] 或者 [window powershell]，输入 **gcc --version**，**g++ --version** 和 **gdb --version** 命令，如果配置成功会显示编译器信息，注意 \bin 目录中还有一个 *mingw32-make.exe* 文件，复制它，重命名为 *make.exe*，后面会用到

<img src="./Pics/pic02.png" width = 50%>

3，为 vscode 安装必要插件 [C/C++ By Microsoft]， [C/C++ Project Generator By danielpinto8zz6]，[Code Runner By Jun Han]，到这一步可以实验一段 c++ 代码看看是否能运行。使用 Ctrl + Shift + P 呼出 vscode 命令行，选择 Create Project ，选择自己的工程目录文件夹，插件会自动创建所需的 \lib, \include, 等文件夹，可以使用 make run 运行程序，如果运行失败，要检查 /.vscode 文件夹中 *c_cpp_properties.json* 的配置，如果运行成功则可以进行下一步

<img src="./Pics/pic03.png" width = 50%>

<img src="./Pics/pic04.png" width = 30%>

4，下载 glfw 框架，[https://www.glfw.org/download.html]，要下载与自己的 minGW 对应的版本，我这里是 *64-bit Windows binaries* 的预编译文件


5，配置库文件
>* glfw 解压包中的 \include\GLFW 文件夹，放入工程目录中的 \include 文件夹下
>* glfw 解压包中的 \lib-mingw-w64 文件夹下的 *libglfw3.a* 和 *libglfw3dll.a* 两个文件，放入工程目录的 \lib 文件夹下，*glfw3.dll* 文件放到工程目录的 \output 文件夹下
>* 生成 glad 静态库文件，在这个链接 [https://glad.dav1d.de/] 下生成 *glad.zip* 文件，Language(c/c++)，Specification(OpenGL)，API(最高版本)，Profile(Core) 需要设置，勾选 *Generate a loader* 生成，生成后下载 glad.zip 文件解压
>* **gcc ./src/glad.c -c -I ./include/** //在终端执行这个命令，会在当前目录下生成 *glad.o* 文件
>* **ar -rc libglad.a glad.o** //在终端执行这个命令，会在当前目录下生成 *libglad.a* 文件，将这个文件也放入工程目录的 \lib 文件夹下
>* 将 glad 解压包中的 \include 文件夹下的内容，也全都放到工程目录的 \include 文件夹下

6，测试库文件，可以在测试的 cpp 代码中包含 **#include <glad/glad.h>** 和 **#include<GLFW/glfw3.h>** ，如果不报错，则是包含成功，这时 **make run** 命令也应该是正常的，否则要检查 *c_cpp_properties.json* 文件

<img src="./Pics/pic05.png" width = 50%>

7，配置 Makefile 命令，打开 Makefile 文件
>* 在 # define lib directory 注释下添加变量，**LIBRARIES := -lglad -lglfw3dll**
>* 在 75 行  \$(OBJECTS) \$(LFLAGS) \$(LIBS) 代码后面再加入 \$(LIBRARIES)，之后再运行 make run，正常

<img src="./Pics/pic07.png" width = 50%>

8，最终测试代码，**make run** 运行

<img src="./Pics/pic08.png" width = 50%>

