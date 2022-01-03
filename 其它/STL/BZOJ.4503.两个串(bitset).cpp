/*
2744kb	1372ms
可以用`bitset`暴力匹配。
维护`bitset<N> Ans`表示每个位置能否匹配$T$串。枚举$T$中的字符$T_j$，维护$Ans_i$是否能够匹配$T_j$，也就是$S_{i+j}$处是否是$T_j$。
可以用$26$个`bitset<N> Pos[26]`得到每种字符在$S$的哪些位置上出现过（出现过的位置设为$1$）。
然后枚举$T_j$（$j\in[0,T|$）的时候，$Ans_i$每次都与上$Pos_{T_j}$右移$j$位就可以了。（若是通配符就不用再与了）（注意是右移）
最后若$Ans_i$还是$1$，则$i$位置匹配$T$串。
复杂度$O(\frac{nm}{w})$。
*/
#include <cctype>
#include <cstdio>
#include <bitset>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 1000000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
const int N=1e5+3;

char S[N],T[N];
std::bitset<N> Ans,pos[26];
char IN[MAXIN],*SS=IN,*TT=IN;

int main()
{
	static int p[N];

	register char c;
	int n=0; while(isalpha(S[n]=gc())) ++n;//会有个换行符啊=_= 所以while的时候n先别加。
	int m=0; while(isalpha(T[m]=gc())||T[m]=='?') ++m;

	for(int i=0; i<n; ++i) pos[S[i]-97].set(i);
	Ans.set();
	for(int i=0; i<m; ++i) if(T[i]!='?') Ans&=pos[T[i]-97]>>i;

	int ans=0;
	for(int i=0; i<=n-m; ++i) if(Ans[i]==1) p[++ans]=i;
	printf("%d\n",ans);
	for(int i=1; i<=ans; printf("%d\n",p[i++]));

	return 0;
}
