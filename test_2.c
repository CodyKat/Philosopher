#include <stdlib.h>
#include <stdio.h>

typedef struct 
{
	int a;
}	t_num;

int main()
{
	t_num A;
	t_num *p_A = &A;
	
	A.a = 0;
	printf("%d\n%p\n%p", p_A->a, &p_A->a, p_A->a);
}