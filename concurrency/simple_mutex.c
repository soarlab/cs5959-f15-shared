#include <pthread.h>
#include <stdio.h>
#include <assert.h>

int Global;
pthread_mutex_t mtx;

void *Thread1(void *x) {
  int y;
  pthread_mutex_lock(&mtx);
  y = Global;
  y++;
  Global = y;
  pthread_mutex_unlock(&mtx);
  return NULL;
}

void *Thread2(void *x) {
  int y;
  pthread_mutex_lock(&mtx);
  y = Global;
  y--;
  Global = y;
  pthread_mutex_unlock(&mtx);
  return NULL;
}

int main() {
  pthread_t t[2];
  pthread_mutex_init(&mtx, 0);
  pthread_create(&t[0], NULL, Thread1, NULL);
  pthread_create(&t[1], NULL, Thread2, NULL);
  pthread_join(t[0], NULL);
  pthread_join(t[1], NULL);
  assert(Global == 0);
  pthread_mutex_destroy(&mtx);
}

