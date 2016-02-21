#include <stdexcept>
#include <string>
using namespace std;

#include "gtest/gtest.h"

#include "Trie.hpp"

namespace trie
{
    static const string kDefaultKey("key");
    static const string kDefaultValue("value");

    void AssertTwoDeletes(const string& iFirstKeyToBeDeleted,
        const string& iSecondKeyToBeDeleted)
    {
        Trie<string> trie;
        trie.addKey(iFirstKeyToBeDeleted, kDefaultValue);
        trie.addKey(iSecondKeyToBeDeleted, kDefaultValue);
        // Checking that the first key is deleted.
        ASSERT_TRUE(trie.deleteKey(iFirstKeyToBeDeleted));
        ASSERT_FALSE(trie.hasKey(iFirstKeyToBeDeleted));
        // Checking that after the first key is deleted, the second one is still there.
        ASSERT_TRUE(trie.hasKey(iSecondKeyToBeDeleted));
        ASSERT_TRUE(trie.deleteKey(iSecondKeyToBeDeleted));
        ASSERT_FALSE(trie.hasKey(iSecondKeyToBeDeleted));
        ASSERT_TRUE(trie.isEmpty());
    }

    TEST (TrieTest, testAddKey_AddTwiceSameKeyValue)
    {
        Trie<string> trie;
        trie.addKey(kDefaultKey, kDefaultValue);
        ASSERT_EQ(kDefaultValue, trie.getValue(kDefaultKey));
        trie.addKey(kDefaultKey, kDefaultValue);
        ASSERT_EQ(kDefaultValue, trie.getValue(kDefaultKey));
    }

    TEST (TrieTest, testAddKey_AddTwiceSameKeyWithDifferentValue)
    {
        const string kNewValue("new value");
        Trie<string> trie;
        trie.addKey(kDefaultKey, kDefaultValue);
        ASSERT_EQ(kDefaultValue, trie.getValue(kDefaultKey));
        trie.addKey(kDefaultKey, kNewValue);
        ASSERT_EQ(kNewValue, trie.getValue(kDefaultKey));
    }

    TEST (TrieTest, testAddKey_EmptyKey)
    {
        Trie<string> trie;
        ASSERT_THROW(trie.addKey("", kDefaultValue), runtime_error);
    }

    TEST (TrieTest, testAddKey_ValidKey)
    {
        Trie<string> trie;
        trie.addKey(kDefaultKey, kDefaultValue);
        ASSERT_FALSE(trie.isEmpty());
        ASSERT_TRUE(trie.hasKey(kDefaultKey));
    }

    TEST (TrieTest, testDeleteKey_EmptyKey)
    {
        Trie<string> trie;
        ASSERT_FALSE(trie.deleteKey(""));
    }

    TEST (TrieTest, testDeleteKey_KeyIsNotPresentInEmptyTrie)
    {
        Trie<string> trie;
        ASSERT_FALSE(trie.deleteKey(kDefaultKey));
    }

    TEST (TrieTest, testDeleteKey_KeyIsNotPresentInNotEmptyTrie)
    {
        Trie<string> trie;
        trie.addKey(kDefaultKey, kDefaultValue);
        ASSERT_FALSE(trie.deleteKey(kDefaultKey + "2"));
    }

    TEST (TrieTest, testDeleteKey_KeyIsPresent)
    {
        Trie<string> trie;
        trie.addKey(kDefaultKey, kDefaultValue);
        ASSERT_TRUE(trie.deleteKey(kDefaultKey));
        ASSERT_FALSE(trie.hasKey(kDefaultKey));
        ASSERT_TRUE(trie.isEmpty());
    }

    TEST (TrieTest, testDeleteKey_MultipleDeletesOnCommonParentPrefix)
    {
        // Checking that the delete works correctly in case of a common parent.
        // The trie is the following         / y
        //                            k - e -
        //                                   \ j
        // The test will first delete "key" and then "kej".
        const string kSecondKey("kej");
        AssertTwoDeletes(kDefaultKey, kSecondKey);
    }

    TEST (TrieTest, testDeleteKey_MultipleDeletesOnSamePrefix)
    {
        // Checking that the delete works correctly in case the parent is deleted before the child.
        // The trie is the following k - e - y
        // The test will first delete "ke" and then "key".
        const string kPrefixKey("ke");
        AssertTwoDeletes(kPrefixKey, kDefaultKey);
    }

    TEST (TrieTest, testGetValue_KeyIsNotPresent)
    {
        Trie<string> trie;
        ASSERT_THROW(trie.getValue(kDefaultKey), runtime_error);
    }

    TEST (TrieTest, testGetValue_KeyIsPresent)
    {
        Trie<string> trie;
        trie.addKey(kDefaultKey, kDefaultValue);
        ASSERT_EQ(kDefaultValue, trie.getValue(kDefaultKey));
    }

    TEST (TrieTest, testIsEmpty_EmptyTrie)
    {
        Trie<string> trie;
        ASSERT_TRUE(trie.isEmpty());
    }

    TEST (TrieTest, testIsEmpty_NotEmptyTrie)
    {
        Trie<string> trie;
        trie.addKey(kDefaultKey, kDefaultValue);
        ASSERT_FALSE(trie.isEmpty());
    }

    TEST (TrieTest, testHasKey_KeyIsPresent)
    {
        Trie<string> trie;
        trie.addKey(kDefaultKey, kDefaultValue);
        ASSERT_TRUE(trie.hasKey(kDefaultKey));
    }

    TEST (TrieTest, testHasKey_KeyIsSubstringOfOneWithValue)
    {
        Trie<string> trie;
        // The trie is the following: k - e - y, with only "key".
        // We check that "ke" is not found.
        trie.addKey(kDefaultKey, kDefaultValue);
        ASSERT_FALSE(trie.hasKey(kDefaultKey.substr(0, 2)));
    }

    TEST (TrieTest, testHasKey_KeyIsNotPresent)
    {
        Trie<string> trie;
        ASSERT_FALSE(trie.hasKey("KeyNotPresent"));
    }

}
