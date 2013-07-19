
#include <memory.h>
#include "bplist.h"

template <typename T>
BPList<T>::BPList ()
{
	data = 0;
	next = 0;
	count = 0;
}

template <typename T>
BPList<T> *BPList<T>::add ()
{
	BPList *last;

	last = last ();
	last->next = new BPList ();
	count ++;

	return last->next;
}

template <typename T>
BPList<T> *BPList<T>::add (T *data)
{
	BPList *last;

	last = add ();
	last->data = data;

	return last;
}

template <typename T>
BPList<T> *BPList<T>::last ()
{
	BPList<T> *res;

	res = this;
	while (res->next) res = res->next;

	return res;
}

/*
	Get(index)
	index - zwischen -1 und count-1
*/

template <typename T>
BPList<T> *BPList<T>::get (int index)
{
	BPList<T> *res;

	if(index<-1) return 0;
	for( res = this; res && index>=0; res = res->next, index-- );

	return res;
}

template <typename T>
T *BPList<T>::get_data (int index)
{
	return get(index)->data;
}

/*
	Del(index)
	index - zwischen 0 und count-1
*/

template <typename T>
void BPList<T>::del (int index)
{
	BPList<T> *delcand, *prev, *next;

	prev = get(index-1);
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
	BPList<T> *last;

	while( count )
		del(count-1);
}

