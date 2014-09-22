/* To do list:
 * Make more robust, i.e. add error checking
 * Add functions to for modifying elements
*/

#include <iostream>

// Doubly linked list node
template <typename T>
class DNode
{
private:
	T data; // Data
	DNode<T>* next; // Pointer to next node in linked list
	DNode<T>* prev; // Pointer to previous node in linked list
	template<typename T>
	friend class DLinkedList; // Give access to DLinkedList
};

// Doubly linked list
template <typename T>
class DLinkedList
{
public:
	DLinkedList();
	~DLinkedList();
	bool empty() const; // Checks if list is empty
	const T& return_front() const; // Returns the front element in linked list
	const T& return_back() const; // Returns the back element in linked list
	DNode<T>* return_head() const; // Returns pointer to head of linked list
	DNode<T>* return_tail() const; // Returns pointer to tail of linked list
	void add_to_front(const T& n); // Add node to front of linked list
	void remove_front(); // Remove node from front of list
	void add_to_back(const T& n); // Add node to back of linked list
	void remove_back(); // Remove node from back of list
	void print_list(); // Prints all the values in linked list
	void search_linked_list(const DNode<T>* ptr, const T& search_value); // Recursively searches linked list
	void search_and_destroy(DNode<T>* ptr, const T& search_value); // Recursively searches linked list and destroys the value when found

private:
	DNode<T>* head;
	DNode<T>* tail;

protected:
	void add(DNode<T>* node, const T& d); // Insert new node before node
	void remove(DNode<T>* node); // Remove selected node
};

// Constructor
template<typename T>
DLinkedList<T>::DLinkedList()
{
	// Initialize head and tail and have them point ot each other
	head = new DNode<T>;
	tail = new DNode<T>;
	head->next = tail;
	tail->prev = head;
}

// Destructor
template<typename T>
DLinkedList<T>::~DLinkedList()
{
	// Remove all elements in linked list and delete head and tail
	while (!empty())
	{
		remove_front();
	}
	delete head;
	delete tail;
}

// Checks if list is empty
template<typename T>
bool DLinkedList<T>::empty() const
{
	return head->next == tail;
}

// Returns the front element in linked list
template<typename T>
const T& DLinkedList<T>::return_front() const
{
	return head->next->data;
}

// Returns the back element in linked list
template<typename T>
const T& DLinkedList<T>::return_back() const
{
	return tail->prev->data;
}

// Returns pointer to head of linked list
template<typename T>
DNode<T>* DLinkedList<T>::return_head() const
{
	return head;
}

// Returns pointer to tail of linked list
template<typename T>
DNode<T>* DLinkedList<T>::return_tail() const
{
	return tail;
}

// Adds element to front of linked list
template<typename T>
void DLinkedList<T>::add_to_front(const T& n)
{
	add(head->next, n);
}

// Remove node from front of list
template<typename T>
void DLinkedList<T>::remove_front()
{
	remove(head->next);
}

// Adds element to back of linked list
template<typename T>
void DLinkedList<T>::add_to_back(const T& n)
{
	add(tail, n);
}

// Remove node from back of list
template<typename T>
void DLinkedList<T>::remove_back()
{
	remove(tail->prev);
}

template<typename T>
void DLinkedList<T>::print_list()
{
	DNode<T>* tn = head->next;
	while (tn != tail)
	{
		std::cout << tn->data << " ";
		tn = tn->next;
	}
	std::cout << std::endl;
}

// Recursively searches linked list
template<typename T>
void DLinkedList<T>::search_linked_list(const DNode<T>* ptr, const T& search_value)
{
	if (ptr == tail)
	{
		std::cout << search_value << " was not found in the list." << std::endl;
	}
	else if (ptr->data == search_value)
	{
		std::cout << search_value << " was found in the list." << std::endl;
	}
	else
	{
		search_linked_list(ptr->next, search_value);
	}
}

// Recursively searches linked list and destroys the value when found
template<typename T>
void DLinkedList<T>::search_and_destroy(DNode<T>* ptr, const T& search_value)
{
	if (ptr == tail)
	{
		std::cout << search_value << " was not found in the list." << std::endl;
	}
	else if (ptr->data == search_value)
	{
		std::cout << search_value << " was found in the list. " << std::endl;
		remove(ptr); // Remove node
		std::cout << search_value << " has been destroyed." << std::endl;
	}
	else
	{
		search_and_destroy(ptr->next, search_value);
	}
}

