#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define ALPHABET_SIZE 26
#define TAM_MAX_PAL 50

typedef struct trieNode{
    struct trieNode *child[ALPHABET_SIZE];
    bool fimDaPalavra;
}trieNode;

trieNode* createNode( void );
bool findWord( char* word, trieNode *rootNode );
void insertWord ( char* word, trieNode *rootNode );
void trie_busca_prefixo(trieNode *root, char *prefixo, char **palavras);

int main(){

    char* word = "batata";

    trieNode *root = createNode();
    insertWord("batman", root);

    bool isWordFound = findWord(word, root);
    printf("Real ou faike: %d\n", isWordFound);

}

trieNode* createNode( void ){
    trieNode *node = (trieNode *)malloc(sizeof(trieNode));
    for (int i = 0; i < ALPHABET_SIZE; i++){
        node->child[i] = NULL;
    } 
    node->fimDaPalavra = false;
    return node;
}

bool findWord( char* word, trieNode *rootNode ) {
    int len_word = strlen( word );
    
    if ( len_word == 0 ) {
        return false;
    }

    trieNode *aux = rootNode;
    int i = 0;

    while ( i < len_word ) {
        int j = (int) word[i] - 'a';
        if ( !aux->child[j] )
            return false;

        aux = aux->child[j];
        i++;
    }

    return true;
}

void insertWord ( char* word, trieNode *rootNode ){
    trieNode *current = rootNode;

    for ( int i = 0; word[i] != '\0'; i++ ){
        int index = word[i] - 'a';
        if ( !current->child[index] ) {
            current->child[index] = createNode();
        }
        current = current->child[index];
    }
    current->fimDaPalavra = true;
}

void trie_busca_prefixo(trieNode *rootNode, char *prefixo, char **palavras){
    
    if ( !rootNode ){
        return;
    }

    int len_prefixo = strlen( prefixo );
    
    if ( len_prefixo == 0 ) {
        return false;
    }

    trieNode *current = rootNode;
    int i = 0;

    while ( i < len_prefixo ) { // avança todas as posicoes do prefixo
        int j = (int) prefixo[i] - 'a';
        if ( !current->child[j] )
            return;

        current = current->child[j];
        i++;
    }

    int num_PalavrasEncontradas = 0;
    
    if (findWord(prefixo, rootNode)){ //adiciona prefixo à lista
        num_PalavrasEncontradas++;
        char **palavras = realloc(palavras, num_PalavrasEncontradas * sizeof(char*)); // talvez precise especificar tipo para compilar
        palavras[num_PalavrasEncontradas - 1] = malloc(sizeof(prefixo) + 1);
        strcpy(palavras[num_PalavrasEncontradas - 1], prefixo);
    }
    
    char auxStr[TAM_MAX_PAL] = malloc( (strlen(prefixo) + 1 ) * sizeof(char)); 
    strcpy(auxStr, prefixo);
    
    // current =  nó da ultima letra do prefixo
    checkerDFS(current, auxStr, palavras, num_PalavrasEncontradas);
    
}

void checkerDFS(trieNode* node, char *auxStr, char **palavras, int *num_PalavrasEncontradas) {

    if ( !node ){
        return;
    }

    bool children_visited[ALPHABET_SIZE] = { 0 };
    
    if (node->fimDaPalavra){
        // adiciona palavra a lista
    }
    
    for( int i = 0; i < ALPHABET_SIZE; i++ ){
        trie_busca_prefixo(node->child[i], auxStr, palavras); // chama para cada filho
        children_visited[i] = true;
    }
}