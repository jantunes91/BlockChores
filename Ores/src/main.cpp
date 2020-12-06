#include "Engine.h"

#include "Button.h"

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#ifdef _DEBUG
#define new new( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#else
#define new new
#endif

int main(int argc, char* args[])
{
	{
		std::shared_ptr<Engine> engine = std::make_shared<Engine>();
		engine->Run();
	}
	_CrtDumpMemoryLeaks();

	return 0;
}