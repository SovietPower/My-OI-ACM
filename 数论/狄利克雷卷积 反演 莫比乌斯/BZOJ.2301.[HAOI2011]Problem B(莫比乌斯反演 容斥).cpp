/*
http://www.cnblogs.com/SovietPower/p/8325835.html
注意利用前缀和是个(l,r],左端点-1 
最后求解要容斥:(a,c为开区间，另外其实并不分左右)
ans=f[a~b,c~d]=f[b,d]-f[a,d]-f[b,c]+f[a,c]
*/
#include<cstdio>
#include<cctype>
#include<algorithm>
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
const int N=5e4+3,MAXIN=1<<17;

int cnt,P[N+2],mu[N+2],sum[N+2];
bool Not_P[N+2];
char IN[MAXIN],*SS=IN,*TT=IN;

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=gc()) if(c=='-') f=-1;
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}
void Init()
{
	mu[1]=1;
	for(int i=2;i<N;++i)
	{
		if(!Not_P[i]) P[++cnt]=i,mu[i]=-1;
		for(int j=1;j<=cnt&&i*P[j]<N;++j)
		{
			Not_P[i*P[j]]=1;
			if(!(i%P[j])) {mu[i*P[j]]=0; break;}
			mu[i*P[j]]=-mu[i];
		}
	}
	for(int i=1;i<N;++i) sum[i]=sum[i-1]+mu[i];
}
int calc(int n,int m)
{
	int t=std::min(n,m),ans=0;//应该不需要longlong 
//	for(int k=1;k<=t;++k) ans+=mu[k]*(n/k)*(m/k);//TLE:O(n^2)
	for(int las,i=1;i<=t;i=las+1)
	{
		las=std::min(n/(n/i),m/(m/i));
		ans+=(sum[las]-sum[i-1])*(n/i)*(m/i);
	}
	return ans;
}

int main()
{
	Init();
	int t=read(),a,b,c,d,k;
	while(t--)
		a=read()-1,b=read(),c=read()-1,d=read(),k=read(),
		a/=k,b/=k,c/=k,d/=k,printf("%d\n",calc(b,d)-calc(a,d)-calc(b,c)+calc(a,c));
	return 0;
}
