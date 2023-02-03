#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <string>
#include <vector>

#include "SDL.h"
#include "SDL_thread.h"
#include "filesystemutilityposix.h"
#include "applicationcontroller.h"

int main(int argc, char *argv[])
{
	srand(time(NULL));
	
	ApplicationController applicationController;
	applicationController.Run();

	return(0);
}
