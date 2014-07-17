#ifndef _H_WPJGEOMETRYEX
#define _H_WPJGEPMETRYEX

#define MATH_PI		3.14159265358979323846
#define MATH_PI_2	1.57079632679489661923
#define MATH_PI_4	0.785398163397448309616

/**
 *	Degree & Radian Operations
 */

//	change radian to (- MATH_PI * 2, MATH_PI * 2)
#define rad_np360(rad) (fmodf((rad), MATH_PI * 2))

//	change radian to [0, MATH_PI * 2)
#define rad_std(rad) ((rad > 0) ? (rad_np360(rad)) : ((rad_np360(rad)) + MATH_PI * 2))

//	change degree to radian
#define deg_to_rad(deg) ((deg) / 180.0 * MATH_PI) 

//	change degree to [0, MATH_PI * 2)
#define deg_std(deg) (rad_std(deg_to_rad(deg)))

#endif