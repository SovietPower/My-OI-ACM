//46MS 1572K
#include <cstdio>
#include <cstring>
#include <algorithm>
const int N=8008,v[5]={0,1,2,5};

int n,f[N],tmp[N],num[5];

int main()
{
	while(scanf("%d%d%d",&num[1],&num[2],&num[3]),num[1]||num[2]||num[3])
	{
		n=1*num[1]+2*num[2]+5*num[3];
		memset(f,0,sizeof f), f[0]=1;
		for(int las=0,nxt,i=1; i<=3; ++i)
		{
			memset(tmp,0,sizeof tmp), nxt=std::min(las+v[i]*num[i],n);
			for(int j=0; j<=las; ++j)
				for(int k=0; k<=num[i]/*&&j+k*v[i]<=nxt*/; ++k)
					tmp[j+k*v[i]]+=f[j];
			memcpy(f,tmp,sizeof f), las=nxt;
		}
		bool flag=1;
		for(int i=1; i<=n; ++i)
			if(!f[i]) {printf("%d\n",i), flag=0; break;}
		if(flag) printf("%d\n",n+1);
	}
	return 0;
}
