#include<stdio.h>
#include"color.h"
    int array[11][11]={{0,0,0,0,0,0,0,0,0,0},
                        {0,0,0,0,2,2,2,2,0,0},
                        {0,0,0,0,2,0,0,0,2,0},
                        {0,0,0,0,2,0,2,0,2,0},
                        {0,0,0,2,2,2,2,0,2,0},
                        {0,0,0,2,2,1,1,1,1,0},
                        {0,0,0,2,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0,0,0}};
void findh(int *x,int*y,int w){
    if(w==0){
    while(array[*y-1][*x]!=0){
        *y-=1;
    }
    }//find vertical
    if(w==1){
    while(array[*y][*x-1]!=0){
        *x-=1;
    }
    }//find horizontal
}
void findt(int x,int y,int w){
    if(w==0){
    while(array[y+1][x]!=0){
        y++;
    }
    }//find vertical
    if(w==1){
    while(array[y][x+1]!=0){
        x++;
    }
    }//find horizontal
     printf("(%d,%d)\n",y,x);
}
void main(){

    int i,j;
        for(i=0;i<11;i++){
        for(j=0;j<11;j++){
        if(array[i][j]==1)textcolor(10,0);
        if(array[i][j]==2)textcolor(14,0);
        if(array[i][j]==0)textcolor(8,0);
        printf("%d ",array[i][j]);
        resetcolor();
    }
    printf("\n");
    }
    //check direct
    int c,t,b,x,y;
    for(i=0;i<11;i++){
        c=0;
        for(j=0;j<11;j++){
            if(array[i][j]==2)c++;
        }
        if(c>1){t=1;b=0;break;}
        else {b=1;t=0;}
    }
    //check tree
    printf("tree\n");
    for(i=0;i<11;i++){
        for(j=0;j<11;j++){
        if(array[i][j]==1){
            printf("Head(%d,%d): ",i,j);
            y=i;x=j;
            findh(&x,&y,t);
            printf("(%d,%d) ",y,x);
            findt(x,y,b);
            break;
        }
    }
    }
    printf("branch\n");
    //check branch
    for(i=0;i<11;i++){
        for(j=0;j<11;j++){
        if(array[i][j]==1){
            printf("Head(%d,%d): ",i,j);
            y=i;x=j;
            findh(&x,&y,b);
            printf("(%d,%d) ",y,x);
            findt(x,y,b);
            getch();
        }
    }
    }

}
