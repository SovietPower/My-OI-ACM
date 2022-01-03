/*
826ms	36000KB (����1��2028ms	34200KB)
�ܽ�һ�¶���ͼƥ�䣨ԭ�����ֻ�ܳ����ӣ������������Ϳ��Լ�[JSOI2019 ��Ϸ](https://www.cnblogs.com/SovietPower/p/9591108.html)��[NOI2011 �����뵰����Ϸ](https://www.cnblogs.com/SovietPower/p/9592769.html)������һ��[����](https://www.cnblogs.com/SovietPower/p/9770464.html)��
**������**
����������Ϊ��һ������ͼ�Ͻ��У�ÿ�δ�һ�����ߵ���һ���֣��Ҳ������߹��ĵ㡣
**������**
��ĳ�㣨ĳ״̬��һ�������ƥ���ϣ����ڸõ�ʱ���ֱ�ʤ���������ĳ��ƥ��ʹ�øõ㲻�����ƥ���ϣ����ڸõ�ʱ���ֱذܡ���֤����[JSOI2019 ��Ϸ](https://www.cnblogs.com/SovietPower/p/9591108.html)��
**�ж�ĳ���Ƿ�һ�������ƥ���ϣ�**
**����1��** �����õ������ƥ�䣬ɾ���õ��������ƥ�䣬��ƥ�����Ƿ���٣�����ʱ�򷴹��������øõ㲻��$S/T$������ƥ�������ټ��ϸõ㵽$S/T$�ı��������߼��Ͼ��а����������������������Ӷ�$O(�ܹ�)$��
**����2��** �������ƥ�䣬���õ�δ��ƥ����϶��ǡ�Ȼ��ö������δ��ƥ���$x$������$x$�бߵĵ�Ϊ$to$����������$to$ƥ��ĵ�$lk[to]$���Բ������ƥ���ϡ�����ֱ�������������Ӷ�$O(nm)$����������������DFS�����Ӷ�$O(�ܹ�+n+m)$��

��Ϊ����1Ҫ�������������ȷ���2��һ�����Ķࣨ������һ���ࣿ����

-----
$Description$
��һ����$m$λ���ֵ�����ÿλΪ$0$��$9$������ʼ״̬������$Alice,Bob$����������ÿ�β������Ը���һλ���֣���һ���һ�����Ҹĺ�״̬���ܺ�֮ǰ���ֹ����ظ����Ҳ��ܳ����ڸ�����$n$��״̬�С�$Alice$���֣����ܲ��������䣬��˭��Ӯ��
$m\leq5,n\lt 10^m,10������$��
$Solution$
ÿ�β�����������λ�͵���ż�Զ���ı䣬���Բ������Կ���һ������ͼ��
Ȼ���ж�����Ƿ�һ�������ƥ���Ͼ�ok�ˡ�
������������RE��ԭ���ǰ���ջ���ˡ���
*/
#include <bits/stdc++.h>
#define pc putchar
#define gc() getchar()
#define pb emplace_back
typedef long long LL;
const int N=1e5+5,M=N*20,LIM=1e5;
const int pw10[]={1,10,100,1000,10000,100000,1000000};

int Enum,S,T,H[N],nxt[M],fr[M],to[M],cap[M],pre[N],lev[N],lk[N];
bool odd[N],vis[N];

inline int read()
{
	int now=0,f=1; char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now*f;
}
inline void AE(int u,int v,int w)
{
	to[++Enum]=v, fr[Enum]=u, nxt[Enum]=H[u], H[u]=Enum, cap[Enum]=w;
	to[++Enum]=u, fr[Enum]=v, nxt[Enum]=H[v], H[v]=Enum, cap[Enum]=0;
}
bool BFS()
{
	static int q[N];
	int T=::T;
	for(int i=S; i<T; ++i) lev[i]=T+1;
	int h=0,t=1; q[0]=T, lev[T]=0;
	while(h<t)
	{
		int x=q[h++];
		for(int i=H[x]; i; i=nxt[i])
			if(lev[to[i]]==T+1 && cap[i^1])
				lev[to[i]]=lev[x]+1, q[t++]=to[i];
	}
	return lev[S]<=T;
}
inline int Augment()
{
	for(int i=T; i; i=fr[pre[i]])
		--cap[pre[i]], ++cap[pre[i]^1];
	return 1;
}
int ISAP()
{
	static int cur[N],num[N];

	if(!BFS()) return 0;
	int S=::S,T=::T,res=0,x=S;
	memset(num,0,T+1<<2);
	for(int i=S; i<=T; ++i) cur[i]=H[i], ++num[lev[i]];
	while(lev[S]<=T)
	{
		if(x==T) res+=Augment(),x=S;
		bool can=0;
		for(int i=cur[x]; i; i=nxt[i])
			if(lev[to[i]]==lev[x]-1 && cap[i])
			{
				can=1, cur[x]=i, pre[x=to[i]]=i;
				break;
			}
		if(!can)
		{
			int mn=T;
			for(int i=H[x]; i; i=nxt[i])
				if(cap[i]) mn=std::min(mn,lev[to[i]]);
			if(!--num[lev[x]]) break;
			++num[lev[x]=mn+1], cur[x]=H[x];
			if(x!=S) x=fr[pre[x]];
		}
	}
	return res;
}
void DFS(int x)
{
	vis[x]=1;
	for(int i=H[x]; i; i=nxt[i])
		if(/*lk[to[i]] && */!vis[lk[to[i]]]) DFS(lk[to[i]]);
}
void Solve()
{
	static int Ts=0; ++Ts;
	static int ban[N];

	int m=read(),n=read(),start=read();
	Enum=1, S=0, T=pw10[m]+1;
	while(n--) ban[read()]=Ts;

	for(int i=0; i+1<T; ++i)
		if(ban[i]!=Ts)
		{
			if(odd[i]) AE(i+1,T,1);
			else AE(S,i+1,1);
		}
	int tmp=Enum;
	for(int i=0; i+1<T; ++i)
		if(ban[i]!=Ts && !odd[i])
			for(int j=0; j<m; ++j)
			{
				int bit=i/pw10[j]%10,x;
				if(bit!=9) x=i+pw10[j];
				else x=i-9*pw10[j];
				if(ban[x]!=Ts) AE(i+1,x+1,1);

				if(bit) x=i-pw10[j];
				else x=i+9*pw10[j];
				if(ban[x]!=Ts) AE(i+1,x+1,1);
			}
	ISAP();
//--����1��
//	if(odd[start]) AE(start+1,T,1);
//	else AE(S,start+1,1);
//	if(ISAP()) puts("Alice");
//	else puts("Bob");

//--����2��
	for(int i=tmp+1; i<=Enum; i+=2)
		if(!cap[i]) assert(!lk[fr[i]]&&!lk[to[i]]),lk[fr[i]]=to[i], lk[to[i]]=fr[i];
	vis[0]=1;//! DFS����0��
	for(int i=1; i<T; ++i) if(!lk[i] && !vis[i]) DFS(i);
	puts(vis[start+1]?"Bob":"Alice");//vis=0:һ�������ƥ���� 

	memset(H,0,T+1<<2), memset(lk,0,T+1<<2), memset(vis,0,T+1);
}

int main()
{
	for(int i=0; i<LIM; ++i)
	{
		int x=i,t=0;
		while(x) t+=x%10,x/=10;
		odd[i]=t&1;
	}
	for(int T=read(); T--; Solve());

	return 0;
}
