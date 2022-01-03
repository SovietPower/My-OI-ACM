/*
920kb	68ms
$Description$
���������Ȩͼ��������С������������ģ31011�����ر����Ի�������ͬȨֵ�ı߲��ᳬ��10����
$n\leq 100,\ m\leq 1000$��
$Solution$
��С���������������ʣ�
1.�ڲ�ͬ��MST��ĳ��Ȩֵ�ı߳��ֵĴ�����һ���ġ�
2.�ڲ�ͬ��MST�У�������ĳ��Ȩֵ�ıߺ��γɵ���ͨ���״̬��һ���ġ�
$Solution1$ 
�����������ʣ���������һ��MST����ö��ÿһ���(Ȩֵ��ͬ�Ŀ���һ���)����ÿ���DFS($O(2^{10})$)����ĳ�ַ�����ͨ��ͬMST��ͬ(��¼��ͨ���������)����sum++��
�����ݳ˷�ԭ�����Ĵ𰸼�Ϊ����sum��ˡ�
$Solution2$
�����뵽MatrixTree����
����Ȩ��С������ÿһ��ߣ��ڼ��������֮ǰ��֮ǰ�ı߻ṹ��һЩ��ͨ�飬������߻�һ���ὫĳЩ��ͨ������һ������ͼ~~(��Ҳ��֪����ͼ�������ĵ���)~~��

��֮ǰ�γɵ�ÿ����ͨ�鿴��һ���㣬�����ֳ���һ��������������������������Ϊ����Ȩֵ�ıߵķ�����������ͼ��
���ݳ˷�ԭ������ֻҪ�����ÿ��ߵ�����������ٳ����������ˡ�
*/
#include <cstdio>
#include <cctype>
#include <vector>
#include <cstring>
#include <algorithm>
#define gc() getchar()
#define mod (31011)
const int N=102,M=1002;

int n,m,A[N][N],tmp[N][N],fa[N],bel[N],Ans;
bool vis[N];
std::vector<int> v[N];
struct Edge{
	int fr,to,val;
	bool operator <(const Edge &a)const{
		return val<a.val;
	}
}e[M];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
int Get_fa(int x,int *f){//�������鼯��һ��ά��MST�е���ͨ�ԣ�һ��ά��������ͨ�顣
	return x==f[x]?x:f[x]=Get_fa(f[x],f);
}
void Gauss(int n)
{
	for(int i=1; i<n; ++i)
		for(int j=1; j<n; ++j) (A[i][j]+=mod)%=mod;//!
	bool f=0;
	for(int j=1; j<n; ++j)
	{
		for(int i=j+1; i<n; ++i)
			while(A[i][j])
			{
				int t=A[j][j]/A[i][j];
				for(int k=j; k<n; ++k) A[j][k]=(A[j][k]-t*A[i][k]%mod+mod)%mod;
				for(int k=j; k<n; ++k) std::swap(A[i][k],A[j][k]);
				f^=1;
			}
		if(!A[j][j]) {Ans=0; break;}
		Ans=Ans*A[j][j]%mod;
	}
	if(f) Ans=mod-Ans;//!
}
void Calc()
{
	for(int i=1; i<=n; ++i)
		if(vis[i]) v[Get_fa(i,bel)].push_back(i),vis[i]=0;//�����ÿ����ͨ�������ĵ�(ԭ����ͨ��Ĵ���Ԫ��)��
	for(int x=1; x<=n; ++x)
		if(v[x].size()>1)
		{
			memset(A,0,sizeof A);
			for(int i=0,lim=v[x].size(); i<lim; ++i)
				for(int a=v[x][i],b,j=i+1; j<lim; ++j)
				{
					b=v[x][j];
					if(tmp[a][b]){//tmp[][]��Ϊ�߾�����Բ���գ���Ϊ������ͨ�鲻����ͬʱ�����ˡ�
						A[i][j]=A[j][i]=-tmp[a][b];
						A[i][i]+=tmp[a][b], A[j][j]+=tmp[a][b];
					}
				}
			Gauss(v[x].size());
		}
	for(int i=1; i<=n; ++i)
		v[i].clear(), bel[i]=fa[i]=Get_fa(i,bel);//������ĳ�ֱߺ��ͬһ��ͨ�����������
}

int main()
{
	n=read(),m=read();
	for(int i=1; i<=m; ++i) e[i].fr=read(),e[i].to=read(),e[i].val=read();
	std::sort(e+1,e+1+m);
	for(int i=1; i<=n; ++i) fa[i]=bel[i]=i;
	e[0].val=e[1].val, Ans=1;
	for(int r1,r2,i=1; i<=m; ++i)
	{
		if(e[i].val!=e[i-1].val) Calc();
		r1=Get_fa(e[i].fr,fa), r2=Get_fa(e[i].to,fa);
		if(r1==r2) continue;
//		fa[r1]=r2;//��ʱ�Ȳ����ӡ�
		vis[r1]=vis[r2]=1;
		++tmp[r1][r2], ++tmp[r2][r1];//, ++tmp[r1][r1], ++tmp[r2][r2];//��Ķ����������֮����ݱߴ���tmp[][]�������߾���������������Բ���ա�
		bel[Get_fa(e[i].fr,bel)]=Get_fa(e[i].to,bel);//ͳ�Ƴ�ÿ����ͨ�顣
	}
	Calc();//the last edge
	for(int i=1; i<n; ++i)
		if(bel[i]!=bel[i+1]) {Ans=0; break;}
	printf("%d",Ans);

	return 0;
}
