//// Dynamic memory allocation

#include<stdio.h>
#include<stdlib.h>

void Display(int *ptr, int size)
{
    int i;
    for(i=0; i<size; i++)
    {
        printf("%d  ",(*ptr++));
    }
    printf("\n");
}

void main()
{
    int *m_ptr,i;
    m_ptr = (int *)malloc(10*sizeof(int));
    for(i=0; i<10; i++)
    {
        // *(m_ptr+i) = i*10;
        m_ptr[i] = i*10;
    }
    Display(m_ptr, 10);
    free(m_ptr);/// m_ptr is dangling pointer
    m_ptr = NULL;  /// m_ptr is not a dagnling pointer now 
    // Display(m_ptr, 10);

    //// Calloc
    // int *c_ptr, i;
    // c_ptr = (int *)calloc(10,sizeof(int));
    // printf("\n marks = %pc\n", c_ptr); // print the base or beginning // address of allocated memory
    // printf("\n marks = %xc\n", c_ptr); // print the base or beginning // address of allocated memory
    // for (i = 0; i < 10; i++)
    // {
    //     *(c_ptr+i) = i*20;
    // }
    // Display(c_ptr, 10);
    // // free(c_ptr);

    // //// Re-alloc
    // c_ptr = realloc(c_ptr, 5*sizeof(int));
    // for (i = 10; i < 20; i++)
    // {
    //     *(c_ptr+i) = i*30;
    // }
    // Display(c_ptr, 20);
    // free(c_ptr);
    // c_ptr=NULL;


}