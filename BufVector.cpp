#include <iostream>
#include <memory>
#include <exception>
#include <vector>

using namespace std;

template<class T>
class Buf_2
{
public:
	Buf_2();
	explicit Buf_2(const int& maxSize);

	void AddData(const T& data);
	T GetData();
	int GetSize() const;

private:
	int head = 0;
	int tail = 0;
	int size = 0;
	int maxSize;
	vector<T> buf;
};

template<class T>
Buf_2<T>::Buf_2()
{
	maxSize = 10;
	buf.resize(maxSize);
}

template<class T>
Buf_2<T>::Buf_2(const int& maxSize)
{
	this->maxSize = maxSize;
	buf.resize(maxSize);
}

template<class T>
void Buf_2<T>::AddData(const T& data)
{
	if (size == 0)
	{
		buf[head] = data;
		++size;
	}
	else
	{
		++tail;
		if (tail == maxSize)
		{
			tail = 0;
		}
		buf[tail] = data;
		if (tail == head)
		{
			++head;
			if (head == maxSize)
			{
				head = 0;
			}
		}
		if (size < maxSize)
		{
			++size;
		}
	}
}

template<class T>
T Buf_2<T>::GetData()
{
	T temp = buf[head];
	++head;
	if (head == maxSize)
	{
		head = 0;
	}
	--size;
	return temp;
}

template<class T>
int Buf_2<T>::GetSize() const
{
	return size;
}

int main() {


	Buf_2<int> b;

	for (int i = 0; i < 15; i++)
	{
		b.AddData(i);
	}

	int size = b.GetSize();
	for (int i = 0; i < size - 5; i++)
	{
		cout << b.GetData() << " ";
	}
	cout << endl;

	for (int i = 0; i < 1000; i++)
	{
		b.AddData(i);
	}

	size = b.GetSize();
	for (int i = 0; i < size; i++)
	{
		cout << b.GetData() << " ";
	}
	cout << endl;

	Buf_2<int> a{ 15 };

	for (int i = 0; i < 15; i++)
	{
		a.AddData(i);
	}

	size = a.GetSize();
	for (int i = 0; i < size - 5; i++)
	{
		cout << a.GetData() << " ";
	}

	cout << endl;
	for (int i = 0; i < 1000; i++)
	{
		a.AddData(i);
	}

	size = a.GetSize();
	for (int i = 0; i < size; i++)
	{
		cout << a.GetData() << " ";
	}

}