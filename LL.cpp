#include "LL.h"

int error_index = 0;                           //错误在的程序splits的index
map<string, int>getIndex;               //终结符与非终结符对应map编号
string termOrN[100];                     //由map编号获得非终结符或终结符
vector<Production>proces;               //所有的产生式（文法）
int table[100][100];                      //预测分析表，数字为产生式在proces中的index
int apartTorNT;                    //终结符与非终结符分界数字：<=22为终结符，>=22为非终结符
int totalTorNT;                     //一共有多少终结符和非终结符
set<string> first[100];                 //first集
set<string> follow[100];                //follow集
vector<Outpro> outPut;                  //推导用到的产生式们

void read_prog(string& prog)
{
    char c;
    const char* fileName = "program.txt";
    ifstream ifs;
    ifs.open(fileName, ios::in);
    while ((c = ifs.get())!=-1) {
        prog += c;
    }
    ifs.close();
}

void initialization()
{

    //获取所有的终结符
    int i;
    memset(table, -1, sizeof(table));
    cout << "请输入所有的终结符，以空格相间，enter结束：" << endl;
    string nTerminals; 
    vector<string> splitNT;
    getline(cin, nTerminals);
    get_splits_of_prog(nTerminals, splitNT);
    for (i = 0; i < splitNT.size(); i++) {
        getIndex[splitNT[i]] = i;
        termOrN[i] = splitNT[i];
    }
    //添加上结尾符号$和空符号E
    getIndex["$"] = i; termOrN[i++] = "$";
    getIndex["E"] = i; termOrN[i++] = "E";
    apartTorNT = i - 1;
    

    //获取所有的非终结符
    cout << "请输入所有的非终结符，以空格相间，enter结束：" << endl;
    string Terminals;
    vector<string> splitT;
    getline(cin, Terminals);
    get_splits_of_prog(Terminals, splitT);
    for (int j=0; j < splitT.size(); j++) {
        getIndex[splitT[j]] = i;
        termOrN[i++] = splitT[j];
    }
    totalTorNT = i;
  
    //从grammar.txt文法生成产生式
    Production tmpPro;
    ifstream ifs("grammar.txt", ios::in);
    while (!ifs.eof()) {
        string tmp;
        vector<string> splitTmp;
        getline(ifs, tmp);
        get_splits_of_prog(tmp, splitTmp);
        tmpPro.left = "";
        tmpPro.right = "";
        int index = 0;
        tmpPro.left = splitTmp[index];
        while (splitTmp[index++] != "->");
        while (index < splitTmp.size()) {
            tmpPro.right += splitTmp[index];
            if(index!=splitTmp.size()-1)
                tmpPro.right += " ";
            index++;
        }
        proces.push_back(tmpPro);
    }
    ifs.close();
};


vector<string> split(string& s, string& seperator) {
    vector<string> result;
    unsigned int posBegin = 0;
    string::size_type posSeperator = s.find(seperator);

    while (posSeperator != s.npos) {
        result.push_back(s.substr(posBegin, posSeperator - posBegin));// 
        posBegin = posSeperator + seperator.size(); // 分隔符的下一个元素
        posSeperator = s.find(seperator, posBegin);
    }
    if (posBegin != s.length()) // 指向最后一个元素，加进来
        result.push_back(s.substr(posBegin));
    return result;
}

void getFirst(string target) {
    Production tmppro;
    for (int i = 0; i < proces.size(); i++) {
        tmppro = proces[i];
        if (tmppro.left == target) {
            string tmpright = tmppro.right;
            string seperator = " ";
            vector<string> splitArray = split(tmpright, seperator);

            if (getIndex[splitArray[0]] <= apartTorNT) {
                first[getIndex[target]].insert(splitArray[0]);
            }
            else {
                int j = 0;
                while (j < splitArray.size()) {
                    getFirst(splitArray[j]);
                    for (set<string>::iterator it = first[getIndex[splitArray[j]]].begin(); it != first[getIndex[splitArray[j]]].end(); it++) {
                        first[getIndex[target]].insert(*it);
                    }
                    if (first[getIndex[splitArray[j]]].count("E") == 0) {
                        break;
                    }
                    j++;
                }
            }
        }
    }
}

