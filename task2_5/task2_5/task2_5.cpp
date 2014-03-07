
/**
* @file		task2_5.cpp
* @brief	Program creates list of screen points. Points consist of two coordinates and name of color
			Progran sorts points by color name and estimates the biggest distance between points of same color
*
* Copyright 2014 by Yuliia Lyubchik
*
* This software is the confidential and proprietary information
* of Yuliia Lyubchik. ("Confidential Information").  You
* shall not disclose such Confidential Information and shall use
* it only with permission from Yuliia.
*/

#include "stdafx.h"
#include "task2_5.h"	/*defines data types and prototypes of used in this file functions*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


const int FIELDS = 2;	/*number of point coordinates */

const unsigned char ERROR = 0;
const unsigned char SUCCESS = 1;
const unsigned char MAIN_SUCCESS = 0;

int main()
{
	Interface();
	unsigned char retCode;
	unsigned int num;

	do
	{
		printf("Enter integer number of points that you want to create: ");
		retCode = scanf("%u", &num);
		fflush(stdin); // Flush the input buffer
	} while (Type_checking ( retCode, (int) num) == ERROR);

	printf("List will consist of %u point(s).\n", num);


	struct point* points = (point*)  malloc(num * sizeof (point) );
	if (points == NULL)
	{
		printf("Error occurs while trying to allocate memory for list of points. \n");
		return (int)ERROR;
	}
	
	retCode = Input(points, num);
	if (retCode == ERROR)
	{
		free(points);
		return (int)ERROR;
	}

	retCode = Sort_by_color(points, num);
	if (retCode == ERROR)
	{
		free(points);
		return (int)ERROR;
	}
	
	printf("\nPoint's list sorted by color name: \n");

	retCode = Output(points, num);
	if (retCode == ERROR)
	{
		free(points);
		return (int) ERROR;
	}

	free(points);
	system("pause");
	return MAIN_SUCCESS;
}


void Interface()
{
	printf("---------------------------------------------------------------------------\n");
	printf("Hi! Please welcome to your display points handler.\n");
	printf("You can store list of color points.\n");
	printf("Program will sort your list \n and define for you smallest distance between two points of the same color.\n");
	printf("Program made by Yuliia Lyubchik;)\n");
	printf("---------------------------------------------------------------------------\n");
}


unsigned char Type_checking(unsigned char retCode, int val)
{
	if (retCode == ERROR)
	{
		printf("Type mismatch. Please next time check the number.\n");
		return ERROR;
	}
	if (val <= 0)
	{
		printf("The value can not be negative or zero.\n");
		return ERROR;
	}
	return SUCCESS;
}



unsigned char Input(struct point* points, unsigned int num)
{
	if (points == NULL)
	{
		printf("Error occurs while trying to get access to memory to input data.\n");
		return ERROR;
	}
	printf("Enter coordinates of points separated by comma \n(in the form of x,y): \n");
	char temp[20];
	char* token;
	unsigned int i, coord_count ;
	float temp_num[FIELDS];
	for (i = 0; i < num; ++i)
	{
		coord_count = 0;
		printf("coordinate of %i point:   ", i + 1);
		scanf("%s", &temp);
		fflush(stdin); // Flush the input buffer
		token = strtok(temp, ",");

		while (token != NULL && coord_count < FIELDS)
		{
			if (Is_digit(token) == ERROR)
			{
				printf("Type mismatch.\nNext time please check if you entered float or integer numbers \n");
				fflush(stdin);
				break;
			}
			temp_num[coord_count] = atof(token);

			token = strtok(NULL, ",");
			coord_count++;
		}
		if (coord_count != FIELDS)
		{
			printf("Coordinates weren't inputed. \n");
			--i;
			continue;
		}
		points[i].x = temp_num[0];
		points[i].y = temp_num[1];

		
		do 
		{
			printf("color name: ");
			gets(points[i].color);
		} while (strlen(points[i].color) == 0);
		
	}
	return SUCCESS;
}


unsigned char Is_digit(const char* pstr)
{
	if (pstr == NULL)
	{
		return ERROR;
	}
	unsigned int i;
	unsigned char krapka = 0;
	for (i = 0; i < strlen(pstr); ++i)
	{
		if (i == 0)
		{
			if (pstr[i] == '-')
			{
				continue;
			}
		}
		if (pstr[i] >= 48 && pstr[i] <= 57)
		{
			continue;
		}
		else if (pstr[i] == '.')
		{
			if (krapka == 0)
			{
				krapka = 1;
			}
			else
			{
				return ERROR;
			}
		}
		else return ERROR;
	}
	return SUCCESS;
}



unsigned char Sort_by_color(struct point* points, unsigned int num)
{
	if (points == NULL)
	{
		printf("Error occurs while trying to get access to memory to sort database.\n");
		return ERROR;
	}
	struct point temp;
	unsigned int i, j;
	for (i = 0; i < num; ++i)
	{
		for (j = i + 1; j < num; ++j)
		{
			if (1 == strcmp((points + i)->color, (points + j)->color))
			{
				memcpy(&temp, points + j, sizeof(point));
				memcpy(points + j, points + i, sizeof(point));
				memcpy(points + i, &temp, sizeof(point));
			}
		}
	}
	return SUCCESS;
}



unsigned char Output(const struct point* points, unsigned int num)
{
	if (points == NULL)
	{
		printf("Error occurs while trying to get access to memory to display data.\n");
		return ERROR;
	}
	char present_color[LEN];
	unsigned int begin_color = 0, end_color = 0;
	unsigned int i, j;
	strcpy(present_color, points[0].color);
	printf("%s", points[0].color);
	for (i = 0; i < num; ++i)
	{
		if (0 != strcmp(present_color, points[i].color))
		{
			strcpy(present_color, points[i].color);
			end_color = i;
			if (1 == (end_color - begin_color))
			{
				printf("Not enough points of this color to evaluate distance.\n");
			}
			else
			{
				Get_distance(points, begin_color, end_color);
			}
			begin_color = i;
			printf("\n%s", points[i].color);
		}
		printf("\t %0.2lf \t %0.2lf\n", points[i].x, points[i].y);
		if (i == (num - 1))
		{
			end_color = i;
			if (0 == (end_color - begin_color))
			{
				printf("Not enough points of this color to evaluate distance.\n");
			}
			else
			{
				Get_distance(points, begin_color, end_color);
			}
		}
	}
	return SUCCESS;
}



unsigned char Get_distance(const struct point* p, unsigned int begin, unsigned int end)
{
	if (p == NULL)
	{
		printf("Error occurs while trying to get access to memory to provide estimation of distance.\n");
		return ERROR;
	}
	double biggest_distan = 0;
	double temp;
	unsigned int i, j;
	unsigned int point1 = begin, point2 = end;
	for (i = begin; i < end; ++i)
	{
		for (j = i+1; j < end; ++j)
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

	return SUCCESS; 
}
