#define ABS(N) ((N<0)?(-N):(N))

float _sineStuff_sin_nick(float xx)
{
	// does not pass frequency test
	float  yy;
	const float  B = 4/PI;
	const float  C = -4/(PI*PI);
	const float  P = 0.224008178776;		//.225
	//0.224008178776
	const float Q = 0.775991821224;

	if (xx < -PI)
		xx += PI + PI;
	if (xx > PI)
		xx -= PI + PI;

	yy = xx * (B + C * ABS(xx));
	yy = yy * (Q + P * ABS(yy));
	return (yy);
}

float _sine_hack22(float xx)
{// same as _sineStuff_sin_nick
	float  yy;
	const float  B = 4/PI;
	const float  C = -4/(PI*PI);
	const float  P = 0.225;

	if (xx < -PI)
		xx += PI + PI;
	//else
	if (xx > PI)
		xx -= PI + PI;

	yy = B * xx + C * xx * ABS(xx);
	yy = P * (yy * ABS(yy)-yy) + yy;
	return (yy);
}

float  _quad_Sine_fast(float xx)
{
    //http://www.mclimatiano.com/faster-sine-approximation-using-quadratic-curve/
    if (xx < -PI)
		xx+= PI + PI;
	else
		if (xx > PI)
			xx -= PI + PI;

	if (xx < 0)
		return xx * (1.273 + 0.405 * xx);
	else
		return xx * (1.273 - 0.405 * xx);
}

float _quad_Sine_accurate(float xx)
{
	//http://www.mclimatiano.com/faster-sine-approximation-using-quadratic-curve/
	const float  B = 1.27323954;//1.2734	4/PI
	const float  C = 0.405284735;	//4/(PI*PI)
	float yy;

	//bring into range of - PI to + PI
	if (xx < -PI)
		xx += PI + PI;
	else
	if (xx > PI)
		xx -= PI + PI;

	if (xx < 0)
	{
			yy = xx * ( B + C * xx );

			if ( yy < 0 )
				yy = yy * ( -0.255 * ( yy + 1 ) + 1 );
			else
				yy = yy * ( 0.255 * ( yy - 1 ) + 1 );
	}
	else
	{
		yy = xx * ( B - C * xx );

			if ( yy < 0 )
				yy = yy * ( -0.255f * ( yy + 1 ) + 1 );
			else
				yy = yy * ( 0.255f * ( yy - 1 ) + 1 );
	}
	return yy;
}

float _sine_Smile(float xx)
{
	//http://devmaster.net/posts/9648/fast-and-accurate-sine-cosine
    //this routine was found by user Smile, don't know where
    //the algorithm comes from
    //pretty fast

	//const float P = 0.224008178776;
    const float P = 0.225;
    const float A = 7.5888;//A = 16 * sqrt(P);
    const float B = 1.634;//B = (1 - P) / sqrt(P);
    float yy = xx / 6.28;

    yy = yy - floor(yy + 0.5);
	//yy = yy - floor(yy + 0.5);
	yy = A * yy * (0.5 - ABS(yy));

	return yy * (B + ABS(yy));
}

//aPackOfWankers
float _aPackOf_fast_sin(float x)
{
    // simplify the range reduction
    // reduce to a -0.5..0.5 range, then apply polynomial directly
    const float P = 0.225; // const float Q = 0.775;

    x = x * M_1_PI;
    int k = (int) floor(x);
    x = x - k;

    float y = (4 - 4 * ABS(x)) * x;

    y = P * (y * ABS(y) - y) + y;

    return (k&1) ? -y : y;
}

float _Dan_Ritchie_sine(float xx)
{
	//Dan_Ritchie
	const float B = 4/PI;
	const float C = -4/(PI*PI);
	const float recip2 = 1 / (PI * 2);
	const float pi2 = PI + PI;

	float yy;

	//convert the input value to a range of 0 to 1
	xx = (xx + PI) * recip2;
	//make it loop
	xx -= (long)(xx-(xx<0));//xx -= (long)(xx-(xx<0));
	//convert back from 0-1 to -pi to +pi.
	xx = (xx * pi2) - PI;

	//original function
	yy = B * xx + C * xx * ABS(xx);
	return (yy);
}