void getfirst()
{
    for (int i = 0; i <= apartTorNT; i++)     //终结符，first集是其本身。
    {
        first[i].insert(termOrN[i]);
    }
    for (int j = 0; j < proces.size(); j++)    //扫描所有产生式
    {
        string left = proces[j].left;
        getFirst(left);
    }
}

void print_first()
{
    cout << "first集:" << endl;
    for (int i = 0; i <= 36; i++)
    {
        cout << "first [" << termOrN[i] << "]: ";
        for (set<string>::iterator it = first[i].begin(); it != first[i].end(); it++)
            cout << *it << " ";
        cout << endl;
    }
    cout << endl;
}

void getFollow(string target)
{
    for (int i = 0; i < proces.size(); i++) {
        string seperator = " ";
        vector<int> index;
        vector<string> splitArray = split(proces[i].right, seperator);
        int len = splitArray.size();
        for (int j = 0; j < len; j++) {
            if (splitArray[j] == target) {
                index.push_back(j);
            }
        }
        while (!index.empty()) {
            if (index[0] < len - 1) {
                string next = splitArray[index[0] + 1];
                if (getIndex[next] < apartTorNT) {
                    follow[getIndex[target]].insert(next);
                }
                else {
                    bool isE = false;
                    for (set<string>::iterator it = first[getIndex[next]].begin(); it != first[getIndex[next]].end(); it++) {
                        if (*it == "E") {
                            isE = true;
                        }
                        else
                            follow[getIndex[target]].insert(*it);
                    }
                    if (isE && proces[i].left != target) {
                        string newtarget = proces[i].left;
                        if (newtarget == proces[0].left) {
                            follow[getIndex[newtarget]].insert("$");
                        }
                        getFollow(newtarget);
                        for (set<string>::iterator it = follow[getIndex[newtarget]].begin(); it != follow[getIndex[newtarget]].end(); it++) {
                            follow[getIndex[target]].insert(*it);
                        }
                    }
                }
                index.erase(index.begin());
            }
            else if (index[0] == len - 1 && target != proces[i].left) {
                string newtarget = proces[i].left;
                if (follow[getIndex[newtarget]].empty()) {
                    getFollow(newtarget);
                }
                for (set<string>::iterator it = follow[getIndex[newtarget]].begin(); it != follow[getIndex[newtarget]].end(); it++) {
                    follow[getIndex[target]].insert(*it);
                }
                index.erase(index.begin());
            }
            else {
                index.erase(index.begin());
            }
        }
        if (target == "program") {
            follow[getIndex[target]].insert("$");
        }
    }
}

void getfollow()
{
    for (int j = 0; j < proces.size(); j++)    //扫描所有产生式
    {
        string left = proces[j].left;
        getFollow(left);
    }
}

void print_follow()
{
    cout << "follow集:" << endl;
    for (int i = apartTorNT + 1; i <= 36; i++)
    {
        cout << "follow [" << termOrN[i] << "]: ";
        for (set<string>::iterator it = follow[i].begin(); it != follow[i].end(); it++)
            cout << *it << " ";
        cout << endl;
    }
    cout << endl;
}

