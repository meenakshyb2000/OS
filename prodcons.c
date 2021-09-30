#include<stdio.h>
#include<omp.h>
int buffer[50];
int s=1;  //binary semaphore
int empty,full; //counting semaphores
int n,i;
int wait(int a)
{
    return --a;
}
int signal(int a)
{
    return ++a;
}
void PRODUCE()
{
    s=wait(s);
    empty=wait(empty);
    printf("Item produced!\n");
    buffer[i++]=1;
    full=signal(full);
    s=signal(s);
}

void CONSUME()
{
    s=wait(s);
    full=wait(full);
    printf("Item consumed!\n");
    buffer[--i]=0;
    empty=signal(empty);
    s=signal(s);
}
void print()
{
    for (int j=0;j<n;j++)
        printf("%d ",buffer[j]);
    printf("\n");
}
void main()
{
    printf("Enter the size of buffer: "); 
    scanf("%d",&n);
    
    empty=n;
    full=0;
    int ch,i=0;
    for (int j=0;j<n;j++)
        buffer[j]=0;
    do
    {
        printf("\nOPTIONS:\n 1.PRODUCE\n 2.CONSUME\n 3.EXIT\n");
        printf("Enter your choice: ");
        scanf("%d",&ch);
        switch(ch)
        {
            case 1: if(s==1 && full!=n)
                    {    
                        PRODUCE();
                        printf(" BUFFER STATUS (1->occupied, 0->free)---->");
                        print();
                    }
                    else
                    {    
                        printf("\tCannot produce now!!\n");
                    }
                    break;
            case 2: if(s==1 && empty!=n)
                    {
                        CONSUME();
                        printf(" BUFFER STATUS (1->occupied, 0->free)---->");
                        print();
                    }
                    else
                    {
                        printf("\tCannot consume now!!\n");
                    }
                    break;
            case 3: printf("EXIT SUCCESSFUL ");
                    break;
            default:printf("Invalid choice!! Exiting");
        }
    }while(ch==1||ch==2);
}