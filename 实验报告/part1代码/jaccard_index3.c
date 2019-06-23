Datum jaccard_index3 (PG_FUNCTION_ARGS)
{
	text *str_01 = PG_GETARG_DATUM(0);
	text *txt_02 = PG_GETARG_DATUM(1);
	float4 result=1;

	char* s1=TextDatumGetCString(str_01);
	char* s2=TextDatumGetCString(txt_02);
	char flag[MAX];
	memset(flag, '\0', sizeof(flag));
	int l1 = strlen(s1), l2 = strlen(s2);
	int inter, _union;
	inter = _union = 0;
	for (int i = 0; i < l1 + 1; i++)
	{
		char s[2];
		if (i == 0)
			s[0] = '$';
		else
			s[0] = toupper(s1[i - 1]);
		if (i == l1)
			s[1] = '$';
		else
			s[1] = s1[i];
		int temp = (toupper(s[0]) << 7) | toupper(s[1]);
		if (flag[temp] == '\0')
		{
			_union++;
			flag[temp] = 'y';
		}
	}
	for (int i = 0; i < l2 + 1; i++)
	{
		char s[2];
		if (i == 0)
			s[0] = '$';
		else
			s[0] = s2[i - 1];
		if (i == l2)
			s[1] = '$';
		else
			s[1] = s2[i];
		int temp = (toupper(s[0]) << 7) | toupper(s[1]);
		if (flag[temp] == '\0')
		{
			_union++;
			flag[temp] = 'n';
		}
		else if (flag[temp] == 'y')
		{
			inter++;
			flag[temp] = 'n';
		}
	}
	result=((float)inter)/_union;
	PG_RETURN_FLOAT4(result);
}
