#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
typedef long long LL;
const int N=1e5+5,Ref1[3]={5,3,1},Ref2[3]={1,3,1};

int mp[N];
LL A[N],s[N],s2[N],s3[N];

inline LL read()
{
	LL now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}

int main()
{
	int n=read(); LL ans=0;
	for(int i=1; i<=n;++i) A[i]=read();
	register char c=gc(); while(c!='W'&&c!='G'&&c!='L') c=gc();
	//Grass:0 Water:1 Lava:2
	mp[1]=c=='L'?2:c=='W';
	for(int i=2; i<=n;++i) c=gc(), mp[i]=c=='L'?2:c=='W';

	for(int i=1; i<=n;++i) ans+=A[i]*Ref1[mp[i]];
//	printf("preans:%I64d\n",ans);

	for(int i=n; i; --i)
		mp[i]==2 ? (s[i]=std::min(s[i+1],0ll)-A[i]) : (s[i]=s[i+1]+A[i]);
	LL res=0,now=0,delta=0; s[0]=-1;
	for(int i=1,f=0,f2=0; i<=n;++i)//Grass:0 Water:1 Lava:2
	{
		if(!f && s[i]>=0) f=1;
		if(f2<2 && mp[i]<2) f2=mp[i]+1;
		if(s[i-1]<0 && s[i]>0) res+=s[i], s3[i]+=s[i];
		now+=A[i];
		if(s[i]>=0 && !mp[i])
		{
			LL v=std::min(res,A[i]<<1);
//			printf("v:%I64d now:%I64d val:%I64d\n",v,now,now<=v?v+now:v<<1);
			if(now<v) now-=A[i], delta+=v+now, res-=now, s3[i]-=now+A[i], now=0;//now*4 + (v-now)/2*(5+1)
			else delta+=v<<1, res-=v, s3[i]-=v, now-=v;
		}
//		else now+=A[i];
		if(!f && s[i]<0) ans-=s[i]*(f2==1?5:3), f=1;
//		printf("After i:%d s[i]:%I64d ans:%I64d res:%I64d now:%I64d delta:%I64d\n",i,s[i],ans,res,now,delta);
	}
	for(int i=n; i; --i) s3[i]+=s3[i+1];
	for(int i=1,f=0; i<=n;++i)//Grass:0 Water:1 Lava:2
	{
		if(mp[i]==1 && s3[i]>0)
		{
			LL v=std::min(s3[i],A[i]<<1);
			delta+=v;
		}
//		printf("s3 i:%d s3[i]:%I64d ans:%I64d delta:%I64d\n",i,s3[i],ans,delta);
	}
	printf("%I64d\n",ans-delta);

	return 0;
}
