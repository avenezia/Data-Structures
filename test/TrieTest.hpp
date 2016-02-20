#ifndef TRIETEST_HPP
#define TRIETEST_HPP

#include <memory>
#include <string>
#include <vector>

#include "gtest/gtest.h"

#include "Trie.hpp"

namespace trie
{

    class TrieTest : public ::testing::Test
    {
      public:
        virtual ~TrieTest() {};
        virtual void SetUp();

      protected:
        static const std::string kDefaultKey;
        static const std::string kDefaultValue;

        void assertTwoDeletes(const std::string& iFirstKeyToBeDeleted, const std::string& iSecondKeyToBeDeleted);

        std::unique_ptr<Trie<std::string>> _trie;

    };

}

#endif
