#include "ThreadedRayTracer.h"

static RayFactory _factory;

typedef struct {
  int i_low, i_high, j_low, j_high;
  ThreadedRayTracer *tracer;
} args_t;

void* renderFrameSection(void *void_args) {
  
  args_t *args = (args_t*)void_args;
  int i_low = args->i_low;
  int i_high = args->i_high;
  int j_low = args->j_low;
  int j_high = args->j_high;
  ThreadedRayTracer *tracer = args->tracer;

  for (int i=i_low; i<i_high; i++) {
    for (int j=j_low; j<j_high; j++) {
      tracer->renderPixel(i, j);
    }
  }

  return NULL;
}

void ThreadedRayTracer::renderFrame(int width, int height) {

  pthread_t *thread_handles = new pthread_t[N*M];
  args_t *args = new args_t[N*M];

  for (long i=0; i<N; i++) {
    for (int j=0; j<M; j++) {
      int id = i*M + j;
      args[id].i_low = (height / N) * i;
      args[id].i_high = (height / N) * (i+1);
      args[id].j_low = (width / M) * j;
      args[id].j_high = (width / M) * (j+1);
      args[id].tracer = this;

      pthread_create(&thread_handles[id], NULL, renderFrameSection, (void*) &args[id]);
    }
  }

  for (long i=0; i<N*M; i++) {
    pthread_join(thread_handles[i], NULL);
  }

  delete []thread_handles;
  delete []args;
}
