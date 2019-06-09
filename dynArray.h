#include <stdio.h>
#include <stdlib.h>

/* ENG:
 * A Dynamic Array is a simple data structure that improves the normal arrays. Normal arrays are not considered dynamic because you must alloc
 * a certain amount of memory when you declare them and there is no way to increase or decrease this space when needed.
 * The only way to do it is to create a new array with a bigger dimension and copy every element of the old one inside it.
 * We'll create a structure that exploits this operation, but in an smart way.
 * A Dynamic Array is made of a normal array and two integers:
 * -c: is the number of cells of the array
 * -n: is the number of the first free cell in the array
 * ITA:
 * Un Array Dinamico è una semplice struttura dati che migliora i normali array. Gli array normali non sono considerati dinamici perchè devi allocare una certa quantità
 * di memoria quando li dichiari e non c'è modo di incrementarla o decrementarla quando serve.
 * L'unico modo per farlo è creare un nuovo array di dimensione maggiore e copiare ogni elemento del vecchio array in esso.
 * Creeremo una struttura che sfrutta questa operazione, ma in maniera intelligente.
 * Un Array Dinamico è fatto da un normale array e due interi:
 * -c: è il numero di celle dell'array
 * -n: è il numero della prima cella libera nell'array 
 */

struct dynArray {
    int *array;
    int c, n;
};

struct dynArray newDynArray(void);
struct dynArray appendLast(struct dynArray, int);
struct dynArray popLast(struct dynArray);
struct dynArray append(struct dynArray, int, int);
struct dynArray pop(struct dynArray, int);
void printDynArray(struct dynArray);

/* ENG:
 * This is a simple function that return a void Dynamic Array.
 * ITA:
 * Questa è una semplice funzione che restituisce un Array Dinamico vuoto.
 */

struct dynArray newDynArray(void) {
    struct dynArray out;
    out.array = NULL, out.c = out.n = 0;
    return out;
}

/* ENG:
 * The function below appends the value 'v' to the first available index in the Dynamic Array.
 * If there's no space left the realloc function from the stdlib header is called to extend the array.
 * Because it can be a quite expensive function we always double the dimension. In this way, the Dynamic Array can store
 * more integers before it's needed to call the realloc function again.
 * ITA:
 * La funzione qui sotto aggiunge il valore 'v' al primo indice libero nell'Array Dinamico.
 * Se non c'è spazio residuo viene chiamata la funzione realloc dell'intestazione stdlib per estendere l'array.
 * Poichè può essere abbastanza costosa come funzione, ogni volta raddoppiamo la dimensione. In questo modo, l'Array Dinamico può
 * immagazzinare più interi prima che ci sia bisogno di chiamare nuovamente la funzione realloc.
 */

struct dynArray appendLast(struct dynArray a, int v) {
    if(a.n >= a.c) {
        a.array = realloc(a.array, sizeof(int) * (a.c * 2 + 1));
        a.c = a.c * 2 + 1;
    }
    a.array[a.n++] = v;
    return a;
}

/* ENG:
 * This is a function to delete the last integer of a Dynamic Array.
 * In order to work, there must be at least one item in the array, so that's the first thing we verify.
 * When we pop an item from the array we always check that the number of elements is not less than a quarter of the total number of
 * available cells. We don't want this to happen, because it would be a waste of memory; so, every time that we reach that condition we halve
 * the array dimension.
 * ITA:
 * Questa è una funzione per eliminare l'ultimo intero di un Array Dinamico.
 * Per funzionare, deve esserci almeno un elemento nell'array, dunque questa è la prima cosa che verifichiamo.
 * Quando eliminiamo un elemento dall'array controlliamo sempre che il numero di elementi non sia inferiore di un quarto del numero totale delle celle
 * dispoinibili. Non vogliamo che ciò accada, perchè sarebbe uno spreco di memoria; dunque, ogni volta che raggiungiamo tale condizione dimezziamo
 * la dimensione dell'array.
 */

