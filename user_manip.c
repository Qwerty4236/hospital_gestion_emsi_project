#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <windows.h>
#define MAX_LINE 256

int valid_numb(char *s){
  while (*s)
  {
    if(!isdigit(*s)){
      return 1;
    }
    s++;
  }
  return 0;
}

void flushInput() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

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
  x=get_info(index);
  x=strtok(x,",");
  for (int i=0;i<numb;i++){
    x=strtok(NULL,",");
  }
  return x;
}

//NAME,SEX,AGE,PRO,SF,A,AM,TEL
void add_user(char *name,char *sex,char* age,char *pro,char *sf, char *a, char *am, char *tel){
  if(exist_file()){
    FILE *file=fopen("user.csv","a+");
    fprintf(file,"%s,%s,%s,%s,%s,%s,%s,%s\n",name,sex,age,pro,sf,a,am,tel);
    printf("%s est ajouter au fichier",name);
    fclose(file);
  }
}

void remove_line(int lineToRemove) {
  if (lineToRemove<0){
    return;
  }
    FILE *file = fopen("user.csv", "r");
    FILE *temp = fopen("temp.csv", "w");
    if (!file || !temp) {
        perror("Error opening file");
        return;
    }
    char buffer[1024];
    int currentLine = -1;
    while (fgets(buffer, sizeof(buffer), file)) {
        if (currentLine != lineToRemove) {
            fputs(buffer, temp);
        }
        currentLine++;
    }
    fclose(file);
    fclose(temp);
    remove("user.csv");
    rename("temp.csv", "user.csv");
}

void modify(int index){
  if (!exist_file() || index<0){
    perror("Erreur");
    return;
  }
  if(index>get_lines()-1){
    perror("Erreur");
    return;
  }
  char *info[]={get_infos(index,0),get_infos(index,1),get_infos(index,2),get_infos(index,3),
  get_infos(index,4),get_infos(index,5),get_infos(index,6),get_infos(index,7)},

  *mrstr=(char *)malloc(40*sizeof(char)),*text=(char *)malloc(10*sizeof(char));

  const char *params[]={"NOM","SEX","AGE","PROFESSION","SITUATION FAMILIALE","ADRESSE","AFFILIATION MUTULLE","TEL"};
  printf(
"\n\nSELECTIONER QUOI MODIFIER\n\n"
"+-----+------------------------------------------+\n"
"|  0  | %-41s|\n"
"+-----+------------------------------------------+\n"
"|  1  | %-41s|\n"
"+-----+------------------------------------------+\n"
"|  2  | %-41s|\n"
"+-----+------------------------------------------+\n"
"|  3  | %-41s|\n"
"+-----+------------------------------------------+\n"
"|  4  | %-41s|\n"
"+-----+------------------------------------------+\n"
"|  5  | %-41s|\n"
"+-----+------------------------------------------+\n"
"|  6  | %-41s|\n"
"+-----+------------------------------------------+\n"
"|  7  | %-41s|\n"
"+-----+------------------------------------------+\n"
"|  8  | SORTIR                                   |\n"
"+-----+------------------------------------------+\n\n",params[0],params[1],params[2],params[3],params[4],params[5],params[6],params[7]);
    do{
      printf("choisir une option a modifier\n>");
      fgets(text,10,stdin);
      if (strchr(text, '\n') == NULL) {
        flushInput();
      } else {
        text[strcspn(text, "\n")] = '\0';
      } // enlever le \n
    }while(valid_numb(text) || strlen(text)>=10 || atoi(text)<0 || atoi(text)>8);
    
    if(atoi(text)==8){
      printf("AUCUNE MODIFICATION SERA EFFECTUER\n");
      return;
    }
    
    do{
      printf("info a modifier -> %s\n>",params[atoi(text)]);
      fgets(mrstr,40,stdin);
      if (strchr(mrstr, '\n') == NULL) {
        flushInput();
      } else {
        mrstr[strcspn(mrstr, "\n")] = '\0';
      } // enlever le \n
    }while(strlen(mrstr)>=40);

    remove_line(index);
    info[atoi(text)]=mrstr;
    add_user(info[0],info[1],info[2],info[3],info[4],info[5],info[6],info[7]);
}

void show_infos(int index){
  if (!exist_file() || index<0){
    perror("Erreur");
    return;
  }
  if(index>get_lines()-1){
    perror("Erreur");
    return;
  }
  char *info[]={get_infos(index,0),get_infos(index,1),get_infos(index,2),get_infos(index,3),
  get_infos(index,4),get_infos(index,5),get_infos(index,6),get_infos(index,7)};

    printf(
"\n\nInfo utilisateur ID: %d\n\n"
"+-------+------------------------------------------+-------+------------------------------------------+\n"
"|  Nom  | %-41s|  Sex  | %-41s|\n"
"+-------+------------------------------------------+-------+------------------------------------------+\n"
"|  Age  | %-41s|  Pro  | %-41s|\n"
"+-------+------------------------------------------+-------+------------------------------------------+\n"
"|  S.F  | %-41s|  ADR  | %-41s|\n"
"+-------+------------------------------------------+-------+------------------------------------------+\n"
"|  A.M  | %-41s|  Tel  | %-41s|\n"
"+-------+------------------------------------------+-------+------------------------------------------+\n\n",index,info[0],info[1],info[2],info[3],info[4],info[5],info[6],info[7]);
}

int list_user(){
  printf("\n\n%46s\n","LISTE D'UTILISATEUR");
  for (int i = 0; i < get_lines(); i++)
  {
    printf(
      "+---------+-----------------------------------------+---------+-------------+\n"
      "|    %-5d| %-40s|   %-6s|   %-8s  |\n",i,get_infos(i,0),get_infos(i,2),get_infos(i,1));
  }
  printf("+---------+-----------------------------------------+---------+-------------+\n\n");
  Sleep(500);
}


