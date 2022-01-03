/*
���ȿ��Կ���DFS ÿB����һ���飬�����������ײ�����ϱ����� 
���ǿ��Ǵӵ��¿�ʼ�֣�����DFS��һ����ʱ�Ž������ջ�У�������size==Bʱ��ջ 
����ڸ��ڵ���ܻ�ʣ��һЩδ����ĵ㣬��Щ������Ȼ<B(���ϸ��ڵ�<=B)���ָ��Ͽ�ͺ��� 
�о���ô�������2B����
*/
#include <cstdio>
#include <cctype>
#define gc() getchar()
const int N=1005;

int n,B,Enum,H[N],to[N<<1],nxt[N<<1],sk[N],num,bel[N],cnt,capt[N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline void AddEdge(int u,int v){
	to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum;
	to[++Enum]=u, nxt[Enum]=H[v], H[v]=Enum;
}
void DFS(int x,int f)
{
	int cur=num;
	for(int i=H[x]; i; i=nxt[i])
		if(to[i]!=f)
		{
			DFS(to[i],x);
			if(num>=B+cur)
			{
				capt[++cnt]=x;
				while(num>cur)
					bel[sk[num--]]=cnt;
			}
		}
	sk[++num]=x;
}

int main()
{
	n=read(),B=read();
	for(int u,v,i=1; i<n; ++i) u=read(),v=read(),AddEdge(u,v);
	if(n<B) {putchar('0'); return 0;}
	DFS(1,1);
	while(num) bel[sk[num--]]=cnt;
	printf("%d\n",cnt);
	for(int i=1; i<n; ++i) printf("%d ",bel[i]);
	printf("%d\n",bel[n]);
	for(int i=1; i<=cnt; ++i) printf("%d ",capt[i]);

	return 0;
}
