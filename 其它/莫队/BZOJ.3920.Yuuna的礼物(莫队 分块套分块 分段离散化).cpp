/*
$Description$
����һ����Ϊn�����У�ÿ�β�ѯ�����г��ִ���k1С���������k2С���������ռ䡣
$Solution$
�����ִ�����Ȩֵ�ֿ飬��������ʵ��O(1)���룬O(sqrt(n))��ѯ��k1С�ĳ��ִ��� 
���ǻ���Ҫ֪����k2С��ֵ������ÿ����ά����ĸ�����ƽ���������������븴�ӶȻ��� 
ͬ��������ÿ������ÿ���ڵ�����һ��Ȩֵ�ֿ飬ͬ���ܹ�O(1)���� 
����Ȩֵ�ֿ�Ĵ�С���ϸ�ֵ��ģ������ִ���Ϊi��ֵ�����ܳ�����i��������ռ��޷����� 
������Ҫ�ֶ���ɢ�������ڿ�i���ó��ִ���>=i��Ax������ɢ����
��tmi=n�����Կռ���O(n)�ģ�ʱ�临�Ӷ�O(m*sqrt(n))(֤��:https://www.cnblogs.com/autsky-jadek/p/4376091.html)
ϸ�ڡ���
*/
#include <cmath>
#include <cstdio>
#include <cctype>
#include <vector>
#include <algorithm>
#define gc() getchar()
#define pb push_back
typedef unsigned short ushort;
const int N=40005;

ushort n,size,m,A[N],B[N],bel[N],Ans[N];
int sz1[N],sum1[N],tm[N];//�������и� 
std::vector<ushort> sum2[N]/*ĳ���д���ĳ��*/,ref[N],rank[N]/*ĳ������ĳ���е�λ��*/,sz2[N];
struct Ask
{
	int l,r,k1,k2,id;
	bool operator <(const Ask &a)const
	{
		return bel[l]==bel[a.l]? r<a.r : bel[l]<bel[a.l];
//		return bel[l]==bel[a.l]? ((l-1)/size&1 ? r>a.r : r<a.r) : bel[l]<bel[a.l];
	}
}q[N];

inline ushort read()
{
	ushort now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
int Get_Pos1(int p)//�ҵ�k1���ڴ�顢and ��������ŵ��Ǹ���
{
	int x=1;
	for(int i=1; i<=bel[n]; ++i)
		if((p-=sz1[i])<=0) {p+=sz1[x=i]; break;}
	for(int tmp=std::min((int)n,x*size-1),i=(x-1)*size; i<=tmp; ++i)
		if(!(p-=(sum1[i]>0))) return i;
}
int Get_Pos2(int id,int p)
{
	int x=1;
	for(int i=1; i<sum2[id].size(); ++i)//������<bel[sum2[id].size()]������ֱ��<size���������϶������ 
		if((p-=sz2[id][i])<=0) {p+=sz2[id][x=i]; break;}
	for(int tmp=std::min((int)sum2[id].size(),x*size),i=(x-1)*size; i<tmp; ++i)//ע��vector�ı߽� 
		if(!(p-=sum2[id][i])) return i;
}
int Query(int k1,int k2)
{
	int id=Get_Pos1(k1);
	return ref[id][Get_Pos2(id,k2)];
}
inline void Update(int p,int delta)//����tm[p]>0(����if(tm[p]))ʱ�ӣ� 
{//�޸Ŀ��ڵĿ� 
	sum1[tm[p]]+=delta;//ͬ�� ���ҲҪ���� 
	if(sum1[tm[p]] && delta==1) ++sz1[bel[tm[p]]];
	if(!sum1[tm[p]] && delta==-1) --sz1[bel[tm[p]]];
	int pos=rank[p][tm[p]-1];//������ͬ����γ�������λ�ڲ�ͬ�Ŀ飬so ���ִ����Ͳ��ù��� 
	sz2[tm[p]][bel[pos]]+=delta, sum2[tm[p]][pos]+=delta;
}
inline void Modify(int p,int delta)
{
	if(tm[p]>0) Update(p,-1);//Ҫ��ԭ�ȵĴ���ɾ�� 
	tm[p]+=delta;
	if(tm[p]>0) Update(p,1);
}
//inline void Add(int p)//WA: û�а�֮ǰ��sz1���� 
//{
//	if(tm[p]>0) Update(p,-1);//Ҫ��ԭ�ȵĴ���ɾ�� 
//	++tm[p];
//	if(++sum1[tm[p]]==1) ++sz1[bel[tm[p]]];//��������Ŀ� ÿ�����ִ���ֻ����һ��
//	if(tm[p]>0) Update(p,1);
//}
//inline void Subd(int p)
//{
//	if(tm[p]>0) Update(p,-1);
//	if(!--sum1[tm[p]]) --sz1[bel[tm[p]]];
//	if(--tm[p]>0) Update(p,1);//����-1��ļ��� 
//}

int main()
{
	n=read(), size=sqrt(n);
	bel[0]=1;//����bel[0]��vectorʹ 
	for(int i=1; i<=n; ++i) A[i]=B[i]=read(),++tm[A[i]],bel[i]=i/size+1;//ȫ��0��ʼ�ֿ������ 
	std::sort(B+1,B+1+n);
	for(int i=1; i<=n; ++i)//Discrete
	{
		for(int j=1; j<=tm[B[i]]; ++j)
			sum2[j].pb(0), rank[B[i]].pb(ref[j].size()), ref[j].pb(B[i]);
		tm[B[i]]=0;//ȥ�� 
	}
	for(int i=1; i<=n; ++i)
		for(int j=0; j<=bel[sum2[i].size()]; ++j) sz2[i].pb(0);//<=!
	m=read();
	for(int i=1; i<=m; ++i)
		q[i].l=read(),q[i].r=read(),q[i].k1=read(),q[i].k2=read(),q[i].id=i;
	std::sort(q+1,q+1+m);
	for(int l=1,r=0,i=1; i<=m; ++i)
	{
		while(l<q[i].l) Modify(A[l++],-1);
		while(l>q[i].l) Modify(A[--l],1);
		while(r<q[i].r) Modify(A[++r],1);
		while(r>q[i].r) Modify(A[r--],-1);
		Ans[q[i].id]=Query(q[i].k1,q[i].k2);
	}
	for(int i=1; i<=m; ++i) printf("%d\n",Ans[i]);

	return 0;
}
