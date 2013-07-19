

#include <memory.h>

template <typename T>
class BPNode {
public:
	T *data;
	BPNode<T> *next;
	
	BPNode (T*);
};

template <typename T>
class BPList {
public:
	BPNode<T> *first;
	unsigned long count;

	BPList ();
	BPNode<T> *add (T*);
	BPNode<T> *last ();
	BPNode<T> *get (int);
	T *get_data (int);
	void del (int);
	void del_all ();
};

template <typename T>
BPNode<T>::BPNode (T *data = 0)
{
	this->data = data;
	this->next = 0;
}

template <typename T>
BPList<T>::BPList ()
{
	first = 0;
	count = 0;
}

template <typename T>
BPNode<T> *BPList<T>::add (T *data = 0)
{
	BPNode<T> *last;

	last = this->last ();
	count ++;
	if (last) {
		last->next = new BPNode<T> (data);
		return last->next;
	}
	else {
		this->first = new BPNode<T> (data);
		return this->first;
	}
}

template <typename T>
BPNode<T> *BPList<T>::last ()
{
	BPNode<T> *res;

	res = this->first;
	while (res && res->next) res = res->next;

	return res;
}

/*
	Get(index)
	index - zwischen -1 und count-1
*/

template <typename T>
BPNode<T> *BPList<T>::get (int index)
{
	BPNode<T> *res;

	if (index < 0) return 0;
	
	res = this->first;
	while (index > 0 && res) {
		res = res->next;
		index --;
	}

	return res;
}

template <typename T>
T *BPList<T>::get_data (int index)
{
	return this->get(index)->data;
}

/*
	Del(index)
	index - zwischen 0 und count-1
*/

template <typename T>
void BPList<T>::del (int index)
{
	BPNode<T> *delcand, *prev, *next;

	prev = this->get (index-1);
	if(!prev) return;
	delcand = prev->next;
	if(!delcand) return;
	next = delcand->next;

	if(delcand->data) delete[] delcand->data;
	delete delcand;
	prev->next = next;
	count --;
}

template <typename T>
void BPList<T>::del_all ()
{
	while( count )
		del(count-1);
}

