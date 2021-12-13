#include <iostream>

using namespace std;

int T;
int money,price,cupons,fre;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    cin >> T;
    while(T--)
    {
        int s = 0,d = 0;
        int sc = 0,dc = 0;
        
        cin >> price >> money >> fre >> cupons;
        
        s = d = money / price; // 기본 개수
        sc = dc = money / price * cupons;
        d += dc / fre;
        
        if(sc >= fre) // 상언이의 쿠폰 개수가 공짜로 시킬 수 있는 개수 이상이라면
        {
            // sc += cupons를 해줌과 동시에 fre개만큼 빼야함
            // 즉, sc = sc - fre + cupons
            // sc에서 fre 개수만큼 빼준 값 ( 여기서 치킨 한 마리 더 먹은 것이니 + 1해주고)에서 fre - cupons를 나눠줌
            
            // [ ] [ ] [ ] [ ] [ ] : [ ] fre의 크기라 하자
            // sc 에서 fre만큼 빼줬으므로
            // [ ] [ ] [ ] [ ] 가 남았다.
            // 그런데 상언이는 공짜로 먹을 때마다 쿠폰을 받는다.
            // 그렇다면 상언이가 또 쿠폰으로 공짜로 먹으려면 모아야하는 개수는 fre - cupons (왜냐면 cupons는 이미 받았으니까)
            // 그러므로 (sc - fre ) / (fre - cupons)
            
            s += 1 + (sc - fre) / (fre - cupons);
        }
        cout << s - d << '\n';
    }
    
    return 0;
}
