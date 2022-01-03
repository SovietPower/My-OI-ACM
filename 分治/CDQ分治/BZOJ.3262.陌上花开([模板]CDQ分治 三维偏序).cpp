/*
5904kb	872ms
��������x,y,z��ͬ��Ԫ��Ҫ����ȥ�أ�����¼�������빱��(����֮������Ĵ���һ���ģ�����ȥ�ػᡣ��) 
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
#define lb(x) (x)&-(x)
const int N=1e5+5;

int n,Ans[N];
int read();
struct Operation
{
	int x,y,z,cnt,res;
	inline void Init(){
		x=read(),y=read(),z=read(),cnt=1;
	}
	bool operator <(const Operation &a)const{
		return x==a.x?(y==a.y?z<a.z:y<a.y):x<a.x;
	}
}q[N],tmp[N];

namespace BIT
{//��ά:��״���� 
	int Max,t[N<<1];
	void Add(int p,int v){
		while(p<=Max) t[p]+=v,p+=lb(p);
	}
	int Query(int p){
		int res=0;
		while(p) res+=t[p],p-=lb(p);
		return res;
	}
}
inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=gc()) if(c=='-') f=-1;
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}
void CDQ(int l,int r)
{//����ڶ�ά 
	if(l<r)
	{
		int m=l+r>>1; CDQ(l,m), CDQ(m+1,r);
		int p1=l,p2=m+1,cnt=0;
		while(p1<=m&&p2<=r)
		{
			if(q[p1].y<=q[p2].y)//���������Ҫ��<= 
				BIT::Add(q[p1].z,q[p1].cnt), tmp[cnt++]=q[p1++];
			else 
				q[p2].res+=BIT::Query(q[p2].z), tmp[cnt++]=q[p2++];
		}
		while(p1<=m) BIT::Add(q[p1].z,q[p1].cnt), tmp[cnt++]=q[p1++];//�ȼ��� �����ټ�ȥ 
		while(p2<=r) q[p2].res+=BIT::Query(q[p2].z), tmp[cnt++]=q[p2++];
		for(int i=l; i<=m; ++i) BIT::Add(q[i].z,-q[i].cnt);
		for(int i=0; i<cnt; ++i) q[l+i]=tmp[i];
	}
}

int main()
{
	n=read(),BIT::Max=read();
	for(int i=1; i<=n; ++i) q[i].Init();
	std::sort(q+1,q+1+n);
	int cnt=1;
	for(int i=2; i<=n; ++i)
		if(q[i].x==q[i-1].x&&q[i].y==q[i-1].y&&q[i].z==q[i-1].z) ++q[cnt].cnt;
		else q[++cnt]=q[i];
	CDQ(1,cnt);
	for(int i=1; i<=cnt; ++i) Ans[q[i].res+q[i].cnt-1]+=q[i].cnt;//f[i]Ϊres[i]+cnt[i]-1, ����Ϊcnt[i] 
	for(int i=0; i<n; ++i) printf("%d\n",Ans[i]);//������� ��ά�����Լ�С������i�� ����������

	return 0;
}
