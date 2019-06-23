Datum jaccard_index (PG_FUNCTION_ARGS)
{
	text *str_01 = PG_GETARG_DATUM(0);
	text *txt_02 = PG_GETARG_DATUM(1);
	float4 result=1;

	char* s1=TextDatumGetCString(str_01);
	char* s2=TextDatumGetCString(txt_02);
	int l1 = strlen(s1), l2 = strlen(s2);
    int i = 0, s1_cnt, s2_cnt;
	s1_cnt = s2_cnt = 0;
	char s1_sub[101][2], s2_sub[101][2];
	while (i < l1 + 1)
	{
		if (!i)
		{
			s1_sub[s1_cnt][0] = '$';
			s1_sub[s1_cnt++][1] = toupper(s1[i]);
		}
		else if (i == l1)
		{
			s1_sub[s1_cnt][0] = toupper(s1[i - 1]);
			s1_sub[s1_cnt++][1] = '$';
		}
		else
		{
			int j = 1;
			while (j < s1_cnt)
			{
				if (s1_sub[j][0] == toupper(s1[i - 1]) && s1_sub[j][1] == toupper(s1[i]))
					break;
				else
					j++;
			}
			if (j == s1_cnt)
			{
				s1_sub[s1_cnt][0] = toupper(s1[i - 1]);
				s1_sub[s1_cnt++][1] = toupper(s1[i]);
			}
		}
		i++;
	}
	i = 0;
	while (i < l2 + 1)
	{
		if (!i)
		{
			s2_sub[s2_cnt][0] = '$';
			s2_sub[s2_cnt++][1] = toupper(s2[i]);
		}
		else if (i == l2)
		{
			s2_sub[s2_cnt][0] = toupper(s2[i - 1]);
			s2_sub[s2_cnt++][1] = '$';
		}
		else
		{
			int j = 1;
			while (j < s2_cnt)
			{
				if (s2_sub[j][0] == toupper(s2[i - 1]) && s2_sub[j][1] == toupper(s2[i]))
					break;
				else
					j++;
			}
			if (j == s2_cnt)
			{
				s2_sub[s2_cnt][0] = toupper(s2[i - 1]);
				s2_sub[s2_cnt++][1] = toupper(s2[i]);
			}
		}
		i++;
	}
	int inter_cnt = 0;
	for (i = 0; i < s1_cnt; i++)
	{
		for (int j = 0; j < s2_cnt; j++)
		{
			if (s2_sub[j][0] == s1_sub[i][0] && s2_sub[j][1] == s1_sub[i][1])
			{
				inter_cnt++;
				break;
			}
		}
	}
	int union_cnt = s1_cnt + s2_cnt - inter_cnt;
	result = ((float)inter_cnt) / union_cnt;
	PG_RETURN_FLOAT4(result);
}
