/*
82080kb	3672ms
������һ����Ĳ��������ǿ����뵽���+ǰ׺��(�о�Ҳûʲô����ˡ���)��
ͬʱ���ڱ����������뵽��ϯ��������ϯ����������ǰһ���ڵ㽨���ġ�
������ɢ������ʱ�����򣬰Ѳ�����ɵ���Ӻͼ����ɡ�
�������ȼ������أ�Ȩֵ�߶�����ȥ�غ�ģ�����Ҫ��¼sz[](����sz[]����ֵ ��sum[])������������k����
���Ƕ���ͬһ���ڵ�ÿ���޸ı����½�logn���ڵ㣿�ǵģ���Ϊÿ��һ���ڵ㶼���ܺ�֮ǰ��·�����ã���Ҫ�½���
ע��ÿ��ѯ�ʲ�����������ռ���2nlogn��
longlong!
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
typedef long long LL;
const int N=1e5+5,S=N*40;//size!

int n,m,cnt,ref[N],root[N];
struct Operation
{
	int p,val,tag;
	Operation() {}
	Operation(int _p,int _v,int _t):p(_p),val(_v),tag(_t) {}
	bool operator <(const Operation &a)const{
		return p<a.p;
	}
}q[N<<1];

namespace T
{
	#define lson son[rt][0]
	#define rson son[rt][1]

	int tot,sz[S],son[S][2]; LL sum[S];
	inline void Update(int rt){
		sum[rt]=sum[lson]+sum[rson];
	}
	void Insert(int rt,int &y,int l,int r,int p,int v)
	{
		sz[y=++tot]=sz[rt]+v, sum[y]=sum[rt];
		if(l==r) sum[y]+=ref[p]*v;//��ֱ����p��
		else{
			int m=l+r>>1;
			if(p<=m) son[y][1]=rson, Insert(lson,son[y][0],l,m,p,v);
			else son[y][0]=lson, Insert(rson,son[y][1],m+1,r,p,v);
			Update(y);
		}
	}
	LL Query(int rt,int l,int r,int k)
	{
		if(l==r) return sz[rt]?sum[rt]/sz[rt]*k:0;
		if(sz[lson]==k) return sum[lson];
		else if(sz[lson]<k) return sum[lson]+Query(rson,(l+r>>1)+1,r,k-sz[lson]);
		else return Query(lson,l,l+r>>1,k);
	}
}

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
int Find(int x)
{
	int l=1,r=cnt,mid;
	while(l<r)
		if(ref[mid=l+r>>1]<x) l=mid+1;
		else r=mid;
	return l;
}

int main()
{
	n=read(),m=read();
	int tot=n<<1;
	for(int s,e,i=0; i<n; ++i)
		s=read(),e=read(),ref[i+1]=read(),q[i<<1]=Operation(s,ref[i+1],1),q[i<<1|1]=Operation(e+1,ref[i+1],-1);
	std::sort(ref+1,ref+1+n), cnt=1;
	for(int i=2; i<=n; ++i)
		if(ref[i]!=ref[i-1]) ref[++cnt]=ref[i];
	std::sort(q,q+tot), q[tot].p=m+1;
	for(int i=0; i<tot; ++i) q[i].val=Find(q[i].val);
	for(int i=1,now=0; i<=m; root[i+1]=root[i],++i)//m����ʱ�䷶Χ��
		while(q[now].p<=i/*&& now<tot*/)
			T::Insert(root[i]/*(��ֵ��)��root[i]�Ļ����Ͻ�*/,root[i],1,cnt,q[now].val/*������дFind(q[].val)������죿*/,q[now].tag), ++now;
	int x,a,b,c; LL res=1;
	while(m--)
		x=read(),a=read(),b=read(),c=read(),printf("%lld\n",res=T::Query(root[x],1,cnt,1+(res*a%c+b)%c));

	return 0;
}
