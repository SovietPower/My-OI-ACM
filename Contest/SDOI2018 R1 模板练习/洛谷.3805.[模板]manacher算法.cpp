/*
��¼��ǰex[]���Ļ�������id����Զ���췶Χmx��
���ڴ��Ĺ���: 
Ӧ���� @ #A#B#C#B#A# $�������� @ A#B#C#B#A $ 
���� @a#b#b#c$����Ӧ��max{ex[i]}-1�����ڶ��ֺܶ�����´���max{ex[i]}.
���Žⲻ�Ĵ�����ż���۸о�sxbk����
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
const int N=22000010;

int n,ex[N];
char tmp[N>>1],s[N];

void Init()
{
	n=strlen(tmp), s[0]='@';
	for(int i=0; i<n; ++i)
		s[i<<1|1]='#', s[(i<<1)+2]=tmp[i];
	s[n=2*n+2]='$', s[n-1]='#';
}
void Manacher()
{
	int res=0,mx=0,id;
	for(int i=1; i<n; ++i)
	{
		if(i<mx) ex[i]=std::min(ex[id*2-i],mx-i);
		else ex[i]=1;
		while(s[i+ex[i]]==s[i-ex[i]]) ++ex[i];
//		if(ex[i]>res) res=ex[i];//���������Ҳ�ԣ��������ˡ���
		if(i+ex[i]>mx) id=i,mx=i+ex[i],res=std::max(res,ex[i]);
	}
	printf("%d",res-1);
}

int main()
{
	scanf("%s",tmp), Init(), Manacher();
	return 0;
}