void gettable()          //得预测分析表
{
    for (int i = 0; i < proces.size(); i++) {
        string tmpleft = proces[i].left;
        string tmpright = proces[i].right;
        string seperator = " ";
        vector<string> splitArray = split(tmpright, seperator);
        string tmp = splitArray[0];
        if (getIndex[tmp] < apartTorNT) {
            table[getIndex[tmpleft]][getIndex[tmp]] = i;
        }

        else if (getIndex[tmp] == apartTorNT) {
            for (set<string>::iterator it = follow[getIndex[tmpleft]].begin(); it != follow[getIndex[tmpleft]].end(); it++) {
                table[getIndex[tmpleft]][getIndex[*it]] = i;
            }
        }
        else {
            for (int j = 0; j < splitArray.size(); j++) {
                for (set<string>::iterator it = first[getIndex[splitArray[j]]].begin(); it != first[getIndex[splitArray[j]]].end(); it++) {
                    table[getIndex[tmpleft]][getIndex[*it]] = i;
                }
                if (first[getIndex[splitArray[j]]].count("E") == 0) {
                    break;
                }
            }
        }
    }
}

string get_production(int i)  //由对应下标获得对应产生式。
{
    if (i < 0)return " ";    //无该产生式
    string ans;
    ans += proces[i].left;
    ans += "->";
    ans += proces[i].right;
    return ans;
}

//void print_table()
//{
//    cout << "预测分析表：" << endl;
//    for (int i = 0; i < apartTorNT; i++)
//        cout << '\t' << termOrN[i];
//    cout << endl;
//    for (int i = apartTorNT + 1; i < totalTorNT; i++)
//    {
//        cout << termOrN[i];
//        for (int j = 0; j < apartTorNT; j++)
//        {
//            //cout << '\t' << get_production(table[i][j]); //这里预测分析表格中打印完整的产生式，与下文2选1
//            if(table[i][j]!=-1)
//                cout << '\t' << table[i][j]; //这里预测分析表格中打印grammar.txt中产生式的编号,与上文2选1
//        }
//        cout << endl;
//    }
//    cout << endl;
//}

void print_table()
{
    //cout重定向，使得预测分析表能够打印到文件table.txt中
    fstream file("table.csv", ios::out);
    streambuf* stream_buf_cout = cout.rdbuf();
    streambuf* stream_buf_file = file.rdbuf();
    cout.rdbuf(stream_buf_file);
    cout <<endl<< "-----------------------------------------\
        预测分析表----------------------------------------" << endl;
    for (int i = 0; i < apartTorNT; i++)
        cout << '\t' << termOrN[i];
    cout << endl;
    for (int i = apartTorNT + 1; i < totalTorNT; i++)
    {
        cout << termOrN[i];
        for (int j = 0; j < apartTorNT; j++)
        {
            //cout << '\t' << get_production(table[i][j]); //这里预测分析表格中打印完整的产生式，与下文2选1
            if (table[i][j] != -1)
                cout << '\t' << table[i][j]; //这里预测分析表格中打印grammar.txt中产生式的编号,与上文2选1
        }
        cout << endl;
    }
    cout << endl;
    cout.rdbuf(stream_buf_cout);
    file.close();
}

bool change = false;            //change变量为true表示出现一次缺失错误
bool tryagain = false;          //tryagain变量为true表示在一次缺失填补好之后再次碰到错误，即该次错误填补失效，需要更换错误填补
bool analyzing(stack<string> stk, vector<string> splits, string& error) {

    int i = 0;
    while (!stk.empty())
    {
        string topstr = stk.top();
        stk.pop();
        if (topstr == splits[i] && topstr != "$")       //是终结符，推进
        {
            i++;
            //cout << topstr << endl;
        }
        else  if (topstr == "$" && splits[i] == "$")   //成功，结束
        {
            return true;
        }
        else  if (table[getIndex[topstr]][getIndex[splits[i]]] > -1) //非终结符，查表
        {
            int proceIndex = table[getIndex[topstr]][getIndex[splits[i]]];
            int height = stk.size();
            if (!change || (change && tryagain)) {
                Outpro pro(proces[proceIndex].left, proces[proceIndex].right, height);
                outPut.push_back(pro);
            }
            
            string tmpright = proces[proceIndex].right;
            string seperator = " ";
            vector<string> splitArr = split(tmpright, seperator);
            for (int j = splitArr.size() - 1; j >= 0; j--)  //逆序入栈
            {
                if (splitArr[j] != "E")
                    stk.push(splitArr[j]);
            }
        }
        else      //失败！
        {
            if (change)
                return false;
            if (!change) {
                error_index = i;
                stk.push(topstr);
            }
            change = true;
            vector<string> splitStr2 = { splits.begin() + i,splits.end() };
            for (int k = 0; k < apartTorNT - 1; k++) {
                if (termOrN[k] == splitStr2[0]) {
                    continue;
                }
                splitStr2.insert(splitStr2.begin(), termOrN[k]);
                if (analyzing(stk, splitStr2, error)) {
                    error = termOrN[k];
                    tryagain = true;
                    analyzing(stk, splitStr2, error);
                    return false;
                }
                else {
                    splitStr2.erase(splitStr2.begin());
                }
            }
            return false;
        }
    }
    return true;
}

