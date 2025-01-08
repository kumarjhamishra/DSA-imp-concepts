#include <bits/stdc++.h>

using namespace std;
using ll = long long;
class TrieNode{
    public:
    // for childern rather than using vector we are using unordered map for feasibility
    unordered_map<int, TrieNode*> children;
    int countEnd; // to maintain how many words at that particular node

    TrieNode(): countEnd(0){}
};

class Trie{
    TrieNode* root;
    ll totalPairs;
    public:
    Trie(){
        totalPairs = 0;
        root = new TrieNode();
    }

    ll getTotalPairs(){
        return totalPairs;
    }

    void insert(string word){
        // in order to check the prefix and suffix at the same time in the trie node we will store the pair of first and consecutive last character for every character of a word
        
        // means i and n-1-i for every i

        int n = word.size();
        TrieNode* node = root;
        for(int i = 0; i < n; i++){
            // to store the pair of i and n-1-i char with feasibility we are hashing then storing it 

            int node_val = word[i]*128 + word[n-1-i];
            // 128 bcoz no char will exceed

            // if this node_val is not present in child make it
            if(node->children.find(node_val) == node->children.end()){
                node->children[node_val] = new TrieNode();
            }

            node = node->children[node_val];

            // increment the totalPairs with the count of how many words ended here
            // bcoz that will represent how many words have the prefix and suffix till here
            totalPairs += node->countEnd;
        }

        // when the word is totally made increment the countEnd for the last node
        node->countEnd++;
    }
};
class Solution {
public:
    long long countPrefixSuffixPairs(vector<string>& words) {
        // complexity is O(n*s) 

        // for better understanding - https://youtu.be/rli_m4ZAt8Q?si=zFcfL9I_xYwp9Dt7

        
        Trie* t = new Trie();

        for(string word : words){
            t->insert(word);
        }

        return t->getTotalPairs();
    }
};

int main(){
    return 0;
}