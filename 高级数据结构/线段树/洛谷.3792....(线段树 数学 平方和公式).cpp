/*
平方和公式:用于求连续自然数的平方和 
∑(k=1 to n) k^2 = 1^2 + 2^2 +...+ n^2 = n^3/3 + n^2/2 + n/6
									   = n(n+1)(2n+1)/6
									   = C(n+2,3)+C(n+1,3)= C(n+1,3)+C(n+1,2)= C(2n+2,3)= nC(n+1,2)-C(n+1,3)
利用最小值最大值得到[l+1,r]区间平方和:r(r+1)(2r+1)*inv6 - l(l+1)(2l+1)*inv6 
inv6为%mod下6的逆元，即6^(mod-2)
注意取模 
*/
#include<cstdio>
#include<cctype>
#include<algorithm>
#define LL long long
//#define gc() getchar()
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
const int N=5e5+5,mod=1e9+7,MAXIN=5e6;

int n,q,Maxn,Minn;
LL inv6;
char IN[MAXIN],*SS=IN,*TT=IN;
inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=gc()) if(c=='-') f=-1;
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}
struct Seg_Tree
{
	int Min[N<<2],Max[N<<2];
	LL sum[N<<2];
	inline void PushUp(int rt)
	{
		Min[rt]=std::min(Min[rt<<1],Min[rt<<1|1]);
		Max[rt]=std::max(Max[rt<<1],Max[rt<<1|1]);
		sum[rt]=(sum[rt<<1]+sum[rt<<1|1])%mod;
	}
	void Build(int l,int r,int rt)
	{
		int m=l+r>>1;
		if(l==r) {Min[rt]=Max[rt]=read(),sum[rt]=1ll*Min[rt]*Min[rt]%mod; return;}
		Build(l,m,rt<<1),Build(m+1,r,rt<<1|1);
		PushUp(rt);
	}
	void Modify(int l,int r,int rt,int p,int v)
	{
		if(l==r) {Max[rt]=Min[rt]=v,sum[rt]=1ll*v*v%mod; return;}
		int m=l+r>>1;
		if(p<=m) Modify(l,m,rt<<1,p,v);
		else Modify(m+1,r,rt<<1|1,p,v);
		PushUp(rt);
	}
	void Query(int l,int r,int rt,int L,int R)
	{
		if(L<=l && r<=R)
		{
			Maxn=std::max(Maxn,Max[rt]),Minn=std::min(Minn,Min[rt]);
			return;
		}
		int m=l+r>>1;
		if(L<=m)
			if(m<R) Query(l,m,rt<<1,L,R),Query(m+1,r,rt<<1|1,L,R);
			else Query(l,m,rt<<1,L,R);
		else Query(m+1,r,rt<<1|1,L,R);
	}
	LL Query_Sum(int l,int r,int rt,int L,int R)
	{
		if(L<=l && r<=R) return sum[rt];
		int m=l+r>>1;
		if(L<=m)
			if(m<R) return (Query_Sum(l,m,rt<<1,L,R)+Query_Sum(m+1,r,rt<<1|1,L,R))%mod;
			else return Query_Sum(l,m,rt<<1,L,R);
		else return Query_Sum(m+1,r,rt<<1|1,L,R);
	}
}t;

int Fast_Pow(int x,int p)
{
	int tmp=1;
	for(;p;p>>=1,x=1ll*x*x%mod)
		if(p&1) tmp=1ll*tmp*x%mod;
	return tmp;
}
bool Judge(int l,int r)
{
	Maxn=-mod, Minn=mod, t.Query(1,n,1,l,r);
	if(Maxn-Minn!=r-l) return 0;
	LL now=t.Query_Sum(1,n,1,l,r);
	--Minn;
	LL fact= 1ll*Maxn*(Maxn+1)%mod*(2*Maxn+1)%mod*inv6
		    -1ll*Minn*(Minn+1)%mod*(2*Minn+1)%mod*inv6;
	fact=(fact%mod+mod)%mod;
//	printf("min:%d max:%d fact:%I64d now:%I64d\n",Minn+1,Maxn,fact,now);
	return now==fact;
}

int main()
{
	n=read(),q=read();
	t.Build(1,n,1);
	int opt,x,y;
	inv6=Fast_Pow(6,mod-2);
//	inv6=166666668;
	while(q--)
	{
		opt=read(),x=read(),y=read();
		if(opt==1) t.Modify(1,n,1,x,y);
		else puts(Judge(x,y)?"damushen":"yuanxing");
	}

	return 0;
}
