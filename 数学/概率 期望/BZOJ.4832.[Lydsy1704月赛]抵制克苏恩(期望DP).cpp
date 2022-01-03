/*
1124kb	8ms
f[s][i][j][k]表示还剩s次攻击，分别有i,j,k个血量为1,2,3的奴隶主时，期望受到伤害。
因为期望是倒推，所以这么表示从后往前求，注意a,b,c的更新顺序(全写反了QAQ)！顺推的话需要同时维护概率(概率就是伤害了)。
注意判断不能超过7。
命中每个的概率是i(j,k)/(i+j+k+1).
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
