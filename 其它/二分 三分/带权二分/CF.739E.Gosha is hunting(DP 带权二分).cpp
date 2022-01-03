/*
46ms    0KB
$Description$
��$n$ֻ���飬���־����򣨸߼��͵ͼ�����ÿ�����ܲ�׽����$i$ֻ����ĸ�����֪������$A$���ͼ����$B$���߼����ܲ�׽�������������������
$n\leq10^5$��
$Solution$
��$f[i][a][b]$��ʾǰ$i$ֻ����$a$���ͼ���$b$���߼�������������ת��ʱ���������Ȼ�����Ӷ�$\mathcal O(nAB)$��
����ĳ�����ʹ���������࣬fӦ��͹������������Խ��Խ������������������������ʡ�
���ǿ���wqs������wqs�����ˡ���
û�и������ƵĻ���ȡ��$\max$����һ�¸����Ϳ����ˡ����Ӷ�$\mathcal O(nlog^2n)$��

���$\leq 10^{-4}$����Ϊ���Ҫ$*A/B$������$eps$Ӧ��$10^{-8}$...��

~~������ȡ$r$�о���̫������~~
**[Update] 19.2.11**
���ֵ�ʱ��ֻҪ��֤ǡ��ȡ��$k$���Ϳ����ˣ�б�ʾ����Ƕ�������ν��������$r$������ȷ��λ��...
Ӧ������ô����...

**�ܽ᣺�������Ŵ���/����֮������ƣ�����ʹ�ô�Ȩ������������һ���ƣ��Ӷ����Խ��м򵥵Ŀ���DP��**
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
#define eps (1e-12)
const int N=2003;

int n,A,B,na[N],nb[N];
double pa[N],pb[N],Ans;

void Solve(double ca,double cb)
{
	na[0]=nb[0]=0;
	double las=0, now;
	for(int i=1; i<=n; ++i, las=now)
	{
		now=las, na[i]=na[i-1], nb[i]=nb[i-1];
		if(las+pa[i]-ca>now) now=las+pa[i]-ca, na[i]=na[i-1]+1;
		if(las+pb[i]-cb>now) now=las+pb[i]-cb, nb[i]=nb[i-1]+1, na[i]=na[i-1];
		if(las+pa[i]+pb[i]-pa[i]*pb[i]-ca-cb>now)//1-(1-pa)(1-pb)
			now=las+pa[i]+pb[i]-pa[i]*pb[i]-ca-cb, na[i]=na[i-1]+1, nb[i]=nb[i-1]+1;
	}
	Ans=now;
}

int main()
{
	scanf("%d%d%d",&n,&A,&B);
	for(int i=1; i<=n; ++i) scanf("%lf",&pa[i]);
	for(int i=1; i<=n; ++i) scanf("%lf",&pb[i]);
	double l1=0,r1=1,mid1,l2,r2,mid2;//ÿ����0/1��Ȩֵ�Ϳ����˰� 
	while(r1>=l1+eps)
	{
		mid1=(l1+r1)*0.5;
		l2=0, r2=1;
		while(r2>=l2+eps)
		{
			if(Solve(mid1,mid2=(l2+r2)*0.5),nb[n]>B) l2=mid2;
			else r2=mid2;
		}
		if(Solve(mid1,r2),na[n]>A) l1=mid1;//���ſ��е���r2����������l2����
		else r1=mid1;
	}
	Solve(r1,r2);//���Checkһ��r����
	printf("%.5lf",Ans+A*r1+B*r2);

	return 0;
}
