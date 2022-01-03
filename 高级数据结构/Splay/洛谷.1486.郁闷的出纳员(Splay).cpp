/*
BZOJ1503: 3164kb  792ms/824ms(新建节点)
洛谷	: 3.06mb  320ms/308ms(前一个要慢wtf 其实都差不多，但前者好写)
四种操作: 
A:所有元素加v。直接TAG+=v即可 
S:所有元素减v。TAG-=v，如果TAG<0，即可能有低于下限的人 
  这时下限就是MIN-TAG(TAG<0)，可以查找值为MIN-TAG的元素，将其旋到根，删掉整棵左子树 
  如果不存在这个元素，可以插入一个值为MIN-TAG的节点，删除左子树后再删掉这一节点 
  删除子树直接更改对应信息即可 
I:插入一个元素。注意是插入v-TAG 
F:查询第k大值。可以直接做，也可以转为找第(sz-k+1)小值 

1.可以通过找MIN-TAG的前驱、将前驱旋转到根来删除，代替单点插入、删除 
2.扣除不只是在TAG<0时才进行删除!
比如MIN=10 v=10, TAG=5, v能插入 
但是TAG-1=4>0，可是v已经要出去了 
*/
#include<cstdio>
#include<cctype>
#define gc() getchar()
//#define gc()
const int N=1e5+5;

int n,MIN,TAG,SUM,size,root,t[N],fa[N],son[N][2],sz[N],cnt[N];

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=gc()) if(c=='-') f=-1;
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}

inline void Update(int rt)
{
	sz[rt]=sz[son[rt][0]]+sz[son[rt][1]]+cnt[rt];
}
void Rotate(int x,int &k)
{
	int a=fa[x],b=fa[a],l=son[a][1]==x,r=l^1;
	if(a==k) k=x;
	else son[b][son[b][1]==a]=x;
	fa[x]=b, fa[a]=x, fa[son[x][r]]=a;
	son[a][l]=son[x][r], son[x][r]=a;
	Update(a), Update(x);
}
void Splay(int x,int &k)
{
	while(x!=k)
	{
		int a=fa[x],b=fa[a];
		if(a!=k)
			(son[b][1]==a^son[a][1]==x)?Rotate(x,k):Rotate(a,k);
		Rotate(x,k);
	}
}
void Insert(int v,int k)
{
	int f=0;
	while(k && t[k]!=v) f=k,k=son[k][v>t[k]];
	if(k) ++sz[k],++cnt[k];
	else
	{
		k=++size, sz[k]=cnt[k]=1, t[k]=v, fa[k]=f;
		if(f) son[f][v>t[f]]=k;
	}
	Splay(k,root);
}
void Get_Rank(int v,int k)
{
	while(t[k]!=v && son[k][v>t[k]]) k=son[k][v>t[k]];
	Splay(k,root);
}
int Find_Pre(int v,int k)
{
	int res=-1;
	while(k)
		if(t[k]>=v) k=son[k][0];
		else res=k,k=son[k][1];
	return res;
}
void Delete(int k)//本题特殊，直接删掉了根节点的左子树 
{
	if(cnt[k]>1) {--cnt[k],--sz[k]; return;}
	root=son[k][1];
	fa[root]=0;
}
int Rank(int v,int k)
{
	if(v>sz[k]) return -1;
	v=sz[k]-v+1;//转化为求第k小值 
	while(1)
	{
		if(sz[son[k][0]]<v && sz[son[k][0]]+cnt[k]>=v) return t[k]+TAG;
		if(sz[son[k][0]]>=v) k=son[k][0];
		else v-=sz[son[k][0]]+cnt[k],k=son[k][1];
	}
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("1486.in","r",stdin);
#endif

	n=read(),MIN=read();
	char s[5];int k;
	while(n--)
	{
		scanf("%s",s),k=read();
		if(s[0]=='I')
			if(k>=MIN) Insert(k-TAG,root);
			else ;
		else if(s[0]=='A') TAG+=k;
		else if(s[0]=='S')
//		if((TAG-=k)<0)//WA!
		{
			TAG-=k;
			int pre=Find_Pre(MIN-TAG,root);
			if(pre==-1) continue;
			Splay(pre,root);
			SUM+=sz[son[pre][0]]+cnt[pre], root=son[pre][1], fa[root]=0;

//			Insert(MIN-TAG,root),  Get_Rank(MIN-TAG,root);
//			SUM+=sz[son[root][0]], 
//			sz[root]-=sz[son[root][0]], fa[son[root][0]]=0, son[root][0]=0;//删除左子树 
//			Delete(root);
		}
		else printf("%d\n",Rank(k,root));
	}
	printf("%d",SUM);

	return 0;
}
