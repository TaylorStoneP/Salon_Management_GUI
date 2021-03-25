#ifndef LLIST_H
#define LLIST_H
#include <iostream>
#include <string>
//Linked List Template Library.
//v.1.0.0
//Author: Taylor Phillips - taylorstone.p@gmail.com
//Date: 24/03/2021
//Description:
//	A linked list templated library capable of dynamically allocated arrays of any type.
//  Capable of handling nested linked lists.
//Requisits:
//	- If program calls llist<type>.to_string(), <type> must have to_string() member function.
//	  Unless <type> is primitive or std::string.
//Potential Work: 
//	- Increase functionality of member functions.
//	- Add bound guards and invalid return types


using std::to_string;

//Linked List template class
template<typename sub_type>
class llist
{
	struct llist_node
	{
		sub_type m_data;
		llist_node* m_prev;
		llist_node* m_next;
		llist_node() :m_data(), m_prev(nullptr), m_next(nullptr) {}
		llist_node(const sub_type& data) :m_data(sub_type(data)), m_prev(nullptr), m_next(nullptr){}
	};

	int m_count;
	llist_node* m_head;
	llist_node* m_end;

	llist_node* get_pointer_at(int index)const
	{
		if (m_count == 0)
		{
			return nullptr;
		}
		else if(index>-1&&index<m_count)
		{
			llist_node* cur = m_head;
			for (int i = 0; i < index; i++)
			{
				cur = cur->m_next;
			}
			return cur;
		}
		return nullptr;
	}
public:
	llist():m_count(0),m_head(nullptr),m_end(nullptr) {}
	llist(int count) :m_count(0), m_head(nullptr), m_end(nullptr)
	{
		for (int i = 0; i < count; i++)
		{
			add_back();
		}
	}
	~llist() 
	{
		llist_node* cur = m_head;
		m_head = nullptr;
		m_end = nullptr;
		if (m_count != 0)
		{
			for (int i = 1; i < m_count; i++)
			{
				cur = cur->m_next;
				delete cur->m_prev;
			}
			delete cur;
		}
	}

	//Appends data to end of list.
	void add_back()
	{
		if (m_count == 0)
		{
			m_head = new llist_node();
			m_end = m_head;
		}
		else
		{
			m_end->m_next = new llist_node();
			m_end->m_next->m_prev = m_end;
			m_end = m_end->m_next;
		}
		m_count++;
	}
	//Appends data to end of list.
	void add_back(const sub_type& data) 
	{
		if (m_count==0)
		{
			m_head = new llist_node(data);
			m_end = m_head;
		}
		else
		{
			m_end->m_next = new llist_node(data);
			m_end->m_next->m_prev = m_end;
			m_end = m_end->m_next;
		}
		m_count++;
	}
	//Pushes data to start of list.
	void add_front()
	{
		if (m_count == 0)
		{
			m_head = new llist_node();
			m_end = m_head;
		}
		else
		{
			m_head->m_prev = new llist_node();
			m_head->m_prev->m_next = m_head;
			m_head = m_head->m_prev;
		}
		m_count++;
	}
	//Pushes data to start of list.
	void add_front(const sub_type& data)
	{
		if (m_count == 0)
		{
			m_head = new llist_node(data);
			m_end = m_head;
		}
		else
		{
			m_head->m_prev = new llist_node(data);
			m_head->m_prev->m_next = m_head;
			m_head = m_head->m_prev;
		}
		m_count++;
	}

	//Returns data at index.
	sub_type& operator[](int index)const
	{
		return get_pointer_at(index)->m_data;
	}

	//Copies data from RHS to LHS.
	//Size differences irrelevant.
	llist<sub_type>& operator=(const llist<sub_type>& copy)
	{
		if (this == &copy)
			return *this;
		if (m_count == copy.count())
		{
			for (int i = 0; i < m_count; i++)
			{
				get_pointer_at(i)->m_data = copy[i];
			}
		}
		else if (m_count < copy.count())
		{
			for (int i = 0; i < m_count; i++)
			{
				get_pointer_at(i)->m_data = copy[i];
			}
			int count_temp = m_count;
			for (int i = count_temp; i < copy.count(); i++)
			{
				add_back(copy[i]);
			}
		}
		else if (m_count > copy.count())
		{
			for (int i = 0; i < copy.count(); i++)
			{
				get_pointer_at(i)->m_data = copy[i];
			}
			int count_temp = m_count;
			for (int i = copy.count(); i < count_temp; i++)
			{
				remove_at(m_count-1);
			}
		}
		m_count = copy.count();
		return *this;
	}

