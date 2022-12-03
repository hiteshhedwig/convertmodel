#ifndef NCNN_H_OPTIMALL
#define NCNN_H_OPTIMALL

#include "ncnnoptimize.h"

class Optimizer {
      public :
      Optimizer();
      ~Optimizer();
      
      // ncnn optimizer
      NetOptimize* ncnn_optimize ;
      void ncnnOptimize(bool fp16, const char* inputStartName , const char* paramPath, const char* binPath);
      void saveOptimized(const char* paramPath, const char* binPath);
};

#endif