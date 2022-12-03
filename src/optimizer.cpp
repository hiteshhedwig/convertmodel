#include "layer.h"
#include "layer_type.h"
#include "net.h"

#include "ncnnoptimize.h"
#include "ncnnreader.h"
#include <algorithm>
#include <map>
#include <set>
#include <vector>
#include "optimizer.h"
#include <iostream>

Optimizer::Optimizer() {
    ncnn_optimize = new NetOptimize(); 
};

Optimizer::~Optimizer() {};


void Optimizer::ncnnOptimize(bool fp16, const char* inputStartName , const char* paramPath, const char* binPath) {
    ncnn_optimize->loadNcnnModel(paramPath, binPath);
    if (fp16) {
        ncnn_optimize->truncateFP16(inputStartName);
    } else {
        ncnn_optimize->truncateFP32(inputStartName);
    }
    ncnn_optimize->optimize();
}

void Optimizer::saveOptimized(const char* paramPath, const char* binPath) {
    //ncnn_optimize->save_optimized_model(paramPath, binPath);
    ncnn_optimize->save_optimized_model(paramPath, binPath);
}
