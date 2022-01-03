/*
$Description$
��n��������ʯ�ӣ�ÿ�β������Խ���ĳЩ��ʯ�ӣ����Ǵ�һ���ѽ�����ʯ�Ӷ�����������(>0)������޷��������䡣�������Ƿ��ʤ��
$Solution$
���������δ�����ģ�������һЩ�ѽ�����ʯ�ӣ�������Ҫ��ʤ ���������������ʹ(�ѽ�����)ʯ�Ӷ�����Ϊ0���������δ������ʯ�Ӷ��д�������Ϊ0�ģ����ֽ������ǿ���ʹ�������ٱذ�̬��
�������������Ϊ0��ĳЩʯ�Ӷѣ����ֻ�����������Ƕ����������������ַ��̻��ᣬ������ʤ��
���������������Ϊ0��ĳЩʯ�Ӷѣ�������Ҫ����һЩʯ�Ӷѿ�ʼ���ǰ�������̵����֡����ֽ����£�״̬Ϊ��δ����������Ϊ0��ʯ�Ӷѣ���֪���ֱذܡ�
����ֱ�������Ի��ж���������Ϊ0��ĳЩʯ�Ӷѡ�
*/
#include <cstdio>
#include <cctype>
#include <cstring>
#define gc() getchar()
#define Bit 29

int base[33];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline bool Insert(int x,bool f)
{
	if(f) return 1;
	for(int i=Bit; ~i; --i)
		if(x>>i&1)
			if(base[i]) x^=base[i];
			else {base[i]=x; break;}
	return x==0;
}

int main()
{
	int T=read();
	while(T--)
	{
		memset(base,0,sizeof base);
		int n=read(); bool f=0;
		while(n--) f|=Insert(read(),f);
		puts(f?"Yes":"No");
	}
	return 0;
}
