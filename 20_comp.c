#include <stdio.h>
int main() {
int n,a;
int result=1;
scanf("%d", &n);
for(int i=1; i<=n; i++)
{scanf("%d", &a);
result=result*(a-i);}
printf("%d", result);
return 0;}
