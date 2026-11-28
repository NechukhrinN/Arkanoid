#ifndef  PRODUCTINFO
#define PRODUCTINFO
#include <string>

class ProductInfo
{
public:
	ProductInfo();

	std::string getVersion() const;

private:
	std::string version;
};

#endif
