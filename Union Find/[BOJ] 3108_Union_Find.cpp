#include <set>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

struct Node
{
    int y1;
    int x1;
    int y2;
    int x2;
};

int N,answer = 0;
vector<Node> nodes;
vector<int> parent;

int Find(int idx)
{
    if(parent[idx] == idx) return idx;
    return Find(parent[idx]);
}

void Union(int x, int y)
{
    int xp = Find(x);
    int yp = Find(y);
    
    if(xp < yp) parent[yp] = xp;
    else parent[xp] = yp;
}

bool cross(int i,int j)
{
    Node& n = nodes[i];
    Node& m = nodes[j];
    
    if(n.y2 < m.y2 && n.x2 < m.x2 && n.y1 > m.y1 && n.x1 > m.x1) return false;
    
    if(n.y2 > m.y2 && n.x2 > m.x2 && n.y1 < m.y1 && n.x1 < m.x1) return false;
    
    if(n.y1 > m.y2 || n.y2 < m.y1 || n.x1 > m.x2 || n.x2 < m.x1) return false;
    
    return true;
}

void input()
{
    cin >> N;
    parent = vector<int>(N+1);
    nodes = vector<Node>(N+1);
    
    for(int i = 0; i <= N; i++)
        parent[i] = i;
    
    nodes[0] = {500,500,500,500};
    for(int i = 1; i <= N; i++)
    {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        x1 += 500; x2 += 500;
        y1 += 500; y2 += 500;
        
        nodes[i] = {y1,x1,y2,x2};
    }
    
    for(int i = 0; i < N; i++)
    {
        for(int j = i+1; j <= N; j++)
        {
            if(cross(i,j))
                Union(i,j);
        }
    }
}

int count()
{
    int cnt;
    set<int> s;
    
    for(int i = 0; i <= N; i++)
        s.insert(Find(parent[i]));
    
    cnt = static_cast<int>(s.size()-1);
    return cnt;
}

int main(int argc, char* argv[])
{
    input();
    cout << count() << endl;
    return 0;
}
