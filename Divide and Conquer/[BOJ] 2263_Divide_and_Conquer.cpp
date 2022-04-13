#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int N;
vector<int> in,post,idx;

void input()
{
    cin >> N;
    
    in = vector<int>(N+1);
    post = vector<int>(N+1);
    idx = vector<int>(N+1);
    
    for(int i = 1; i <= N; i++)
    {
        cin >> in[i];
        idx[in[i]] = i;
    }
    for(int i = 1; i <= N; i++)
        cin >> post[i];
}

void preorder(int iLeft, int iRight, int pLeft, int pRight)
{
    if(iLeft > iRight || pLeft > pRight) return;
    
    int parent = post[pRight];
    int i = idx[parent];
    
    cout << parent << " ";
    
    // inorder left : in_left ~ i-1 / inorder right : i+1 ~ in_right
    // postorder left : post_left ~ j: post_left+(i-1-in_left)-1 / postorder right : j+1 ~ post_right-1
    
    preorder(iLeft, i-1, pLeft, pLeft+i-iLeft-1);
    preorder(i+1, iRight, pLeft+i-iLeft, pRight-1);
}

int main(int argc, char* argv[])
{
    input();
    preorder(1, N, 1, N);
    return 0;
}
