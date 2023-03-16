#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_POKEMONS 1190
#define MAX_STATS 11
#define MAX_NAME_LENGTH 50

// Definición de la estructura Pokemon
typedef struct {
    int id;
    char name[MAX_NAME_LENGTH];
    char form[MAX_NAME_LENGTH];
    char type1[MAX_NAME_LENGTH];
    char type2[MAX_NAME_LENGTH];
    int total;
    int hp;
    int attack;
    int defense;
    int spAtk;
    int spDef;
    int speed;
    int generation;

} Pokemon;

// Definición de la estructura de la lista de pokémons

typedef struct node {
    int id;
    char name[MAX_NAME_LENGTH];
    char form[MAX_NAME_LENGTH];
    char type1[MAX_NAME_LENGTH];
    char type2[MAX_NAME_LENGTH];
    int total;
    int hp;
    int attack;
    int defense;
    int spAtk;
    int spDef;
    int speed;
    int generation;
    
    struct node *next;
} PokemonList;

// Función para cargar la base de datos de pokémon
void loadDatabase(char *filename, PokemonList **database, int *size) {
    int i = 0;
    // Abrir el archivo en modo lectura
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("No se ha podido abrir el archivo.\\n");
        exit(1);

    }
    printf("Cargando la base de datos... Exito\n");
    // Leer el archivo línea por línea y cargar los datos en la estructura de la base de datos
    char pokemones[1191];
    //char *status =  NULL;
    PokemonList *current, *prev;
    *database = NULL;

    while (fgets(pokemones, sizeof(pokemones), fp) != NULL) {
        
        
        current = (PokemonList *) malloc(sizeof(PokemonList ));
            if (current == NULL) {
                printf("No se ha podido asignar memoria.\n");
                exit(1);
            }
            // Leemos los datos del archivo y los asignamos a la estructura de Pokemon dentro del nodo actual
            sscanf(pokemones, "%d,%49[^,],%49[^,],%49[^,],%49[^,],%d,%d,%d,%d,%d,%d,%d,%d", 
            &current->id, current->name, current->form, current->type1, current->type2, &current->total, &current->hp, &current->attack, &current->defense, &current->spAtk, &current->spDef, &current->speed, &current->generation);
            // Agregamos el nodo actual a la lista enlazada
            current->next = NULL;
            if (*database == NULL) 
            {
                *database = current;
            } 
            else {
                prev->next = current;
            }
            prev = current;
            i++;
           
    }
    //cerrar el archivo
    fclose(fp);

    // Guardar la cantidad de registros en la base de datos
    *size = i;

}

 

// Función para mostrar la cantidad de registros de la base de datos

void showSize(int size) {
    printf("La base de datos contiene %d registros.\n", size);
}

// Función para mostrar los primeros n registros de la base de datos
void showRange(PokemonList *database, int n) {
    if (n > MAX_POKEMONS) {
        printf("El valor de n es demasiado grande.\n");
        return;
    }

    printf("Los primeros %d registros de la base de datos son:\n", n);
   
    PokemonList *currentPokemon = database;

    for (int i = 0; i < n && database != NULL; i++) {
        printf("%d, %s, %s, %s, %s, %d, %d, %d, %d, %d, %d, %d, %d\n", 
           currentPokemon->id,
           currentPokemon->name,
           currentPokemon->form,
           currentPokemon->type1,
           currentPokemon->type2,
           currentPokemon->total,
           currentPokemon->hp,
           currentPokemon->attack,
           currentPokemon->defense,
           currentPokemon->spAtk,
           currentPokemon->spDef,
           currentPokemon->speed,
           currentPokemon->generation);

        currentPokemon = currentPokemon->next;
       
    }

}

// Función para mostrar el registro con ID n
void showPokemon(PokemonList *database, int id) {
 PokemonList *currentPokemon = database;
    if (id > MAX_POKEMONS) {
        printf("El valor de id es demasiado grande.\n");
        return;
    }
    printf("El pokemon con %d id es:\n", id);
     while (currentPokemon != NULL) {
        if (currentPokemon->id == id) {
            printf("%d, %s, %s, %s, %s, %d, %d, %d, %d, %d, %d, %d, %d\n",
                   currentPokemon->id,
                   currentPokemon->name,
                   currentPokemon->form,
                   currentPokemon->type1,
                   currentPokemon->type2,
                   currentPokemon->total,
                   currentPokemon->hp,
                   currentPokemon->attack,
                   currentPokemon->defense,
                   currentPokemon->spAtk,
                   currentPokemon->spDef,
                   currentPokemon->speed,
                   currentPokemon->generation);
            return;
        }
        currentPokemon = currentPokemon->next;
    }

    printf("No se encontró un pokemon con ID %d.\n", id);
}


