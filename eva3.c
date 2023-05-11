#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <assert.h>

typedef struct IOperacionesComand IOperacionesComand;
typedef struct Comand Comand;
typedef struct pokedex pokedex;
typedef struct edit edit;
typedef struct NodoComand NodoComand;
typedef struct Line Line;
typedef struct Nodeline Nodeline;

#define LENGTH 50
#define LENGTHCOMAND 128
#define MAX_POKEMONS 1199
#define MAX_STATS 1200

int NumberConvert(char *cadena);
void AddComand(Comand *Comand, NodoComand **start, int undoMax);
void Destroyline(Nodeline *lines);
void DestroyComand(NodoComand *lines);

//Aqui construimos las estructuturas

struct IOperacionesComand{
    void (*deshacer)(Comand * const lines, Line * archivo);
};

struct Line{ 
    int id;
    char name[LENGTH];
    char form[LENGTH];
    char type1[LENGTH];
    char type2[LENGTH];
    int total;
    int hp;
    int attack;
    int defense;
    int spAtk;
    int spDef;
    int speed;
    int generation;
};

struct Nodeline{
    struct Line *dato;
    struct Nodeline *next;
};

struct NodoComand{
    struct Comand *dato;
    struct NodoComand *next;
};

//-------------------------------------------------------------------------------------

struct Comand{
    IOperacionesComand const *cptr;
    char nombre[LENGTH];
};

void Comand_ctor(Comand * const lines, char *nombre);
void Comand_dtor(Comand * const lines);
void Comand_undo(Comand * const lines, Line * archivo);

//-------------------------------------------------------------------------------------

struct pokedex{
    Comand EditPokemon;
    Line pokemonIngresado;
    int pos;
};

void pokedexCntr(pokedex * const lines, Line LCreada, int posicion, char *_nombre);
void destroyPokedex(pokedex * const lines);
void undoPokedex(Comand * const lines, Line * archivo);

//-------------------------------------------------------------------------------------

struct edit{
    Comand EditPokemon;
    int id; 
    char values[LENGTH];
    char Lastvalue[LENGTH];
};

void edit_ctor(edit * const lines, int id, char *stat, char *value, char *_nombre);
void edit_dtor(edit * const lines);
void edit_undo(Comand * const lines, Line * archivo);

//-------------------------------------------------------------------------------------

