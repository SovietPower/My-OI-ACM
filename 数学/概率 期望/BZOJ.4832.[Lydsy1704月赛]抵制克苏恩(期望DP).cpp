/*
1124kb	8ms
f[s][i][j][k]��ʾ��ʣs�ι������ֱ���i,j,k��Ѫ��Ϊ1,2,3��ū����ʱ�������ܵ��˺���
��Ϊ�����ǵ��ƣ�������ô��ʾ�Ӻ���ǰ��ע��a,b,c�ĸ���˳��(ȫд����QAQ)��˳�ƵĻ���Ҫͬʱά������(���ʾ����˺���)��
ע���жϲ��ܳ���7��
����ÿ���ĸ�����i(j,k)/(i+j+k+1).
*/
#include <cstdio>

double f[53][9][9][9];

void Init()
{
//	f[0][A][B][C]=0;
	for(int i=0; i<50; ++i)
		for(int a=0; a<=7; ++a)
			for(int b=0; b<=7-a; ++b)
				for(int c=0; c<=7-a-b; ++c)
				{
					double p=1.0/(a+b+c+1.0);
					f[i+1][a][b][c]+=/*1.0**/p*(f[i][a][b][c]+1.0);
					if(a) f[i+1][a][b][c]+=(double)a*p*f[i][a-1][b][c];
					if(b){
						if(a+b+c<7) f[i+1][a][b][c]+=(double)b*p*f[i][a+1][b-1][c+1];
						else f[i+1][a][b][c]+=(double)b*p*f[i][a+1][b-1][c];
					}
					if(c){
						if(a+b+c<7) f[i+1][a][b][c]+=(double)c*p*f[i][a][b+1][c];
						else f[i+1][a][b][c]+=(double)c*p*f[i][a][b+1][c-1];
					}
				}
}

int main()
{
	Init();
	int A,B,C,K,T; scanf("%d",&T);
	while(T--)
		scanf("%d%d%d%d",&K,&A,&B,&C),printf("%.2lf\n",f[K][A][B][C]);
	return 0;
}
