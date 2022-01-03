/*
93ms	100KB
f[l][r][rt]表示l~r以rt为根是否可行，转移时枚举l,r,rt，再枚举左右子树的根。当存在f[l][rt-1][lrt]==1 && f[rt+1][r][rrt]==1 && lrt,rrt均可与rt连边 时，f[l][r][rt]=1。
最后一层枚举总共是O(r-l)的，一共O(n^4)。
但是一个区间是否合法，我们只需要知道左右能否拼起来。我们用L[l][k]/R[k][r]表示以k为根往左/右是否能延伸到l/r。
那么区间[l,r]合法 当且仅当存在k满足 L[l][k]==1 && R[k][r]==1。当[l,r]合法后就可以根据k更新L[l][r+1]和R[l-1][r]了。
这样只需枚举区间和子树的根，复杂度O(n^3)。
可以用bitset优化。
数据感觉好水啊。。L,R更新都错了还是在51个点WA。
另外果然有更神奇的做法。。贪心么。。?
*/
#include <cstdio>
#include <cctype>
#include <bitset>
#include <algorithm>
#define gc() getchar()
const int N=707;

int n,A[N];
std::bitset<N> ok[N],L[N],R[N],ans[N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
int Gcd(int a,int b){
	return b?Gcd(b,a%b):a;
}

int main()
{
	n=read();
	for(int i=1; i<=n; ++i) A[i]=read(), L[i][i]=R[i][i]=1;
	for(int i=1; i<n; ++i)
		for(int j=i+1; j<=n; ++j) ok[i][j]=ok[j][i]=(Gcd(A[i],A[j])>1);
	for(int len=0; len<n; ++len)//得先用长度为1的区间更新一次。。
		for(int l=1,r; (r=l+len)<=n; ++l)
		{
			ans[l]=L[l]&R[r];
			if((ans[l]&ok[r+1]).count()) L[l][r+1]=1;
			if((ans[l]&ok[l-1]).count()) R[r][l-1]=1;//l-1是第二维啊 
		}
	puts(ans[1].count()?"Yes":"No");

	return 0;
}
