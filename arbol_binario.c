#include<stdio.h>
#include<stdlib.h>

struct nodo_arbol{
    int dato;
    int profundidad;
    struct nodo_arbol *hijo_izq;
    struct nodo_arbol *hijo_der;
};

struct nodo_arbol *insertar(struct nodo_arbol *raiz, int dato)
{
    //Insertar cuando no existe ninguna raíz.
    if(raiz == NULL){
        raiz = malloc(sizeof(struct nodo_arbol));
        raiz->dato = dato;
        raiz->hijo_izq = NULL;
        raiz->hijo_der = NULL;
    }
    //insertar a la izquierda de la raiz.
    if(dato < raiz->dato){
        raiz->hijo_izq = insertar(raiz->hijo_izq,dato);
    }
    //insertar a la derecha.
    if (dato > raiz->dato)
    {
        raiz->hijo_der = insertar(raiz->hijo_der,dato);
    }
    return raiz;
};

// Funcion para Buscar el Minimo nodo.
struct nodo_arbol *buscar_min(struct nodo_arbol *raiz){

    if(raiz == NULL)
        return NULL;

    if(raiz->hijo_izq == NULL)
        return raiz;
    else
    {
        return buscar_min(raiz->hijo_izq);
    }
}

//Función para buscar el Máximo nodo
struct nodo_arbol *buscar_max(struct nodo_arbol *raiz){
    if(raiz == NULL)
        return raiz;
    if(raiz ->hijo_der == NULL)
        return raiz;
    else
    {
        return buscar_max(raiz->hijo_der);
    } 
}

struct nodo_arbol *borrar_nodo(struct nodo_arbol *raiz,int dato){

    struct nodo_arbol *aux;

    if(raiz == NULL)
        return NULL;
    
    //El dato que buscamos en menor a la raiz entonces nos movemos a la izquierda.
    if(dato < raiz->dato){
        raiz->hijo_izq = borrar_nodo(raiz->hijo_izq,dato);
    }
    //El dato que buscamos es mayor a la raiz nos movemos a la derecha.
    if (dato > raiz->dato)
    {
        raiz->hijo_der = borrar_nodo(raiz->hijo_der,dato);
    }
    //Si el tado que buscamos es igual a la raiz, entonces revisamos los distintos casos que pueden pasar.
    if(dato == raiz->dato){
        
        //Cuando tenemos que es una Hoja, no tiene hijos izq. e hijo Der. 
        if (raiz->hijo_izq == NULL && raiz->hijo_der == NULL)
        {
            aux = raiz;
            raiz = NULL;
            free(raiz);
        }
        //Cuando tiene un solo hijo Izq. y el hijo Der. es Nulo.
        else if(raiz->hijo_der == NULL){
            printf("\nBorrando Nodo con hijo izquierdo %d",raiz->dato);
            aux = raiz;
            raiz = raiz->hijo_izq;
            free(raiz);
        }
        //Cuanto tiene un solo hijo Der, y ahora el izquierdo es Nulo.
        else if(raiz->hijo_izq == NULL)
        {
            printf("\nBorrando Nodo con hijo derecho %d",raiz->dato);
            aux = raiz;
            raiz = raiz->hijo_der;
            free(raiz);
        }
        //Cuando el Nodo raiz tiene ambos hijos.
        else if(raiz->hijo_izq != NULL && raiz->hijo_der != NULL){

            aux = buscar_min(raiz->hijo_izq);
            raiz->dato = aux->dato;
            borrar_nodo(raiz->hijo_izq,aux->dato);
        }
    }
    return raiz;
}


//función para identificar el tipo de nodo PADRE, HIJO U HOJA.
void identifica_nodo(struct nodo_arbol *raiz){
    if(raiz != NULL){
        if(raiz->hijo_der != NULL && raiz->hijo_izq != NULL)
            printf("\nSoy el nodo %d y soy un nodo con dos hijos.",raiz->dato);
        else if(raiz->hijo_der == NULL && raiz->hijo_izq == NULL)
            printf("\nSoy el nodo %d y soy una hoja.",raiz->dato);
        else if(raiz->hijo_der == NULL)
            printf("\nSoy el nodo %d y tengo un hijo izquierdo.",raiz->dato);
        else if(raiz->hijo_izq == NULL)
            printf("\nSoy el nodo %d y tengo un hijo derecho.",raiz->dato);
        identifica_nodo(raiz->hijo_izq);
        identifica_nodo(raiz->hijo_der);
    }
}

//Funcion para asinar profunfidad;
void asignar_profundidas(struct nodo_arbol *raiz,int profundidad){
    if(raiz != NULL){
        raiz->profundidad = profundidad;
        asignar_profundidas(raiz->hijo_izq,profundidad+1);
        asignar_profundidas(raiz->hijo_der,profundidad+1);
    }
}


//FUNCIONES PARA IMPRIMIR 

void preorden(struct nodo_arbol *raiz,int profundad){
    if(raiz == NULL)
        return;
    for(int i = 0; i < profundad ;i++){
        printf("|--");
    } 
    profundad++;
    printf("%d\n",raiz->dato);
    preorden(raiz->hijo_izq,profundad);
    preorden(raiz->hijo_der,profundad);
}


void inorden(struct nodo_arbol *raiz){
    if (raiz == NULL)
    {
        return;
    }
    inorden(raiz->hijo_izq);
    printf("(%d)->",raiz->dato);
    inorden(raiz->hijo_der);
}

void posorden(struct nodo_arbol *raiz){
    if(raiz == NULL)
        return;
    posorden(raiz->hijo_izq);
    posorden(raiz->hijo_der);
    printf("(%d)->",raiz->dato);
}

int main(int argc, char const *argv[])
{
    struct nodo_arbol *raiz, *nodo_min, *nodo_max;
    int profundidad;
    raiz = NULL;
    nodo_min = NULL;
    raiz = insertar(raiz,6);
    raiz = insertar(raiz,4);
    raiz = insertar(raiz,7);
    raiz = insertar(raiz,3);
    raiz = insertar(raiz,5);
   
    printf("Imprimiendo datos en PREORDEN\n");
    preorden(raiz,0);
    
    
    
    identifica_nodo(raiz);
    asignar_profundidas(raiz,0);


    // nodo_min = buscar_min(raiz);
    // printf("\nEl Nodo Menor es %d",*nodo_min);
    // nodo_max = buscar_max(raiz);
    // printf("\nEl Nodo Mayor es %d\n",*nodo_max);

    // raiz = borrar_nodo(raiz,6);
    // preorden(raiz);

    // printf("\nImprimiendo datos en INORDEN\n");
    // inorden(raiz);
    // printf("\nImprimiendo datos en POSORDEN\n");
    // posorden(raiz);

    return 0;
}
