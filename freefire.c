#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --- Documentação: Definição da Estrutura de Dados ---
// A struct 'Item' é a base do nosso inventário. Ela agrupa as informações
// essenciais de cada objeto que o jogador pode coletar no jogo.
// - nome: uma string para identificar o item.
// - tipo: uma categoria para o item (ex: Arma, Munição, Cura).
// - quantidade: o número de unidades daquele item.
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// --- Protótipos das Funções Obrigatórias ---
// A boa prática de programação sugere declarar os protótipos das funções
// antes de usá-las. Isso informa ao compilador quais funções existem.
void inserirItem(Item mochila[], int *totalItens);
void removerItem(Item mochila[], int *totalItens);
void listarItens(Item mochila[], int totalItens);
void buscarItem(Item mochila[], int totalItens);

int main() {
    // --- Manutenibilidade: Nomes Claros ---
    // 'mochila' é o nosso vetor de structs, representando o inventário do jogador.
    // 'totalItens' controla o número atual de itens na mochila.
    Item mochila[10];
    int totalItens = 0;
    int opcao;

    // --- Usabilidade: Interface Clara e Orientativa ---
    // O laço 'do-while' garante que o menu seja exibido continuamente
    // até que o jogador decida sair do sistema (opção 5).
    do {
        printf("\n--- MOCHILA DE LOOT INICIAL ---\n");
        printf("1. Cadastrar novo item\n");
        printf("2. Remover item da mochila\n");
        printf("3. Listar todos os itens\n");
        printf("4. Buscar por um item\n");
        printf("5. Sair do sistema\n");
        printf("---------------------------------\n");
        printf("Escolha sua acao: ");
        scanf("%d", &opcao);
        
        // Limpa o buffer de entrada para evitar problemas com fgets/scanf
        while (getchar() != '\n'); 

        switch (opcao) {
            case 1:
                inserirItem(mochila, &totalItens);
                break;
            case 2:
                removerItem(mochila, &totalItens);
                break;
            case 3:
                listarItens(mochila, totalItens);
                break;
            case 4:
                buscarItem(mochila, totalItens);
                break;
            case 5:
                printf("\nSaindo do sistema de inventario. Ate a proxima!\n");
                break;
            default:
                printf("\nOpcao invalida! Por favor, escolha uma acao valida.\n");
        }
        
        // A listagem após cada operação (exceto sair) mantém o jogador informado.
        if(opcao >= 1 && opcao <= 2){
            listarItens(mochila, totalItens);
        }

    } while (opcao != 5);

    return 0;
}

/**
 * @brief Cadastra um novo item na mochila.
 * @param mochila O vetor de itens (inventário).
 * @param totalItens Um ponteiro para a variável que controla o número de itens.
 */
void inserirItem(Item mochila[], int *totalItens) {
    // --- Documentação: Fluxo de Execução (Inserir) ---
    // 1. Verifica se a mochila já está cheia (limite de 10 itens).
    // 2. Se houver espaço, solicita ao usuário o nome, tipo e quantidade.
    // 3. Usa fgets para ler strings com espaços de forma segura.
    // 4. Armazena o novo item na próxima posição livre do vetor.
    // 5. Incrementa o contador 'totalItens'.
    if (*totalItens >= 10) {
        printf("\nMochila cheia! Nao e possivel adicionar mais itens.\n");
        return;
    }

    printf("\n--- Cadastro de Novo Item ---\n");
    Item novoItem;

    printf("Nome do item: ");
    fgets(novoItem.nome, 30, stdin);
    novoItem.nome[strcspn(novoItem.nome, "\n")] = 0; // Remove a quebra de linha do fgets

    printf("Tipo do item (Arma, Municao, Cura, etc.): ");
    fgets(novoItem.tipo, 20, stdin);
    novoItem.tipo[strcspn(novoItem.tipo, "\n")] = 0;

    printf("Quantidade: ");
    scanf("%d", &novoItem.quantidade);
    while (getchar() != '\n'); // Limpa o buffer

    mochila[*totalItens] = novoItem;
    (*totalItens)++;

    printf("\n'%s' adicionado a mochila com sucesso!\n", novoItem.nome);
}

