#include <stdio.h>
#include <stdlib.h>

typedef struct List List;
struct List{
  int key;
  List* next;
};
void include(List** pointer, List* list){
  list->next = *pointer;
  *pointer = list;
}
List* exclude(List** list){
  List* aux = *list;
  *list = aux->next;
  return aux;
}
List** min(List** list1, List** list2){
  return (*list1)->key<(*list2)->key ? list1 : list2;
}
List** searchMin(List** list, List** aux){
  return *list==NULL ? aux : searchMin(&(*list)->next, min(list, aux));
}
void selectionSort(List** list){
  if(*list!=NULL && (*list)->next!=NULL){
    include(list, exclude(searchMin(list, list)));
    selectionSort(&(*list)->next);
  }
}
List* allocate(int key){
  List* list = (List*)calloc(1, sizeof(List));
  if(list!=NULL)
    list->key = key;
  return list;
}
void insert(List** list, int key){
  if(*list==NULL)
    include(list, allocate(key));
  else
    insert(&(*list)->next, key);
}
void print(List* list){
  if(list!=NULL){
    printf("%d ", list->key);
    print(list->next);
  }else
    printf("\n");
}
List* keysToList(char* keys[], int num){
  List* list = NULL;
  for(int i=0; i<num; i++)
    insert(&list, atoi(keys[i]));
  return list;
}
void deleteAll(List* list){
  if(list!=NULL){
    deleteAll(list->next);
    free(list);
  }
}
int main(int argc, char* argv[]){
  List* list = keysToList(&argv[1], argc-1);
  selectionSort(&list);
  print(list);
  deleteAll(list);
}
