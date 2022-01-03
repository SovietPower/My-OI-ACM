/*
795ms	41500KB
$Description$
��$n$���˶�Ҫ�μӿ��ԣ�ÿ���˿�����$ai$��$bi$�쿼�ԣ�ͬһ�첻���������˿��ԡ��������Ե��˵�ʱ���������Ƕ��١��޽����-1��
$Solution$
��ÿ������$ai,bi$���ߡ�����ÿ����ͨ�鵥�����ǡ�
�ǵ���Ϊn������Ϊm�����Է��ֵ�ĳһ��ͨ��n>m(n=m+1)ʱ��������һ���㲻ѡ(����)��
��n=mʱ�����е㶼Ҫѡ��n<mʱ���޽⡣
�ò��鼯ά����ͨ��˳��ά����󡢴δ�ֵ������һ�γ��ֻ�ʱ����n=m���ڶ��γ��־��޽�(n<m)�ˡ�
��ɢ������д��Hashʡ��log��
��ô�����⻹�ǲ�ȥ�����ߡ���
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
//#define MAXIN 200000
//#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
const int N=2e6+5;

int ref[N],A[N>>1],B[N>>1],fa[N],mx[N],smx[N];
bool tag[N];
//char IN[MAXIN],*SS=IN,*TT=IN;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline int Find(int x,int r)
{
	int l=1,mid;
	while(l<r)
		if(ref[mid=l+r>>1]<x) l=mid+1;
		else r=mid;
	return l;
}
inline int Getfa(int x)
{
	return x==fa[x]?x:fa[x]=Getfa(fa[x]);
}

int main()
{
	int n=read(),t=0;
	for(int i=1; i<=n; ++i) ref[++t]=A[i]=read(),ref[++t]=B[i]=read();
	std::sort(ref+1,ref+1+t); int cnt=1;
	for(int i=2; i<=t; ++i) if(ref[i]!=ref[i-1]) ref[++cnt]=ref[i];

	for(int i=1; i<=cnt; ++i) fa[i]=i,mx[i]=ref[i];
	for(int i=1,x,y,r1,r2; i<=n; ++i)
	{
		x=Find(A[i],cnt), y=Find(B[i],cnt);
		if((r1=Getfa(x))!=(r2=Getfa(y)))
		{
			fa[r2]=r1, tag[r1]|=tag[r2];//!
			if(mx[r2]>mx[r1]) smx[r1]=std::max(mx[r1],smx[r2]), mx[r1]=mx[r2];
			else smx[r1]=std::max(smx[r1],mx[r2]);
		}
		else if(tag[r1]) return puts("-1"),0;
		else tag[r1]=1;
	}
	int ans=0;
	for(int i=1; i<=cnt; ++i)
		if(fa[i]==i)
			if(tag[i]) ans=std::max(ans,mx[i]);
			else ans=std::max(ans,smx[i]);
	printf("%d\n",ans);

	return 0;
}
