/*
�߸�����(����ƫ��)(t2��ʾ�ڶ�������): 
1.�ϲ�:ֱ�Ӻϲ�(��Ҫ��һ��t2��ԭ�еĸ��ڵ�ɾ��) 
2.�����:�����������Ķ���ɾ�ˣ������ٲ����ȥ(�и���)(�����ܳ�Ϊ��һ���ѵĸ�������ҲҪ��t2��ɾ���ٲ���) 
3.������ͨ���:���ڵ����(��t2��ɾ�����������ٲ��뵽t2) 
4.���нڵ��:ȫ�ֱ�� 
5.���ĳ�����ֵ:���ϼ������и��ڵ��ֵ����� 
6.���ĳ����������ͨ������ֵ:�ҵ�������� 
7.������нڵ�����ֵ:�����жѵĸ��ڵ�ȡ������ά���ڶ������� 

(1)
��Ҫ�Ķ��ӽڵ�Ҫ�´����ڵ��ǣ����߶���һ�� 
(2)
��ƫ����ɾ��:��ƫ��������ƽ���������ʣ�����������ɾ��ȨֵΪĳ��ֵ�ĵ㣬���ǿ���ɾ��ָ���±�ĵ� 
�Ⱥϲ�Ҫɾ���ĵ�x����������Ϊs���ٽ����Һϲ����������fa[x]�ϲ� 
�ϲ�������������ܻ�ı䣬���Ҫ����fa[x]�ľ��� 
	���dis[s]+1<dis[fa]����dis[fa]�ľ���Ҫ��С�����s��fa������������Ҫ������������ 
��Ϊdis[fa]�ľ����������Ҫ�������� 
	���dis[s]+1>dis[fa]�����s���������Ϳ��Խ��������������������dis[s]<dis[left]�������fa�ľ��룬����Ҫ�ٽ���һ�������������ϸ��� 
(3)
�����/��(��Ҫ�Ǽ�)�п����ڸ�����ᵼ�����������ı� 
���ڵڶ�����ƫ������Ҫά������λ���Խ������7 
(4)
ע��ڶ�������ʼʱ�Ľ�����������ԭ�ڵ�ϲ� 
(5)
�ϲ����������轫�ǿø����Ǻϲ���ĸ��ڵ�������ӵڶ�����ɾ�� 
(6)
�ڶ����������ÿ�ѵĸ��ڵ㣬����Ҫ�Զ�Ӧ�ѵĸ��ڵ���в��� 
(7)
��һ����ȡ�����²���ʱ�ǵ�Init 
*/
#include<cstdio>
#include<cctype>
#include<algorithm>
//#define gc() (SS==TT &&(TT=(SS=IN)+fread(IN,1,1<<22,stdin),SS==TT)?EOF:*SS++)
#define gc() getchar()
const int N=3e5+5;

int n,TAG,q[N],root;
//char IN[1<<22],*SS=IN,*TT=IN;

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=gc()) if(c=='-') f=-1;
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}
struct Leftist_Tree
{
	int val[N],fa[N],son[N][2],tag[N],dis[N];
	void Init(int p){fa[p]=son[p][0]=son[p][1]=0;}
	inline void PushDown(int x)
	{
		if(son[x][0]) val[son[x][0]]+=tag[x],tag[son[x][0]]+=tag[x];
		if(son[x][1]) val[son[x][1]]+=tag[x],tag[son[x][1]]+=tag[x];
		tag[x]=0;
	}
	int	Getf(int p)
	{
		while(fa[p]) p=fa[p];
		return p;
	}
	int Sum(int p)//�����ڵ�·���ı�Ǻ� 
	{
		int res=0;
		while(p=fa[p]) res+=tag[p];
		return res;
	}
	int Merge(int A,int B)
	{
		if(!A||!B) return A+B;
		if(val[A]<val[B]) std::swap(A,B);
		if(tag[A]) PushDown(A);
		son[A][1]=Merge(son[A][1],B);
		fa[son[A][1]]=A;
		if(dis[son[A][1]]>dis[son[A][0]]) std::swap(son[A][0],son[A][1]);
		dis[A]=dis[son[A][1]]+1;
		return A;
	}
	int Delete(int x)
	{
		if(tag[x]) PushDown(x);
		int f=fa[x],s=Merge(son[x][0],son[x][1]);
		fa[s]=f;
		if(f) son[f][son[f][1]==x]=s;
		while(f)
		{
			if(dis[son[f][0]]<dis[son[f][1]]) std::swap(son[f][0],son[f][1]);
			if(dis[son[f][1]]+1==dis[f]) return root;//���ڵ�û�иı�(���벢δ�����ı�)��ֱ��returnԭ���ĸ� 
			dis[f]=dis[son[f][1]]+1;
//			fa[son[f][1]]=f;
			s=f, f=fa[f];
		}
		return s;//�µĸ��ڵ� �����Ҫ����裬��ʼ����s����Ϊs���ܾ��Ǹ��ڵ�(f=0) 
	}
	int Add_Point(int x,int v)
	{
		int rt=Getf(x);
		if(rt==x)
			if(!(son[x][0]+son[x][1])||v>=0){val[x]+=v;return x;}
			else if(son[x][0]) rt=son[x][0];
			else rt=son[x][1];
		Delete(x);
		val[x]+=v+Sum(x);
		Init(x);
		return Merge(Getf(rt),x);//Ҫ�ϲ�Getf(rt)!ɾ�����Ѿ��������� 
	}
	int Build()
	{
		int h=0,t=0,x,y;
		for(int i=1;i<=n;++i) q[t++]=i;
		while(h<t-1)
		{
			x=q[h++],y=q[h++];
			q[t++]=Merge(x,y);
		}
		return q[t-1];//���صڶ��������ĸ��ڵ� 
	}
}t1,t2;

int main()
{
#ifndef ONLINE_JUDGE
	freopen("3273.in","r",stdin);
#endif

	t1.dis[0]=t2.dis[0]=-1;
	n=read();
	for(int i=1;i<=n;++i) t1.val[i]=t2.val[i]=read();
	root=t2.Build();
	int q=read(),x,y,rx,ry,v,tmp;
	char s[5];
	while(q--)
	{
		scanf("%s",s);
		if(s[0]=='U')
		{
			x=read(),y=read(),rx=t1.Getf(x),ry=t1.Getf(y);
			if(rx==ry) continue;
			tmp=t1.Merge(rx,ry);
			if(tmp==rx) root=t2.Delete(ry);
			else root=t2.Delete(rx);
		}
		else if(s[0]=='A')
			if(s[1]=='1')
			{
				x=read(),v=read();
				root=t2.Delete(t1.Getf(x));
				ry=t1.Add_Point(x,v);//��һ���������º�x���ڶѵĸ��ڵ� 
				t2.val[ry]=t1.val[ry];
				t2.Init(ry);
				root=t2.Merge(root,ry);
			}
			else if(s[1]=='2')
			{
				x=read(),v=read();
				root=t2.Delete((rx=t1.Getf(x)));
				t1.val[rx]+=v, t1.tag[rx]+=v;
				t2.val[rx]=t1.val[rx];
				t2.Init(rx);
				root=t2.Merge(root,rx);
			}
			else
				v=read(), TAG+=v;
		else if(s[0]=='F')
			if(s[1]=='1') x=read(), printf("%d\n",t1.val[x]+t1.Sum(x)+TAG);
			else if(s[1]=='2') x=read(), printf("%d\n",t1.val[t1.Getf(x)]+TAG);
			else printf("%d\n",t2.val[root]+TAG);
	}

	return 0;
}
