#ifndef MAIN_C
#define MAIN_C

#include <stdio.h>
#include <stdlib.h>
#include "lctrl.h"

#include  <fcntl.h>
#include  <unistd.h>
#include  <signal.h>
#include  <sys/stat.h>
#include  <linux/kd.h>
#include  <sys/types.h>
#include  <sys/ioctl.h>

int main(int argc, char** argv) {
#ifdef TEST_FOR_FRAME_PLAY
	str_light* l_num = make_light(LT_NUMLOCK);
	str_light* l_caps = make_light(LT_CAPSLOCK);
	str_light* l_scroll = make_light(LT_SCROLLLOCK);

	str_light* lights = (str_light*)malloc(3*sizeof(str_light));
	lights[0] = *l_num;
	lights[1] = *l_caps;
	lights[2] = *l_scroll;

	LightStatus *status = (LightStatus*)malloc(3*sizeof(LightStatus));
	status[0] = 0;
	status[1] = 0;
	status[2] = 1;

	int fd;
    if ((fd = open(LTCTRL_DEVICE,O_NOCTTY)) < 0)
        return 0;

	frame_play(fd,lights,status,3);

	close(fd);
#endif //TEST_FOR_FRAME_PLAY
	return 0;
}

#endif // MAIN_C
