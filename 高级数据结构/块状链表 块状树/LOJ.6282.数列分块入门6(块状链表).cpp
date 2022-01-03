#include <cmath>
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
typedef long long LL;
const int N=1e5+5;

int n,size,H[N],nxt[N],nxtv[N<<1],A[N<<1],sz[N];//二倍数组！mdzzC++数组越界各种奇葩错误(这指针无语) 

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=gc()) if(c=='-') f=-1;
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}
inline int New_Node()
{
	static int cnt=n;
	return ++cnt;
}
inline int New_Block()
{
	static int cnt=(n-1)/size+1;
	return ++cnt;
}
void Init()
{
	for(int i=1; i<=n; ++i) A[i]=read();
	int tot=(n-1)/size+1;
	H[0]=1;
	for(int now=0,i=1; i<tot; ++i)//块整体的链表 
		H[i]=(i-1)*size+1, nxt[i]=i+1, sz[i]=size;
	sz[tot]=n-(tot-1)*size, H[tot]=(tot-1)*size+1;
	for(int i=1,tmp=i*size; i<=tot; tmp=++i*size)//块内链表 
		for(int j=(i-1)*size+1; j<tmp; ++j)
			nxtv[j]=j+1;
}
int Get_Pos(int &p)
{
	for(int i=H[0]; i; i=nxt[i])
		if((p-=sz[i])<=0) {p+=sz[i]; return i;}
}
int Query(int p)
{
	int id=Get_Pos(p);
	for(int i=H[id]; i; i=nxtv[i])
		if(!--p) return A[i];
}
void Insert(int p,int v)
{
	int id=Get_Pos(p),pos=New_Node();
	A[pos]=v, ++sz[id];
//	printf("I pos:%d id:%d p:%d size:%d stdsz:%d sz[id]:%d\n",pos,id,p,size*(id-1)+p,size,sz[id]);
	if(!p) nxtv[pos]=H[id], H[id]=pos;
	else
		for(int i=H[id]; i; i=nxtv[i])
			if(!--p) {nxtv[pos]=nxtv[i], nxtv[i]=pos; break;}
	if(sz[id] > size<<1)//2倍比较合适 
	{
		p=size;
		for(int i=H[id]; i; i=nxtv[i])
			if(!(--p)) {pos=nxtv[i], nxtv[i]=0; break;}
		int posb=New_Block();
		H[posb]=pos, nxt[posb]=nxt[id], nxt[id]=posb, sz[posb]=sz[id]-size, sz[id]=size;
	}
}
//void Print()
//{
//	puts("Output:");
//	for(int i=H[0]; i; i=nxt[i])
//		for(int j=H[i]; j; j=nxtv[j])
//			printf("%d ",A[j]);
//	putchar('\n');
//}

int main()
{
	n=read(), size=sqrt(n);
	Init();
	for(int opt,l,r,c,i=1; i<=n; ++i)
	{
		opt=read(),l=read(),r=read(),c=read();
		if(opt) printf("%d\n",Query(r));
		else Insert(l-1,r);
	}
	return 0;
}
