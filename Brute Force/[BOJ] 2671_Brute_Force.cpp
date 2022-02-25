#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

// 잠수함 소리 : (100~1~|01)~
// 100~1~ 그리고 01을 임의로 섞어서 만들 수 있는 모든 스트링의 집합
// 100 .. 0 .. + 1 .. 1 ..| 01 .. 01 ..
// 1001 , 01

string sound = "";

string solve()
{
    int len = static_cast<int>(sound.length());
    int idx = 0;
    
    if(len < 2 || len > 150)
        return "NOISE";
    
    // 시작이 0이면 뒤에 무조건 1이 나와야 함
    
    // 시작이 1이면 뒤에 무조건 0이 나와야 함
    while(idx < len)
    {
        int num = sound[idx]-'0';
        
        if(num != 0) // 1로 시작 : 1000...1.. 문자열
        {
            if(idx+3 >= len)
                return "NOISE";
            
            if(sound[idx+1] != '0' || sound[idx+2] != '0')
                return "NOISE";
            
            idx += 3;
            while(sound[idx] == '0')
                idx++;
            if(idx >= len)
                return "NOISE";
            
            idx++;
            for(; idx < len && sound[idx] == '1'; idx++) // 1이 끝날 때까지 반복
            {
                if(idx+2 < len && sound[idx+1] == '0' && sound[idx+2] == '0')
                    break;
            }
            
            continue;
        }
        
        // 0으로 시작
        if(idx+1 >= len || sound[idx+1] != '1') // 바로 문자열이 끝나버리거나 뒤에 1이 없다면
            return "NOISE";
        idx += 2;
    }
    
    return "SUBMARINE";
}

int main(int argc,char* argv[])
{
    cin >> sound;
    cout << solve() << endl;
    return 0;
}
