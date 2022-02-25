#include <map>
#include <queue>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

struct Unit
{
    int pos;
    int score;
    bool blue;
};

int result = 0;
Unit units[4];
vector<int> selected(10);
vector<int> dices(10);
map<int,vector<vector<int>>> Map;
const int DESTINATION = 41;
const int TURN = 10;

void print_map()
{
    for(int i = 0; i <= 40; i++)
    {
        if(Map.find(i) == Map.end())
            continue;
        if(Map[i][0].size() <= 0 && Map[i][1].size() <= 0)
            continue;

        printf("Map[%2d] :",i);
        for(auto j = 0; j < Map[i].size(); j++)
        {
            printf(" {");
            for(auto k = 0; k < Map[i][j].size(); k++)
                printf("%2d ",Map[i][j][k]);
            printf("}");
        }
        printf("\n");
    }
}

void print_selected()
{
    printf("selected : { ");
    for(int i = 0; i < TURN; i++)
    {
        printf("%3d ", selected[i]);
    }
    printf("}\n");
}

void input()
{
    for(int i = 0; i < TURN; i++)
    {
        int dice; cin >> dice;
        dices[i] = dice;
    }

    for(int i = 0; i <= 50; i++)
        Map[i] = vector<vector<int>>(2);

    // red line
    Map[1][0] = {2,4,6,8,10};
    for(int i = 2; i <= 40; i+=2)
    {
        int idx = 0;
        vector<int> tmp(5,0);
        for(int j = 2; j <= 10; j+= 2)
            tmp[idx++] = i+j;
        if(i == 30)
            Map[i][1] = {28,27,26,25,0};
        else
            Map[i][0] = tmp;
    }

    // blue line
    Map[10][1] = {13,16,19,25,0};
    Map[13][1] = {16,19,25,0,35};
    Map[16][1] = {19,25,0,35,40};
    Map[19][1] = {25,0,35,40,41};
    Map[20][1] = {22,24,25,0,35};
    Map[22][1] = {24,25,0,35,40};
    Map[24][1] = {25,0,35,40,41};
    Map[25][1] = {0,35,40,41,42};
    Map[26][1] = {25,0,35,40,41};
    Map[27][1] = {26,25,0,35,40};
    Map[28][1] = {27,26,25,0,35};
    Map[ 0][1] = {35,40,41,42,43}; // 30
    Map[35][1] = {40,41,42,43,44};
    Map[40][1] = {41,42,43,44,45};
}

void solve(int cnt)
{
    if(cnt == TURN)
    {
        for(int i = 0; i < 4; i++)
            units[i] = {1,0,false};

        int sum = 0;
        for(int turn = 0; turn < TURN; turn++)
        {
            int idx = selected[turn];
            int dice = dices[turn];
            int pos = units[idx].pos,next_pos;
            vector<int> v = Map[pos][0];

            if(units[idx].pos >= DESTINATION)
                return;
            if(pos == 10 || pos == 20 || pos == 30)
                units[idx].blue = true;
            if(units[idx].blue)
                v = Map[pos][1];
            
            next_pos = v[dice-1];
            if(next_pos >= DESTINATION)
            {
                units[idx].pos = DESTINATION;
                continue;
            }
            
            for(int i = 0; next_pos < DESTINATION && i < 4; i++)
            {
                if(idx == i)
                    continue;
                if(next_pos == units[i].pos)
                {
                    if(next_pos == 40)
                        return;
                    if(units[idx].blue == units[i].blue)
                        return;
                }
            }
            
            units[idx].pos = next_pos;
            if(next_pos == 0)
                units[idx].score += 30;
            else
                units[idx].score += next_pos;
        }

        for(int i = 0; i < 4; i++)
            sum += units[i].score;
        
        result = max(result,sum);
        return;
    }

    for(int i = 0; i < 4; i++)
    {
        selected[cnt] = i;
        solve(cnt+1);
    }
}

int main(int argc,char* argv[])
{
    input();
    //print_map();
    solve(0);

    cout << result << endl;
    return 0;
}
