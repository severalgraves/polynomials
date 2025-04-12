#pragma once


#include <iostream>
using std::size_t;
using namespace std;

template<typename T>
class Node
{
public:
	T data;
	Node* next;
	Node(T _data = T(), Node* _next = nullptr) : data(_data), next(_next) { }
};

template<typename T>
class List
{
protected:
	Node<T>* first;
	size_t size;
public:
	List()
	{
		first = nullptr;
		size = 0;
	}

	List(Node<T>* first_node)
	{
		first = first_node;
		size = 1;
	}

	List(const List<T>& _list)
	{
		first = nullptr;
		size = 0;
		for (iterator it = _list.begin(); it != _list.end(); ++it)
			push_back(*it);
	}

	void clear()
	{
		while (first != nullptr)
		{
			Node<T>* temp = first;
			first = first->next;
			delete temp;
		}
		size = 0;
	}

	~List()
	{
		this->clear();
	}

	List<T>& operator=(const List<T>& _list)
	{
		if (this != &_list)
		{
			this->clear();
			for (iterator it = _list.begin(); it != _list.end(); ++it)
				push_back(*it);
		}
		return *this;
	}

	Node<T>* get_first() const noexcept { return first; }
	size_t get_size() const noexcept { return size; }

	void push_front(T elem)
	{
		try
		{
			Node<T>* new_node = new Node<T>(elem, first);
			this->first = new_node;
			size++;
		}
		catch (const bad_alloc& m) { cerr << m.what() << '\n'; }
	}

	void pop_front()
	{
		if (first == nullptr)
			throw ("Error");
		Node<T>* temp = first;
		first = temp->next;
		delete temp;
		size--;
	}

	void insert(T elem, Node<T>* node)
	{
		if (node == nullptr)
			push_front(elem);
		else
		{
			try
			{
				Node<T>* new_node = new Node<T>(elem, node->next);
				node->next = new_node;
				size++;
			}
			catch (const bad_alloc& m) { cerr << m.what() << '\n'; }
		}
	}

	void erase(Node<T>* node)
	{
		if (node == nullptr)
			pop_front();
		else
		{
			Node<T>* temp = node->next;
			if (temp != nullptr)
			{
				node->next = temp->next;
				delete temp;
				size--;
			}
			else
				node->next = nullptr;
		}
	}

	Node<T>* get_last()
	{
		if (first == nullptr)
			return nullptr;

		Node<T>* current = first;
		Node<T>* next_node = first->next;

		while (next_node != nullptr)
		{
			current = next_node;
			next_node = next_node->next;
		}
		return current;
	}

	void push_back(T elem)
	{
		this->insert(elem, this->get_last());
	}

	class iterator
	{
		Node<T>* current;

	public:

		iterator(Node<T>* node) : current(node) {}
		iterator(const Node<T>* node) : current(const_cast<Node<T>*>(node)) {}
		iterator(const iterator& it) { current = it.current; }
		Node<T>* get_current() const noexcept { return current; }
		iterator(std::nullptr_t ptr) { current = nullptr; }

		iterator& operator++()
		{
			current = current->next;
			return *this;
		}

		iterator operator++(int)
		{
			iterator tmp = *this;
			++(*this);
			return tmp;
		}

		T& operator*()
		{
			return current->data;
		}

		const T& operator*() const
		{
			return current->data;
		}

		bool operator==(const iterator& it)
		{
			return this->current == it.current;
		}

		const bool operator==(const iterator& it) const
		{
			return this->current == it.current;
		}

		bool operator!=(const iterator& it)
		{
			return !(*this == it);
		}
	};

	iterator begin() noexcept { return iterator(first); }
	iterator end() noexcept { return iterator(nullptr); }
	const iterator begin() const noexcept { return iterator(first); }
	const iterator end() const noexcept { return iterator(nullptr); }
};


class Monom
{
protected:

	size_t degree;
	double c;

public:

	const size_t MAX_DEG = 9;
	Monom(size_t deg = 0, double cf = 0) : degree(deg), c(cf)
	{
		if (deg > 999) throw ("Error");
	};
	size_t x_deg() const noexcept { return degree / 100; }
	size_t y_deg() const noexcept { return (degree / 10) % 10; }
	size_t z_deg() const noexcept { return degree % 10; }
	size_t get_deg() const noexcept { return degree; }
	double get_c() const noexcept { return c; }
	void set_c(const double _c) noexcept { c = _c; }

	bool is_deg_correct() const noexcept{ return (x_deg() <= MAX_DEG && y_deg() <= MAX_DEG && z_deg() <= MAX_DEG);}

	Monom operator+(const Monom& m)
	{
		if (this->degree == m.get_deg())
		{
			Monom res(this->degree, this->c + m.get_c());
			if (res.get_c() == 0)
				return Monom(0, 0);
			return res;
		}
		else throw ("Error");
	}

	Monom operator-(const Monom& m)
	{
		if (this->degree == m.get_deg())
		{
			Monom res(this->degree, this->c - m.get_c());
			if (res.get_c() == 0)
				return Monom(0, 0);
			return res;
		}
		else throw ("Error");
	}

	Monom operator*(const double scal)
	{
		Monom res(this->degree, this->c * scal);
		if (res.get_c() == 0)
			return Monom(0, 0);
		return res;
	}

	Monom operator*(const Monom& m)
	{
		if (this->x_deg() + m.x_deg() <= MAX_DEG && this->y_deg() + m.y_deg() <= MAX_DEG
			&& this->z_deg() + m.z_deg() <= MAX_DEG)
		{
			Monom res(this->degree + m.get_deg(), this->c * m.get_c());
			if (res.get_c() == 0)
				return Monom(0, 0);
			return res;
		}
		else throw ("Error");

	}

};

class Polynom : public List<Monom>
{
public:

	Polynom()
	{
		try
		{
			Monom m;
			Node<Monom>* p = new Node<Monom>(m);
			first = p;
			p->next = nullptr;
		}
		catch (const bad_alloc& mem) { cerr << mem.what() << '\n'; }
	}

	

	Polynom operator+ (const Polynom& p)
	{
		Polynom res;
		iterator it1 = this->begin().get_current()->next;
		iterator it2 = p.begin().get_current()->next;

		while (it1 != this->end() && it2 != p.end())
		{
			if ((*it1).get_deg() == (*it2).get_deg())
			{
				res.push_back(*(it1)+*(it2));
				++it1;
				++it2;
			}
			else if ((*it1).get_deg() > (*it2).get_deg())
			{
				res.push_back(*it1);
				++it1;
			}
			else
			{
				res.push_back(*it2);
				++it2;
			}
		}
		if (it1 == this->end())
		{
			while (it2 != p.end())
			{
				res.push_back(*it2);
				++it2;
			}
		}
		if (it2 == p.end())
		{
			while (it1 != this->end())
			{
				res.push_back(*it1);
				++it1;
			}
		}
		return res;
	}

	Polynom operator* (const double scal)
	{
		Polynom res;
		for (iterator it = this->begin().get_current()->next; it != this->end(); ++it)
			res.push_back((*it) * scal);
		return res;
	}

	Polynom operator* (const Monom& m) const
	{
		Polynom res;
		for (iterator it = this->begin().get_current()->next; it != this->end(); ++it) res.push_back((*it) * m);
		return res;
	}

	Polynom operator* (const Polynom& p)
	{
		Polynom res;
		res.begin().get_current()->next = nullptr;
		iterator it1 = this->begin().get_current()->next;
		while (it1 != this->end())
		{
			res = res + p * (*it1);
			++it1;
		}
		return res;
	}


};