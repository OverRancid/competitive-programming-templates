class Trie{
public:
    Trie(){
        root = new TrieNode;
    }
    void insert(string &str){
        //inserts string into Trie
        TrieNode *currentNode = root;
        for(char x: str){
            int c = (int)(x-'a');
            if(currentNode->next[c]==nullptr){
                currentNode->next[c] = new TrieNode;
            }
            currentNode->prefix_count++;
            currentNode = currentNode->next[c];
        }
        currentNode->count++;
    }
    int search(string &str){
        //returns number of strings equivalent to str in Trie.
        TrieNode *currentNode = root;
        for(char x: str){
            int c = (int)(x-'a');
            if(currentNode->next[c]==nullptr){
                return 0;
            }
            currentNode = currentNode->next[c];
        }
        return currentNode->count;
    }
    void remove(string &str){
        //removes string from Trie if it exists - does nothing otherwise.
        root = remove_worker(root, str, 0);
    }
    int search_prefix(string &str){
        //returns number of strings with given prefix.
        TrieNode* currentNode = root;
        for(char x: str){
            int c = (int)(x-'a');
            if(currentNode->next[c]==nullptr){
                return 0;
            }
            currentNode = currentNode->next[c];
        }
        return currentNode->prefix_count;
    }
private:
    class TrieNode{
    public:
        TrieNode(){
            fill(next.begin(), next.end(), nullptr);
            count = 0;
            prefix_count = 0;
        }
        bool empty(){
            return prefix_count == 0;
        }
        array<TrieNode *, 26> next;
        int count;
        int prefix_count;
    };
    TrieNode* remove_worker(TrieNode* node, string &str, int depth){
        node->prefix_count--;
        
        if(depth == str.size()){
            node->count--;
            if(node->empty() && node->count==0){
                delete node;
                node = nullptr;
            }
            return node;
        }
        int c = str[depth] - 'a';
        node->next[c] = remove_worker(node->next[c], str, depth+1);
        
        if(node->empty() && node->count==0){
            delete node;
            node = nullptr;
        }
        return node;
    }
    TrieNode *root;
};
