#include "SqList.h"
#include <stdio.h>
#include <stdlib.h>

Status InitList(SqList* L) {
    L->head = (ElemType*)malloc(LIST_INIT_SIZE * sizeof(ElemType));
    L->listsize = LIST_INIT_SIZE * sizeof(ElemType);
    L->length = 0;
    if (L->head) {
        return OK;
    }
    else {
        return ERROR;
    }
}

Status GetElem(SqList L, int i, ElemType* e) {
    if (i >= 1 && i <= L.length) {
        *e = L.head[i - 1];
        return OK;
    }
    else {
        return ERROR;
    }
}

Status compare(ElemType a, ElemType b) {
    if (a == b) {
        return TRUE;
    }
    else {
        return FALSE;
    }
}

int LocateElem(SqList L, ElemType e, Status compare(ElemType a, ElemType b)) {
    if (!L.head) {
        return ERROR;
    }
    else {
        for (int i = 0; i < L.length; i++) {
            if (compare(L.head[i], e)) {
                return i + 1;
            }
        }
        return ERROR;
    }
}

Status TraverseList(const SqList L) {
    for (int i = 0; i < L.length; i++) {
        printf("%d ", L.head[i]);
    }
    printf("\n\n");
    return OK;
}

Status ListInsert(SqList* L, int i, ElemType e) {
    if (!L->head) {
        return ERROR;
    }
    else {
        if (i <= 0) {
            return ERROR;
        }
        else if (L->length >= (L->listsize / sizeof(ElemType))) {
            ElemType* newbase = (ElemType*)realloc(L->head, (L->length + LIST_INCREASE_SIZE) * sizeof(ElemType));
            if (newbase) {
                L->head = newbase;
            }
            else {
                return OVERFLOW;
            }
        }
        int tmp;
        for (int index = i - 1; index < L->length; index++) {
            tmp = L->head[index + 1];
            L->head[index + 1] = L->head[index];
        }
        L->head[i - 1] = e;
        L->length++;
        return OK;
    }
}

Status ListIntersaction(SqList La, SqList Lb, SqList* Lc) {
    Lc->length = 0;
    for (int i = 0; i < La.length; i++) {
        if (LocateElem(Lb, La.head[i], compare) && !LocateElem(*Lc, La.head[i], compare)) {
            ListInsert(Lc, i + 1, La.head[i]);
        }
    }
    return OK;
}

Status DestoryList(SqList* L) {
    free(L->head);
    L->listsize = 0;
    L->length = 0;
    L = NULL;
    return OK;
}

void MergeList(SqList* La, SqList* Lb,SqList *Lc) {
    ElemType a; ElemType b; 
    int ia = 1, ib = 1, ic = 1;
    printf("\n");
    while (ia <= La->length && ib <= Lb->length) {
        GetElem(*La, ia, &a); GetElem(*Lb, ib, &b);
        if (a < b) {
            ListInsert(Lc, ic, a); ic++; ia++;
        }
        else {
            ListInsert(Lc, ic, b); ic++; ib++;
        }

    }
    if (ia > La->length) {
        while (ib <= Lb->length) {
            GetElem(*Lb, ib, &b);
            ListInsert(Lc, ic, b); ic++; ib++;
        }
    }
    if (ib > Lb->length) {
        while (ia <= La->length) {
            GetElem(*La, ia, &a);
            ListInsert(Lc, ic, a); ic++; ia++;
        }
    }
}

Status DestoryElem(SqList* L, int index, ElemType* e) {
    TraverseList(*L);
    *e = L->head[index - 1];
    int i = index - 1;
    while (i < L->length - 1) {
        L->head[i] = L->head[i + 1];
        i++;
    }
    L->length--;
    return OK;
}

int main(void) {
    SqList* L = (SqList*)malloc(LIST_INIT_SIZE * sizeof(ElemType));// pointer should be init before first use.
    printf("after Init ,the return : %d .\n", InitList(L));
    printf("the length of list: %d .\t the listsize of list %d .\n", L->length, L->listsize);
    printf("the ptr of list head is %p.\n", L->head);
    L->head[0] = 1; L->head[1] = 2; L->length = 2;
    ElemType e;
    int returnvalue = GetElem(*L, 2, &e);
    printf("\nafter GetElem , the return value is %d.\n", returnvalue);
    printf("the value should be 1. and it is %d exactly.\n", e);
    returnvalue = LocateElem(*L, e, compare);
    printf("%d is in %d place.\n", e, returnvalue);
    TraverseList(*L);
    printf("\n\n");
    e = 3;
    returnvalue = ListInsert(L, 2, e);
    returnvalue = ListInsert(L, 2, e);
    printf("\nLa is ");
    TraverseList(*L);
    printf("\n");
    SqList* Lb = (SqList*)malloc(LIST_INIT_SIZE * sizeof(ElemType));// pointer should be init before first use.
    InitList(Lb);
    Lb->head[0] = 1; Lb->head[1] = 2; Lb->head[2] = 3; Lb->length = 3;
    SqList* Lc = (SqList*)malloc(LIST_INIT_SIZE * sizeof(ElemType));// pointer should be init before first use.
    InitList(Lc);
    Lc->length = 10;
    ListIntersaction(*L, *Lb, Lc);
    printf("Lb is :");
    TraverseList(*Lb);
    printf("\n\nfinally after ListIntersaction , Lc is :");
    TraverseList(*Lc);
    DestoryList(L); DestoryList(Lb); DestoryList(Lc);

    // test for mergeList
    SqList* Laa; SqList* Lbb; SqList* Lcc;
    Laa = (SqList*)malloc(LIST_INIT_SIZE * sizeof(ElemType));
    Lbb = (SqList*)malloc(LIST_INIT_SIZE * sizeof(ElemType));
    Lcc = (SqList*)malloc(LIST_INIT_SIZE * sizeof(ElemType));

    InitList(Laa); InitList(Lbb); InitList(Lcc);
    Laa->head[0] = 1; Laa->head[1] = 2; Laa->head[2] = 3; Laa->length = 3;
    Lbb->head[0] = 4; Lbb->head[1] = 5; Lbb->length = 2;
    MergeList(Laa, Lbb,Lcc);
    TraverseList(*Lcc);
    ElemType t4d;
    DestoryElem(Lcc, 2, &t4d);
    TraverseList(*Lcc);
    return 0;
}