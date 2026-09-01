# Trie — buscar_palavra e busca por prefixo
## Arthur Ferreira Borges
## Miguel Muller da Rosa

## 1. findWord (buscar_palavra)

Percorre a trie caractere a caractere seguindo child[c - 'a']. Se em algum
ponto o filho não existe, a palavra não está na estrutura. Se percorre todos
os caracteres, ainda precisa checar fimDaPalavra no nó final — só existir o
caminho não basta, porque esse caminho pode ser apenas prefixo de outra
palavra maior (era exatamente o bug original: buscar "desat" retornava
true mesmo sem "desat" ter sido inserida, só por "desatento" existir).

- **Complexidade de tempo**: O(L), L = tamanho da palavra buscada. Não depende
  do número de palavras armazenadas.
- **Complexidade de espaço**: O(1) extra (só ponteiros auxiliares).

## 2. trie_busca_prefixo

Duas etapas:
1. Desce na trie seguindo o prefixo (O(P), P = tamanho do prefixo). Se algum
   caractere não tem filho, não existe nenhuma palavra com esse prefixo.
2. A partir do nó onde o prefixo termina, faz uma DFS (checkerDFS) por toda
   a subárvore, reconstruindo cada palavra em um buffer (auxStr) e
   copiando para a lista de saída sempre que encontra um nó com
   fimDaPalavra == true (incluindo o próprio nó do prefixo, se ele for
   uma palavra válida).

- **Complexidade de tempo**: O(P + N), onde N é a soma do tamanho de todas as
  palavras da subárvore do prefixo (cada nó visitado uma vez, custo de cópia
  de string proporcional ao nível).
- **Complexidade de espaço**: O(altura da subárvore) de pilha de recursão +
  O(tamanho total das palavras encontradas) na lista de saída.

### Por que o protótipo mudou de char **palavras para char ***palavras, int *num_PalavrasEncontradas

O protótipo sugerido (void trie_busca_prefixo(trie_nodo_t *raiz, char *prefixo, char **palavras))
não é suficiente por dois motivos:

- **Contagem**: a função não sabe de antemão quantas palavras vai encontrar,
  então precisa realocar a lista dinamicamente (realloc) a cada palavra
  nova. Isso exige um contador que sobreviva entre chamadas recursivas — daí
  o int *num_PalavrasEncontradas (passado por ponteiro, senão cada chamada
  recursiva teria sua própria cópia local e o valor se perderia ao retornar).
- **Realocação do próprio vetor**: realloc pode mover o bloco de memória
  inteiro para outro endereço. Se palavras fosse char ** (passado por
  valor), a função só teria uma cópia local do ponteiro para o vetor — o
  realloc dentro dela não seria visto pelo chamador (main), causando um
  ponteiro "fantasma"/perda de memória. Por isso char ***: um ponteiro para
  o ponteiro do vetor, permitindo que a função atualize o vetor de fato
  usado pelo main.

Resumo: sempre que uma função precisa alterar, dentro dela, um ponteiro que o
chamador enxerga (aqui, o próprio endereço do vetor palavras, por causa do
realloc), esse ponteiro precisa ser passado com um nível a mais de
indireção.

## Bugs corrigidos no código original

- findWord não checava fimDaPalavra (achava prefixo como palavra).
- trie_busca_prefixo tinha return false; dentro de uma função void
  (erro de compilação).
- checkerDFS não estava implementada; existia só o protótipo e um corpo
  incompleto que chamava trie_busca_prefixo por engano em vez de si mesma
  (recursão errada) e teria vazamento de memória com malloc de auxStr
  sem free.
- nivel estava sendo incrementado a cada iteração do laço for (percorrendo
  as 26 letras), e não a cada nível real de profundidade da recursão — o que
  bagunçava a posição de escrita em auxStr.

## Testado

Compilado com gcc -Wall -Wextra, sem warnings. Saída:

Real ou faike: 1
Palavras com prefixo 'des':
desanima
desanimar
desatento
descobri
descobrir
desfaz
desfazer