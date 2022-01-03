/*
2120kb	9300ms
woc����ʱ��ȥ ��Щ2000ms��ô���ģ��������Ҳ�������~~������~~��
�����뵽ÿ��һ������һƬ��
�����ƽ�棬�������뵽ֱ��������ͼƥ�䡣����3ά�ģ�
���Է���min(a,b,c)�����ֵֻ��$\sqrt[3]{n}��17$�����Ǳ���ö����һ��Сֵ������Ƿ�ѡ������ʣ�µ���ά����ͼƥ��(\approx) 
������������ʲô��������������ô�鷳��
�����������Ĺ����мǵü�֦��
��Ϊʵ�ʵ���Ӧ��Զ����A*B*C�࣬���Բ�Ҫ��memset��ֱ��ö�١�

zz���ҿ���д��ÿ��DFS���ؽ���+ISAP���ɹ���T��(д�ķ�ʽҲ��zz����ÿ��A*B*Cö���ҵ㣬3������3��DFS)
�о�����һ���ݶ�û��ȫ��5s������
*/
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define gc() getchar()
const int N=5005,M=20005;

int A,B,C,Time,bit[1<<18],Enum,H[N],nxt[M],to[M],match[N],use[N]/*�ռ任ʱ�䣬������������·��*/;
struct Node
{
	int x,y,z;
	Node() {}
	Node(int x,int y,int z):x(x),y(y),z(z) {}
}node[N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline void AddEdge(int u,int v){
	to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum;
}
bool Can(int x)
{
	for(int i=H[x]; i; i=nxt[i])
		if(use[to[i]]!=Time)
		{
			use[to[i]]=Time;
			if(!match[to[i]]||Can(match[to[i]]))
			{
				match[to[i]]=x; return 1;
			}
		}
	return 0;
}
void Work()
{
	A=read(),B=read(),C=read();
	int cnt=0, f=1, lim=1<<A, Max=B;
	if(B<A&&B<C) f=2,lim=1<<B,Max=A;
	else if(C<A&&C<B) f=3,lim=1<<C,Max=A;
	for(int v,i=1; i<=A; ++i)
		for(int j=1; j<=B; ++j)
			for(int k=1; k<=C; ++k)
				if(v=read()){
					if(f==1) node[++cnt]=Node(i,j,k);//ֱ�ӽ���˳�򼴿� 
					else if(f==2) node[++cnt]=Node(j,i,k);
					else node[++cnt]=Node(k,i,j);
				}
	int Ans=10000;
	for(int res,s=0; s<lim; ++s)
	{
		Enum=0, res=bit[s];//Time������Ҫ��� 
//		memset(H,0,sizeof H), memset(match,0,sizeof match);
		for(int i=1; i<=Max; ++i) H[i]=match[i]=0;//here!
		for(int i=1; i<=cnt; ++i)
			if(!(s&(1<<node[i].x-1))) AddEdge(node[i].y,node[i].z);
		++Time;
		for(int i=1; i<=Max; ++i,++Time)
			if(Can(i)){
				if(++res>=Ans) break;//��֦��
			}
		Ans=std::min(res,Ans);
	}
	printf("%d\n",Ans);
}

int main()
{
	for(int i=1; i<(1<<17); ++i) bit[i]=bit[i>>1]+(i&1);
	int T=read();
	while(T--) Work();
	return 0;
}
