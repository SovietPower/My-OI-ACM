/*
�ֿ飬ά����ĳλ��������һ������Ҫ���ٲ� 
*/
#include<cmath>
#include<cstdio>
#include<cctype>
using namespace std;
const int N=2e6+5;

int n,v[N],belong[N],size,tot,step[N]/*�����������Ҫ���ٲ�*/,nxt[N]/*�������������*/;

inline int read()
{
	int now=0,f=1;register char c=getchar();
	for(;!isdigit(c);c=getchar())
	  if(c=='-') f=-1;
	for(;isdigit(c);now=now*10+c-'0',c=getchar());
	return now*f;
}

void Modify(int p)
{
	int val=read();
	v[p]=val;
//����ֻ��һ���㣡��Ϊͬһ���У�ǰ�����ɺ���õ��ģ���ά����nxt[aft]����aft������һ�����λ�ã����Ա����pos��ǰ�ٸ���һ�� 
	for(int i=p;i>(belong[p]-1)*size;--i)
	{
		int aft=i+v[i];
		if(aft>n)//���ܻ��ڱ߽� 
			step[i]=1, nxt[i]=n+1;
		else if(belong[aft]!=belong[i])
			step[i]=1, nxt[i]=aft;
		else
			step[i]=step[aft]+1, nxt[i]=nxt[aft];
	}
//	printf("Modify  %d:v:%d aft:%d step:%d nxt:%d\n",p,v[p],aft,step[p],nxt[p]);
}
int Query(int p)
{
	int res=0;
	while(p<=n)
//		printf("pos:%d step:%d nxt:%d\n",p,step[p],nxt[p]),
		res+=step[p], p=nxt[p];
	return res;
}

int main()
{
//	freopen("bzoj_2002.in","r",stdin);
//	freopen("bzoj_2002.out","w",stdout);

	n=read();size=sqrt(n);
//	tot=size;//n/size = n/sqrt(n) = sqrt(n) = size
//	if(n%size) ++tot;
	for(int i=1;i<=n;++i)
		v[i]=read(), belong[i]=(i-1)/size+1;
	for(int i=n;i;--i)//��������������������ǰ�ߵõ���ֵO(1)�õ�ĳ��� 
	{
		int aft=i+v[i];
		if(aft>n)
			step[i]=1, nxt[i]=n+1;
		else if(belong[aft]!=belong[i])
			step[i]=1, nxt[i]=aft;
		else
			step[i]=step[aft]+1, nxt[i]=nxt[aft];
//		printf("%d:v:%d aft:%d step:%d nxt:%d\n",i,v[i],aft,step[i],nxt[i]);
	}
	int m=read(),opt,p;
	while(m--)
	{
		opt=read(),p=read()+1;
		if(opt==1)
			printf("%d\n",Query(p));
		else
			Modify(p);
	}

//	fclose(stdin);fclose(stdout);
	return 0;
}
