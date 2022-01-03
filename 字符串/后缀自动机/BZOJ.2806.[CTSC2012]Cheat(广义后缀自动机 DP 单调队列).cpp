/*
63128kb	820ms
首先二分答案L。然后就是判断能否将原串划分出一些长度不小于L的子串，这些子串要是给定n个串中的某个串的子串，且满足它们的长度之和不小于原串长度的90%。
贪心多长选一段什么的显然不对。老老实实DP。
设f[i]为到i划分出的最长长度（不用想什么奇奇怪怪的状态啊→_→），则f[i]=max{f[i-1],f[j]+i-j}(s[i~j]为n个串中某串的子串，且i-j>=L)。
求以某位置结尾的子串是否匹配，可以对n个串建广义SAM，原串在上面匹配就能得到每个位置作为后缀所能匹配的最大长度，记为mx[i]。
那么j的范围就是i-mx[i]<=j<=i-L.
这是n^2的，要优化。因为贪心不对，区间内的数还是要都尝试更新一遍的。观察决策位置是否有单调性，比如i与i+1，有mx[i]+1>=mx[i+1]。
mx[i]+1>=mx[i+1]
i-mx[i]<=i+1-mx[i+1] (凑个i+1)
即决策位置是单调不降的。只需用单调队列维护当前区间f[j]-j的最值就可以了。
另外卡精度，0.9*n会偏大？要减个eps。（不想再看浮点数存储...太sxbk了吧）
*/
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define gc() getchar()
#define eps 1e-8
const int N=2200007;//字节。。

int n,m;
struct Suffix_Automaton
{
	int tot,las,son[N][2],fa[N],len[N],mx[N],q[N],f[N];
	char s[N];

	Suffix_Automaton() {tot=las=1;}
	void Insert(int c)
	{
		int p=las,np=++tot; len[las=np]=len[p]+1;
		for(; p&&!son[p][c]; p=fa[p]) son[p][c]=np;
		if(!p) fa[np]=1;
		else
		{
			int q=son[p][c];
			if(len[q]==len[p]+1) fa[np]=q;
			else
			{
				int nq=++tot; len[nq]=len[p]+1;
				memcpy(son[nq],son[q],sizeof son[q]);
				fa[nq]=fa[q], fa[q]=fa[np]=nq;
				for(; son[p][c]==q; p=fa[p]) son[p][c]=nq;
			}
		}
	}
	void Build()
	{
		scanf("%s",s), las=1;//!
		for(int i=0,l=strlen(s); i<l; ++i) Insert(s[i]-'0');
	}
	void Get_mx(char *s)
	{
		for(int c,now=0,p=1,i=1,l=strlen(s+1); i<=l; mx[i++]=now)
			if(son[p][c=s[i]-'0']) ++now, p=son[p][c];
			else
			{
				for(; p&&!son[p][c]; p=fa[p]);
				if(!p) now=0, p=1;
				else now=len[p]+1, p=son[p][c];
			}
	}
	bool Check(int L,int n)
	{
		int h=1,t=0; f[0]=0;
		for(int i=1; i<=n; ++i)
		{
			f[i]=f[i-1];
			if(i>=L && L<=mx[i])
			{
				int p=i-L;
				while(h<=t && f[q[t]]-q[t]<=f[p]-p) --t;
				q[++t]=p;
			}
			while(h<=t && q[h]<i-mx[i]) ++h;
			if(h<=t) f[i]=std::max(f[i],i+f[q[h]]-q[h]);//好像f[0]=INF不太方便 
		}
		return (double)f[n]>=0.9*n-eps;//0.89999999
	}
	void Query()
	{
		scanf("%s",s+1), Get_mx(s);
		int len=strlen(s+1);
		int l=1,r=len,mid,ans=0;
		while(l<=r)
			if(Check(mid=l+r>>1,len)) ans=mid,l=mid+1;
			else r=mid-1;
		printf("%d\n",ans);
	}
}sam;

int main()
{
	scanf("%d%d",&n,&m);
	while(m--) sam.Build();
	while(n--) sam.Query();
	return 0;
}
