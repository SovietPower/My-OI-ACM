/*
����һ����:����Щ���ȵ�����һ��ƽ����t'.��pos������,pos+1����son[root][1],ֱ�ӽ�t'�ŵ�son[pos+1][0]���� 
ɾ��һ����:��Ҫɾ��������ת��r+1��������ϣ�ֱ��ɾ�� 
ͳһ�޸�һ���������䷴ת:ͬ������ȡ�޸����䣬���� 
�������:��ȡ�������¼��sum 
���������:��һ������������е�nlogn�����㷨�����ڴ��޸ĵ���������� 
	���Ǽ�¼lmax,rmax,maxn,sum(�Ƿ����������/�Ҷ˵�)��dp˼����� 
1.�������4*10^6����������ʱ��ֻ����5*10^5����������Ҫ��һ��ջ����д洢�����±�(�ڴ��) 
  Ҫid[]��¼ 
  ��Delete�����±�ʹ棻ջ��û�о�++cnt 
  Buildʱһ��Ҫ������λ��m�����±�rt 
2.sum[ls],sum[rs]���ǲ�����val[rt]�ģ�ת��ʱע����� 
3.�´�rt�ڵ�ʱ��ȥ�ñ�Ǹ���ls,rs�������ǻ�����rt��û���͸��
  ����rt�ı��ʱҪ����rt��ֵ!����rev�����´�ʱ���ӽڵ���ͬʱ�����ӽڵ� 
  Ҳ�������ᵼ�±���´�����ȫ����Ϊ�����Ƕ�ѯ�ʵģ�������ƽ�������������������ʱһ������±�ǡ� 
4.���䷴ת�ᵼ��lmx,rmx���ˣ�Ҫ��!
5.Down()һ��ֻ��Ҫ��Find���µݹ�ʱ���оͿ��� 
6.����ÿ��Split���ᵼ�¸��ӹ�ϵ�ı䣬����ÿ�θ��¶�ҪUpdate(son[root]),Update(root) 
7.��ʼ��mx[0],����������ֵ���Բ��ù��Ƿ�����ӽڵ� 
8.mx��lmx,rmx���·�ʽ�ǲ�һ����! 
ע��ת�� 
*/
#include<cstdio>
#include<cctype>
#include<algorithm>
#define gc() getchar()
const int N=5e5+5,INF=1e9;

