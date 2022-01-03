/*
46136kb	13912ms
Ҫ��b^(aj+x)���Ӧ��(aj+x)�����λ��������b�෴����������Trie������������������Ҳ��ᡣ
�����λ��ʼ�������λb��0/1���ж��Ƿ����sum+(1<<l)-x<=aj<sum+(1<<l+1)-x / sum-x<=aj<sum+(1<<l)-x������ϯ���жϡ�
�һ��������һ��ѯ����ôһ���㡣��ֱ��O(logn)ö�١�
ע��Ҫ��0��ʼ��
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
const int N=2e5+5,S=N*19,Max=1e5;

int n,m,root[N];
namespace T
{
	int tot,son[S][2],sz[S];
	void Insert(int x,int &y,int l,int r,int p)
	{
		sz[y=++tot]=sz[x]+1;
		if(l<r){
			int m=l+r>>1;
			if(p<=m) son[y][1]=son[x][1], Insert(son[x][0],son[y][0],l,m,p);
			else son[y][0]=son[x][0], Insert(son[x][1],son[y][1],m+1,r,p);
		}
	}
	bool Exist(int x,int y,int l,int r,int L,int R)
	{
		if(L<=l && r<=R) return sz[y]-sz[x];
		int m=l+r>>1;
		if(L<=m)
			if(m<R) return Exist(son[x][0],son[y][0],l,m,L,R)|Exist(son[x][1],son[y][1],m+1,r,L,R);
			else return Exist(son[x][0],son[y][0],l,m,L,R);
		return Exist(son[x][1],son[y][1],m+1,r,L,R);
	}
	bool Query(int r1,int r2,int l,int r)
	{
		l=std::max(0,l), r=std::min(r,Max);
		return l>r?0:Exist(r1,r2,0,Max,l,r);
	}
}
inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}

int main()
{
	n=read(),m=read();
	int b,x,l,r,sum;
	for(int i=1; i<=n; ++i) T::Insert(root[i-1],root[i],0,Max,read());
	while(m--)
	{
		b=read(),x=read(),l=read(),r=read();
		sum=0;
		for(int i=17,now; i>=0; --i)
		{
			now=sum+((1^((b>>i)&1))<<i);
			if(T::Query(root[l-1],root[r],now-x,now+(1<<i)-1-x)) sum=now;//���Բ�����λʹ�ô���� 
			else sum+=((b>>i)&1)<<i;//���ܵĻ�˵����λֻ��ͬbһ�������� 
		}
		printf("%d\n",sum^b);//ֱ�Ӽ�¼�ͣ����^b���ɡ���Ȼ�Ǵ�Ҳ�С�
	}
	return 0;
}
