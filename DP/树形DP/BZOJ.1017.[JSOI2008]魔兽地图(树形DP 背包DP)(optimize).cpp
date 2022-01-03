/*
43108kb	1100ms
����DP�������ӽڵ�Ը��ڵ�Ĺ��ס� 
��f[x][i][j]��ʾ��ǰΪx����i��xȥ�ϳ���һ��װ��������Ϊj������ֵ��
���ӽڵ�ת��ʱ ��һ�����鱳������Ҫһ����������g[i][j]��ʾǰi����������Ϊj�ܹ��׸�x������ֵ��
��ô $g[i][j] = max{g[i-1][j-k]+f[v][l*need[x]][k]}$��$need[x]$Ϊx��Ҫ�ӽڵ�v�ĸ�����$l$Ϊ�ϳ�x�ĸ��������ͬ����Ҫö�١�
��ô����ÿ��$l$������ö���ö��ٸ�x�ϳ���һ�㣬����f���� $f[x][i][j] = max{g[all][j]+val[x]*(l-i)}$��($g$�Ѿ���Ҫ��ϳ�$l$��x�ļ�ֵ)
������һ���������Ϳ��Լ򵥵ر���һ������ֵ�ˡ���
g[][]ȷʵ������һά�����ǾͲ��ܽ�һ���Ż��ˣ����ұ��ⲻ��ÿ��memset��(�Ż��൱����)
��������Ȼ���������
*/
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define gc() getchar()
const int N=53,M=2002,INF=0x3f3f3f3f;

int n,m,Enum,H[N],nxt[N],to[N],need[N],dgr[N],val[N],cost[N],num[N],Ans[M],f[N][101][M],g[N][M];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline void AddEdge(int u,int v,int w){
	++dgr[v], to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum, need[Enum]=w;
}
void dfs(int x)
{
	if(!H[x]){
		num[x]=std::min(num[x],m/cost[x]);
		for(int i=0; i<=num[x]; ++i)
			for(int j=i; j<=num[x]; ++j)//���Ʋ��� j*cost[x]<=m��������num[]���ơ�
				f[x][i][j*cost[x]]=(j-i)*val[x];
		return;
	}
	num[x]=100;
	for(int i=H[x]; i; i=nxt[i])
		dfs(to[i]), num[x]=std::min(num[x],num[to[i]]/need[i]), cost[x]+=need[i]*cost[to[i]];
	num[x]=std::min(num[x],m/cost[x]);
	memset(g,-0x3f,sizeof g);
	g[0][0]=0;
	for(int now,l=num[x]; ~l; --l)//��ǰҪ�ϳ�l�� 
	{
		now=0;
		for(int i=H[x],v=to[i],w=l*need[i]; i; i=nxt[i],v=to[i],w=l*need[i],++now)
			for(int j=0; j<=m; ++j)
				if(g[now][j]>=0)//����Ż�����Ч 
					for(int k=0; k+j<=m; ++k)//g[0][..]���ᱻ�����ˣ�ÿ��һ������֮ǰ�Ϸ���ת���� 
						g[now+1][j+k]=std::max(g[now+1][j+k],g[now][j]+f[v][w][k]);
		for(int i=0; i<=l; ++i)
			for(int j=0; j<=m; ++j)
				f[x][i][j]=std::max(f[x][i][j],g[now][j]+(l-i)*val[x]);//����Ҫ��ö��k��g[k]����f[j-k]��fֻ����g[]ת��������ֻ�ܴӵ�ǰg[]ת�ơ�
	}
}

int main()
{
	n=read(),m=read();
	char s[3];
	for(int x,v,i=1; i<=n; ++i)
	{
		val[i]=read(), scanf("%s",s);
		if(s[0]=='A'){
			x=read();
			while(x--) v=read(),AddEdge(i,v,read());
		}
		else cost[i]=read(),num[i]=read();
	}
	memset(f,-0x3f,sizeof f);//���зǷ�״̬��
	for(int i=1; i<=n; ++i)
		if(!dgr[i])
		{
			dfs(i);
			for(int j=m; j; --j)
				for(int k=1; k<=j; ++k)
					Ans[j]=std::max(Ans[j],Ans[j-k]+f[i][0][k]);//���ڵ��f[i][0]ת�ƾͺ��ˡ�
		}
	printf("%d",Ans[m]);
	return 0;
}