struct dynArray popLast(struct dynArray a) {
    if(a.n != 0) {
        a.n--;
        if(a.n <= a.c / 4) {
            a.array = realloc(a.array, sizeof(int) * (a.c / 2));
            a.c /= 2;
        }
    }
    return a;
}

/* ENG:
 * This function appends an element in any of the already used indexes of the array (0 <= i <= n).
 * To do this, we first append the element in the first position available, then we move it to the desired index with a for cycle.
 * This keeps the same order of the elements in the array.
 * ITA:
 * Questa funzione aggiunge un elemento in uno degli indici già utilizzati dell'array (0 <= i <= n).
 * Per fare ciò, prima aggiungiamo un elemento nella prima posizione disponibile, poi lo muoviamo all'indice desiderato con un ciclo for.
 * Ciò mantiene inalterato l'ordine degli elementi dell'array.
 */

struct dynArray append(struct dynArray a, int i, int v) {
    int j, temp;
    if(i >= 0 && i <= a.n) {
        a = appendLast(a, v);
        for(j = a.n - 1; j > i; j--) {
            temp = a.array[j];
            a.array[j] = a.array[j - 1];
            a.array[j - 1] = temp;
        }
    }
    return a;
}

/* ENG:
 * This function pops an element from one of the already used indexes of the array (0 <= i <= n).
 * To do this, we first move the desired element to the end of the array with a for cycle, then we call the popLast function to pop it.
 * This keeps the same order of the elements in the array.
 * ITA:
 * Questa funzione elimina un elemento da uno degli inidici già utilizzati dell'array (0 <= i <= n).
 * Per fare ciò, prima muoviamo l'elemento desiderato alla fine dell'array con un ciclo for, poi chiamiamo la funzione popLast per eliminarlo.
 * Ciò mantiene inalterato l'ordine degli elementi dell'array.
 */

struct dynArray pop(struct dynArray a, int i) {
    int j, temp;
    if(i < a.n && i >= 0) {
        for(j = i; j < a.n - 1; j++) {
            temp = a.array[j];
            a.array[j] = a.array[j + 1];
            a.array[j + 1] = temp;
        }
        a = popLast(a);
    }
    return a;
}

/* ENG:
 * This simple function prints all the elements of a Dynamic Array by scrolling them.
 * ITA:
 * Questa semplice funzione stampa tutti gli elementi di un Array Dinamico scorrendoli.
 */

void printDynArray(struct dynArray a) {
    int i;
    for(i = 0; i < a.n; i++) {
        printf("%d\n", a.array[i]);
    }
}

/* ENG:
 * Calculating the costs of these functions is easy.
 * To append an element to the last index of the array needs constant time, but if there's no space left, a new array must be created, and
 * in the worst case 'n' operations are needed to copy all the content of the old array in the new one ('n' is the number of elements of the array).
 * The same thing applies to the popLast function when a smaller array is created.
 * The cost of the append and pop functions is linear in the dimension of the input in the worst case.
 * In fact, in both the functions we move the desired element to a specific index or to the last index, and in the worst case the length of this gap is 'n'.
 * The cost of the printDynArray function is simply calculable, because it needs to scroll every element of the array, so it needs to do 'n' iterations.
 * ITA:
 * Calcolare il costo di queste funzioni è semplice.
 * Per aggiungere un elemento all'ultimo indice dell'array richiede tempo costante, ma se non c'è spazio rimanente, deve essere creato un nuovo array, e
 * nel caso peggiore devono essere svolte 'n' operazione per copiare tutto il contenuto del vecchio array in quello nuovo ('n' è il numero di elementi dell'array).
 * La stessa cosa si applica alla funzione popLast quando viene creato un array più piccolo.
 * Il coso delle funzioni append e pop è lineare nella dimensione dell'input nel caso peggiore.
 * Infatti, in entrambe le funzioni muoviamo l'elemento desiderato ad un indice specifico o all'ultimo indice, e nel caso peggiore la lunghezza di questo intervallo è 'n'.
 * Il costo della funzione printDynArray è facilmente calcolabile, perchè deve scorrere ogni elemento dell'array, dunque impiega 'n' iterazioni.
 */