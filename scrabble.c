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
int wpos[15][15]={0},wpos_temp[15][15]={0};
char wmap[15][15],wmap_temp[15][15];
int tile_sack[100]={0},tile_left=100;
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
                      "||TWS|   |   |DLS|   |   |   |   |   |   |   |DLS|   |   |TWS||",
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
                          "|                                                 |",
                          "|_________________________________________________|"};

void put_tile(char *rack,char key,int x,int y,int n){
    int i;
    if(key==KEY_BS&&(wmap_temp[y][x]>=63&&wmap_temp[y][x]<=90)){
        //fix board
        walk(((x)*4)+2,(y*2)+2);
        if(bonuscore_loc[y][x]==2)textcolor(11,0);
        if(bonuscore_loc[y][x]==3)textcolor(1,0);
        if(bonuscore_loc[y][x]==4)textcolor(13,0);
        if(bonuscore_loc[y][x]==5)textcolor(12,0);
        printf("%c%c%c",board[y*2+2][x*4+2],board[y*2+2][x*4+3],board[y*2+2][x*4+4]);
        resetcolor();
        walk(((x)*4)+3,(y*2)+2);
        //fix rack
        for(i=0;i<strlen(rack);i++){
            if(rack[i]=='0'){rack[i]=wmap_temp[y][x];break;}
        }
        //Delete wmap_temp
        wmap_temp[y][x]='0';
        wpos_temp[y][x]=0;
    }
    //convert capital letter
    if(key==47)key=63;
    else key-=32;
    //put the tile on board
    if(wpos_temp[y][x]==0){
        for(i=0;i<strlen(rack);i++){
            if(rack[i]==key){
                    walk(((x)*4)+2,(y*2)+2);
                    textcolor(14,0);printf(" %c ",rack[i]);resetcolor();
                    walk(((x)*4)+3,(y*2)+2);
                    wmap_temp[y][x]=rack[i];
                    wpos_temp[y][x]=1;
                    rack[i]='0';
                    break;
            }
            //if tile blank
        }
    }
    //update tile on rack
    printrack(rack,n);
    walk((x*4)+3,(y*2)+2);
}
void checkword(char *p,char word[]){
    int binary=dic/2,N,x,e=0;
    N=binary;
    while(strcmp(word,p+(N*20))!=0&&e!=8){
        x=strcmp(word,(p+(N*20)));
        switch(x){
        case 1: if(binary==0)N++;
                else N+=(binary/2);break;
        case -1:if(binary==0)N--;
                else N-=(binary/2);break;
        }
        binary/=2;
        if(binary==0)e++;
    }
    walk(70,6);
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
char draw(){
    char alphabet;
    int random;
    srand(time(NULL));
    if(tile_left!=0){
        do{
            random=rand()%100;
        }while(tile_sack[random]!=0);
        tile_left--;
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
        if(random>=98&&random<100)alphabet='?';
    }else alphabet='0';
    return alphabet;
}
void fillrack(char *r){
    int i;
    for(i=0;i<7;i++,r++){
        if(*r=='0')*r=draw();
    }
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
void printrack(char *r,int n){
    int i;
    for(i=0;i<5;i++){
        walk(64,i+27);
        textcolor(8,0);
        if(i==0){printf(" ____________________",n+1);
                textcolor(10,0);printf("Player %d",n+1);textcolor(8,0);
                printf("_____________________\n");
                }
        else if(i==4)printf("|_________________________________________________|");
        else printf("|                                                 |\n");
        //printf("%s\n",display_rack[i]);
        resetcolor();
    }
        printtile(r);
}
void printtile(char *r){
    int i,j,c=0,sc;//special_c
    char rack_out[8];
    textcolor(8,0);
    for(i=0;i<7;i++,r++){
        if(*r>=63&&*r<=90){rack_out[c]=*r;c++;}
    }
    rack_out[c]='\0';
    for(i=0;i<strlen(rack_out);i++){
        for(j=0;j<3;j++){
            walk(i*7+65+(21-3*c),j+28);
            if(j==0||j==2)printf(" +---+ ");
            else {printf(" | ");textcolor(14,0);printf("%c",rack_out[i]);textcolor(8,0);printf(" | ");}
            printf("\n");
        }
    }
    printf("\n\n");
}
int endgame(int n,char*r){
    int i,j,c=0,e=0;
    for(i=0;i<n;i++,r+=8){
        for(j=0;j<7;j++){
            if(*(r+j)>=63&&*(r+j)<=90)c++;
        }
        if(c==0)e=1;
    }
    return e;
}
int rule_check(int turn,int player){
    int i,j,e=0;
    //rule 1 : the first turn. the word must place on heart(center of the board)
    if(turn==0&&player==0){
        if(wpos_temp[7][7]!=0)e=1;
        else{
            walk(70,23);printf("the game's first word always needs one\n");
            walk(70,24);printf("       letter on center square\n");
            walk(70,25);printf("          give it another ago");
            getch();
            walk(70,23);printf("                                      ");
            walk(70,24);printf("                                      ");
            walk(70,25);printf("                                      ");
            }
    }else e=1;
    //rule 2 : the tile that you put,must be touching or in the same line

    return e;
}
void cpyarr(){
    int i,j;
    for(i=0;i<15;i++){
        for(j=0;j<15;j++){
            wpos_temp[i][j]=wpos[i][j];
            wmap_temp[i][j]=wmap[i][j];
        }
    }
}
void mergearr(){
    int i,j;
    for(i=0;i<15;i++){
        for(j=0;j<15;j++){
            if(wpos_temp[i][j]!=0){
                wpos[i][j]=wpos_temp[i][j];
                wmap[i][j]=wmap_temp[i][j];
            }
        }
    }
}
void findword(char *word){
    int i,j,c,t,b,x,y;
    char letter[16];
    for(i=0;i<15;i++){
        c=0;
        for(j=0;j<15;j++){
            if(wpos_temp[i][j]==2)c++;
        }
        if(c>1){t=1;b=0;break;}
        else {b=1;t=0;}
    }
    //check tree

    for(i=0;i<15;i++){
        for(j=0;j<15;j++,word+=16){
        if(wpos_temp[i][j]==1){
            y=i;x=j;
            findh(&x,&y,t);

            collectw(x,y,b,&letter);
            printf("%s",letter);
            break;
        }
    }
    }

    //check branch
    for(i=0;i<15;i++){
        for(j=0;j<15;j++,word+=16){
        if(wpos_temp[i][j]==1){
            y=i;x=j;
            findh(&x,&y,b);
            collectw(x,y,b,&letter);
            delay(500);
            printf("%s",letter);
        }
    }
    }
}
void findh(int *x,int*y,int w){
    if(w==0){
    while(wpos_temp[*y-1][*x]!=0){
        *y-=1;
    }
    }//find vertical
    if(w==1){
    while(wpos_temp[*y][*x-1]!=0){
        *x-=1;
    }
    }//find horizontal
}
void collectw(int x,int y,int w,char *letter){
    int i=0;
    if(w==0){
    while(wpos_temp[y+1][x]!=0){
        *(letter+i)=wmap_temp[y][x];
        i++;
        y++;
    }
    }//find vertical
    if(w==1){
    while(wpos_temp[y][x+1]!=0){
        *(letter+i)=wmap_temp[y][x];
        i++;
        x++;

    }
    }//find horizontal
    *(letter+i)='\0';

}
void main(){
    int i,j,player=2,*score;
    char *rack,preword[15][15]={'0'};
    char *dictionary,*p,*word;;
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
    //load dictionnary
    loaddic(dictionary);
    //------------main game---------------
    char key;
    int x=7,y=7,n,end,rule,correct,turn=0,b=0;
    end=endgame(player,rack);
    p=rack;
    while(end!=1){
        //x=7;y=7;
        p=rack;
        for(n=0;n<2;n++,p+=8){
                rule=0;correct=0;
                memset(preword,'0', 225);
                //print rack
                printrack(p,n);
                walk((x*4)+3,(y*2)+2);
                fflush(stdin);
                while(rule!=1||correct!=1){
                    //----------------------build temp array-------------------
                    if(rule==0&&correct==0){for(i=0;i<15;i++){
                                                for(j=0;j<15;j++){
                                                    wpos_temp[i][j]=wpos[i][j];
                                                    wmap_temp[i][j]=wmap[i][j];
                                                }
                                            }
                    }//--------------------------------------------------------
                    do{
                        fflush(stdin);
                        switch(key=getch()){
                        case KEY_UP   :if(y>0)walk((x*4)+3,((--y)*2)+2);break;
                        case KEY_DOWN :if(y<14)walk((x*4)+3,((++y)*2)+2);break;
                        case KEY_LEFT :if(x>0)walk(((--x)*4)+3,(y*2)+2);break;
                        case KEY_RIGHT:if(x<14)walk(((++x)*4)+3,(y*2)+2);break;
                        default:put_tile(p,key,x,y,n);
                        }
                    }while(key!=KEY_ENTER);
                    //check rule

                    rule=rule_check(turn,n);

                    correct=1;

                    //rule_check(i,j,&preword);
                    //check word
                }
                //---------------merge array----------------
                for(i=0;i<15;i++){
                    for(j=0;j<15;j++){
                        if(wpos_temp[i][j]!=0){
                            wpos[i][j]=2;
                            wmap[i][j]=wmap_temp[i][j];
                        }
                    }
                }//-----------------------------------------

                //find word
                char *w;
                word=(char*)malloc(sizeof(char)*16*5);
                findword(word);
                w=word;
                for(i=0;i<5;i++,w+=16){
                    walk(60,20+i);
                    printf("%s\n",*w);
                }
                fillrack(p);
        }
        end=endgame(player,rack);
        turn++;
    }

    //getch();


    free(word);
    free(dictionary);
    free(score);

}
