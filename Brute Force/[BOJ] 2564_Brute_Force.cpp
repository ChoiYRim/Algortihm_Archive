#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int n, m;
int width, height, N;

vector<pair<int, int>> v;

int main(int argc, char* argv[])
{
    cin >> width >> height;
    cin >> N;
    
    while(N >= 0)
    {
        int dir, pos; cin >> dir >> pos;
        
        if(dir == 2) pos = width + height + (width - pos);
        else if(dir == 3) pos = 2 * width + height + (height - pos);
        else if(dir == 4) pos = width + pos;
        
        v.push_back({dir, pos});
        
        N--;
    }
    
    int cnt, result = 0;
    auto player = v.back();
    for(int i = 0; i < v.size()-1; i++)
    {
        cnt = abs(player.second-v[i].second);
        result += min(2*width+2*height-cnt, cnt);
    }
    
    cout << result << endl;
    return 0;
}
