/*
Problem:the attack and the defense between Ciel and Duel
Algorithm 1:Greedy
We can divide the result into 2 aspects:
One is that Ciel can kill all the cards in Duel including the defense cards,so
Ciel can choose the leastest strength card each time to kill the current defense card
of Duel,we should sort at the first time of course.
The second is that we cannot kill all the cards of Duel.We will enum the k-num of the number that
Ciel use to kill the Attack cards of Duel.And in this method,the k - cards in Ciel is the strongest strength
and the k-cards of Duel is the leastest strength.
Finally,we compare the two parts.Both of the two part use the greedy algorithm.
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

#define Maxn 105
#define Maxm 950005
#define INF 1<<30

struct Ciel
{
    int val;
    bool operator < (const Ciel &a) const
    {
        return val < a.val;
    }
}ciel[Maxn];

struct Jiro
{
    char op[10];
    int val;
    bool operator < (const Jiro &a)const
    {
        return op[0] < a.op[0] || (op[0] == a.op[0] && val < a.val);
    }
}jiro[Maxn];

int visC[Maxn];

int main()
{
    #ifndef ONLINE_JUDGE
        freopen("in.txt","r",stdin);
    #endif
    int n,m;
    int natk;
    while(scanf(" %d %d",&n,&m)!=EOF)
    {
        natk = 0;
        for(int i=0;i<n;i++)
        {
            scanf(" %s %d",jiro[i].op,&jiro[i].val);
            if(jiro[i].op[0] == 'A') natk++;
        }
        for(int i=0;i<m;i++)
        {
            scanf(" %d",&ciel[i].val);   
        }
        sort(ciel,ciel+m);
        sort(jiro,jiro+n);
        
        memset(visC,0,sizeof(visC));

        int ans = 0;
        //能全部消灭
        if(m >= n)
        {
            int j = 0;
            int tot = 0;
            //依次找到最小的能消灭def属性的点
            for(int i=natk;i<n;i++)
            {
                while(ciel[j].val <= jiro[i].val || visC[j]) j++;
                if(j<m) visC[j] = 1;
            }
            if(j<m)
            {
                j = 0;
                for(int i=0;i<natk;i++)
                {
                    while(ciel[j].val < jiro[i].val || visC[j]) j++;
                    if(j<m)
                    {
                        tot += ciel[j].val - jiro[i].val;
                        visC[j] = 1;
                    }
                }
                if(j < m)
                {
                    for(int i=0;i<m;i++)
                    {
                        if(!visC[i]) tot += ciel[i].val;
                    }
                    ans = max(ans,tot);
                }
            }
        }
        //不能消灭全部卡片
        //求出最多能消灭的卡片数
        for(int k =1;k<=natk && k<=m;k++)
        {
            int tot = 0;
            int flag = 0;
            for(int i=0;i<k;i++)
            {
                if(ciel[m-k+i].val >= jiro[i].val)
                {
                    tot += ciel[m-k+i].val - jiro[i].val;
                }
                else
                {
                    flag = 1;
                    break;
                }
            }
            if(flag == 1) break;
            ans = max(ans,tot);
        }
        printf("%d\n",ans);
    }
    return 0;
}
