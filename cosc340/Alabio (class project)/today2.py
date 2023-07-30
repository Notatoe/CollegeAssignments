# Autocomplete
words = ["team", "tea", "teal", "tether", "teams"]
#"tea" -> ["tea", "team", "teams", "teal"]
#"team" -> ["team", "teams"]



class Node:
    def __init__(self):
        self.children = []
        self.value = ""

class Trie:
    def __init__(self):
        self.root = Node()

    def addWord(self, word):
        node = self.root
        for c in word:
            if c not in node.children:
                newNode = Node()
                node.children[c] = newNode
            node = node.children[c]
        node.value = word

    def addWords(self, words):
        for w in words:
            self.addWord(w)

    def dfs(self, suggestions, node):
        suggestions = []
        if node.value:
            suggestions.append(node.value)
        for n in node.children:
            suggestions.append(self.dfs(suggestions, n))

    def getSuggestion(self, word):
        # get to the farthest existing node in the tree, then DFS
        node = self.root
        for c in word:
            if c not in node.children:
                return [] # No suggestions
            node = node.children[c]

        suggestions = self.dfs([], node)
        return suggestions


t = Trie()
t.addWords(words)