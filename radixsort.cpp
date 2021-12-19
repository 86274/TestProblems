#include <vector>

int digit(const int& n, const int& k) {
	return (n >> (8 * k) & (256 - 1));
}

void radixsort(int* l, int* r) {

	const int k = 4; //���������� ����������� ����/��������
	const int M = 256; //���������� �������� ������ �����/�������
	++r;
	const int sz = r - l; //������ �������
	vector<int> b(sz); //��������������� ������
	vector<vector<int>> c(4); //������� �������� ������/��������
	for (auto& i : c) {
		i.resize(M);
	}

	//������� �������� �����/�������
	for (int* i = l; i < r; i++) {
		for (int j = 0; j < k; j++)
		{
			c[j][digit(*i, j)]++;
		}
	}

	//���������� ����� ��������
	for (int i = 0; i < k; i++) {
		for (int j = 1; j < M; j++)
		{
			c[i][j] += c[i][j - 1];
		}
	}

	for (int i = 0; i < k; i++) {

		//���������� �� �������� �����/�������
		for (int* j = r - 1; j >= l; j--) {
			b[--c[i][digit(*j, i)]] = *j;
		}

		//����������� �� ���������������� ������� � �����������
		int cur = 0;
		if (i == 3) {

			int* j = l;
			if (b[sz - 1] < 0)
			{
				while (b[cur] > -1)
				{
					++cur;
				}
				while (cur < sz)
				{
					*j = b[cur++];
					++j;
				}
			}

			cur = 0;
			while (j < r)
			{
				*j = b[cur++];
				++j;
			}

		}
		else {
			for (int* j = l; j < r; j++) {
				*j = b[cur++];
			}
		}
	}
}


int main() {

	array<int, 100000> v;

	for (auto& i : v) {
		srand(time(nullptr) + rand());
		i = rand() % 1000000 * -1;
	}

	for (int i = 0; i < 10; i++)
	{
		if (i % 2 == 0)
		{
			srand(time(nullptr) + rand());
			v[i] = rand() % 1000000;
		}
	}

	radixsort(&v[0], &v[v.size() - 1]);
}