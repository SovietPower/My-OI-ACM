/*
$Description$
给定长为$n$的RGB序列，每次变换，序列中所有相邻的两个字符会产生一个字符（即每次总长度减1）。求$n-1$次变换后剩下的那个字符是多少。
字符产生规则：相同的两个字符产生相同的字符（如`RR->R`），不同的两个字符产生没出现的第三类字符（如`RG->B`）。
$n\leq 10^5$。
Ludicrous Coloured Triangles为加强版：$n\leq 10^9$。

$Solution$
**Sol 1.**
容易想到将$R,G,B$看做$0,1,2$，则不同颜色$a,b$转成第三者就是$3-a-b$。
然后可发现，$a,b$颜色相同时，$(3-a-b+3)\%3$也能正确表示同色的情况，即$(3-2a+3)\%3==a$。
所以每一次操作，就是将相邻两个颜色$a,b$变为$(6-a-b)\%3$，即$-a-b$然后取模下。只要算 到最后一层时，每个元素$x$被累积了几次，用$x$乘以这个次数即可。
可以猜到，第$i$个位置的元素会被累积$C_{n-1}^i$次（下标从$0$开始）。因为就是从$(1,i)$往下走，走到$(n,n/2)$前可以在任意行选择向右/左走$i$次。
其实也就是个倒置的杨辉三角。

所以答案为：$\sum_{i=0}^{n-1}value(s[i])*\binom{n-1}{i}\%3$（最后根据$n$奇偶性取正或负）。

~~求$C_{n-1}^i$可以用$\frac{n-1-i+1}{i}$递推。注意因为是$\mod 3$，$i$的逆元就是$i$，所以就是$(n-1-i+1)*i\%3$，可以$O(n)$递推~~
注意模数$3$太小，组合数不能递推或用阶乘算，要Lucas。。
复杂度$O(n\log_3n)$。

btw，将颜色$a,b$转化也可以使用$2*(a+b)\%3$，最后是有个$2^{n-1}$而不是$(-1)^{n-1}$。

**Sol 2.**
有一个性质：任意长为4的序列，其最终结果只与第一个和最后一个字符有关（而且是同样的转换原则）。
然后，对任意长为$3^k+1$的序列，其结果也有规律。具体是什么我已经不想去想了...
*/
#include <bits/stdc++.h>
typedef long long LL;
const int N=1e5+5;
using std::string;

int fac[3]={1,1,2};
#define Val(c) (c=='R'?0:c=='G'?1:2)
#define Char(v) (v==0?'R':v==1?'G':'B')
int C(int n,int m)//inv(x)==x
{
	return n<m ? 0 : fac[n]*fac[m]*fac[n-m]%3;
}
int Lucas(int n,int m)
{
	int ans=1;
	for(; m && ans; n/=3, m/=3) (ans*=C(n%3,m%3))%=3;
	return ans;
}
char triangle(const std::string &row)
{
	int n=row.length()-1;
	if(!n) return row[0];
	int i=0, ans=0;
	for(auto c: row) ans+=Val(c)*Lucas(n,i), ++i;
	return ans=(n&1?3-ans%3:ans)%3, Char(ans);
}

int main()
{
	string str;
	std::cin>>str;
	printf("%c",triangle(str));

	return 0;
}
