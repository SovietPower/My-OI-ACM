/*
61ms	7700KB
���ְ뾶r�����Ƿ��ְ뾶ȷ����Բ�ĵ�������Ҳȷ������y=r�ϣ���
��������Ҫ���Ƿ����Բ����y=r�ϵĸ������е��Բ����ÿ���㻭һ���뾶Ϊr��Բ��������Ҫ��y=r����ֱ�����н���
ÿ��Բ��y=r��������������ù��ɶ��������������ת�������Ƿ��н������⡣��������Ҷ˵�����ҵ���˵�����ˡ�
��ΪҪ��x�����У����԰뾶���ܷǳ����ù��ɶ�����Եõ������5e13+����Ϊ��Χ�ϴ�ע������������
*/
#include <cmath>
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
#define MAXIN 200000
//#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=1e6+6;

int n,x[N],y[N];
char IN[MAXIN],*SS=IN,*TT=IN;

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}
bool Check(double r)
{
	double L=-1e18,R=1e18,tmp;
	for(int i=1; i<=n; ++i)
	{
		if(r+r<y[i]) return 0;
		tmp=sqrt(1.0*(r+r-y[i])*y[i]);
		L=std::max(L,-tmp+x[i]), R=std::min(R,tmp+x[i]);
		if(L>R) return 0;
	}
	return 1;
}

int main()
{
	n=read(); int cnt=0;
	for(int i=1; i<=n; ++i) x[i]=read(),y[i]=read(),cnt+=(y[i]<0);
	if(cnt)
	{
		if(cnt!=n) return puts("-1"),0;
		for(int i=1; i<=n; ++i) y[i]=-y[i];
	}
	double l=0,r=1e14,mid;
	for(int T=80; T--; )
	{
//		if(l>1 && l+1>r) mid=sqrt(l*r);//����ƽ��������ôдô����
//		else mid=(l+r)*0.5;
		if(Check(mid=(l+r)*0.5)) r=mid;
		else l=mid;
	}
	printf("%.7lf\n",l);

	return 0;
}
