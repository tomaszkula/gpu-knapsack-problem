#include <vector>
#include <iostream>
#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <cuda.h>
#include <device_functions.h>
#include <cuda_runtime_api.h>

__global__ void fillArray(int* _array, int n, int _value)
{
    int _id = threadIdx.x + blockIdx.x * blockDim.x;
    if (_id < n)
    {
        _array[_id] = _value;
    }
}

__device__ int maxi(int _a, int _b)
{
    if (_a > _b)
    {
        return _a;
    }
    else
    {
        return _b;
    }
}

__global__ void knapsackKernel(int i, int _xSize, int *_weights, int *_profits, int *maxValues)
{
    int j = threadIdx.x;

    int _id1 = (i * _xSize) + j;
    int _id2 = ((i - 1) * _xSize) + j;

    if (i == 0 || j == 0)
    {
        maxValues[_id1] = 0;
    }
    else if (_weights[i - 1] <= j)
    {
        maxValues[_id1] = maxi(maxValues[((i - 1) * _xSize) + (j - _weights[i - 1])] + _profits[i - 1], maxValues[_id2]);
    }
    else
    {
        maxValues[_id1] = maxValues[_id2];
    }

    __syncthreads();
}

extern "C"
{
    __host__ void solveParallelly(int _capacity, std::vector<int> _weights, std::vector<int> _profits)
    {
        int _intSize = sizeof(int);
        int _weightCount = _weights.size();
        int _weightsSize = _weightCount * _intSize;
        int _profitsCount = _profits.size();
        int _profitsSize = _profitsCount * _intSize;

        int* _dCapacity, * _dWeights, * _dProfits;
        cudaMalloc((void**)&_dCapacity, _intSize);
        cudaMalloc((void**)&_dWeights, _weightsSize);
        cudaMalloc((void**)&_dProfits, _profitsSize);
        cudaMemcpy(_dCapacity, &_capacity, _intSize, cudaMemcpyHostToDevice);
        cudaMemcpy(_dWeights, &_weights[0], _weightsSize, cudaMemcpyHostToDevice);
        cudaMemcpy(_dProfits, &_profits[0], _profitsSize, cudaMemcpyHostToDevice);

        int _maxValuesCount = (_weightCount + 1) * (_capacity + 1);
        int _maxValuesSize = _maxValuesCount * _intSize;
        int* _maxValues = (int*)malloc(_maxValuesSize);
        int* _dMaxValues; cudaMalloc((void**)&_dMaxValues, _maxValuesSize);
        //fillArray <<<_maxValuesCount, 1 >>> (_dMaxValues, _maxValuesCount, 0);
        //cudaMemcpy(_maxValues, _dMaxValues, _maxValuesSize, cudaMemcpyDeviceToHost);

        for (int i = 0; i <= _weightCount; i++)
        {
            knapsackKernel << <1, _capacity + 1 >> > (i, _capacity + 1, _dWeights, _dProfits, _dMaxValues);
        }

        cudaDeviceSynchronize();
        cudaMemcpy(_maxValues, _dMaxValues, _maxValuesSize, cudaMemcpyDeviceToHost);

        std::cout << "BEST VALUE : " << _maxValues[_weightCount * (_capacity + 1) + _capacity] << std::endl;

        free(_maxValues);

        cudaFree(_dCapacity);
        cudaFree(_dWeights);
        cudaFree(_dProfits);
        cudaFree(_dMaxValues);
    }

    __host__ float testParallelly(int _capacity, std::vector<int> _weights, std::vector<int> _profits, int _times)
    {
        cudaEvent_t _startEvent, _stopEvent;
        cudaEventCreate(&_startEvent);
        cudaEventCreate(&_stopEvent);

        int _intSize = sizeof(int);
        int _weightCount = _weights.size();
        int _weightsSize = _weightCount * _intSize;
        int _profitsCount = _profits.size();
        int _profitsSize = _profitsCount * _intSize;

        int* _dCapacity, * _dWeights, * _dProfits;
        cudaMalloc((void**)&_dCapacity, _intSize);
        cudaMalloc((void**)&_dWeights, _weightsSize);
        cudaMalloc((void**)&_dProfits, _profitsSize);
        cudaMemcpy(_dCapacity, &_capacity, _intSize, cudaMemcpyHostToDevice);
        cudaMemcpy(_dWeights, &_weights[0], _weightsSize, cudaMemcpyHostToDevice);
        cudaMemcpy(_dProfits, &_profits[0], _profitsSize, cudaMemcpyHostToDevice);

        int _maxValuesCount = (_weightCount + 1) * (_capacity + 1);
        int _maxValuesSize = _maxValuesCount * _intSize;
        int* _maxValues = (int*)malloc(_maxValuesSize);
        int* _dMaxValues; cudaMalloc((void**)&_dMaxValues, _maxValuesSize);

        cudaEventRecord(_startEvent);
        for (int t = 0; t < _times; t++)
        {
            for (int i = 0; i <= _weightCount; i++)
            {
                knapsackKernel << <1, _capacity + 1 >> > (i, _capacity + 1, _dWeights, _dProfits, _dMaxValues);
            }
        }
        cudaEventRecord(_stopEvent);

        cudaDeviceSynchronize();
        cudaMemcpy(_maxValues, _dMaxValues, _maxValuesSize, cudaMemcpyDeviceToHost);

        cudaEventSynchronize(_stopEvent);
        float _duration = 0;
        cudaEventElapsedTime(&_duration, _startEvent, _stopEvent);

        free(_maxValues);

        cudaFree(_dCapacity);
        cudaFree(_dWeights);
        cudaFree(_dProfits);
        cudaFree(_dMaxValues);

        return _duration;
    }
}