/*
    Trie.cpp
    Copyright (c) 2024, Amit Gefen

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
    THE SOFTWARE.
*/

#include <unordered_map>
#include <string_view> // (Since C++17)
#include <memory>
#include <iostream>


// A trie of characters. A tree-like data structure used to store a dynamic set of strings where
// each node represents a single character. This is a versatile data structure suitable for efficient
// storage and retrieval of strings, particularly where prefix-based searching is required.

template<typename CharType>
class Trie final
{
public:

    // Function to insert a string into the trie.
    void Insert(const std::basic_string_view<CharType> string_view)
    {
        if (!string_view.empty()) {
            Insert(root_, string_view);
        }
    }


    // Function to find the common prefix among trie strings.
    auto CommonPrefix() const
    {
        std::basic_string<CharType> common_prefix{};
        CommonPrefix(root_, common_prefix);

        return common_prefix;
    }

private:

    // Trie__
 
    // Structure representing a node in the trie.
    struct Node final
    {
        std::unordered_map<CharType, std::unique_ptr<Node>> child_node{}; // Map of child nodes.
        bool end_of_string{ false }; // Flag to indicate end of a string
    };

    Node root_{}; // Root node of the trie (Represents a null prefix.)

    // __Trie


    // Recursive function to insert a string into the trie.
    void Insert(Node& node, const std::basic_string_view<CharType> string_view)
    {
        if (string_view.empty()) {
            node.end_of_string = true; // Mark the end of the string

            return;
        }

        CharType first_char{ string_view[0] }; // Get the first character of the string.
        std::basic_string_view<CharType> remaining_view{ string_view.substr(1) }; // Get the substring starting from index 1.

        if (node.child_node.find(first_char) == node.child_node.end()) {
            // If the character does not exist in the trie, create a new node and insert it into the child nodes map.
            node.child_node[first_char] = std::make_unique<Node>();
        }

        Insert(*node.child_node[first_char], remaining_view); // Recursively insert the remaining substring.
    }


    // Recursive function to find the common prefix among all inserted strings.
    void CommonPrefix(const Node& root, std::basic_string<CharType>& common_prefix) const
    {
        // Check if there's only one child node and it's not the end of a string
        if (root.child_node.size() != 1 || root.end_of_string) {

            return;
        }

        common_prefix += root.child_node.begin()->first; // Append the current character to the common prefix.
        CommonPrefix(*root.child_node.begin()->second, common_prefix); // Recursively find the common prefix in the next node.
    }
};


// Main
int main()
{
    Trie<wchar_t> trie_1{}, trie_2{};

    // Test 1:

    trie_1.Insert(L"123456");
    trie_1.Insert(L"1234");

    std::wcout << L"common prefix: " << trie_1.CommonPrefix() << std::endl;

    // Test 2:

    trie_2.Insert(L"");
    trie_2.Insert(L"xabX");
    trie_2.Insert(L"xabXYZ");
    trie_2.Insert(L"xabXP");
    trie_2.Insert(L"xabXT");

    std::wcout << L"common prefix: " << trie_2.CommonPrefix() << std::endl;
}