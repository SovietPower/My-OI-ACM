/*
14964kb	3036ms
����: ��������Ϊk����ͨ�飬Ҫ��ÿ����ͨ���С��ͬ��������ܵĴ�С��
����: ��������ʱ��ɫ�Ľڵ���Ϊk�����ҽ�����n/k���ڵ���������������k�ı���(��Ȼ����k|n)��
֤���Ͳ�֤�ˣ�˵�����(Ȼ��Ҳ˵���������)��
����һ�����������СΪx*k����������������������������(�������ڵ�)һ����x����������СΪk�ı������Ұ�sz[]Ϊk�ĵ�����ɾȥ�����϶���ɾ������������
��Ϊ����x*k��ô�󡣡�˵���������������Ӧ���Ǻ���ġ�
��Ϊ���ڵ���һ�����ӽڵ�С������sz[]ʱ����ѭ��һ�鼴�ɣ�����ҪDFS��
*/
#include <cstdio>
#include <cctype>
#include <cstring>
#define gc() getchar()
#define XXX (19940105)
const int N=1200005;

int n,fa[N],sz[N],num[N],cnt,p[10005],lim[10005];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}

int main()
{
	n=read();
	for(int i=2; i<=n; ++i) if(!(n%i)) p[++cnt]=i,lim[cnt]=n/i;//if(i*i!=n) p[++cnt]=n/i;//��������ö�ٵ�sqrt(n)?
	for(int T=1; T<=10; ++T)
	{
		memset(sz,0,sizeof sz), memset(num,0,sizeof num);;
		for(int i=2; i<=n; ++i) fa[i]=T==1?read():((fa[i]+XXX)%(i-1)+1);//read()����233.
		for(int i=n; i; --i) sz[fa[i]]+=(++sz[i]);
		for(int i=1; i<=n; ++i) ++num[sz[i]];
		printf("Case #%d:\n1\n",T);//�е�1Ҳ�С�
		for(int t,i=1; i<=cnt; ++i)
		{
			t=0;//����szΪx*p[i]�Ľڵ���� 
			for(int j=1; j<=lim[i]; ++j) t+=num[j*p[i]];
			if(t*p[i]==n) printf("%d\n",p[i]);
		}
	}
	return 0;
}
