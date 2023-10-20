#ifndef GRAPHIC_MATH_H
#define GRAPHIC_MATH_H


union v2;
union v3; 
v2 V2(double X, double Y);
v2 V2(double Arg);
v2 operator+ (v2 A, v2 B);
v2 operator* (v2 A, v2 B);
v2 operator* (double A, v2 B);
v2 operator/ (v2 A, double B);
v3 V3(double X, double Y, double Z);
v3 operator+(v3 A, v3 B);

union v2
{
	struct 
	{
		double x, y;
	};

	double e[2];
};

union v3
{
	struct 
	{
		double x, y, z;
	};

	struct 
	{
		v2 xy;
		double Ignored0_; 
	};

	double e[3];
};

#endif // !	GRAPHIC_MATH_H
