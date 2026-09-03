#include "Kili.h"

class Runtime : public Kili::Engine
{
public:
	Runtime() = default;
	~Runtime() override = default;
};

Kili::Engine* Kili::CreateEngine()
{
	return new Runtime();
}