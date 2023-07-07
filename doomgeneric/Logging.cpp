#include <iostream>
#include "kwaplan_logging.h"

void Kwaplan::Misc::Logging::Log(Kwaplan::Misc::Logging::LogType errType, std::string str) {
	 switch (errType) {
	 case LOG_INFO:
		 std::cout << "[kwaplan))) | INFO] ";
		 break;
	 case LOG_WARN:
		 std::cout << "[kwaplan))) | WARN] ";
		 break;
	 case LOG_ERROR:
		 std::cout << "[kwaplan))) | ERROR] ";
		 break;
	 }
	 std::cout << str;
	 std::cout << "\n";
}