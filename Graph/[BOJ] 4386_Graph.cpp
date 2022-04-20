#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <queue>
#include <unordered_set>

using namespace std;
const double INF = 987654321;

int N;
vector<pair<double, double>> stars;

void input()
{
    scanf("%d", &N);
    for(int i = 0; i < N; i++)
    {
        double x, y;
        scanf("%lf%lf", &x, &y);
        stars.push_back({x, y});
    }
}

double solve() // MST 만들면 됨
{
    unordered_set<int> visit;
    double result = 0;
    
    if(N < 1) return 0;
    
    visit.insert(0); // 첫 번째 정점부터 출발
    while(visit.size() != N)
    {
        int target = -1;
        double dist = INF;
        
        for(int i = 0; i < N; i++)
        {
            if(visit.find(i) != visit.end()) continue; // 이미 연결된 상태
            
            for(const auto& ele : visit)
            {
                double x = stars[ele].first;
                double y = stars[ele].second;
                
                double tx = stars[i].first;
                double ty = stars[i].second;
                
                double tmp = sqrt((tx-x)*(tx-x)+(ty-y)*(ty-y));
                
                if(dist > tmp)
                {
                    dist = tmp;
                    target = i;
                }
            }
        }
        
        visit.insert(target);
        result += dist;
    }
    
    return result;
}

int main(int argc, char* argv[])
{
    input();
    printf("%.2lf\n", solve());
    return 0;
}
