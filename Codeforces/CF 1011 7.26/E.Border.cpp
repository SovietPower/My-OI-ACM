#include <cstdio>
#include <cctype>
#include <bitset>
#include <algorithm>
#define gc() getchar()
const int N=1e5+5;

std::bitset<N<<1> B;
std::bitset<N<<1> tmp;
int A[N],C[N];

inline int read()
{
	int now=0;register char C=gc();
	for(;!isdigit(C);C=gc());
	for(;isdigit(C);now=now*10+C-'0',C=gc());
	return now;
}

int Gcd(int x,int y){
	return y?Gcd(y,x%y):x;
}

int main() {
	
	int n=read(), K=read(), f=0;
	for(int i=1; i<=n; ++i)
	{
		A[i]=read()%K;
		if(A[i] && Gcd(A[i],K)==1) {f=1; break;}
	}
	if(f)
	{
		printf("%d\n",K);
		for(int i=0; i<K; ++i) printf("%d ",i);
		return 0;
	}
	B[0]=1;
	for(int i=1; i<=n; ++i)
		if(!C[A[i]])
		{
			C[A[i]]=1;
			if(!A[i]) continue;
			for(int j=A[i]; j<K; j+=A[i])
			{
				tmp=B;
				tmp=tmp<<j, B|=tmp;
				tmp=tmp>>K, B|=tmp;
			}
		}
	int res=0;
	for(int i=0; i<K; ++i) if(B[i]) ++res;
	printf("%d\n",res);
	for(int i=0; i<K; ++i)
		if(B[i]) printf("%d ",i);

	return 0;
}
