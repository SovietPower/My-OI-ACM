/*
����λ��ֱ����sz��� 
��Ҫ���id���±겢��ͳһ 
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
const int N=5e5+15,INF=1e8,MAXIN=1e6;

int n,m,root;
inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=gc()) if(c=='-') f=-1;
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}
struct SPLAY
{
	int A[N],size,fa[N],son[N][2],val[N],sz[N],id[N],sum[N],lmax[N],rmax[N],smax[N];
	int pool[N],top,cnt;
	bool cover[N],rev[N];
	inline int New_Node(){
		if(top) return pool[--top];
		return ++cnt;
	}
	inline void Update(int rt)
	{
		int ls=son[rt][0],rs=son[rt][1];
		sz[rt]=sz[ls]+sz[rs]+1;
		sum[rt]=sum[ls]+val[rt]+sum[rs];
		smax[rt]=std::max(rmax[ls]+val[rt]+lmax[rs],std::max(smax[ls],smax[rs]));
		lmax[rt]=std::max(lmax[ls],sum[ls]+val[rt]+lmax[rs]);
		rmax[rt]=std::max(rmax[rs],sum[rs]+val[rt]+rmax[ls]);
	}
	inline void Set(int rt,int v)
	{
		sum[rt]=v*sz[rt], val[rt]=v, cover[rt]=1;
		if(v>0) smax[rt]=lmax[rt]=rmax[rt]=sum[rt];
		else smax[rt]=v, lmax[rt]=rmax[rt]=0;//���ٴ���һԪ�� ������Ϊ����˵㻹�ǿ��Բ�Ҫ�� 
	}
	inline void Rev(int rt)
	{
		std::swap(lmax[rt],rmax[rt]), std::swap(son[rt][0],son[rt][1]);
		rev[rt]^=1;
	}
	void PushDown(int rt)
	{
		if(cover[rt])
			Set(son[rt][0],val[rt]), Set(son[rt][1],val[rt]), cover[rt]=rev[rt]=0;//���revû�б�Ҫ�� 
		if(rev[rt])
			Rev(son[rt][0]), Rev(son[rt][1]), rev[rt]^=1;
	}
	void Rotate(int x,int &k)
	{
		int a=fa[x],b=fa[a]; bool l=son[a][1]==x,r=l^1;
		if(k==a) k=x;
		else son[b][son[b][1]==a]=x;
		fa[a]=x, fa[x]=b, fa[son[x][r]]=a,
		son[a][l]=son[x][r], son[x][r]=a;
		Update(a), Update(x);
	}
	void Splay(int x,int &k)
	{
		while(x!=k)
		{
			int a=fa[x],b=fa[a];
//			PushDown(b), PushDown(a), PushDown(x);
			if(a!=k) son[a][1]==x^son[b][1]==a?Rotate(x,k):Rotate(a,k);
			Rotate(x,k);
		}
	}
	int Rank(int k,int p)
	{
		while(1)
		{
			PushDown(k);
			if(sz[son[k][0]]+1==p) return k;
			if(sz[son[k][0]]>=p) k=son[k][0];
			else p-=sz[son[k][0]]+1, k=son[k][1];
		}
	}
	void Build(int l,int r,int f)
	{
		if(l>r) return;
		int m=l+r>>1,rt=id[m],pre=id[f];
		val[rt]=A[m], fa[rt]=pre, son[pre][m>f]=rt;//son[pre][val[rt]>val[pre]]=rt;ͬ���Ĵ���--�����е��������±꣡
		cover[rt]=rev[rt]=0;
		if(l==r){
			sz[rt]=1, sum[rt]=smax[rt]=val[rt];
			if(val[rt]>0) lmax[rt]=rmax[rt]=val[rt];
			else lmax[rt]=rmax[rt]=0;
		}
		else{//������Ϣ��Updateʱ���� 
			Build(l,m-1,m), Build(m+1,r,m),
			Update(rt);
		}
	}
	void Insert()
	{
		int p=read()+1,tot=read();
		for(int i=1; i<=tot; ++i) A[i]=read(),id[i]=New_Node();
		Build(1,tot,0);
		int r=id[1+tot>>1],x=Rank(root,p),y=Rank(root,p+1);
		Splay(x,root), Splay(y,son[x][1]);
		fa[r]=y, son[y][0]=r;
		Update(y), Update(x);
	}
	void Free(int x)
	{
		pool[top++]=x;
		if(son[x][0]) Free(son[x][0]);
		if(son[x][1]) Free(son[x][1]);
		son[x][0]=son[x][1]=0;//son������Buildʱ���� 
//		fa[x]=rev[x]=cover[x]=0;
	}
	int Split()
	{
		int p=read(),tot=read();
		int x=Rank(root,p),y=Rank(root,p+tot+1);
		Splay(x,root), Splay(y,son[x][1]);
//		printf("p:%d tot:%d x:%d y:%d z:%d\n",p,tot,x,y,son[y][0]);
		return son[y][0];
	}
	void Delete()
	{
		int z=Split(),y=fa[z];
		/*if(z)*/ Free(z);//��ǰz���ﲻ��Ҫ���� ����ɾ��Ԫ�� 
		son[y][0]=0, Update(y), Update(fa[y]);
	}
	void Modify(){
		int z=Split(),v=read();
		Set(z,v), Update(fa[z]), Update(root);//���£�
	}
	void Reverse(){
		int rt=Split();
		if(!cover[rt])//����cover���ʱ��ת 
			Rev(rt), Update(fa[rt]), Update(root);
	}
	int Query_Sum(){
		printf("%d\n",sum[Split()]);
	}
//	void Print(int x)
//	{
//		PushDown(x);
//		if(son[x][0]) Print(son[x][0]);
//		printf("%d:%d\n",x,val[x]);
//		if(son[x][1]) Print(son[x][1]);
//	}
//	void Debug()
//	{
//		puts("Debug");
//		Print(root);
//		putchar('\n');
//	}
}t;


int main()
{
	n=read(),m=read();
	t.id[1]=1, t.id[n+2]=n+2;//������0 
	t.A[1]=t.A[n+2]=-INF;//�߽�������Ҫ��������𰸣�
	for(int i=2; i<=n+1; ++i) t.A[i]=read(),t.id[i]=i;
	t.cnt=n+2, t.Build(1,n+2,0);
	root=t.id[n+3>>1];
	char opt[15];
	while(m--)
	{
		scanf("%s",opt);
		if(opt[0]=='I') t.Insert();
		else if(opt[0]=='D') t.Delete();
		else if(opt[4]=='-') t.Modify();
		else if(opt[0]=='R') t.Reverse();
		else if(opt[0]=='G') t.Query_Sum();
		else printf("%d\n",t.smax[root]);
	}
	return 0;
}
