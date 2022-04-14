#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;
using ll = long long;

ll N,K,Q;

ll get_parent(ll node)
{
    if(node%K < 2) return node/K;
    return node/K+1;
}

int get_depth(ll node)
{
    int depth = 0;
    
    while(node != 1)
    {
        depth++;
        node = get_parent(node);
    }
    
    return depth;
}

void solve()
{
    cin >> N >> K >> Q;
    for(int i = 0; i < Q; i++)
    {
        ll dist = 0,from, to;
        
        scanf("%lld%lld", &from, &to);
        
        if(from > to) swap(from,to);
                
        if(K == 1)
        {
            printf("%lld\n", to-from);
            continue;
        }
        
        int from_depth = get_depth(from);
        int to_depth = get_depth(to);
        
        while(from_depth != to_depth)
        {
            to = get_parent(to);
            dist++;
            to_depth--;
        }
        
        while(from != to)
        {
            from = get_parent(from);
            to = get_parent(to);
            dist += 2;
        }
        
        printf("%lld\n", dist);
    }
}

int main(int argc, char* argv[])
{
    solve();
    return 0;
}
