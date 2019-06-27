#include"Deep.h"

Situation Situation::up(){
    string::size_type loc = code.find('0');//0的位置,从0开始计数
    Situation son;
    son.code = code;
    son.deep = deep + 1;
    if (loc>=3){
        char temp = son.code[loc];//即0
        son.code[loc] = son.code[loc - 3];
        son.code[loc-3] = temp;
    }
    else{
        son.code = "";
    }
    return son;
}

Situation Situation::down(){
    string::size_type loc = code.find('0');//0的位置,从0开始计数
    Situation son;
    son.code = code;
    son.deep = deep + 1;
    if (loc<=5){
        char temp = son.code[loc];//即0
        son.code[loc] = son.code[loc + 3];
        son.code[loc + 3] = temp;
    }
    else{
        son.code = "";
    }
    return son;
}

Situation Situation::left(){
    string::size_type loc = code.find('0');//0的位置,从0开始计数
    Situation son;
    son.code = code;
    son.deep = deep + 1;
    if (loc!=0&&loc!=3&&loc!=6){
        char temp = son.code[loc];//即0
        son.code[loc] = son.code[loc - 1];
        son.code[loc - 1] = temp;
    }
    else{
        son.code = "";
    }
    return son;
}

Situation Situation::right(){
    string::size_type loc = code.find('0');//0的位置,从0开始计数
    Situation son;
    son.code = code;
    son.deep = deep + 1;
    if (loc!=2&&loc!=5&&loc!=8){
        char temp = son.code[loc];//即0
        son.code[loc] = son.code[loc + 1];
        son.code[loc + 1] = temp;
    }
    else{
        son.code = "";
    }
    return son;
}

bool Situation::isGoal(){
    return code == GOAL;
}

bool Situation::isInOpen(deque<Situation> &open){
    for (int i = 0; i < open.size();i++){
        if (code==open.at(i).code){
            return true;
        }
    }
    return false;
}

bool Situation::isInClosed(deque<Situation> &closed){
    for (int i = 0; i < closed.size(); i++){
        if (code == closed.at(i).code){
            return true;
        }
    }
    return false;
}

void Situation::show() const{
    if (!code.empty()){
        cout << code[0] << code[1] << code[2] << endl
            << code[3] << code[4] << code[5] << endl
            << code[6] << code[7] << code[8] << endl << endl;
    }
    else{
        cout << "空的" << endl;
    }
}

void Situation::show(string code) const{
    if (!code.empty()){
        cout << code[0] << code[1] << code[2] << endl
            << code[3] << code[4] << code[5] << endl
            << code[6] << code[7] << code[8] << endl << endl;
    }
    else{
        cout << "空的" << endl;
    }
}

void Situation::show_deque(deque<Situation> &m_deque) const{
    for (int i = 0; i < m_deque.size();i++){
        m_deque.at(i).show();
    }
}

//路径
deque<Situation> Situation::showWay(deque<Situation> &closed){
    deque<Situation> dequeList;
    Situation temp = closed.back();
    dequeList.push_back(temp);

    //closed表从后往前，根据father值找到路径
    for (int i = closed.size()-1; i >= 0;i--){
        if (temp.father==closed.at(i).code){
            dequeList.push_back(closed.at(i));
            temp = closed.at(i);
        }
    }
    return dequeList;
}

void Situation::showAnswer(deque<Situation> &closed){
    deque<Situation> way(showWay(closed));
    cout << "共需要" << way.size() << "步" << endl;
    for (int i = way.size() - 1; i >= 0; i--)
    {
        way.at(i).show();
    }
    //输出目标
    show(GOAL);
}
