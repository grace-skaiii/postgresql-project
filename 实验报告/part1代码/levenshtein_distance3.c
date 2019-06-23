Datum levenshtein_distance3(PG_FUNCTION_ARGS)
{
	text * str_01 = PG_GETARG_DATUM(0);
	text *txt_02 = PG_GETARG_DATUM(1);
	int32 result=1;
	
	char* s1=TextDatumGetCString(str_01);
	char* s2=TextDatumGetCString(txt_02);
	int l1 = strlen(s1), l2 = strlen(s2);
	static int d[101];
	for (int i = 0; i < l1+1; i++)
		d[i] = i;//预处理，与二维数组中预处理作用相同
	for (int j = 1; j < l2+1; j++) {
		int pre = d[0];//保存d[i-1][j-1]
		d[0] = j; //预处理      
		for (int i = 1; i < l1+1; i++) {
			int temp = d[i];//记住当前d[i]，因为这就是下一次循环中的d[i-1][j-1]
			if (s1[i - 1] == s2[j - 1])
				d[i] = pre;
			else d[i] = min(pre + 1, min(d[i] + 1, d[i - 1] + 1));   
			pre = temp;
		}
	}
	result=d[l1];
	PG_RETURN_INT32(result);
}
