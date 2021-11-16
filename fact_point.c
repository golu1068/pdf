// #include<stdio.h>

// void factorial(int *num, int *fact)
// {
//     int temp=1;
//     while (*num != 1)
//     {
//         *fact = *fact * (*num);
//         *num = *num - 1;
//     }
// }
// void number_reverse(int *num)
// {
//     int temp=0,rem;
//     while (*num != 0)
//     {
//         rem = *num%10;
//         *num = *num/10;
//         temp = temp*10 + rem;
//     }
//     *num = temp;
// }

// void main()
// {
//     int num;
//     float fact=1;
//     printf("enter the number: \n");
//     scanf("%d", &num);

//     // factorial(&num, &fact);
//     // printf("%d\n",fact);

//     number_reverse(&num);
//     printf("%d\n", num);
// }

#include<stdio.h>
void function(char**);
int main()
{
	int *iptr;
    int i, arr[2][2] = {10, 11, 12, 13};
    iptr = *arr ;
    printf("%d ", arr);
    printf("%d ", *arr);
    return 0;
}
void function(char **ptr)
{
	char *ptr1;
	ptr1 = (ptr += sizeof(int))[-2];
	printf("%s\n", ptr1);
}