Datum levenshtein_distance2(PG_FUNCTION_ARGS)
{
	text * str_01 = PG_GETARG_DATUM(0);
	text *txt_02 = PG_GETARG_DATUM(1);
	int32 result=1;
	
	char* s1=TextDatumGetCString(str_01);
	char* s2=TextDatumGetCString(txt_02);
	int l1 = strlen(s1), l2 = strlen(s2);
	static int d[101][101];
	for (int i = 0; i < l1+ 1; i++)
	{
		for (int j = 0; j < l2 + 1; j++)
		{
			if (!i)
				d[i][j] = j;
			else if (!j)
				d[i][j] = i;
			else
			{
				int k = ((s1[i-1] == s2[j-1]) ? 0 : 1);
				d[i][j] = min(min(d[i - 1][j] + 1, d[i][j - 1] + 1), d[i - 1][j - 1] + k);
			}
		}
	}
	result=d[l1][l2];
	PG_RETURN_INT32(result);
}
