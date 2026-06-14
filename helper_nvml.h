#ifndef HELPER_NVML_H
#define HELPER_NVML_H

#include <stdio.h>
#include <nvml.h>
#include <iostream>
#include <cstdlib>

#define checkNVMLErrors(val) check((val), #val, __FILE__, __LINE__)

void check(nvmlReturn_t result, const char* func, const char* file, int const line) {
	if (result != NVML_SUCCESS) {
		fprintf(stderr, "Failed to %s in %s at %d: %s\n", func, file, line, nvmlErrorString(result));
		exit(EXIT_FAILURE);
	}
}

#endif