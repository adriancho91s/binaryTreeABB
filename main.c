#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct Synonym Synonym;
typedef struct Tree Tree;

struct Synonym {
    char *synonym;
    Synonym *next;
};

typedef struct Tree Tree;

struct Tree {
    Tree *left, *right;
    char *word;
    char *meaning;
    char *category;
    Synonym *synonyms;
};

// Functions declarations
void delay();
void clearScreen();
void removeTree(Tree **t);
Tree *findNode(Tree **t, char *word);
void listByCategory(Tree **t, char *category);
void listByLetter(Tree **t, char *letter);
void listAlphabetically(Tree **t);
void showProperties(Tree **t, char *word);
void addWord(Tree **t);
void modifyWord(Tree **t);
void deleteWord(Tree **t);

int main() {
    Tree *root;
    root = NULL;
    int choice = 0, num;
    
    char *options[] = {
        "Add a Word To Dictionary",
        "Modify properties of a word",
        "Delete a word",
        "Show properties of a word",
        "List of words by grammatical category",
        "List of words by letter",
        "List of words alphabetically",
        "Exit"
    };
    int numOptions = sizeof(options) / sizeof(options[0]);

    do {
        clearScreen();
        printf("Dictionary\n");
        for (int i = 0; i < numOptions; i++) {
            printf("%d. %s\n", i + 1, options[i]);
        }
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                addWord(&root);
                printf("Press Enter to continue...");
                fgetc(stdin);
                fgetc(stdin);
                break;
            case 2:
                modifyWord(&root);
                printf("Press Enter to continue...");
                fgetc(stdin);
                fgetc(stdin);
                break;
            case 3:
                deleteWord(&root);
                printf("Press Enter to continue...");
                fgetc(stdin);
                fgetc(stdin);
                break;
            case 4:
                char word[100];
                printf("Enter the word: ");
                scanf("%s", word);
                showProperties(&root, word);
                printf("Press Enter to continue...");
                fgetc(stdin);
                fgetc(stdin);
                break;
            case 5:
                char category[100];
                printf("Enter the category: ");
                scanf("%s", category);
                listByCategory(&root, category);
                printf("Press Enter to continue...");
                fgetc(stdin);
                fgetc(stdin);
                break;
            case 6:
                char letter[100];
                printf("Enter the letter: ");
                scanf("%s", letter);
                listByLetter(&root, letter);
                printf("Press Enter to continue...");
                fgetc(stdin);
                fgetc(stdin);
                break;
            case 7:
                listAlphabetically(&root);
                printf("Press Enter to continue...");
                fgetc(stdin);
                fgetc(stdin);
                break;
            default:
                printf("Invalid choice\n");
        }
        delay();

    } while (choice != numOptions);

    removeTree(root);
}

/**
 * Delay the program
 * @return void
 * */
void delay()
{
#ifdef WINDOWS
    system("timeout 1 > nul");
#else
    system("sleep 1");
#endif
}

/**
 * Clear the screen
 * @return void
 * */
void clearScreen()
{
#ifdef WINDOWS
    system("cls");
#else
    system("clear");
#endif
}


/**
 * Remove a tree from memory
 * @param Tree **t
 * @return void
*/
void removeTree(Tree **t) {
    if (t != NULL) {
        removeTree((*t)->left);
        removeTree((*t)->right);
        free(t);
    }

    return NULL;
}

/**
 * Find node in the tree
 * @param Tree **t
 * @param char *word
 * @return Tree *
*/
Tree *findNode(Tree **t, char *word) {
    if (*t == NULL) {
        return NULL;
    }

    if (strcmp(word, (*t)->word) < 0) {
        return findNode(&(*t)->left, word);
    } else if (strcmp(word, (*t)->word) > 0) {
        return findNode(&(*t)->right, word);
    } else {
        return *t;
    }

    return NULL;
}

/**
 * List words by grammatical category
 * @param Tree **t
 * @param char *category
 * @return void
*/
void listByCategory(Tree **t, char *category) {
    if (*t == NULL) {
        return;
    }

    listByCategory(&(*t)->left, category);
    if (strcmp(category, (*t)->category) == 0) {
        printf("%s\n", (*t)->word);
    }
    listByCategory(&(*t)->right, category);
}

/**
 * List words by letter
 * @param Tree **t
 * @param char *letter
 * @return void
*/
void listByLetter(Tree **t, char *letter) {
    if (*t == NULL) {
        return;
    }

    listByLetter(&(*t)->left, letter);
    if (strcmp(letter, (*t)->word[0]) == 0) {
        printf("%s\n", (*t)->word);
    }
    listByLetter(&(*t)->right, letter);
}

/**
 * List words alphabetically
 * @param Tree **t
 * @return void
*/
void listAlphabetically(Tree **t) {
    if (*t == NULL) {
        return;
    }

    listAlphabetically(&(*t)->left);
    printf("%s\n", (*t)->word);
    listAlphabetically(&(*t)->right);
}

