#include "EmulationThread.h"



std::string toString(SpeedMode mode) {
	switch (mode) {
	case SpeedMode::Infinity:
		return "Infinity";
	case SpeedMode::Intel8080:
		return "Intel8080";
	case SpeedMode::Intel8085:
		return "Intel8085";
	default:
		return "Unknown";
	}
}

void EmulationThread::SetControlMode(const ControlMode& mode) {

	while (isThreadWorking() == true) {
		if (mode != ControlMode::Continous) {
			processor->ActiveFlagStop();
		}
	}

	Control = mode;
}
void EmulationThread::SetSpeedMode(const SpeedMode& mode) {
	Speed = mode;
}

bool EmulationThread::isThreadWorking() {
	return flag_ThreadWorking;
}

EmulationThread::EmulationThread(I8080* processor) : SaveSystem("Emulation") {
#ifdef WITH_DEBUG_OUTPUT
	cout << "Creating second thread for processor\n";
#endif

	this->processor = processor;

	threadObject = new thread(&EmulationThread::ThreadLoop, this);
}

EmulationThread::~EmulationThread() {

}


SpeedMode EmulationThread::GetSpeedMode() {
	return Speed;
}
ControlMode EmulationThread::GetControlMode() {
	return Control;
}



void EmulationThread::ThreadLoop() {


	while (true) {

		if (Control == ControlMode::Continous) {
			flag_ThreadWorking = true;


			if (Speed == SpeedMode::Infinity){

				while (1) {
					processor->NextStep();

					if (processor->PC_on_BreakPoint() || *processor->IsStop()) {
						Control = ControlMode::Stop;
						break;
					}
				}

			}



			if (Speed == SpeedMode::Intel8080) {

				const uint64_t targetTicksPerSecond = 3'000'000;
				const uint64_t targetTicksPerFrame = targetTicksPerSecond / 1000;

				while (1) {

					if (processor->PC_on_BreakPoint() || *processor->IsStop() || Speed != SpeedMode::Intel8080) {
						Control = ControlMode::Stop;
						break;
					}

					auto frameStartTime = std::chrono::high_resolution_clock::now();
					uint64_t startTicks = processor->GetCountTicks();

					while (processor->GetCountTicks() - startTicks < targetTicksPerFrame) {
						processor->NextStep();
					}

					while (true) {
						auto currentTime = std::chrono::high_resolution_clock::now();
						std::chrono::duration<double, std::milli> elapsedTime = currentTime - frameStartTime;

						if (elapsedTime.count() >= 1.0) {
							break;
						}
					}
					
				}

			}

			if (Speed == SpeedMode::Intel8085) {

				const uint64_t targetTicksPerSecond = 6'000'000;
				const uint64_t targetTicksPerFrame = targetTicksPerSecond / 1000; 

				while (1) {

					if (processor->PC_on_BreakPoint() || *processor->IsStop() || Speed != SpeedMode::Intel8085) {
						Control = ControlMode::Stop;
						break;
					}

					auto frameStartTime = std::chrono::high_resolution_clock::now();
					uint64_t startTicks = processor->GetCountTicks();

					while (processor->GetCountTicks() - startTicks < targetTicksPerFrame) {
						processor->NextStep();
					}

					while (true) {
						auto currentTime = std::chrono::high_resolution_clock::now();
						std::chrono::duration<double, std::milli> elapsedTime = currentTime - frameStartTime;

						if (elapsedTime.count() >= 1.0) {
							break;
						}
					}

				}

			}



			flag_ThreadWorking = false;
		}




		this_thread::sleep_for(chrono::milliseconds(100));
	}
}



std::string EmulationThread::Save() {
	std::string result = MakeBegin(1);

	result += MakeSaveItem("SpeedMode", toString(Speed));

	return result;
}
void EmulationThread::Load(const std::string& Data) {
	PrintDebugInfoAboutData(Data);

	auto save_info = SplitData(Data);

	for (int i = 0; i < save_info.size(); i++) {

		std::string Name_Element = save_info[i].first;
		std::string Data_Element = save_info[i].second;

		if (Name_Element == "SpeedMode") {

			if (Data_Element == "Infinity")
				Speed = SpeedMode::Infinity;
			else if (Data_Element == "Intel8080")
				Speed = SpeedMode::Intel8080;
			else if (Data_Element == "Intel8085")
				Speed = SpeedMode::Intel8085;
			else
				std::cout << "Unknowed save element founded: [" << Name_Element << "] [" << Data_Element << "]\n";
		}
		else {
			std::cout << "Unknowed save element founded: [" << Name_Element << "] [" << Data_Element << "]\n";
		}
	}
}