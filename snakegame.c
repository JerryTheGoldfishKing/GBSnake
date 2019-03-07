#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <conio.h>
#define row 30
#define column 40
#define lower 1
struct node{
  int x,y;
  char value;
  struct node *next;
};
struct food{
  int x,y;
  char value;
}f;
struct mine{
  int x,y;
  char value;
}m1[10];
struct wall{
  int x,y,length;
}wall[25];
int score = 0,level = 1,minecounter = 0,wallcounter = 0;
void clearscreen()
{
    HANDLE hOut;
    COORD Position;

    hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    Position.X = 0;
    Position.Y = 0;
    SetConsoleCursorPosition(hOut, Position);
}
void print(char board[row][column]){
    int i,j;
    clearscreen();
    for(i = 0; i < row; i++){
    for(j = 0; j < column; j++){
      printf("%c",board[i][j]);
    }
    printf("\n");
    }
}
struct node * createsnake(){
  struct node *ptr,*n,*head = NULL;
  int i,px,py;
  px = 5;
  py = 5;
  for(i = 0; i < 5; i++){
  n = (struct node*)malloc(sizeof(struct node));
  if(i == 0){
  n -> value = '@';
  n -> x = px;
  n -> y = py;
  }
  else if(i < 4){
    n -> value = '#';
    px++;
    n -> x = px;
    n -> y = py;
  }
  else{
    n -> value = '!';
    px++;
    n -> x = px;
    n -> y = py;
  }
  if(head == NULL){
    n -> next = NULL;
    head = n;
  }
  else{
    ptr = head;
    while(ptr -> next != NULL){
      ptr = ptr -> next;
    }
    ptr -> next = n;
    n -> next = NULL;
  }
  }
  return head;
}

void foodcheck(struct node *head){
    struct node *ptr,*ptr2;
    ptr = head;
    while(ptr != NULL){
    ptr2 = head;
    while(ptr2 != NULL){
        if((ptr2 -> x == f.x)&&(ptr2 -> y == f.y)){
         f.x = (rand()%((row-2)-lower+1))+lower;
         f.y = (rand()%((column-2)-lower+1))+lower;
        }
        ptr2 = ptr2 -> next;
    }
    ptr = ptr -> next;
    }
}

void wallcheck(struct node *head){
    int i = 0,j;
    struct node *ptr,*ptr2;
    ptr = head;
    while(ptr != NULL){
    ptr2 = head;
    while(ptr2 != NULL){
        for(i = 0; i < wallcounter; i++){
         for(j = wall[i].x; j <= wall[i].length; j++){
         if(((j == ptr2->x)&&(wall[i].y == ptr2->y))||((j == f.x)&&(wall[i].y == f.y))){
             wall[i].x = (rand()%((row-6)-lower+1))+lower;
             wall[i].y = (rand()%((column-2)-lower+1))+lower;
             wall[i].length = wall[i].x + 4;
         }
        }
        }
        ptr2 = ptr2 -> next;
    }
    ptr = ptr -> next;
    }
}

void generatemine(){
    int i,j,f;
    for(i = 0; i < minecounter; i++){
       m1[i].x = (rand()%((row-2)-lower+1))+lower;
       m1[i].y = (rand()%((column-2)-lower+1))+lower;
       m1[i].value = '*';
       j = i-1;
       while(j >= 0){
        if((m1[i].x == m1[j].x)&&(m1[i].y == m1[j].y)){
             m1[i].x = (rand()%((row-2)-lower+1))+lower;
             m1[i].y = (rand()%((column-2)-lower+1))+lower;
             m1[i].value = '*';
        }
        j--;
       }
    }
}

