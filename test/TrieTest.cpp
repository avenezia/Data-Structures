#include "TrieTest.hpp"

#include <algorithm>
#include <stdexcept>
using namespace std;

namespace trie
{
    const string TrieTest::kDefaultKey("key");
    const string TrieTest::kDefaultValue("value");

    void TrieTest::assertTwoDeletes(const string& iFirstKeyToBeDeleted,
        const string& iSecondKeyToBeDeleted)
    {
        _trie->addKey(iFirstKeyToBeDeleted, kDefaultValue);
        _trie->addKey(iSecondKeyToBeDeleted, kDefaultValue);
        // Checking that the first key is deleted.
        ASSERT_TRUE(_trie->deleteKey(iFirstKeyToBeDeleted));
        ASSERT_FALSE(_trie->hasKey(iFirstKeyToBeDeleted));
        // Checking that after the first key is deleted, the second one is still there.
        ASSERT_TRUE(_trie->hasKey(iSecondKeyToBeDeleted));
        ASSERT_TRUE(_trie->deleteKey(iSecondKeyToBeDeleted));
        ASSERT_FALSE(_trie->hasKey(iSecondKeyToBeDeleted));
        ASSERT_TRUE(_trie->isEmpty());
    }

    void TrieTest::SetUp()
    {
        _trie.reset(new Trie<string>);
    }

    TEST_F (TrieTest, testAddKey_AddTwiceSameKeyValue)
    {
        _trie->addKey(kDefaultKey, kDefaultValue);
        ASSERT_EQ(kDefaultValue, _trie->getValue(kDefaultKey));
        _trie->addKey(kDefaultKey, kDefaultValue);
        ASSERT_EQ(kDefaultValue, _trie->getValue(kDefaultKey));
    }

    TEST_F (TrieTest, testAddKey_AddTwiceSameKeyWithDifferentValue)
    {
        const string kNewValue("new value");
        _trie->addKey(kDefaultKey, kDefaultValue);
        ASSERT_EQ(kDefaultValue, _trie->getValue(kDefaultKey));
        _trie->addKey(kDefaultKey, kNewValue);
        ASSERT_EQ(kNewValue, _trie->getValue(kDefaultKey));
    }

    TEST_F (TrieTest, testAddKey_EmptyKey)
    {
        ASSERT_THROW(_trie->addKey("", kDefaultValue), runtime_error);
    }

    TEST_F (TrieTest, testAddKey_ValidKey)
    {
        _trie->addKey(kDefaultKey, kDefaultValue);
        ASSERT_FALSE(_trie->isEmpty());
        ASSERT_TRUE(_trie->hasKey(kDefaultKey));
    }

    TEST_F (TrieTest, testDeleteKey_EmptyKey)
    {
        ASSERT_FALSE(_trie->deleteKey(""));
    }

    TEST_F (TrieTest, testDeleteKey_KeyIsNotPresentInEmptyTrie)
    {
        ASSERT_FALSE(_trie->deleteKey(kDefaultKey));
    }

    TEST_F (TrieTest, testDeleteKey_KeyIsNotPresentInNotEmptyTrie)
    {
        _trie->addKey(kDefaultKey, kDefaultValue);
        ASSERT_FALSE(_trie->deleteKey(kDefaultKey + "2"));
    }

    TEST_F (TrieTest, testDeleteKey_KeyIsPresent)
    {
        _trie->addKey(kDefaultKey, kDefaultValue);
        ASSERT_TRUE(_trie->deleteKey(kDefaultKey));
        ASSERT_FALSE(_trie->hasKey(kDefaultKey));
        ASSERT_TRUE(_trie->isEmpty());
    }

    TEST_F (TrieTest, testDeleteKey_MultipleDeletesOnCommonParentPrefix)
    {
        // Checking that the delete works correctly in case of a common parent.
        // The trie is the following         / y
        //                            k - e -
        //                                   \ j
        // The test will first delete "key" and then "kej".
        const string kSecondKey("kej");
        assertTwoDeletes(kDefaultKey, kSecondKey);
    }

    TEST_F (TrieTest, testDeleteKey_MultipleDeletesOnSamePrefix)
    {
        // Checking that the delete works correctly in case the parent is deleted before the child.
        // The trie is the following k - e - y
        // The test will first delete "ke" and then "key".
        const string kPrefixKey("ke");
        assertTwoDeletes(kPrefixKey, kDefaultKey);
    }

    TEST_F (TrieTest, testGetValue_KeyIsNotPresent)
    {
        ASSERT_THROW(_trie->getValue(kDefaultKey), runtime_error);
    }

    TEST_F (TrieTest, testGetValue_KeyIsPresent)
    {
        _trie->addKey(kDefaultKey, kDefaultValue);
        ASSERT_EQ(kDefaultValue, _trie->getValue(kDefaultKey));
    }

    TEST_F (TrieTest, testIsEmpty_EmptyTrie)
    {
        ASSERT_TRUE(_trie->isEmpty());
    }

    TEST_F (TrieTest, testIsEmpty_NotEmptyTrie)
    {
        _trie->addKey(kDefaultKey, kDefaultValue);
        ASSERT_FALSE(_trie->isEmpty());
    }

    TEST_F (TrieTest, testHasKey_KeyIsPresent)
    {
        _trie->addKey(kDefaultKey, kDefaultValue);
        ASSERT_TRUE(_trie->hasKey(kDefaultKey));
    }

    TEST_F (TrieTest, testHasKey_KeyIsSubstringOfOneWithValue)
    {
        // The trie is the following: k - e - y, with only "key".
        // We check that "ke" is not found.
        _trie->addKey(kDefaultKey, kDefaultValue);
        ASSERT_FALSE(_trie->hasKey(kDefaultKey.substr(0, 2)));
    }

    TEST_F (TrieTest, testHasKey_KeyIsNotPresent)
    {
        ASSERT_FALSE(_trie->hasKey("KeyNotPresent"));
    }

}
