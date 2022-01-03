/*
�ֿ顣���ڿ�֮��ģ������޸ġ���ѯ��
����һ�����ڵģ��޸ĺ�sortʹÿһ�������ѯ��ʱ����>=C��λ������� 
*/
#include<cmath>
#include<cstdio>
#include<cctype>
#include<algorithm>
using namespace std;
const int N=1e6+5;

int n,m,A[N],bel[N],size,blo[N],tag[N];//����Ҫ����ģ�Ҫ��ԭ����ֿ� 

inline int read()
{
	int now=0,f=1;register char c=getchar();
	for(;!isdigit(c);c=getchar())
	  if(c=='-') f=-1;
	for(;isdigit(c);now=now*10+c-'0',c=getchar());
	return now*f;
}

void Reset(int p)
{
	int l=(p-1)*size+1,r=min(p*size,n);//ע��ȡmin ��Ҫ���߽磡
	for(int i=l;i<=r;++i)
		blo[i]=A[i];
	sort(blo+l,blo+1+r);//��֤һ���е�Ԫ������ 
}
void Add(int l,int r,int v)
{
	int t=min(r,bel[l]*size);
	for(int i=l; i<=t; ++i)
		A[i]+=v;
	Reset(bel[l]);
	if(bel[l]!=bel[r])
	{
		for(int i=(bel[r]-1)*size+1; i<=r; ++i)
			A[i]+=v;
		Reset(bel[r]);
	}
	for(int i=bel[l]+1; i<bel[r]; ++i)
		tag[i]+=v;
}
int Find(int p,int x)//�ҵ���һ�� >= x ��λ�� 
{
	int l=(p-1)*size+1, r=min(p*size,n), m, R=r;
	while(l<=r)
	{
		m=l+r>>1;
		if(blo[m]<x) l=m+1;
		else r=m-1;
	}
	return R-l+1;
}
int Query(int l,int r,int v)
{
	int res=0, t=min(r,bel[l]*size);
	for(int i=l; i<=t; ++i)
		if(A[i]+tag[bel[l]]>=v) ++res;//�����˼ӿ�ı��tag 
	if(bel[l]!=bel[r])
		for(int i=(bel[r]-1)*size+1; i<=r; ++i)
			if(A[i]+tag[bel[r]]>=v) ++res;
	for(int i=bel[l]+1; i<bel[r]; ++i)
		res+=Find(i,v-tag[i]);//��ѯһ�����ֵʱ��Ҫ��ȥ��ļӱ�� 
	return res;
}

int main()
{
	n=read(),m=read();size=sqrt(n);
	for(int i=1;i<=n;++i)
		A[i]=read(), bel[i]=(i-1)/size+1;
	for(int i=1;i<=bel[n];++i)//������blo�ĳ�ֵ 
		Reset(i);
	char opt[3];int l,r,v;
	while(m--)
	{
		scanf("%s",opt);l=read(),r=read(),v=read();
		if(opt[0]=='M')
			Add(l,r,v);
		else
			printf("%d\n",Query(l,r,v));
	}

	return 0;
}
