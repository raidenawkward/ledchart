#ifndef MAIN_C
#define MAIN_C

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lctrl.h"
#include "chart.h"
#include <fcntl.h>


#define VERSION "0.11"
#define DEFAULT_LIGHT_NUM 3 // num lock, caps lock, scroll lock

void show_help_info();
void show_chart_example();
void show_program_version(const char* version);

int main(int argc, char** argv) {

	if (argc < 2) {
		show_help_info();
		return 0;
	}

	int repeat = 1;
	int interval = 1;
	int status_num = -1;
	int status_caps = -1;
	int status_scroll = -1;
	int file_path_index = 0;

	int argi = 1;
	while(argi < argc) {
		if (strcmp(argv[argi],"-r") == 0) {
			if (argv[argi + 1][0] != '-' && argi + 1 < argc) {
				repeat = atoi(argv[++argi]);
				if (repeat <= 0) {
					show_help_info();
					return 0;
				}
			} else {
				show_help_info();
				return 0;
			}
		} else if (strcmp(argv[argi],"-R") == 0) {
			repeat = 0;

		} else if (strcmp(argv[argi],"-s") == 0) {
			if (argi + 3 > argc) {
				show_help_info();
				return 0;
			}
			
			status_num = atoi(argv[++argi]);
			status_caps = atoi(argv[++argi]);
			status_scroll = atoi(argv[++argi]);

		} else if (strcmp(argv[argi],"-i") == 0) {
			if (argi + 1 > argc) {
				show_help_info();
				return 0;
			}
			interval = atoi(argv[++argi]);

		} else if (strcmp(argv[argi],"-e") == 0) {
			show_chart_example();
			return 0;

		} else if (strcmp(argv[argi],"-v") == 0) {
			show_program_version(VERSION);
			return 0;

		} else if (strcmp(argv[argi],"-h") == 0) {
			show_help_info();
			return 0;

		} else {
			if (argv[argi][0] == '-') {
				show_help_info();
				return 0;
			}
			file_path_index = argi;
		}
		++argi;
	}

	str_light* l_num = make_light(LT_NUMLOCK);
	str_light* l_caps = make_light(LT_CAPSLOCK);
	str_light* l_scroll = make_light(LT_SCROLLLOCK);

	str_light* lights = (str_light*)malloc(DEFAULT_LIGHT_NUM * sizeof(str_light));
	lights[0] = *l_num;
	lights[1] = *l_caps;
	lights[2] = *l_scroll;

	if (status_num >=0 && status_caps >= 0 && status_scroll >= 0) {
		int fd;
		if ((fd = open(LTCTRL_DEVICE,O_NOCTTY)) < 0)
        	return 1;
		LightStatus* light_status = (LightStatus*)malloc(sizeof(LightStatus) * DEFAULT_LIGHT_NUM);
		light_status[0] = status_num;
		light_status[1] = status_caps;
		light_status[2] = status_scroll;
		frame_play(fd,lights,light_status,DEFAULT_LIGHT_NUM);
		close(fd);
		return 0;
	}

	if (repeat < 0) {
		printf("invalid repeat num \'%d\'\n",repeat);
		return 1;
	}

	if (interval < 1) {
		printf("invalid time interval \'%d\'\n",interval);
		return 1;
	}

	str_ltchart* chart = load_chart(argv[file_path_index],lights,DEFAULT_LIGHT_NUM);
	if (!chart) {
		printf("error when loading chart file \'%s\'\n",argv[1]);
		return 1;
	}

	chart_play(chart,repeat,interval);

	return 0;
}

void show_help_info() {
	printf("ledchart - ctrls 3 led lights (num lock, caps lock, scroll lock) by chart or status.\n");
	printf("usage : ledchart [options] [chart file | led status]\n");
	printf("options :\n");
	printf("-r [repeat times]\t-\tplay the chart cyclically by n(of course bigger than 0) times;\n");
	printf("-R\t-\twill repeat all the time;\n");
	printf("-s status\t-\tdo not use a chart file, use a one-time status info instead (for example ledchart -s 0 1 0);\n");
	printf("-i interval\t-\tset time interval(second);\n");
	printf("-e\t-\tshow chart example;\n");
	printf("-v\t-\tshow program version;\n");
	printf("-h\t-\tshow this message.\n");
	printf("copyleft by raiden.ht@gmail.com\n");
	printf("it may be a silly program, but enjoy it. -_-\n");
}

void show_chart_example() {
	printf("this is a chart file example:\n");
	printf("0,0,0\n0,0,1\n0,1,0\n0,1,1\n1,0,0\n1,0,1\n1,1,0\n1,1,1\n");
}

void show_program_version(const char* version) {
	printf("version : %s\n",version);
}

#endif // MAIN_C
