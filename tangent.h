//tangent = sine(x) / cosine(x)

/*
float _cosine (float xx)
{
	return _sine_Smile(xx + PI / 2);
}

void Cosine_smile (void)
{
    // this routine IS compatible with frequency yet
	//freq = 4.0;// 2.0

	for (x=0; x <= xWidth; x++)
	{
		sinCalc = _cosine(x * freq * PI / xWidth);
        YY = ( ( sinCalc + 1.0) * (halfHeight));
        y = (int)YY;
		plot(x, y);
	}
}
*/


float _tangent (float xx)
{
	//return _sine_Smile(xx + PI / 2) / _cosine(xx + PI / 2);
	//float yy;
	//yy = (xx + PI / 2);
	return _sine_Smile(xx)/ _cosine(xx);

}

void Tangent_smile (void)
{
    // this routine IS compatible with frequency yet
	//freq = 4.0;// 2.0

	for (x=0; x <= xWidth; x++)
	{
		sinCalc = _tangent(PI / x);
        YY = ( ( sinCalc + 1.0) * (halfHeight));
        y = (int)YY;
		plot(x, y);
	}
}

