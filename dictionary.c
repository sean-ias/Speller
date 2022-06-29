// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "dictionary.h"

// Represents a node in a hash table

typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 143091;

// Hash table
node *table[N];
int i = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    char *nw = malloc(strlen(word) + 1);
    if (nw == NULL)
    {
        return false;
    }
    for (int j = 0; j < strlen(word) + 1; j++)
    {
        nw[j] = tolower(word[j]);
    }
    node *tmp = table[hash(nw)];
    while (tmp != NULL)
    {
        if (strcmp(tmp->word, nw) == 0)
        {
            free(nw);
            return true;
        }
        tmp = tmp->next;
    }
    free(nw);
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO
    unsigned int hv = 7;
    for (int j = 0; j < strlen(word); j++)
    {
        int c = word[j];
        hv = hv * 31 + c;
        hv = hv % N;
    }
    return hv % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }
    char *w = malloc(LENGTH + 1);
    if (w == NULL)
    {
        return false;
    }
    while (fscanf(file, "%s", w) != EOF)
    {
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }
        strcpy(n->word, w);
        n->next = table[hash(w)];
        table[hash(w)] = n;
        i++;
    }
    free(w);
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return i;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int j = 0; j < N; j++)
    {
        while (table[j] != NULL)
        {
            node *tmp = table[j];
            table[j] = table[j]->next;
            free(tmp);
        }
    }
    return true;
}
