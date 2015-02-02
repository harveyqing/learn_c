#include <stdio.h>
#include <stdlib.h>

#define STACK_MAX 256

typedef enum {
    OBJ_INT,
    OBJ_PAIR
} ObjectType;

typedef struct sObject {
    /* the next object in the list of all objects. */
    struct sObject* next;
    unsigned char marked;
    ObjectType type;

    union {
        /* OBJ_INT */
        int value;

        /* OBJ_PAIR */
        struct {
            struct sObject* head;
            struct sObject* tail;
        };
    };
} Object;

typedef struct {
    /* The total number of currently mallocated objects. */
    int numObjects;

    /* The number of objects required to trigger a GC. */
    int maxObjects;

    /* The first object in the list of all objects. */
    Object* firstObject;
    Object* stack[STACK_MAX];
    int stackSize;
} VM;

void mark(Object* object)
{
    /* If already marked, we're done. Check this first
     * to avoid recursing on cycles in the object graph.
     */
    if (object->marked) return;

    object->marked = 1;

    if (object->type == OBJ_PAIR) {
        mark(object->head);
        mark(object->tail);
    }
}

void sweep(VM* vm)
{
    Object** object = &vm->firstObject;
    while (*object) {
        if (!(*object)->marked) {
            /* This object wasn't reached, so remove it from the list 
             * and free it.
             */
            Object* unreached = *object;

            *object = unreached->next;
            free(unreached);

            vm->numObjects--;
        } else {
            /* This object was reached, so unmark it (for the next GC)
             * and move on to the next.
             */
            (*object)->marked = 0;
            object = &(*object)->next;
        }
    }
}

void markAll(VM* vm)
{
    for (int i = 0; i < vm->stackSize; i++) {
        mark(vm->stack[i]);
    }
}

/* 对于vm栈中对象，其均被标记且都可达
 * 那些开始在栈中（该演示中所有对象
 */
void gc(VM* vm)
{
    int numObjects = vm->numObjects;

    markAll(vm);
    sweep(vm);

    vm->maxObjects = vm->numObjects * 2;

    printf("Collected %d objects, %d remaining.\n", \
            numObjects - vm->numObjects, vm->numObjects);
}

void assert(int condition, const char* message)
{
    if (!condition) {
        printf("%s\n", message);
        exit(1);
    }
}

VM* newVM() {
    VM* vm = (VM*)malloc(sizeof(VM));
    vm->stackSize = 0;
    vm->firstObject = NULL;
    vm->numObjects = 0;
    vm->maxObjects = 8;
    return vm;
}

void push(VM* vm, Object* value) {
    assert(vm->stackSize < STACK_MAX, "Stack overflow!");
    vm->stack[vm->stackSize++] = value;
}

Object* pop(VM* vm) {
    assert(vm->stackSize > 0, "Stack underflow!");
    return vm->stack[vm->stackSize--];
}

Object* newObject(VM* vm, ObjectType type)
{
    if (vm->numObjects == vm->maxObjects) gc(vm);

    Object* object = (Object*) malloc(sizeof(Object));
    object->type = type;
    object->marked = 0;

    /* Insert it into the list of mallocated objects. */
    object->next = vm->firstObject;
    vm->firstObject = object;
    vm->numObjects++;

    return object;
}

void pushInt(VM* vm, int intValue)
{
    Object* object = newObject(vm, OBJ_INT);
    object->value = intValue;
    push(vm, object);
}

Object* pushPair(VM* vm)
{
    Object* object = newObject(vm, OBJ_PAIR);
    object->tail = pop(vm);
    object->head = pop(vm);

    push(vm, object);
    return object;
}

void objectPrint(Object* object)
{
    switch (object->type) {
        case OBJ_INT:
            printf("%d", object->value);
            break;

        case OBJ_PAIR:
            printf("(");
            objectPrint(object->head);
            printf(", ");
            objectPrint(object->tail);
            printf(")");
            break;
    }
}

void freeVM(VM *vm)
{
    vm->stackSize = 0;
    gc(vm);
    free(vm);
}

void test1()
{
    printf("Test 1: Objects on stack are preserved.\n");
    VM* vm = newVM();
    pushInt(vm, 1);
    pushInt(vm, 2);

    gc(vm);
    assert(vm->numObjects == 2, "Should have preserved objects.");
    freeVM(vm);
}

void test2()
{
    printf("Test 2: Unreached objects are collected.\n");
    VM* vm = newVM();
    pushInt(vm, 1);
    pushInt(vm, 2);
    pop(vm);
    pop(vm);

    gc(vm);
    assert(vm->numObjects == 0, "Should have collected objects.");
    pushInt(vm, 3);
    pushInt(vm, 4);
    pushInt(vm, 5);
    pop(vm);
    pop(vm);
    gc(vm);
    assert(vm->numObjects == 1, "Should have collected objects.");
    printf("\nhello %d", vm->firstObject->value);
    freeVM(vm);
}

int main()
{
    test1();
    test2();

    getchar();
    return 0;
}
