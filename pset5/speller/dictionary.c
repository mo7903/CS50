// Implements a dictionary's functionality
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <strings.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 600;
int count, now, len;
node *cursor = NULL;
// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    now = hash(word);
    cursor = table[now];
    while (cursor != NULL)
    {
        if (strcasecmp(cursor->word, word) == 0) //compares the word to the list in dictionary case-sensetively
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
    len = strlen(word);
    return toupper(word[0]) * len % N; //hashes the word considering its length and first letter together
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *rDictionary = fopen(dictionary, "r");
    char temp[LENGTH + 1];
    if (rDictionary == NULL)
    {
        return false;
    }
    while (fscanf(rDictionary, "%s", temp) != EOF)
    {
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }
        strcpy(n->word, temp);
        int c = hash(temp);
        n->next = NULL;
        if (table[c] == NULL)
        {
            table[c] = n; //makes the node point to the new node
            count++; //useful for the size functions
        }
        else
        {
            n->next = table[c]; //adds the new node without losing the rest of the nodes
            table[c] = n;
            count++;
        }
    }
    fclose(rDictionary);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        while (table[i] != NULL)
        {
            node *temp = table[i]->next; //frees each node separately so that none is lost in memory
            free(table[i]);
            table[i] = temp;
        }
    }
    return true;
}
