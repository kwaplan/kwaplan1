#pragma once
#include <iostream>

namespace Kwaplan {
	namespace Misc {
		namespace Logging {

			typedef enum{LOG_INFO, LOG_WARN, LOG_ERROR}LogType;
			void Log(LogType errType, std::string str);
		}
	}
}