void generatewall(){
    int i,j,k;
    for(i = 0; i < wallcounter; i++){
    wall[i].x = (rand()%((row-6)-lower+1))+lower;
    wall[i].y = (rand()%((column-2)-lower+1))+lower;
    wall[i].length = wall[i].x + 4;
    j = i-1;
    while(j >= 0){
       for(k = wall[j].x; k <= wall[j].length; k++){
        if((wall[i].x == k)&&(wall[i].y == wall[j].y)){
            wall[i].x = (rand()%((row-6)-lower+1))+lower;
            wall[i].y = (rand()%((column-2)-lower+1))+lower;
            wall[i].length = wall[i].x + 4;
            k = wall[j].x;
        }
       }
       j--;
    }
    }
}

void minecheck(struct node *head){
    int i = 0;
    struct node *ptr,*ptr2;
    ptr = head;
    while(ptr != NULL){
    ptr2 = head;
    while(ptr2 != NULL){
       for(i = 0; i < minecounter; i++){
        if(((ptr2 -> x == m1[i].x)&&(ptr2 -> y == m1[i].y)) || ((m1[i].x == f.x)&&(m1[i].y == f.y))){
         m1[i].x = (rand()%((row-2)-lower+1))+lower;
         m1[i].y = (rand()%((column-2)-lower+1))+lower;
        }
       }
        ptr2 = ptr2 -> next;
    }
    ptr = ptr -> next;
    }
}

void settingvalues(struct node *head,char board[row][column]){
  struct node *ptr;
  int i,j,ik,jk;
  ptr = head;
  for(i = 0; i < row; i++){
    for(j = 0; j < column; j++){
      if((i == 0)||(i == row-1)){
        if(level >= 4){
         if(head->x==i){
            system("cls");
            printf("\n\nGAME OVER! YOUR SNAKE IS HIT BY WALL\n\n");
            printf("\n\nLEVEL : %d\t\tSCORE : %d\n\n",level,score);
            printf("\n\nPRESS ANY KEY TO EXIT\n\n");
            getch();
            exit(1);
         }
        }
        board[i][j] = '-';
      }
      else if((j == 0)||(j == column-1)){
        if(level >= 4){
         if(head->y==j){
            system("cls");
            printf("\n\nGAME OVER! YOUR SNAKE IS HIT BY WALL\n\n");
            printf("\n\nLEVEL : %d\t\tSCORE : %d\n\n",level,score);
            printf("\n\nPRESS ANY KEY TO EXIT\n\n");
            getch();
            exit(1);
         }
        }
        board[i][j] = '|';
      }
      else{
      board[i][j] = ' ';
      }
    }
  }
  ptr = head;
  while(ptr != NULL){
      board[ptr->x][ptr->y] = ptr->value;
    ptr = ptr -> next;
  }
  foodcheck(head);
  board[f.x][f.y] = f.value;
  if(level > 1){
    minecheck(head);
    for(i = 0; i < minecounter; i++){
            board[m1[i].x][m1[i].y] = m1[i].value;
    }
    if(level >= 5){
     wallcheck(head);
     for(i = 0; i < wallcounter; i++){
     for(j = wall[i].x; j <= wall[i].length; j++){
         board[j][wall[i].y] = '|';
     }
     }
    }
  }
}

void scoreincrease(){
    score++;
    if(score >= 20){
        if(score == 20){
          level++;
          minecounter++;
          generatemine();
        }
        else if(score == 40){
            level++;
            minecounter = (rand()%(8-lower+1))+lower;
            generatemine();
        }
        else if(score == 60){
            level++;
            minecounter = (rand()%(8-lower+1))+lower;
            generatemine();
        }
        else if(score == 80){
            level++;
            minecounter = (rand()%(8-lower+1))+lower;
            generatemine();
            wallcounter = 2;
            generatewall();
        }
    }
}
void scoreincrease2(){
    if(score >= 20){
        if((score >= 20)&&(score <= 39)){
          minecounter++;
          generatemine();
        }
        else if((score >= 40)&&(score <= 59)){
            minecounter = (rand()%(8-lower+1))+lower;
            generatemine();
        }
        else if((score >= 60)&&(score <=79)){
            minecounter = (rand()%(8-lower+1))+lower;
            generatemine();
        }
        else if((score >= 80)&&(score <= 100)){
            minecounter = (rand()%(8-lower+1))+lower;
            generatemine();
            wallcounter = 2;
            generatewall();
        }
    }
}

