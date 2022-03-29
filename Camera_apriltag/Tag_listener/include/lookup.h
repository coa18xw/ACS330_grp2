
const char* lookup(int32_t Id)
{
	int size = 8;
	int id = Id;
	const char* table[size];
	table[0] = "Base";
	table[1] = "143.167.45.210";
	table[2] = "143.167.47.142";
	table[3] = "Base";
	table[4] = "143.167.45.210";
	table[5] = "143.167.47.142";
	table[6] = "6_Ip";
	table[7] = "143.167.45.210";
	table[8] = "143.167.47.142";
	if (id>size)
	{
		return "error - tag not known";
	}
	return table[id];
}
