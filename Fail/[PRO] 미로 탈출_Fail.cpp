#include <string>
#include <vector>
#include <queue>
#include <iostream>
#include <algorithm>

#define MAX 1010
#define TRAP_MAX 10
#define INF 987654321
using namespace std;

bool Is_Trap[MAX];
int Trap_Index[MAX];
int Dist[MAX][1 << TRAP_MAX];
vector<pair<pair<int, int>, bool>> MAP[MAX];

int Min(int A, int B) { return A < B ? A : B; }

void Setting(int N, vector<vector<int>> Road)
{
    for (int i = 1; i <= N; i++) fill(Dist[i], Dist[i] + 1030, INF);
    for (int i = 0; i < Road.size(); i++)
    {
        int S = Road[i][0];
        int E = Road[i][1];
        int D = Road[i][2];
        MAP[S].push_back(make_pair(make_pair(E, D), true));
        MAP[E].push_back(make_pair(make_pair(S, D), false));
    }
}

void Make_Trap_Info(vector<int> Trap)
{
    for (int i = 0; i < Trap.size(); i++)
    {
        int N = Trap[i];
        Is_Trap[N] = true;
        Trap_Index[N] = i;
    }
}

int Find_Min_Cost(int E)
{
    int Result = INF;
    for (int i = 0; i < (1 << TRAP_MAX); i++)
    {
        Result = Min(Result, Dist[E][i]);
    }
    return Result;
}

int Find_Case(int Cur, int Next, int State)
{
    if (Is_Trap[Cur] == false && Is_Trap[Next] == false) return 1;
    if (Is_Trap[Cur] == false && Is_Trap[Next] == true) return 2;
    if (Is_Trap[Cur] == true && Is_Trap[Next] == false) return 3;
    return 4;
}

bool Trap_State(int Next, int State)
{
    if ((State & (1 << Trap_Index[Next])) == false) return false;
    return true;
}

int Active_Trap(int State, int Idx) { return State | (1 << Trap_Index[Idx]); }

int UnActive_Trap(int State, int Idx) { return State ^ (1 << Trap_Index[Idx]); }

int Dijkstra(int N, int S, int E)
{
    priority_queue<pair<int, pair<int, int>>> PQ;
    PQ.push(make_pair(0, make_pair(S, 0)));
    Dist[S][0] = 0;

    while (PQ.empty() == 0)
    {
        int Cur = PQ.top().second.first;
        int Cost = -PQ.top().first;
        int State = PQ.top().second.second;
        PQ.pop();

        for (int i = 0; i < MAP[Cur].size(); i++)
        {
            int Next = MAP[Cur][i].first.first;
            int Next_Cost = MAP[Cur][i].first.second + Cost;
            int Next_State = State;
            bool Edge_State = MAP[Cur][i].second;

            int Case = Find_Case(Cur, Next, State);
            if (Case == 1)
            {
                if (Edge_State == true)
                {
                    if (Dist[Next][Next_State] > Next_Cost)
                    {
                        Dist[Next][Next_State] = Next_Cost;
                        PQ.push(make_pair(-Next_Cost, make_pair(Next, Next_State)));
                    }
                }
            }
            else if (Case == 2)
            {
                bool Next_Trap_State = Trap_State(Next, State);
                if (Edge_State != Next_Trap_State)
                {
                    if (Next_Trap_State == true) Next_State = UnActive_Trap(Next_State, Next);
                    else Next_State = Active_Trap(Next_State, Next);

                    if (Dist[Next][Next_State] > Next_Cost)
                    {
                        Dist[Next][Next_State] = Next_Cost;
                        PQ.push(make_pair(-Next_Cost, make_pair(Next, Next_State)));
                    }
                }
            }
            else if (Case == 3)
            {
                bool Cur_Trap_State = Trap_State(Cur, State);
                if (Edge_State != Cur_Trap_State)
                {
                    if (Dist[Next][Next_State] > Next_Cost)
                    {
                        Dist[Next][Next_State] = Next_Cost;
                        PQ.push(make_pair(-Next_Cost, make_pair(Next, Next_State)));
                    }
                }
            }
            else
            {
                bool Cur_Trap_State = Trap_State(Cur, State);
                bool Next_Trap_State = Trap_State(Next, State);

                if ((Cur_Trap_State == Next_Trap_State) && (Edge_State == true))
                {
                    if (Next_Trap_State == true) Next_State = UnActive_Trap(Next_State, Next);
                    else Next_State = Active_Trap(Next_State, Next);

                    if (Dist[Next][Next_State] > Next_Cost)
                    {
                        Dist[Next][Next_State] = Next_Cost;
                        PQ.push(make_pair(-Next_Cost, make_pair(Next, Next_State)));
                    }
                }
                else if ((Cur_Trap_State != Next_Trap_State) && (Edge_State == false))
                {
                    if (Next_Trap_State == true) Next_State = UnActive_Trap(Next_State, Next);
                    else Next_State = Active_Trap(Next_State, Next);

                    if (Dist[Next][Next_State] > Next_Cost)
                    {
                        Dist[Next][Next_State] = Next_Cost;
                        PQ.push(make_pair(-Next_Cost, make_pair(Next, Next_State)));
                    }
                }
            }
        }
    }
    return Find_Min_Cost(E);
}

int solution(int n, int start, int end, vector<vector<int>> roads, vector<int> traps)
{
    int answer = 0;
    Setting(n, roads);
    Make_Trap_Info(traps);
    answer = Dijkstra(n, start, end);
    return answer;
}

int main()
{
    cout << solution(4, 1, 4, {{1,2,1},{3,2,1},{2,4,1}}, {2,3}) << endl;
    return 0;
}
