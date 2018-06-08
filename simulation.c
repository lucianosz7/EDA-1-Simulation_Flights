#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>


struct decolagem{
  char codeVoos[6];
  int combustivel;
  char prioridade;
  char status;
  int prioridade_indice;
  int pista;
  int hora;
  int minutos;
  struct decolagem* prox;
  
};
typedef struct decolagem Decolagem;

struct pouso {
  char codeVoos[6];
  int combustivel;
  char prioridade;
  char status;
  int prioridade_indice;
  int pista;
  int hora;
  int minutos;
  struct pouso* prox;
};
typedef struct pouso Pouso;

struct fila{
  Decolagem* ini_d;
  Decolagem* fim_d;
  Pouso* ini_p;
  Pouso* fim_p;
};
typedef struct fila Fila;

Fila* cria_dec();
Decolagem* ins_fim_dec();
Decolagem* ret_ini_dec();
void insere_dec();
char *retira_dec();
int vazia_dec();
void imprime_dec();
void libera_Dec();
/******************************************************************************/
Fila* cria_pou();
Pouso* ins_fim_pou();
Pouso* ret_ini_pou();
void insere_pou();
char *retira_pou();
int vazia_pou();
void imprime_pou();
void libera_pou();
/******************************************************************************/
int gera_aleaorios();
int gera_voos_comb_prior();
void mostra_horas();
int *ListaPista();
int cronos();

int main(int argc, char const *argv[]) {
  char *codeVoos[] = {"VG3001","JJ4404", "LN7001", "TG1501", "GL7602", "TT1010",
                       "AZ1009", "AZ1008","AZ1010", "TG1506", "VG3002", "JJ4402",
                       "GL7603", "RL7880", "AL0012","TT4544", "TG1505", "VG3003",
                       "JJ4403", "JJ4401", "LN7002", "AZ1002","AZ1007", "GL7604",
                       "AZ1006", "TG1503", "AZ1003", "JJ4403", "AZ1001", "LN7003",
                       "AZ1004", "TG1504", "AZ1005", "TG1502", "GL7601", "TT4500",
                       "RL7801", "JJ4410", "GL7607", "AL0029", "VV3390", "VV3392",
                       "GF4681", "GF4690", "AZ1020", "JJ4435", "VG3010", "LF0920",
                       "AZ1065", "LF0978", "RL7867", "TT4502", "GL7645", "LF0932",
                       "JJ4434", "TG1510", "TT1020", "AZ1098", "BA2312", "VG3030",
                       "BA2304", "KL5609","KL5610", "KL5611"};

  int UnTempo = 5;
  int hora = 8, minutos=0;
  int NVoos;
  int NAproximacoes;
  int NDecolagens;
  char prioridade;
  int prioridade_indice;
  int opcaoVoo;
  char status;
  int combustivel;
  int num_codeVoo;
  int conta_comb = 0;
  int lista_vazia1 = 0;
  int lista_vazia2 = 0;
  int pista = 0;
  int i = 0, j = 0;


  Fila *f = cria_dec();
  Fila *f2 = cria_pou();
  gera_aleaorios(&NVoos, &NAproximacoes, &NDecolagens);
  gera_voos_comb_prior(&num_codeVoo, &prioridade_indice, &combustivel, &opcaoVoo);

  if(prioridade_indice == 0){
    prioridade = 'A';
    status = 'P';
  }
  else{
    prioridade = 'D';
    status = 'D';
  }

  pista = 1 + (rand() % 2);

  printf("---------------------------------------------------------------------\n");
  printf("Aeroporto de Brasília\n");
  printf("Hora Inicial: 0%d:0%d\n", hora, minutos);
  if(prioridade == 'A'){
    printf("Fila de pedidos: %s - %c - %c%d \n", codeVoos[num_codeVoo], status, prioridade, combustivel);
  }
  else{
    printf("Fila de pedidos: %s - %c - %c \n", codeVoos[num_codeVoo], status, prioridade);
  }
  printf("NVoos: %d\n", NVoos);
  printf("Naproximacoes: %d\n", NAproximacoes);
  printf("Ndecolagens: %d\n", NDecolagens);
  printf("---------------------------------------------------------------------\n");

  if(prioridade == 'A' && combustivel == 0){
    insere_pou(f2, codeVoos[num_codeVoo], prioridade, status, combustivel, hora, minutos, pista, &conta_comb);
  }

  while(j < NAproximacoes){
    gera_voos_comb_prior(&num_codeVoo, &prioridade_indice, &combustivel, &opcaoVoo);
    if(lista_vazia2 != 0){
      //cronos(&hora, &minutos, 2);
      minutos += 3*UnTempo;
      //printf("%d\n", minutos);
      if(minutos >= 60){
        minutos = minutos - 60;
        hora++;
      }
      pista = 1 + (rand() % 2);
      //printf("%d\n", hora);
      insere_pou(f2, codeVoos[num_codeVoo], prioridade, status, combustivel, hora, minutos, pista, &conta_comb);
    }
    else{
      //cronos(&hora, &minutos, 2);
      minutos += 3*UnTempo;
      //printf("%d\n", minutos);
      if(minutos >= 60){
        minutos = minutos - 60;
        hora++;
      }
      pista = 1 + (rand() % 2);
      //printf("%d\n", hora);
      insere_pou(f2, codeVoos[num_codeVoo], prioridade, status, combustivel, hora, minutos, pista, &conta_comb);
    }
    lista_vazia2++;
    j++;
  }
  while(i < NDecolagens){
    gera_voos_comb_prior(&num_codeVoo, &prioridade_indice, &combustivel, &opcaoVoo);
    if(lista_vazia1 != 0){
      //cronos(&hora, &minutos, 0);
      minutos += 2*UnTempo;
      //printf("%d\n", minutos);
      if(minutos >= 60){
        minutos = minutos - 60;
        hora++;
      }
      pista = 1 + (rand() % 3);
      //printf("%d\n", hora);
      insere_dec(f, codeVoos[num_codeVoo], prioridade, status, combustivel, hora, minutos, pista, &conta_comb);
    }
    else{
      minutos += 2*UnTempo;
      //printf("%d\n", minutos);
      if(minutos >= 60){
        minutos = minutos - 60;
        hora++;
      }
      pista = 1 + (rand() % 3);
      //printf("%d\n", hora);
      insere_dec(f, codeVoos[num_codeVoo], prioridade, status, combustivel, hora, minutos, pista, &conta_comb);

    }
    lista_vazia1++;
    i++;
  }

  insere_pou(f2, codeVoos[num_codeVoo], prioridade, status, combustivel, hora, minutos, pista, &conta_comb);

  printf("Listagem de eventos:\n\n");
  imprime_pou(f2);
  imprime_dec(f);

  return 0;
}

