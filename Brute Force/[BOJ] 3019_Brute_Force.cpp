//#include <iostream>
//#include <vector>
//
//using namespace std;
//
//int N,block,ans = 0;
//bool Map[128][128] = {0,};
//vector<int> height;
//vector<pair<int,int>> blocks[7][4];
//
//inline bool range(int y,int x) { return ((0 <= y && y < 128) && (0 <= x && x < N));}
//
//void make_block(void)
//{
//    // case 1
//    blocks[0][0] = {{0,0},{1,0},{2,0},{3,0}}; // {y,x}
//    blocks[0][1] = {{0,0},{0,1},{0,2},{0,3}};
//    //blocks[0][2] = blocks[0][0]; blocks[0][3] = blocks[0][1];
//
//    // case 2
//    blocks[1][0] = {{0,0},{0,1},{1,0},{1,1}};
//    //blocks[1][1] = blocks[1][2] = blocks[1][3] = blocks[1][0];
//
//    // case 3
//    blocks[2][0] = {{0,0},{0,1},{-1,1},{-1,2}};
//    blocks[2][1] = {{0,0},{-1,0},{-1,-1},{-2,-1}};
//    //blocks[2][2] = blocks[2][0]; blocks[2][3] = blocks[2][1];
//
//    // case 4
//    blocks[3][0] = {{0,0},{0,1},{1,1},{1,2}};
//    blocks[3][1] = {{0,0},{1,0},{1,-1},{2,-1}};
//    //blocks[3][2] = blocks[3][0]; blocks[3][3] = blocks[3][1];
//
//    // case 5
//    blocks[4][0] = {{0,0},{1,-1},{1,0},{1,1}};
//    blocks[4][1] = {{0,0},{-1,-1},{0,-1},{1,-1}};
//    blocks[4][2] = {{0,0},{-1,1},{-1,0},{-1,-1}};
//    blocks[4][3] = {{0,0},{1,1},{0,1},{-1,1}};
//
//    // case 6
//    blocks[5][0] = {{0,0},{0,1},{0,2},{-1,2}};
//    blocks[5][1] = {{0,0},{1,0},{2,0},{2,1}};
//    blocks[5][2] = {{0,0},{0,-1},{0,-2},{1,-2}};
//    blocks[5][3] = {{0,0},{-1,0},{-2,0},{-2,-1}};
//
//    // case 7
//    blocks[6][0] = {{0,0},{1,0},{1,1},{1,2}};
//    blocks[6][1] = {{0,0},{0,-1},{1,-1},{2,-1}};
//    blocks[6][2] = {{0,0},{-1,0},{-1,-1},{-1,-2}};
//    blocks[6][3] = {{0,0},{0,1},{-1,1},{-2,1}};
//}
//
//vector<pair<int,int>> get_min(vector<pair<int,int>> v)
//{
//    vector<pair<int,int>> ret[128],result;
//
//    for(int i = 0; i < v.size(); i++)
//    {
//        int y = v[i].first,x = v[i].second;
//
//        if(ret[x].size() <= 0)
//            ret[x].push_back(v[i]);
//        else
//        {
//            pair<int,int> prev = ret[x][0];
//
//            if(prev.first > y)
//                ret[x][0] = v[i];
//        }
//    }
//
//    for(int i = 0; i < N; i++)
//        if(ret[i].size() > 0)
//            result.push_back(ret[i][0]);
//
//    return result;
//}
//
//void solve()
//{
//    for(int col = 0; col < N; col++)
//    {
//        int row = height[col];
//
//        for(; row < height[col]+5; row++)
//        {
//            for(int i = 0; i < 4 && blocks[block-1][i].size() > 0 ; i++)
//            {
//                bool check = true;
//                vector<pair<int,int>> b = blocks[block-1][i],pos;
//                for(int j = 0; j < b.size(); j++)
//                {
//                    int y = b[j].first+row,x = b[j].second+col;
//
//                    if(!range(y,x) || Map[y][x])
//                        break;
//                    pos.push_back({y,x});
//                }
//
//                if(pos.size() >= 4)
//                {
//                    vector<pair<int,int>> minimize = get_min(pos);
//
//                    for(int j = 0; j < minimize.size(); j++)
//                    {
//                        int y = minimize[j].first,x = minimize[j].second;
//
//                        if(height[x] < y)
//                        {
//                            check = false;
//                            break;
//                        }
//                    }
//
//                    if(check)
//                        ans++;
//                }
//            }
//        }
//    }
//}
//
//void input()
//{
//    cin >> N >> block;
//    for(int i = 0; i < N; i++)
//    {
//        int tmp; cin >> tmp;
//        for(int j = 0; j < tmp; j++)
//            Map[j][i] = true;
//        height.push_back(tmp);
//    }
//}
//
//int main(int argc,char* argv[])
//{
//    input();
//    make_block();
//    solve();
//
//    cout << ans << '\n';
//    return 0;
//}

#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
 
using namespace std;
 
#define Max 105
 
int m[Max], c, p;
vector<string> v;
 
int simulation(int number)
{
    int ret = 0;
 
    if (number == 1) {
        v.push_back("0");
        v.push_back("0000");
    }
    else if (number == 2) {
        v.push_back("00");
    }
    else if (number == 3) {
        v.push_back("001");
        v.push_back("10");
    }
    else if (number == 4) {
        v.push_back("100");
        v.push_back("01");
    }
    else if (number == 5) {
        v.push_back("000");
        v.push_back("01");
        v.push_back("101");
        v.push_back("10");
    }
    else if (number == 6) {
        v.push_back("000");
        v.push_back("00");
        v.push_back("011");
        v.push_back("20");
    }
    else if (number == 7) {
        v.push_back("000");
        v.push_back("02");
        v.push_back("110");
        v.push_back("00");
    }
 
    for (int i = 0; i < v.size(); i++) {
        int len = v[i].length();
 
        vector<int> temp;
        for (auto k : v[i]) {
            temp.push_back(k - '0');
        }
 
        for (int j = 0; j + len <= c; j++) {
            bool calc = true;
 
            for (int k = j + 1; k < j + len; k++) {
                if (m[k] - m[k - 1] != temp[k - j] - temp[k - j - 1]) {
                    calc = false;
                    break;
                }
            }
            if (calc) {
                ++ret;
            }
        }
    }
 
    return ret;
}
 
int main()
{
    cin.tie(0);
    scanf("%d %d", &c, &p);
 
    for (int i = 0; i < c; i++) {
        scanf("%d", &m[i]);
    }
    
    printf("%d\n", simulation(p));
    
    return 0;
}
