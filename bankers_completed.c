#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct proc
{
    int alloc[5];
    int need[5];
    int max[5];
};

void disp();
int safe_state( int pn,int rn, char seq[]);

struct proc p[5];
char r[]={'A','B','C','D','E'};
int r_tot[5],r_avail[5],r_inter[5],pn,rn;

void main()
{
    int i,j,k=0,b,f,succ=0;
    char seq[5],temp;

    printf("\nEnter number of processes ?\n");
    scanf("%d",&pn);
    if(pn<2)
    {
        printf("\nThere should atleast be 2 processes !");
        getchar();
        exit(0);
    }
    printf("\nEnter number of resources ?\n");
    scanf("%d",&rn);

    for(i=0;i<pn;i++)
    {
        for(j=0;j<rn;j++)
        {
            printf("\nEnter number of instances of %c allocated to P%d \n",r[j],i);
            scanf("%d",&p[i].alloc[j]);

        }
    }

     for(i=0;i<pn;i++)
    {
        for(j=0;j<rn;j++)
        {
            printf("\nEnter maximum instances of %c required for P%d \n",r[j],i);
            scanf("%d",&p[i].max[j]);

        }
    }

    for(i=0;i<pn;i++)
    {
        for(j=0;j<rn;j++)
        {
            p[i].need[j] = p[i].max[j] - p[i].alloc[j];
        }
    }


    for(i=0;i<rn;i++)
    {
        printf("Enter the total instances of resource %c \n",r[i]);
        scanf("%d",&r_tot[i]);
    }

    for(i=0;i<5;i++)
    r_inter[i]=0;


    for(i=0;i<pn;i++)
    {
        for(j=0;j<rn;j++)
        {
            r_inter[j] = r_inter[j] + p[i].alloc[j];

        }
    }

    for(i=0;i<rn;i++)  //checks if the initial allocations can be satisfied
    {
        k=r_tot[i]-r_inter[i];
        if(k<0)
        {
            printf("\nNot enough resources !");
            getch();
            exit(0);
        }
        r_avail[i]=r_tot[i]-r_inter[i];
    }

disp();

printf("\nChecking for safe sequences if any !!!\n");
getchar();

//creating seq , for simplicity the programs takes as input up to 5 processes only
if(pn==2)
strcpy(seq,"01");
else if(pn==3)
strcpy(seq,"012");
else if(pn==4)
strcpy(seq,"01234");
else if(pn==5)
strcpy(seq,"012345");

k=1;

//permutation steps start here
for(i=1;i<=strlen(seq);i++)
{
k=k*i;
}
f=strlen(seq);
for(i=0;i<k;i++)
{
b=i%(f-1);
temp = seq[b+1];
seq[b+1]=seq[b];
seq[b]=temp;
succ=safe_state(pn,rn,seq);
if(succ==1)
{
    break;
}
}

}


void disp()
{
    int i,j;

    printf("\n\nAllocation Matrix\n");
    printf("\t");
    for(i=0;i<rn;i++)
    {
        printf("\t %c",r[i]);
    }

    for(i=0;i<pn;i++)
    {
        printf("\n Process P%d",i);
        for(j=0;j<rn;j++)
        {
            printf("\t %d",p[i].alloc[j]);
        }
    }


    printf("\n\nNeed Matrix\n");
    printf("\t");
    for(i=0;i<rn;i++)
    {
        printf("\t %c",r[i]);
    }

    for(i=0;i<pn;i++)
    {
        printf("\n Process P%d",i);
        for(j=0;j<rn;j++)
        {
            printf("\t %d",p[i].need[j]);
        }
    }

    printf("\n\nMaximum Matrix\n");
    printf("\t");
    for(i=0;i<rn;i++)
    {
        printf("\t %c",r[i]);
    }

    for(i=0;i<pn;i++)
    {
        printf("\n Process P%d",i);
        for(j=0;j<rn;j++)
        {
            printf("\t %d",p[i].max[j]);
        }
    }


    printf("\n\nInstances of resources available\n");
    for(i=0;i<rn;i++)
    {
      printf("\t %c",r[i]);
    }
    printf("\n");
    for(i=0;i<rn;i++)
    {
        printf("\t %d",r_avail[i]);
    }

}


int safe_state(int pn, int rn, char seq[])
{

int i,j,ravail[5],flag=0,cnt=0,prc=0,flag1=0;
struct proc pr[5];

 printf("\nSequence taken as input %s\n",seq);

 for(i=0;i<pn;i++)
 {
     for(j=0;j<rn;j++)
     {
         pr[i].alloc[j] = p[i].alloc[j];
         pr[i].need[j] = p[i].need[j];
     }
}

for(i=0;i<rn;i++)
{
    ravail[i]=r_avail[i];
}

for(i=0;i<pn;i++)
{
    prc=(int)seq[i];
    prc=prc-48;

    for(j=0;j<rn;j++)
    {
        if(pr[prc].need[j]<=ravail[j])
        {

        }
        else
        {
            flag=1;
        }
    }

    if(flag!=1)
    {
        cnt++;
        for(j=0;j<rn;j++)
        {
            ravail[j]=ravail[j]-pr[prc].need[j];
        }

        for(j=0;j<rn;j++)
        {
            ravail[j]=ravail[j]+pr[prc].need[j]+pr[prc].alloc[j];
        }
    }
    else
    {
        printf("\nSequence %s wont work\n",seq);
        flag1=1;
        break;
    }
}

if((cnt==pn) && (flag1!=1))
{
    printf("\nSequence %s runs to success\n",seq);
    return(1);
}
return(0);
}
