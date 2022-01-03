/*
1630ms	6.86MB
�ⲻ���Ǹ������������Ĵ���ô������ǿ�����ߣ�ֵ��ֿ���Ī�Ӷ��������õ�Ī�ӡ�
���ִ��������һ������������Ǵ𰸣�������Ѵ���
���Ǵ�Ҫô����Ҫô��-1������һ�³���x�ε��ж��ٸ����������ˡ�
*/
#include <cmath>
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
const int N=2e5+5;

int n,m,A[N],ref[N],bel[N],Ans,tm[N],cnt[N],ans[N];
struct Quries
{
	int l,r,id;
//	Quries() {}
//	Quries(int l,int r,int id):l(l),r(r),id(id) {}//д�˾�ȻӰ�������ˡ���
	bool operator <(const Quries &x)const{
		return bel[l]==bel[x.l]?r<x.r:bel[l]<bel[x.l];
	}
}q[N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
int Find(int x,int r)
{
	int l=1,mid;
	while(l<r)
		if(ref[mid=l+r>>1]<x) l=mid+1;
		else r=mid;
	return l;
}
inline void Add(int p)
{
	--cnt[tm[p]], Ans=std::max(Ans,++tm[p]), ++cnt[tm[p]];
}
inline void Subd(int p)
{
	if(!--cnt[tm[p]] && Ans==tm[p]) --Ans;
	--tm[p], ++cnt[tm[p]];
}

int main()
{
	n=read(), m=read();
	int size=sqrt(n);
	for(int i=1; i<=n; ++i) bel[i]=i/size;
	for(int i=1; i<=n; ++i) ref[i]=A[i]=read();
	std::sort(ref+1,ref+1+n); int cnt=1;
	for(int i=2; i<=n; ++i) if(ref[i]!=ref[i-1]) ref[++cnt]=ref[i];
	for(int i=1; i<=n; ++i) A[i]=Find(A[i],cnt);

	for(int i=1; i<=m; ++i) q[i]=(Quries){read(),read(),i};
	std::sort(q+1,q+1+m);
	for(int l=1,r=0,i=1; i<=m; ++i)
	{
		int ln=q[i].l,rn=q[i].r;
		while(l<ln) Subd(A[l++]);
		while(l>ln) Add(A[--l]);
		while(r<rn) Add(A[++r]);
		while(r>rn) Subd(A[r--]);
		ans[q[i].id]=Ans;
	}
	for(int i=1; i<=m; ++i) printf("%d\n",-ans[i]);

	return 0;
}
