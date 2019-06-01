#include <stdio.h>
int main() {
int n,a;
int negative=0;
scanf("%d", &n);
for(int i=1; i<=n; i++)
{scanf("%d", &a);
if (a<0)
	negative=negative+1;}
printf("%d", negative);
	return 0;}