int main(){
    char ComandRecibido[LENGTHCOMAND];
    char TrueComand[LENGTHCOMAND];
    char extra1[LENGTHCOMAND];
    char extra2[LENGTHCOMAND];
    char extra3[LENGTHCOMAND];
    struct Line *archivo;
    struct Nodeline *LastList = NULL;
    struct NodoComand *lista = NULL;
    FILE *fp;
    int nulinesroRecibido;
    int undoMax = 100;
    
    archivo = calloc(MAX_STATS, sizeof(struct Line));
    while(1){
        
        // lee Comands y si tienen un extra añadido
        printf("Ingresa un comando: ");
        if(fgets(ComandRecibido, LENGTHCOMAND, stdin) != NULL){
            ComandRecibido[strlen(ComandRecibido) - 1] = 0;
            sscanf(ComandRecibido, "%[^ ] %[^ ] %[^ ] %s", TrueComand, extra1, extra2, extra3);
        }
        
        if(strcmp(TrueComand, "exit") == 0){
            free(archivo);
            printf("Nos vemos uwu\n");
            exit(EXIT_SUCCESS);
        }
        else if(strcmp(TrueComand, "load") == 0){
            fp = fopen(extra1, "r");
            if (fp == NULL){
                perror("error al abrir el archivo\n");
                return(EXIT_FAILURE);
            }

            char buffer[LENGTHCOMAND];
            char *status =  NULL;
            int i = 0;
            status = fgets(buffer, LENGTHCOMAND,fp);
            do{
                status = fgets(buffer, LENGTHCOMAND,fp);
                if(status != NULL){
                    sscanf(buffer, "%d,%[^,],%[^,],%[^,],%[^,],%d,%d,%d,%d,%d,%d,%d,%d",
                                    &archivo[i].id,
                                    archivo[i].name,
                                    archivo[i].form,
                                    archivo[i].type1,
                                    archivo[i].type2,
                                    &archivo[i].total,
                                    &archivo[i].hp,
                                    &archivo[i].attack,
                                    &archivo[i].defense,
                                    &archivo[i].spAtk,
                                    &archivo[i].spDef,
                                    &archivo[i].speed,
                                    &archivo[i].generation);
                    i++;
                }
            }while (status !=NULL);
            printf("Archivo cargado correctamente\n");            
        }
        else if(strcmp(TrueComand, "size") == 0){
            for(int i = MAX_POKEMONS; i > 0; i--){
                if (archivo[i].id != 0){
                    printf("La cantidad de registros en la base de datos son: %d\n", i);
                    break;
                }
            }

        }
        else if(strcmp(TrueComand, "range") == 0){
            nulinesroRecibido = NumberConvert(extra1);
            
            for (int i = 0; i < nulinesroRecibido; i++){
                printf("%d,%s,%s,%s,%s,%d,%d,%d,%d,%d,%d,%d,%d\n",
                        archivo[i].id,
                        archivo[i].name,
                        archivo[i].form,
                        archivo[i].type1,
                        archivo[i].type2,
                        archivo[i].total,
                        archivo[i].hp,
                        archivo[i].attack,
                        archivo[i].defense,
                        archivo[i].spAtk,
                        archivo[i].spDef,
                        archivo[i].speed,
                        archivo[i].generation);
            }
        }
        else if(strcmp(TrueComand, "show") == 0){
            nulinesroRecibido = NumberConvert(extra1);

            if(nulinesroRecibido == -1 && strcmp(extra1, "search") == 0){
                struct Nodeline *Current = LastList;
                if(Current == NULL){
                    printf("No se ha creado una lista aún.\n");
                    continue;
                }
                do{
                    printf("%d,%s,%s,%s,%s,%d,%d,%d,%d,%d,%d,%d,%d\n",
                        Current->dato->id,
                        Current->dato->name,
                        Current->dato->form,
                        Current->dato->type1,
                        Current->dato->type2,
                        Current->dato->total,
                        Current->dato->hp,
                        Current->dato->attack,
                        Current->dato->defense,
                        Current->dato->spAtk,
                        Current->dato->spDef,
                        Current->dato->speed,
                        Current->dato->generation);
                    Current = Current -> next;
                } while(Current != NULL);
            }
            else{
                for (int i = 0; i < MAX_STATS; i++){
                    if(nulinesroRecibido == archivo[i].id){
                        printf("%d,%s,%s,%s,%s,%d,%d,%d,%d,%d,%d,%d,%d\n",
                            archivo[i].id,
                            archivo[i].name,
                            archivo[i].form,
                            archivo[i].type1,
                            archivo[i].type2,
                            archivo[i].total,
                            archivo[i].hp,
                            archivo[i].attack,
                            archivo[i].defense,
                            archivo[i].spAtk,
                            archivo[i].spDef,
                            archivo[i].speed,
                            archivo[i].generation);
                        break;
                    }
                }
            }
            
        }
        else if(strcmp(TrueComand, "search") == 0){
            struct Nodeline *Current = NULL;

            if(strcmp(extra1, "id") == 0){
                Destroyline(LastList);
                int val = NumberConvert(extra2);

                for(int i = 0; i < MAX_STATS; i++){
                    if(archivo[i].id == val){
                        struct Nodeline *new;
                        new = malloc(sizeof(struct Nodeline));
                        new->dato = &archivo[i];
                        new->next = NULL;
                        if (Current == NULL){
                            Current = new;
                            LastList = new;
                        }
                        else{
                            Current->next = new;
                            Current = new;
                        }
                    }
                }
            }
            else if(strcmp(extra1, "name") == 0){
                Destroyline(LastList);
                
                for(int i = 0; i < MAX_STATS; i++){
                    if(strcmp(archivo[i].name, extra2) == 0){
                        struct Nodeline *new;
                        new = malloc(sizeof(struct Nodeline));
                        new->dato = &archivo[i];
                        new->next = NULL;
                        if (Current == NULL){
                            Current = new;
                            LastList = new;
                        }
                        else{
                            Current->next = new;
                            Current = new;
                        }
                    }
                }
            }
            else if(strcmp(extra1, "form") == 0){
                Destroyline(LastList);
                
                for(int i = 0; i < MAX_STATS; i++){
                    if(strcmp(archivo[i].form, extra2) == 0){
                        struct Nodeline *new;
                        new = malloc(sizeof(struct Nodeline));
                        new->dato = &archivo[i];
                        new->next = NULL;
                        if (Current == NULL){
                            Current = new;
                            LastList = new;
                        }
                        else{
                            Current->next = new;
                            Current = new;
                        }
                    }
                }
            }
            else if(strcmp(extra1, "type1") == 0){
                Destroyline(LastList);
                
                for(int i = 0; i < MAX_STATS; i++){
                    if(strcmp(archivo[i].type1, extra2) == 0){
                        struct Nodeline *new;
                        new = malloc(sizeof(struct Nodeline));
                        new->dato = &archivo[i];
                        new->next = NULL;
                        if (Current == NULL){
                            Current = new;
                            LastList = new;
                        }
                        else{
                            Current->next = new;
                            Current = new;
                        }
                    }
                }
            }
            else if(strcmp(extra1, "type2") == 0){
                Destroyline(LastList);
                
                for(int i = 0; i < MAX_STATS; i++){
                    if(strcmp(archivo[i].type2, extra2) == 0){
                        struct Nodeline *new;
                        new = malloc(sizeof(struct Nodeline));
                        new->dato = &archivo[i];
                        new->next = NULL;
                        if (Current == NULL){
                            Current = new;
                            LastList = new;
                        }
                        else{
                            Current->next = new;
                            Current = new;
                        }
                    }
                }
            }
            else if(strcmp(extra1, "total") == 0){
                Destroyline(LastList);
                int val = NumberConvert(extra2);

                for(int i = 0; i < MAX_STATS; i++){
                    if(archivo[i].total == val){
                        struct Nodeline *new;
                        new = malloc(sizeof(struct Nodeline));
                        new->dato = &archivo[i];
                        new->next = NULL;
                        if (Current == NULL){
                            Current = new;
                            LastList = new;
                        }
                        else{
                            Current->next = new;
                            Current = new;
                        }
                    }
                }
            }
            else if(strcmp(extra1, "hp") == 0){
                Destroyline(LastList);
                int val = NumberConvert(extra2);

                for(int i = 0; i < MAX_STATS; i++){
                    if(archivo[i].hp == val){
                        struct Nodeline *new;
                        new = malloc(sizeof(struct Nodeline));
                        new->dato = &archivo[i];
                        new->next = NULL;
                        if (Current == NULL){
                            Current = new;
                            LastList = new;
                        }
                        else{
                            Current->next = new;
                            Current = new;
                        }
                    }
                }
            }
            else if(strcmp(extra1, "attack") == 0){
                Destroyline(LastList);
                int val = NumberConvert(extra2);

                for(int i = 0; i < MAX_STATS; i++){
                    if(archivo[i].attack == val){
                        struct Nodeline *new;
                        new = malloc(sizeof(struct Nodeline));
                        new->dato = &archivo[i];
                        new->next = NULL;
                        if (Current == NULL){
                            Current = new;
                            LastList = new;
                        }
                        else{
                            Current->next = new;
                            Current = new;
                        }
                    }
                }
            }
            else if(strcmp(extra1, "defense") == 0){
                Destroyline(LastList);
                int val = NumberConvert(extra2);

                for(int i = 0; i < MAX_STATS; i++){
                    if(archivo[i].defense == val){
                        struct Nodeline *new;
                        new = malloc(sizeof(struct Nodeline));
                        new->dato = &archivo[i];
                        new->next = NULL;
                        if (Current == NULL){
                            Current = new;
                            LastList = new;
                        }
                        else{
                            Current->next = new;
                            Current = new;
                        }
                    }
                }
            }
            else if(strcmp(extra1, "Sp.Atk") == 0){
                Destroyline(LastList);
                int val = NumberConvert(extra2);

                for(int i = 0; i < MAX_STATS; i++){
                    if(archivo[i].spAtk == val){
                        struct Nodeline *new;
                        new = malloc(sizeof(struct Nodeline));
                        new->dato = &archivo[i];
                        new->next = NULL;
                        if (Current == NULL){
                            Current = new;
                            LastList = new;
                        }
                        else{
                            Current->next = new;
                            Current = new;
                        }
                    }
                }
            }
            else if(strcmp(extra1, "Sp.Def") == 0){
                Destroyline(LastList);
                int val = NumberConvert(extra2);

                for(int i = 0; i < MAX_STATS; i++){
                    if(archivo[i].spDef == val){
                        struct Nodeline *new;
                        new = malloc(sizeof(struct Nodeline));
                        new->dato = &archivo[i];
                        new->next = NULL;
                        if (Current == NULL){
                            Current = new;
                            LastList = new;
                        }
                        else{
                            Current->next = new;
                            Current = new;
                        }
                    }
                }
            }
            else if(strcmp(extra1, "speed") == 0){
                Destroyline(LastList);
                int val = NumberConvert(extra2);

                for(int i = 0; i < MAX_STATS; i++){
                    if(archivo[i].speed == val){
                        struct Nodeline *new;
                        new = malloc(sizeof(struct Nodeline));
                        new->dato = &archivo[i];
                        new->next = NULL;
                        if (Current == NULL){
                            Current = new;
                            LastList = new;
                        }
                        else{
                            Current->next = new;
                            Current = new;
                        }
                    }
                }
            }
            else if(strcmp(extra1, "generation") == 0){
                Destroyline(LastList);
                int val = NumberConvert(extra2);

                for(int i = 0; i < MAX_STATS; i++){
                    if(archivo[i].generation == val){
                        struct Nodeline *new;
                        new = malloc(sizeof(struct Nodeline));
                        new->dato = &archivo[i];
                        new->next = NULL;
                        if (Current == NULL){
                            Current = new;
                            LastList = new;
                        }
                        else{
                            Current->next = new;
                            Current = new;
                        }
                    }
                }
            }
            else{
                printf("Esa caracteristica no existe, por favor intenta nuevamente\n");
                continue;
            }
            printf("Lista cargada exitosamente, use el comando save para guardarla o show search para verla\n");
        }
        else if(strcmp(TrueComand, "save") == 0){
            FILE *fn;
            struct Nodeline *Current = LastList;

            fn = fopen(extra1, "w");
            if (fn == NULL){
                perror("error al crear el archivo\n");
                return(EXIT_FAILURE);
            }
            if (Current == NULL){
                printf("No se ha creado una lista aún.\n");
                continue;
            }

            while(Current != NULL){
                fprintf(fn, "%d,%s,%s,%s,%s,%d,%d,%d,%d,%d,%d,%d,%d\n",
                    Current->dato->id,
                    Current->dato->name,
                    Current->dato->form,
                    Current->dato->type1,
                    Current->dato->type2,
                    Current->dato->total,
                    Current->dato->hp,
                    Current->dato->attack,
                    Current->dato->defense,
                    Current->dato->spAtk,
                    Current->dato->spDef,
                    Current->dato->speed,
                    Current->dato->generation);
                Current = Current -> next;
            }
            printf("Archivo creado correctamente\n");
        }
        else if(strcmp(TrueComand, "mkpok") == 0){
            struct Line LCreada;
            int posicionL;

            for(int i = 0; i < MAX_STATS; i++){
                printf("Creando pokemon...\n");
                if(archivo[i].id == 0){
                    sscanf(extra1, "%d,%[^,],%[^,],%[^,],%[^,],%d,%d,%d,%d,%d,%d,%d,%d",
                                    &archivo[i].id,
                                    archivo[i].name,
                                    archivo[i].form,
                                    archivo[i].type1,
                                    archivo[i].type2,
                                    &archivo[i].total,
                                    &archivo[i].hp,
                                    &archivo[i].attack,
                                    &archivo[i].defense,
                                    &archivo[i].spAtk,
                                    &archivo[i].spDef,
                                    &archivo[i].speed,
                                    &archivo[i].generation);
                    LCreada = archivo[i];
                    posicionL = i;
                    printf("Hecho! :)\n");
                    break;
                }
            }

            pokedex *ComandHecho = malloc(sizeof(pokedex));
            pokedexCntr(ComandHecho, LCreada, posicionL, "mkpok");

            AddComand((Comand *)ComandHecho, &lista, undoMax);
        }
        else if(strcmp(TrueComand, "edit") == 0){
            int idBuscado = NumberConvert(extra1);
            char values[20];
            char Lastvalue[20];

            if(strcmp(extra2, "name") == 0){
                memcpy(values, "name", 20);
                for(int i = 0; i < MAX_STATS; i++){
                    if(archivo[i].id == idBuscado){
                        memcpy(Lastvalue, archivo[i].name, sizeof(archivo[i].name) + 1);
                        memcpy(archivo[i].name, extra3, 20);
                        break;
                    }
                }
            }
            else if(strcmp(extra2, "form") == 0){
                memcpy(values, "form",  LENGTH);
                for(int i = 0; i < MAX_STATS; i++){
                    if(archivo[i].id == idBuscado){
                        memcpy(Lastvalue, archivo[i].form, sizeof(archivo[i].form) + 1);
                        memcpy(archivo[i].form, extra3, 20);
                        break;
                    }
                }
            }
            else if(strcmp(extra2, "type1") == 0){
                memcpy(values, "Type 1", LENGTH);
                for(int i = 0; i < MAX_STATS; i++){
                    if(archivo[i].id == idBuscado){
                        memcpy(Lastvalue, archivo[i].type1, sizeof(archivo[i].type1) + 1);
                        memcpy(archivo[i].type1, extra3, 20);
                        break;
                    }
                }
            }
            else if(strcmp(extra2, "type2") == 0){
                memcpy(values, "Type 2", LENGTH);
                for(int i = 0; i < MAX_STATS; i++){
                    if(archivo[i].id == idBuscado){
                        memcpy(Lastvalue, archivo[i].type2, sizeof(archivo[i].type2) + 1);
                        memcpy(archivo[i].type2, extra3, 20);
                        break;
                    }
                }
            }
            else if(strcmp(extra2, "total") == 0){
                memcpy(values, "total", LENGTH);
                for(int i = 0; i < MAX_STATS; i++){
                    if(archivo[i].id == idBuscado){
                        sprintf(Lastvalue, "%d", archivo[i].total);
                        int valor = NumberConvert(extra3);
                        archivo[i].total = valor;
                        break;
                    }
                }
            }
            else if(strcmp(extra2, "hp") == 0){
                memcpy(values, "hp", LENGTH);
                for(int i = 0; i < MAX_STATS; i++){
                    if(archivo[i].id == idBuscado){
                        sprintf(Lastvalue, "%d", archivo[i].hp);
                        int valor = NumberConvert(extra3);
                        archivo[i].hp = valor;
                        break;
                    }
                }
            }
            else if(strcmp(extra2, "attack") == 0){
                memcpy(values, "attack", LENGTH);
                for(int i = 0; i < MAX_STATS; i++){
                    if(archivo[i].id == idBuscado){
                        sprintf(Lastvalue, "%d", archivo[i].attack);
                        int valor = NumberConvert(extra3);
                        archivo[i].attack = valor;
                        break;
                    }
                }
            }
            else if(strcmp(extra2, "defense") == 0){
                memcpy(values, "defense", LENGTH);
                for(int i = 0; i < MAX_STATS; i++){
                    if(archivo[i].id == idBuscado){
                        sprintf(Lastvalue, "%d", archivo[i].defense);
                        int valor = NumberConvert(extra3);
                        archivo[i].defense = valor;
                        break;
                    }
                }
            }
            else if(strcmp(extra2, "Sp.Atk") == 0){
                memcpy(values, "Sp.Atk", 20);
                for(int i = 0; i < MAX_STATS; i++){
                    if(archivo[i].id == idBuscado){
                        sprintf(Lastvalue, "%d", archivo[i].spAtk);
                        int valor = NumberConvert(extra3);
                        archivo[i].spAtk = valor;
                        break;
                    }
                }
            }
            else if(strcmp(extra2, "Sp.Def") == 0){
                memcpy(values, "Sp,Def", LENGTH);
                for(int i = 0; i < MAX_STATS; i++){
                    if(archivo[i].id == idBuscado){
                        sprintf(Lastvalue, "%d", archivo[i].spDef);
                        int valor = NumberConvert(extra3);
                        archivo[i].spDef = valor;
                        break;
                    }
                }
            }
            else if(strcmp(extra2, "speed") == 0){
                memcpy(values, "speed", LENGTH);
                for(int i = 0; i < MAX_STATS; i++){
                    if(archivo[i].id == idBuscado){
                        sprintf(Lastvalue, "%d", archivo[i].speed);
                        int valor = NumberConvert(extra3);
                        archivo[i].speed = valor;
                        break;
                    }
                }
            }
            else if(strcmp(extra2, "generation") == 0){
                memcpy(values, "generation", LENGTH);
                for(int i = 0; i < MAX_STATS; i++){
                    if(archivo[i].id == idBuscado){
                        sprintf(Lastvalue, "%d", archivo[i].generation);
                        int valor = NumberConvert(extra3);
                        archivo[i].generation = valor;
                        break;
                    }
                }
            }

            edit *ComandHecho = malloc(sizeof(edit));
            edit_ctor(ComandHecho, idBuscado, values, Lastvalue, "edit");

            AddComand((Comand *)ComandHecho, &lista, undoMax);
        }
        else if(strcmp(TrueComand, "undomax") == 0){
            undoMax = NumberConvert(extra1);
            printf("Ahora puedes deshacer hasta %d comandos.\n", undoMax);

            if(undoMax == -1){
                undoMax = 0;
                printf("Por favor ingrese un número válido.\n");
            }
        }
        else if(strcmp(TrueComand, "undo") == 0){
            int n = NumberConvert(extra1);
            NodoComand *actual = lista;

            if(n == -1 || n > undoMax){
                n = 100;
                printf("Por favor ingrese un numero válido.\n");
            }

            if(lista == NULL){
                printf("no se ha realizado ningun Comando para deshacer.\n");
                continue;
            }

            for(int i = 1; i <= n; i++){
                actual->dato->cptr->deshacer(actual->dato, archivo);
                actual = actual->next;
                printf("Se deshicieron los ultimos %d comandos", n);
            }
            lista = actual;
        }
        else{
            printf("El Comando ingresado no existe, por favor intente de nuevo\n");
        }
    }
    exit(EXIT_SUCCESS);
}

