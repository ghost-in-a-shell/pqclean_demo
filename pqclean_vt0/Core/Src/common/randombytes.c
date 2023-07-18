/*
The MIT License

Copyright (c) 2017 Daan Sprenkels <hello@dsprenkels.com>

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
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/
// In the case that are compiling on linux, we need to define _GNU_SOURCE
// *before* randombytes.h is included. Otherwise SYS_getrandom will not be
// declared.
#if defined(__linux__)
# define _GNU_SOURCE
#endif /* defined(__linux__) */

#include "randombytes.h"
#include "string.h"
#include "stm32f4xx_hal.h"
#include "rng.h"
int randombytes(uint8_t *output, size_t n)
{
  //RNG_HandleTypeDef hrng;
  //hrng.Instance = RNG;
	MX_RNG_Init();
  size_t i;
  for (i = 0; i < n; i += 4) {
    uint32_t randValue;
    if (HAL_RNG_GenerateRandomNumber(&hrng, &randValue) == HAL_OK) {
      memcpy(&(output[i]), &randValue, 4);
    } else {
      // Error handling
    }
  }
	return 0;
}
