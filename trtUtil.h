#ifndef _TRT_UTIL_H_
#define _TRT_UTIL_H_

#include <opencv2/opencv.hpp>
#include "NvInfer.h"

using namespace nvinfer1;

char *changeSuffix(char *name, const char *new_suffix);
double getUnixTime(void);
char *getFileName(char *buf, const char *path);
char *joinPath(char *prepath, char *subpath);
void validateDir(const char *dir, int do_mkdir);
std::vector<std::string> getImageList(const char *pathname, const char *eval_list);
char *assemblePath(char *buf, const char *dir, const char *file_path, const char *suffix);
std::map<std::string, Weights> loadWeights(const std::string file);
cv::Mat readImage(const std::string& filename, int width, int height, float *img_width, float *img_height);
void preprocessFrame(cv::Mat &frame, cv::Mat &frame_origin, int width, int height, float *img_width, float *img_height);

/* class Reshape: public IPlugin */
/* { */
/* public: */
/*     Reshape(Dims newDim): mNewDim(newDim) { */
/*     } */

/*     Reshape(const void* data, size_t length) { */
/*         const char* d = reinterpret_cast<const char*>(data), *a = d; */
/*         mNewDim = read<Dims>(d); */
/*         mCopySize = read<size_t>(d); */
/*         assert(d == a + length); */
/*     } */

/*     int getNbOutputs() const override { */
/*         return 1; */
/*     } */

/* 	Dims getOutputDimensions(int index, const Dims* inputDims, int nbInputDims) override { */
/*         assert(nbInputDims == 1); */
/*         assert(index == 0); */
/*         assert(inputDims[index].nbDims == 4); */
/*         assert((inputDims[0].d[0])*(inputDims[0].d[1])*(inputDims[0].d[2])*(inputDims[0].d[3]) == (mNewDim[0].d[0])*(mNewDim[0].d[1])*(mNewDim[0].d[2])*(mNewDim[0].d[3])); */
/*         return mNewDim; */
/*     } */

/* 	int initialize() override { */
/*         return 0; */
/*     } */

/* 	void terminate() override { */
/*     } */

/* 	size_t getWorkspaceSize(int) const override { */
/*         return 0; */
/*     } */

/* 	// currently it is not possible for a plugin to execute "in place". Therefore we memcpy the data from the input to the output buffer */
/* 	int enqueue(int batchSize, const void*const *inputs, void** outputs, void*, cudaStream_t stream) override { */
/*         CHECK(cudaMemcpyAsync(outputs[0], inputs[0], mCopySize * batchSize, cudaMemcpyDeviceToDevice, stream)); */
/*         return 0; */
/*     } */

/* 	size_t getSerializationSize() override { */
/*         return sizeof(mCopySize) + sizeof(mNewDim); */
/*     } */

/* 	void serialize(void* buffer) override { */
/*         char* d = reinterpret_cast<char*>(buffer), *a = d; */
/* 		write(d, mNewDim); */
/* 		write(d, mCopySize); */
/* 		assert(d == a + getSerializationSize()); */
/*     } */

/*     void configure(const Dims*inputDims, int nbInputs, const Dims* outputDims, int nbOutputs, int)	override { */
/*         mCopySize = inputDims[0].d[0] * inputDims[0].d[1] * inputDims[0].d[2] * inputDims[0].d[3] * sizeof(float); */
/*     } */

/* private: */
/* 	template<typename T> void write(char*& buffer, const T& val) { */
/*         *reinterpret_cast<T*>(buffer) = val; */
/*         buffer += sizeof(T); */
/*     } */

/* 	template<typename T> T read(const char*& buffer) { */
/*         T val = *reinterpret_cast<const T*>(buffer); */
/*         buffer += sizeof(T); */
/*         return val; */
/*     } */

/*     Dims mNewDim; */
/*     size_t mCopySize; */
/* } */

#endif  /* _TRT_UTIL_H_ */