void snakeincrease(struct node *head){
    struct node *ptr,*n,*q;
    ptr = head;
    scoreincrease();
    while(ptr -> next -> next != NULL){
        ptr = ptr -> next;
    }
    q = ptr -> next;
    n = (struct node *)malloc(sizeof(struct node));
    n -> value = '#';
    n -> next = ptr -> next;
    ptr -> next = n;
    n -> x = q -> x;
    n -> y = q -> y;
}

void shiftup(struct node *head,int x,int y){
  if(head -> next == NULL){
    head -> x = x;
    head -> y = y;
    return;
  }
  else{
    shiftup(head -> next,head -> x,head -> y);
    head -> x = x;
    head -> y = y;
    return;
  }
}

void settingshiftingvaluesup(struct node *head,char board[row][column],int tempx,int tempy){
  struct node *ptr;
  int i,j;
  ptr = head;
  ptr -> x = ptr -> x - 1;

  if((board[ptr->x][ptr->y] == '#')||(board[ptr->x][ptr->y] == '!')){
    system("cls");
    printf("\n\nGAME OVER! YOU ATE YOUR SNAKE\n\n");
    printf("\n\nLEVEL : %d\t\tSCORE : %d\n\n",level,score);
    printf("\n\nPRESS ANY KEY TO EXIT\n\n");
    getch();
    exit(1);
  }
  if(level >= 2){
  for(i = 0; i < minecounter; i++){
   if((m1[i].x == head->x) && (m1[i].y == head -> y)){
    system("cls");
    printf("\n\nGAME OVER! MINE KILLED YOU\n\n");
    printf("\n\nLEVEL : %d\t\tSCORE : %d\n\n",level,score);
    printf("\n\nPRESS ANY KEY TO EXIT\n\n");
    getch();
    exit(1);
   }
  }
  if(level >= 5){
    for(i = 0; i < wallcounter; i++){
     for(j = wall[i].x; j <= wall[i].length; j++){
         if((j == head->x)&&(wall[i].y == head->y)){
             system("cls");
             printf("\n\nGAME OVER! YOUR SNAKE IS HIT BY WALL\n\n");
             printf("\n\nLEVEL : %d\t\tSCORE : %d\n\n",level,score);
             printf("\n\nPRESS ANY KEY TO EXIT\n\n");
             getch();
             exit(1);
         }
     }
     }
  }
  }
  if(ptr -> x == -1){
    ptr -> x = row-1;
  }
  if((f.x == head->x) && (f.y == head -> y)){
      snakeincrease(head);
      ptr = head;
       while(ptr -> next != NULL){
        ptr = ptr -> next;
       }
       ptr -> x = tempx;
       ptr -> y = tempy;
       f.x = (rand()%((row-2)-lower+1))+lower;
       f.y = (rand()%((column-2)-lower+1))+lower;
  }
  settingvalues(head,board);
}

