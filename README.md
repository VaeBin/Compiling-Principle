# Compiling-Principle
一些编译原理的实现算法或者讲解
文件内容指南 	
	(1) LL(1) Parser 项目文件
	LL.h           ---------    数据结构定义以及函数声明  
	LL.cpp         ---------    LL.h文件的函数定义以及变量声明  
	main.cpp       ---------    主函数  
	program.txt    ---------    待分析的程序语句（token之间需要用空格或者换行符分割）  
	grammar.txt    ---------    语法文法分析（每一条产生式token之间用空格分割，相邻产生式使用换行符分割）  
	table.txt      ---------    生成的parsing table将被保存至此  
