
#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdlib.h>

template <class T>
struct ListElement
{
	int prev;
	int next;
	bool used;
	T data;
};

template <class T>
class LinkedList
{
public:
	LinkedList();
	LinkedList(int size);
	~LinkedList();
	bool push(T item);
	T pop();
	T* itemAt(int index);
	T* first();
	T* last();
	T* next();
	int count();
	void pointer(int index);
	void moveToEnd(int index);
	T remove(int index);

private:
	int findItem(int index);
	void freeSlot(int index);

	ListElement<T>* p_storage;
	int count_i;
	int size_i;
	int first_i;
	int last_i;
	int current_i;
};

template <class T>
LinkedList<T>::LinkedList()
{
	LinkedList(10);
}

template <class T>
LinkedList<T>::LinkedList(int size)
{
	p_storage = (ListElement<T>*)malloc(sizeof(struct ListElement<T>) * size);
	size_i = size;
	count_i = 0;
	last_i = 0;
	first_i = 0;

	for (int i = 0; i < size_i; i++)
	{
		p_storage[i].used = false;
	}
}

template <class T>
LinkedList<T>::~LinkedList()
{

}

template <class T>
bool LinkedList<T>::push(T item)
{
	struct ListElement<T> element;

	if (count_i < size_i)
	{
		for (int i = 0; i < size_i; i++)
		{
			if (p_storage[i].used == false)
			{
				element.next = -1;
				element.data = item;
				element.prev = last_i;

				p_storage[last_i].next = i;
				p_storage[i] = element;
				last_i = i;

				if (count_i == 0)
				{
					first_i = i;
				}

				count_i++;
				break;
			}
		}
		return true;
	}
	else
	{
		return false;
	}
}

template <class T>
T LinkedList<T>::pop()
{
	T element;
	element = p_storage[last_i];
	freeSlot(last_i);
	last_i = p_storage[last_i].prev;
	count_i--;
	return element;
}

template <class T>
T* LinkedList<T>::first()
{
	current_i = p_storage[first_i].next;
	return &(p_storage[first_i].data);
}

template <class T>
T* LinkedList<T>::last()
{
	current_i = last_i;
	return &(p_storage[last_i].data);
}

template <class T>
T* LinkedList<T>::next()
{
	if (current_i != -1)
	{
		T* data = &(p_storage[current_i].data);
		current_i = p_storage[current_i].next;
		return data;
	}
	else
	{
		return NULL;
	}
}

template <class T>
int LinkedList<T>::findItem(int index)
{
	int array_pos;
	if (index < count_i)
	{
		array_pos = first_i;
		for (int i = 0; i < index; i++)
		{
			array_pos = p_storage[array_pos].next;
		}
	}
	else
	{
		array_pos = -1;
	}

	return array_pos;
}

template <class T>
T* LinkedList<T>::itemAt(int index)
{
	if (index >= count_i)
	{
		return NULL;
	}
	else
	{
		int array_pos;
		array_pos = findItem(index);

		return &(p_storage[array_pos].data);
	}
}

template <class T>
int LinkedList<T>::count()
{
	return count_i;
}

template <class T>
void LinkedList<T>::pointer(int index)
{
	current_i = index;
}

template<class T>
void LinkedList<T>::moveToEnd(int index)
{
	int array_pos,next,prev;

	array_pos = findItem(index);
	next = p_storage[array_pos].next;
	prev = p_storage[array_pos].prev;

	if (array_pos != last_i)
	{
		if (array_pos == first_i)
		{
			first_i = next;
			p_storage[next].prev = -1;
		}
		else
		{
			p_storage[next].prev = prev;
			p_storage[prev].next = next;
		}
		p_storage[array_pos].prev = last_i;
		p_storage[last_i].next = array_pos;
		p_storage[array_pos].next = -1;
		last_i = array_pos;
	}
}

template <class T>
T LinkedList<T>::remove(int index)
{
	int array_pos,next,prev;
	array_pos = findItem(index);
	next = p_storage[array_pos].next;
	prev = p_storage[array_pos].prev;
	
	if (array_pos == first_i)
	{
		first_i = next;
		p_storage[next].prev = -1;
	}
	else if (array_pos == last_i)
	{
		last_i = prev;
		p_storage[prev].next = -1;
	}
	else
	{
		p_storage[prev].next = next;
		p_storage[next].prev = prev;
	}

	count_i--;
	freeSlot(array_pos);
	return p_storage[array_pos].data;
}

template <class T>
void LinkedList<T>::freeSlot(int index)
{
	p_storage[index].used = false;
	free(p_storage[index].data);
}

#endif //LINKED_LIST_H
