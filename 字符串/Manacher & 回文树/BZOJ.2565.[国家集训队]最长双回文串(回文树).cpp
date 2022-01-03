/*
23576kb	156ms
**Manacher：**
记$R_i$表示以$i$位置为结尾的最长回文串长度，$L_i$表示以$i$开头的最长回文串长度。答案就是$\max\{R_i+L_{i+1}\}$。式子可能会有差别，因为Manacher会在里面加字符。当然我们直接只用'#'位置的$L_i+R_i$就可以更新答案啦。
Manacher，然后对于位置$i$，设它的最远延伸距离是$ex_i$。
然后用$i-j$更新$L_j,\;j\in[i-ex_i+1,\ i]$，$j-i$更新$R_j,\;j\in[i,i+ex_i-1]$（注意字符串里加了'#'的）。

显然只需要维护更新它的$\max\{i\},\min\{i\}$就可以了，可以用线段树。（当然我懒得去写）
但这个做法显然不够好，考虑能否$O(1)$更新，也就是更新一个位置然后递推过来。（表示没想出来= =）

可以啊...更新$i-j$这个值，相邻两个位置是相差$1$的。而从$j$更新到$i$位置时，$i-j$就$\leq0$了。也就是我们只更新$L_{i-ex_i+1}=\max\{ex_i-1\}$，最后用$L_j=\max\{L_j,\ L_{j-1}-1\}$递推即可。$R$同理。
这样就$O(n)$啦。

当然我们只需要在'#'处统计，所以只更新这些位置即可。

**回文树：**
对正反串建两次回文树，求出每个位置的最长回文长度就可以了。。
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
typedef long long LL;
const int N=1e5+5;

char s[N];
struct PAM
{
	int las,tot,fail[N],son[N][26],len[N],mx[N];

	PAM() {tot=1, fail[0]=1, len[1]=-1;}
	inline int Find(int x,int n)
	{
		while(s[n-len[x]-1]!=s[n]) x=fail[x];
		return x;
	}
	void Insert(int c,int n)
	{
		int p=Find(las,n);
		if(!son[p][c])
		{
			int np=++tot; fail[np]=son[Find(fail[p],n)][c];
			son[p][c]=np, len[np]=len[p]+2;
		}
		las=son[p][c];
	}
	void Build(char *s,const int n,const int opt)
	{
		if(opt) for(int i=1; i<=n; ++i) Insert(s[i]-'a',i), mx[i]=len[las];
		else for(int i=1; i<=n; ++i) Insert(s[i]-'a',i), mx[n-i+1]=len[las];//...
	}
}p1,p2;

int main()
{
	scanf("%s",s+1); int n=strlen(s+1);
	p1.Build(s,n,1), std::reverse(s+1,s+1+n), p2.Build(s,n,0);
	int ans=0;
	for(int i=1; i<n; ++i) ans=std::max(ans,p1.mx[i]+p2.mx[i+1]);
	printf("%d\n",ans);

	return 0;
}
