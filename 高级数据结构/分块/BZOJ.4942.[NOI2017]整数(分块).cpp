/*
18148kb	3740ms
[参考这里](https://www.luogu.org/blog/ShadowassIIXVIIIIV/solution-p3822)。

如果没有减法，对一个二进制数暴力进位，均摊复杂度是$O(1)$的（要进$O(n)$次位就至少需要$O(n)$次操作）。
但是这题有减法...显然暴力进位就不对了。
那么我们把减法变成加法，分别维护加上的数$inc$和减掉的数$dec$是多大。查询时显然不能直接两位相减，要判断一下后面是否需要进位。
对此用$set$维护一下$inc,dec$所有不同位的位置，找到查询位后面第一个不同的位置，判一下大小关系就可以了。

关于维护进位，比较显然的是拿线段树维护每一位的情况，把$a\times2^b$拆成$(2^{a_1}+2^{a_2}+...)2^n$。。这样就成两个$\log$了(╯‵□′)╯︵┻━┻。
注意到$a$不算大，而且线段树的每个位置是可以表示$16$或$32$位的。直接把$a$左移$b$位（本来就是= =），也就是把$a$加到$b$那个位置即可。如果取$32$位这么加一次显然是只会进位一次的（最多影响两个位置）。
（$32$位可以直接用`unsigned int`，自然溢出就可以得到加之后这几位的值，判断是否进位就判一下这个数加之前与加之后的大小关系即可）

注意到这个线段树其实没什么必要。分块，每块维护$32$位的值，每次只要在对应块上加，然后暴力进位即可。
复杂度$O(n\log n)$（`set`...）。

另外移位不能$\geq$位宽，所以移$32$位拆成移$31$位再移$1$位好了。。
*/
#include <set>
#include <cstdio>
#include <cctype>
#include <algorithm>
#define pc putchar
#define gc() getchar()
#define MAXIN 300000
//#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
typedef unsigned int uint;
const int N=1e6+5;

uint inc[N],dec[N];
std::set<int> st;
char IN[MAXIN],*SS=IN,*TT=IN,OUT[N<<1],*O=OUT;

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now*f;
}
void Modify(uint a,uint b,uint *A,uint *B)//a在传参前就要取abs啊（uint）
{//2^5=32
	int p=b>>5,q=b&31;
	uint tmp=A[p],delta=(a>>31-q)>>1; A[p]+=(a<<q);//uint
	delta+=(A[p]<tmp); std::set<int>::iterator it;
	if(A[p]!=B[p]) st.insert(p);
	else if((it=st.find(p))!=st.end()) st.erase(it);
	while(delta)
	{
		tmp=A[++p], A[p]+=delta, delta=A[p]<tmp;
		if(A[p]!=B[p]) st.insert(p);
		else if((it=st.find(p))!=st.end()) st.erase(it);
	}
}
void Query()
{
	int b=read(),p=b>>5,q=b&31,ans=((inc[p]^dec[p])>>q)&1;
	uint v1=inc[p]&((1<<q)-1),v2=dec[p]&((1<<q)-1);//inc[p]%(2^q) 取出该块p后面的部分 
	if(v1<v2) *O++=((ans^1)+48);//借位 
	else if(v1>v2||/*st.empty()||*/*st.begin()>=p) *O++=(ans+48);
	else
	{
		std::set<int>::iterator it=st.lower_bound(p); --it;
		*O++=((inc[*it]>dec[*it]?ans:ans^1)+48);
	}
	*O++='\n';
}

int main()
{
	st.insert(N);
	for(int T=read(),a=(read(),read(),read()),b; T--; )
		switch(read())
		{
			case 1: a=read(),b=read(),Modify(a>0?a:-a,b,a>0?inc:dec,a>0?dec:inc); break;
			case 2: Query();
		}
	fwrite(OUT,1,O-OUT,stdout);

	return 0;
}