//Función para buscar pokémon por stat
void searchPokemon(PokemonList *database, int size, char *stat, int value, PokemonList **result) {
    // Crear la lista de resultados
    *result = NULL;
    PokemonList *currentPokemon = database;
    PokemonList *current, *prev;

    // Recorrer la base de datos y agregar los pokémon que coincidan con la búsqueda a la lista de resultados
     for (int i = 0; i < MAX_POKEMONS && database != NULL; i++){
        if (strcmp(stat, "id") == 0 && currentPokemon->id == value) {
             current = (PokemonList *) malloc(sizeof(PokemonList ));
            if (current == NULL) {
                printf("No se ha podido asignar memoria.\\n");
                exit(1);
            }
            current->next = NULL;
            if (*result == NULL) 
            {
                *result = current;
            } 
            else {
                prev->next = current;
            }
            prev = current;

        } else if (strcmp(stat, "name") == 0 && strcmp(currentPokemon->name, stat) == 0) {
            current = (PokemonList *) malloc(sizeof(PokemonList ));
            if (current == NULL) {
                printf("No se ha podido asignar memoria.\\n");
                exit(1);
            }
            strcpy(current->name, currentPokemon->name);
            current->next = NULL;
            if (*result == NULL) 
            {
                *result = current;
            } 
            else {
                prev->next = current;
            }
            prev = current;

        } else if (strcmp(stat, "form") == 0 && strcmp(currentPokemon->form, stat) == 0) {
            current = (PokemonList *) malloc(sizeof(PokemonList ));
            if (current == NULL) {
                printf("No se ha podido asignar memoria.\\n");
                exit(1);
            }
            current->next = NULL;
            if (*result == NULL) 
            {
                *result = current;
            } 
            else {
                prev->next = current;
            }
            prev = current;

        } else if (strcmp(stat, "type1") == 0 && strcmp(currentPokemon->type1, stat) == 0) {
            current = (PokemonList *) malloc(sizeof(PokemonList ));
            if (current == NULL) {
                printf("No se ha podido asignar memoria.\\n");
                exit(1);
            }
            current->next = NULL;
            if (*result == NULL) 
            {
                *result = current;
            } 
            else {
                prev->next = current;
            }
            prev = current;

        } else if (strcmp(stat, "type2") == 0 && strcmp(currentPokemon->type2, stat) == 0) {
            current = (PokemonList *) malloc(sizeof(PokemonList ));
            if (current == NULL) {
                printf("No se ha podido asignar memoria.\\n");
                exit(1);
            }
            current->next = NULL;
            if (*result == NULL) 
            {
                *result = current;
            } 
            else {
                prev->next = current;
            }
            prev = current;

        } else if (strcmp(stat, "total") == 0 && currentPokemon->total == value) {
            current = (PokemonList *) malloc(sizeof(PokemonList ));
           
            if (current == NULL) {
                printf("No se ha podido asignar memoria.\\n");
                exit(1);
            }
            current->next = NULL;
            if (*result == NULL) 
            {
                *result = current;
            } 
            else {
                prev->next = current;
            }
            prev = current;
        } else if (strcmp(stat, "hp") == 0 && currentPokemon->hp == value) {
            current = (PokemonList *) malloc(sizeof(PokemonList ));
            if (current == NULL) {
                printf("No se ha podido asignar memoria.\\n");
                exit(1);
            }
            current->next = NULL;
            if (*result == NULL) 
            {
                *result = current;
            } 
            else {
                prev->next = current;
            }
            prev = current;;

        } else if (strcmp(stat, "attack") == 0 && currentPokemon->attack == value) {
            current = (PokemonList *) malloc(sizeof(PokemonList ));
            if (current == NULL) {
                printf("No se ha podido asignar memoria.\\n");
                exit(1);
            }
            current->next = NULL;
            if (*result == NULL) 
            {
                *result = current;
            } 
            else {
                prev->next = current;
            }
            prev = current;

        } else if (strcmp(stat, "defense") == 0 && currentPokemon->defense == value) {
            current = (PokemonList *) malloc(sizeof(PokemonList ));
            if (current == NULL) {
                printf("No se ha podido asignar memoria.\\n");
                exit(1);
            }
            current->next = NULL;
            if (*result == NULL) 
            {
                *result = current;
            } 
            else {
                prev->next = current;
            }
            prev = current;;

        } else if (strcmp(stat, "spAtk") == 0 && currentPokemon->spAtk == value) {
            current = (PokemonList *) malloc(sizeof(PokemonList ));
            if (current == NULL) {
                printf("No se ha podido asignar memoria.\\n");
                exit(1);
            }
            current->next = NULL;
            if (*result == NULL) 
            {
                *result = current;
            } 
            else {
                prev->next = current;
            }
            prev = current;

        } else if (strcmp(stat, "spDef") == 0 && currentPokemon->spDef == value) {
            current = (PokemonList *) malloc(sizeof(PokemonList ));
            if (current == NULL) {
                printf("No se ha podido asignar memoria.\\n");
                exit(1);
            }
            current->next = NULL;
            if (*result == NULL) 
            {
                *result = current;
            } 
            else {
                prev->next = current;
            }
            prev = current;

        } else if (strcmp(stat, "speed") == 0 && currentPokemon->speed == value) {
            current = (PokemonList *) malloc(sizeof(PokemonList ));
            if (current == NULL) {
                printf("No se ha podido asignar memoria.\\n");
                exit(1);
            }
            current->next = NULL;
            if (*result == NULL) 
            {
                *result = current;
            } 
            else {
                prev->next = current;
            }
            prev = current;

        } else if (strcmp(stat, "generation") == 0 && currentPokemon->generation == value) {
            current = (PokemonList *) malloc(sizeof(PokemonList ));
            if (current == NULL) {
                printf("No se ha podido asignar memoria.\\n");
                exit(1);
            }
            current->id = currentPokemon->id;  // copy the values of the matching pokemon to the new node
            strcpy(current->name, currentPokemon->name);
            strcpy(current->form, currentPokemon->form);
            strcpy(current->type1, currentPokemon->type1);
            strcpy(current->type2, currentPokemon->type2);
            current->total = currentPokemon->total;
            current->hp = currentPokemon->hp;
            current->attack = currentPokemon->attack;
            current->defense = currentPokemon->defense;
            current->spAtk = currentPokemon->spAtk;
            current->spDef = currentPokemon->spDef;
            current->speed = currentPokemon->speed;
            current->generation = currentPokemon->generation;
            current->next = NULL;
            if (*result == NULL) 
            {
                *result = current;
            } 
            else {
                prev->next = current;
            }
            prev = current;

        }    
    }

}

