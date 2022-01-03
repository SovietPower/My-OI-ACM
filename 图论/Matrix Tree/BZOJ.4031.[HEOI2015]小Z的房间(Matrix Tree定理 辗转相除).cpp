//864kb	64ms
/*
$Description$
����n*m�ĸ�״���Σ�ÿ��������һ�����������һ�����ӡ�һ��ʼʱ�����ڵĸ���֮�䶼��ǽ���š�
����ǽ��ʹ�����з����γ�һ���������ܴ���������Χ�ͱ߽��ǽ���󷽰�����ģ$10^9$��
$n,m\leq 9$��
$Solution$
���Matrix Tree������ϰһ����շת���������ʽ��(��Ϊģ���������������Բ���ֱ�ӳ���Ԫ����˹��Ԫ����Ҫշת�����)
ע����Ŀ�ǽ����з���(��Щ���ǵ�)����һ������ǽ�ǽڵ㣬������ʽ��ֻ���ڱ�ʾ����ĵ㡣����ͺܿ����޽��ˡ���
*/
#include <cstdio>
#include <algorithm>
#define mod (1000000000)
const int N=103,way[3]={1,0,1};

int n,m,A[N][N],id[12][12];
char mp[12][12];

void Solve(int n)
{
	for(int i=1; i<n; ++i)
		for(int j=1; j<n; ++j) (A[i][j]+=mod)%=mod;//�ȱ�����ģ�
	int f=1,res=1;
	for(int j=1; j<n; ++j)
	{
		for(int i=j+1; i<n; ++i)
			while(A[i][j])
			{//����A[j][j]��A[i][j]��Ϊ0��(A[j][j],A[i][j]) -> (a,b) -> (b,a%b).
				int t=A[j][j]/A[i][j];
				for(int k=j; k<n; ++k) A[j][k]=(A[j][k]-1ll*t*A[i][k]%mod+mod)%mod;
				for(int k=j; k<n; ++k) std::swap(A[i][k],A[j][k]);
				f^=1;//����ʽ��(0)��(1)��š�
			}
		if(!A[j][j]) {res=0; break;}
		res=1ll*res*A[j][j]%mod;//������ʽ��Ϊ����������ʽ�󣬶Խ����ϵ�Ԫ����˼�Ϊ����ʽ��ֵ��
	}
	printf("%d",f?res:(mod-res)%mod);
}

int main()
{
	scanf("%d%d",&n,&m);
	int cnt=0;
	for(int i=0; i<n; ++i) scanf("%s",mp[i]);
	for(int i=0; i<n; ++i)
		for(int j=0; j<m; ++j)
			if(mp[i][j]=='.') id[i][j]=cnt++;//!
	for(int i=0; i<n; ++i)
		for(int j=0; j<m; ++j)
			if(mp[i][j]=='.')
				for(int u=id[i][j],v,xn,yn,d=0; d<2; ++d)
					if((xn=i+way[d])<n&&(yn=j+way[d+1])<m&&mp[xn][yn]=='.')
						v=id[xn][yn],--A[u][v],--A[v][u],++A[u][u],++A[v][v];
	Solve(cnt);
	return 0;
}
