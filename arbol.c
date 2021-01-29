/************************************************************************\
* Programa: arbol.c                                                      *
* Descripción: Programa con defición de un árbol binario con sus         * 
*              principales funciones que son insertar, buscar Minimo,    *
*              buscar Máximo, borrar un nodo, actualiza y borrar nodo    *
* Autor: Molina Vásquez Luis Alberto                                     *
* Revisión: 1.0 19/10/2020                                               *
\************************************************************************/


#include<stdlib.h>
#include<stdio.h>

struct Arbol_binario{
    int dato;
    int profundidad;
    int altura;
    struct Arbol_binario *h_izquierdo;
    struct Arbol_binario *h_derecho;
};


struct Arbol_binario *inserta(struct Arbol_binario *raiz, int dato){

    if (raiz == NULL)
    {
        raiz = (struct Arbol_binario*)malloc(sizeof(struct Arbol_binario));
        raiz->dato =  dato;
        raiz->h_izquierdo = NULL;
        raiz->h_derecho = NULL;
        raiz->profundidad = 0;
    }else
    {
        if(dato < raiz->dato){
            raiz->h_izquierdo = inserta(raiz->h_izquierdo,dato);
            raiz->profundidad++;
        }
        else if(dato > raiz->dato)
        {
            raiz->h_derecho = inserta(raiz->h_derecho,dato);
            raiz->profundidad++;
        }
        return raiz;
    }
}


/*  En este metodo insertamos de forma recursiva notamos que son menos lineas de codigo que de la 
    forma iterativa. Entra en la concición donde dice que si en nula la raiz agrega de lo contrario 
    sigue comparando el dato con los demas valores MENOR o MAYOR hasta encontrar un subArbol vacio.*/
struct Arbol_binario *InserarRecursivo(struct Arbol_binario *raiz,int dato){

    if(raiz == NULL){
        struct Arbol_binario *nuevoNodo = (struct Arbol_binario*)malloc(sizeof(struct Arbol_binario));
        raiz = nuevoNodo;
        raiz->dato =  dato;
        raiz->h_izquierdo = NULL;
        raiz->h_derecho = NULL;
    }
    else if(dato < raiz->dato)
        raiz->h_izquierdo = InserarRecursivo(raiz->h_izquierdo,dato);
    else if(dato > raiz->dato)
        raiz->h_derecho = InserarRecursivo(raiz->h_derecho,dato);
    return raiz;
}

/*  Si raiz esta vacia devolvemos NULL si el hijo izquierdo es NULL no hay datos menores recordar
    que los números menos estan de lado izquierdo por último si existe un hijo izquierdo entonces
    llama recursivamente para encontrar el minimo. */
struct Arbol_binario *buscar_Minimo(struct Arbol_binario *raiz){
    
    if(raiz == NULL)
        return NULL;
    else if(raiz->h_derecho == NULL)
        return raiz;
    else{
        return buscar_Minimo(raiz->h_izquierdo);
    }
}

/*  Si en la raiz es nula indica que no existen datos en, por otra parte si el hijo derecho es nulo 
    quiere decir que no tiene ningun hijo derecho más entonces deja buscar, de lo contrario llama 
    llama recursivamente hasta en contrar su ultimo hijo derecho.*/
struct Arbol_binario *buscar_Maximo(struct Arbol_binario *raiz){
   
    if(raiz == NULL)
        return NULL;
    else if(raiz->h_derecho == NULL)    
        return raiz;
    else
        return buscar_Maximo(raiz->h_derecho);
}


/* En este caso revisamos cada uno de los nodos si es menor se mueve a la izquierda si es mayor a la
   derecha, hasta encontrar el nodo que sea igual al dato a borrar, cuando encuentre el dato entonces 
   revisamos cada uno de los casos 1. Si es una hoja, 2. Si es el nodo tiene solo un hijo izquierdo o 
   derecho y por ultimo si es tiene ambos hijos.*/
