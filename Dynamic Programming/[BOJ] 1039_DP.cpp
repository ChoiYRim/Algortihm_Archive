#include <string>
#include <cstring>
#include <iostream>

#define MAX(a,b) (a > b ? a : b)

int N,K;
std::string num = "";
int visit[11][1000001];

int DFS(int level,std::string str)
{
    if(level >= K)
        return std::stoi(str);

    int idx = std::stoi(str);

    if(visit[level][idx] >= 0)
        return visit[level][idx];

    for(int i = 0; i < (int)str.length(); i++)
    {
        for(int j = i+1; j < (int)str.length(); j++)
        {
            if(i == 0 && str[j]-'0' == 0)
                continue;

            std::swap(str[i],str[j]);
            visit[level][idx] = MAX(visit[level][idx],DFS(level+1,str));
            std::swap(str[i],str[j]);
        }
    }

    return visit[level][idx];
}

int main(int argc,char* argv[])
{
    std::cin >> N >> K;

    num = std::to_string(N);
    memset((int *)visit,-1,sizeof(visit));
    std::cout << DFS(0,num) << '\n';
    return 0;
}
