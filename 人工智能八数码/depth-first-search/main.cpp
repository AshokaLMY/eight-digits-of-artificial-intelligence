#include<iostream>
#include"Deep.h"

using namespace std;

void loop(deque<Situation> &open, deque<Situation> &closed, int range);

int main(){
    string original = "283164705";
    Situation first;
    deque<Situation> open, closed;//open存放未扩展节点，closed存放已扩展节点
    int range = 10;//深度界限

    first.code = original;
    first.deep = 0;
    open.push_back(first);
    loop(open,closed,range);
    return 0;
}

void loop(deque<Situation> &open, deque<Situation> &closed,int range){
    Situation a;
    int i = 0;
    while (!open.empty()){
        i++;
        if (open.front().code == GOAL){
            cout << "成功：" << endl;
            a.showAnswer(closed);
            return;
        }
        if (open.empty()){
            cout << "失败" << endl;
            return;
        }
        closed.push_back(open.front());
        open.pop_front();
        //节点n的深度是否等于深度界限
        if (closed.back().deep == range){
            continue;
        }
        else{
            //扩展节点n,把其后裔节点放入OPEN表的末端
            Situation son1 = closed.back().up();
            Situation son2 = closed.back().down();
            Situation son3 = closed.back().left();
            Situation son4 = closed.back().right();
            /*
            广度优先搜索和深度优先搜索的唯一区别就是子节点放到open表的位置：
            （1）广度优先搜索放到open表的后面
            （2）深度优先搜索放到open表的前面
            */
            if (!son1.code.empty()){
                if (!son1.isInOpen(open)&&!son1.isInClosed(closed)){
                    son1.father = closed.back().code;
                    open.push_front(son1);
                }
            }
            if (!son2.code.empty()){
                if (!son2.isInOpen(open) && !son2.isInClosed(closed)){
                    son2.father = closed.back().code;
                    open.push_front(son2);
                }
            }
            if (!son3.code.empty()){
                if (!son3.isInOpen(open) && !son3.isInClosed(closed)){
                    son3.father = closed.back().code;
                    open.push_front(son3);
                }
            }
             if (!son4.code.empty()){
                if (!son4.isInOpen(open) && !son4.isInClosed(closed)){
                    son4.father = closed.back().code;
                    open.push_front(son4);
                }

            }
            //是否有任何后继节点为目标节点
            if (son1.isGoal()){
                cout << "后继节点中有目标节点" << endl;
                son1.showAnswer(closed);
                break;
            }
            if (son2.isGoal()){
                cout << "后继节点中有目标节点" << endl;
                son2.showAnswer(closed);
                break;
            }
            if (son3.isGoal()){
                cout << "后继节点中有目标节点" << endl;
                son3.showAnswer(closed);
                break;
            }
            if (son4.isGoal()){
                cout << "后继节点中有目标节点" << endl;
                son4.showAnswer(closed);
                break;
            }
        }
    }
}