// Insert new node before node
template<typename T>
void DLinkedList<T>::add(DNode<T>* node, const T& d)
{
	DNode<T>* nn = new DNode<T>; // Create a new node to hold d
	nn->data = d; 
	nn->prev = node->prev; // Link new node to node before current node
	nn->next = node; // Link new node to current node
	node->prev = nn; // Link current node to new node
	nn->prev->next = nn; // Link previous node to new node
}

// Remove selected node
template<typename T>
void DLinkedList<T>::remove(DNode<T>* node)
{
	DNode<T>* predecessor = node->prev; // Save predecessor
	DNode<T>* successor = node->next; // Save successor
	predecessor->next = successor; // Unlink node from list
	successor->prev = predecessor;
	delete node; // Bye bye
}

int main()
{
	// Testing with ints
	std::cout << "A doubly linked list has been created...\n" << std::endl;
	DLinkedList<int> dllint;
	std::cout << "Checking if doubly linked list is empty..." << std::endl;
	if (dllint.empty())
	{
		std::cout << "Doubly linked list has no values...\n" << std::endl;
	}

	std::cout << "Generating values for doubly linked list..." << std::endl;
	std::cout << "Linked List:" << std::endl;
	for (size_t i = 10; i > 0; i--)
	{
		dllint.add_to_front(i);
	}
	dllint.print_list();
	std::cout << "\n";

	std::cout << "The first element in the doubly linked list is " << dllint.return_front() << "." << std::endl;
	std::cout << "Removing the first element in doubly linked list..." << std::endl;
	dllint.remove_front();
	std::cout << "Linked List:" << std::endl;
	dllint.print_list();
	std::cout << "\n";

	std::cout << "The back element in the doubly linked list is " << dllint.return_back() << "." << std::endl;
	std::cout << "Removing the back element in doubly linked list..." << std::endl;
	dllint.remove_back();
	std::cout << "Linked List:" << std::endl;
	dllint.print_list();
	std::cout << "\n";

	std::cout << "Searching for the value 1 in linked list... ";
	dllint.search_linked_list(dllint.return_head(), 1);
	std::cout << "Searching for the value 8 in linked list... ";
	dllint.search_linked_list(dllint.return_head(), 8);
	std::cout << "Searching for the value 21 in linked list... ";
	dllint.search_linked_list(dllint.return_head(), 21);
	std::cout << "\n" << std::endl;

	std::cout << "Activating search and destroy protocol... " << std::endl;
	std::cout << "Searching for the value 6 in linked list... ";
	dllint.search_and_destroy(dllint.return_head(), 6);
	std::cout << "Linked List:" << std::endl;
	dllint.print_list();
	std::cout << "\n";



	// Testing with chars 
	std::cout << "A doubly linked list has been created...\n" << std::endl;
	DLinkedList<char> dllchar;
	std::cout << "Checking if doubly linked list is empty..." << std::endl;
	if (dllchar.empty())
	{
		std::cout << "Doubly linked list has no values...\n" << std::endl;
	}

	std::cout << "Generating values for doubly linked list..." << std::endl;
	std::cout << "Linked List:" << std::endl;
	char values[] = { 'u', 'o', 'i', 'e', 'a' };
	for (auto &c : values)
	{
		dllchar.add_to_front(c);
	}
	dllchar.print_list();
	std::cout << "\n";

	std::cout << "The first element in the doubly linked list is " << dllchar.return_front() << "." << std::endl;
	std::cout << "Removing the first element in doubly linked list..." << std::endl;
	dllchar.remove_front();
	std::cout << "Linked List:" << std::endl;
	dllchar.print_list();
	std::cout << "\n";

	std::cout << "The back element in the doubly linked list is " << dllchar.return_back() << "." << std::endl;
	std::cout << "Removing the back element in doubly linked list..." << std::endl;
	dllchar.remove_back();
	std::cout << "Linked List:" << std::endl;
	dllchar.print_list();
	std::cout << "\n";

	std::cout << "Searching for the character b in linked list... ";
	dllchar.search_linked_list(dllchar.return_head(), 'b');
	std::cout << "Searching for the character i in linked list... ";
	dllchar.search_linked_list(dllchar.return_head(), 'i');
	std::cout << "Searching for the character z in linked list... ";
	dllchar.search_linked_list(dllchar.return_head(), 'z');
	std::cout << "\n" << std::endl;

	std::cout << "Activating search and destroy protocol... " << std::endl;
	std::cout << "Searching for the character i in linked list... ";
	dllchar.search_and_destroy(dllchar.return_head(), 'i');
	std::cout << "Linked List:" << std::endl;
	dllchar.print_list();
	std::cout << "\n";
}