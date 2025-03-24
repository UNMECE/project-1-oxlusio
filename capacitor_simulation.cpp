#include <iostream>
#include <iomanip>

// define structre for capacitor
struct _capacitor {
	double *time; // time array
	double *voltage; // voltage array
	double *current;
	double C;
};
typedef struct _capacitor Capacitor;

// function to initialize the capacitor structure
void initializeCapacitor(Capacitor &cap, int num_timesteps, double C) {
	cap.time = new double[num_timesteps];
	cap.voltage = new double[num_timesteps];
	cap.current = new double[num_timesteps];
	cap.C = C;

	// initalize time array
	int i;
	for (i = 0; i < num_timesteps; ++i) {
		cap.time[i] = i * 1e-10;
	}

	// initalize voltage and current arrays to zero
	std::fill(cap.voltage, cap.voltage + num_timesteps, 0.0);
	std::fill(cap.current, cap.current + num_timesteps, 0.0);
}

// function to solve for voltage across capacitor with constant current source
void solveConstantCurrent(Capacitor &cap, int num_timesteps, double I) {
	int t;
	for (t = 0; t < num_timesteps - 1; ++t) {
		cap.voltage[t + 1] = cap.voltage[t] + I * 1e-10 / cap.C;
	}
}

// function to solve for current through capacitor with constant voltage source
void solveConstantVoltage(Capacitor &cap, int num_timesteps, double R, double V0) {
	cap.current[0] = V0 / R; //inital current

	int t;
	for (t = 0; t < num_timesteps - 1; ++t) {
		cap.current[t + 1] = cap.current[t] - (cap.current[t] * 1e-10) / (R * cap.C);
	}
}

int main() {
	const int num_timesteps = 50000;
	const double C = 100e-12;
	const double R = 1e3;
	const double I = 1e-2;
	const double V0 = 10.0;

	Capacitor cap;
	initializeCapacitor(cap, num_timesteps, C);

	// solve for consant with constant current source
	solveConstantCurrent(cap, num_timesteps, I);

	// output the resuluting voltage every 200 timesteps
	std::cout << "Constant Current Source:" << std::endl;
	for (int t = 0; t < num_timesteps; t += 200) {
		std::cout << "Time: " << cap.time[t] << " s, Voltage: " << cap.voltage[t] << " V" << std::endl;
	}
	
	// reinitialize the capacitor for constant volatage source case
	initializeCapacitor(cap, num_timesteps, C);

	// solve for current with constant voltage source
	solveConstantVoltage(cap, num_timesteps, R, V0);

	//output the resulting voltage for every 200 timesteps
	std::cout << "Constant Voltage Source:" << std::endl;
	for (int t = 0; t < num_timesteps; t += 200) {
		std::cout << "Time: " << cap.time[t] << " s, Current: " << cap.current[t] << " A" << std::endl;
	}

	// clean up memory
	delete[] cap.time;
	delete[] cap.voltage;
	delete[] cap.current;

	return 0;
}
