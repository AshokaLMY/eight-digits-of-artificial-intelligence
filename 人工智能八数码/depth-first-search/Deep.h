#include<iostream>
#include"queue"
#include"string"
#include<list>

using namespace std;

const string GOAL = "803214765";

class Situation{
private:

public:
    string father;
    string code;//当前状态
    int deep;
    Situation up();
    Situation down();
    Situation left();
    Situation right();
    bool isGoal();
    bool isInOpen(deque<Situation> &open);
    bool isInClosed(deque<Situation> &closed);
    void show() const;
    void show(string) const;
    void show_deque(deque<Situation> &) const;
    deque<Situation> showWay(deque<Situation> &closed);
    void showAnswer(deque<Situation> &closed);//显示解答
    Situation() :father(""), code(""), deep(-1){};
};
