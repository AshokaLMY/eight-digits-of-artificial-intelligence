#include<iostream>
#include"Deep.h"

using namespace std;

void loop(deque<Situation> &open, deque<Situation> &closed, int range);

int main(){
    string original = "283164705";
    Situation first;
    deque<Situation> open, closed;//open���δ��չ�ڵ㣬closed�������չ�ڵ�
    int range = 10;//��Ƚ���

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
            cout << "�ɹ���" << endl;
            a.showAnswer(closed);
            return;
        }
        if (open.empty()){
            cout << "ʧ��" << endl;
            return;
        }
        closed.push_back(open.front());
        open.pop_front();
        //�ڵ�n������Ƿ������Ƚ���
        if (closed.back().deep == range){
            continue;
        }
        else{
            //��չ�ڵ�n,�������ڵ����OPEN���ĩ��
            Situation son1 = closed.back().up();
            Situation son2 = closed.back().down();
            Situation son3 = closed.back().left();
            Situation son4 = closed.back().right();
            /*
            ��������������������������Ψһ��������ӽڵ�ŵ�open���λ�ã�
            ��1��������������ŵ�open��ĺ���
            ��2��������������ŵ�open���ǰ��
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
            //�Ƿ����κκ�̽ڵ�ΪĿ��ڵ�
            if (son1.isGoal()){
                cout << "��̽ڵ�����Ŀ��ڵ�" << endl;
                son1.showAnswer(closed);
                break;
            }
            if (son2.isGoal()){
                cout << "��̽ڵ�����Ŀ��ڵ�" << endl;
                son2.showAnswer(closed);
                break;
            }
            if (son3.isGoal()){
                cout << "��̽ڵ�����Ŀ��ڵ�" << endl;
                son3.showAnswer(closed);
                break;
            }
            if (son4.isGoal()){
                cout << "��̽ڵ�����Ŀ��ڵ�" << endl;
                son4.showAnswer(closed);
                break;
            }
        }
    }
}
