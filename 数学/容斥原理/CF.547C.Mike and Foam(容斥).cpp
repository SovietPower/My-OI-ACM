/*
171ms	4700KB
$Description$
����n����(1<=ai<=5e5)��ÿ�δ���n������ѡһ���������ǰ������û�оͼ��뼯�ϣ��оʹӼ�����ɾȥ��ÿ�β�������������л��ʵ����Ը�����
$Solution$
���Ǳ���һ�㣬����Ҫ�޸ĵ����ֽ����������������������ʵ����ĸ������� n-(��1������������)+(��2������������)-...
ά��һ��ÿ������(�����Ƕ�������Ļ�)��Ӧ�����еĶ��ٸ������С�
��ĺñ�����������һ�����������Ӵ��Ҳ��4.5����so��û����ġ�
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 200000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
const int N=2e5+5,MAX=5e5+3;

int n,Q,A[N],now,have[N],num[MAX],bit[23333],pcnt,P[N],cnt,p[233];
long long Ans;
bool not_P[MAX];
char IN[MAXIN],*SS=IN,*TT=IN;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
void Pre(int n)
{
	for(int i=2; i<=n; ++i)
	{
		if(!not_P[i]) P[++pcnt]=i;
		for(int j=1; j<=pcnt && i*P[j]<=n; ++j)
		{
			not_P[i*P[j]]=1;
			if(!(i%P[j])) break;
		}
	}
	for(int i=1,s=0; i<=5000; ++i,s=0)
	{
		for(int j=0; j<=13; ++j)
			if(i>>j & 1) ++s;
		bit[i]=s;
	}
}
void Div(int x)
{
	cnt=0;
	for(int i=1; i<=pcnt&&P[i]*P[i]<=x; ++i)//P[i]*P[i]<=x not P[i]<=x����Ȼ�ͳ�O(n)���ˣ�
		if(!(x%P[i]))
		{
			p[cnt++]=P[i];
			while(!(x%P[i])) x/=P[i];
		}
	if(x!=1) p[cnt++]=x;
}
void Add(int x,int val)
{
	Div(A[x]);
	long long ans=~val?now++:--now;//���x����Ĳ���Ӱ�� 
	for(int i=1; i<(1<<cnt); ++i)
	{//ö��������ϡ���
		int fac=1;
		for(int j=0; j<cnt; ++j)
			if(i>>j & 1) fac*=p[j];
		if(val==-1) --num[fac];//������x����
		if(bit[i]&1) ans-=num[fac]; else ans+=num[fac];
		if(~val) num[fac]++;
	}
	Ans+=(long long)val*ans;
}

int main()
{
	n=read(), Q=read(); int mx=0;
	for(int i=1; i<=n; ++i) mx=std::max(mx,A[i]=read()), have[i]=-1;
	Pre(mx); int x;
	while(Q--)
		have[x=read()]*=-1, Add(x,have[x]), printf("%I64d\n",Ans);
	return 0;
}
