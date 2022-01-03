/*
3360kb	84ms
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
#define gc() getchar()
typedef long long LL;
const int N=2e5+5;

int ex[N],L[N],R[N];
char s[N];

int Build()
{
	int n=strlen(s+1);
	for(int i=n; i; --i) s[i<<1]=s[i], s[(i<<1)-1]='#';
	s[0]='!', s[n<<1|1]='#', s[(n<<1)+2]='@';
	return n<<1|1;
}
void Manacher(const int n)
{
	for(int i=1,id,mx=0; i<=n; ++i)
	{
		if(i<mx) ex[i]=std::min(ex[2*id-i],mx-i);
		else ex[i]=1;
		while(s[i-ex[i]]==s[i+ex[i]]) ++ex[i];
		if(i+ex[i]>mx) mx=i+ex[i], id=i;
		L[i-ex[i]+1]=std::max(L[i-ex[i]+1],ex[i]-1);
		R[i+ex[i]-1]=std::max(R[i+ex[i]-1],ex[i]-1);
	}
}

int main()
{
	scanf("%s",s+1);
	int n=Build(); Manacher(n);
	for(int i=n-2; i>=1; i-=2) R[i]=std::max(R[i],R[i+2]-2);//i>=1 not i!
	for(int i=3; i<=n; i+=2) L[i]=std::max(L[i],L[i-2]-2);
	int ans=0;
	for(int i=1; i<=n; i+=2) if(L[i]&&R[i]) ans=std::max(ans,L[i]+R[i]);//if!
	printf("%d\n",ans);

	return 0;
}
