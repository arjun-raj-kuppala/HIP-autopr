/*
Copyright (c) 2015 - 2021 Advanced Micro Devices, Inc. All rights reserved.
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

/* HIT_START
 * BUILD: %t %s ../../test_common.cpp
 * TEST: %t
 * HIT_END
 */

#include "test_common.h"
#define SIZE 100

int main(){

    void *Sd;
    hipError_t e;
    char S[SIZE]="This is not a device symbol";

    HIPCHECK(hipMalloc(&Sd,SIZE));

    hipStream_t stream;
    HIPCHECK(hipStreamCreate(&stream));

    e = hipMemcpyToSymbolAsync(HIP_SYMBOL(Sd), S, SIZE, 0, hipMemcpyHostToDevice, stream);
    HIPASSERT(e==hipErrorInvalidSymbol);

    e = hipMemcpyToSymbolAsync(NULL, S, SIZE, 0, hipMemcpyHostToDevice, stream);
    HIPASSERT(e==hipErrorInvalidSymbol);

    HIPCHECK(hipFree(Sd));

    passed();
}
