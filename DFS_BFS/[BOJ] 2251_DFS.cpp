#include <iostream>

using namespace std;

int A,B,C;
bool visit[256][256][256] = {0,};
bool result[256] = {0,};

inline int remain(int first,int second) { return ((first > second ? second : first)); }

inline bool range(int cup,int limit) { return (0 <= cup && cup <= limit); }

void DFS(int a,int b,int c)
{
    if(!range(a,A) || !range(b,B) || !range(c,C))
        return;
    if(result[c] || visit[a][b][c])
        return;
    
    visit[a][b][c] = true;
    
    int ab = remain(a,B-b);
    int ac = remain(a,C-c);
    int ba = remain(b,A-a);
    int bc = remain(b,C-c);
    int ca = remain(c,A-a);
    int cb = remain(c,B-b);
    
    // A to B
    DFS(a-ab,b+ab,c);
    // A to C
    DFS(a-ac,b,c+ac);
    
    // B to A
    DFS(a+ba,b-ba,c);
    // B to C
    DFS(a,b-bc,c+bc);
    
    // C to A
    DFS(a+ca,b,c-ca);
    // C to B
    DFS(a,b+cb,c-cb);
    
    if(!a)
        result[c] = true;
}

void output()
{
    for(int i = 0; i <= 200; i++)
    {
        if(result[i])
            cout << i << ' ';
    }
    cout << '\n';
}

int main()
{
    cin >> A >> B >> C;
    
    DFS(remain(A,C),0,C-remain(A,C));
    DFS(0,remain(B,C),C-remain(B,C));
    output();
    return 0;
}