/**
 * Show properties of a word
 * @param Tree **t
 * @param char *word
 * @return void
*/
void showProperties(Tree **t, char *word) {
    Tree *node = findNode(t, word);
    if (node != NULL) {
        printf("Word: %s\n", node->word);
        printf("Meaning: %s\n", node->meaning);
        printf("Category: %s\n", node->category);
        printf("Synonyms: ");
        Synonym *syn = node->synonyms;
        while (syn != NULL) {
            printf("%s, ", syn->synonym);
            syn = syn->next;
        }
        printf("\n");
    } else {
        printf("Word not found\n");
    }
}

/**
 * Add a word to the dictionary
 * @param Tree **t
 * @return void
*/
void addWord(Tree **t) {
    char word[100], meaning[100], category[100];
    Synonym *synonyms = NULL;
    printf("Enter the word: ");
    scanf("%s", word);
    printf("Enter the meaning: ");
    scanf("%s", meaning);
    printf("Enter the category: ");
    scanf("%s", category);
    printf("Enter synonyms (separated by commas): ");
    char syns[100];
    scanf("%s", syns);
    char *token = strtok(syns, ",");
    while (token != NULL) {
        Synonym *syn = (Synonym *)malloc(sizeof(Synonym));
        syn->synonym = token;
        syn->next = NULL;
        if (synonyms == NULL) {
            synonyms = syn;
        } else {
            Synonym *tmp = synonyms;
            while (tmp->next != NULL) {
                tmp = tmp->next;
            }
            tmp->next = syn;
        }
        token = strtok(NULL, ",");
    }
    addWork(t, word, meaning, category, synonyms);
}

/**
 * Add or remove a word from sinonims list
 * @param Synonym **synonyms
 * @param char *synonym
 * @param int add
 * @return void
*/
void addRemoveSynonym(Synonym **synonyms, char *synonym, int add) {
    if (add == 1) {
        Synonym *syn = (Synonym *)malloc(sizeof(Synonym));
        syn->synonym = synonym;
        syn->next = NULL;
        if (*synonyms == NULL) {
            *synonyms = syn;
        } else {
            Synonym *tmp = *synonyms;
            while (tmp->next != NULL) {
                tmp = tmp->next;
            }
            tmp->next = syn;
        }
    } else {
        Synonym *tmp = *synonyms;
        Synonym *prev = NULL;
        while (tmp != NULL) {
            if (strcmp(tmp->synonym, synonym) == 0) {
                if (prev == NULL) {
                    *synonyms = tmp->next;
                } else {
                    prev->next = tmp->next;
                }
                free(tmp);
                break;
            }
            prev = tmp;
            tmp = tmp->next;
        }
    }
}

/**
 * Modify properties of a word
 * @param Tree **t
 * @return void
*/
void modifyWord(Tree **t) {
    char word[100];
    printf("Enter the word: ");
    scanf("%s", word);
    Tree *node = findNode(t, word);
    if (node != NULL) {
        printf("Word: %s\n", node->word);
        printf("Meaning: %s\n", node->meaning);
        printf("Category: %s\n", node->category);
        printf("Synonyms: ");
        Synonym *syn = node->synonyms;
        while (syn != NULL) {
            printf("%s, ", syn->synonym);
            syn = syn->next;
        }
        printf("\n");
        printf("What do you want to modify?\n");
        printf("1. Word\n");
        printf("2. Meaning\n");
        printf("3. Category\n");
        printf("4. Synonyms\n");
        int choice;
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                char newWord[100];
                printf("Enter the new word: ");
                scanf("%s", newWord);
                strcpy(node->word, newWord);
                break;
            case 2:
                char newMeaning[100];
                printf("Enter the new meaning: ");
                scanf("%s", newMeaning);
                strcpy(node->meaning, newMeaning);
                break;
            case 3:
                char newCategory[100];
                printf("Enter the new category: ");
                scanf("%s", newCategory);
                strcpy(node->category, newCategory);
                break;
            case 4:
                printf("Do you want to add or remove a synonym?\n");
                printf("1. Add\n");
                printf("2. Remove\n");
                int addRemove;
                printf("Enter your choice: ");
                scanf("%d", &addRemove);
                if (addRemove == 1) {
                    char newSynonym[100];
                    printf("Enter the new synonym: ");
                    scanf("%s", newSynonym);
                    addRemoveSynonym(&node->synonyms, newSynonym, 1);
                } else {
                    char removeSynonym[100];
                    printf("Enter the synonym to remove: ");
                    scanf("%s", removeSynonym);
                    addRemoveSynonym(&node->synonyms, removeSynonym, 0);
                }
                break;
            default:
                printf("Invalid choice\n");
        }
    } else {
        printf("Word not found\n");
    }
}

/**
 * Delete a word from the dictionary
 * @param Tree **t
 * @return void
*/
void deleteWord(Tree **t) {
    char word[100];
    printf("Enter the word: ");
    scanf("%s", word);
    Tree *node = findNode(t, word);
    if (node != NULL) {
        delete(t, word);
    } else {
        printf("Word not found\n");
    }
}

