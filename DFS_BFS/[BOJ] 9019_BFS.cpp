#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <queue>

using namespace std;

struct Str
{
    int a;
    string cmd;
};

int T;
int A,B;
vector<string> result;
bool visit[10010];

string DSLR = "DSLR";
int (*func[4])(int);

int D(int a)
{
    if(a*2 > 9999)
        return (a*2)%10000;
    return a*2;
}

int S(int a)
{
    if(!a)
        return a=9999;
    return a-1;
}

int L(int a)
{
    int first = a/1000;
    a = (a%1000) * 10 + first;
    return a;
}

int R(int a)
{
    int last = (a%10) * 1000;
    a = (a/10)+last;
    return a;
}

int main()
{
    cin >> T;
    func[0] = D; func[1] = S; func[2] = L; func[3] = R;
    result = vector<string>(T,"");
    for(int i = 0; i < T; i++)
    {
        memset((bool*)visit,false,sizeof(visit));
        
        queue<Str> q;
        
        cin >> A >> B;
        
        q.push({A,""});
        while(!q.empty())
        {
            Str cur = q.front();
            q.pop();
            
            int a = cur.a;
            string cmd = cur.cmd;
            
            if(a == B)
            {
                result[i] = cmd;
                break;
            }
            
            for(int j = 0; j < 4; j++)
            {
                int newA = func[j](a);
                
                if((0 <= newA && newA < 10000) && !visit[newA])
                {
                    visit[newA] = true;
                    q.push({newA,cmd+DSLR[j]});
                }
            }
        }
    }
    
    for(int i = 0; i < (int)result.size(); i++)
        cout << result[i] << '\n';
    return 0;
}
