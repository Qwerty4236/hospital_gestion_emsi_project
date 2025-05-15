#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
    fprintf(file,"NAME,AGE,DosM\n");
    fclose(file);
  }
}

int check_first_line() {
  if (exist_file()){
    FILE *file = fopen("user.csv", "r");  // File pointer
    char *first_line=(char *)malloc(MAX_LINE*sizeof(char)); // Alocation dinamique
    if (fgets(first_line, MAX_LINE, file)) { // Voir si la premiere line existe et fait le traitement suivant ↓
        first_line[strcspn(first_line, "\n")] = '\0';  // Transformer le \n en char null (\0)
        if(strcmp(first_line, "NAME,AGE,DosM") != 0){ // Voir si il est egale au tete de page
          file=fopen("user.csv","w");
          fprintf(file,"NAME,AGE,DosM\n");
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

int main(){
  
}