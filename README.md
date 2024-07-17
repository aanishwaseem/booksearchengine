# booksearchengine

Purpose:

This code implements a comprehensive Book Search Engine, designed to facilitate efficient searching and management of words across multiple books. The key features include:

## Populating Stop Words:
The code reads a list of common stop words from a file. These words are excluded from searches to improve the relevancy of the results.
## Searching in the books:
Users can search for specific words in the BST of a particular book or in a merged books. The search is case-insensitive and excludes stop words.
## Printing words of books:
Users can print all words in a book along with their occurrences, in sorted order.
## Deleting Words:
Users can delete specific words from the BST, effectively removing all their occurrences from the book's index.
## Merging Books:
The code merges the word indexes of two books into a single BST, allowing for a unified search and analysis.
## Finding Common Words:
The code identifies and displays words that are common between two books.

# Functionalities:
1. Reads a list of stop words from "stopwords.txt".
2. Reads "input.txt" and "input2.txt", skipping stop words, and inserts the remaining words into bst and bst2 respectively
3. Users can now search for words in book1, book2, or merged of both books. If found, prints the word along with all its occurrences.
4. Prints all words and their occurrences in bst, bst2 or merged bst in sorted order.
5. Allows users to delete words from bst, bst2, or merged BST. Removes all occurrences of the specified word.
6. Merges the BSTs of two books (bst and bst2) into a single BST (merged), allowing for combined search and analysis.
7. Identifies and displays words that are common between the two BSTs (bst and bst2).
Usage:
Users can interact with the program through a menu-driven interface to perform various operations like printing, searching, deleting, merging, and finding common words.
The code ensures efficient search and management by utilizing binary search trees for storing and processing words and their occurrences.

## Preview
![book3](https://github.com/user-attachments/assets/63163d0c-2a22-45e1-b700-343b69c95ee8)

![book2](https://github.com/user-attachments/assets/629886a6-4548-48ec-9369-bdf95d71e9b7)

![book1](https://github.com/user-attachments/assets/c71c0454-9a1e-48b0-b333-cbda39399157)
