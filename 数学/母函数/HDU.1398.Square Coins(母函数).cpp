//0MS 1512K
#include <cstdio>
#include <cstring>
const int N=303;

int n,f[N],tmp[N]; //ƽ��������ʵ�ʷ�����Ҳ������ô�ࡣ

void Init()
{
	n=300;//N=300����17*17����
	for(int i=0; i<=n; ++i) f[i]=1;
	for(int i=2; i<=17; ++i)
	{
		memset(tmp,0,sizeof tmp);
		for(int j=0; j<=n; ++j)
			for(int k=0; j+k<=n; k+=i*i)
				tmp[j+k]+=f[j];
		memcpy(f,tmp,sizeof f);
	}
}

int main()
{
	Init();
	while(scanf("%d",&n),n) printf("%d\n",f[n]);
	return 0;
}
