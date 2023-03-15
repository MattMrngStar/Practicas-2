#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Declaración de estructuras 

#define Max_pok 1010
#define Max_stat 11
#define Max_name 50

typedef struct {
    int id;
    char name[Max_name];
    char form[Max_name];
    char type1[Max_name];
    char type2[Max_name];
    int total;
    int hp;
    int attack;
    int defense;
    int spatk;
    int spdef;
    int speed;
    int generation;
} Pokemon; 

typedef struct node {
    Pokemon pokemones;
    struct node *sig;

} basePokemon;

// Funcion principal 
int main(){
  char archivo[100];
  printf("Ingrese el nombre del archivo de base de datos: ");
  scanf("%s", archivo);

  // Abrir el archivo de la base de datos

  FILE *fp = fopen("./pokemon.csv", "r");
  if (fp == NULL){
    printf("No se pudo abrir el archivo.\n");
    exit(1);
  }

//Leer el numero de registros en el archivo
  //int numPokemones = 1190;
  //fscanf("./pokemon.csv", "%d", &numPokemones);
  
  // Crear una estructura de base de datos en el HEAP
  //basePokemon *base = (basePokemon *)malloc(sizeof(basePokemon));
 // base->numPokemones = numPokemones;

  // Reservar espacio para los registros en el HEAP
  //base->pokemones = (Pokemon *)malloc(numPokemones * sizeof(Pokemon));

  //Leer cada registro del archivo y almacenarlo en el HEAP

  char buffer[1191];
  char *status =  NULL;

  do{status = fgets(buffer, sizeof(buffer), fp);
        if(status != NULL){
            printf("%s",buffer);}
    }while (status !=NULL);
    printf("\n");

  //for (int i = 0; i < numPokemones; i++){
    //Pokemon r;
    //fscanf(fp, "%d %s %s %s %s %d %d %d %d %d %d %d %d", &r.id, r.name, r.form, r.type1, r.type2, &r.total, &r.hp, &r.attack, &r.defense, &r.spatk, &r.spdef, &r.speed, &r.generation);
    //base->pokemones[i] = r;
  //}

  // Cerrar el archivo de base de datos
  fclose(fp);

  // Imprimir la base cargada en la memoria 
  //printf("Base de datos cargada:\n");
 // printf("Número de registros: %d\n", base->numPokemones);
  //for (int i = 0; i < numPokemones; i++){
   // printf("Registro %d: id=%d, name=%s, form=%s, type1=%s, type2=%s, total=%d, hp=%d, attack=%d, defense=%d, spatk=%d, spdef=%d, speed=%d, generation=%d\n", i+1, base->pokemones[i].id, base->pokemones[i].name, base->pokemones[i].form, base->pokemones[i].type1, base->pokemones[i].type2, base->pokemones[i].total, base->pokemones[i].hp, base->pokemones[i].attack, base->pokemones[i].defense, base->pokemones[i].spatk, base->pokemones[i].spdef, base->pokemones[i].speed, base->pokemones[i].generation);
  //}

 return 0; 

}