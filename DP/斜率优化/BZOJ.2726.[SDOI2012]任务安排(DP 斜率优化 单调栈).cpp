/*
11172kb	1092ms(怎么一不小心就rank1了...)
用$t_i$表示加工时间的前缀和，$s_i$表示费用系数$F_i$的前缀和。
$f_i$表示以$i$作为某一组的最小花费。因为每次分组都会对后面所有任务产生影响，所以都乘
费用系数$F_i$就好了。所以：$$f_i=\min\{f_j+(t_i-t_j+S)*(s_n-s_j)\}$$
拆开，就能写成直线形式了：$f_i+t_is_j=f_j+t_js_j-Ss_j-s_nt_j+Ss_n+t_is_n$。
因为斜率$t_i$不单调，所以不能用单调队列弹出队首来维护。但是费用系数是正的，即横坐标$s_j$是单增的，所以可以直接用单调栈维护一个下凸壳，每次查询时在上面二分合适的斜率。
弹栈的时候要写>=，>不行。
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
#define MAXIN 1000000
//#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=3e5+5;//数据范围是3e5-- 

int n,S,t[N],s[N];
LL f[N];
char IN[MAXIN],*SS=IN,*TT=IN;
struct Node
{
	int id,x; LL y;
}sk[N];

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}
inline LL Calc(int i,int j)
{
	return f[j]+1ll*(t[i]-t[j]+S)*(s[n]-s[j]);
}

int main()
{
	n=read(),S=read();
	for(int i=1; i<=n; ++i) t[i]=t[i-1]+read(),s[i]=s[i-1]+read();
	for(int i=1,top=0; i<=n; ++i)
	{
		int l=1,r=top,res=0;//l=1!
		while(l<=r)
		{
			int mid=l+r>>1;
			if(sk[mid].y-sk[mid-1].y<1ll*t[i]*(sk[mid].x-sk[mid-1].x)) res=mid, l=mid+1;
			else r=mid-1;
		}
		f[i]=Calc(i,sk[res].id);
		Node tmp=(Node){i,s[i],f[i]+1ll*t[i]*s[i]-1ll*S*s[i]-1ll*s[n]*t[i]};
		while(top && 1ll*(sk[top].y-sk[top-1].y)*(tmp.x-sk[top].x)>=1ll*(tmp.y-sk[top].y)*(sk[top].x-sk[top-1].x)) --top;
		sk[++top]=tmp;
	}
	printf("%lld\n",f[n]);

	return 0;
}
