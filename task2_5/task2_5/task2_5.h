#include "stdafx.h"
/*maximum length of color name*/
const int LEN = 10;

struct point
{
	double x;
	double y;
	char color[LEN];
};

/*displays some information about program*/
void Interface();

/*checking entered data and return 0 if type doesn't match requirements*/
unsigned char Type_checking(unsigned char retCode, int val);

/*input coordinates of points into list of points */
unsigned char Input(struct point* points, unsigned int num);

/*checking if string pstr involves only digits*/
unsigned char Is_digit(const char* pstr);

/*sorted list of entered points by color name*/
unsigned char Sort_by_color(struct point* point_list, unsigned int num);

/*displays list of points on display and calls Get distance function*/
unsigned char Output(const struct point* points, unsigned int num);

/*evaluate the distance between points of one color*/
unsigned char Get_distance(const struct point* point, unsigned int begin, unsigned int end);
