#include <queue>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>

using namespace std;
const int kMax = 987654321;

struct Edge
{
    string type;
    int cost;
};

int N, R, M, K;
vector<string> target;
unordered_set<string> Free, Half;
unordered_map<string, int> m;
vector<vector<vector<Edge>>> edges;
vector<vector<double>> norm, rail;

void input()
{
    cin >> N >> R;
    edges = vector<vector<vector<Edge>>>(N, vector<vector<Edge>>(N));
    for(int i = 0; i < N; i++)
    {
        string city; cin >> city;
        m.insert({city, i});
    }
    cin >> M;
    for(int i = 0; i < M; i++)
    {
        string city; cin >> city;
        target.push_back(city);
    }
    cin >> K;
    for(int i = 0; i < K; i++)
    {
        string type, from, to;
        int cost;
        
        cin >> type >> from >> to >> cost;
        edges[m[from]][m[to]].push_back({type, cost});
    }
    
    Free = {"Mugunghwa", "ITX-Saemaeul", "ITX-Cheongchun"};
    Half = {"S-Train", "V-Train"};
}

void floyd_warshall()
{
    norm = vector<vector<double>>(N, vector<double>(N, kMax));
    rail = vector<vector<double>>(N, vector<double>(N, kMax));
    
    int city_len = static_cast<int>(m.size());
    
    // init
    for(int from = 0; from < city_len; from++)
    {
        for(int to = 0; to < city_len; to++)
        {
            if(from == to) continue;
            
            for(int i = 0; i < edges[from][to].size(); i++)
            {
                string type = edges[from][to][i].type;
                double cost = static_cast<double>(edges[from][to][i].cost);
                
                norm[from][to] = min(norm[from][to], cost);
                norm[to][from] = min(norm[to][from], cost);
                
                if(Free.find(type) != Free.end())
                {
                    rail[from][to] = 0;
                    rail[to][from] = 0;
                }
                else if(Half.find(type) != Half.end())
                {
                    rail[from][to] = min(rail[from][to], cost/2);
                    rail[to][from] = min(rail[to][from], cost/2);
                }
                else
                {
                    rail[from][to] = min(rail[from][to], cost);
                    rail[to][from] = min(rail[to][from], cost);
                }
            }
        }
    }
    
    // floyd warshall
    for(int mid = 0; mid < city_len; mid++)
    {
        for(int from = 0; from < city_len; from++)
        {
            for(int to = 0; to < city_len; to++)
            {
                norm[from][to] = min(norm[from][to], norm[from][mid]+norm[mid][to]);
                rail[from][to] = min(rail[from][to], rail[from][mid]+rail[mid][to]);
            }
        }
    }
}

string solve()
{
    int len = static_cast<int>(target.size());
    double on = 0, off = 0;
    
    floyd_warshall();
    
    for(int i = 0; i < len-1; i++)
    {
        int from = m[target[i]];
        int to = m[target[i+1]];
        
        on += rail[from][to];
        off += norm[from][to];
    }
    
    return (on+R < off ? "Yes" : "No");
}

int main(int argc, char* argv[])
{
    input();
    cout << solve() << endl;
    return 0;
}

