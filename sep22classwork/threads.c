#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

void *printLettersLower();
void *printLettersUpper();
void *printNumbers();

pthread_mutex_t mutex;

int main() {
  pthread_t p1, p2, p3;
  pthread_mutex_init(&mutex, NULL);
  int t1 = pthread_create(&p1, NULL, &printLettersLower, NULL);
  int t2 = pthread_create(&p2, NULL, &printLettersUpper, NULL);
  int t3 = pthread_create(&p3, NULL, &printNumbers, NULL);
  pthread_join(p1, NULL);
  pthread_join(p2, NULL);
  pthread_join(p3, NULL);
  pthread_mutex_destroy(&mutex);
  return 0;
}

void *printLettersLower() {
  pthread_mutex_lock(&mutex);
  char firstLetter = 'a';
  int  counter = 0;
  while (counter < 26) {
    printf("%c\n", firstLetter + counter);
    counter++;
  }
  pthread_mutex_unlock(&mutex);
}

void *printLettersUpper() {
  pthread_mutex_lock(&mutex);
  char firstLetter = 'A';
  int  counter = 0;
  while (counter < 26) {
    printf("%c\n", firstLetter + counter);
    counter++;
  }
  pthread_mutex_unlock(&mutex);
}

void *printNumbers() {
  pthread_mutex_lock(&mutex);
  for (int i = 1; i <= 100; i++) {
    printf("%d\n", i);
  }
  pthread_mutex_unlock(&mutex);
}
