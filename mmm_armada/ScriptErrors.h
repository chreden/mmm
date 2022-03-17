#pragma once

namespace mmm
{
	void scriptError(const std::string& error, bool stop = true);
	void reportError(const std::string& functionName, const std::string& error);
}
