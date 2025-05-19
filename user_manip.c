#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <windows.h>
#define MAX_LINE 256

int exist_file(){
  FILE *file=fopen("user.csv","r");
  if (file==NULL){
    fclose(file);
    return 0;
  }
  else {
    fclose(file);
    return 1;
  }
}

void make_file(){
  if(!exist_file()){
    FILE *file=fopen("user.csv","w");
    fprintf(file,"NAME,SEX,AGE,PRO,SF,A,AM,TELL\n");
    fclose(file);
  }
}

int check_first_line() {
  if (exist_file()){
    FILE *file = fopen("user.csv", "r");  // File pointer
    char *first_line=(char *)malloc(MAX_LINE*sizeof(char)); // Alocation dinamique
    if (fgets(first_line, MAX_LINE, file)) { // Voir si la premiere line existe et fait le traitement suivant ↓
        first_line[strcspn(first_line, "\n")] = '\0';  // Transformer le \n en char null (\0)
        if(strcmp(first_line, "NAME,SEX,AGE,PRO,SF,A,AM,TEL") != 0){ // Voir si il est egale au tete de page
          file=fopen("user.csv","w");
          fprintf(file,"NAME,SEX,AGE,PRO,SF,A,AM,TEL\n");
        }    
    }
    free(first_line); // Free la memoir no utiliser
    fclose(file);
  }
  return 0;
}

char* get_info(int index){
  FILE *file=fopen("user.csv","r");
  int count=-1;
   /* On commence le compteur à -1 parce qu'on commence par l'en-tête (ligne 1). 
   Le premier élément réel est à la ligne 2, donc si on veut y accéder comme dans une liste 
   (qui commence à l'index 0), on fait -1 + 1 (pour l'en-tête), ce qui donne 0 - 
   ce qui veut dire que le premier élément correspond à la ligne 2. */
  if (!exist_file()) {
    perror("Error");
    return '\0';
  }
  else{
    char *line=(char *)malloc(MAX_LINE*sizeof(char));
    while (fgets(line,MAX_LINE,file)){ // On loop jusqu'a rien trouver dans le fichier
      
      if (count>=index){ // Voir si le compteur est egale a l'index qu'on veut trouver 
        line[strcspn(line, "\n")]='\0';
        fclose(file);
        return line; // On retourne la ligne 
      }  
      count++;
    }
    free(line);
    return '\0';
  }
}

int mini(int a, int b, int c) {
    if (a <= b && a <= c) return a;
    if (b <= a && b <= c) return b;
    return c;
}

int levenshtein_max2(const char *s1, const char *s2, int max_dist) {
    int len1 = strlen(s1);
    int len2 = strlen(s2);

    // Si la différence de longueur dépasse le seuil, inutile de comparer
    if (abs(len1 - len2) > max_dist)
        return max_dist + 1;

    int *prev = malloc((len2 + 1) * sizeof(int));
    int *curr = malloc((len2 + 1) * sizeof(int));

    for (int j = 0; j <= len2; j++)
        prev[j] = j;

    for (int i = 1; i <= len1; i++) {
        curr[0] = i;
        int min_in_row = curr[0];

        for (int j = 1; j <= len2; j++) {
            int cost = (tolower(s1[i - 1]) == tolower(s2[j - 1])) ? 0 : 1;
            curr[j] = mini(
                prev[j] + 1,         // suppression
                curr[j - 1] + 1,     // insertion
                prev[j - 1] + cost   // substitution
            );
            if (curr[j] < min_in_row)
                min_in_row = curr[j];
        }

        if (min_in_row > max_dist) {
            free(prev);
            free(curr);
            return max_dist + 1;
        }

        int *tmp = prev;
        prev = curr;
        curr = tmp;
    }

    int result = prev[len2];
    free(prev);
    free(curr);
    return result;
}

BOOL WINAPI ConsoleHandler(DWORD signal) {
    if (signal == CTRL_CLOSE_EVENT || signal == CTRL_C_EVENT) {
        printf("Caught console close or Ctrl+C — cleaning up!\n");
        return TRUE;
    }
    return FALSE;
}


int get_lines(){
  // calcule combien de ligne on a dans le fichier
  FILE *file=fopen("user.csv","r");
  int count=-1;
  if (!exist_file()) {
    perror("Error");
    return -1;
  }
  char *line=(char *)malloc(MAX_LINE*sizeof(char));
  while (fgets(line,MAX_LINE,file))
  {  
    count++;
  }
  free(line);
  fclose(file);
  return count;
}

char* get_infos(int index,int numb){
  if(numb>7 || numb<0){
    return '\0';
  }
  // Il prend la valeur de la ligne retourner par l'index (fonction get_info retourne la ligne)
  if (!exist_file()){
    return '\0';
  }
  
  char *x=(char *)malloc(MAX_LINE*sizeof(char));
  char *type=(char *)malloc(MAX_LINE*sizeof(char));
  x=get_info(index);
  int c=0;
  x=strtok(x,",");
  for (int i=0;i<numb;i++){
    x=strtok(NULL,",");
  }
  return x;
}

int main(){
    // if (!SetConsoleCtrlHandler(ConsoleHandler, TRUE)) {
    //   printf("Error: Could not set control handler\n");
    //   return 1;
    // }

    // printf("Running... Press Ctrl+C or close the window.\n");

    // while (1) {
    //   Sleep(1000);  // Simulate work
    // }
    printf("%s %s %s %s %s %s %s %s",get_infos(0,0),get_infos(0,1),get_infos(0,2),get_infos(0,3),get_infos(0,4),get_infos(0,5),get_infos(0,6),get_infos(0,7));
}
