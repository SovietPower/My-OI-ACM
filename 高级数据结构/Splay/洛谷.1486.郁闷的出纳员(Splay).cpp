/*
BZOJ1503: 3164kb  792ms/824ms(�½��ڵ�)
���	: 3.06mb  320ms/308ms(ǰһ��Ҫ��wtf ��ʵ����࣬��ǰ�ߺ�д)
���ֲ���: 
A:����Ԫ�ؼ�v��ֱ��TAG+=v���� 
S:����Ԫ�ؼ�v��TAG-=v�����TAG<0���������е������޵��� 
  ��ʱ���޾���MIN-TAG(TAG<0)�����Բ���ֵΪMIN-TAG��Ԫ�أ�������������ɾ������������ 
  ������������Ԫ�أ����Բ���һ��ֵΪMIN-TAG�Ľڵ㣬ɾ������������ɾ����һ�ڵ� 
  ɾ������ֱ�Ӹ��Ķ�Ӧ��Ϣ���� 
I:����һ��Ԫ�ء�ע���ǲ���v-TAG 
F:��ѯ��k��ֵ������ֱ������Ҳ����תΪ�ҵ�(sz-k+1)Сֵ 

1.����ͨ����MIN-TAG��ǰ������ǰ����ת������ɾ�������浥����롢ɾ�� 
2.�۳���ֻ����TAG<0ʱ�Ž���ɾ��!
����MIN=10 v=10, TAG=5, v�ܲ��� 
����TAG-1=4>0������v�Ѿ�Ҫ��ȥ�� 
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
void Delete(int k)//�������⣬ֱ��ɾ���˸��ڵ�������� 
{
	if(cnt[k]>1) {--cnt[k],--sz[k]; return;}
	root=son[k][1];
	fa[root]=0;
}
int Rank(int v,int k)
{
	if(v>sz[k]) return -1;
	v=sz[k]-v+1;//ת��Ϊ���kСֵ 
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
//			sz[root]-=sz[son[root][0]], fa[son[root][0]]=0, son[root][0]=0;//ɾ�������� 
//			Delete(root);
		}
		else printf("%d\n",Rank(k,root));
	}
	printf("%d",SUM);

	return 0;
}
