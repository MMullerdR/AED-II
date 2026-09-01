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
void trie_busca_prefixo(trieNode *root, char *prefixo, char ***palavras, int *num_PalavrasEncontradas);
void checkerDFS(trieNode *node, char *auxStr, char ***palavras, int *num_PalavrasEncontradas, int nivel);

int main(){
    char* word = "desatento";
    trieNode *root = createNode();
    insertWord("desatento", root);
    insertWord("desanima", root);
    insertWord("desanimar", root);
    insertWord("desfaz", root);
    insertWord("desfazer", root);
    insertWord("descobri", root);
    insertWord("descobrir", root);
    bool isWordThere = findWord(word, root);
    printf("Real ou faike: %d\n", isWordThere);

    char **palavras = NULL;
    int num_PalavrasEncontradas = 0;
    trie_busca_prefixo(root, "des", &palavras, &num_PalavrasEncontradas);

    printf("Palavras com prefixo 'des':\n");
    for (int i = 0; i < num_PalavrasEncontradas; i++){
        printf("%s\n", palavras[i]);
        free(palavras[i]);
    }
    free(palavras);

    return 0;
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
    return aux->fimDaPalavra; // returna true so se for o fim da palavra
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

void trie_busca_prefixo ( trieNode *rootNode, char *prefixo, char ***palavras, int *num_PalavrasEncontradas ) {
    
    if ( !rootNode ){
        return;
    }
    int len_prefixo = strlen( prefixo );
    
    if ( len_prefixo == 0 ) {
        return; 
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
    
    if ( current->fimDaPalavra ){ // adiciona o proprio prefixo à lista, se ele for uma palavra
        *palavras = realloc(*palavras, (*num_PalavrasEncontradas + 1) * sizeof(char*));
        (*palavras)[*num_PalavrasEncontradas] = malloc(strlen(prefixo) + 1);
        strcpy((*palavras)[*num_PalavrasEncontradas], prefixo);
        (*num_PalavrasEncontradas)++;
    }
    
    char auxStr[TAM_MAX_PAL];
    strcpy(auxStr, prefixo); // garante o '\0' no fim do buffer
    
    // current = nó da ultima letra do prefixo
    int nivel = len_prefixo - 1; // indice do ultimo caractere valido em auxStr
    checkerDFS(current, auxStr, palavras, num_PalavrasEncontradas, nivel);
}

void checkerDFS ( trieNode* node, char *auxStr, char ***palavras, int *num_PalavrasEncontradas, int nivel ) {
    if ( !node ){
        return;
    }
    
    for ( int i = 0; i < ALPHABET_SIZE; i++ ){
        if ( node->child[i] ){
            char caractereAtual = ( i + 'a' );
            auxStr[nivel + 1] = caractereAtual;
            auxStr[nivel + 2] = '\0';
            
            if ( node->child[i]->fimDaPalavra ){ // adiciona palavra a lista
                *palavras = realloc(*palavras, (*num_PalavrasEncontradas + 1) * sizeof(char*));
                (*palavras)[*num_PalavrasEncontradas] = malloc(strlen(auxStr) + 1);
                strcpy((*palavras)[*num_PalavrasEncontradas], auxStr);
                (*num_PalavrasEncontradas)++;
            }
            
            checkerDFS(node->child[i], auxStr, palavras, num_PalavrasEncontradas, nivel + 1); // chamava trie_busca_prefixo por engano
        }
    }
}