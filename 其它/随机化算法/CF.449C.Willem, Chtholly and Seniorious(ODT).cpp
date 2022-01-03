/*
343ms	5500KB
$Description$
����һ�����У�������ֲ�����
1.�����x��
2.���串��Ϊx�� 
3.��������k�������
4.�������k���ݵĺ͡�
$Solution$
ODT������setά��ͬɫ��������ı����㷨��
��ľ��Ǵ���������������ݺ����丳ֵ�ܶ�����ܹ���û������ġ�
�����������㱻����һ�㲻���ǡ���������д�����ӡ�
**Ҫע��ģ�**
�ж�it�Ƿ�Ϊ��
�����е�����longlong��������ǰҪȡģ��
�����L=Split(l)�Ļ�Split(r+1)ʱ���ܽ�L���������ɾ������RE 
set.insert����ֵ��pair<set<int>::iterator, bool> (iterator:����λ�� bool:�Ƿ�ɹ����벻���ؼ�)
set.erase(beg,end)��ɾ������������[beg,end)�е�����Ԫ�أ�������һ��Ԫ�صĵ�����	 
����Ҫ�õ������޸ĵ����ݣ�mutable�Ǳ�Ҫ��
*/
#include <set>
#include <cstdio>
#include <algorithm>
#define mp std::make_pair
#define pr std::pair<LL,int>
#define Iter std::set<Node>::iterator
typedef long long LL;
const int N=1e5+5;

LL seed;
struct Node
{
	int l,r;
	mutable LL v;
	Node(int l=0,int r=-1,LL v=0):l(l),r(r),v(v) {}
	bool operator <(const Node &x)const
	{
		return l<x.l;
	}
};
std::set<Node> st;

inline int Rand()
{
	int tmp=seed; seed=(seed*7+13)%1000000007;
	return tmp;
}
inline int FP(LL x,int k,int mod)
{
	LL res=1;
	for(; k; k>>=1,x=x*x%mod)
		k&1&&(res=res*x%mod);
	return res;
}
Iter Split(int p)
{
	Iter it=st.lower_bound(Node(p));//Node(p,p,0)
	if(it!=st.end() && it->l==p) return it;//�ж�it�Ƿ�Ϊ�գ�
	--it;
	int l=it->l,r=it->r; LL v=it->v;
	st.erase(it), st.insert(Node(l,p-1,v));
	return st.insert(Node(p,r,v)).first;
	//set.insert����ֵ��pair<set<int>::iterator, bool> (iterator:����λ�� bool:�Ƿ�ɹ����벻���ؼ�)
}
LL Kth(int l,int r,int k)
{
	static pr A[N];
	Iter R=Split(r+1),L=Split(l);
	int cnt=0;
	for(; L!=R; ++L) A[++cnt]=mp(L->v,L->r-L->l+1);//longlong!
	std::sort(A+1,A+1+cnt);
	for(int i=1; i<=cnt; ++i)
		if((k-=A[i].second)<=0) return A[i].first;
	return 0;
}
int Sum(int l,int r,int x,int mod)
{
	LL res=0;
	Iter R=Split(r+1),L=Split(l);
	for(; L!=R; ++L) res+=1ll*(L->r-L->l+1)*FP(L->v%mod,x,mod)%mod;//L->v(longlong)Ҫȡģ����
	return res%mod;
}

int main()
{
	int n,m,vmax;
	scanf("%d%d%lld%d",&n,&m,&seed,&vmax);
	for(int i=1; i<=n; ++i) st.insert(Node(i,i,Rand()%vmax+1));
	for(int i=1; i<=m; ++i)
	{
		int opt=Rand()%4+1,l=Rand()%n+1,r=Rand()%n+1;
		l>r&&(std::swap(l,r),0);
		switch(opt)
		{
			case 1:
			{
				int x=Rand()%vmax+1;
				Iter R=Split(r+1),L=Split(l);
				for(; L!=R; L->v+=x, ++L);
				break;
			}
			case 2:
			{
				int x=Rand()%vmax+1;
				Iter R=Split(r+1),L=Split(l);
				//�����L=Split(l)�Ļ�Split(r+1)ʱ���ܽ�L���������ɾ������RE
				st.erase(L,R), st.insert(Node(l,r,x));
				//set.erase(beg,end)��ɾ������������[beg,end)�е�����Ԫ�أ�������һ��Ԫ�صĵ�����
				break;
			}
			case 3: printf("%lld\n",Kth(l,r,Rand()%(r-l+1)+1)); break;
			case 4:
			{
				int x=Rand()%vmax+1,y=Rand()%vmax+1;
				printf("%d\n",Sum(l,r,x,y));
				break;
			}
		}
	}

	return 0;
}
