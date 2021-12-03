#include <stdio.h>
#include <time.h> 
#include <math.h>
#include <stdlib.h>
struct game{
    int elements_types;
    int map_lenth;
    int map_wide;
    int score;
    int score_target;
}games[] = 
{
    {4, 5, 5, 0, 400},
    {4, 5, 5, 0, 800},
    {4, 5, 5, 0, 1000},
    {5, 5, 5, 0, 1200},
    {5, 7, 7, 0, 1000},
    {6, 7, 7, 0, 1000}
};
//设置关卡数组
int ii=0;
int map0[5][5],map1[7][7],trans[2],ver[2],tmp,a0,a1,b0,b1,step,i,j,cnt=0,m,n,stute,t_score=0;
void creatmap(void){
        if(ii<4){
            for(i=0;i<games[ii].map_lenth;i++){
                for(j=0;j<games[ii].map_wide;j++){
                    map0[i][j]=rand()%games[ii].elements_types;
                }
            }
        
//创建地图
            do{
                cnt=0;
                for(i=1;i<games[ii].map_lenth-1;i++){
                    for(j=0;j<games[ii].map_wide;j++){
                        if(map0[i-1][j]==map0[i][j] && map0[i][j]==map0[i+1][j]){
                            map0[i][j]=rand()%games[ii].elements_types;
                            cnt++;
                        }
                    }
                }
                for(i=0;i<games[ii].map_lenth;i++){
                    for(j=1;j<games[ii].map_wide-1;j++){
                        if(map0[i][j-1]==map0[i][j] && map0[i][j]==map0[i][j+1]){ 
                            map0[i][j]=rand()%games[ii].elements_types;
                            cnt++;
                        }
                    }
                }
            }while(cnt!=0);
        }
        else{
            for(i=0;i<games[ii].map_lenth;i++){
                for(j=0;j<games[ii].map_wide;j++){
                    map1[i][j]=rand()%games[ii].elements_types;
                }
            }
        
//创建地图
            do{
                cnt=0;
                for(i=1;i<games[ii].map_lenth-1;i++){
                    for(j=0;j<games[ii].map_wide;j++){
                        if(map1[i-1][j]==map1[i][j] && map1[i][j]==map1[i+1][j]){
                            map1[i][j]=rand()%games[ii].elements_types;
                            cnt++;
                        }
                    }
                }
                for(i=0;i<games[ii].map_lenth;i++){
                    for(j=1;j<games[ii].map_wide-1;j++){
                        if(map1[i][j-1]==map1[i][j] && map1[i][j]==map1[i][j+1]){ 
                            map1[i][j]=rand()%games[ii].elements_types;
                            cnt++;
                        }
                    }
                }
            }while(cnt!=0);
        }
    }
