/*
2ms	896KB
对于某个元素分类讨论一下，就可以知道n个元素的总颜色种数了。
比如对a[1]分类讨论：
若1的颜色和某个元素相同，则总颜色数为a[1]。a[i]要么等于a[1]（i与某个元素颜色相同，记个数为A），要么等于a[1]+1（i的颜色唯一，记个数为B）。
要满足：B不等于n-1（得有个i和1颜色相同）；最多颜色数=(A+1)/2+B要大于等于a[1]；同时还有上界限制！即最少颜色数=1+B要小于等于a[1]。
若1的颜色是唯一的，则总颜色数为a[1]+1。a[i]要么等于a[1]（i的颜色唯一，记个数为A），要么等于a[1]+1（与某个元素颜色相同，记个数为B）。
要满足：B不能为1（可以大于1也可以为0）；最多颜色数=1+A+B/2要大于等于a[1]+1；同时也有上界限制！即最少颜色数=1+A+(B!=0)要小于等于a[1]+1。
当然这个分类讨论实际和别人写的求最大最小值有多少个一样（只会执行一种check）。
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 300000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=1e6+5;

int a[N];
char IN[MAXIN],*SS=IN,*TT=IN;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
bool Check1(const int n)
{
	int A=0,B=0;
	for(int i=2,a1=a[1]; i<=n; ++i)
		if(a[i]==a1) ++A;
		else if(a[i]==a1-1) ++B;
		else return 0;
	return B<n-1&&(A+1>>1)+B>=a[1]&&B<a[1];//上界限制啊啊啊 
}
bool Check2(const int n)
{
	int A=0,B=0;
	for(int i=2,a1=a[1]; i<=n; ++i)
		if(a[i]==a1) ++A;
		else if(a[i]==a1+1) ++B;
		else return 0;
	return B!=1&&A+(B>>1)>=a[1]&&A+(B!=0)<=a[1];
}

int main()
{
	int n=read();
	for(int i=1; i<=n; ++i) a[i]=read();
	puts(Check1(n)||Check2(n)?"Yes":"No");
	return 0;
}
