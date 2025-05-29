//internal includes
#include "Engine.h"
#include "Defines.h"

int main()
{
	CEngine engine(WIDTH * SCALE, HEIGHT * SCALE);
	while (engine.IsWindowRunning())
	{
		engine.Update();
		engine.Render();
	}
}
