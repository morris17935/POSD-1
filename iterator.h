#ifndef ITERATOR_H
#define ITERATOR_H

#include "struct.h"
#include "list.h"

class Iterator {
public:
	virtual void first() = 0;
	virtual void next() = 0;
	virtual Term* currentItem() const = 0;
	virtual bool isDone() const = 0;
	virtual Term* the_term_that_itr_ptr() = 0;
};

class NullIterator :public Iterator {
public:
	NullIterator(Term *n) : temp(n) {}
	void first() {}
	void next() {}
	Term * currentItem() const {
		return nullptr;
	}
	bool isDone() const {
		return true;
	}
	Term* the_term_that_itr_ptr() { 
		return temp;
	};
	Term* temp;
};

class StructIterator :public Iterator {
public:
	friend class Struct;
	void first() {
		_index = 0;
	}

	Term* currentItem() const {
		return _s->args(_index);
	}

	bool isDone() const {
		return _index >= _s->arity();
	}

	void next() {
		_index++;
	}
	Term* the_term_that_itr_ptr() {
		return _s;
	};
private:
	StructIterator(Struct *s) : _index(0), _s(s) {}
	int _index;
	Struct* _s;
};

class ListIterator :public Iterator {
public:
	friend class List;

	void first() {
		_index = 0;
	}

	Term* currentItem() const {
		return _list->args(_index);
	}

	bool isDone() const {
		return _index >= _list->arity();
	}

	void next() {
		_index++;
	}
	Term* the_term_that_itr_ptr() {
		return _list;
	};
private:
	ListIterator(List *list) : _index(0), _list(list) {}
	int _index;
	List* _list;
};
template <class Type>
class DFSIterator :public Iterator {
public:
	friend class List;
	friend class Struct;
	void first() {
		_index = 0;
	}

	Term* currentItem() const {
		return dfsstack[dfsstack.size() - 1]->the_term_that_itr_ptr();
	}

	bool isDone() const {
		if (dfsstack.size() == 0)
			return true;
		else
			return false;
	}

	void next() {
		if (dfsstack[dfsstack.size() - 1]->isDone()) {
			while(dfsstack.size() > 0 && dfsstack[dfsstack.size() - 1]->isDone())
				dfsstack.pop_back();
			if (dfsstack.size() > 0) {
				Iterator*temp = dfsstack[dfsstack.size() - 1]->currentItem()->createIterator();
				dfsstack[dfsstack.size() - 1]->next();
				temp->first();
				dfsstack.push_back(temp);
			}
		}
		else if(! dfsstack[dfsstack.size()-1]->isDone()){
			Iterator*temp = dfsstack[dfsstack.size() - 1] ->currentItem()->createIterator();
			dfsstack[dfsstack.size() - 1]->next();
			temp->first();
			dfsstack.push_back(temp);
		}
	}
	Term* the_term_that_itr_ptr() {
		return ptr;
	};
private:
	DFSIterator(Type *tempptr) : _index(0), ptr(tempptr) { 
		Iterator*temp = ptr->createIterator();
		temp->first();
		dfsstack.push_back(temp);
	}
	int _index;
	Type* ptr;
	vector<Iterator*>dfsstack;
};

template <class Type>
class BFSIterator :public Iterator {
public:
	friend class List;
	friend class Struct;
	void first() {
		_index = 0;
	}

	Term* currentItem() const {
		return bfsstack[bfsstack.size() - 1]->the_term_that_itr_ptr();
	}

	bool isDone() const {
		if (bfsstack.size() == 0)
			return true;
		else
			return false;
	}

	void next() {
		if (bfsstack.size() > 0) {
			while (!bfsstack[bfsstack.size() - 1]->isDone()) {
				Iterator*temp = bfsstack[bfsstack.size() - 1]->currentItem()->createIterator();
				bfsstack[bfsstack.size() - 1]->next();
				temp->first();
				vector<Iterator*>::iterator it = bfsstack.begin();
				bfsstack.insert(it, temp);
			}
			bfsstack.pop_back();
		}
	}
	Term* the_term_that_itr_ptr() {
		return ptr;
	};
private:
	BFSIterator(Type *tempptr) : _index(0), ptr(tempptr) {
		Iterator*temp = ptr->createIterator();
		temp->first();
		bfsstack.push_back(temp);
	}
	int _index;
	Type* ptr;
	vector<Iterator*>bfsstack;
};
#endif