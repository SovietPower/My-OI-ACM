/*
645ms	8.14MB
$f_i=s_{i-1}+h_i^2+\min\{f_j-s_j+h_j^2-2h_i2h_j\}$，显然可以斜率优化。
$f_i-s_{i-1}-h_i^2+2h_ih_j=f_j-s_j+h_j^2$，横坐标不单调可以$CDQ$分治或$Splay$。
然后差不多就是个模板了。
*/
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 500000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=1e5+5;
const double INF=1e18;

int h[N],sk[N];
LL s[N],f[N];
char IN[MAXIN],*SS=IN,*TT=IN;
struct Quries
{
	int id,k,x; LL y;
	bool operator <(const Quries &t)const
	{
		return k>t.k;
	}
}q[N],tmp[N];

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now*f;
}
inline double GetK(int i,int j)
{
	return q[i].x==q[j].x?(q[i].y<=q[j].y?-INF:INF):1.0*(q[i].y-q[j].y)/(q[i].x-q[j].x);//1.0!!!
}
void CDQ(int l,int r)
{
	if(l==r)
	{
		if(l!=1) f[l]+=1ll*h[l]*h[l]+s[l-1];
		else f[l]=0;
		q[l].y=f[l]-s[l]+1ll*h[l]*h[l];
		return;
	}
	int mid=l+r>>1,p1=l,p2=mid+1;
	for(int i=l; i<=r; ++i) q[i].id<=mid?tmp[p1++]=q[i]:tmp[p2++]=q[i];
	for(int i=l; i<=r; ++i) q[i]=tmp[i];
	CDQ(l,mid);

	int top=0;
	for(int i=l; i<=mid; ++i)
	{
		while(top>=2 && GetK(sk[top],sk[top-1])>GetK(i,sk[top])) --top;
		sk[++top]=i;
	}
	for(int i=mid+1; i<=r; ++i)
	{
		while(top>=2 && GetK(sk[top],sk[top-1])>q[i].k) --top;
		int pi=q[i].id,j=sk[top],pj=q[j].id; f[pi]=std::min(f[pi],q[j].y-2ll*h[pi]*h[pj]);
	}
	CDQ(mid+1,r);

	p1=l,p2=mid+1; int t=l;
	while(p1<=mid && p2<=r) tmp[t++]=q[p1].x<=q[p2].x?q[p1++]:q[p2++];
	while(p1<=mid) tmp[t++]=q[p1++];
	while(p2<=r) tmp[t++]=q[p2++];
	for(int i=l; i<=r; ++i) q[i]=tmp[i];
}

int main()
{
	int n=read();
	for(int i=1; i<=n; ++i) h[i]=read();
	for(int i=1; i<=n; ++i) s[i]=s[i-1]+read();
	for(int i=1; i<=n; ++i) q[i]=(Quries){i,h[i]<<1,h[i],0};
	memset(f,0x3f,sizeof f), f[1]=0, std::sort(q+1,q+1+n), CDQ(1,n);
	printf("%lld\n",f[n]);

	return 0;
}
