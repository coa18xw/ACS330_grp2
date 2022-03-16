const char* lookup(int32_t id)
{
	const char *table[3];
	table[0] = "Base";
	table[1] = "143.167.45.210";
	table[2] = "143.167.47.142";
	if (id>sizeof(table))
	{
		return "error - tag not known";
	}
	return table[id];
}
