/*
13948kb	5904ms
$Description$
n����m���ߵ�����ͼ��ÿ�����е�Ȩ����������һ����Ԫ��(i,j,k),i<j<k���乱��Ϊmax{ai,aj,ak}����������Ԫ���Ĺ��׺͡�
$Solution$
һ�����Ԫ���������⣺���ݳ����Ƿ�<=sqrt(m)�����Ϊ���ࡣ
����dgr[x]<=sqrt(m)�ĵ�x��ö��x�������������ߣ��ж����������ߵĶ˵���Ƿ��бߣ�map/set/�ڽӱ�hash������Ϊһ������౻���ö��sqrt(m)�Σ����ö��m���ߣ����Ը��ӶȲ�����O(m*sqrt(m))������ͼ�Ļ�������ĵ㲻�ټ����ˣ���
����dgr[x]>sqrt(m)�ĵ�x����������ö����Щ�㣬�����ж�֮���Ƿ��бߡ���Ϊ���ֻ��sqrt(m)�������ĵ㣬so���Ӷ���O(sqrt(m)^3)=O(m*sqrt(m))��
���ڱ��⣬��������ȡmax�����ơ�����ԭͼ�е�һ����u<->v����val[u]<val[v]��������v->u����������u->v������ȵĻ�һ���ɣ�
Ȼ�����Ǵ�val���ĵ������ͼ����Ϊ������ͼ��so�����ظ�����ö�ٵ�ǰ��ĳ���x->v����dgr[v]<=sqrt(m)����ö��v�ĳ��ߣ��ж��Ƿ���x���ڣ�����ö��x�ĳ���v'���ж��Ƿ���v���ڡ�
�ж����ж�v�Ƿ���v'�����ߣ�������v'��v�бߣ���Ϊ��v'����С��ֻö������ߣ���������������жϣ�v->v'�бߣ�ö��vʱ����𰸣���v'��ö������ߣ���������v��������׾�û�ˡ�so��ͳһ�Ƴ��ߴ𰸾����ˡ�
�������ڴ�֮ǰö��x�ĳ���x->v����v���ǣ��Ϳ���֪��ĳ�����Ƿ���x���ڣ�
���ӶȲ�֪����
???�������ڽӱ��У�T�����顣
*/
#include <set>
#include <cmath>
#include <cstdio>
#include <cctype>
#include <vector>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 250000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
const int N=1e5+5,M=250005;

int n,m,/*Enum,H[N],nxt[M],to[M],*/Link[N],dgr[N];
std::set<int> s[N];
std::vector<int> vec[N];
char IN[MAXIN],*SS=IN,*TT=IN;
struct Node{
	int val,id;
	bool operator <(const Node &a)const{
		return val>a.val;
	}
}A[N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline void AddEdge(int u,int v){
	++dgr[u], vec[u].push_back(v);
//	++dgr[u], to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum;
}

int main()
{
	n=read(), m=read();
	for(int i=1; i<=n; ++i) A[i]=(Node){read(),i};
	for(int i=1,u,v; i<=m; ++i)
		u=read(), v=read(), A[u].val>A[v].val?(AddEdge(u,v),s[u].insert(v)):(AddEdge(v,u),s[v].insert(u));//set��˫��/��������ν�ˣ�������ͨ�ǵ����(���������찡)
	std::sort(A+1,A+1+n);
	long long ans=0;
	for(int i=1,x,val,size=sqrt(m); i<=n; ++i)
	{
		x=A[i].id, val=A[i].val;
		const std::vector<int> &X=vec[x];
		int l=X.size();
		for(int j=0,l=X.size(); j<l; ++j) Link[X[j]]=x;
		for(int j=0,l=X.size(),v; j<l; ++j)
		{
			v=X[j];
			if(dgr[v]<=size){
				for(int k=0,l2=vec[v].size(); k<l2; ++k)
					if(Link[vec[v][k]]==x) ans+=val;
			}
			else{
				for(int k=0; k<l; ++k)
					if(s[v].count(X[k])) ans+=val;//not s[to[k]].count(v)!!!
			}
		}
//		for(int j=H[x]; j; j=nxt[j]) Link[to[j]]=x;
//		for(int j=H[x],v; j; j=nxt[j])
//		{
//			v=to[j];
//			if(dgr[v]<=size){
//				for(int k=H[v]; k; k=nxt[k])
//					if(Link[to[k]]==x) ans+=val;
//			}
//			else{
//				for(int k=H[x]; k; k=nxt[k])
//					if(s[v].count(to[k])) ans+=val;//if(s[to[k]].count(v)) ans+=val;//WA
//			}
//		}
	}
	printf("%lld",ans);

	return 0;
}
