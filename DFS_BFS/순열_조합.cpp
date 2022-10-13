#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

vector<int> v(3), check(4);

void print(int depth)
{
    for(int i = 0; i < depth; i++)
            cout << v[i] << " ";
    cout << "\n";
}

void permutation(int depth)
{
    if(depth == 3)
    {
        print(depth);
        return;
    }
    
    for(int i = 1; i <= 4; i++)
    {
        if(check[i]) continue;
        
        check[i] = 1;
        v[depth] = i;
        permutation(depth+1);
        check[i] = 0;
    }
}

void dupPermutation(int depth)
{
    if(depth == 3)
    {
        print(depth);
        return;
    }
    
    for(int i = 1; i <= 4; i++)
    {
        v[depth] = i;
        dupPermutation(depth+1);
    }
}

void combination(int depth, int cur)
{
    if(depth == 3)
    {
        print(depth);
        return;
    }
    
    for(int i = cur; i <= 4; i++)
    {
        v[depth] = i;
        combination(depth+1, i+1);
    }
}

void dupCombination(int depth, int cur)
{
    if(depth == 3)
    {
        print(depth);
        return;
    }
    
    for(int i = cur; i <= 4; i++)
    {
        v[depth] = i;
        dupCombination(depth+1, i);
    }
}

int main(int argc, char* argv[])
{
    permutation(0);
    cout << "----------------" << endl;
    dupPermutation(0);
    cout << "----------------" << endl;
    combination(0, 1);
    cout << "----------------" << endl;
    dupCombination(0, 1);
    return 0;
}
