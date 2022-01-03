//Pollard_Rho:http://blog.csdn.net/thy_asdf/article/details/51347390
#include<cstdio>
#include<cctype>
#include<algorithm>
#define gc() getchar()
const int p[]={2,3,5,7,11,13,17,19};
typedef long long LL;
LL Ans;

inline LL read()
{
	LL now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=gc()) if(c=='-') f=-1;
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}
inline LL Mult(LL a,LL b,LL p)//O(1)���ٳ� 
{
	LL tmp=a*b-(LL)((long double)a/p*b+1e-8)*p;
	return tmp<0?tmp+p:tmp;
}
LL Fast_Pow(LL n,LL k,LL p)
{
	LL t=1;
	for(;k;k>>=1,n=n*n%p)
		if(k&1) t=t*n%p;
	return t;
}
bool Miller_Rabin(LL n)
{
	if(n==2) return 1;
	if(!(n&1)||n==1) return 0;
	for(int i=0;i<8;++i)
		if(n==p[i]) return 1;
		else if(!(n%p[i])) return 0;
	LL u=n-1,now,las; int t=0;
	while(!(u&1)) u>>=1,++t;
	for(int i=0;i<8;++i)
	{
		now=Fast_Pow(p[i],u,n);
		for(int j=1;j<=t;++j)
		{
			las=now, now=Mult(now,now,n);
			if(now==1&&las!=1&&las!=n-1) return 0;
		}
		if(now!=1) return 0;
	}
	return 1;
}
LL gcd(LL x,LL y)
{
	return y?gcd(y,x%y):x;
}
LL Rho(LL n,LL delta)
{//��Ҫ�ֽ�n�������������x,y����p=gcd(x-y,n)!=1&&p!=n����ôpΪn��һ��Լ��...ʡ�� 
	LL x=rand()%n,y=x,p=1; int k=2;//�趨kΪ�˴�·���� 
	for(int i=1;p==1;++i)
	{
		x=(Mult(x,x,n)+delta)%n;//�������f(x)=x*x+d 
		p=gcd(std::abs(x-y),n);//��������������ֱ���ҵ�p��n��һ������ 
		if(i==k) y=x,k<<=1;//�ﵽk�κ��y��ֵΪx��·��ÿ�α��� 
	}
	return p;
}
void Find(LL n)
{
	if(n==1) return;
	if(Miller_Rabin(n)) {Ans=std::max(Ans,n);/*fac[++cnt]=n;*/ return;}
	LL t=n;
	while(t==n) t=Rho(n,rand()%(n-1)+1);
	//t=n˵�������������ᵼ���ߵ�n�Ļ��ϣ��ٻ�һ�����Լ��� 
	Find(t), Find(n/t);
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("3667.in","r",stdin);
#endif

	int t=read();LL n;
	while(t--)
		n=read(),Ans=0,Find(n),Ans==n?puts("Prime"):printf("%lld\n",Ans);
	return 0;
}
