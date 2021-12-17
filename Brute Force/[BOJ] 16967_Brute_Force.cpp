#include <array>
#include <iostream>

int H,W,X,Y;
std::array<std::array<int,1024>,1024> A({0}),B({0});

bool rangeA(int i,int j)
{
    if((0 <= i && i < H) && (0 <= j && j < W))
        return true;
    return false;
}

bool rangeB(int i,int j)
{
    if((X <= i && i < H+X) && (Y <= j && j < W+Y))
        return true;
    return false;
}

void input()
{
    std::cin >> H >> W >> X >> Y;
    for(int i = 0; i < H+X; i++)
    {
        for(int j = 0; j < W+Y; j++)
        {
            std::cin >> B[i][j];
        }
    }
}

void print()
{
    for(int i = 0; i < H; i++)
    {
        for(int j = 0; j < W; j++)
        {
            std::cout << A[i][j] << ' ';
        }
        std::cout << '\n';
    }
}

int get_case(int i,int j)
{
    // case 1
    if(!rangeA(i,j) && !rangeB(i,j))
        return 1;
    // case 2
    else if(rangeA(i,j) && rangeB(i,j))
        return 2;
    // case 3
    return 3;
    
}

void solve()
{
    for(int i = 0; i < H+X; i++)
    {
        for(int j = 0; j < W+Y; j++)
        {
            int Case = get_case(i,j);
            
            if(Case == 1)
                continue;
            else if(Case == 2)
            {
                // B[i][j] = A[i][j] + A[i-X][j-Y];
                A[i][j] = B[i][j]-A[i-X][j-Y];
            }
            else
            {
                // B[i][j] = A[i][j] or A[i-X][j-Y]
                if(i < H || j < W)
                    A[i][j] = B[i][j];
                else
                    A[i-X][j-Y] = B[i][j];
            }
        }
    }
}

int main(int argc,char* argv[])
{
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    
    input();
    
    solve();
    
    print();
    return 0;
}