// Función para mostrar la lista de resultados
void showResultList(PokemonList *result){

    if (result == NULL) {
        printf("No se han encontrado resultados.\n");
        return;

    }

    PokemonList *currentPokemon = result;
    while (currentPokemon != NULL) {
        printf("%d %s %s %s %s %d %d %d %d %d %d %d\n",
                   currentPokemon->id,
                   currentPokemon->name,
                   currentPokemon->form,
                   currentPokemon->type1,
                   currentPokemon->type2,
                   currentPokemon->total,
                   currentPokemon->hp,
                   currentPokemon->attack,
                   currentPokemon->defense,
                   currentPokemon->spAtk,
                   currentPokemon->spDef,
                   currentPokemon->speed,
                   currentPokemon->generation);
        currentPokemon = currentPokemon->next;
    }

}

// Función para guardar la lista de resultados en un archivo
void saveResultList(char *filename, PokemonList *result) {

    FILE *fp;
    // Abrir el archivo en modo escritura
    fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("No se ha podido abrir el archivo.\\n");
        exit(1);
    }

    // Guardar los datos de la lista de resultados en el archivo
    PokemonList *currentPokemon = result;
    while (currentPokemon != NULL) {
        fprintf(fp, "%d,%s,%d,%s,%s,%d,%d,%d,%d,%d,%d,%d\\n",
                   currentPokemon->id,
                   currentPokemon->name,
                   currentPokemon->form,
                   currentPokemon->type1,
                   currentPokemon->type2,
                   currentPokemon->total,
                   currentPokemon->hp,
                   currentPokemon->attack,
                   currentPokemon->defense,
                   currentPokemon->spAtk,
                   currentPokemon->spDef,
                   currentPokemon->speed,
                   currentPokemon->generation);
        currentPokemon = currentPokemon->next;
    };

    // Cerrar el archivo
    fclose(fp);

}

int main() {
    PokemonList *database;
    int databaseSize = 0;
    PokemonList *searchResult = NULL;
    char command[10];
    int value;
    char stat[MAX_NAME_LENGTH];
    char filename[MAX_NAME_LENGTH];

    // Loop infinito para recibir comandos desde la terminal

    while (1) {
        printf("Ingrese un comando: ");
        scanf("%s", command); 

        if (strcmp(command, "exit") == 0) {
            printf("Saliendo de la aplicación...\n");
            break;

        } else if (strcmp(command, "load") == 0) {
                scanf("%s", filename);
                loadDatabase(filename, &database, &databaseSize);

        } else if (strcmp(command, "size") == 0) {
            showSize(databaseSize);

        } else if (strcmp(command, "range") == 0) {
            scanf("%d", &value);
            showRange(database, value);

        } else if (strcmp(command, "search") == 0) {
            scanf("%s %d", stat, &value);
            searchPokemon(database, databaseSize, stat, value, &searchResult);

        } else if (strcmp(command, "view") == 0) {
          showResultList(searchResult);

        } else if (strcmp(command, "show") == 0) {
            scanf("%d", &value);
            showPokemon(database, value);  

        } else if (strcmp(command, "save") == 0) {
            scanf("%s", filename);
            saveResultList(filename, searchResult);

        } else {
            printf("Comando no válido. Intente de nuevo.\n");

        }

    }
    return 0;

}
