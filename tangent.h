#ifndef TANGENT_H
#define TANGENT_H
//tangent = sine(x) / cosine(x)

float _Smiletangent (float xx)
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
		sinCalc = _Smiletangent((x * PI) / (xWidth - freq));

		if (sinCalc > freq)
            sinCalc = freq;
        if (sinCalc < -freq)
            sinCalc = -freq;

        sinCalc += freq;

        YY = sinCalc / (freq + freq) * yHeight;

        y = (int)YY;
		plot(x, y);
	}
}

#endif
//leave blank line after

