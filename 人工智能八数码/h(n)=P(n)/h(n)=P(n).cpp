#include<iostream> 
#include<vector>
#include<time.h>
#include<algorithm>
using namespace std;
const int GRID = 3; //Grid表示表格的行数(列数)，这是3*3的九宫格
int rightPos[9] = { 4, 0, 1, 2, 5, 8, 7, 6, 3 };
//目标状态时，若p[i][j]=OMG,那么3*i+j = rightPos[OMG]
struct state{
    int panel[GRID][GRID];
    int level; //记录深度
    int h; state * parent;
    state(int level) :level(level){}
    bool operator == (state & q){
        //判断两个状态是否完全相等（对应位置元素相等），完全相等返回true, 否则返回false
        for (int i = 0; i<GRID; i++)
            {
                for (int j = 0; j<GRID; j++)
                {
                    if (panel[i][j] != q.panel[i][j])
                    return false;
                }
             }
             return true;
    }
    state & operator = (state & p){ //以状态p为当前状态赋值， 对应位置元素相同
        for (int i = 0; i<GRID; i++)
            {
                for (int j = 0; j<GRID; j++)
                {
                    panel[i][j] = p.panel[i][j];
                }
            }
        return *this;
    }
};

void dump_panel(state * p){ //将八数码按3*3矩阵形式输出
    for (int i = 0; i<GRID; i++)
        {
            for (int j = 0; j<GRID; j++)
                cout << p->panel[i][j] << " ";
            cout << endl;
        }
}
int countH(state & st){ //给定状态st，计算它的h值。
    int h = 0;
    for (int i = 0; i<GRID; i++)
        {
            for (int j = 0; j<GRID; j++)
            {
                if (st.panel[i][j] != 0)
                h += abs(rightPos[st.panel[i][j]] / GRID - i) + abs(rightPos[st.panel[i][j]] % GRID - j);
    //h=各个将牌与其目标位置的距离之和.距离定义为： 行下标之差的绝对值+列下 标之差的绝对值。
             }
        }
        return h;
}

int findZero(state & st){ //找到零值元素，返回其在表中的位置
    for (int i = 0; i<GRID; i++)
        {
            for (int j = 0; j<GRID; j++)
            {
                if (st.panel[i][j] == 0) return i * 3 + j;
            }
        }
}

int f(state * p){ //计算并返回f()值，即h值+level
    return countH(*p) + p->level;
}

bool compare_state(state * p, state * q){ //比较两个状态的f值
    return f(p) > f(q);
}

vector<state *> open_table; //open表
vector<state *> close_table;  //close表

vector<state*>::iterator look_up_dup(vector<state*> & vec, state * p){
    vector<state*>::iterator it_r = vec.begin();
    for (; it_r<vec.end(); it_r++){
            if ((*(*it_r)) == *p){
                break;
             }
    }
    return it_r;
}

state * search(state & start){ //A*算法进行搜索
    int level = 0;
    open_table.push_back(&start);
    int count = 0;

    while (!open_table.empty()){
            sort(open_table.begin(), open_table.end(), compare_state);
    //对open表中的元素进行排序

    state * p = open_table.back();
    open_table.pop_back();
    if (countH(*p) == 0)
        return p; //所有将牌到达目标位置，搜索过程结束
    level = p->level + 1;

    int zeroPos = findZero(*p);
    int x = zeroPos / 3; //空格的行下标
    int y = zeroPos % 3; //空格的列下标
    for(int i = 0; i<4; i++){ //上下左右四个方向
        int x_offset = 0, y_offset = 0;
        switch (i){
            case 0:x_offset = 0, y_offset = 1; break; //右
            case 1:x_offset = 0, y_offset = -1; break;//左
            case 2:x_offset = 1, y_offset = 0; break;//上
            case 3:x_offset = -1, y_offset = 0; break;//下

        };
        if (x + x_offset<0 || x + x_offset >= GRID || y + y_offset<0 || y + y_offset >= GRID){
                continue;
        //若移动一步后，将超出上/下/左/右边界，则这个方向不可走，尝试下一个方向
        }
        state * q = new state(level); //这个方向可走，扩展下一 个节点
        q->parent = p;
        *q = *p;
        q->panel[x][y] = q->panel[x + x_offset][y + y_offset];
        q->panel[x + x_offset][y + y_offset] = 0;//空格沿这个方向移一步
        bool skip = false;
        vector<state *>::iterator dup = look_up_dup(open_table, q);
        //若q已在open表中，则对open表中的信息进行更新
        if (dup != open_table.end()){
                if (f(q) < f(*dup)){
                    (*dup)->level = q->level;
                    (*dup)->parent = q->parent;
                }
                skip = true;
        }

        dup = look_up_dup(close_table, q);
        if (dup != close_table.end()){ //若q已在close表中，且f值比原值小，
             if (f(q) < f(*dup)){ //则将q从close表清除，加入open表
                delete *dup;
                close_table.erase(dup);
                open_table.push_back(q);
                skip = true;
              }
        }
        if (!skip){
                open_table.push_back(q);
        }
      }
      close_table.push_back(p);
    }
}

void dump_solution(state * q) { //输出解路径
    vector<state *> trace;
    while (q){
            trace.push_back(q);
            q = q->parent;
    }

    int count = 0;

    while (!trace.empty()){
            cout << "Step " << count << " :^-^=^-^=^-^=^-^=^ ^=^-^=^-^=^-^=^-^=^-^=^@\n";
            dump_panel(trace.back());
            cout << "h: " << countH(*trace.back()) <<"\tg:"<<count<< "\tf: "  << f(trace.back()) << endl << endl;
            trace.pop_back();
            count++;
    }
}

int main()
{
    state p(0);
    state *q;

    p.panel[0][0] = 2;//设置初始状态
    p.panel[0][1] = 1;
    p.panel[0][2] = 6;
    p.panel[1][0] = 4;
    p.panel[1][1] = 0;
    p.panel[1][2] = 8;
    p.panel[2][0] = 7;
    p.panel[2][1] = 5;
    p.panel[2][2] = 3;

    p.parent = NULL;
    q = search(p);

    dump_solution(q);

    system("pause");
}
