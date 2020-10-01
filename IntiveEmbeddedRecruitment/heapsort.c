#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*  compare arguments at Idx x,y
    returns int: <0 when x < y; >0 when x > y; =0 when x = y    */
#define comp(x,y) cmp(basePtr + (x) * pointerInc, basePtr + (y) * pointerInc)

/*  swap arguments at Idx x,y  */
#define swap(x,y) swapFnc(basePtr, nmemb, pointerInc, (x), (y), size)

/*  heapifyFnc, x - Idx of Node to start heapify  */
#define heapify(x) heapifyFnc(basePtr, nmemb, pointerInc, (x), size, cmp);

/*  Idx of left and right child of Node [i] */
#define LCH (2*i+1)
#define RCH (2*i+2)

typedef int (*cmp_t)(const void *a, const void *b);

void swapFnc(char *basePtr, size_t nmemb, size_t pointerInc, 
            size_t a, size_t b, size_t size)
{
    int i = 0;
    char temp[1];
    
    if (a >= nmemb || b >= nmemb)
        return;
    
    else {
        for (i = 0; i < size; i++) {
            *temp = *(basePtr + a * pointerInc + i);
            *(basePtr + a * pointerInc + i) = *(basePtr + b * pointerInc + i);
            *(basePtr + b * pointerInc + i) = *temp;
        }
    }
}

void heapifyFnc(char *basePtr, size_t nmemb, size_t pointerInc, 
                size_t i, size_t size, cmp_t cmp)
{
    size_t largestNod = i;

    /* infinite loop for heapify */
    while (1) {
        
        /*  compare values at parrent (i) with left and right child (LCH, RCH)
        returns Idx of largest Node and put at var largestNod  */
        if (LCH < nmemb && (comp(LCH,i)) > 0)
            largestNod = LCH;

        if (RCH < nmemb && (comp(RCH,largestNod)) > 0)
            largestNod = RCH;

        /*  if largest node NOT at [i]
            --> swap and continue while loop with i = largestNod
            else heapify complete (return) */
        if (largestNod != i) 
            swap(i,largestNod); 
        else
            return;

        i = largestNod;
    }
    
}

void heapsort(void *base, size_t nmemb, size_t size, cmp_t cmp)
{
    const size_t pointerInc = size / sizeof(char);
    char *basePtr = base;

    /* BuildHeap (shift down) */
    int i = (nmemb - 2) / 2;

    while (i >= 0)
        heapify(i--);

    /* Sort */
    while (nmemb > 1) {
        swap(0,nmemb - 1);
        nmemb--;
        heapify(0);
    }
}

int cmp_int(const void *a, const void *b)
{
    if (*(int *)a < *(int *)b)
        return -1;

    else if (*(int *)a > *(int *)b)
        return 1;

    else
        return 0;
}

int cmp_str(const void *a, const void *b)
{
    return strcmp(*(const char **)a, *(const char **)b);
}

int main(void)
{
    int A[] = {5, 8, 2, 11, 3, 7, 9, 12};
    char *B[] = { "Jacek", "Maria", "Szymon", "Zosia",
        "Adam", "Gosia", "Bonawentura", "Kunegunda" };

    int i;

    heapsort(A, 8, sizeof(*A), cmp_int);
    heapsort(B, 8, sizeof(*B), cmp_str);

    for (i = 0; i < 8; i++)
        printf("%d%c", A[i], (i == 7) ? '\n' : ' ');

    for (i = 0; i < 8; i++)
        printf("%s%c", B[i], (i == 7) ? '\n' : ' ');

    return 0;
}