//消除新建地图的重复元素
void displayA(void){
    int i,j,color;
    // char scolor[8] = "color ";
    // scolor[6] = color + 48;
    system("cls");
    // system("color f5");
    printf("Chapter : %d/5\n",ii);
    printf("Step : %d\n",step);
    printf("Score : %d/%d\n",games[ii].score,games[ii].score_target);
    printf("************************\n");
    if(ii<4){    
        for(i=0;i<games[ii].map_lenth;i++){
            for(j=0;j<games[ii].map_wide;j++){
                // color = map0[i][j]%games[ii].elements_types;
                // scolor[6] = color + 48;
                //system(scolor);
                if(map0[i][j] == 0){
                    printf("\033[40;31;1m%d ",map0[i][j]);
                }else if(map0[i][j] == 1){
                    printf("\033[40;32;1m%d ",map0[i][j]);
                }else if(map0[i][j] == 2){
                    printf("\033[40;33;1m%d ",map0[i][j]);
                }else if(map0[i][j] == 3){
                    printf("\033[40;34;1m%d ",map0[i][j]);
                }else if(map0[i][j] == 4){
                    printf("\033[40;35;1m%d ",map0[i][j]);
                }else{
                    printf("\033[40;36;1m%d ",map0[i][j]);
                }
            }
            if(j%games[ii].map_wide==0){
                printf("\n");
            }
        }  
        printf("\033[0m************************\n");  
    }else{
        for(i=0;i<games[ii].map_lenth;i++){
            for(j=0;j<games[ii].map_wide;j++){
                // color = map1[i][j]%games[ii].elements_types;
                // scolor[6] = color + 48;
                // printf("%d ",map1[i][j]);
                if(map1[i][j] == 0){
                    printf("\033[40;31;1m%d ",map1[i][j]);
                }else if(map1[i][j] == 1){
                    printf("\033[40;32;1m%d ",map1[i][j]);
                }else if(map1[i][j] == 2){
                    printf("\033[40;33;1m%d ",map1[i][j]);
                }else if(map1[i][j] == 3){
                    printf("\033[40;34;1m%d ",map1[i][j]);
                }else if(map1[i][j] == 4){
                    printf("\033[40;35;1m%d ",map1[i][j]);
                }else{
                    printf("\033[40;36;1m%d ",map1[i][j]);
                }
            }
            if(j%games[ii].map_wide==0){
                printf("\n");
            }
        }  
        printf("\033[0m************************\n");  
        }
}//打印地图
void elimate(int a0 ,int a1){           //eliminate elements
    if(ii<4){
        for(i=1,cnt=0;a0-i>=0;i++){
                    if(map0[a0-i][a1]==map0[a0][a1]){
                        cnt++;
                    }else{
                        break;
                    }
                }
        trans[0]=cnt;
        for(i=1,cnt=0;a0+i<games[ii].map_lenth;i++){
            if(map0[a0+i][a1]==map0[a0][a1]){
                cnt++;
            }else{
                break;
            }
        }
        trans[1]=cnt;
        for(i=1,cnt=0;a1-i>=0;i++){
            if(map0[a0][a1-i]==map0[a0][a1]){
                cnt++;
            }else{
                break;
            }
        }
        ver[0]=cnt;
        for(i=1,cnt=0;a1+i<games[ii].map_wide;i++){
            if(map0[a0][a1+i]==map0[a0][a1]){
                cnt++;
            }else{
                break;
            }
        }
        ver[1]=cnt;
        //count repeat elements
        if((trans[0]+trans[1])>=(ver[0]+ver[1]) && (trans[0]+trans[1])>1){
            if(a0-trans[0]==0){
                for(i=0;a0+trans[1]-i>=0;i++){
                    map0[i][a1]=rand()%games[ii].elements_types;
                }
            }else{
                for(i=0;a0-trans[0]-i-1>=0;i++){
                    map0[a0+trans[1]-i][a1]=map0[a0-trans[0]-i-1][a1];
                }
                for(;a0+trans[1]-i>=0;i++){
                    map0[a0+trans[1]-i][a1]=rand()%games[ii].elements_types;
                }
            }
            step++;
            games[ii].score+=200;
        }else if((trans[0]+trans[1])<(ver[0]+ver[1]) && (ver[0]+ver[1])>1){
                if(a0==0){
                    for(i=a1-ver[0];i<=a1+ver[1];i++){
                        map0[a0][i]=rand()%games[ii].elements_types;
                    }
                }else{
                    for(j=a1-ver[0];j<=a1+ver[1];j++){
                        for(i=0;a0-i-1>=0;i++){
                            map0[a0-i][j]=map0[a0-i-1][j];
                        }
                        map0[0][j]=rand()%games[ii].elements_types;
                    }
                }
                step++;
                games[ii].score+=200;
        }else{
            tmp=map0[a0][a1];
            map0[a0][a1]=map0[b0][b1];
            map0[b0][b1]=tmp;
            step--;
        }
    }else{
        for(i=1,cnt=0;a0-i>=0;i++){
            if(map1[a0-i][a1]==map1[a0][a1]){
                cnt++;
            }else{
                break;
           }
        }
        trans[0]=cnt;
        for(i=1,cnt=0;a0+i<games[ii].map_lenth;i++){
            if(map1[a0+i][a1]==map1[a0][a1]){
                cnt++;
            }else{

                break;
            }
        }
        trans[1]=cnt;
        for(i=1,cnt=0;a1-i>=0;i++){
            if(map1[a0][a1-i]==map1[a0][a1]){
                cnt++;
            }else{
                break;
            }
        }
        ver[0]=cnt;
        for(i=1,cnt=0;a1+i<games[ii].map_wide;i++){
            if(map1[a0][a1+i]==map1[a0][a1]){
                cnt++;
            }else{
                break;
            }
        }
        ver[1]=cnt;
        //count repeat elements
        if((trans[0]+trans[1])>=(ver[0]+ver[1]) && (trans[0]+trans[1])>1){
            if(a0-trans[0]==0){
                for(i=0;a0+trans[1]-i>=0;i++){
                    map1[i][a1]=rand()%games[ii].elements_types;
                }
            }else{
                for(i=0;a0-trans[0]-i-1>=0;i++){
                    map1[a0+trans[1]-i][a1]=map1[a0-trans[0]-i-1][a1];
                }
                for(;a0+trans[1]-i>=0;i++){
                    map1[a0+trans[1]-i][a1]=rand()%games[ii].elements_types;
                }
            }
            step++;
            games[ii].score+=200;
        }else if((trans[0]+trans[1])<(ver[0]+ver[1]) && (ver[0]+ver[1])>1){
                if(a0==0){
                    for(i=a1-ver[0];i<=a1+ver[1];i++){
                        map1[a0][i]=rand()%games[ii].elements_types;
                    }
                }else{
                    for(j=a1-ver[0];j<=a1+ver[1];j++){
                        for(i=0;a0-i-1>=0;i++){
                            map1[a0-i][j]=map1[a0-i-1][j];
                        }
                        map1[0][j]=rand()%games[ii].elements_types;
                    }
                }
                step++;
                games[ii].score+=200;
        }else{
            tmp=map1[a0][a1];
            map1[a0][a1]=map1[b0][b1];
            map1[b0][b1]=tmp;
            step--;
        }
    }
}//消除算法
int main(){ 
    srand((unsigned)time(NULL));
    // FILE *f_rank = fopen("rank.txt","r"); That is too difficult!
    for(ii=0;ii<6;ii++){
        if(ii<4){
            step = 5;
            creatmap();
            displayA();
            // if(ii>0){
            //     printf("Pass!!!\n");
            // }
            while(1){
                if(step==0){
                    printf("Game Over!\n");
                    t_score += games[ii].score;
                    goto over;
                }
                if(games[ii].score >= games[ii].score_target){
                    t_score += games[ii].score;
                    break;
                }
                printf("entrer the num u want to change!(first point will elimated)\n");
                scanf("%d %d %d %d",&a0,&a1,&b0,&b1);
                if(abs(a0-b0)+abs(a1-b1)>2){
                    step--;
                }else{
                    tmp=map0[a0][a1];
                    map0[a0][a1]=map0[b0][b1];
                    map0[b0][b1]=tmp;
                    elimate(a0,a1);
                    //exchange tow elements
                    
                    // system("clear\n");
                }
                displayA();
                printf("%d %d %d %d\n",trans[0],trans[1],ver[0],ver[1]);
                do{
                    stute=0;
                    for(i=0;i<games[ii].map_lenth;i++){
                        for(j=0;j+2<games[ii].map_wide;j++){
                            if(map0[i][j] == map0[i][j+1] && map0[i][j] == map0[i][j+2]){
                                elimate(i,j);
                                stute++;
                                goto aa;
                            }
                        }
                    }
        aa:         for(j=0;j<games[ii].map_wide;j++){
                        for(i=0;i+2<games[ii].map_lenth;i++){
                            if(map0[i][j] == map0[i+1][j] && map0[i][j] == map0[i+2][j]){
                                elimate(i,j);
                                stute++;
                                goto bb;
                            }
                        }
                    }
        bb:         displayA();
                }while(stute);
                //判断死局
                for(i=0;i<games[ii].map_lenth;i++){
                    for(j=0;j+2<games[ii].map_wide;j++){
                        if(map0[i][j] == map0[i][j+1] || map0[i][j] == map0[i][j+2] || map0[i][j+1] == map0[i][j+2]){
                            stute++;
                            goto aaa;
                        }
                    }
                }
        aaa:         for(j=0;j<games[ii].map_wide;j++){
                    for(i=0;i+2<games[ii].map_lenth;i++){
                        if(map0[i][j] == map0[i+1][j] || map0[i][j] == map0[i+2][j] || map0[i+1][j] == map0[i+2][j]){
                            stute++;
                            goto bbb;
                        }
                    }
                }
        bbb:     if(stute==0){
                    printf("This map is dead!\n");
                    creatmap();
                    // displayA();
                }
            }
        }else{
            step = 5;
            creatmap();
            displayA();
            while(1){
                if(step==0){
                    printf("Game Over!\n");
                    t_score += games[ii].score;
                    goto over;
                }
                if(games[ii].score >= games[ii].score_target){
                    t_score += games[ii].score;
                    break;
                }
                printf("entrer the num u want to change!(first point will elimated)\n");
                scanf("%d %d %d %d",&a0,&a1,&b0,&b1);
                if(abs(a0-b0)+abs(a1-b1)>2){
                    step--;
                }else{
                    tmp=map1[a0][a1];
                    map1[a0][a1]=map1[b0][b1];
                    map1[b0][b1]=tmp;
                    elimate(a0,a1);
                    //exchange tow elements
                    
                    // system("clear\n");
                }
                displayA();
                printf("%d %d %d %d\n",trans[0],trans[1],ver[0],ver[1]);
                do{
                    stute=0;
                    for(i=0;i<games[ii].map_lenth;i++){
                        for(j=0;j+2<games[ii].map_wide;j++){
                            if(map1[i][j] == map1[i][j+1] && map1[i][j] == map1[i][j+2]){
                                elimate(i,j);
                                stute++;
                                goto aa1;
                            }
                        }
                    }
        aa1:         for(j=0;j<games[ii].map_wide;j++){
                        for(i=0;i+2<games[ii].map_lenth;i++){
                            if(map1[i][j] == map1[i+1][j] && map1[i][j] == map1[i+2][j]){
                                elimate(i,j);
                                stute++;
                                goto bb1;
                            }
                        }
                    }
        bb1:         displayA();
                }while(stute);
                //判断死局
                for(i=0;i<games[ii].map_lenth;i++){
                    for(j=0;j+2<games[ii].map_wide;j++){
                        if(map1[i][j] == map1[i][j+1] || map1[i][j] == map1[i][j+2] || map1[i][j+1] == map1[i][j+2]){
                            stute++;
                            goto aaa1;
                        }
                    }
                }
        aaa1:         for(j=0;j<games[ii].map_wide;j++){
                    for(i=0;i+2<games[ii].map_lenth;i++){
                        if(map1[i][j] == map1[i+1][j] || map1[i][j] == map1[i+2][j] || map1[i+1][j] == map1[i+2][j]){
                            stute++;
                            goto bbb1;
                        }
                    }
                }
        bbb1:     if(stute==0){
                    printf("This map is dead!\n");
                    creatmap();
                    // displayA();
                }
            }
        }
    }
over:      
    if(ii == 6){
        ii--;
    }
    displayA();
    printf("Your score : %d\n",t_score);
    printf("Thank u for playing my game!\n");
    return 0;
}