/*
1092MS	151236K(fread) <- 7784MS	149280K
$Description$
����һ��$Trie$����$Trie$�����л��Ĵ� ���ȳ��Գ��ִ��� �ĺ͡�����Ļ��Ĵ�ֻ���Ǵ��ϵ��µ�һ������
�ڵ���$n\leq 2\times 10^6$���ַ���Ϊ`a,b,c,d`��

$Solution$
��������������ǻ�����ģ�塣��������DFS $x$��ÿ�����ӵ�ʱ������$x$����$las$���ɣ�Ҳ���ǰ���ȴ�һ��$las$���飬ÿ����$las[dep-1]$��$las$ȥ���뼴�ɡ���Ҳ���Ի��ݵ�ʱ��ֱ��ɾ�ڵ㣩
ÿ�β�������Ĺ�����ô�㡣����
��$ans[x]$��ʾ$x$�ڵ㣨״̬�����Ĺ��ף��������$x$�ڵ�𰸾ͼ���$ans[x]$��
�����½���$x$�ڵ㣬$ans[x]=len[x]+ans[fail[x]]$�������²����Ĵ���ʣ�µĹ��׾���$fail[x]$��״̬�Ĺ����ˣ���

����`fread`֮�󾪴���= =�õ���hdu�ϵ�һ��rank1= =
��Ȼ�������㷨Ч�����⡣����
*/
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 2000000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=2e6+6;

char IN[MAXIN],*SS=IN,*TT=IN;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}

struct PAM
{
	int s[N],H[N],nxt[N],tot,las[N],son[N][4],len[N],fail[N];
	LL Ans,ans[N];
	char tmp[N];
	inline void Init()
	{
		las[0]=tot=1, fail[0]=1, len[1]=-1, s[0]=-1;
		memset(son[0],0,sizeof son[0]), memset(son[1],0,sizeof son[1]);
	}
	inline int Find(int x,int n)
	{
		while(s[n]!=s[n-len[x]-1]) x=fail[x];
		return x;
	}
	void Insert(int c,int n)
	{
		s[n]=c;
		int p=Find(las[n-1],n);
		if(!son[p][c])
		{
			int np=++tot;
			memset(son[np],0,sizeof son[np]);
			fail[np]=son[Find(fail[p],n)][c];
			son[p][c]=np, len[np]=len[p]+2;
			ans[np]=ans[fail[np]]+len[np];
		}
		Ans+=ans[las[n]=son[p][c]];
	}
	void DFS(int x,int dep)
	{
		for(int v=H[x]; v; v=nxt[v])
			Insert(tmp[v]-'a',dep), DFS(v,dep+1);
	}
	void Solve()
	{
		Init();
		const int n=read();
		for(int i=1; i<=n; ++i)
		{
			while(!isalpha(tmp[i]=gc()));
			int fa=read();
			nxt[i]=H[fa], H[fa]=i;
		}
		Ans=0, DFS(0,1), printf("%lld\n",Ans);
		memset(H,0,n+1<<2);
	}
}pam;

int main()
{
	for(int T=read(); T--; pam.Solve());
	return 0;
}