void mostra_horas(int hours, int minutes){
  if (hours < 10 && minutes < 10){
    printf("Horário do início do procedimento: 0%d:0%d\n", hours,minutes);
  }
  if(hours >= 10 && minutes >= 10){
    printf("Horário do início do procedimento: %d:%d\n", hours,minutes);
  }
  if(hours < 10 && minutes >= 10){
    printf("Horário do início do procedimento: 0%d:%d\n", hours,minutes);
  }
  if(hours >= 10 && minutes < 10){
    printf("Horário do início do procedimento: %d:0%d\n", hours,minutes);
  }
}

/******************************************************************************/

int gera_aleaorios(int *NVoos, int *NAproximacoes, int *NDecolagens,
                   int *combustivel){
  srand( (unsigned)time(NULL) );
  *NAproximacoes = 10 + (rand() % 22 );
  srand( (unsigned)time(NULL) );
  *NDecolagens = 10 + (rand() % 22 );
  *NVoos = *NAproximacoes + *NDecolagens;
  return 0;
}

int gera_voos_comb_prior(int *num_codeVoo, int *prioridade_indice,
                         int *combustivel, int *opcaoVoo){
  *num_codeVoo = 0 + (rand() % 63);

  *prioridade_indice = 0 + (rand() % 2 );

  *combustivel = 0 + (rand() % 12);

  *opcaoVoo = 0 + (rand() % 2);

  return 0;
}

/******************************************************************************/

Fila* cria_dec(void){
  Fila* f = (Fila*)malloc(sizeof(Fila));
  f->ini_d = f->fim_d = NULL;
  return f;
}

Decolagem* ins_fim_dec (Decolagem* fim_d, char *CodeVoos, char *prioridade,
                        char *status, int combustivel, int hora, int minuto,int pista){
  Decolagem* p = (Decolagem*) malloc(sizeof(Decolagem));
  strcpy(p->codeVoos,CodeVoos);
  p->prioridade = prioridade;
  p->status = status;
  p->combustivel = combustivel;
  p->hora = hora;
  p->minutos = minuto;
  p->pista = pista;
  p->prox = NULL;
  if(fim_d != NULL){
    fim_d->prox = p;
  }
  return p;
}

