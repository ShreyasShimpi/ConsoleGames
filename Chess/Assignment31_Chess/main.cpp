//internal includes
#include "CChess.h"
#include "Engine.h"

int main()
{
	CEngine engine(WIDTH, HEIGHT);
	while (engine.IsWindowRunning())
	{
		engine.Update();
		engine.Render();
	}
}