void settingshiftingvaluesdown(struct node *head,char board[row][column],int tempx,int tempy){
  struct node *ptr;
  int i,j;
  ptr = head;
  ptr -> x = ptr -> x + 1;

  if((board[ptr->x][ptr->y] == '#')||(board[ptr->x][ptr->y] == '!')){
    system("cls");
    printf("\n\nGAME OVER! YOU ATE YOUR SNAKE\n\n");
    printf("\n\nLEVEL : %d\t\tSCORE : %d\n\n",level,score);
    printf("\n\nPRESS ANY KEY TO EXIT\n\n");
    getch();
    exit(1);
  }
  if(level >= 2){
  for(i = 0; i < minecounter; i++){
   if((m1[i].x == head->x) && (m1[i].y == head -> y)){
    system("cls");
    printf("\n\nGAME OVER! MINE KILLED YOU\n\n");
    printf("\n\nLEVEL : %d\t\tSCORE : %d\n\n",level,score);
    printf("\n\nPRESS ANY KEY TO EXIT\n\n");
    getch();
    exit(1);
   }
  }
  if(level >= 5){
    for(i = 0; i < wallcounter; i++){
     for(j = wall[i].x; j <= wall[i].length; j++){
         if((j == head->x)&&(wall[i].y == head->y)){
             system("cls");
             printf("\n\nGAME OVER! YOU SNAKE IS HIT BY WALL\n\n");
             printf("\n\nLEVEL : %d\t\tSCORE : %d\n\n",level,score);
             printf("\n\nPRESS ANY KEY TO EXIT\n\n");
             getch();
             exit(1);
         }
     }
     }
  }
  }
  if(ptr -> x == row){
    ptr -> x = 0;
  }
  if((f.x == head->x) && (f.y == head -> y)){
      snakeincrease(head);
      ptr = head;
       while(ptr -> next != NULL){
        ptr = ptr -> next;
       }
       ptr -> x = tempx;
       ptr -> y = tempy;
       f.x = (rand()%((row-2)-lower+1))+lower;
       f.y = (rand()%((column-2)-lower+1))+lower;
  }
  settingvalues(head,board);
}

void settingshiftingvaluesleft(struct node *head,char board[row][column],int tempx,int tempy){
  struct node *ptr;
  int i,j;
  ptr = head;
  ptr -> y = ptr -> y - 1;

  if((board[ptr->x][ptr->y] == '#')||(board[ptr->x][ptr->y] == '!')){
    system("cls");
    printf("\n\nGAME OVER! YOU ATE YOUR SNAKE\n\n");
    printf("\n\nLEVEL : %d\t\tSCORE : %d\n\n",level,score);
    printf("\n\nPRESS ANY KEY TO EXIT\n\n");
    getch();
    exit(1);
  }
  if(level >= 2){
  for(i = 0; i < minecounter; i++){
   if((m1[i].x == head->x) && (m1[i].y == head -> y)){
    system("cls");
    printf("\n\nGAME OVER! MINE KILLED YOU\n\n");
    printf("\n\nLEVEL : %d\t\tSCORE : %d\n\n",level,score);
    printf("\n\nPRESS ANY KEY TO EXIT\n\n");
    getch();
    exit(1);
   }
  }
  if(level >= 5){
    for(i = 0; i < wallcounter; i++){
     for(j = wall[i].x; j <= wall[i].length; j++){
         if((j == head->x)&&(wall[i].y == head->y)){
             system("cls");
             printf("\n\nGAME OVER! YOUR SNAKE IS HIT BY WALL\n\n");
             printf("\n\nLEVEL : %d\t\tSCORE : %d\n\n",level,score);
             printf("\n\nPRESS ANY KEY TO EXIT\n\n");
             getch();
             exit(1);
         }
     }
     }
  }
  }
  if(ptr -> y == -1){
    ptr -> y = column-1;
  }
  if((f.x == head->x) && (f.y == head -> y)){
      snakeincrease(head);
      ptr = head;
       while(ptr -> next != NULL){
        ptr = ptr -> next;
       }
       ptr -> x = tempx;
       ptr -> y = tempy;
       f.x = (rand()%((row-2)-lower+1))+lower;
       f.y = (rand()%((column-2)-lower+1))+lower;
  }
  settingvalues(head,board);
}