struct Arbol_binario *borrar_nodo(struct Arbol_binario *raiz, int borrar_dato){
    struct Arbol_binario *aux;
    if (raiz==NULL)
        return NULL;
    else if(borrar_dato < raiz->dato){
        raiz->h_izquierdo = borrar_nodo(raiz->h_izquierdo,borrar_dato);
    }
    else if(borrar_dato > raiz->dato){
        raiz->h_derecho = borrar_nodo(raiz->h_derecho,borrar_dato);
    }
    else if(borrar_dato == raiz->dato){
        if(raiz->h_izquierdo == NULL && raiz->h_derecho == NULL){
            raiz->profundidad--;
            aux = raiz;
            raiz = NULL;
            free(raiz);
        } 
        else if(raiz->h_izquierdo == NULL){
            raiz->profundidad--;
            aux = raiz;
            raiz = raiz->h_derecho;
            free(aux);
        }
        else if(raiz->h_derecho == NULL){
            raiz->profundidad--;
            aux = raiz;
            raiz = raiz->h_izquierdo;
            free(aux);
        }
        else if(raiz->h_izquierdo != NULL && raiz->h_derecho != NULL){
            raiz->profundidad--;
            aux = buscar_Minimo(raiz->h_izquierdo);
            raiz->dato = aux->dato;
            borrar_nodo(raiz->h_derecho,borrar_dato);
        }
    }
    return raiz;
}

/*  Este metodo al elimina un dato en especial de forma recursiva al con menos lienas de cogido 
    revisa que el dato sea MENOR o MAYOR, dependiendo el caso se mueve hacia la izquierda o a la 
    derecha una vez que llega al dato revisa que caso es si es: 1) Hoja 2) Tiene un hijo Izquierdo 
    3) Tiene un Hijo Derecho y 4) Si tiene ambos hijos.
*/
struct Arbol_binario *borrar_Recursivo(struct Arbol_binario *raiz,int BorrarDato){
    struct Arbol_binario *aux;
    if(raiz == NULL)    
        return NULL;
    else if(BorrarDato < raiz->dato)  
        raiz->h_izquierdo = borrar_Recursivo(raiz->h_izquierdo,BorrarDato);
    else if(BorrarDato > raiz->dato)
        raiz->h_derecho = borrar_Recursivo(raiz->h_derecho,BorrarDato);
    else if(BorrarDato == raiz->dato){
        if(raiz->h_izquierdo == NULL && raiz->h_derecho == NULL)
            raiz = NULL;
        else if(raiz->h_derecho == NULL)
            raiz = raiz->h_izquierdo;
        else if(raiz->h_izquierdo == NULL)
            raiz = raiz->h_derecho;
        else if(raiz->h_izquierdo != NULL && raiz->h_derecho != NULL){
            aux = buscar_Minimo(raiz->h_derecho);
            raiz->dato = aux->dato;
            borrar_Recursivo(raiz->h_derecho,BorrarDato);
        }
    }
    return raiz;
}

/*  Este metodo busca y actualiza el dato recibe como parametro la raiz, el dato que va a sustituir 
    al dato existente y el dato a buscar y ser cambiado. Todo esto de forma recursiva.
*/
struct Arbol_binario *actualizar_Recursivo(struct Arbol_binario *raiz, int Actualizardato, int CambiarDato){
    if(raiz == NULL)
        return NULL;
    else if(CambiarDato < raiz->dato)
        raiz->h_izquierdo = actualizar_Recursivo(raiz->h_izquierdo,Actualizardato,CambiarDato);
    else if(CambiarDato > raiz->dato)
        raiz->h_derecho = actualizar_Recursivo(raiz->h_derecho,Actualizardato,CambiarDato);
    else if(CambiarDato == raiz->dato)
        raiz->dato = Actualizardato;
    return raiz;
}
/*  Este metodo busca dentro del arbol el dato si existe muestra el valor de lo contrario solo
    manda un mensaje que no existe el dato.
*/
void buscar_Dato(struct Arbol_binario *raiz,int BuscarDato){
    if(raiz == NULL)
        printf("\nNO Existe el dato en el Arbol");
    else if(BuscarDato < raiz->dato)
        buscar_Dato(raiz->h_izquierdo,BuscarDato);
    else if(BuscarDato > raiz->dato)
        buscar_Dato(raiz->h_derecho,BuscarDato);
    else if(BuscarDato == raiz->dato)
        printf("El DATO BUSCADO ES : %d",raiz->dato);
}

