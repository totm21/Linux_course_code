# Linux_course_code

linux_四级项目_五级项目

如果可以的话最好给我点个star

白嫖伤人，点赞才是可持续发展的道路

## 文件规格

命名方式为  级数_序号_项目英文名

    例如:5_8_TCP    代表五级项目8-TCP基本网络通信

此处不多赘述

## 使用方法—基础

1. 打开终端(快捷键:Ctrl+Alt+T)
2. 在命令行输入 ./run  执行批处理脚本
3. 查看文件内是否有run2这个文件
   如果有则再开一个终端新并输入 ./run2
   没有就不用管了
4. 查看项目指导书并按照程序提示输入对应信息(例如自制shell这个项目 批处理执行后，需要在程序内输出对应指令)，程序入口处的参数信息，则不需要考虑(该参数已内嵌在批处理文件中)

## 使用方法—进阶

此处涉及更改程序

1. 首先，文件基础内基础结构为
   一定含有：
   n个.c(源码文件)+Makefile(编译规则文件)+run(批处理文件)
   可能含有
   .h(源码头文件)+run2(批处理文件)   大部分都是后面的项目才有
2. 最基础的是更改run文件  更改传入参数 执行顺序什么的 或者你也可以不敲./run 而是手敲里面的指令
3. Makefile文件不建议动(虽然大部分都没什么东西)
4. 最后是源码文件更改(我提倡，但出问题请别找我，以下是注释情况)
   首先是前几个项目比较简单  所以没怎么打注释
   中间的项目比较有耐心   所以注释比较全
   后面的项目失去耐心  所以注释比较随缘
5. 其实上面这些都是废话，你有更改的想法的时候，根本不需要看我这些话
