/*
6096K	704MS
$Description$
�������ַ������Ȳ�С��k�Ĺ����Ӵ�������
$Solution$
���ht[]���ȼ�ȥk����������������׺A',B'������֮��Ĺ���Ϊmin{ht(A)}(A'��B'ht[]����Сֵ)��
ά��һ��ջ��ջ��ht�ӵ׵����ݼ���
�����ǰ����B�к�׺i��ǰ��A���Ӵ��Ĵ𰸣���ô��¼֮ǰ�ġ�(ht(A))�������ǰ��A��i�Ĺ��ס�
Ȼ��������ջ����ht[i]>ht[top]����ջ���� ������B����𰸣�
��ht[i]<=ht[top]����Ϊ�����Ӵ���min{ht()}��i��ջ��Ҫ������ht[top-1]>=ht[i]��top-1�ĳ�ht[i]������i��ջ(�ڼ��ȥ��ǰ����Ĵ�ht[top]-ht[top-1])��ֱ��ht[top-1]<ht[top] 
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
typedef long long LL;
const int N=2e5+10;

int n,sa[N],ht[N],rk[N],sa2[N],tm[N],sk[N],val[N],bel[N];
char s[N];

void Get_SA()
{
	int *x=rk,*y=sa2,m=260;
	for(int i=0; i<=m; ++i) tm[i]=0;
	for(int i=1; i<=n; ++i) ++tm[x[i]=s[i]+1];
	for(int i=1; i<=m; ++i) tm[i]+=tm[i-1];
	for(int i=n; i; --i)  sa[tm[x[i]]--]=i;
	for(int p=0,k=1; k<n; k<<=1,m=p,p=0)
	{
		for(int i=n-k+1; i<=n; ++i) y[++p]=i;
		for(int i=1; i<=n; ++i) if(sa[i]>k) y[++p]=sa[i]-k;
		for(int i=0; i<=m; ++i) tm[i]=0;
		for(int i=1; i<=n; ++i) ++tm[x[i]];
		for(int i=1; i<=m; ++i) tm[i]+=tm[i-1];
		for(int i=n; i; --i) sa[tm[x[y[i]]]--]=y[i];

		std::swap(x,y), p=x[sa[1]]=1;
		for(int i=2; i<=n; ++i)
			x[sa[i]]=y[sa[i-1]]==y[sa[i]]&&y[sa[i-1]+k]==y[sa[i]+k]?p:++p;
		if(p>=n) break;
	}
	for(int i=1; i<=n; ++i) rk[sa[i]]=i;
	ht[1]=0;
	for(int k=0,p,i=1; i<=n; ++i)
	{
		if(rk[i]==1) continue;
		if(k) --k;
		p=sa[rk[i]-1];
		while(i+k<=n&&p+k<=n&&s[i+k]==s[p+k]) ++k;
		ht[rk[i]]=k;
	}
}

int main()
{
	int k;
	while(scanf("%d",&k),k)
	{
		scanf("%s",s+1); int l=strlen(s+1);
		s[l+1]=1, scanf("%s",s+2+l), n=strlen(s+1);
		Get_SA();
		for(int i=2/*1*/; i<=n; ++i)
		{
			ht[i]-=k-1, bel[i]=sa[i]>l;
			if(ht[i]<0) ht[i]=0;
		}
		LL res=0,tmp;
		val[0]=-1, ht[n+1]=0;
		for(int top,t=0; t<=1; ++t)
		{
			tmp=0, top=0;
			for(int i=2/*1*/; i<=n; ++i)//ht[1]���ǲ����ַ� ���㲻���㶼�� 
			{//����Ҫ���ϵ�n���ַ�  
				if(bel[i]!=t) res+=tmp;
				sk[++top]=bel[i]==t;
				val[top]=ht[i+1];//�������i+1��i�����Ĺ��� 
				tmp+=(LL)sk[top]*val[top];
				while(val[top-1]>=val[top])
				{
					--top;
					tmp-=(LL)(val[top]-val[top+1])*sk[top];//��ȥ֮ǰ����Ĺ��� 
					val[top]=val[top+1], sk[top]+=sk[top+1];
				}
			}
		}
		printf("%lld\n",res);
	}
	return 0;
}
