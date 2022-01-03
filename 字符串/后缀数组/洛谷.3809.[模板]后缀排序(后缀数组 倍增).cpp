//���ht��UOJ.35 
#include<cstdio>
#include<cstring>
#include<algorithm>
const int N=1e6+5;

int n,tm[N],t1[N],t2[N],SA[N],rk[N],ht[N];
//SA[i]=j:����Ϊi�ĺ�׺��ͷ���±�Ϊj 
//rk[i]=j:���±�i��ͷ�ĺ�׺����Ϊj 
//ht[i]:����Ϊi�ĺ�׺������Ϊi-1�ĺ�׺��LCP���� 
char s[N];

void Get_SA()
{
	int *x=t1,*y=t2,limit=80;//���ȶԵ����ַ���������limit�����Ϊ�ַ�����С(���ǲ�ͬ�ַ��ĸ���) 
	for(int i=0;i<n;++i) ++tm[x[i]=s[i]-'0'];
	for(int i=1;i<limit;++i) tm[i]+=tm[i-1];
	for(int i=n-1;~i;--i) SA[--tm[x[i]]]=i;//��������
 	//x[]�൱����rankֵ 
	for(int p=0,k=1;k<n;k<<=1,limit=p,p=0)//ÿ�θ���limitΪp 
	{//pʵ�ʾ��ǲ�ͬ�ַ����ĸ��� 
		//���ȶԵڶ��ؼ��ֽ�������y����ľ��ǶԵڶ��ؼ��������Ľ�� 
		//��һ���̿���ֱ�����ϴεõ���SA[]��� 
		for(int i=n-k;i<n;++i) y[p++]=i;//�ڶ��ؼ��ֳ��Ȳ�Ϊk�������� 
		for(int i=0;i<n;++i) if(SA[i]>=k) y[p++]=SA[i]-k;//ʣ�µ��������ڶ��ؼ��ֵ�(SA[i]>=k)��˳�򣬼�SA[i]�ţ���һ�ؼ��ֵ�λ����Ȼ����SA[i]-k 
		//�Ե�һ�ؼ��ֵ�����ͬ�Ե����ַ����� 
		for(int i=0;i<limit;++i) tm[i]=0;
		for(int i=0;i<n;++i) ++tm[x[i]];//++tm[x[y[i]]];
		for(int i=1;i<limit;++i) tm[i]+=tm[i-1];
		for(int i=n-1;~i;--i) SA[--tm[x[y[i]]]]=y[i];
		//��������ָ�룬��ΪҪ�õ���һ�ֵ�rk(x)����y��û������ 
		std::swap(x,y), x[SA[0]]=0, p=1;
		//�õ��µ�rank 
		for(int i=1;i<n;++i)
//			x[SA[i]]=(y[SA[i-1]]==y[SA[i]]&&y[SA[i-1]+k]==y[SA[i]+k])?p-1:p++;//���������ַ����ַ�����WA 
			if(y[SA[i-1]]==y[SA[i]]&&((y[SA[i-1]+k]==y[SA[i]+k]&&SA[i-1]+k<n&&SA[i]+k<n)||(SA[i-1]+k>=n&&SA[i]+k>=n))) x[SA[i]]=p-1;
			else x[SA[i]]=p++;
		if(p>=n) break;//��ͬ�ַ���������n�����ټ�������������ˣ�break 
	}
}
void Calc_Ht()
{
	for(int i=0;i<n;++i) rk[SA[i]]=i;//rk[]��SA[]��Ϊ������ 
//	��һ��������:ht[i]>=ht[i-1]-1 
//	��Ϊȥ����ͷ�ַ� ��׺һ�󲿷�����ȵġ��Ƚ����� 
	for(int j,k=0,i=0;i<n;ht[rk[i++]]=k)
	{
		if(!rk[i])// continue;//����Ϊ0���ַ���htΪ0 
		{ht[0]=0;continue;}
		j=SA[rk[i]-1], k?--k:0;//��k-1��ʼƥ��(����һ�����ַ���) 
		while(s[i+k]==s[j+k]&&i+k<n&&j+k<n) ++k;
	}
}

int main()
{
//	freopen("sais.in","r",stdin);
//	freopen("sais.out","w",stdout);

	scanf("%s",s),n=strlen(s);
	Get_SA();
	Calc_Ht();
	for(int i=0;i<n;++i) printf("%d ",SA[i]+1);
	putchar('\n');
	for(int i=1;i<n;++i) printf("%d ",ht[i]);

	return 0;
}