//Comparamos la altura de ambos lados izquierdo y derecho. El mayor sera 
//retornado, iniciando desde el ultimo nodo recursivamente sube sumando 1
//cada que avanza hacia la raíz.
int encuentra_altura(struct Arbol_binario *raiz){
    int altura_izq=0, altura_der=0;
    if(raiz == NULL)    
        return -1;
    else{
        altura_izq = encuentra_altura(raiz->h_izquierdo)+1;
        altura_der = encuentra_altura(raiz->h_derecho)+1;
        if(altura_izq > altura_der)
            return raiz->altura = altura_izq;
        else    
            return raiz->altura = altura_der;
    }
}

//Función para sumar los nodos recursivamente.
int sumar_nodos(struct Arbol_binario *raiz){
    int suma = 0;
    if(raiz == NULL){
        return 0;
    }
    else{
        suma = sumar_nodos(raiz->h_izquierdo)+sumar_nodos(raiz->h_derecho)+raiz->dato;
        return suma;
    }
}

void imprimir_preorden(struct Arbol_binario *raiz, int profundidad){
    if(raiz == NULL){
        return;
    }
    else {
        for(int i = 0;  i < profundidad; i++){
            printf("|-");
        }
        profundidad++;
            printf(" %d\n",raiz->dato);
            imprimir_preorden(raiz->h_izquierdo,profundidad);
            imprimir_preorden(raiz->h_derecho,profundidad);
    }
}

void imprimir_Inorden(struct Arbol_binario *raiz, int profundidad){
    if(raiz == NULL){
        return;
    }
    else {
        for(int i = 0;  i < profundidad; i++){
            printf("|-");
        }
        profundidad++;
            imprimir_preorden(raiz->h_izquierdo,profundidad);
            printf(" %d\n",raiz->dato);
            imprimir_preorden(raiz->h_derecho,profundidad);
    }
}

void imprimir_Posorden(struct Arbol_binario *raiz, int profundidad){
    if(raiz == NULL){
        return;
    }
    else {
        for(int i = 0;  i < profundidad; i++){
            printf("|-");
        }
        profundidad++;
            imprimir_preorden(raiz->h_izquierdo,profundidad);
            imprimir_preorden(raiz->h_derecho,profundidad);
            printf(" %d\n",raiz->dato);
    }
}



int main(int argc, char const *argv[])
{
    struct Arbol_binario *raiz,*minimo,*maximo;
    raiz = NULL;
    int suma;
    raiz = inserta(raiz,1);
    raiz = inserta(raiz,2);
    raiz = inserta(raiz,-2);
    raiz = inserta(raiz,7);
    raiz = inserta(raiz,4);
    raiz = inserta(raiz,3);
    raiz = InserarRecursivo(raiz,-11);
    imprimir_preorden(raiz,0);
    printf("\nLista despues de borrar\n");
    raiz = borrar_Recursivo(raiz,3);
    raiz = actualizar_Recursivo(raiz,10,-2);
    imprimir_preorden(raiz,0);
    buscar_Dato(raiz,400);
   /*
    encuentra_altura(raiz);
    printf("\nLa altura es: %d",raiz->altura);
    
    printf("\nProfundidad: %d",raiz->profundidad);
   
    suma = sumar_nodos(raiz);
    printf("\nLa suma es de todos los nodos: %d",suma);

    minimo = buscar_Minimo(raiz);
    printf("\nEl nodo Menor es: %d",minimo->dato);
    */
    maximo = buscar_Maximo(raiz);
    printf("\nEl nodo Mayor es: %d",maximo->dato);
    
    return 0;
}
