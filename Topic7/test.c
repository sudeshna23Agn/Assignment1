#include <stdio.h>
int main()
{
char str[20];
// gets(str);
fgets(str, 20, stdin);
printf("%s", str);
printf("okay");
return 0;
}