/**
 * @brief Lista todos os itens atualmente na mochila.
 * @param mochila O vetor de itens.
 * @param totalItens O número total de itens no vetor.
 */
void listarItens(Item mochila[], int totalItens) {
    // --- Documentação: Fluxo de Execução (Listar) ---
    // 1. Verifica se a mochila está vazia.
    // 2. Se não estiver, percorre o vetor de 0 até 'totalItens - 1'.
    // 3. Imprime os dados de cada item de forma organizada.
    printf("\n--- Itens na Mochila (%d/10) ---\n", totalItens);
    if (totalItens == 0) {
        printf("A mochila esta vazia.\n");
        return;
    }

    // Uso de laço 'for' para percorrer o vetor
    for (int i = 0; i < totalItens; i++) {
        printf("Item %d: Nome: %-20s | Tipo: %-15s | Qtd: %d\n",
               i + 1, mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
    }
    printf("--------------------------------\n");
}

/**
 * @brief Remove um item da mochila com base no nome.
 * @param mochila O vetor de itens.
 * @param totalItens Um ponteiro para o contador de itens.
 */
void removerItem(Item mochila[], int *totalItens) {
    if (*totalItens == 0) {
        printf("\nA mochila ja esta vazia. Nenhum item para remover.\n");
        return;
    }
    
    char nomeParaRemover[30];
    printf("\nDigite o nome do item que deseja remover: ");
    fgets(nomeParaRemover, 30, stdin);
    nomeParaRemover[strcspn(nomeParaRemover, "\n")] = 0;

    int indiceEncontrado = -1;
    // Laço 'for' para encontrar o índice do item a ser removido
    for (int i = 0; i < *totalItens; i++) {
        if (strcmp(mochila[i].nome, nomeParaRemover) == 0) {
            indiceEncontrado = i;
            break; // Para a busca assim que encontra o item
        }
    }

    // --- Documentação: Fluxo de Execução (Remover) ---
    // 1. Pede o nome do item a ser removido.
    // 2. Faz uma busca sequencial para encontrar o item no vetor.
    // 3. Se encontrar, 'puxa' todos os itens subsequentes uma posição para trás,
    //    sobrescrevendo o item a ser removido.
    // 4. Decrementa o contador 'totalItens'.
    // 5. Se não encontrar, informa ao jogador.
    if (indiceEncontrado != -1) {
        for (int i = indiceEncontrado; i < *totalItens - 1; i++) {
            mochila[i] = mochila[i + 1];
        }
        (*totalItens)--;
        printf("\nItem '%s' removido da mochila!\n", nomeParaRemover);
    } else {
        printf("\nItem '%s' nao encontrado na mochila.\n", nomeParaRemover);
    }
}

/**
 * @brief Busca um item pelo nome e exibe seus dados.
 * @param mochila O vetor de itens.
 * @param totalItens O número total de itens.
 */
void buscarItem(Item mochila[], int totalItens) {
    if (totalItens == 0) {
        printf("\nA mochila esta vazia. Nenhum item para buscar.\n");
        return;
    }

    char nomeParaBuscar[30];
    printf("\nDigite o nome do item que deseja buscar: ");
    fgets(nomeParaBuscar, 30, stdin);
    nomeParaBuscar[strcspn(nomeParaBuscar, "\n")] = 0;
    
    // --- Documentação: Busca Sequencial ---
    // A função implementa uma busca sequencial simples.
    // 1. Percorre o vetor item por item (sequencialmente).
    // 2. Compara o nome do item atual com o nome buscado usando 'strcmp'.
    // 3. Se encontrar uma correspondência, exibe os dados e para a busca.
    // 4. Se o laço terminar sem encontrar, informa que o item não existe.
    int encontrado = 0;
    for (int i = 0; i < totalItens; i++) {
        if (strcmp(mochila[i].nome, nomeParaBuscar) == 0) {
            printf("\n--- Item Encontrado! ---\n");
            printf("Nome: %s\n", mochila[i].nome);
            printf("Tipo: %s\n", mochila[i].tipo);
            printf("Quantidade: %d\n", mochila[i].quantidade);
            printf("------------------------\n");
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("\nItem '%s' nao foi encontrado na mochila.\n", nomeParaBuscar);
    }
}