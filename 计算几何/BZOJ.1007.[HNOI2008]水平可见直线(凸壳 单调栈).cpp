/*
1800kb	160ms
可以看出我们是要维护一个下凸壳。
先对斜率从小到大排序。斜率最大、最小的直线是一定会保留的，因为这是凸壳最边上的两段。
维护一个单调栈，栈中为当前可见直线(按照斜率排序)。
当加入一条直线l时，可以发现 如果l与栈顶直线l'的交点p在 l'入栈前与栈顶直线 的交点p'的左侧，那么l会覆盖l'(直接用与第一条直线的交点好像也可以？)。弹出l'加入l。
如果p在p'右侧，则保留栈顶直线，并将l入栈；如果重合，那么后加入的直线应该会覆盖l'，弹出l'加入l。
在斜率符号改变时结果也是一样的。更新栈的过程应持续到p在p'的右侧。
如果有多条直线斜率相同，截距大的直线会覆盖截距小的直线。排序后过掉即可。
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
const int N=5e4+5;

int n,sk[N],top,Ans[N];
struct Line{
	int k,b,id;
	bool operator <(const Line &a)const{
		return k==a.k?b>a.b:k<a.k;
	}
}l[N];

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=gc()) if(c=='-') f=-1;
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}
bool Check(int a,int b,int c){//p(l_a&l_b) is on the left of p'(l_b&l_c)
	return 1ll*(l[a].b-l[b].b)*(l[c].k-l[b].k)<=1ll*(l[b].b-l[c].b)*(l[b].k-l[a].k);
}

int main()
{
	n=read();
	for(int i=1; i<=n; ++i) l[i].k=read(),l[i].b=read(),l[i].id=i;
	std::sort(l+1,l+1+n), sk[top=1]=1;
	for(int i=2; i<=n; ++i)
	{
		if(l[i].k==l[i-1].k) continue;
		while(top>1 && Check(i,sk[top],sk[top-1])) --top;//x=(b2-b1)/(k1-k2)
		sk[++top]=i;
	}
	for(int i=1; i<=top; ++i) Ans[i]=l[sk[i]].id;
	std::sort(Ans+1,Ans+1+top);
	for(int i=1; i<=top; ++i) printf("%d ",Ans[i]);

	return 0;
}
