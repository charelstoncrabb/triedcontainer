# triedcontainer
Implements a templated trie-like container, where the first template arg is a hashable data type, and the second is the data stored at the tree nodes

Example usage:
```
char my_str[] = "foobar"
size_t str_len = 6;
double my_dbl = 3.1415926;

TriedContainer<char,double> trie;

cout << (trie.insert(my_str,str_len,my_dbl) ? "true" : "false") << endl;
trie.erase(my_str,str_len);
cout << "trie.size() = " << trie.size() << endl;
```
This snippet will produce the following output:
```
true
0
