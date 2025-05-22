#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "serv_com.c" 
#include "user_manip.c" 
#pragma comment(lib, "Ws2_32.lib")


// BOOL WINAPI ConsoleHandler(DWORD signal) {
//     if (signal == CTRL_CLOSE_EVENT || signal == CTRL_C_EVENT) {
//         printf("Caught console close or Ctrl+C — cleaning up!\n");
//         return TRUE;
//     }
//     return FALSE;
// }

void add();
void find();
void tarification();
void list_doc();
void send_pat();

int main(){
  while(1){
    char *i=(char *)malloc(50*sizeof(char)),
    *choix=(char *)malloc(10*sizeof(char));
    printf(
"\n\n+-----+------------------------------------------+\n"
"|  0  | AJOUTER PATIENT                          |\n"
"+-----+------------------------------------------+\n"
"|  1  | MODIFIER PATIENT                         |\n"
"+-----+------------------------------------------+\n"
"|  2  | SUPRIMMER PATIENT                        |\n"
"+-----+------------------------------------------+\n"
"|  3  | VOIR DOCTEUR DISPONIBLE                  |\n"
"+-----+------------------------------------------+\n"
"|  4  | LISTER PATIENT                           |\n"
"+-----+------------------------------------------+\n"
"|  5  | CHERCHER PATIENT                         |\n"
"+-----+------------------------------------------+\n"
"|  6  | PASSER PATIENT VERS DOCTEUR              |\n"
"+-----+------------------------------------------+\n"
"|  7  | TARIFICATION                             |\n"
"+-----+------------------------------------------+\n"
"|  8  | SORTIR                                   |\n"
"+-----+------------------------------------------+\n\n");

      do{
        printf("choisir une option a modifier\n>");
        fgets(choix,10,stdin);
      if (strchr(choix, '\n') == NULL) {
        flushInput();
      } else {
        choix[strcspn(choix, "\n")] = '\0';
      } // enlever le \n
    }while(valid_numb(choix) || strlen(choix)>=10);
    switch(atoi(choix)){
      case 0:
        add();
        break;
      case 1:
        list_user();
        do{
          printf("SAISIR L'ID\n>");
          fgets(i,50,stdin);
          if (strchr(i, '\n') == NULL) {
            flushInput();
          } else {
            i[strcspn(i, "\n")] = '\0';
          } // enlever le \n
        }while(valid_numb(i) || strlen(i)>50 || atoi(i)<0 || atoi(i)>get_lines());
        modify(atoi(i));
        free(i);
        break;
      case 2:
        list_user();
        do{
          printf("SAISIR L'ID\n>");
          fgets(i,50,stdin);
          if (strchr(i, '\n') == NULL) {
            flushInput();
          } else {
            i[strcspn(i, "\n")] = '\0';
          } // enlever le \n
        }while(valid_numb(i) || strlen(i)>50 || atoi(i)<0 || atoi(i)>get_lines());
        remove_line(atoi(i));
        free(i);
        break;
      case 3:
        if(atoi(get("127.0.0.1",3000,"numbers"))>0){
          printf("\n\nDOCTEUR DISPONIBLE\n");
        }else{
          printf("\n\nDOCTEUR NON DISPONIBLE\n");
        }
        break;
      case 4:
        list_user();
        break;
      case 5:
        find();
        break;
      case 6:
        if(atoi(get("127.0.0.1",3000,"numbers"))<=0){
          printf("\n\nDOCTEUR NON DISPONIBLE\n\n");
        }else{
          send_pat();
        }
        break;
      case 7:
        tarification();
        break;
      case 8:
        free(i);
        free(choix);
        printf("\n\nsorti du programe");
        Sleep(800);
        return 0;
        break;
      default:
        break;
    }
  }
}



//fonction pricipale
void list_doc(){
  printf("\n\n%46s\n","LISTE D'UTILISATEUR");
  for (int i = 0; i < atoi(get("127.0.0.1",3000,"numbers")); i++)
  {
    printf(
      "+---------+-----------------------------------------+---------------------------------+-------------------------+\n"
      "|    %-5d| %-40s|   %-30s|   %-20s  |\n",i,get_info_doc(i,1),get_info_doc(i,2),get_info_doc(i,3));
  }
  printf("+---------+-----------------------------------------+---------------------------------+-------------------------+\n\n");
  Sleep(500);
}

