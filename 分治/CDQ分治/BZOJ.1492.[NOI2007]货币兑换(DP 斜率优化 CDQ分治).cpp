/*
12648kb	792ms
���ĳ���ܹ�׬Ǯ����ôһ��������������ϵĽ�ȯȫ������ͬ�����ĳ��Ҫ��һ���������Ǯ���⡣
��ô��$f_i$��ʾ����$i$����ӵ�е����Ǯ������ʱ����û���κν�ȯ��������ѡ��ʲô�����ɣ�$f_i=f_{i-1}$��Ҳ���Դ�֮ǰ��ĳһ��$j$��$f_j$��Ǯ���ȯ���ڵ�$i$��ȫ�������õ�$j$�����Ϣ��һ�����˶���$A,B$���Ϳ��Եõ���$i$�����˶���Ǯ��
������$f_i=\max\{f_{i-1},\ A_i\frac{f_jk_j}{A_jk_j+B_j}+B_i\frac{f_j}{A_jk_j+B_j}\}$��
�Ѻ����ǲ���д��ֱ�ߵ���ʽ��$\frac{f_i}{B_i}-\frac{A_i}{B_i}*\frac{f_jk_j}{A_jk_j+B_j}=\frac{f_j}{A_jk_j+B_j}$����$x_j=\frac{A_i}{B_i}*\frac{f_jk_j}{A_jk_j+B_j},\ y_j=\frac{A_i}{B_i}*\frac{f_j}{A_jk_j+B_j}$��$\frac{f_i}{B_i}-\frac{A_i}{B_i}x_j=y_j$��Ҫ����$k=-\frac{A_i}{B_i}$��ֱ��ȥ��$(x_j,y_j)$ʹ�ýؾ����Ҳ����ά����͹�ǡ�
��$x$��ÿ�����ߵ㲻�ǵ����ģ�����Ҫƽ����/CDQ����ȥά��͹����
**CDQ���Σ�**
�Ƚ����е㰴б��$k$����
�ȴ�����������ѯ�ʣ�Ȼ�������䰴������$x$�鲢�ź�����������������ѯ�ʵ�ʱ������ֻ���ǵ�ǰ�����������������ѯ�ʵ�Ӱ�죬Ҳ����Ҫ��������ά����͹�ǣ����������$x$����Ϳ���ֱ���õ���ջ����͹��ά�������ˡ�
���������Ѿ���б��$k$�ź����ˣ����Կ���$O(n)$����͹���еõ����Ž⣨ʵ�ֵ�ǰ������������������ת�ƣ���
���ݹ鵽$l=r$����˵���Ѿ�������õ�$l$֮ǰ�ĵ��$l$��Ӱ���ˣ��Ϳ���ֱ�ӵõ�$f_l$��ֵ��˳��Ҫ��$f_{l-1}$ȡ$\max$��������$l$������ߵ����Ϣ�ˡ�
*/
#include <cmath>
#include <cstdio>
#include <cctype>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 500000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
#define eps 1e-9
typedef long long LL;
const int N=1e5+5;
const double INF=1e17;

double f[N],read();
char IN[MAXIN],*SS=IN,*TT=IN;
struct Node
{
	int id;
	double A,B,k,Rate,x,y;
	inline void Init(int i)
	{
		id=i,A=read(),B=read(),k=-A/B,Rate=read();
	}
	bool operator <(const Node &x)const
	{
		return k<x.k;
	}
}q[N];

inline double read()
{
	double x=0,y=0.1;register char c=gc();
	for(;!isdigit(c)&&c!='.';c=gc());
	for(;isdigit(c);x=x*10+c-'0',c=gc());
	for(c=='.'&&(c=gc());isdigit(c);x+=(c-'0')*y,y*=0.1,c=gc());
	return x;
}
inline double GetK(int i,int j)
{
	return fabs(q[i].x-q[j].x)<=eps?(q[i].y<q[j].y?-INF:INF):(q[i].y-q[j].y)/(q[i].x-q[j].x);
//	return fabs(q[i].x-q[j].x)<=eps?INF:(q[i].y-q[j].y)/(q[i].x-q[j].x);
}
void CDQ(int l,int r)
{
	static int sk[N];
	static Node tmp[N];
	if(l==r)
	{
		f[l]=std::max(f[l],f[l-1]);
		q[l].y=f[l]/(q[l].A*q[l].Rate+q[l].B), q[l].x=q[l].y*q[l].Rate;
		return;
	}
	int mid=l+r>>1,p1=l,p2=mid+1;
	for(int i=l; i<=r; ++i)//��ǰmid��ѯ�ʷ������ ��mid�������ұ� 
		q[i].id<=mid?tmp[p1++]=q[i]:tmp[p2++]=q[i];
	for(int i=l; i<=r; ++i) q[i]=tmp[i];
	CDQ(l,mid);

	int top=0;
	for(int i=l; i<=mid; ++i)
	{
		while(top>=2 && GetK(i,sk[top])>GetK(sk[top],sk[top-1])) --top;
		sk[++top]=i;
	}
	for(int i=mid+1; i<=r; ++i)
	{
		while(top>=2 && GetK(sk[top],sk[top-1])<q[i].k) --top;
		int j=sk[top];
		f[q[i].id]=std::max(f[q[i].id],q[i].A*q[j].x+q[i].B*q[j].y);
	}
	CDQ(mid+1,r);

	p1=l,p2=mid+1; int p=l;//���������������x���� 
	while(p1<=mid && p2<=r) q[p1].x<=q[p2].x?tmp[p++]=q[p1++]:tmp[p++]=q[p2++];
	while(p1<=mid) tmp[p++]=q[p1++];
	while(p2<=r) tmp[p++]=q[p2++];
	for(int i=l; i<=r; ++i) q[i]=tmp[i];
}

int main()
{
	int n=read(); f[0]=read();
	for(int i=1; i<=n; ++i) q[i].Init(i);
	std::sort(q+1,q+1+n), CDQ(1,n);
	printf("%.3lf\n",f[n]);

	return 0;
}
