#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stack>
#include <queue>
#include <algorithm>
#include <iostream>

using namespace std;

#define Maxn 200005
#define Maxm 950005
#define INF 1<<30
struct Edge
{
    int a,b;
    int w;
    int isC;
};

Edge edge[Maxm];
int first[Maxn];
int next[Maxm];
int vis[Maxm];
int total;
int flow[Maxn];
int n,m;

void init()
{
    total = 0;
    memset(first,-1,sizeof(first));
}
void addEdge(int a,int b,int w)
{
    flow[a] +=w,flow[b] += w;
    edge[total].a = a,edge[total].b = b,edge[total].w = w;
    edge[total].isC = 1;
    next[total] = first[a];
    first[a] = total++;

    edge[total].a = b,edge[total].b = a,edge[total].w = w;
    edge[total].isC = 1;
    next[total] = first[b];
    first[b] = total++;
}
void bfs()
{
    for(int i=1;i<=n;i++)
    {
        flow[i] /= 2;
    }
    memset(vis,0,sizeof(vis));
    queue<int> q;
    q.push(1);
    while(!q.empty())
    {
        int temp = q.front();
        q.pop();
        for(int i=first[temp];i!=-1;i=next[i])
        {
            if(vis[i] == 0)
            {
                Edge &e = edge[i];
                flow[e.b] -= e.w;
                vis[i] = vis[i^1] = 1;
                if(flow[e.b] == 0 && e.b!=n)
                {
                    q.push(e.b);
                    //printf("e.b = %d\n",e.b );
                }
                e.isC = 0;
            }
        }
    }
}
int main()
{
    #ifndef ONLINE_JUDGE
        freopen("in.txt","r",stdin);
    #endif
    
    int u,v,z;  
    int s,t;
    while(scanf(" %d %d",&n,&m)!=EOF)  
    {
        init();  
        for(int i=0; i<m; i++)  
        {  
            scanf(" %d %d %d",&u,&v,&z);  
            addEdge(u,v,z);
        }
        bfs();
        for(int i=0;i<total;i+=2)
        {
            printf("%d\n",edge[i].isC );
        }
    }
    return 0;
}