void settingshiftingvaluesright(struct node *head,char board[row][column],int tempx,int tempy){
  struct node *ptr,*ptr2;
  int i,j;
  ptr = head;
  ptr -> y = ptr -> y + 1;
  if((board[ptr->x][ptr->y] == '#')||(board[ptr->x][ptr->y] == '!')){
    system("cls");
    printf("\n\nGAME OVER! YOU ATE YOUR SNAKE\n\n");
    printf("\n\nLEVEL : %d\t\tSCORE : %d\n\n",level,score);
    printf("\n\nPRESS ANY KEY TO EXIT\n\n");
    getch();
    exit(1);
  }
  if(level >= 2){
  for(i = 0; i < minecounter; i++){
   if((m1[i].x == head->x) && (m1[i].y == head -> y)){
    system("cls");
    printf("\n\nGAME OVER! MINE KILLED YOU\n\n");
    printf("\n\nLEVEL : %d\t\tSCORE : %d\n\n",level,score);
    printf("\n\nPRESS ANY KEY TO EXIT\n\n");
    getch();
    exit(1);
   }
  }
  if(level >= 5){
    for(i = 0; i < wallcounter; i++){
     for(j = wall[i].x; j <= wall[i].length; j++){
         if((j == head->x)&&(wall[i].y == head->y)){
             system("cls");
             printf("\n\nGAME OVER! YOUR SNAKE IS HIT BY WALL\n\n");
             printf("\n\nLEVEL : %d\t\tSCORE : %d\n\n",level,score);
             printf("\n\nPRESS ANY KEY TO EXIT\n\n");
             getch();
             exit(1);
         }
     }
     }
  }
  }
  if(ptr -> y == column){
    ptr -> y = 0;
  }

 if((f.x == head->x) && (f.y == head -> y)){
       snakeincrease(head);
       ptr = head;
       while(ptr -> next != NULL){
        ptr = ptr -> next;
       }
       ptr -> x = tempx;
       ptr -> y = tempy;
       f.x = (rand()%((row-2)-lower+1))+lower;
       f.y = (rand()%((column-2)-lower+1))+lower;

  }
  settingvalues(head,board);
}

void up(struct node *head,char board[row][column]){
  struct node *ptr;
  int i,j,tempx,tempy;
if((f.x == head -> x - 1) && (f.y == head -> y)){
    ptr = head;
    while(ptr->next != NULL){
        ptr = ptr -> next;
    }
    tempx = ptr -> x;
    tempy = ptr -> y;
  }
  shiftup(head,head->x,head->y);
  settingshiftingvaluesup(head,board,tempx,tempy);
}

void right(struct node *head,char board[row][column]){
  struct node *ptr;
  int i,j,tempx,tempy;
  if((f.x == head -> x) && (f.y == head -> y + 1)){
    ptr = head;
    while(ptr->next != NULL){
        ptr = ptr -> next;
    }
    tempx = ptr -> x;
    tempy = ptr -> y;
  }
  shiftup(head,head->x,head->y);
  settingshiftingvaluesright(head,board,tempx,tempy);
}

void left(struct node *head,char board[row][column]){
  struct node *ptr;
  int i,j,tempx,tempy;
  if((f.x == head -> x) && (f.y == head -> y - 1)){
    ptr = head;
    while(ptr->next != NULL){
        ptr = ptr -> next;
    }
    tempx = ptr -> x;
    tempy = ptr -> y;
  }
  shiftup(head,head->x,head->y);
  settingshiftingvaluesleft(head,board,tempx,tempy);
}

void down(struct node *head,char board[row][column]){
  struct node *ptr;
  int i,j,tempx,tempy;
  if((f.x == head -> x + 1) && (f.y == head -> y)){
    ptr = head;
    while(ptr->next != NULL){
        ptr = ptr -> next;
    }
    tempx = ptr -> x;
    tempy = ptr -> y;
  }

  shiftup(head,head->x,head->y);
  settingshiftingvaluesdown(head,board,tempx,tempy);
}
void filewrite(struct node *head){
    struct node *ptr;
    FILE *fp;
    fp = fopen("snakedata.txt","w");
    if(fp == NULL){
        printf("Error occurred while saving!\n");
        exit(1);
    }
    fprintf(fp,"f%d,%d,%c",f.x,f.y,f.value);
    ptr = head;
    while(ptr != NULL){
        fprintf(fp,"s%d,%d,%c",ptr->x,ptr->y,ptr->value);
        ptr = ptr -> next;
    }
    fprintf(fp,"S%d",score);
    fprintf(fp,"L%d",level);
    fclose(fp);
    printf("Successfully saved\n");
}

