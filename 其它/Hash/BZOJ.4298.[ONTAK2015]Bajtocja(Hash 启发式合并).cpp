/*
75500kb	4628ms
������Ҫ֪����ֻ��ÿ�Ե�֮���Ƿ���ͨ������ͬһ��ͼ��������ͨ���Ƿ�һ�� 
�������Ƕ�ÿ������d��ͼ����������ͨ���Ž��й�ϣ�������ϣҪ�ܿ���ɾ��һ����� ����һ����� 
������������ϣ���ֵ��ͬ����ô����������d��ͼ�ж���ͨ�����������ٶ������ϣֵ��һ���ϣ����������ͬ��ϣֵ�ĸ��� 
����ʱ������ʽ�ϲ���ÿ�ν�sizeС����ͨ��ȫ���޸�fa���ܸ��Ӷ�O(dnlogn) 
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
typedef unsigned long long ull;
const int N=5005,D=205,M=1e6+5,mod=2e6;
const ull seed=769;

int n,m,d,H[D][N],Enum,to[M<<1],nxt[M<<1],fa[D][N],sz[D][N],Ans;
ull hs_id[N],Pow[D];
struct Hash_Table
{
	int top,h_H[mod+5],sk[mod],h_nxt[mod],cnt[mod];
	ull val[mod];
	void Init(){
		top=mod-5;
		for(int i=1; i<=top; ++i) sk[i]=i;
	}
	void Insert(ull x)
	{
		int p=x%mod;
		for(int i=h_H[p]; i; i=h_nxt[i])
			if(val[i]==x) {Ans+=2*cnt[i]+1,++cnt[i]; return;}
		++Ans;//(a,a)Ҳ��һ�� 
		int pos=sk[top--];
		val[pos]=x, cnt[pos]=1, h_nxt[pos]=h_H[p], h_H[p]=pos;
	}
	void Delete(ull x)
	{
		int p=x%mod,pre=h_H[p];
		if(val[pre]==x)
		{
			Ans-=2*cnt[pre]-1;
			if(!--cnt[pre]) sk[++top]=pre, h_H[p]=h_nxt[pre];
		}
		else
			for(int i=h_nxt[pre]; i; pre=i,i=h_nxt[i])
				if(val[i]==x)
				{
					Ans-=2*cnt[i]-1;
					if(!--cnt[i]) sk[++top]=i, h_nxt[pre]=h_nxt[i];
					break;
				}
	}
}hs2;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline void AddEdge(int u,int v,int k){
	to[++Enum]=v, nxt[Enum]=H[k][u], H[k][u]=Enum;
}
void DFS(int x,int f,int k,int anc)
{
	hs2.Delete(hs_id[x]);
	hs_id[x]-=Pow[k]*fa[k][x];//fa����bel�� 
	fa[k][x]=anc;
	hs_id[x]+=Pow[k]*anc;
	hs2.Insert(hs_id[x]);
	for(int i=H[k][x]; i; i=nxt[i])
		if(to[i]!=f) DFS(to[i],x,k,anc);
}
void Union(int u,int v,int k)
{
	if(fa[k][u]==fa[k][v]) return;
	if(sz[k][fa[k][u]]<sz[k][fa[k][v]]) std::swap(u,v);
	sz[k][fa[k][u]]+=sz[k][fa[k][v]];
	DFS(v,u,k,fa[k][u]);
	AddEdge(u,v,k),AddEdge(v,u,k);
}

int main()
{
	d=read(),n=read(),m=read();
	Pow[0]=1;
	for(int i=1; i<D; ++i) Pow[i]=Pow[i-1]*seed;
	hs2.Init();
	for(int i=1; i<=n; hs2.Insert(hs_id[i++]))
		for(int j=1; j<=d; ++j)
			fa[j][i]=i, sz[j][i]=1, hs_id[i]+=Pow[j]*i;//Hash = (��s[i]seed^i) mod 2^{31}
	int a,b,k;
	while(m--)
		a=read(),b=read(),k=read(),Union(a,b,k),printf("%d\n",Ans);
	return 0;
}
