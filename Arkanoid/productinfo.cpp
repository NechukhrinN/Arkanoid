#include "productinfo.h"

/*
1.0 Start
1.1 Resolution and display settings, borderless mode, frame-rate independent movement
*/

ProductInfo::ProductInfo()
	: version("1.1")
{
}

std::string ProductInfo::getVersion() const
{
	return "v." + version;
}