struct node * fileread(struct node *head){
    struct node *n,*ptr;
    char ch,value;
    int x,y;
    FILE *fp;
    fp = fopen("snakedata.txt","r");
    if(fp == NULL){
        printf("Error occurred while loading data, first save your progress\n");
        exit(1);
    }
    while(!feof(fp)){
    ch = fgetc(fp);
    if(ch == 'f'){
        fscanf(fp,"%d,%d,%c",&f.x,&f.y,&f.value);
    }
    else if(ch == 's'){
        fscanf(fp,"%d,%d,%c",&x,&y,&value);
        n = (struct node*)malloc(sizeof(struct node));
        n -> value = value;
        n -> x = x;
        n -> y = y;
        if(head == NULL){
            n -> next = NULL;
            head = n;
        }
        else{
            ptr = head;
            while(ptr -> next != NULL){
                ptr = ptr -> next;
            }
            ptr -> next = n;
            n -> next = NULL;
        }
    }
    else if(ch == 'S'){
        fscanf(fp,"%d",&score);
    }
    else if(ch == 'L'){
        fscanf(fp,"%d",&level);
    }
    }
    fclose(fp);
    scoreincrease2();
    return head;
}

int main(){
  int i, j,flag = 0,ftemp = 0;
  char save,start;
  int option1 = 0,option2 = 0;
  char board[row][column];
  struct node *head = NULL;
  srand(time(0));
  printf("\nIt is recommended to play game in full screen for best experience");
  printf("\n\nPress (y) to load previous game or any other key to start new game\n");

  start = getch();
  system("cls");
  if((start == 'y')||(start == 'Y')){
   head = fileread(head);
  }
  else{
  f.x = (rand()%((row-2)-lower+1))+lower;
  f.y = (rand()%((column-2)-lower+1))+lower;
  f.value = 'O';
  head = createsnake();
  }

  settingvalues(head,board);

  for(i = 0; i < row; i++){
    for(j = 0; j < column; j++){
      printf("%c",board[i][j]);
    }
    printf("\n");
  }

  while(1){
  if(kbhit()){
    flag = 1;
    option1 = getch();
    if(option1 != 27){
    ftemp = option2;
    option2 = getch();
    }
  }
  if((option1 == 224)&&(option2 == 72)){
  if(ftemp == 80){
    down(head,board);
    option2 = 80;
  }
  else{
    up(head,board);
  }
  }
  else if((option1 == 224)&&(option2 == 80)){
  if(ftemp == 72){
    up(head,board);
    option2 = 72;
  }
  else{
    down(head,board);
  }
  }
  else if((option1 == 224)&&(option2 == 77)){
  if(ftemp == 75){
    left(head,board);
    option2 = 75;
  }
  else{
    right(head,board);
  }
  }
  else if((option1 == 224)&&(option2 == 75)){
  if(ftemp == 77){
    right(head,board);
    option2 = 77;
  }
  else{
    left(head,board);
  }
  }
  else if(option1 == 27){
    printf("\n\nDo you wish to save your current game? Press (y) to save and any other key to exit without saving\n\n");
    save = getch();
    if((save == 'y')||(save == 'Y')){
        filewrite(head);
    }
    exit(1);
  }
    if(flag == 1){
    if(level == 1){
    Sleep(40);
    }
    else if(level == 2){
        Sleep(25);
    }
    else if(level == 3){
        Sleep(15);
    }
    else if(level == 4){
        Sleep(5);
    }
    print(board);
    if((score == 20)||(score == 40)||(score == 60)||(score == 80)){
    printf("\n\nCongratulations you are in level %d                        \n\n",level);
    }
    else{
    if(score == 100){
        system("cls");
        printf("\n\nLEVEL : %d\t\tSCORE : %d\n\n",level,score);
        printf("\n\nWINNER WINNER! CHICKEN DINNER\n\n");
        printf("\n\nPRESS ANY KEY TO EXIT\n\n");
        break;
    }
    printf("\n\nLEVEL : %d                 SCORE : %d                      \n\n",level,score);
    }
    }

  }
  getch();
  return 0;
}
