/*
��f[s][i]��ʾ��ǰ����Ϊs���Ե�iͷ��ţ��β�ķ����� 
��i������s�еģ�����ͨ��ö�ٲ���s������������������j����f[s][i]ȥ����f[s|(1<<j)][j]
(��ţһ�����������)
*/
#include<cstdio>
#include<cctype>
#include<algorithm>
using namespace std;
const int N=17;

int n,k,a[N];
long long f[(1<<N)+3][N];

inline int read()
{
	int now=0,f=1;register char c=getchar();
	for(;!isdigit(c);c=getchar())
	  if(c=='-') f=-1;
	for(;isdigit(c);now=now*10+c-'0',c=getchar());
	return now*f;
}

int main()
{
	n=read(),k=read();
	for(int i=0;i<n;++i)
		a[i]=read();
	for(int i=0;i<n;++i)//ע���ʼ����!
		f[1<<i][i]=1;//����һͷţ�ڶ�������Ȼ��һ�ַ��� 
	for(int s=1;s<(1<<n);++s)
		for(int i=0;i<n;++i)
			if(s&(1<<i))
				for(int j=0;j<n;++j)
					if(!(s&(1<<j)) && abs(a[j]-a[i])>k)
						f[s|(1<<j)][j]+=f[s][i];
	long long res=0;
	for(int i=0;i<n;++i)
		res+=f[(1<<n)-1][i];
	printf("%lld",res);

	return 0;
}
