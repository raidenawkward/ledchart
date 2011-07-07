/// light ctrl
// raiden.ht@gmail.com
//

#ifndef LCTRL_H
#define LCTRL_H

#include "light.h"
#include <stdio.h>
#include <stdlib.h>

#define LTCTRL_ON 1
#define LTCTRL_OFF 0

#define LTCTRL_DEVICE "/dev/console"

typedef int LightStatus;

typedef struct {
	int light_num;
	struct str_light* lights;

	LightStatus** light_status;
	long frame_count;
} str_ltchart;

int light_ctrl(str_light *light, LightStatus status);
int frame_play(int device, str_light* lights, LightStatus *status, int lightnum);
int chart_play(str_ltchart* chart);

#endif
