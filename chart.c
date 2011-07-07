#include "chart.h"

str_ltchart* load_chart(const char* file, str_light* lights, int lightnum) {
	str_ltchart* chart = NULL;
	if (!lights || lightnum <=0)
		return chart;

	FILE* fp = fopen(file,"r");
	if (!fp)
		return chart;

	LightStatus **status = NULL;

	status = (LightStatus**)malloc(sizeof(LightStatus*));
	status[0] = (LightStatus*)malloc(sizeof(LightStatus) * lightnum);

	long frame_size = 1;


	char ch;
	int line_num = 0;
	while ((ch = fgetc(fp)) != EOF) {
		switch (ch) {
		case '\n':
		case '\r':
			{
				if (line_num < lightnum)
					return NULL; // error format;
				status = (LightStatus**)realloc(status,sizeof(LightStatus*) * (++frame_size));
				status[frame_size - 1] = (LightStatus*)malloc(sizeof(LightStatus) * lightnum);
				line_num = 0;
			}
			break;
		case ',':
		case '\t':
		case ' ':
		case ':':
		case '-':
				continue;
			break;
		case '1':
		case '0':
			{
				if (line_num > lightnum - 1)
					continue; // line content out of lightnum, ignore
				status[frame_size - 1][line_num++] = (ch == '1')?1:0;
			}
			break;
		default:
			continue;
			break;
		}
	}

#ifdef __TEST_LOAD_CHART
	int j,k;
	for (j = 0; j < frame_size - 1; ++j) {
		for (k = 0; k < lightnum; ++k)
			printf("%d\t",status[j][k]);
		printf("\n");
	}
#endif //__TEST_LOAD_CHART

	fclose(fp);

	chart = (str_ltchart*)malloc(sizeof(str_ltchart));
	chart->light_num = lightnum;
	chart->lights = lights;
	chart->light_status = status;
	chart->frame_count = frame_size;

	return chart;
}