void get_lines(string prog, int& error_index) {
    int index = 0;
    int lines = 0;
    bool flag = false;
    for (int i = 0; i < prog.size(); i++) {
        if (prog[i] != ' ' && prog[i] != '\t' && prog[i] != '\n') {
            if (!flag) {
                index++;
            }
            if (index == error_index) {
                error_index = lines;
                return;
            }
            flag = true;
        }
        else {
            flag = false;
            if (prog[i] == '\n') {
                lines++;
            }
        }
    }
}

void tabs(int height) {
    while (height--) {
        cout << "\t";
    }
}

int height = 1;
void tree_construct(TreeNode cur) {
    int tmpheight = cur->height;
    if ((height - 1) < outPut.size()) {
        string right = outPut[height - 1].right;
        string seperator = " ";
        vector<string> splits = split(right, seperator);
        for (int j = 0; j < splits.size(); j++) {
            Node* tmp = new Node(splits[j], tmpheight + 1);
            cur->child.push_back(tmp);
        }
        for (int j = 0; j < cur->child.size(); j++) {
            while ((j < cur->child.size()) && (getIndex[cur->child[j]->symbol] <= apartTorNT)) {
                j++;
            }
            if (j < cur->child.size()) {
                height++;
                tree_construct(cur->child[j]);
            }
            else {
                return;
            }
        }
    }
}

void tree_print(TreeNode root) {
    int len = root->child.size();
    for (int i = 0; i < len; i++) {
        tabs(root->child[i]->height);
        cout << root->child[i]->symbol << endl;
        //if (getIndex[root->child[i]->symbol] > apartTorNT) {
        tree_print(root->child[i]);
        //}
    }
    return;
}

void get_splits_of_prog(string prog, vector<string>& splitStr) {
    string word;
    for (int i = 0; i < prog.size(); i++) {
        if (prog[i] != ' ' && prog[i] != '\t' && prog[i] != '\n' && prog[i] != '\r') {
            word += prog[i];
        }
        else {
            if (word.size() != 0)
                splitStr.push_back(word);
            word.clear();
        }
    }
    if (!word.empty())
        splitStr.push_back(word);
}


void Analysis()       //总控，分析字prog的合法性，若合法，输出所有产生式。
{
    string prog;
    vector<string> splitStr;
    read_prog(prog);
    initialization();
    getfirst();
    print_first();
    getfollow();
    print_follow();
    gettable();
    print_table();
    get_splits_of_prog(prog, splitStr);
    splitStr.push_back("$");

    //分析栈
    stack<string> stk;
    string error = "";
    stk.push("$");
    stk.push(proces[0].left);

    //分析出入栈过程
    analyzing(stk, splitStr, error);
    get_lines(prog, error_index);
    if (error != "") {
        cout << "语法错误，第" << error_index + 1 << "行，缺少\"" << error << "\"" << endl;
    }

    //构造语法树并横向输出（同层高度的符号举例左侧的举例相同）
    Node root("program", 0);
    tree_construct(&root);
    tabs(root.height);
    cout << root.symbol << endl;
    tree_print(&root);

}