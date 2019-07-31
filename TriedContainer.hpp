

#ifndef __TRIE_TPP__
#define __TRIE_TPP__

// Forward declaration for TrieNode definition
template<class Hashable, class DataType>
class TriedContainer;


// T must be hashable
template<class Hashable = char, class DataType = int>
class TrieNode
{
public:
	TrieNode() : datum(NULL) {}
	TrieNode(DataType init_datum) : datum(new DataType(init_datum)) {}
	~TrieNode() {if (datum != NULL) delete datum;}

	DataType get_datum(void) const
	{
		return *datum;
	}
private:
	DataType* datum;
	std::map<Hashable,TrieNode<Hashable,DataType>*> children;

	friend class TriedContainer<Hashable,DataType>;
};


/*
	Trie class data structure puts arrays of (hashable) data
	types T (e.g., char) into a trie tree structure
	T must be hashable
	The nodes may also contain a data point so that the data
	structure is a templated container, but structured as 
	a trie with hashables
*/
template<class Hashable = char, class DataType = int>
class TriedContainer
{
public:
	TriedContainer()
	{
		root = new TrieNode<Hashable,DataType>();
	}

	/*
		Search trie for provided data array
		Returns true if data array is in trie
		If found, datum is replaced with leaf datum
	*/
	bool find(
		const Hashable* search_array,
		const size_t array_len,
		DataType& datum)
	{
		return _find(root,search_array,array_len,datum);
	}

	/*
		Inserts new data array into trie
		Returns true if insert is successful
	*/
	bool insert(
		const Hashable* new_array, 
		const size_t array_len, 
		const DataType datum)
	{
		return _insert(root,new_array,array_len,datum);
	}

	/*
		Erases provided data array from trie
		Returns true if erase is successful
	*/
	bool erase(
		const Hashable* array, 
		const size_t array_len)
	{
		size_t array_len_copy = array_len;
		return _erase(root,array,array_len_copy);
	}

	/*
		Updates the datum point associated
		with the provided hashable array
		Returns true if update is successful
	*/
	bool set_datum(
		const Hashable* array,
		const size_t array_len,
		const DataType new_datum)
	{
		DataType datum;
		if (_find(root,array,array_len,datum))
		{
			// TODO
			return true;
		}
		return false;
	}

	/*
		Return size of trie
	*/
	size_t size(void){return _size;}

private:
	// Private helpers for recursion
	bool _find(
		TrieNode<Hashable,DataType>* root, 
		const Hashable* array, 
		const size_t array_len,
		DataType& datum)
	{
		if (array_len == 0) return true;
		if (root->children.find(array[0]) == root->children.end()) 
			return false;
		datum = root->children[array[0]]->get_datum();
		return _find(root->children[array[0]],array+1,array_len-1,datum);
	}

	bool _insert(
		TrieNode<Hashable,DataType>* root, 
		const Hashable* array, 
		const size_t array_len,
		const DataType datum)
	{
		if (array_len == 0) return true;
		if (root->children.find(array[0]) == root->children.end())
		{
			root->children[array[0]] 
				= new TrieNode<Hashable,DataType>(datum);
			_size++;
		}
		return _insert(root->children[array[0]],array+1,array_len-1,datum);
	}

	bool _erase(
		TrieNode<Hashable,DataType>* root, 
		const Hashable* array, 
		size_t& array_len)
	{
		bool ans = true;
		if (array_len == 0) return ans;
		if (root->children.find(array[0]) == root->children.end()) return false;
		if (array_len > 1)
		{
			array_len--;
			ans = _erase(root->children[array[0]],array+1,array_len);
			array_len++;
		}
		if (array_len == 1)
		{
			delete root->children[array[0]];
			root->children.erase(array[0]);
			_size--;
			if (root->children.empty()) array_len--;
		}
		return ans;
	}

	// Data members:
	TrieNode<Hashable,DataType>* root;
	size_t _size;
};

#endif