int NumberConvert(char *cadena){
    long val;
    char *endPrt;
    errno = 0;
    val = strtol(cadena, &endPrt, 10);
    /* Check for various possible errors */
    if (errno != 0)
    {
        perror("strtol");
        exit(EXIT_FAILURE);
    }

    if (endPrt == cadena) {
        val = -1;
    }
    return val;
}

//Constructor de comando y destroy de line 
void AddComand(Comand *Comand, NodoComand **start, int undoMax){
    NodoComand *new = malloc(sizeof(NodoComand));
    new->dato = Comand;
    new->next = NULL;

    if (*start == NULL){
        *start = new;
    }
    else{
        new->next = *start;
        *start = new;
    }

    NodoComand *actual = *start;
    int cantidad = 0;
    while(actual != NULL){
        cantidad++;
        if(cantidad > undoMax){
            DestroyComand(actual->next);
            actual->next = NULL;
        }
        else{
            actual = actual->next;
        }
    }
}

void DestroyComand(NodoComand *lines){
    if(lines == NULL){
        return;
    }
    
    if(lines->next != NULL){
        DestroyComand(lines->next);
        lines->next = NULL;
    }

    lines = NULL;
    free(lines);
}

void Destroyline(Nodeline *lines){
    if(lines == NULL){
        return;
    }

    if(lines->next != NULL){
        Destroyline(lines->next);
        lines->next = NULL;
    }

    lines = NULL;
    free(lines);
}

