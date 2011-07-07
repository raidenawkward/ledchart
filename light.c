#include "light.h"
#include <linux/kd.h>


str_light* make_light(LightType type) {
	int key = get_key_by_light_type(type);
	str_light *light = NULL;
	if (key) {
		light = (str_light*)malloc(sizeof(str_light));
		light->type = type;
		light->key = key;
		light->device_fd = 0;
	} else {
		light->type = LT_INVALID;
	}
	return light;
}

int get_key_by_light_type(LightType type) {
	int key = 0;
	switch(type) {
	case LT_NUMLOCK:
		key = LED_NUM;
		break;
	case LT_CAPSLOCK:
		key = LED_CAP;
		break;
	case LT_SCROLLLOCK:
		key = LED_SCR;
		break;
	case LT_INVALID:
	default:
		break;
	}
	return key;
}