void add(){
  char *choix[8] = {
    (char *) malloc(40*sizeof(char)),
    (char *) malloc(40*sizeof(char))
    ,(char *) malloc(40*sizeof(char))
    ,(char *) malloc(40*sizeof(char))
    ,(char *) malloc(40*sizeof(char))
    ,(char *) malloc(40*sizeof(char))
    ,(char *) malloc(40*sizeof(char))
    ,(char *) malloc(40*sizeof(char))};
  do{
    printf("donner nom\n>");
    fgets(choix[0],40,stdin);
    if (strchr(choix[0], '\n') == NULL) {
      flushInput();
    } else {
      choix[0][strcspn(choix[0], "\n")] = '\0';
    } // enlever le \n
  }while( strlen(choix[0])>40);

    do{
    printf("donner le sex\n>");
    fgets(choix[1],40,stdin);
    if (strchr(choix[1], '\n') == NULL) {
      flushInput();
    } else {
      choix[1][strcspn(choix[1], "\n")] = '\0';
    } // enlever le \n
  }while( strlen(choix[1])>40);

    do{
    printf("donner l'age\n>");
    fgets(choix[2],40,stdin);
    if (strchr(choix[2], '\n') == NULL) {
      flushInput();
    } else {
      choix[2][strcspn(choix[2], "\n")] = '\0';
    } // enlever le \n
  }while(valid_numb(choix[2]) || strlen(choix[2])>40);

    do{
    printf("donner la profession\n>");
    fgets(choix[3],40,stdin);
    if (strchr(choix[3], '\n') == NULL) {
      flushInput();
    } else {
      choix[3][strcspn(choix[3], "\n")] = '\0';
    } // enlever le \n
  }while( strlen(choix[3])>40);

    do{
    printf("donner la situation familial\n>");
    fgets(choix[4],40,stdin);
    if (strchr(choix[4], '\n') == NULL) {
      flushInput();
    } else {
      choix[4][strcspn(choix[4], "\n")] = '\0';
    } // enlever le \n
  }while( strlen(choix[4])>40);

    do{
    printf("donner l'adresse\n>");
    fgets(choix[5],40,stdin);
    if (strchr(choix[5], '\n') == NULL) {
      flushInput();
    } else {
      choix[5][strcspn(choix[5], "\n")] = '\0';
    } // enlever le \n
  }while( strlen(choix[5])>40);

    do{
    printf("donner l'affiliation mutuelle\n>");
    fgets(choix[6],40,stdin);
    if (strchr(choix[6], '\n') == NULL) {
      flushInput();
    } else {
      choix[6][strcspn(choix[6], "\n")] = '\0';
    } // enlever le \n
  }while( strlen(choix[6])>40);

      do{
    printf("donner numero de telephone\n>");
    fgets(choix[7],40,stdin);
    if (strchr(choix[7], '\n') == NULL) {
      flushInput();
    } else {
      choix[7][strcspn(choix[7], "\n")] = '\0';
    } // enlever le \n
  }while( strlen(choix[7])>40);

  add_user(choix[0],choix[1],choix[2],choix[3],choix[4],choix[5],choix[6],choix[7]);
  free(choix[0]);
  free(choix[1]);
  free(choix[2]);
  free(choix[3]);
  free(choix[4]);
  free(choix[5]);
  free(choix[6]);
  free(choix[7]);
}

void find(){
  char *ii=(char *)malloc(40*sizeof(char));
  int d=0;
  printf("\n\nRECHERCHE\n>");
  do{
    fgets(ii,40,stdin);
    if (strchr(ii, '\n') == NULL) {
      flushInput();
    } else {
      ii[strcspn(ii, "\n")] = '\0';
    } // enlever le \n
  }while(strlen(ii)>=40);
  for(int i=0;i<get_lines();i++){
    if(levenshtein_max2(ii,get_infos(i,0),2)<3){
        printf(
      "+---------+-----------------------------------------+---------+-------------+\n"
      "|    %-5d| %-40s|   %-6s|   %-8s  |\n",i,get_infos(i,0),get_infos(i,2),get_infos(i,1));
      d++;
    }
  }
  if(d>0){
    printf("+---------+-----------------------------------------+---------+-------------+\n\n\n");
  }
  else{
    printf("PERSONNE NE S'APPLE %s\n\n\n",ii);
  }
  free(ii);
  Sleep(800);
}

void tarification(){
  char *i=(char *)malloc(50*sizeof(char));
  printf("SAISIR TYPE DE CONSULTATION\n(Saisir sortir pour sortir)>");
  do{
    redo:
      fgets(i,50,stdin);
      if (strchr(i, '\n') == NULL) {
        flushInput();
      } else {
        i[strcspn(i, "\n")] = '\0';
      } // enlever le \n
    }while(strlen(i)>50);
  if(levenshtein_max2(i,"normal",2)<3){
    printf("\n\nLE PRIX EST 300Dhs\n\n");
  }
  else if(levenshtein_max2(i,"urgent",2)<3){
    printf("\n\nLE PRIX EST 800Dhs\n\n");
  }
  else if(levenshtein_max2(i,"sortir",2)<3){
    free(i);
    return;
  }
  else{
    goto redo;
  }
  free(i);
  Sleep(800);
}

void send_pat(){
  char *i=(char *)malloc(50*sizeof(char)),
  *ii=(char *)malloc(50*sizeof(char));
  list_user();
  printf("SAISIR ID\n(Saisir sortir pour sortir)>");
  do{
    fgets(i,50,stdin);
    if (strchr(i, '\n') == NULL) {
        flushInput();
      } else {
        i[strcspn(i, "\n")] = '\0';
      } // enlever le \n
    }while(strlen(i)>50 || valid_numb(i) || atoi(i)<0 || atoi(i) > get_lines());

    list_doc();
    printf("SAISIR ID\n(Saisir sortir pour sortir)>");
    
    do{
      fgets(ii,50,stdin);
      if (strchr(ii, '\n') == NULL) {
        flushInput();
      } else {
        ii[strcspn(ii, "\n")] = '\0';
      } // enlever le \n
    }while(strlen(ii)>50 || valid_numb(ii) || atoi(ii)<0 || atoi(ii) > atoi(get("127.0.0.1",3000,"numbers")));
    
    client(get_info_doc(atoi(ii),2),8000,get_infos(atoi(i),0));
    free(ii);
    free(i);
}