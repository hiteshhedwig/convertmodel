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
#include "onnx2ncnn.h"
#include <iostream>

Optimizer::Optimizer() {
    ncnn_optimize = new NetOptimize(); 
    onnx2ncnn     = new Onnx2Ncnn();
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

void Optimizer::convertFromOnnx2Ncnn(const char* onnxPath) {
    onnx2ncnn->convert(onnxPath, "ncnn_onnx.param", "ncnn_onnx.bin");
}
