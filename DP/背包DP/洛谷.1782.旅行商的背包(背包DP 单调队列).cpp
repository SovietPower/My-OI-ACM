/*
���صĶ��ر�����: f[i][j] = max{ f[i-1][j-k*v[i]]+k*w[i] }�����Ӷ�O(nV*��num_i) 
���Է�����maxʱ�кܶ�ֵ�Ǳ��ظ�ö�ٹ��� 
��һ�ַ��̱�ʾ��ʽ������ÿ��v[i]����j=K*v[i]+r, K=j/v[i], r=j%v[i]��������%v[i]�������ֱ����dp 
ö��k=0~K-1����ô f[i][j] = max{ f[i-1][k*v[i]+r]-k*w[i] } + K*w[i]
������һ���ֿ����õ�������ά����
���Ӷȴ�ž���O(nV)��������ö���൱�ڰ�0~V������һ����ֻ��һ�顣
��������Ʋ��Ҳ���������Ӷ�O(nV*��log(num_i))��������������� num_i���ܱȽ�С����log(num_i)������O(n)�� 
���ַ���������С�����Աȵ������л��� 
��һ���������ֻ��5��ֱ��V^2��������
ע�⵱ǰö�ٵ����now������������: ����������ֵ�����(�õ�����k_h)+��ǰ��Ʒ������(��������num)<��ǰö�ٵ����(k)ʱ��Ҫ�������� 
�������ֱ�����f[V]?�Ҿ��ò�̫�԰��������m����Ʒһ���������Ȩֵ��
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
const int N=1e4+5;

int n,m,V,f[N],q[N],nm[N];

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=gc()) if(c=='-') f=-1;
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}

int main()
{
	n=read(),m=read(),V=read();
	for(int v,w,num,now,tmp,i=1; i<=n; ++i)
	{
		v=read(),w=read(),num=read();
		for(int j=0; j<v; ++j)
			for(int k=0,h=1,t=0; (now=k*v+j)<=V; ++k)//now:��ǰ��� 
			{
				tmp=f[now]-k*w;
				while(h<=t && q[t]<tmp) --t;
				nm[++t]=k, q[t]=tmp;
				if(nm[h]+num<k) ++h;//ÿ�ν��ᵯ��һ��Ԫ�� 
				f[now]=q[h]+k*w;
			}
	}
	for(int a,b,c,i=1; i<=m; ++i)
	{
		a=read(),b=read(),c=read();
		for(int j=V; j; --j)
			for(int k=0; k<=j; ++k)
				f[j]=std::max(f[j],f[j-k]+(a*k+b)*k+c);
	}
//	int res=f[1];
//	for(int i=2; i<=V; ++i) res=std::max(res,f[i]);
	printf("%d",f[V]);

	return 0;
}
