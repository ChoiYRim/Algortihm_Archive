#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;
using ll = long long;

int N;
ll B;
vector<vector<ll>> set[39]; // 2의 거듭제곱 행렬들
vector<vector<ll>> mat;
string binary = "";

vector<vector<ll>> product(vector<vector<ll>>& mat1,vector<vector<ll>>& mat2)
{
    vector<vector<ll>> mat1_cols; // [[1 3] [2 4]]
    vector<vector<ll>> ret(N,vector<ll>(N,0));
    
    for(int col = 0; col < N; col++)
    {
        vector<ll> tmp;
        for(int row = 0; row < N; row++)
            tmp.push_back(mat1[row][col]);
        mat1_cols.push_back(tmp);
    }
    
    for(int col = 0; col < N; col++)
    {
        for(int row = 0; row < N; row++)
        {
            ll ele = mat2[row][col];
            auto v = mat1_cols[row];
            for(int i = 0; i < v.size(); i++) // [1 3]
                ret[i][col] += (v[i]*ele)%1000;
        }
    }
    
    return ret;
}

void make_binary()
{
    ll b = B;
    while(b > 0)
    {
        binary.push_back(b%2+'0');
        b /= 2;
    }
}

void init()
{
    scanf("%d%lld", &N, &B);
    mat = vector<vector<ll>>(N,vector<ll>(N,0));
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
            scanf("%lld", &mat[i][j]);
    }
    
    set[0] = mat;
    for(int i = 1; i <= 38; i++)
    {
        auto v = product(set[i-1],set[i-1]);
        set[i] = v;
    }
    
    make_binary();
}

void print()
{
    vector<vector<ll>> result;
    
    for(int i = 0; i < binary.length(); i++)
    {
        if(binary[i] != '0')
        {
            if(result.size() <= 0)
                result = set[i];
            else
                result = product(result,set[i]);
        }
    }
    
    for(int row = 0; row < N; row++)
    {
        for(int col = 0; col < N; col++)
            printf("%lld ", result[row][col]%1000);
        printf("\n");
    }
}

int main(int argc,char* argv[])
{
    init();
    print();
    return 0;
}
