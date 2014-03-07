/**
* @file		task2_5.h
* @brief	header file for task2_5.cpp
			defines data types and prototypes for functions used in task2_5.cpp
*/


#include "stdafx.h"

/*maximum length of color name*/
const int LEN = 10;


/*defines data type for holding coordinates and color name of screen points*/
struct point
{
	double x;
	double y;
	char color[LEN];
};


/**
* @brief				This function displays general information about program to users
* @param	void
* @return	void
*/
void Interface();


/**
* @brief					Checking if data match requirements set to that data types or functions return values

* @param	[in]			unsigned char retCode - return value of other functions for checking functions ended properly
			[in]			int val - number for checking if it's negative or zero
* @return	unsigned char		Return ERROR if data doesn't match requirements
								Return SUCCESS if inputed data match requirements
*/
unsigned char Type_checking(unsigned char retCode, int val);



/**
* @brief					Function for input coordinates and color of screen points
* @param	[in/out]		struct point* points - pointer to array of structures that holds coordinates and color of points
			[in]			unsigned int num - number of points in list
* @return	unsigned char	Return ERROR if pointer to array of structures is NULL
							Return SUCCESS if data was inputed
*/
unsigned char Input(struct point* points, unsigned int num);


/**
* @brief					Function for checking if inputed string involves only digits
* @param	[in]			const char* pstr - pointer to, checking for numbers, string
* @return	unsigned char	Return ERROR if string contains not only numbers
							Return SUCCESS if string contains only numbers
*/
unsigned char Is_digit(const char* pstr);



/**
* @brief					Function sorts screen points by color name
* @param	[in/out]		struct point* points - pointer to array of structures that holds coordinates of points
			[in]			unsigned int num - number of points in list
* @return	unsigned char	Return ERROR if pointer to array of structures  is NULL
							Return SUCCESS if points were sorted
*/
unsigned char Sort_by_color(struct point* points, unsigned int num);




/**
* @brief					Function for displaying list of screen points 
* @param	[in]			const struct point* points - pointer to array of structures that holds coordinates of points
			[in]			unsigned int num - number of points in list
* @return	unsigned char	Return ERROR if pointer to array of structure is NULL
							Return SUCCESS if data was displayed
*/
unsigned char Output(const struct point* points, unsigned int num);



/**
* @brief					Function estimates the distance between screen points of the same color
							and displays it on the screen
* @param	[in]			const struct point* points - pointer to structure that holds coordinates of points
			[in]			unsigned int begin - index of point that stands for beginning of new color 
			[in]			unsigned int end - index of point that stands for ending of color
* @return	unsigned char	Return ERROR if pointer to array of structures is NULL
							Return SUCCESS if distance  was estimated
*/
unsigned char Get_distance(const struct point* points, unsigned int begin, unsigned int end);
