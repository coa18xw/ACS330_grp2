const char* lookup(int id)
{
	const char *table[2];
	table[0] = "143.167.45.210";
	table[1] = "143.167.47.142";
	if (id>sizeof(table))
	{
		return "error - tag not known";
	}
	return table[id];
}
