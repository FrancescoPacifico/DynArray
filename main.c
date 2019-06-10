#include "dynArray.h"

struct dynArray newDynArray(void);
struct dynArray appendLast(struct dynArray, int);
struct dynArray popLast(struct dynArray);
struct dynArray append(struct dynArray, int, int);
struct dynArray pop(struct dynArray, int);
void printDynArray(struct dynArray);

int main() {
    struct dynArray dynamic_array = newDynArray();
    int i;
    for(i = 0; i < 13; i++) {
        dynamic_array = appendLast(dynamic_array, i);
    }
    printDynArray(dynamic_array);
    printf("\n\n//////////////////////////////\n\n");
    dynamic_array = append(dynamic_array, 0, 99);
    printDynArray(dynamic_array);
    printf("\n\n//////////////////////////////\n\n");
    dynamic_array = pop(dynamic_array, dynamic_array.n - 1);
    printDynArray(dynamic_array);
    return 0;
}