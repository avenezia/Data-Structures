#include "Trie.hpp"

#include <stdexcept>
#include <string>
#include <vector>
using namespace std;

namespace trie
{
    template <typename T>
    void Trie<T>::addKey(const string& iKey, const T& iValue)
    {
        if (iKey.empty())
        {
            throw runtime_error("An empty key cannot be inserted in the trie");
        }
        // Traversing the path from the root to the last character node; in case a specific key
        //  in a map is not yet available, it will be created using operator[] of the map.
        Trie<T>* currentTrie = this;
        for (string::const_iterator keyIterator = iKey.begin(); keyIterator != iKey.end(); ++keyIterator)
        {
            currentTrie = &currentTrie->_subTrieMap[*keyIterator];
        }

        currentTrie->_value = iValue;
    }

    template <typename T>
    bool Trie<T>::deleteKey(const string& iKey)
    {
        bool deleteIsCompleted = false;
        // If the key is available, pathContainer will contain the list of nodes
        // corresponding to the path from the root to the last char of the key.
        vector<Trie<T>* > pathContainer;
        Trie<T>* trie = findKeyWithPath(iKey, pathContainer);
        // Checking if the key exists.
        if (trie != nullptr)
        {
            // Reset the value.
            trie->_value = boost::optional<T>();
            typename vector<Trie<T>* >::const_reverse_iterator reversePathIterator = pathContainer.rbegin();
            if (trie->isEmpty())
            {
                // This is a node without any other sub-trie and no value, we go directly to the parent
                // to delete the mapping with this node.
                ++reversePathIterator;
            }
            else
            {
                // The node has sub-tries; the delete is completed simply resetting the value of the node,
                // action already performed above with an empty boost::optional.
                deleteIsCompleted = true;
            }

            // We traverse the trie from the last char node to possibly its root.
            string::const_reverse_iterator keyIterator = iKey.rbegin();
            while (reversePathIterator != pathContainer.rend() && !deleteIsCompleted)
            {
                // Checking just to be safe but the iteration on reversePathIterator
                // has the same range size as the one on keyIterator.
                if (keyIterator == iKey.rend())
                {
                    throw runtime_error("Unexpected condition while deleting a key");
                }

                char currentCharacter = *keyIterator;
                Trie<T>* currentTrie = *reversePathIterator;

                map<char, Trie<T>>& currentSubTrieMap = currentTrie->_subTrieMap;
                if (currentSubTrieMap[currentCharacter].isEmpty())
                {
                    // The sub-trie at currentCharacter is empty, so we can delete it.
                    currentSubTrieMap.erase(currentCharacter);
                }
                // The trie has some children or a value, so we stop the delete process.
                if (!currentTrie->isEmpty())
                {
                    deleteIsCompleted = true;
                }

                // Going up to the parent of currentTrie.
                ++reversePathIterator;
                ++keyIterator;
            }

            // In case the full trie (up to the root) is cleared.
            if (!deleteIsCompleted && reversePathIterator == pathContainer.rend())
            {
                deleteIsCompleted = true;
            }
        }

        return deleteIsCompleted;
    }

    template <typename T>
    const Trie<T>* Trie<T>::findKey(const string& iKey) const
    {
        if (iKey.empty())
        {
           return nullptr;
        }

        // Traversing the trie from the root to the last character node.
        bool isKeyPresent = true;
        const Trie<T>* currentTrie = this;
        for (string::const_iterator keyIterator = iKey.begin(); keyIterator != iKey.end() && isKeyPresent;
            ++keyIterator)
        {
           const map<char, Trie<T>>& aCurrentMap = currentTrie->_subTrieMap;
           typename map<char, Trie<T>>::const_iterator trieIterator = aCurrentMap.find(*keyIterator);
           if (trieIterator != aCurrentMap.end())
           {
               currentTrie = &(trieIterator->second);
           }
           else
           {
               // The key is not present in the trie.
               isKeyPresent = false;
           }
        }

        if (isKeyPresent && currentTrie->_value)
        {
           // The key is present; we return the last character node.
           return currentTrie;
        }

        // This is a normal case for the following scenarios:
        // - the prefix is not present at all in the trie.
        // - the prefix is present but without value, and this can happen only if the node has children.
        return nullptr;
    }

    /* To avoid code duplication for a const and a non-const version of the method, we use
       the following method, as explained by Scott Meyers in Effective C++ 3rd edition in Item 3.
       Basically the non-const version uses the const one through a const cast: this is safe
       because whoever called the non-const version must have had a non-const object in the
       first place. Otherwise they could not have called a non-const method.
       That said, this pointer is a non-const object; we static cast it to const in order to use
       the const version and then apply the const_cast to remove the fake constness we added.
   */
    template <typename T>
    Trie<T>* Trie<T>::findKey(const string& iKey)
    {
        return const_cast<Trie<T>* >(static_cast<const Trie<T>* >(this->findKey(iKey)));
    }

    template <typename T>
    template <typename Container>
    Trie<T>* Trie<T>::findKeyWithPath(const string& iKey, Container& oPathContainer)
    {
        if (iKey.empty())
        {
            return nullptr;
        }

        // Same algorithm as findKey but it is kept separated because of extra actions useful for the
        // deleteKey. In fact each node in the path is added to a temporary container; if the key
        // is finally available, the content of the temporary container will be swapped in oPathContainer.
        bool isKeyPresent = true;
        Trie<T>* currentTrie = this;
        Container temporaryPathContainer;
        temporaryPathContainer.push_back(currentTrie);

        for (string::const_iterator keyIterator = iKey.begin(); keyIterator != iKey.end() && isKeyPresent;
            ++keyIterator)
        {
            map<char, Trie<T>>& aCurrentMap = currentTrie->_subTrieMap;
            if (aCurrentMap.find(*keyIterator) != aCurrentMap.end())
            {
                currentTrie = &currentTrie->_subTrieMap[*keyIterator];
                temporaryPathContainer.push_back(currentTrie);
            }
            else
            {
                isKeyPresent = false;
            }
        }

        if (isKeyPresent && currentTrie->_value)
        {
            // The key is present; we set the oPathContainer and return the last character node.
            oPathContainer.swap(temporaryPathContainer);
            return currentTrie;
        }

        // This is a normal case for the following scenarios:
        // - the prefix is not present at all in the trie.
        // - the prefix is present but without value, and this can happen only if the node has children.
        return nullptr;
    }

    template <typename T>
    const T& Trie<T>::getValue(const std::string& iKey) const
    {
        const Trie<T>* trieForKey = findKey(iKey);
        if (trieForKey == nullptr)
        {
            throw runtime_error("Key " + iKey + " not available in the trie");
        }

        assert(trieForKey->_value);
        return trieForKey->_value.get();
    }

    template <typename T>
    bool Trie<T>::hasKey(const string& iKey) const
    {
        return findKey(iKey) != nullptr;
    }

    template <typename T>
    bool Trie<T>::isEmpty() const
    {
        return !_value && _subTrieMap.empty();
    }

    // Instantiation for test purposes.
    template class Trie<string>;

}