//Constructor del comando 
void Comand_ctor(Comand * const lines, char *_nombre){
    static IOperacionesComand const cptr = {Comand_undo};
    lines->cptr = &cptr;
    memcpy(lines->nombre, _nombre, LENGTH);
}

void Comand_dtor(Comand * const lines){
    free(lines);
}

void Comand_undo(Comand * const lines, Line * archivo){
}

// Constructor de la pokedex
void pokedexCntr(pokedex * const lines, Line LCreada, int posicion, char *_nombre){
    static IOperacionesComand const cptr = {undoPokedex};
    Comand_ctor((Comand *)lines, _nombre);
    lines->EditPokemon.cptr = &cptr;
    lines->pokemonIngresado = LCreada;
    lines->pos = posicion;
}

//Destruir lineas
void destroyPokedex(pokedex * const lines){
    free(lines);
}

//comando undo
void undoPokedex(Comand * const lines, Line * archivo){
    pokedex * const _lines = (pokedex *)lines;
    archivo[_lines->pos].id = 0;
    char cero[20];
    memcpy(archivo[_lines->pos].name, cero, LENGTH);
    memcpy(archivo[_lines->pos].form, cero, LENGTH);
    memcpy(archivo[_lines->pos].type1, cero, LENGTH);
    memcpy(archivo[_lines->pos].type2, cero, LENGTH);
    archivo[_lines->pos].total = 0;
    archivo[_lines->pos].hp = 0;
    archivo[_lines->pos].attack = 0;
    archivo[_lines->pos].defense = 0;
    archivo[_lines->pos].spAtk = 0;
    archivo[_lines->pos].spDef = 0;
    archivo[_lines->pos].speed = 0;
    archivo[_lines->pos].generation = 0;
}

