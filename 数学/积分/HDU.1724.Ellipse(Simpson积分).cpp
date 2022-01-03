/*
171MS	1632K
������Բ����x^2/a^2+y^2/b^2=1��l,r����[l,r]������Բ�����
y=b*sqrt(1-x^2/a^2)��y������Գơ�ֱ����Simpson�󶨻��ּ��ɡ�
����Ҫ������ô��λ��
*/
#include <cmath>
#include <cstdio>
typedef double db;

db a,b;

inline db f(db x){
	return 2*b*sqrt(1-(x/a)*(x/a));
}
inline db Simpson(db l,db r){
	return (r-l)*(f(l)+f(r)+4.0*f((l+r)*0.5))/6.0;
}
db asr(db l,db r,db Eps,db ans)
{
	db mid=(l+r)*0.5, lans=Simpson(l,mid), rans=Simpson(mid,r);
	if(fabs(lans+rans-ans)<Eps) return lans+rans;
	return asr(l,mid,Eps*0.5,lans)+asr(mid,r,Eps*0.5,rans);
}

int main()
{
	int T,l,r; scanf("%d",&T);
	while(T--) scanf("%lf%lf%d%d",&a,&b,&l,&r), printf("%.3lf\n",asr(l,r,1e-4,Simpson(l,r)));

	return 0;
}
