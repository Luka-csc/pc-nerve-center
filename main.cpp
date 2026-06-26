#include "helper_nvml.h"
#include <thread>
#include <chrono>
#include <cmath>
#include <iomanip>
#include "third_party/nlohmannParser/json.hpp"

using json = nlohmann::json;

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
		std::cout << std::fixed << std::setprecision(2) << "GPU Power Usage: " << gpu_power / 1000.0 << " W\n";

		nvmlUtilization_t gpu_util;
		checkNVMLErrors(nvmlDeviceGetUtilizationRates(device, &gpu_util));
		std::cout << "GPU Utilization: " << gpu_util.gpu << " %\n";

		nvmlMemory_t gpu_memory;
		checkNVMLErrors(nvmlDeviceGetMemoryInfo(device, &gpu_memory));
		std::cout << std::fixed << std::setprecision(2) << "GPU Memoryu Usage: " << gpu_memory.used/GB << "/" << gpu_memory.total/GB << " GB\n";

		// json section
		json data;
		data["gpu_temp"] = temp;
		data["gpu_clock"] = clock;
		data["gpu_power"] = gpu_power / 1000.0;
		data["gpu_util"] = gpu_util.gpu;
		data["gpu_memory_used"] = gpu_memory.used / GB;
		data["gpu_memory_total"] = gpu_memory.total / GB;

		std::cout << data.dump() << "\n";

		// Need to add sleeping to prevent 100% CPU usage
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}

	// Shutdown NVML
	nvmlShutdown();
	return 0;
}