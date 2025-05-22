#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "serv_com.c" 
#include "user_manip.c" 
#pragma comment(lib, "Ws2_32.lib")

int ID,*ptrID=&ID;
char servIp[30];


BOOL WINAPI ConsoleHandler(DWORD signal) {
    if (signal == CTRL_CLOSE_EVENT || signal == CTRL_C_EVENT) {
        delete(servIp,3000,"names",ID);
        exit(0);
        return TRUE;
    }
    return FALSE;
}

int main(){
    if (!SetConsoleCtrlHandler(ConsoleHandler, TRUE)) {
      printf("Error: Could not set control handler\n");
      return 1;
    }
  
  char *name=(char *)malloc(50*sizeof(char)),
  *message=(char *)malloc(100*sizeof(char)),*ip=(char *)malloc(30*sizeof(char));
  printf("Saisir Votre Nom\n>");
  do{
    fgets(name,50,stdin);
    if (strchr(name, '\n') == NULL) {
      flushInput();
    } else {
      name[strcspn(name, "\n")] = '\0';
    } // enlever le \n
  }while(strlen(name)>=50);

  printf("Saisir l'IP Serveur\n>");
  do{
    fgets(servIp,30,stdin);
    if (strchr(servIp, '\n') == NULL) {
      flushInput();
    } else {
      servIp[strcspn(servIp, "\n")] = '\0';
    } // enlever le \n
  }while(strlen(servIp)>=30);
  
  get_ip(ip);
  snprintf(message,100,"{\"name\":\"%s\",\"ip\":\"%s\"}",name,ip);
  *ptrID=atoi(post(servIp,3000,"names",message));
  free(message);
  while(1){
    char *i=(char *)malloc(50*sizeof(char)),
    *choix=(char *)malloc(10*sizeof(char));
    printf(
      "\n\n+-----+------------------------------------------+\n"
"|  0  | ATTENDRE PATIANT                         |\n"
"+-----+------------------------------------------+\n"
"|  1  | SORTIR                                   |\n"
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
        listner(8000,i);
        while (1){
          char *choixx=(char *)malloc(10*sizeof(char));
          printf("\n\nPatiant %s",i);
          printf(
            "\n\n"
            "+-----+------------------------------------------+\n"
            "|  0  | CREE ORDONANCE                           |\n"
            "+-----+------------------------------------------+\n"
            "|  1  | SORTIR                                   |\n"
            "+-----+------------------------------------------+\n\n"
          );
          do{
            printf("choisir une option\n>");
            fgets(choixx,10,stdin);
            if (strchr(choixx, '\n') == NULL) {
              flushInput();
            } else {
              choix[strcspn(choixx, "\n")] = '\0';
            } // enlever le \n
          }while(valid_numb(choixx) || strlen(choixx)>=10);
          switch(atoi(choixx)){
            case 0:
              // make a pdf file with node js i can't cause deadline is tomorrow
              break;
            case 1:
              free(choixx);
              break;
          }
        }
        break;
      case 1:
        free(choix);
        delete(servIp,3000,"names",ID);
        return 0;
    }
  }
}