//Constructor edit 
void edit_ctor(edit * const lines, int id, char *stat, char *value, char *_nombre){
    static IOperacionesComand const cptr = {edit_undo};
    Comand_ctor((Comand *)lines, _nombre);
    lines->EditPokemon.cptr = &cptr;
    lines->id = id;
    memcpy(lines->values, stat, LENGTH);
    memcpy(lines->Lastvalue, value, LENGTH);
}

void edit_dtor(edit * const lines){
    free(lines);
}

void edit_undo(Comand * const lines, Line * archivo){
    edit * const _lines = (edit *)lines;
    int SavedLines = NumberConvert(_lines->Lastvalue);
    int posicion;
    for(int i = 0; i < MAX_STATS; i++){
        if(archivo[i].id == _lines->id){
            posicion = i;
        }
    }

    if(strcmp(_lines->values, "name") == 0){
        memcpy(archivo[posicion].name, _lines->Lastvalue, LENGTH);
    }
    else if(strcmp(_lines->values, "form") == 0){
        memcpy(archivo[posicion].form, _lines->Lastvalue, LENGTH);
    }
    else if(strcmp(_lines->values, "type 1") == 0){
        memcpy(archivo[posicion].type1, _lines->Lastvalue, LENGTH);
    }
    else if(strcmp(_lines->values, "type 2") == 0){
        memcpy(archivo[posicion].type2, _lines->Lastvalue, LENGTH);
    }
    else if(strcmp(_lines->values, "total") == 0){
        archivo[posicion].total = SavedLines;
    }
    else if(strcmp(_lines->values, "hp") == 0){
        archivo[posicion].hp = SavedLines;
    }
    else if(strcmp(_lines->values, "attack") == 0){
        archivo[posicion].attack = SavedLines;
    }
    else if(strcmp(_lines->values, "Defese") == 0){
        archivo[posicion].defense = SavedLines;
    }
    else if(strcmp(_lines->values, "Sp.Atk") == 0){
        archivo[posicion].spAtk = SavedLines;
    }
    else if(strcmp(_lines->values, "Sp.Def") == 0){
        archivo[posicion].spDef = SavedLines;
    }
    else if(strcmp(_lines->values, "speed") == 0){
        archivo[posicion].speed = SavedLines;
    }
    else if(strcmp(_lines->values, "generation") == 0){
        archivo[posicion].generation = SavedLines;
    }
}

