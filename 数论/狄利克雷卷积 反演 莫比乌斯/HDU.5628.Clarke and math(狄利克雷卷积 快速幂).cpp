/*
http://www.cnblogs.com/SovietPower/p/8351671.html
�տ�ʼҪ��ans��ʼ��Ϊ��λԪ����ans[2~n]=0,ans[1]=1,���������һ�����������������������1 
��ʼ��xΪI,I(n)=1 
ע:1.���������������׾���Ǹ����� 
2.��������ȡģ����ֱ����-=mod 
*/
#include<cstdio>
#include<cctype>
#include<cstring>
#define gc() getchar()
typedef long long LL;
const int N=1e5+5,mod=1e9+7;

int n,k;
LL f[N],ans[N],tmp[N],x[N];

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=gc()) if(c=='-') f=-1;
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}
#define Mod(x) x>=mod?x-=mod:0
void Dirichlet(LL *a,LL *b)//a*b
{
	memset(tmp,0,sizeof tmp);
	for(int i=1;i*i<=n;++i)
	{
		tmp[i*i]+=a[i]*b[i]%mod, Mod(tmp[i*i]);
		for(int j=i+1;i*j<=n;++j)//�±߼���a[i]*b[j]��a[j]*b[i]������j��i+1��ʼ���� 
			(tmp[i*j]+=a[i]*b[j]%mod+a[j]*b[i]%mod)%=mod;//ע���������������һ����Modȡģ����
	}
	memcpy(a,tmp,sizeof tmp);
}
void Solve()
{
	for(int i=1;i<=n;++i) x[i]=1,ans[i]=0;//x:I^0
	ans[1]=1;//ans:e
	for(;k;k>>=1,Dirichlet(x,x))
		if(k&1) Dirichlet(ans,x);
	Dirichlet(ans,f);
	for(int i=1;i<=n;++i) printf("%lld%c",ans[i],i==n?'\n':' ');//�ո񼰻��з���Ҫ�� 
}

int main()
{
	for(int t=read();t--;)
	{
		n=read(),k=read();
		for(int i=1;i<=n;++i) f[i]=read();
		Solve();
	}
	return 0;
}
