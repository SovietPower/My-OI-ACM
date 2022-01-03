/*
1228kb	28ms
������ȷ����ôans = (n-2)!/[(d1-1)!(d2-1)!...(dn-1)!] 
���ڰ���Щ��ȷ���ĵ�һ����(������m��)��������Prufer�������ܳ���������left=n-2-(d1-1)-(d2-1)-...-(dn-1)
��left������������m^{left}�� 
���� ans = (n-2)!/[(d1-1)!(d2-1)!...(dn-1)!left!]*m^{left} 
��Ȼ��Ҫ�߾��ȡ�Ϊ����߾�����Ҫ��ÿ���׳˷ֽ�������(�������������һ�������������Էֽ��������ͷ��Ӽ�����ĸ�Ĵ�������)
n!�к�������p������ʽ: f(n)=f(n/p)+n/p 
ע�����޽��������� 
Ҫ�˵�����С �������� 
*/
#include <cstdio>
const int N=1005,Base=10000;

int n,dgr[N],up[N],down[N],cnt,P[N],ans[100005];
bool Not_P[N+3];

void Init()
{
	Not_P[1]=1;
	for(int i=2; i<N; ++i)
	{
		if(!Not_P[i]) P[++cnt]=i;
		for(int j=1; j<=cnt&&i*P[j]<N; ++j)
		{
			Not_P[i*P[j]]=1;
			if(!(i%P[j])) break;
		}
	}
}
void Divide(int x,int *a)
{
	for(int i=1; i<=cnt&&P[i]<=x; ++i)
		for(int tmp=x; tmp; tmp/=P[i]) a[i]+=tmp/P[i];
}
void Mult(int *a,int b)
{
	for(int i=1; i<=a[0]; ++i) a[i]*=b;
//		if(a[i]/Base) a[i+1]+=a[i]/Base, a[i]%=Base;//��Ҫ��������ٽ�λ 
	for(int i=1; i<=a[0]; ++i)
		if(a[i]/Base) a[i+1]+=a[i]/Base, a[i]%=Base;
//		else break;//WA:��Ȼ�������� 
	if(a[a[0]+1]) ++a[0];
}
void Print(int *a)
{
	printf("%d",a[a[0]]);
	for(int i=a[0]-1; i; --i) printf("%0*d",4,a[i]);
//	putchar('\n');
}

int main()
{
	scanf("%d",&n), Init();
	int tot=0,m=0;
	for(int i=1; i<=n; ++i)
	{
		scanf("%d",&dgr[i]);
		if(dgr[i]>1) tot+=dgr[i]-1, Divide(dgr[i]-1,down);
		else if(dgr[i]<0) ++m;
		else if(!dgr[i]) tot=N;
	}
	if(tot>n-2 || (tot==n-2&&!m)) {putchar('0'); return 0;}
	int left=n-2-tot;
	Divide(n-2,up), Divide(left,down);
	for(int i=1; i<=cnt; ++i) up[i]-=down[i];
//	for(int i=1; i<=cnt; ++i) printf("%d^%d\n",P[i],up[i]);
	ans[ans[0]=1]=1;
	for(int i=1; i<=cnt; ++i)
		while(up[i]--) Mult(ans,P[i]);
	for(int i=1; i<=left; ++i) Mult(ans,m);
	Print(ans);

	return 0;
}
