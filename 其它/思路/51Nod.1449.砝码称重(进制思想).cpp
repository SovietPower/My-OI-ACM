/*
���Ƚ�m��ʾ��w���� 
����ǹ���m����ÿһλ���Ƿ��Ϊ1��0���� 
������һ����ƽ 
�������m��w���Ƶ�iλΪw-1�����Խ�i+1���������̣���m^i����m��һ�� 
�������̿�����������Ԫ�أ������i+1�����������ˣ��൱����һλ����1����iλ��w-1��Ϊ1�� 
*/
#include<cstdio>
using namespace std;
const int N=100;

int w,m,cnt,bit[N];

int main()
{
	scanf("%d%d",&w,&m);
	while(m)//�߷ֽ���󼴿� 
	{
		if(!(m%w) || m%w==1)
			m/=w;
		else if(m%w==w-1)
			m=m/w+1;//i+1��Ҫһ�����룬��һλ����1 
		else
		{
			printf("NO");
			return 0;
		}
	}
	printf("YES");
	return 0;
}
/*----------90��------------ 
int main()
{
	scanf("%d%d",&w,&m);
	while(m) bit[++cnt]=m%w, m/=w;
	bool f=1;
	for(int i=1; i<=cnt && f; ++i)
		if(bit[i]==w-1)
		{
			if(use[i+1]) f=0;
			else use[i+1]=use[i]=1,++bit[i+1];//ǿ�м�1...
		}
		else if(bit[i]==1)
		{
			if(use[i]) f=0;
			use[i]=1;
		}
		else if(bit[i]) f=0;
	printf(f?"YES":"NO");

	return 0;
}*/
