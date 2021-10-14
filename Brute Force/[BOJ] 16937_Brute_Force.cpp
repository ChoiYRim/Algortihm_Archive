#include <vector>
#include <iostream>

using namespace std;

struct Square
{
    int y;
    int x;
    int extent;
};

vector<Square> v;
int N,H,W,ans = 0;

inline bool range(int y,int x) { return ((0 <= y && y <= H) && (0 <= x && x <= W)); }

inline int MAX(int a,int b) { return (a > b ? a : b); }

void compare(int idx,int y1,int x1)
{
    for(int j = idx+1; j < (int)v.size(); j++)
    {
        int case1,case2,case3;
        int y2 = v[j].y,x2 = v[j].x;
        
        case1 = case2 = case3 = 0;
        
        // case 1 : 1번 스티커와 2번 스티커를 횡렬로 이어 붙였을 때
        if(range(MAX(y1,y2),x1+x2))
            case1 = v[idx].extent+v[j].extent;
        
        // case 2 : 1번 스티커와 2번 스티커를 종렬로 이어 붙였을 때
        if(range(y1+y2,MAX(x1,x2)))
            case2 = v[idx].extent+v[j].extent;
        
        // case 3 : 1번 스티커와 2번 스티커를 대각선 꼭지점을 기준으로 이어 붙였을 때
        if(range(y1+y2,x1+x2))
            case3 = v[idx].extent+v[j].extent;
        
        ans = MAX(ans,MAX(case1,MAX(case2,case3)));
        
        swap(y2,x2); // 2번 스티커 90도 회전
        
        case1 = case2 = case3 = 0;
        
        // case 1
        if(range(MAX(y1,y2),x1+x2))
            case1 = v[idx].extent+v[j].extent;
        
        // case 2
        if(range(y1+y2,MAX(x1,x2)))
            case2 = v[idx].extent+v[j].extent;
        
        // case 3
        if(range(y1+y2,x1+x2))
            case3 = v[idx].extent+v[j].extent;
        
        ans = MAX(ans,MAX(case1,MAX(case2,case3)));
    }
}

int main(int argc,char* argv[])
{
    cin >> H >> W;
    cin >> N;
    for(int i = 0; i < N; i++)
    {
        int r,c; cin >> r >> c;
        v.push_back({r,c,r*c});
    }
    
    for(int i = 0; i < (int)v.size()-1; i++)
    {
        int y1 = v[i].y,x1 = v[i].x;
        
        compare(i,y1,x1);
        swap(y1,x1); // 1번 스티커 90도 회전
        compare(i,y1,x1);
    }
    
    cout << ans << '\n';
    return 0;
}
