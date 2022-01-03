/*
15072kb	416ms
首先数位DP 用f[i][0/1]表示匹配到第i位前面i-1位是否为上界。
这样还需要状态转移，对于每个状态 枚举每一个数，用AC自动机得到下一个状态(这样状态其实就是在树上的标号) 
ps1.数不能带前导0(因为会有00...这样的串)，对每一位要先加上以每个非零数开头的方案数 
ps2.如果某个点能沿着fail跳回到一个模式串节点，它也是不可行的 
*/
#include <cstdio>
#include <cstring>
#define mod 1000000007
const int N=1505,S=10;

int n,m,A[N],f[1205][2][1505];
char s[N],tmp[N];
struct AC_Automaton
{
	int cnt,son[N][S],fail[N],q[N];
	bool val[N];
	void Insert(char *s)
	{
		int x=0;
		for(int t,i=0,l=strlen(s); i<l; ++i)
		{
			if(!son[x][t=s[i]-'0']) son[x][t]=++cnt;
			x=son[x][t];
		}
		val[x]=1;
	}
	void Build()
	{
		int h=0,t=0;
		for(int i=0; i<S; ++i)
			if(son[0][i]) fail[son[0][i]]=0,q[t++]=son[0][i];
		while(h<t)
		{
			int x=q[h++];
			val[x]|=val[fail[x]];//!
			for(int i=0; i<S; ++i)
				if(son[x][i]) fail[son[x][i]]=son[fail[x]][i],q[t++]=son[x][i];
				else son[x][i]=son[fail[x]][i];
		}
	}
}ac;
inline void Add(int &x,int v) {x+=v, x>=mod?x-=mod:0;}

int main()
{
	scanf("%s%d",s+1,&m), n=strlen(s+1);
	for(int i=1; i<=n; ++i) A[i]=s[i]-'0';
	for(int i=1; i<=m; ++i) scanf("%s",tmp),ac.Insert(tmp);
	ac.Build();

	int now=1,las=0;
	for(int i=1; i<A[1]; ++i) ++f[1][0][ac.son[0][i]];//不计算0 
	/*if(!ac.val[ac.son[0][A[1]]])*/ f[1][1][ac.son[0][A[1]]]=1;
	for(int i=2; i<=n; ++i)
	{
		for(int j=1; j<S; ++j)
			++f[i][0][ac.son[0][j]];//以当前每个数开头 
		for(int j=0; j<=ac.cnt; ++j)
			if(!ac.val[j])
			{
				for(int k=0; k<S; ++k)
					Add(f[i][0][ac.son[j][k]],f[i-1][0][j]);
				for(int k=0; k<A[i]; ++k)
					Add(f[i][0][ac.son[j][k]],f[i-1][1][j]);
				Add(f[i][1][ac.son[j][A[i]]],f[i-1][1][j]);
			}
	}
	int res=0;
	for(int i=0; i<=ac.cnt; ++i)
		if(!ac.val[i]) Add(res,(f[n][0][i]+f[n][1][i])%mod/*这带个取模*/);
	printf("%d",res);

	return 0;
}
