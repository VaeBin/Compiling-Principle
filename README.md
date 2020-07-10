# Compiling-Principle<br>
# 一些编译原理的实现算法或者讲解<br>

## 文件内容指南<br> 	
  ### (1) LL(1) Parser 项目文件<br>
　LL.h&emsp;&emsp;&emsp;&emsp;--------&emsp;&emsp;&emsp;&emsp;数据结构定义以及函数声明<br>  
　LL.cpp&emsp;&emsp;&emsp;&emsp;---------&emsp;&emsp;&emsp;&emsp;LL.h文件的函数定义以及变量声明<br>  
　main.cpp&emsp;&emsp;&emsp;&emsp;---------&emsp;&emsp;&emsp;&emsp;主函数<br>  
　program.txt&emsp;&emsp;&emsp;&emsp;---------&emsp;&emsp;&emsp;&emsp;待分析的程序语句（token之间需要用空格或者换行符分割）<br>  
　grammar.txt&emsp;&emsp;&emsp;&emsp;---------&emsp;&emsp;&emsp;&emsp;语法文法分析（每一条产生式token之间用空格分割，相邻产生式使用换行符分割）<br>  
　table.txt&emsp;&emsp;&emsp;&emsp;---------&emsp;&emsp;&emsp;&emsp;生成的parsing table将被保存至此<br>  
