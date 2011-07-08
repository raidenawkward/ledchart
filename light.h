/// light defines
// raiden.ht@gmail.com
//

#ifndef LIGHT_H
#define LIGHT_H

#include <stdio.h>
#include <stdlib.h>

#define LT_INVALID 0x00
#define LT_NUMLOCK 0x1
#define LT_CAPSLOCK 0x2
#define LT_SCROLLLOCK 0x4

typedef int LightType;

/*enum LightType {
	LT_NUMLOCK,
	LT_CAPSLOCK,
	LT_SCROLLLOCK,
	LT_INVALID
};*/

typedef struct {
	LightType type;
	int key;
	int device_fd;
} str_light;

str_light* make_light(LightType type);
int get_key_by_light_type(LightType type);

#endif // LIGHT_H
