#include <iostream>
#include <memory>
#include <exception>

using namespace std;

template <class T>
class Buf_1
{
public:
	Buf_1();
	explicit Buf_1(int); // параметризированный конструктор для указания размера кольца буфера

	void AddData(const T&);
	T GetData();
	int GetSize() const;

private:

	struct Node
	{
		Node(const T& data, const shared_ptr<Node>& next = nullptr) {
			this->data = data;
			this->next = next;
		}

		T data;
		shared_ptr<Node> next;
	};

	bool circle = 0; //флаг означающий, что цикл замкнулся
	int size = 0;
	int maxSize;
	shared_ptr<Node> head = nullptr;
	shared_ptr<Node> tail = nullptr;

	void popData();
};

template<class T>
Buf_1<T>::Buf_1()
{
	maxSize = 10;
}

template<class T>
Buf_1<T>::Buf_1(int maxSize)
{
	this->maxSize = maxSize;
}

template<class T>
void Buf_1<T>::AddData(const T& data)
{
	if (circle == false)
	{
		auto node = make_shared<Node>(data);

		if (tail == nullptr)
		{
			tail = node;
			head = tail;
		}
		else
		{
			tail->next = node;
			tail = node;
		}
		++size;
		if (size == maxSize)
		{
			circle = true;
		}
	}
	else
	{
		if (tail->next == nullptr)
		{
			tail->next = head;
			tail = head;
			tail->data = data;
			head = head->next;
		}
		else
		{
			tail = tail->next;
			tail->data = data;
			if (tail == head) //если хвост переписал значение головы, то сдвинуть указатель головы на следующий элемент
			{
				head = head->next;
			}
		}
		if (size < maxSize)
		{
			++size;
		}
	}
}

template<class T>
T Buf_1<T>::GetData()
{
	if (size == 0)
	{
		throw out_of_range("buf empty");
	}
	else
	{
		T temp = head->data;
		popData();
		return temp;
	}

}

template<class T>
int Buf_1<T>::GetSize() const
{
	return size;
}

template<class T>
void Buf_1<T>::popData()
{
	head = head->next;
	--size;
}

int main() {

	Buf_1<int> b; // maxSize == 10

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

	Buf_1<int> a{ 15 }; //maxSize == 15

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
