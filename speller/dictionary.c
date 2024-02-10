// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include <stdio.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// Total number of words in the dictionary
unsigned int word_count = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    unsigned int hash_value = hash(word);
    node *cursor = table[hash_value];

    while (cursor != NULL)
    {
        if (strcasecmp(word, cursor->word) == 0)
        {
            return true;
        }
        cursor = cursor->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // Simple hash function that hashes based on the first character of the word
    // Assuming the input word contains only alphabetical characters or apostrophes
    return toupper(word[0]) - 'A';
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Open dictionary file
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }

    // Clear hash table
    for (unsigned int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }

    // Buffer for storing each word
    char word[LENGTH + 1];

    // Read words from dictionary and insert into hash table
    while (fscanf(file, "%s", word) != EOF)
    {
        // Create a new node for the word
        node *new_node = malloc(sizeof(node));
        if (new_node == NULL)
        {
            fclose(file);
            return false;
        }

        // Copy the word into the node
        strcpy(new_node->word, word);

        // Hash the word to get the index
        unsigned int hash_value = hash(word);

        // Insert the new node at the beginning of the linked list
        new_node->next = table[hash_value];
        table[hash_value] = new_node;

        // Increment word count
        word_count++;
    }

    // Close dictionary file
    fclose(file);

    // Dictionary loaded successfully
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return word_count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // Free the memory for each node in the hash table
    for (unsigned int i = 0; i < N; i++)
    {
        node *cursor = table[i];
        while (cursor != NULL)
        {
            node *temp = cursor;
            cursor = cursor->next;
            free(temp);
        }
    }

    // Reset word count and return success
    word_count = 0;
    return true;
}
