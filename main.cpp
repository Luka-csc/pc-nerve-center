#include <nvml.h>
#include <iostream>

int main() {
	// Initialize NVML
	nvmlReturn_t result = nvmlInit();
	if (result != NVML_SUCCESS) {
		std::cerr << "Failed to initialize NVML: " << nvmlErrorString(result) << std::endl;
		return 1;
	}

	// Get the handle for the first GPU device
	nvmlDevice_t device;
	result = nvmlDeviceGetHandleByIndex(0, &device);
	if (result != NVML_SUCCESS) {
		std::cerr << "Failed to get handle for device 0: " << nvmlErrorString(result) << std::endl;
		nvmlShutdown();
		return 1;
	}

	// Get the temperature of the GPU
	unsigned int temp;
	result = nvmlDeviceGetTemperature(device, NVML_TEMPERATURE_GPU, &temp);
	if (result != NVML_SUCCESS) {
		std::cerr << "Failed to get temperature for device 0: " << nvmlErrorString(result) << std::endl;
		nvmlShutdown();
		return 1;
	}

	std::cout << "GPU Temperature: " << temp << " C\n";

	// Shutdown NVML
	nvmlShutdown();
	return 0;
}