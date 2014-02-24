#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/*maximum length of color name*/
const int LEN = 10;

struct point
{
	double x;
	double y;
	char color[10];
};

/*checking entered data and return 0 if type doesn't match requirements*/
int Type_checking(int retCode, int val);

/*sorted list of entered points by color name*/
void Sort_by_color(struct point* point_list, int num_of_points);

/*evaluate the distance between points of one color*/
void Get_distance(struct point* point_list, int begin, int end);

int main()
{
	printf("Enter how many points do you want to create: ");
	int retCode, num_of_points;
	retCode = scanf("%i", &num_of_points);
	if (0 == Type_checking(retCode,num_of_points))
	{
		return 0;
	}

	struct point* points_list = (point*)malloc(num_of_points*sizeof(point));
	printf("Enter coordinates of display points in the form of x y. For example, 5 7 \n");

	for (int i = 0; i < num_of_points; i++)
	{
		printf("coordinate of %i display point:   ", i );
		retCode = scanf("%lf %lf", &points_list[i].x, &points_list[i].y);
		if (0 == retCode)
		{
			printf("Type mismatch. Next time please enter decimal coordinate. \n");
			free(points_list);
			return 0;
		}
		printf("color name: ");
		scanf("%s", &points_list[i].color);

	}

	printf("\nPoint list sorted by color name: \n");
	Sort_by_color(points_list, num_of_points);
	char present_color[LEN];
	int begin_color = 0, end_color = 0;
	strcpy(present_color, points_list[0].color);
	printf("%s", points_list[0].color);
	for (int i = 0; i < num_of_points; i++)
	{
		if (0 != strcmp(present_color, points_list[i].color))
		{
			strcpy(present_color, points_list[i].color);
			end_color = i;
			if (1 == (end_color - begin_color))
			{
				printf("Not enough points of this color to evaluate distance.");
			}
			else
			{
				Get_distance(points_list, begin_color, end_color);
			}
			begin_color = i;
			printf("\n%s", points_list[i].color);
		}
			printf("\t %0.2lf \t %0.2lf\n", points_list[i].x, points_list[i].y);
			if (i == (num_of_points - 1))
			{
				end_color = i;
				if (0 == (end_color - begin_color))
				{
					printf("Not enough points of this color to evaluate distance.\n");
				}
				else
				{
					Get_distance(points_list, begin_color, end_color);
				}
			}
			
		
	}
	return 0;
}

int Type_checking(int retCode, int val)
{
	if (0 == retCode)
	{
		printf("Type mismatch.\n");
		return 0;
	}
	if (val < 0)
	{
		printf("The value can not be negative or null.\n");
		return 0;
	}
	return 1;
}

void Sort_by_color(struct point* point_list, int num_of_points)
{
	struct point temp;
	for (int i = 0; i < num_of_points; i++)
	{
		for (int j = i + 1; j < num_of_points; j++)
		{
			if (1 == strcmp((point_list + i)->color, (point_list + j)->color))
			{
				temp = *(point_list + i);
				*(point_list + i) = *(point_list + j);
				*(point_list + j) = temp;
			}
		}
	}
}

void Get_distance(struct point* p, int begin, int end)
{
	double biggest_distan=0;
	double temp;
	int point1=begin, point2=end;
	for (int i = begin; i < end;i++)
	{
		for (int j = i+1; j < end; j++)
		{
			temp = sqrt((p[i].x - p[j].x) * (p[i].x - p[j].x) + (p[i].y - p[j].y) * (p[i].y - p[j].y));
			if (temp > biggest_distan)
			{
				point1 = i; 
				point2 = j;
				biggest_distan = temp;
			}
		}
	}
	printf("\nbiggest distance of %s color is between %i and %i point \n ", p[begin].color, point1+1, point2+1);
	 
}
