#pragma once

#ifndef _FLOATCMP
#define _FLOATCMP


// Includes

#include <float.h>
#include <math.h>
#include <stdbool.h>


// Macros

typedef long double floatEP;


// Functions

bool FloatEP_ApproxEqual(floatEP _first, floatEP _second)
{
	//Implementation influenced by: https://floating-point-gui.de/errors/comparison/, https://randomascii.wordpress.com/2012/02/25/comparing-floating-point-numbers-2012-edition/

	floatEP firstAbs  = fabsl(_first          ),
	        secondAbs = fabsl(_second         ),
	        diffAbs   = fabsl(_first - _second) ;

	bool ExactlyEqual,
		 CloseToZero  ;

	ExactlyEqual = (_first == _second                                      );
    CloseToZero  = (_first == 0       || _second == 0 || diffAbs < LDBL_MIN);

	if (ExactlyEqual)       //Handles infinites
	{
		return true;
	}
	else if (CloseToZero)   //Close to zero
	{
		return (diffAbs < (LDBL_EPSILON * LDBL_EPSILON));
	}
	else                    //Relative Error
	{
		return (diffAbs / fminl(firstAbs + secondAbs, LDBL_MAX) < LDBL_EPSILON);
	}
}

bool FloatEP_ApproxGreater(floatEP _first, floatEP _second)
{
	//Implementation influenced by: https://floating-point-gui.de/errors/comparison/, https://randomascii.wordpress.com/2012/02/25/comparing-floating-point-numbers-2012-edition/

	floatEP firstAbs  = fabsl(_first )      ,
		    secondAbs = fabsl(_second)      ,
		    diff      = firstAbs - secondAbs ;

	bool ExactlyEqual,
		 CloseToZero  ;

	ExactlyEqual = (_first == _second                                          );
	CloseToZero  = (_first == 0       || _second == 0 || fabsl(diff) < LDBL_MIN);

	if (CloseToZero)   //Close to zero
	{
		return (diff > (LDBL_EPSILON * LDBL_MIN)) && !signbit(diff);
	}
	else               //Relative Error
	{
		return (diff / fminl(firstAbs + secondAbs, LDBL_MAX) > LDBL_EPSILON) && !signbit(diff);
	}
}

bool FloatEP_ApproxLess(floatEP _first, floatEP _second)
{
	//Implementation influenced by: https://floating-point-gui.de/errors/comparison/, https://randomascii.wordpress.com/2012/02/25/comparing-floating-point-numbers-2012-edition/

	floatEP firstAbs  = fabsl(_first )        ,
	        secondAbs = fabsl(_second)        ,
		    diff      = firstAbs - secondAbs   ;

	bool ExactlyEqual,
		 CloseToZero  ;

	ExactlyEqual = (_first == _second                                          );
	CloseToZero  = (_first == 0       || _second == 0 || fabsl(diff) < LDBL_MIN);

	if (CloseToZero)   //Close to zero
	{
		return (diff > (LDBL_EPSILON * LDBL_MIN)) && signbit(diff);
	}
	else               //Relative Error
	{
		return (diff / fminl(firstAbs + secondAbs, LDBL_MIN) > LDBL_EPSILON) && signbit(diff);
	}
}


#endif _FLOATCMP