#include "lctrl.h"
#include <unistd.h>
#include <signal.h>
#include <linux/kd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>

int light_ctrl(str_light *light, LightStatus status) {
	if (!light)
		return 0;
	
	return 0;
}

int frame_play(int device, str_light *light, LightStatus *status, int lightnum) {
	char c;
	if (ioctl(device,KDGETLED,&c) != 0)
		return 0;
	int i;
	for (i = 0; i < lightnum; ++i) {
		int key = light[i].key;
		if (status[i]) {
			c &= ~key;
		} else {
			c |= key;
		}
		if (ioctl(device,KDSETLED,c) != 0)
			return 0;
	}
	return 0;
}

int chart_play(str_ltchart *chart) {
	if (!chart)
		return 0;
	int fd;
	if ((fd = open(LTCTRL_DEVICE,O_NOCTTY)) < 0)
		return 0;
	long i;
	for (i = 0; i < chart->frame_count; ++i) {
		if (!frame_play(fd,chart->lights,chart->light_status[i],chart->light_num))
			break;;
	}
	close(fd);
	return 1;
}
