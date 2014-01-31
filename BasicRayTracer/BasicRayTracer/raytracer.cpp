#include <windows.h>
#include <stdio.h>
#include "scene_io.h"
#include "Timer.h"

#define IMAGE_WIDTH		1500
#define IMAGE_HEIGHT	1500


typedef unsigned char u08;

SceneIO *scene = NULL;


static void loadScene(char *name) {
	/* load the scene into the SceneIO data structure using given parsing code */
	scene = readScene(name);

	/* hint: use the Visual Studio debugger ("watch" feature) to probe the
	   scene data structure and learn more about it for each of the given scenes */


	/* write any code to transfer from the scene data structure to your own here */
	/* */

	return;
}


/* just a place holder, feel free to edit */
void render(void) {
	int i, j, k;
	u08 *image = (u08 *)malloc(sizeof(u08) * IMAGE_HEIGHT * IMAGE_WIDTH * 3);
	u08 *ptr = image;

	for (j = 0; j < IMAGE_HEIGHT; j++) {
		for (i = 0; i < IMAGE_WIDTH; i++) {
			for (k = 0; k < 3; k++) {
				*(ptr++) = 0;
			}
		}
	}

	/* save out the image */
	/* */

	/* cleanup */
	free(image);

	return;
}



int main(int argc, char *argv[]) {
	Timer total_timer;
	total_timer.startTimer();

	loadScene("../Scenes/test1.scene");

	/* write your ray tracer here */
	render();

	/* cleanup */
	if (scene != NULL) {
		deleteScene(scene);
	}

	total_timer.stopTimer();
	fprintf(stderr, "Total time: %.5lf secs\n\n", total_timer.getTime());
	
	return 1;
}
