/*
22156ms	31.88MB
$Description$
����һ�ñߴ�Ȩ��������ɾ��K���ߡ�������K��ȨΪ0�ıߺ����������ֱ����
$n,K\leq3\times10^5$��
$Solution$
��Ŀ����ת��Ϊ�������ϲ��ཻ��$k+1$������ʹ�����ǵı�Ȩ�����(�Ѳ�����˵ʲô�ˡ���)��
ѡ������Խ�࣬��������Խ�������ٵ�ʱ�򻹻���ٵ�Խ�죬���γ���һ��$K-Ans_K$����͹���������û�����������ƣ�DP�Ǻ����׵�(�������ü�һά$k$)��
��Ȩ���֡�DP��$f[x][0/1/2]$��ʾ��$x$����Ϊ$0/1/2$ʱ�����Ž⣬��һ����������µ�������

**DPϸ�ڣ�**
$f[x][1]$������Ϊ$1$ʱ������Ϊ���Ļ��ѣ����Ǻϲ�ʱ���ϣ�������ɡ�
�����$f[x][0]$ �� ��$f[x][1]$����������$f[x][2]$ȡ��$\max$����ʾ����״̬���������ϸ��µ�����״̬��������Ͽ�����
�ṹ��д��Ȼ�������㵫��̫��д�ˡ���������Ȼ��ô���ô...
ע����$K+1$��_�� 

**[Update] 19.2.11**
���ֱ߽��ǣ�ʹ�ñ߽��㹻���ܱ�֤ÿһ����Ʒ������ѡ��Ҳ����ÿ����Ʒ��������ֵ�Ϳ����ˡ�������[CF739E](https://www.cnblogs.com/SovietPower/p/9163792.html)��Ȩֵ0~1�͹���
Ȼ��...���ֵ�ʱ��ֻҪ��֤ǡ��ȡ��$k$���Ϳ����ˣ�б�ʾ����Ƕ�������ν...�ɡ�
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 200000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=3e5+5;

int n,K,Enum,H[N],nxt[N<<1],to[N<<1],len[N<<1];
char IN[MAXIN],*SS=IN,*TT=IN;
LL C,sum;
struct Node{
	LL v; int n;
	Node() {}
	Node(LL v,int n):v(v),n(n) {}
	bool operator <(const Node &x)const{
		return v==x.v?n>x.n:v<x.v;
	}
	Node operator +(const Node &x){
		return Node(v+x.v, n+x.n);
	}
	Node operator +(LL val){
		return Node(v+val, n);
	}
}f[N][3];

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=gc()) if(c=='-') f=-1;
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}
inline void AddEdge(int u,int v)
{
	int w=read(); sum+=abs(w);
	to[++Enum]=v, nxt[Enum]=H[u], len[Enum]=w, H[u]=Enum;
	to[++Enum]=u, nxt[Enum]=H[v], len[Enum]=w, H[v]=Enum;	
}
inline Node Update(Node t){//�ϲ���һ������ 
	return Node(t.v-C, t.n+1);
}
void DFS(int x,int fa)
{
	f[x][0]=f[x][1]=Node(0,0), f[x][2]=Node(-C,1);
	//�������f[x][1/2]��Ӧ��û��ֵ�𡣡�����������ʼ��û���� ��Ϊ���ֻ���������Ҳ�����f[x][0]���Űɡ�
	for(int v,val,i=H[x]; i; i=nxt[i])
		if((v=to[i])!=fa)
		{
			DFS(v,x), val=len[i];
			f[x][2]=std::max(f[x][2]+f[v][0],Update(f[x][1]+f[v][1]+val));
			f[x][1]=std::max(f[x][1]+f[v][0],f[x][0]+f[v][1]+val);
			f[x][0]=f[x][0]+f[v][0];
		}
	f[x][0]=std::max(f[x][0],std::max(Update(f[x][1]),f[x][2]));
}

int main()
{
	n=read(), K=read()+1;
	for(int i=1; i<n; ++i) AddEdge(read(),read());
	LL l=-sum,r=sum;
	while(l<=r)
	{
		if(C=l+r>>1, DFS(1,1), f[1][0].n>K) l=C+1;
		else r=C-1;
	}
	C=l, DFS(1,1);//�����l(r+1)Ϊ�𰸡�
	printf("%lld",f[1][0].v+K*l);

	return 0;
}
