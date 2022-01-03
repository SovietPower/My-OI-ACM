/*
$Description$
����һ����Ϊn�����У��Լ�n�������������漰����ѯ�ʵ���һ����c��Ԫ�أ�����������������Ԫ�ظ�Ϊc��
$Solution$
ģ��һЩ���ݿ��Է��֣�ѯ�ʺ�һ���ζ��ᱻ�޸ģ�����ѯ�ʺ����п���ֻʣ�¼��β�ͬ�������ˡ�
��ô���Ǳ�����ÿ����ά�������������Ƿ����һ��Ȩֵ���ǡ���ѯʱ������ͬȨֵ�Ŀ�Ϳ���O(1)ͳ�ƣ�������ͳ�Ʋ��޸Ĵ𰸣��������Ŀ鱩���� 
����������������ÿ����ҪO(n)��ʱ�䣬��ʵ��ԶԶ������ 
�����ʼ���ж���ͬһ��ֵ����ô��ѯ��ҪO(sqrt(n))�������ʱ���������޸ģ���ô�����ƻ���β������ı�� 
����ֻ��ʹ�����ѯ�������2����ı���ʱ�䣬���Ծ�̯ÿ�β������Ӷ�ΪO(sqrt(n)) 
���仰˵��Ҫ����һ�������ķ�O(n)��ʱ�䣬Ҫ�Ȼ���sqrt(n)�������޸����� 
--by hzwer
*/
#include <cmath>
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
const int N=1e5+5,MAXIN=1e6;

int n,size,sizen,A[N],tag[2000],bel[N],L[2000],R[2000];
bool cover[2000];
char IN[MAXIN],*SS=IN,*TT=IN;

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=gc()) if(c=='-') f=-1;
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}
int Count(int l,int r,int v)
{
	int res=0;
	for(int i=l; i<=r; ++i)
		if(A[i]==v) ++res; else A[i]=v;
	return res;
}
void Reset(int p,int l,int r,int vbef,int v)
{//Reset [L(p),l)&&(r,R(p)] to vbef,[l,r] to v
	for(int i=L[p]; i<l; ++i) A[i]=vbef;
	for(int i=l; i<=r; ++i) A[i]=v;
	int t=std::min(n,R[p]);
	for(int i=r+1; i<=t; ++i) A[i]=vbef;
	cover[p]=0;
}
int Get_scatter(int l,int r,int v)
{
	if(cover[bel[l]])
		if(tag[bel[l]]==v) return r-l+1;
		else Reset(bel[l],l,r,tag[bel[l]],v);
	else return Count(l,r,v);
	return 0;
}
int Query(int l,int r,int v)
{
	int res=Get_scatter(l,std::min(r,R[bel[l]]),v);

	if(bel[l]!=bel[r]) res+=Get_scatter(L[bel[r]],r,v);

	for(int i=bel[l]+1; i<bel[r]; ++i)
		if(cover[i])
			if(tag[i]==v) res+=bel[l]==bel[n]?sizen:size;
			else tag[i]=v;
		else
			res+=Count(L[i],R[i],v), cover[i]=1, tag[i]=v;
	return res;
}

int main()
{
	n=read(), size=sqrt(n);
	for(int i=1; i<=n; ++i) bel[i]=(i-1)/size+1, A[i]=read();
	for(int i=1; i<=bel[n]; ++i) L[i]=(i-1)*size+1,R[i]=i*size;
	sizen=n-(bel[n]-1)*size;
	for(int l,r,c,i=1; i<=n; ++i)
		l=read(), r=read(), c=read(), printf("%d\n",Query(l,r,c));
	return 0;
}
