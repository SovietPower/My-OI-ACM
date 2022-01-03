/*
��ǰ׺�ͣ��ж�һ�κ��ƽ������������ (sum[n]-sum[r]+sum[l-1])/(n-r+l-1)
���ִ�����СֵΪt�����и��Ž� (sum[n]-sum[r]+sum[l-1])/(n-r+l-1) < t 
-> sum[n]-sum[r]+sum[l-1] < nt - rt + lt - t 
-> (sum[n]-nt) - (sum[r]-rt) + (sum[l-1]-(l-1)) < 0
-> (sum[n]-nt) < (sum[r]-rt) - (sum[l-1]-(l-1))
�� b[i] = sum[i] - i*t,������ж��Ƿ���һ�� b[l]~b[r] > b[n] 
O(n^2)ö��l��r�϶��ǲ��еģ���¼һ��ǰ׺��Сֵ�ͺ�׺���ֵ��ע����β����ѡ 
Ҳ���Բ�����b[]��������ֵ���飬��ǰ��������Сֵ��ÿ���õ�ǰ�ļ���Сֵ�ж�һ�£��ٸ�����Сֵ���� 

Ҫ������λС������ l rƫ��<1e-4����ΪҪ�ڵ���λ�������룬��Ҫ����ȷ 
*/
#include<cstdio>
#include<cctype>
#include<algorithm>
using namespace std;
const int N=1e5+5;

int n,sum[N];
//double b[N],Min[N],Max[N];

inline int read()
{
	int now=0,f=1;register char c=getchar();
	for(;!isdigit(c);c=getchar())
	  if(c=='-') f=-1;
	for(;isdigit(c);now=now*10+c-'0',c=getchar());
	return now*f;
}

//bool Check(double x)
//{
//	for(int i=1;i<=n;++i)
//		b[i]=1.0*sum[i]-1.0*i*x;
//	Min[1]=b[1], Max[n-1]=b[n-1];
//	for(int i=2;i<n-1;++i)//��С�� b[l-1] 
//		Min[i]=min(Min[i-1],b[i]);
//	for(int i=n-2;i;--i)//���� b[r] 
//		Max[i]=max(Max[i+1],b[i]);
//	for(int i=2;i<n;++i)
//		if(Max[i]-Min[i-1]>b[n]) 
//			return 1;
//	return 0;
//}
bool Check(double x)
{
	double Min=1.0*sum[1]-x, cmp=1.0*sum[n]-n*x;;
	for(int i=2;i<n;++i)
	{
		if(1.0*sum[i]-i*x-Min > cmp) return 1;
		Min=min(Min,1.0*sum[i]-i*x);
	}
	return 0;
}

int main()
{
//	freopen("testdata.in","r",stdin);
//	freopen("2115.txt","w",stdout);

	n=read();
	for(int i=1;i<=n;++i)
		sum[i]=sum[i-1]+read();
	double l=1.0,r=1.0*sum[n],m;//r������sum[n]/n��ʵ�ʴ𰸿��ܱ����� 
	while(r-l>0.00001)
	{
		m=(l+r)/2.0;
		if(Check(m)) r=m;
		else l=m;
	}
	printf("%.3lf",r);

	return 0;
}
