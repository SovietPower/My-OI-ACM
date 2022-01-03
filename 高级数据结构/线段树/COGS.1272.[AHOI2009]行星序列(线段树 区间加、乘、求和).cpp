//×¢ÒâÈ¡Ä£! 
#include<cstdio>
#include<cctype>
using namespace std;
const int N=1e5+5;

int n,mod,Sum[N<<2],aTag[N<<2],mTag[N<<2];

inline int read()
{
	int now=0,f=1;register char c=getchar();
	for(;!isdigit(c);c=getchar())
	  if(c=='-') f=-1;
	for(;isdigit(c);now=now*10+c-'0',c=getchar());
	return now*f;
}

inline void PushUp(int rt)
{
	Sum[rt]=(Sum[rt<<1]+Sum[rt<<1|1])%mod;
}
inline void PushDown(int m,int rt)
{
	if(mTag[rt]!=1)
	{
		mTag[rt<<1]=1ll*mTag[rt<<1]*mTag[rt]%mod;
		mTag[rt<<1|1]=1ll*mTag[rt<<1|1]*mTag[rt]%mod;
		aTag[rt<<1]=1ll*aTag[rt<<1]*mTag[rt]%mod;
		aTag[rt<<1|1]=1ll*aTag[rt<<1|1]*mTag[rt]%mod;
		Sum[rt<<1]=1ll*Sum[rt<<1]*mTag[rt]%mod;
		Sum[rt<<1|1]=1ll*Sum[rt<<1|1]*mTag[rt]%mod;
		mTag[rt]=1;
	}
	if(aTag[rt])
	{
		aTag[rt<<1]+=aTag[rt], aTag[rt<<1]%=mod;
		aTag[rt<<1|1]+=aTag[rt], aTag[rt<<1|1]%=mod;
		Sum[rt<<1]=(1ll*Sum[rt<<1]+1ll*(m-(m>>1))*aTag[rt]%mod)%mod;
		Sum[rt<<1|1]=(1ll*Sum[rt<<1|1]+1ll*(m>>1)*aTag[rt]%mod)%mod;
		aTag[rt]=0;
	}
}
void Build(int l,int r,int rt)
{
	mTag[rt]=1;
	if(l==r)
	{
		Sum[rt]=read()%mod;
		return;
	}
	int m=l+r>>1;
	Build(l,m,rt<<1),Build(m+1,r,rt<<1|1);
	PushUp(rt);
}
void Modify_Add(int l,int r,int rt,int L,int R,int v)
{
	if(L<=l && r<=R)
	{
		aTag[rt]+=v;
		if(aTag[rt]>=mod) aTag[rt]-=mod;
		Sum[rt]=(1ll*Sum[rt]+1ll*v*(r-l+1))%mod;
		return;
	}
	PushDown(r-l+1,rt);
	int m=l+r>>1;
	if(L<=m) Modify_Add(l,m,rt<<1,L,R,v);
	if(m<R) Modify_Add(m+1,r,rt<<1|1,L,R,v);
	PushUp(rt);
}
void Modify_Mult(int l,int r,int rt,int L,int R,int v)
{
	if(L<=l && r<=R)
	{
		aTag[rt]=1ll*aTag[rt]*v%mod;
		mTag[rt]=1ll*mTag[rt]*v%mod;
		Sum[rt]=1ll*Sum[rt]*v%mod;
		return;
	}
	PushDown(r-l+1,rt);
	int m=l+r>>1;
	if(L<=m) Modify_Mult(l,m,rt<<1,L,R,v);
	if(m<R) Modify_Mult(m+1,r,rt<<1|1,L,R,v);
	PushUp(rt);
}
int Query_Sum(int l,int r,int rt,int L,int R)
{
	if(L<=l && r<=R) return Sum[rt];
	PushDown(r-l+1,rt);
	int m=l+r>>1;long long res=0;
	if(L<=m) res+=Query_Sum(l,m,rt<<1,L,R), res%=mod;
	if(m<R) res+=Query_Sum(m+1,r,rt<<1|1,L,R), res%=mod;
	return res;
}

int main()
{
	freopen("seqb.in","r",stdin);
	freopen("seqb.out","w",stdout);

	n=read(),mod=read();
	Build(1,n,1);
	int m=read(),opt,l,r,v;
	while(m--)
	{
		opt=read(),l=read(),r=read();
		if(opt==1)
			v=read(), Modify_Mult(1,n,1,l,r,v);
		else if(opt==2)
			v=read(), Modify_Add(1,n,1,l,r,v);
		else
			printf("%d\n",Query_Sum(1,n,1,l,r));
	}

	fclose(stdin);fclose(stdout);
	return 0;
}
