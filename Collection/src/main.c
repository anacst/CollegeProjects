#include <stdio.h>

#include <auxiliary.h>
#include <collection.h>

int main() {

  //times
  double time_read;

  double time_insert_ordered;
  double time_insert_last;
  double time_insert_first;
  double time_insert_binary;
  double time_insert_avl;

  double time_search_ordered;
  double time_search_last;
  double time_search_first;
  double time_search_binary;
  double time_search_avl;

  //flags item found
  int found_ordered = 0;
  int found_last    = 0;
  int found_first   = 0;
  int found_binary  = 0;
  int found_avl     = 0;

  //collections
  COLLECTION* c_ordered;
  COLLECTION* c_last;
  COLLECTION* c_first;
  COLLECTION* c_binary;
  COLLECTION* c_avl;

  //reading values
  const int N = 50000;

  init_time();
    int* insert = read_integers("../insert.txt", N);
    int* search    = read_integers("../search.txt", N);
  time_reading = end_time();

  //add values in each of the 5 structures
  init_time();
  c_ordered = create_collection(ORDERED_LIST);
  for(int i = 0; i < N; i++)
    insert(c_ordered, insert[i]);
  time_insert_ordered = end_time;

  init_time();
  c_last = create_collection(LAST_LIST);
  for(int i = 0; i < N; i++)
    insert(c_last, insert[i]);
  time_insert_last = end_time;

  init_time();
  c_first = create_collection(FIRST_LIST);
  for(int i = 0; i < N; i++)
    insert(c_first, insert[i]);
  time_insert_first = end_time;

  init_time();
  c_binary = create_collection(BINARY_TREE);
  for(int i = 0; i < N; i++)
    insert(c_binary, insert[i]);
  time_insert_binary = end_time;

  init_time();
  c_avl = create_collection(AVL_TREE);
  for(int i = 0; i < N; i++)
    insert(c_avl, insert[i]);
  time_insert_avl = end_time;

  //search values in each of the five structures
  init_time();
  for(int i = 0; i < N; i++)
    found_ordered += exist(c_ordered, insert[i]);
  time_search_ordered = end_time;

  init_time();
  for(int i = 0; i < N; i++)
    found_last += exist(c_last, insert[i]);
  time_search_last = end_time;

  init_time();
  for(int i = 0; i < N; i++)
    found_first += exist(c_first, insert[i]);
  time_search_first = end_time;

  init_time();
  for(int i = 0; i < N; i++)
    found_binary += exist(c_binary, insert[i]);
  time_search_binary = end_time;

  init_time();
  for(int i = 0; i < N; i++)
    found_avl += exist(c_avl insert[i]);
  time_search_avl = end_time;

  destroy(c_ordered);
  destroy(c_last);
  destroy(c_first);
  destroy(c_binary);
  destroy(c_avl);

  printf("\n\n\t\tINSERTION TIME\n\n");
  printf("Ordered list     \t%f\t%d\n", time_insert_ordered);
  printf("Insertion on tail\t%f\t%d\n", time_insert_last);
  printf("Insertion on head\t%f\t%d\n", time_insert_first);
  printf("Binary tree      \t%f\t%d\n", time_insert_binary);
  printf("AVL Tree         \t%f\t%d\n", time_insert_avl);

  printf("\n\n\t\tSEARCH TIME\n\n");
  printf("Ordered list     \t%f\t%d\n", time_search_ordered);
  printf("Insertion on tail\t%f\t%d\n", time_search_last);
  printf("Insertion on head\t%f\t%d\n", time_search_first);
  printf("Binary tree      \t%f\t%d\n", time_search_binary);
  printf("AVL Tree         \t%f\t%d\n", time_search_avl);

  return 0;
}
