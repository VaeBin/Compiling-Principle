#pragma once
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <stack>
#include <set>
using namespace std;

//产生式结构pro1 -> statement分为左右两部分string
typedef struct Production {
    string left;
    string right;
    Production(string l, string r) {
        this->left = l;
        this->right = r;
    }
    Production() {}
}Production;

//推导过程用到的产生式，多加了height属性：语法树中的高度
typedef struct Outpro {
    string left;
    string right;
    int height;
    Outpro(string l, string r, int h) {
        this->left = l;
        this->right = r;
        this->height = h;
    }
    Outpro() {}
}Outpro;

//语法树中的节点，包含自身符号，子节点们，以及本身的树中的高度（根节点高度为0）
typedef struct Node {
    string symbol;
    vector<Node*> child;
    int height;
    Node(string s, int h) {
        this->symbol = s;
        this->height = h;
    }
}Node;
typedef Node* TreeNode;
typedef struct Tree {
    TreeNode root;
}Tree;

void read_prog(string& prog);             //从program.txt文件中输入程序得到字符串prog
void initialization();             //初始化输入终结符、非终结符、以及从grammar.txt文法文件中生成产生式
vector<string> split(string& s, string& seperator);        //利用分隔符seperator分割s得到字符串数组
void getFirst(string target);           //得到first集合
void getfirst();            //getFirst调用的递归函数得到first集合
void print_first();         //打印first集合
void getFollow(string target);          //得到follow集合
void getfollow();           //getFollow调用的递归函数得到follow集合
void print_follow();        //打印follow集合
void gettable();        //得到预测分析表
string get_production(int i);       //根据相应的产生式编号i得到产生式字符串形式A -> Abc
void print_table();         //打印预测分析表
bool analyzing(stack<string> stk, vector<string> splits, string& error);        //分析栈出入过程
void get_lines(string prog, int& error_index);      //由程序prog空格分割后的字符串数组的error_index找到程序prog对应的行数
void tabs(int height);          //根据语法树的高度height横向打印空格
void tree_construct(TreeNode cur);      //建造语法树（非终结符）
void tree_print(TreeNode root);         //打印语法树
void get_splits_of_prog(string prog, vector<string>& splitStr);     //由prog程序得到分割后的字符串数组splitStr
void Analysis();        //main函数调用的唯一分析函数，所有函数的“容器”

