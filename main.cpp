#include "helper_nvml.h"
#include <thread>
#include <chrono>
#include <cmath>
#include <iomanip>

int main() {
	const double GB = 1024 * 1024 * 1024;

	// Initialize NVML
	checkNVMLErrors(nvmlInit());

	// Get the handle for the first GPU device
	nvmlDevice_t device;
	checkNVMLErrors(nvmlDeviceGetHandleByIndex(0, &device));

	while (true) {
		// Get the temperature of the GPU
		unsigned int temp;
		checkNVMLErrors(nvmlDeviceGetTemperature(device, NVML_TEMPERATURE_GPU, &temp));
		std::cout << "GPU Temperature: " << temp << " C\n";

		// Get the core clock of the GPU
		unsigned int clock;
		checkNVMLErrors(nvmlDeviceGetClockInfo(device, NVML_CLOCK_GRAPHICS, &clock));
		std::cout << "GPU Core Clock: " << clock << " MHz\n";

		unsigned int gpu_power;
		checkNVMLErrors(nvmlDeviceGetPowerUsage(device, &gpu_power));
		std::cout << "GPU Power Usage: " << gpu_power / 1000 << " W\n";

		nvmlUtilization_t gpu_util;
		checkNVMLErrors(nvmlDeviceGetUtilizationRates(device, &gpu_util));
		std::cout << "GPU Utilization: " << gpu_util.gpu << " %\n";

		nvmlMemory_t gpu_memory;
		checkNVMLErrors(nvmlDeviceGetMemoryInfo(device, &gpu_memory));
		std::cout << std::fixed << std::setprecision(2) << "GPU Memoryu Usage: " << gpu_memory.used/GB << "/" << gpu_memory.total/GB << " GB\n";

		// Need to add sleeping to prevent 100% CPU usage
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}

	// Shutdown NVML
	nvmlShutdown();
	return 0;
}