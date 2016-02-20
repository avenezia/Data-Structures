#ifndef TRIE_TRIE_HPP
#define TRIE_TRIE_HPP

#include <map>
#include "boost/optional.hpp"

namespace trie
{
    /** Class implementing a trie data structure with very good performance characteristics:
     *  - Search hits take time proportional to the length of the search key.
     *  - Search misses involve examining only a few characters. */
    template <typename T>
    class Trie
    {
      public:

        /** It adds iKey in the trie with a corresponding value iValue.
         *  If iKey is already existing, its value will be overwritten.
         *  If iKey is empty, a std::runtime_error exception is thrown.  */
        void addKey(const std::string& iKey, const T& iValue);

        /** If iKey is present with a corresponding value, it deletes it and
         *  returns true. Otherwise the trie is not modified and false is returned. */
        bool deleteKey(const std::string& iKey);

        /** If iKey is present with a corresponding value, it returns the value.
         *  Otherwise a std::runtime_error exception is thrown. */
        const T& getValue(const std::string& iKey) const;

        /** If iKey is present with a corresponding value, it returns true; false otherwise. */
        bool hasKey(const std::string& iKey) const;

        /** If the trie has no value and no children, it returns true; false otherwise. */
        bool isEmpty() const;

      private:
        /** If iKey is present with a corresponding value, a pointer to
         *  the node is returned; a null pointer otherwise. */
        Trie<T>* findKey(const std::string& iKey);

        /** Const version of findKey. */
        const Trie<T>* findKey(const std::string& iKey) const;

        /** Utility method used for deleteKey.
         *  If iKey is present with a corresponding value, a pointer to
         *  the node is returned and oContainer is filled with the nodes from the
         *  root to the last character node. Otherwise a null pointer is returned
         *  and oContainer is not modified. */
        template <typename Container>
        Trie<T>* findKeyWithPath(const std::string& iKey, Container& oContainer);

        std::map<char, Trie<T>> _subTrieMap;
        boost::optional<T> _value;

    };
}

#endif
