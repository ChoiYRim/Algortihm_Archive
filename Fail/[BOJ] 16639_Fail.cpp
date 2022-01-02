#include <string>
#include <iostream>

using namespace std;

typedef long long ll;

int n;
string str;
ll ans = 0;
bool visit[16] = {0,};

inline ll MAX(ll a,ll b) { return (a > b ? a : b); }

inline bool is_operator(char ch) { return (ch == '+' || ch == '-' || ch == '*'); }

inline bool is_num(char ch) { return (ch >= '0' && ch <= '9'); }

int convert_index(char ch)
{
    if(ch >= 62 && ch < 73) // *
        return ch-62;
    else if(ch >= 73 && ch < 85) // +
        return ch-73;
    return ch-85; // -
}

char convert_operator(char ch)
{
    if(ch >= 62 && ch < 73) // *
        return '*';
    else if(ch >= 73 && ch < 85) // +
        return '+';
    return '-'; // -
}

string result(string front,string rear,char op)
{
    if(front.length() <= 0)
        front = "0";
    if(rear.length() <= 0)
        rear = "0";
    
    ll lfront = stoll(front),lrear = stoll(rear);
    ll ret = 0;
    
    switch(op)
    {
        case '+':
            ret = lfront+lrear;
            break;
        case '-':
            ret = lfront-lrear;
            break;
        case '*':
            ret = lfront*lrear;
            break;
        default:
            return "";
    }
    
    return to_string(ret);
}

void dfs(int depth,string cur)
{
    if(depth <= 0)
    {
        ans = MAX(ans,stoll(cur));
        return;
    }
    
    for(int i = 0; i < (int)cur.length(); i++)
    {
        if(!is_num(cur[i]))
        {
            int oidx = convert_index(cur[i]);
            
            if(!visit[oidx])
            {
                visit[oidx] = true;
                
                int fidx = 0,ridx = 0;
                string next = "";
                string front = "",rear = "",frest = "",rrest = "";
                
                // front
                for(int j = i-1; j >= 0 && cur[j] < 62; j--)
                {
                    front = cur[j] + front;
                    fidx = j;
                }
                frest = cur.substr(0,fidx);
                
                // rear
                for(int j = i+1; j < (int)cur.length() && cur[j] < 62; j++)
                {
                    rear += cur[j];
                    ridx = j;
                }
                rrest = cur.substr(ridx+1,cur.length());
                
                next = frest + result(front, rear, convert_operator(cur[i])) + rrest;
                dfs(depth-1,next);
                
                visit[oidx] = false;
            }
        }
    }
}

int main()
{
    int order = 0;
    
    cin >> n;
    cin >> str;
    for(int i = 0; i < (int)str.length(); i++)
    {
        if(is_operator(str[i]))
        {
            if(str[i] == '*')
                str[i] += (order++ + 20);
            else if(str[i] == '+')
                str[i] += (order++ + 30);
            else
                str[i] += (order++ + 40);
        }
    }
    
    dfs(n/2,str);
    
    cout << ans << '\n';
    return 0;
}
