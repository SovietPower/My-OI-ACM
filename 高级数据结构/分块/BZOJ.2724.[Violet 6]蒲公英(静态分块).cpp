/*
2520kb	19652ms ��ô������
�������� ǿ������ 
����ʲô���������Ϊ���� 
���һ������S1������Ϊx����ôS1��������S2�Ĳ�������ֻ����x��S2�е��� 
�������ǿ��Էֿ���Ԥ����f[i][j]��ʾ��i����j������� 
������ɢ���֣����ǻ���Ҫ֪�������������еĳ��ִ������ⲿ��������2sqrt(n)�� 
����û���޸ģ���ɢ�������ÿ����x��һ��vector����x����λ��push_back��ȥ����xʱ���ּ��ɡ�
����ͨ�ֿ�һ�����¼��ɡ�~~��tmдһ������~~ 
*/
#include <cmath>
#include <cctype>
#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
#define gc() getchar()
const int N=4e4+5,S=205;

int n,m,size,f[S][S],t[S][S],A[N],ref[N],bel[N],tm[N];
std::vector<int> v[N];

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
		if(ref[mid=l+r>>1]>=x) r=mid;
		else l=mid+1;
	return l;
}
void Discrete()
{
	for(int i=1; i<=n; ++i) ref[i]=A[i]=read();
	std::sort(ref+1,ref+1+n);
	int cnt=1;
	for(int i=2; i<=n; ++i)
		if(ref[i]!=ref[i-1]) ref[++cnt]=ref[i];
	for(int i=1; i<=n; ++i) A[i]=Find(A[i],cnt);
}
void Init()
{
	Discrete();
	for(int i=1; i<=n; ++i) bel[i]=(i-1)/size+1;
	for(int i=1; i<=n; ++i) v[A[i]].push_back(i);
	for(int i=1; i<=bel[n]; ++i)
	{
		memset(tm,0,sizeof tm);
		int id=0,mxt=0;
		for(int j=i; j<=bel[n]; ++j)
		{
			int r=std::min(size*j,n);
			for(int k=(j-1)*size+1; k<=r; ++k)
				if(++tm[A[k]]>mxt) id=A[k],mxt=tm[id];
				else if(tm[A[k]]==mxt && A[k]<id) id=A[k];
			f[i][j]=id, t[i][j]=mxt;
		}
	}
}
int Lower(int id,int x)
{
	int l=0,r=v[id].size()-1,mid;
	while(l<r)
		if(v[id][mid=l+r>>1]>=x) r=mid;
		else l=mid+1;
	return l;
}
int Upper(int id,int x)
{
	int l=0,r=v[id].size(),mid;
	while(l+1<r)
	{
		if(v[id][mid=l+r>>1]<=x) l=mid;
		else r=mid;
	}
	return l;
}
inline int Query(int l,int r,int id){
	if(!id) return 0;
	return Upper(id,r)-Lower(id,l)+1;
}
void Update(int l,int r,int L,int R,int &id,int &mxt)
{
	for(int tmp,i=l; i<=r; ++i)
		if((tmp=Query(L,R,A[i]))>mxt||(tmp==mxt&&id>A[i]))
			id=A[i], mxt=tmp;
}
int Solve(int l,int r)
{
	int id=f[bel[l]+1][bel[r]-1],mxt=t[bel[l]+1][bel[r]-1];//mxt=Query(l,r,id);//����id���ܲ����� Ϊ0��Query�б���Ҫ���� 
	Update(l,std::min(r,bel[l]*size),l,r,id,mxt);
	if(bel[l]!=bel[r]) Update((bel[r]-1)*size+1,r,l,r,id,mxt);
	return id;
}

int main()
{
	n=read(),m=read(); size=sqrt(n);//200
	Init();
	int res=0,l,r;
	while(m--)
	{
		l=(read()+res-1)%n+1, r=(read()+res-1)%n+1;
		if(l>r) std::swap(l,r);
		printf("%d\n",res=ref[Solve(l,r)]);
	}
	return 0;
}
