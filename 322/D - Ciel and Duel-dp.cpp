/*
I just copy the code from cgy4ever.This is a very interesting method.
dp[pCard][pAtk][pDef][iskillAll] faces four choices:
1.Skip, this card don't attack.
2.Attack on the next ATK card.
3.Attack on the next DEF card.
4.Assume Jiro has no cards and make a direct attack.
We also use a method called memoried search.It is useful and important.
The code is clear and easy to understand.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stack>
#include <queue>
#include <algorithm>
#include <iostream>

using namespace std;
int n, m;
vector <int> atk;
vector <int> def;
vector <int> myCard;
int F[101][101][101][2];
int inf = 0x3f3f3f3f;

int f(int pMyCard, int pAtk, int pDef, int noCard)
{
    if(pMyCard == myCard.size())
    {
        if(noCard == false) return 0;
        if(noCard == true)
        {
            if(pAtk == atk.size() && pDef == def.size())
                return 0;
            return -inf;
        }
    }
    int &ret = F[pMyCard][pAtk][pDef][noCard];
    //记忆化搜索
    if(ret != -1) return ret;

    ret = -inf;

    // don't move
    ret = max(ret, f(pMyCard + 1, pAtk, pDef, noCard));

    // no monster
    ret = max(ret, f(pMyCard + 1, pAtk, pDef, true) + myCard[pMyCard]);

    // attack on ATK monster
    if(pAtk < atk.size() && myCard[pMyCard] >= atk[pAtk])
        ret = max(ret, f(pMyCard + 1, pAtk + 1, pDef, noCard) + myCard[pMyCard] - atk[pAtk]);

    // attack on DEF monster
    if(pDef < def.size() && myCard[pMyCard] > def[pDef])
        ret = max(ret, f(pMyCard + 1, pAtk, pDef + 1, noCard));

    return ret;
}

int main()
{
    #ifndef ONLINE_JUDGE
        freopen("in.txt","r",stdin);
    #endif
    while(cin >> n >> m)
    {
        atk.clear();
        def.clear();
        myCard.clear();
        for(int i = 1; i <= n; i++)
        {
            string type;
            int s;
            cin >> type >> s;
            if(type == "ATK")
                atk.push_back(s);
            else
                def.push_back(s);
        }
        for(int i = 1; i <= m; i++)
        {
            int s;
            cin >> s;
            myCard.push_back(s);
        }
        sort(atk.begin(), atk.end());
        sort(def.begin(), def.end());
        sort(myCard.begin(), myCard.end());
        memset(F, 0xff, sizeof(F));
        cout << f(0, 0, 0, 0) << endl;
    }
    return 0;
}