int n,root,A[N],id[N],sk[N],tp,cnt;
int fa[N],son[N][2],sz[N],val[N],lmx[N],rmx[N],mx[N],sum[N];
bool tag[N],rev[N];//ֱ����val[rt]��ֵ����int tag[rt] 
inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=gc()) if(c=='-') f=-1;
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}
#define ls son[rt][0]
#define rs son[rt][1]
inline void Update(int rt)
{
	sz[rt]=sz[ls]+sz[rs]+1;
	mx[rt]=std::max(mx[ls],std::max(mx[rs],rmx[ls]+val[rt]+lmx[rs]));
	lmx[rt]=std::max(lmx[ls],sum[ls]+val[rt]+lmx[rs]);
	rmx[rt]=std::max(rmx[rs],sum[rs]+val[rt]+rmx[ls]);
	sum[rt]=sum[ls]+val[rt]+sum[rs];
}
inline void Down(int rt)
{
	if(tag[rt])
	{
		if(ls)
		{
			tag[ls]=1, val[ls]=val[rt], sum[ls]=sz[ls]*val[rt];
			if(val[rt]>=0) lmx[ls]=rmx[ls]=mx[ls]=sum[ls];
			else lmx[ls]=rmx[ls]=0,mx[ls]=val[rt];
		}
		if(rs)
		{
			tag[rs]=1, val[rs]=val[rt], sum[rs]=sz[rs]*val[rt];
			if(val[rt]>=0) lmx[rs]=rmx[rs]=mx[rs]=sum[rs];
			else lmx[rs]=rmx[rs]=0,mx[rs]=val[rt];
		}
		rev[rt]=tag[rt]=0;//���޸ı�ǾͲ���Ҫ��ת 
	}
	else if(rev[rt])
	{
		rev[rt]=0, rev[ls]^=1, rev[rs]^=1;
		std::swap(lmx[ls],rmx[ls]), std::swap(son[ls][0],son[ls][1]);
		std::swap(lmx[rs],rmx[rs]), std::swap(son[rs][0],son[rs][1]);
//	WA:	std::swap(lmx[rt],rmx[rt]);
//		std::swap(ls,rs);
	}
}
void Rotate(int x,int &k)
{
	int a=fa[x],b=fa[a];bool l=son[a][1]==x,r=l^1;
	if(a==k) k=x;
	else son[b][son[b][1]==a]=x;
	fa[x]=b, fa[a]=x, fa[son[x][r]]=a;
	son[a][l]=son[x][r], son[x][r]=a;
	Update(a),Update(x);
}
void Splay(int x,int &k)
{
	while(x!=k)
	{
		int a=fa[x],b=fa[a];
		if(a!=k) (son[a][1]==x^son[b][1]==a)?Rotate(x,k):Rotate(a,k);
		Rotate(x,k);
	}
}
int Rank(int rt,int k)
{
	while(1)
	{
		Down(rt);
		if(sz[ls]+1==k) return rt;
		if(sz[ls]>=k) rt=ls;
		else k-=sz[ls]+1,rt=rs;
	}
}
void Build(int l,int r,int f)
{
	if(l>r) return;
	int m=l+r>>1,rt=id[m],pre=id[f];
	fa[rt]=pre, son[pre][m>f]=rt;/*,sz[rt]=1;*///son[pre][m>f]:ע�������±��λ��û�й�ϵ 
	rev[rt]=tag[rt]=0, val[rt]=A[m];//��Ϊsum,lmx�Ȼ�����Update���¸��� 
	if(l==r)//����ֻ����ʱ������Щֵ 
	{
		mx[rt]=sum[rt]=A[l], sz[rt]=1;//mx[rt]���������(��)����Ҫѡ�����Ծ���A[l] 
		lmx[rt]=rmx[rt]=std::max(val[rt],0);
		return;
	}
	Build(l,m-1,m), Build(m+1,r,m);
	Update(rt);
}
void Free(int rt)//ʱ�任�ռ䣬�������ñ�� 
{
	if(!rt) return;
	sk[++tp]=rt;
	Free(ls), Free(rs);
	fa[rt]=ls=rs=0;//waiting to try
	rev[rt]=tag[rt]=0;
}
int Split(int pos,int tot)
{
	int x=Rank(root,pos),y=Rank(root,pos+tot+1);
	Splay(x,root), Splay(y,son[x][1]);
	return son[y][0];
}
void Ins()
{
	int pos=read()+1,tot=read();
	for(int i=1;i<=tot;++i) A[i]=read();
	for(int i=1;i<=tot;++i)
		if(tp) id[i]=sk[tp--];
		else id[i]=++cnt;
	Build(1,tot,0);
	int z=id[1+tot>>1],x=Rank(root,pos),y=Rank(root,pos+1);//z:the root of t'
	Splay(x,root), Splay(y,son[x][1]);
	fa[z]=y, son[y][0]=z;
	Update(y), Update(x);
}
void Del()
{
	int pos=read(),tot=read(),y=Split(pos,tot),x=fa[y];
	Free(y), son[x][0]=0;
	Update(x), Update(fa[x]);//��Ҫ����y! 
}
void Modify()
{
	int pos=read(),tot=read(),v=read(),rt=Split(pos,tot);
	tag[rt]=1,val[rt]=v,sum[rt]=sz[rt]*v;
	if(v>=0) lmx[rt]=rmx[rt]=sum[rt], mx[rt]=sum[rt];//lmx,rmxȫѡ��ѡ 
	else lmx[rt]=rmx[rt]=0, mx[rt]=v;//mxȫѡ��ѡһ�� 
	Update(fa[rt]), Update(root);
}
void Rev()
{
	int pos=read(),tot=read(),rt=Split(pos,tot);
	if(!tag[rt])
	{
		rev[rt]^=1;
		std::swap(ls,rs), std::swap(lmx[rt],rmx[rt]);
		Update(fa[rt]), Update(root);
	}
//WA:rev[rt]^=1;
//	Update(fa[rt]), Update(root);
}
void Query()
{
	int pos=read(),tot=read(),rt=Split(pos,tot);
	printf("%d\n",sum[rt]);
}
//void Print(int x)
//{
//	if(!x) return;
//	Down(x);
//	Print(son[x][0]), printf("%d ",val[x]), Print(son[x][1]);
//}

int main()
{
//#ifndef ONLINE_JUDGE
//	freopen("2042.in","r",stdin);
//#endif

//	freopen("seq2005.in","r",stdin);
//	freopen("seq2005.out","w",stdout);

	n=read();int q=read();
	mx[0]=A[1]=A[n+2]=-INF;
	for(int i=1;i<=n;++i) A[i+1]=read(),id[i]=i;
	id[n+1]=n+1,id[n+2]=n+2;
	Build(1,n+2,0), root=n+3>>1, cnt=n+2;
	char s[12];
	while(q--)
	{
		scanf("%s",s);
		if(s[0]=='I') Ins();
		else if(s[0]=='D') Del();
		else if(s[2]=='K') Modify();
		else if(s[0]=='R') Rev();
		else if(s[0]=='G') Query();
		else printf("%d\n",mx[root]);
	}

	return 0;
}
