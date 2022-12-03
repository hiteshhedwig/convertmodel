#ifndef NCNN_H_OPTIM
#define NCNN_H_OPTIM

#include "modelwriter.h"

class NetOptimize : public ModelWriter
{
public:
    NetOptimize();

public:
    int fuse_batchnorm_scale();
    int fuse_convolution_batchnorm();
    int fuse_convolution_mul();
    int fuse_convolution_add();
    int fuse_convolutiondepthwise_batchnorm();
    int fuse_convolutiondepthwise_mul();
    int fuse_convolutiondepthwise_add();
    int fuse_deconvolution_batchnorm();
    int fuse_deconvolution_mul();
    int fuse_deconvolution_add();
    int fuse_deconvolutiondepthwise_batchnorm();
    int fuse_innerproduct_batchnorm();
    int fuse_innerproduct_add();
    int fuse_innerproduct_dropout();
    int fuse_convolution_activation();
    int fuse_convolutiondepthwise_activation();
    int fuse_deconvolution_activation();
    int fuse_deconvolutiondepthwise_activation();
    int fuse_innerproduct_activation();
    int fuse_memorydata_binaryop();
    int fuse_binaryop_eltwise();

    int eliminate_dropout();
    int eliminate_pooling1x1();
    int eliminate_noop();
    int eliminate_split();
    int eliminate_orphaned_memorydata();
    int eliminate_flatten_after_global_pooling();
    int eliminate_reshape_after_global_pooling();
    int eliminate_flatten_after_innerproduct();
    int eliminate_reshape_before_binaryop();

    int replace_reduction_with_global_pooling();
    int replace_prelu_with_leaky_relu();
    int replace_convolution_with_innerproduct_after_global_pooling();
    int replace_convolution_with_innerproduct_after_innerproduct();

    int optimize();
    int save_optimized_model(const char *paramPath, const char *binPath) {
        save(paramPath, binPath);
    }
};


#endif

