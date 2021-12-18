1. bool isEven_1(const int& value) {
	if (value & 1)
		return 0;
	else
		return 1;

}

bool isEven_2(const int& value) {
	int x = value / 2;
	if (value - (x + x))
		return 0;
	else
		return 1;
}
