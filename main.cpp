
#include "ncnnoptimize.h"
#include "ncnnreader.h"
#include <algorithm>
#include <map>
#include <set>
#include <vector>

// ncnn public header
#include "layer.h"
#include "layer_type.h"
#include "net.h"


int main(int argc, char** argv)
{
    if (argc < 6)
    {
        fprintf(stderr, "usage: %s [inparam] [inbin] [outparam] [outbin] [flag] [cutstart] [cutend]\n", argv[0]);
        return -1;
    }

    const char* inparam = argv[1];
    const char* inbin = argv[2];
    const char* outparam = argv[3];
    const char* outbin = argv[4];
    int flag = atoi(argv[5]);
    const char* cutstartname = nullptr;
    const char* cutendname = nullptr;

    if (argc > 6)
    {
        cutstartname = argv[6];
    }

    if (argc > 7)
    {
        cutendname = argv[7];
    }

    NetOptimize optimizer;

    if (flag == 65536 || flag == 1)
    {
        optimizer.storage_type = 1;
    }
    else
    {
        optimizer.storage_type = 0;
    }

    optimizer.load_param(inparam);

    if (strcmp(inbin, "null") == 0)
    {
        DataReaderFromEmpty dr;
        optimizer.load_model(dr);
        optimizer.gen_random_weight = true;
    }
    else
        optimizer.load_model(inbin);

    if (optimizer.set_cutparam(cutstartname, cutendname) < 0)
    {
        return -1;
    }

    optimizer.fuse_batchnorm_scale();
    optimizer.fuse_convolution_batchnorm();
    optimizer.fuse_convolution_mul();
    optimizer.fuse_convolution_add();
    optimizer.fuse_convolutiondepthwise_batchnorm();
    optimizer.fuse_convolutiondepthwise_mul();
    optimizer.fuse_convolutiondepthwise_add();
    optimizer.fuse_deconvolution_batchnorm();
    optimizer.fuse_deconvolution_mul();
    optimizer.fuse_deconvolution_add();
    optimizer.fuse_deconvolutiondepthwise_batchnorm();
    optimizer.fuse_innerproduct_batchnorm();
    optimizer.fuse_innerproduct_add();
    optimizer.fuse_innerproduct_dropout();

    optimizer.replace_reduction_with_global_pooling();
    optimizer.replace_prelu_with_leaky_relu();

    optimizer.fuse_convolution_activation();
    optimizer.fuse_convolutiondepthwise_activation();
    optimizer.fuse_deconvolution_activation();
    optimizer.fuse_deconvolutiondepthwise_activation();
    optimizer.fuse_innerproduct_activation();
    optimizer.fuse_memorydata_binaryop();
    optimizer.fuse_binaryop_eltwise();

    optimizer.eliminate_dropout();
    optimizer.eliminate_pooling1x1();
    optimizer.eliminate_noop();
    optimizer.eliminate_split();
    optimizer.eliminate_flatten_after_global_pooling();
    optimizer.eliminate_reshape_after_global_pooling();
    optimizer.eliminate_reshape_before_binaryop();

    optimizer.replace_convolution_with_innerproduct_after_global_pooling();
    optimizer.replace_convolution_with_innerproduct_after_innerproduct();

    optimizer.eliminate_flatten_after_innerproduct();
    optimizer.eliminate_orphaned_memorydata();

    optimizer.shape_inference();

    optimizer.estimate_memory_footprint();

    optimizer.save(outparam, outbin);

    return 0;
}