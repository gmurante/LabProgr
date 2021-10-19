#include<stdio.h>
int main()
{
    int var,*ptr,**ptr_var;
    var=5;
    ptr=&var;
    ptr_var=&ptr;
    printf("\n\tAddresses");
    printf("\nAddress of var -> %d",&var);
    printf("\nAddress of ptr -> %d",&ptr);
    printf("\nAddress of ptr_var -> %d",&ptr_var);
    printf("\n\tContents");
    printf("\nContents in var -> %d",var);
    printf("\nContents in ptr -> %d",ptr);
    printf("\nContents in ptr_var -> %d",ptr_var);
    printf("\n\tIndirection");
    printf("\n*ptr implies -> %d",*ptr);
    printf("\n*ptr_var implies -> %d",*ptr_var);
    printf("\n**ptr_var implies -> %d\n",**ptr_var);
    return 0;
}
