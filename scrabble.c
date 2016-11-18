#include<stdio.h>
#include"color.h"
#include"tool.h"
#include"string.h"
#include"windows.h"
#include"stdlib.h"
#define dic 178691
#define KEY_UP          72
#define KEY_LEFT        75
#define KEY_RIGHT       77
#define KEY_DOWN        80
#define KEY_ENTER       13
#define KEY_BS          8
int tile_sack[100]={0};
int bonuscore_loc[15][15]={ {5,0,0,2,0,0,0,5,0,0,0,5,0,0,5},
                              {0,4,0,0,0,3,0,0,0,3,0,0,0,4,0},
                              {0,0,4,0,0,0,2,0,2,0,0,0,4,0,0},
                              {2,0,0,4,0,0,0,2,0,0,0,4,0,0,5},
                              {0,0,0,0,4,0,0,0,0,0,4,0,0,0,0},
                              {0,3,0,0,0,3,0,0,0,3,0,0,0,3,0},
                              {0,0,2,0,0,0,2,0,2,0,0,0,2,0,0},
                              {5,0,0,2,0,0,0,1,0,0,0,2,0,0,5},
                              {0,0,2,0,0,0,2,0,2,0,0,0,2,0,0},
                              {0,3,0,0,0,3,0,0,0,3,0,0,0,3,0},
                              {0,0,0,0,4,0,0,0,0,0,4,0,0,0,0},
                              {2,0,0,4,0,0,0,2,0,0,0,4,0,0,2},
                              {0,0,4,0,0,0,2,0,2,0,0,0,4,0,0},
                              {0,4,0,0,0,3,0,0,0,3,0,0,0,4,0},
                              {5,0,0,2,0,0,0,5,0,0,0,2,0,0,5}};

char board[100][100]={" _____________________________________________________________",
                      "|+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+|",
                      "||TWS|   |   |DLS|   |   |   |TWS|   |   |   |DLS|   |   |TWS||",
                      "|+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+|",
                      "||   |DWS|   |   |   |TLS|   |   |   |TLS|   |   |   |DWS|   ||",
                      "|+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+|",
                      "||   |   |DWS|   |   |   |DLS|   |DLS|   |   |   |DWS|   |   ||",
                      "|+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+|",
                      "||DLS|   |   |DWS|   |   |   |DLS|   |   |   |DWS|   |   |DLS||",
                      "|+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+|",
                      "||   |   |   |   |DWS|   |   |   |   |   |DWS|   |   |   |   ||",
                      "|+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+|",
                      "||   |TLS|   |   |   |TLS|   |   |   |TLS|   |   |   |TLS|   ||",
                      "|+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+|",
                      "||   |   |DLS|   |   |   |DLS|   |DLS|   |   |   |DLS|   |   ||",
                      "|+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+|",
                      "||TWS|   |   |DLS|   |   |   |STR|   |   |   |DLS|   |   |TWS||",
                      "|+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+|",
                      "||   |   |DLS|   |   |   |DLS|   |DLS|   |   |   |DLS|   |   ||",
                      "|+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+|",
                      "||   |TLS|   |   |   |TLS|   |   |   |TLS|   |   |   |TLS|   ||",
                      "|+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+|",
                      "||   |   |   |   |DWS|   |   |   |   |   |DWS|   |   |   |   ||",
                      "|+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+|",
                      "||DLS|   |   |DWS|   |   |   |DLS|   |   |   |DWS|   |   |DLS||",
                      "|+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+|",
                      "||   |   |DWS|   |   |   |DLS|   |DLS|   |   |   |DWS|   |   ||",
                      "|+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+|",
                      "||   |DWS|   |   |   |TLS|   |   |   |TLS|   |   |   |DWS|   ||",
                      "|+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+|",
                      "||TWS|   |   |DLS|   |   |   |TWS|   |   |   |DLS|   |   |TWS||",
                      "|+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+|",
                      " -------------------------------------------------------------"};
char display_rack[5][60]={" ___________________Your_Tile_____________________",
                          "|                                                 |",
                          "|                                                 |",
                          "| 				                  |",
                          "|_________________________________________________|"};
void put_tile(char *rack,char key,char *p,int x,int y){
    int i;
    if(key==KEY_BS&&(*(p+((15*y)+x))>=65&&*(p+((15*y)+x))<=90)){
        //fix board
        walk(70,5);
        printf("%d %d",x,y);
        walk(((x)*4)+2,(y*2)+2);
        printf("%c%c%c",board[y*2+2][x*4+2],board[y*2+2][x*4+3],board[y*2+2][x*4+4]);
        walk(((x)*4)+3,(y*2)+2);
        //fix rack


    }
    key-=32;
    for(i=0;i<strlen(rack);i++){
        if(rack[i]==key){
                walk(((x)*4)+2,(y*2)+2);
                textcolor(14,0);printf(" %c ",rack[i]);resetcolor();
                walk(((x)*4)+3,(y*2)+2);
                *(p+((15*y)+x))=rack[i];
                rack[i]='0';
                break;
        }
    }

}

