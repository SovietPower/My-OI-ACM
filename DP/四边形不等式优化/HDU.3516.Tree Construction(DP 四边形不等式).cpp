/*
$Description$
����ƽ���ϵ�n���㣬����Xi�ϸ�����Yi�ϸ񵥼�����x���y�����������ߣ�ʹ��n���㹹��һ����������ܳ���С��
$Solution$
���������ù���õ�����Ҫ�ϲ�����������Ҫ���ұߵ�������һ�����ŵ�������ߵ����� 
�����뵽����DP(~~����벻��==~~) 
f[i][j]��ʾ��[i,j]�ϲ�Ϊһ��������С���ۣ���ô�� f[i][j] = min{ f[i][k-1]+f[k][j]+cost(i,j,k) }
cost(i,j,k)=X[k]-X[i]+Y[k-1]-Y[j] //ps: ��ǰ�����������Xiλ�ã����²��߶�ΪY_{k-1}���ϲ����²�ӦΪYj������϶������ұ����������ϵ�ϲ��� 
���cost����ά�ģ�֤����cost�����ı��β���ʽ 
������ ����Ӧ�������㵥���Եģ��� P[i][j-1]<=P[i][j]<=P[i+1][j] 
ע����˵�Ӧ��max(P[i][j-1],i+1) 
fӦ�������ı��β���ʽ������֤��
*/
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define gc() getchar()
const int N=1005;

int n,X[N],Y[N],P[N][N],f[N][N];

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=gc()) if(c=='-') f=-1;
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}

int main()
{
	while(~scanf("%d",&n))
	{
		for(int i=1; i<=n; ++i) X[i]=read(),Y[i]=read();
		memset(f,0x3f,sizeof f);
		for(int i=1; i<=n; ++i) P[i][i]=i, f[i][i]=0;
		for(int tmp,i=n-1; i; --i)
			for(int j=i+1; j<=n; ++j)
				for(int k=std::max(P[i][j-1],i+1); k<=P[i+1][j]; ++k)
					if(f[i][j]>(tmp=f[i][k-1]+f[k][j]+X[k]-X[i]+Y[k-1]-Y[j]))
						f[i][j]=tmp, P[i][j]=k;
		printf("%d\n",f[1][n]);
	}
	return 0;
}
