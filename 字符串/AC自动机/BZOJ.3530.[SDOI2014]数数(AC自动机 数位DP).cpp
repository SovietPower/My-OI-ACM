/*
15072kb	416ms
������λDP ��f[i][0/1]��ʾƥ�䵽��iλǰ��i-1λ�Ƿ�Ϊ�Ͻ硣
��������Ҫ״̬ת�ƣ�����ÿ��״̬ ö��ÿһ��������AC�Զ����õ���һ��״̬(����״̬��ʵ���������ϵı��) 
ps1.�����ܴ�ǰ��0(��Ϊ����00...�����Ĵ�)����ÿһλҪ�ȼ�����ÿ����������ͷ�ķ����� 
ps2.���ĳ����������fail���ص�һ��ģʽ���ڵ㣬��Ҳ�ǲ����е� 
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
	for(int i=1; i<A[1]; ++i) ++f[1][0][ac.son[0][i]];//������0 
	/*if(!ac.val[ac.son[0][A[1]]])*/ f[1][1][ac.son[0][A[1]]]=1;
	for(int i=2; i<=n; ++i)
	{
		for(int j=1; j<S; ++j)
			++f[i][0][ac.son[0][j]];//�Ե�ǰÿ������ͷ 
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
		if(!ac.val[i]) Add(res,(f[n][0][i]+f[n][1][i])%mod/*�����ȡģ*/);
	printf("%d",res);

	return 0;
}