void checkword(char *p,char word[]){
    int binary=dic/2,N,x,e=0;
    N=binary;
    while(strcmp(word,p+(N*20))!=0&&e!=8){
        x=strcmp(word,(p+(N*20)));
        //printf("before=%d  ",x);
        //printf("before=%-5d  word=%-20s binary=%-5d N=%-5d\n",x,(p+(N*20)),binary,N);
        switch(x){
        case 1: if(binary==0)N++;
                else N+=(binary/2);break;
        case -1:if(binary==0)N--;
                else N-=(binary/2);break;
        }
        binary/=2;
        if(binary==0)e++;
    }
    if(e==8)printf("\n invalid word");
    else printf("\n valid word");
}
void loaddic(char*word){
    FILE *fp;
    char *p;
    int i;
    char read[20];
    fp = fopen("word.txt","r");
    p=word;
    while (fgets(read, 20, fp) != NULL) {
        if(read[strlen(read)-1]=='\n')read[strlen(read)-1]='\0';
        strcpy(p,read);
        p+=20;
    }
}
void printtile(char *rack){
    int i,j;
    char *p;
    p=rack;
        //printf(" %d ",strlen(rack_me));
    textcolor(8,0);
    for(i=0;i<7;i++){
        for(j=0;j<3;j++){
            walk(i*7+65,j+28);
            if(j==0||j==2)printf(" +---+ ");
            else {printf(" | ");textcolor(14,0);printf("%c",*(rack+i));textcolor(8,0);printf(" | ");}
            printf("\n");
        }
    }
    printf("\n\n");



}
char draw(){
    char alphabet;
    int random;
    srand(time(NULL));
    do{
        random=rand()%100;
    }while(tile_sack[random]!=0);
    tile_sack[random]=1;
    if(random>=0&&random<9)alphabet='A';
    if(random>=9&&random<11)alphabet='B';
    if(random>=11&&random<13)alphabet='C';
    if(random>=13&&random<17)alphabet='D';
    if(random>=17&&random<29)alphabet='E';
    if(random>=29&&random<31)alphabet='F';
    if(random>=31&&random<34)alphabet='G';
    if(random>=34&&random<36)alphabet='H';
    if(random>=36&&random<45)alphabet='I';
    if(random>=45&&random<46)alphabet='J';
    if(random>=46&&random<47)alphabet='K';
    if(random>=47&&random<51)alphabet='L';
    if(random>=51&&random<53)alphabet='M';
    if(random>=53&&random<59)alphabet='N';
    if(random>=59&&random<67)alphabet='O';
    if(random>=67&&random<69)alphabet='P';
    if(random>=69&&random<70)alphabet='Q';
    if(random>=70&&random<76)alphabet='R';
    if(random>=76&&random<80)alphabet='S';
    if(random>=80&&random<86)alphabet='T';
    if(random>=86&&random<90)alphabet='U';
    if(random>=90&&random<92)alphabet='V';
    if(random>=92&&random<94)alphabet='W';
    if(random>=94&&random<95)alphabet='X';
    if(random>=95&&random<97)alphabet='Y';
    if(random>=97&&random<98)alphabet='Z';
    if(random>=98&&random<100)alphabet=32;
    return alphabet;
}
void printboard(){
    int i,j;
    for(i=0;i<33;i++){
            for(j=0;j<63;j++){
                textcolor(8,0);
                printf("%c",board[i][j]);
                resetcolor();
            }
        printf("\n");
    }
    for(i=0;i<15;i++){
            for(j=0;j<15;j++){
                walk((j*4)+2,(i*2)+2);
                if(bonuscore_loc[i][j]==1){textcolor(13,0);printf(" %c ",003);}
                if(bonuscore_loc[i][j]==2){textcolor(11,0);printf("DLS");}
                if(bonuscore_loc[i][j]==3){textcolor(1,0);printf("TLS");}
                if(bonuscore_loc[i][j]==4){textcolor(13,0);printf("DWS");}
                if(bonuscore_loc[i][j]==5){textcolor(12,0);printf("TWS");}
                resetcolor();
            }
        printf("\n");
    }
    printf("\n\n");
}
void main(){
    int i,j,player=2,*score;
    char *rack,word_map[15][15],preword[15][15]={};
    char *dictionary,*p,word[20];
    rack=(char*)malloc(sizeof(char)*8*player);
    dictionary = (char *)malloc(dic*20);
    score=(int*)malloc(sizeof(int)*2);
    printboard();
    //draw tile
    p=rack;
    for(i=0;i<player;i++,p+=8){
            for(j=0;j<8;j++){
                    *(p+j)=draw();
                    if(j==7)*(p+j)='\0';
            }
    }
    p=rack;


    //print rack
    for(i=0;i<5;i++){
        walk(64,i+27);
        textcolor(8,0);
        printf("%s\n",display_rack[i]);
        resetcolor();
    }
    printtile(rack);
    //load dictionnary
    loaddic(dictionary);

    //------------main game---------------
    //cursor movement and put tile
    char key;
    int x=7,y=7;

    walk((x*4)+3,(x*2)+2);

    do{
        fflush(stdin);
        //getch();
        //getch();
        switch(key=getch()){
        case KEY_UP   :if(y>0)walk((x*4)+3,((--y)*2)+2);break;
        case KEY_DOWN :if(y<14)walk((x*4)+3,((++y)*2)+2);break;
        case KEY_LEFT :if(x>0)walk(((--x)*4)+3,(y*2)+2);break;
        case KEY_RIGHT:if(x<14)walk(((++x)*4)+3,(y*2)+2);break;
        default:put_tile(rack,key,&preword,x,y);
       }

    }while(key!=KEY_ENTER);

    int c=0;
    for(i=0;i<15;i++){
        for(j=0;j<15;j++){
            if(preword[i][j]>=65&&preword[i][j]<=90){word[c]=preword[i][j];c++;}
            word[c+1]='\0';
        }
    }
    walk(70,5);
    printf(" %s\n ",word);
    checkword(dictionary,word);
    walk(70,40);
    //getch();



    free(dictionary);
    free(score);

}
