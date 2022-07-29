## 动态加载
利用dlopen实现动态链接库的运行时加载,只需要所有动态库实现include/lib_common.h中的接口，编译成动态库xxx.so,然后将其放置在指定目录下（build/lib_srcs),本项目只是一个demo

## 技术栈
1. dlfcn
2. thread
3. mutex

## 使用
<pre>
mkdir build && cd build
cmake .. && make
./main
</pre>