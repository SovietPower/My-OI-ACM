/*
13516kb	220ms
$Description$
������ַ����� ���k�����Ĵ����ȵĳ˻�(Ҫ����Ĵ�����Ϊ����)�����������Ȼ��Ĵ�����k�������-1.(len<=10^6,k<=10^12)
$Solution$
ֻ�����������ȵĻ��Ĵ������ǲ���Ҫ��ÿ����֮������ַ���ֻ�����ַ�����β����ַ���
����ÿ��λ�ü����ex[i](���İ뾶)����ô����1~i+ex[i](�е�����)���ȵĻ��Ĵ�����Ҫ����������+1 
����ֻ��Ҫ���õ�cnt[]����(��Ӧ���Ȼ��Ĵ��ĸ���)�����Խ�����Ӳ�֣����ǰ׺�͡�
�Ӵ�Сö�ٳ��� ����˾ͺ��� 
*/
#include <cstdio>
#include <algorithm>
#define rg register
#define mod 19930726
typedef long long LL;
const int N=1e6+7;

int n,ex[N];
LL K,cnt[N];
char s[N];

void Manacher()
{
	int mx=0,id;
	for(int i=1; i<=n; ++i)
	{
		if(i<mx) ex[i]=std::min(ex[2*id-i],mx-i);
		else ex[i]=1;
		while(s[i-ex[i]]==s[i+ex[i]]) ++ex[i];
		if(i+ex[i]>mx) mx=i+ex[id=i];
		--cnt[2*ex[i]];
	}
//	for(int i=1; i<=n; ++i) printf("%d ",ex[i]);putchar('\n');
}
LL FP(LL x,int k)
{
	LL t=1;
	for(; k; k>>=1,x=x*x%mod)
		if(k&1) t=t*x%mod;
	return t;
}

int main()
{
	scanf("%d%lld%s",&n,&K,s+1);
	s[0]='$', s[n+1]='%', Manacher();
	cnt[1]=n;
	for(int i=2; i<=n; ++i) cnt[i]+=cnt[i-1];
//	for(int i=1; i<=n; ++i) printf("%I64d ",cnt[i]);putchar('\n');
	LL res=1;
	for(int i=n&1?n:n-1; i>0; i-=2)
		if(cnt[i])
			if(K>cnt[i]) res=res*FP(i,cnt[i])%mod, K-=cnt[i];
			else {res=res*FP(i,K)%mod, K=0; break;}
	if(K) printf("-1");
	else printf("%lld",res);

	return 0;
}
