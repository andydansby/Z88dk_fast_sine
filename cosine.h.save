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
