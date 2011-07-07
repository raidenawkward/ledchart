#ifndef MAIN_C
#define MAIN_C

#include <stdio.h>
#include <stdlib.h>
#include "lctrl.h"
#include "chart.h"


#define DEFAULT_LIGHT_NUM 3 // num lock, caps lock, scroll lock

int main(int argc, char** argv) {

	if (argc < 2) {
		printf("usage : %s [chart]\n",argv[0]);
		return 0;
	}

	str_light* l_num = make_light(LT_NUMLOCK);
	str_light* l_caps = make_light(LT_CAPSLOCK);
	str_light* l_scroll = make_light(LT_SCROLLLOCK);

	str_light* lights = (str_light*)malloc(DEFAULT_LIGHT_NUM * sizeof(str_light));
	lights[0] = *l_num;
	lights[1] = *l_caps;
	lights[2] = *l_scroll;


	str_ltchart* chart = load_chart(argv[1],lights,DEFAULT_LIGHT_NUM);
	if (!chart) {
		printf("error when loading chart file %s\n",argv[1]);
		return 1;
	}

	chart_play(chart,0,2);

	return 0;
}

#endif // MAIN_C
