#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int gerarLab(int lab[12][12]){
  srand(time(NULL));
  int X=(rand() & 9) + 1, Y = 0;
  int controleX = 0, controleY = 0;
  int partida = X;
  for(int i=0; i<12; i++){
    for(int j = 0; j<12; j++){
      lab[i][j]= 0;
    }
  }
  lab[X][Y] = 1;
  Y++;
  lab[X][Y] = 1;
  while(Y != 11 ){
    int acao = rand() % 3;
    //frente
    if (acao == 0){
      Y=Y+1;
      controleX= controleX - 1;
      controleY= controleY - 1;
    }
    //esquerda
    if(acao == 1 && controleX<=0){
      X=X-1;
      controleY=2;
      if(X==0)
        X=X+1;
    }
    //direita
    if(acao == 2 && controleY<=0){
      X=X+1;
      controleX=2;
      if(X==11)
        X=X-1;  
    }
    lab[X][Y] = 1;
  }
  return partida;
}

void caminhoAlt(int lab[12][12], int partida){
  srand(time(NULL));
  int X, Y, altc;
  int controleX = 0, controleY = 0;
  for(int caminho=0; caminho<4; caminho++){
    for(int i= 0; i<12; i++){
      for(int j=0; j<12; j++){
        if(lab[i][j]==1&&j!=0&&j!=11){
          altc= rand() % 2;
          if(altc == 1){
            X=i;
            Y=j;
            break;
          }
        }
      }
    }
    while(Y != 10 ){
    int acao = rand() % 3;
    //frente
    if (acao == 0){
      Y=Y+1;
      controleX= controleX - 1;
      controleY= controleY - 1;
    }
    //esquerda
    if(acao == 1 && controleX<=0){
      X=X-1;
      controleY=2;
      if(X==0)
        X=X+1;
    }
    //direita
    if(acao == 2 && controleY<=0){
      X=X+1;
      controleX=2;
      if(X==11)
        X=X-1;  
    }
  lab[X][Y]=1;
    }
  }
}

void Robo(int lab[12][12], int partidaX){
  printf("\n");
  printf("\n");
  int X = partidaX;
  int Y = 0, rotacao=0;
  int i, j;
  while(Y != 11){
    lab[X][Y] = 2;
    sleep(1);
    //frente
    if(rotacao == 0){
      if(lab[X+1][Y]==0 && lab[X][Y+1]==1 ){
        Y=Y+1;
        rotacao=0;
      }
      else if(lab[X+1][Y]==0 && lab[X][Y+1]==0 ){
        if(lab[X-1][Y]==1){
          X=X-1;
          rotacao=1;
          lab[X][Y]=2;
        }
        else if (lab[X-1][Y]==0){
          rotacao= -2;
        }
      }
      else if(lab[X+1][Y] == 1){
        X=X+1;
        rotacao= -1;
        lab[X][Y]=2;
      }
    }
    //subindo
    if(rotacao == 1){
      if(lab[X][Y+1]==0 && lab[X-1][Y]==1){
        X=X-1;
        rotacao = 1;
      }
      else if(lab[X][Y+1]==0 && lab[X-1][Y]==0){
        if(lab[X][Y-1]==1){
          Y=Y-1;
          rotacao = -2;
        }
        else if (lab[X-1][Y]==0){
          X=X+1;
          rotacao=-1;
        }
      }
      else if(lab[X][Y+1]==1){
        Y=Y+1;
        rotacao=0;
        lab[X][Y]=2;
      }
    }
    //descendo
    if(rotacao == -1){
      if(lab[X][Y-1]==0 && lab[X+1][Y]==1){
        X=X+1;
        rotacao=-1;
      }
      else if(lab[X][Y-1]==0 && lab[X+1][Y]==0){
        if(lab[X][Y+1]==1){
          Y=Y+1;
          rotacao=0;
        }
       else if (lab[X-1][Y]==0){
          X=X-1;
          rotacao=1;
        }
      }
      else if(lab[X][Y-1]==1){
        Y=Y-1;
        rotacao=-2;
        lab[X][Y]=2;
      }
    }
    //voltando
    if(rotacao == -2){
      if(lab[X-1][Y]==0 && lab[X][Y-1]==1){
        Y=Y-1;
        rotacao = -2;
      }
      else if(lab[X-1][Y]==0 && lab[X][Y-1]==0){
        if(lab[X+1][Y]==1){
          X=X+1;
          rotacao = -1;
        }
        else if (lab[X-1][Y]==0){
          Y=Y+1;
          rotacao= 0;

        }
      }
      else if(lab[X-1][Y]==1){
        X=X-1;
        rotacao=1;
      }
    }  
    lab[X][Y]=2;
  for(int i=0; i<12; i++){
    for(int j=0; j<12;j++){
      if(lab[i][j] == 0)
        printf("▉ ");
      if(lab[i][j] == 1)
        printf("• ");
      if(lab[i][j] == 2)
       printf("+ ");
      if(lab[i][j] == 3)
       printf("x ");
    }
    printf("\n");
  }
    printf("\n");
}
}


int main(void) {
  int lab[12][12], partidaX;
  partidaX = gerarLab(lab);
  caminhoAlt(lab, partidaX);
  Robo(lab,partidaX);
  printf("A saída foi encontrada parabens!!");
  return 0;
}