float sineStuff_sin(float xx)
{
	const float  B = 1.27323954;//1.2734	4/PI
	const float  C = 0.405284735;	//4/(PI*PI)
	float yy;

	//bring into range of - PI to + PI
	if (xx < -PI)
		xx += PI + PI;
	else
	if (xx > PI)
		xx -= PI + PI;

	if (xx < 0)
	{
			yy = xx * ( B + C * xx );

			if ( yy < 0 )
				yy = yy * ( -0.255 * ( yy + 1 ) + 1 );
			else
				yy = yy * ( 0.255 * ( yy - 1 ) + 1 );
	}
	else
	{
		yy = xx * ( B - C * xx );

			if ( yy < 0 )
				yy = yy * ( -0.255f * ( yy + 1 ) + 1 );
			else
				yy = yy * ( 0.255f * ( yy - 1 ) + 1 );
	}
	return yy;
}


////////////////////////////////////////////////////////////////////
//               separate callers from algorithms
////////////////////////////////////////////////////////////////////

void sineStuff_sin_nick (void)
{
    // this routine not compatible with frequency yet
	freq = 2.0;// 2.0

	for (x=0; x <= xWidth; x++)
	{
		sinCalc = _sineStuff_sin_nick(x * freq * PI / xWidth);
        YY = ( ( sinCalc + 1.0) * (halfHeight));
        y = (int)  YY;
		plot(x, y);
	}
}

void sine_hack22 (void)
{
    // this routine not compatible with frequency yet
	freq = 2.0;// 2.0

	for (x=0; x <= xWidth; x++)
	{
		sinCalc = _sine_hack22(x * freq * PI / xWidth);
        YY = ( ( sinCalc + 1.0) * (halfHeight));
        y = (int)  YY;
		plot(x, y);
	}
}

void quad_Sine_fast (void)
{
    // this routine not compatible with frequency yet
	freq = 2.0;// 2.0

	for (x=0; x <= xWidth; x++)
	{
		sinCalc = _quad_Sine_fast(x * freq * PI / xWidth);
        YY = ( ( sinCalc + 1.0) * (halfHeight));
        y = (int)  YY;
		plot(x, y);
	}
}

void quad_Sine_accurate (void)
{
    // this routine not compatible with frequency yet
	freq = 2.0;// 2.0

	for (x=0; x <= xWidth; x++)
	{
		sinCalc = _quad_Sine_accurate(x * freq * PI / xWidth);
        YY = ( ( sinCalc + 1.0) * (halfHeight));
        y = (int)  YY;
		plot(x, y);
	}
}

void sine_Smile (void)
{
    // this routine IS compatible with frequency yet
	//freq = 2.0;// 2.0

	for (x=0; x <= xWidth; x++)
	{
		sinCalc = _sine_Smile(x * freq * PI / xWidth);
        YY = ( ( sinCalc + 1.0) * (halfHeight));
        y = (int)  YY;
		plot(x, y);
	}
}

void aPackOf_fast_sin (void)
{
    // this routine IS compatible with frequency yet
	//freq = 4.0;// 2.0

	for (x=0; x <= xWidth; x++)
	{
		sinCalc = _aPackOf_fast_sin(x * freq * PI / xWidth);
        YY = ( ( sinCalc + 1.0) * (halfHeight));
        y = (int)  YY;
		plot(x, y);
	}
}

void Dan_Ritchie_sine (void)
{
    // this routine IS compatible with frequency yet
	//freq = 4.0;// 2.0

	for (x=0; x <= xWidth; x++)
	{
		sinCalc = _Dan_Ritchie_sine(x * freq * PI / xWidth);
        YY = ( ( sinCalc + 1.0) * (halfHeight));
        y = (int)  YY;
		plot(x, y);
	}
}