	//Returns copy of data at index and deletes it from list.
	sub_type pop_at(int index)
	{
		if (index >= 0 && index < m_count)
		{
			llist_node* cur = get_pointer_at(index);
			sub_type data = cur->m_data;
			if (cur != m_head)
				cur->m_prev->m_next = cur->m_next;
			else
				m_head = cur->m_next;
			if (cur != m_end)
				cur->m_next->m_prev = cur->m_prev;
			else
				m_end = cur->m_prev;
			delete cur;
			m_count--;
			return data;
		}
		return sub_type();
	}
	//Deletes node at index from list.
	void remove_at(int index)
	{
		pop_at(index);
	}
	//Inserts data node at index.
	void insert_at(const sub_type& data, int index)
	{
		if (m_count == 0)
		{
			add_back(data);
		}
		else if (index == 0)
		{
			add_front(data);
		}
		else if (index == m_count-1)
		{
			add_back(data);
		}
		else if (index > -1 && index < m_count)
		{
			llist_node* cur = get_pointer_at(index);
			cur->m_prev->m_next = new llist_node(data);
			cur->m_prev = cur->m_prev->m_next;
			m_count++;
		}
	}
	//Searches list for target data.
	//Returns index if found, otherwise -1.
	int search(const sub_type& target)const
	{
		llist_node* cur = m_head;
		for (int i = 0; i < m_count; i++)
		{
			if (cur->m_data == target)
			{
				return i;
			};
			cur = cur->m_next;
		}
		return -1;
	}
	//Returns number of elements in list.
	int count()const { return m_count; }

	//Sorts list in either ascending(true) or descending(false) order.
	//<sub_class> must have operator<() & operator>() overloads.
	void sort(bool ascending = true)
	{
		llist<int> copy;
		int max = m_head->m_data;
		for (int i = 0; i < m_count; i++)
		{
			int min = max;
			for (llist_node* cur = m_head; cur != nullptr; cur = cur->m_next)
			{
				if (cur->m_data < min)
				{
					min = cur->m_data;
					cur->m_data = max;
				}
				else if (cur->m_data > max)
				{
					max = cur->m_data;
				}
			}
			switch (ascending)
			{
			case true:
				copy.add_back(min);
				break;
			case false:
				copy.add_front(min);
				break;
			}
		}
		*this = copy;
	}

	//Returns list as string.
	//<sub_class> must have sub_class.to_string() member function
	//unless sub_class is primitive or std::string.
	std::string to_string()
	{
		std::string out = "";
		for (int i = 0; i < m_count; i++)
			out += get_pointer_at(i)->m_data.to_string() + (i < m_count - 1 ? "\n" : "");
		return out;
	}
};
//Converts standard types to string of list
std::string llist<std::string>::to_string()
{
	std::string out = "";
	for (int i = 0; i < m_count; i++)
		out += get_pointer_at(i)->m_data + (i < m_count - 1 ? ",":"");
	return out;
}
std::string llist<int>::to_string()
{
	std::string out = "";
	for (int i = 0; i < m_count; i++)
		out += std::to_string(get_pointer_at(i)->m_data) + (i < m_count - 1 ? "," : "");
	return out;
}

template<typename sub_class>
using llist_mat2D = llist<llist<sub_class>>;
template<typename sub_class>
using llist_mat3D = llist<llist<llist<sub_class>>>;
template<typename sub_class>																  
using llist_mat4D = llist<llist<llist<llist<sub_class>>>>;									  
template<typename sub_class>																  
using llist_mat5D = llist<llist<llist<llist<llist<sub_class>>>>>;							  
template<typename sub_class>																  
using llist_mat6D = llist<llist<llist<llist<llist<llist<sub_class>>>>>>;					  
template<typename sub_class>																  
using llist_mat7D = llist<llist<llist<llist<llist<llist<llist<sub_class>>>>>>>;				  
template<typename sub_class>																  
using llist_mat8D = llist<llist<llist<llist<llist<llist<llist<llist<sub_class>>>>>>>>;		  


#endif