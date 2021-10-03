#include <cmath>
#include <vector>
#include <iostream>

typedef long long ll;

using namespace std;

long long mod = 1000000007;

class SegTree
{
private:
    vector<ll> v;
    vector<ll> nodes;
    
public:
    SegTree(vector<ll> init)
    {
        int height = ceil(log2((int)init.size()));
        int size = (1 << (height+1));
        v = init;
        nodes = vector<ll>(size,0);
        makeTree(1,0,(int)init.size()-1);
    }
    
    ll makeTree(int cur,int left,int right)
    {
        if(left == right)
            return nodes[cur] = v[left]%mod;
        
        int mid = (left+right)/2;
        ll left_result = makeTree(cur*2,left,mid);
        ll right_result = makeTree(cur*2+1,mid+1,right);
        
        nodes[cur] = (left_result * right_result)%mod;
        return nodes[cur];
    }
    
    ll update(int cur,int left,int right,int idx,ll change)
    {
        if(idx < left || idx > right)
            return nodes[cur];
        if(left == right)
            return nodes[cur] = change;
        
        int mid = (left+right)/2;
        ll left_result = update(cur*2,left,mid,idx,change);
        ll right_result = update(cur*2+1,mid+1,right,idx,change);
        nodes[cur] = (left_result*right_result)%mod;
        
        return nodes[cur];
    }
    
    ll getMulti(int cur,int start,ll end,int left,int right) // [start,end] : 찾는 범위 , [left,right] : 현재 탐색 중인 범위
    {
        if(start > right || end < left)
            return 1;
        if(start <= left && end >= right)
            return nodes[cur];
        
        int mid = (left+right)/2;
        ll left_result = getMulti(cur*2, start, end, left, mid);
        ll right_result = getMulti(cur*2+1, start, end, mid+1, right);
        
        return (left_result*right_result)%mod;
    }
};

int N,M,K;
vector<ll> input;

int main(int argc,char* argv[])
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    
    SegTree* root;
    
    cin >> N >> M >> K;
    for(int i = 0; i < N; i++)
    {
        ll tmp; cin >> tmp;
        input.push_back(tmp);
    }
    
    root = new SegTree(input);
    
    for(int i = 0; i < M+K; i++)
    {
        int a,b; ll c;
        cin >> a >> b >> c;
        
        if(a == 1)
        {
            root->update(1,0,N-1,b-1,c);
        }
        else if(a == 2)
        {
            cout << root->getMulti(1,b-1,c-1,0,N-1)%mod << '\n';
        }
    }
    
    delete root;
    return 0;
}
