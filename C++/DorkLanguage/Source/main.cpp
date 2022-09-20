#include <iostream>
#include "Compiler/Compiler.h"

int main()
{
	std::ifstream t("../../Examples/test.dork");
	if (t.good())
	{
		Compiler compiler(&t);
	}
	return 0;
}