Decolagem* ret_ini_dec(Decolagem* ini_d){
  Decolagem* p = ini_d->prox;
  free(ini_d);
  return p;
}

void insere_dec(Fila* f, char *codeVoos, char *prioridade, char *status,
                int combustivel, int hora, int minuto, int pista,
                int *conta_comb){
  f->fim_d = ins_fim_dec(f->fim_d, codeVoos, prioridade, status, combustivel,
                         hora, minuto, pista);

  if(f->ini_d==NULL){
    f->ini_d = f->fim_d;
  }
  if(combustivel == 0){
    *conta_comb = *conta_comb + 1;
  }
}

char *retira_dec(Fila* f){
  char *codeVoos = malloc(6);
  if(vazia_dec(f)){
    printf("Fila vazia\n");
    exit(1);
  }
  strcpy(codeVoos,f->ini_d->codeVoos);
  f->ini_d = ret_ini_dec(f->ini_d);
  if(f->ini_d == NULL){
    f->fim_d = NULL;
  }
  return codeVoos;
}

int vazia_dec(Fila* f){
  return(f->ini_d==NULL);
}

void libera_Dec(Fila* f){
  Decolagem* q = f->ini_d;
  while(q!=NULL){
    Decolagem* t = q->prox;
    free(q);
    q=t;
  }
  free(f);
}

void imprime_dec(Fila* f, int *pista){
  Decolagem* q;
  int check;
  for(q=f->ini_d; q!=NULL;q=q->prox){
    printf("Código do voo: %s\n", q->codeVoos);
    printf("Status: [aeronave decolou]\n");
    mostra_horas(q->hora,q->minutos);
    printf("Número da pista: %d\n", q->pista);
    printf("combustivel: %d\n",q->combustivel);
    printf("\n");
  }
}

/******************************************************************************/

Fila* cria_pou(void){
  Fila* f = (Fila*)malloc(sizeof(Fila));
  f->ini_d = f->fim_d = NULL;
  return f;
}

Pouso* ins_fim_pou (Pouso* fim_p, char *CodeVoos, char *prioridade, char *status,
                    int combustivel, int hora, int minuto, int pista){
  Pouso* p = (Pouso*) malloc(sizeof(Pouso));
  strcpy(p->codeVoos,CodeVoos);
  p->prioridade = prioridade;
  p->status = status;
  p->combustivel = combustivel;
  p->hora = hora;
  p->minutos = minuto;
  p->pista = pista;
  p->prox = NULL;
  if(fim_p != NULL){
    fim_p->prox = p;
  }
  return p;
}

Pouso* ret_ini_pou(Pouso* ini_p){
  Pouso* p = ini_p->prox;
  free(ini_p);
  return p;
}

void insere_pou(Fila* f, char *codeVoos, char *prioridade, char *status,
                int combustivel, int hora, int minuto, int pista,
                int *conta_comb){
  f->fim_p = ins_fim_pou(f->fim_p, codeVoos, prioridade, status, combustivel,
                         hora, minuto, pista);

  if(f->ini_p==NULL){
    f->ini_p = f->fim_p;
  }
  if(combustivel == 0){
    *conta_comb = *conta_comb + 1;
  }
}

char *retira_pou(Fila* f){
  char *codeVoos = malloc(6);
  if(vazia_pou(f)){
    printf("Fila vazia\n");
    exit(1);
  }
  strcpy(codeVoos,f->ini_p->codeVoos);
  f->ini_p = ret_ini_pou(f->ini_p);
  if(f->ini_p == NULL){
    f->fim_p = NULL;
  }
  return codeVoos;
}

int vazia_pou(Fila* f){
  return(f->ini_p==NULL);
}

void libera_pou(Fila* f){
  Pouso* q = f->ini_p;
  while(q!=NULL){
    Pouso* t = q->prox;
    free(q);
    q=t;
  }
  free(f);
}

void imprime_pou(Fila* f, int *pista){
  Pouso* q;
  for(q=f->ini_p; q!=NULL;q=q->prox){
    printf("Código do voo: %s\n", q->codeVoos);
    printf("Status: [aeronave pousou]\n");
    mostra_horas(q->hora,q->minutos);
    printf("Número da pista: %d\n", q->pista);
    printf("combustivel: %d\n",q->combustivel);
    printf("\n");
  }
}
