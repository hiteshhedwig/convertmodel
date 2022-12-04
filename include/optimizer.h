#ifndef NCNN_H_OPTIMALL
#define NCNN_H_OPTIMALL

#include "ncnnoptimize.h"
#include "onnx2ncnn.h"

class Optimizer {
      public :
      Optimizer();
      ~Optimizer();
      
      // ncnn optimizer
      NetOptimize* ncnn_optimize ;
      Onnx2Ncnn*   onnx2ncnn     ;
      
      void convertFromOnnx2Ncnn(const char* onnxPath) ;
      void ncnnOptimize(bool fp16, const char* inputStartName , const char* paramPath, const char* binPath);
      void saveOptimized(const char* paramPath, const char* binPath);
};

#endif