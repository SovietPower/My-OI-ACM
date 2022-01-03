/*
19768kb	5976ms
$Description$
����������$S,T$����$T$��$S$�г����˶��ٴΡ�������ָ��������$3$�Σ�$3$���ַ�����ƥ�䣨�޸�ʹ��ƥ�䣩��
$Solution$
һ����·�������ǹ������ʽ����ÿ���ַ�c�������ǣ�$f[i]=[S[i]��ƥ��c],g[i]=[T[i]==c]$��
Ȼ��$F=f*g$�����Եõ�ÿ��λ������m�Ĵ����ж��ٸ�λ��S,T��ƥ����c�����ĳ��λ��ƥ���ַ���>=m-3��������Ϊ��˵�Ĵ����С�
FFT/NTTʵ�֣�������Ҳ���ܹ���
SA������ö��S��ÿ��λ��i���赱ǰƥ��Tƥ�䵽j���õ���������ht��������ǿ���$O(1)$���LCP(suf[i],suf[j])��ֱ��j+=LCP�����ˡ�
���ĳ��λ�ò�ƥ�䣬����������3�λ���ֱ������ȥ������ʵ��ö��j�Ĵ���ֻ��5��
���Ӷ�$O(Tn\log n)$��
SAM�������õ�parent����ֱ��������DFS�������ƥ�����ߣ�����ƥ������һ�δ���������m������ϸõ�Ĺ���(���ֹ����ٴ�)��
���Ӷ�$O(T*Cn)$($C$Ϊ�ַ�����С)��
����ĳ�������Hash�������������ӶȱȽ��š�
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
const int N=2e5+7;

int MAP[233],sa[N],sa2[N],rk[N],tm[N],ht[N],lg2[N],mn[18][N];
char s[N];

void Get_SA(int n)
{
	int *x=rk,*y=sa2,m=5;
	for(int i=0; i<=m; ++i) tm[i]=0;
	for(int i=1; i<=n; ++i) ++tm[x[i]=MAP[s[i]]];
	for(int i=1; i<=m; ++i) tm[i]+=tm[i-1];
	for(int i=n; i; --i) sa[tm[x[i]]--]=i;
	for(int k=1,p=0; k<n; k<<=1,m=p,p=0)
	{
		for(int i=n-k+1; i<=n; ++i) y[++p]=i;
		for(int i=1; i<=n; ++i) if(sa[i]>k) y[++p]=sa[i]-k;

		for(int i=0; i<=m; ++i) tm[i]=0;
		for(int i=1; i<=n; ++i) ++tm[x[i]];
		for(int i=1; i<=m; ++i) tm[i]+=tm[i-1];
		for(int i=n; i; --i) sa[tm[x[y[i]]]--]=y[i];

		std::swap(x,y), x[sa[1]]=p=1;
		for(int i=2; i<=n; ++i)
			x[sa[i]]=(y[sa[i]]==y[sa[i-1]]&&y[sa[i]+k]==y[sa[i-1]+k])?p:++p;
		if(p>=n) break;
	}
	for(int i=1; i<=n; ++i) rk[sa[i]]=i;
	ht[1]=0;
	for(int i=1,k=0,p; i<=n; ++i)
	{
		if(rk[i]==1) continue;
		if(k) --k;
		p=sa[rk[i]-1];
		while(i+k<=n && p+k<=n && s[i+k]==s[p+k]) ++k;
		ht[rk[i]]=k;
	}
}
void Init_ST(int n)
{
	for(int i=1; i<=n; ++i) mn[0][i]=ht[i];
	for(int j=1; j<=lg2[n]; ++j)
		for(int i=1; i<=n; ++i)
			mn[j][i]=std::min(mn[j-1][i],mn[j-1][i+(1<<j-1)]);
}
inline int LCP(int l,int r)
{
	l=rk[l], r=rk[r]; if(l>r) std::swap(l,r);
	++l;
	int k=lg2[r-l+1];
	return std::min(mn[k][l],mn[k][r-(1<<k)+1]);
}

int main()
{
	MAP['A']=1, MAP['T']=2, MAP['C']=3, MAP['G']=4, MAP['Z']=5;
	lg2[1]=0;
	for(int i=2; i<=200005; ++i) lg2[i]=lg2[i>>1]+1;

	int T; scanf("%d",&T);
	while(T--)
	{
		int l,n;
		scanf("%s",s+1), s[l=strlen(s+1)+1]='Z';
		scanf("%s",s+l+1), n=strlen(s+1);
		Get_SA(n), Init_ST(n);
		int ans=0;
		for(int i=1,m=n-l,lim=l-m; i<=lim; ++i)
		{
			for(int j=1,t=0; t<=3; )
			{
				if(j>m) {++ans; break;}
				else if(s[i+j-1]!=s[l+j]) ++j, ++t;
				else j+=LCP(i+j-1,l+j);
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}
