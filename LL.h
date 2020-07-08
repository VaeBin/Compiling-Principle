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

//����ʽ�ṹpro1 -> statement��Ϊ����������string
typedef struct Production {
    string left;
    string right;
    Production(string l, string r) {
        this->left = l;
        this->right = r;
    }
    Production() {}
}Production;

//�Ƶ������õ��Ĳ���ʽ�������height���ԣ��﷨���еĸ߶�
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

//�﷨���еĽڵ㣬����������ţ��ӽڵ��ǣ��Լ���������еĸ߶ȣ����ڵ�߶�Ϊ0��
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

void read_prog(string& prog);             //��program.txt�ļ����������õ��ַ���prog
void initialization();             //��ʼ�������ս�������ս�����Լ���grammar.txt�ķ��ļ������ɲ���ʽ
vector<string> split(string& s, string& seperator);        //���÷ָ���seperator�ָ�s�õ��ַ�������
void getFirst(string target);           //�õ�first����
void getfirst();            //getFirst���õĵݹ麯���õ�first����
void print_first();         //��ӡfirst����
void getFollow(string target);          //�õ�follow����
void getfollow();           //getFollow���õĵݹ麯���õ�follow����
void print_follow();        //��ӡfollow����
void gettable();        //�õ�Ԥ�������
string get_production(int i);       //������Ӧ�Ĳ���ʽ���i�õ�����ʽ�ַ�����ʽA -> Abc
void print_table();         //��ӡԤ�������
bool analyzing(stack<string> stk, vector<string> splits, string& error);        //����ջ�������
void get_lines(string prog, int& error_index);      //�ɳ���prog�ո�ָ����ַ��������error_index�ҵ�����prog��Ӧ������
void tabs(int height);          //�����﷨���ĸ߶�height�����ӡ�ո�
void tree_construct(TreeNode cur);      //�����﷨�������ս����
void tree_print(TreeNode root);         //��ӡ�﷨��
void get_splits_of_prog(string prog, vector<string>& splitStr);     //��prog����õ��ָ����ַ�������splitStr
void Analysis();        //main�������õ�Ψһ�������������к����ġ�������

