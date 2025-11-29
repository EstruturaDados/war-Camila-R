#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAX_TERRITORIO 5
int idMissao = -1; // -1 indica que a missão ainda não foi definida

typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

void cleanBuffer(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Função para alocar memória para os territórios
void alocMemoria(Territorio **territorio, int quantidade){
    *territorio = (Territorio *) calloc(MAX_TERRITORIO, sizeof(Territorio));
    if (*territorio == NULL) {
        printf("Error: Falha ao alocar memória.\n");
        exit(1);
    }
}

// Função que define o território
void defineTerritorio(Territorio *territorio){

    int totalTerritorio = 0;

    printf("=================================================\n");
    printf("========== DEFINA OS CINCO TERRITÓRIOS ==========\n");
    printf("=================================================\n\n");

    for (totalTerritorio; totalTerritorio < MAX_TERRITORIO; totalTerritorio++)
    {
        int indiceTerritorio = totalTerritorio + 1;
        printf("=================================================\n");
        printf("=========== Cadastre o território %d ============\n", indiceTerritorio);
        printf("=================================================\n");
        printf("\n");

        printf("Nome do território: ");
        fgets(territorio[totalTerritorio].nome, sizeof(territorio[totalTerritorio].nome), stdin);
        territorio[totalTerritorio].nome[strcspn(territorio[totalTerritorio].nome, "\n")] = '\0';

        printf("Cor do exército: ");
        fgets(territorio[totalTerritorio].cor, sizeof(territorio[totalTerritorio].cor), stdin);
        territorio[totalTerritorio].cor[strcspn(territorio[totalTerritorio].cor, "\n")] = '\0';

        printf("Número de tropas: ");
        scanf("%d", &territorio[totalTerritorio].tropas);

        printf("\n");

        cleanBuffer();
    }
}

// Função que mostra o mapa atual
void mapaAtual(Territorio *territorio){
    printf("\n=================================================\n");
    printf("========== MAPA DO MUNDO - ESTADO ATUAL =========\n");
    printf("=================================================\n");    

    for (int i = 0; i < MAX_TERRITORIO; i++)
    {
        int numero = i + 1;
        printf("[%d] %s (Exército %s, Tropas: %d)\n", numero, territorio[i].nome, territorio[i].cor, territorio[i].tropas);
    }
}

// Função que define e verifica a missão
int missao(Territorio *territorio){

    printf("\n=================================================\n");
    printf("================== SUA MISSÃO É =================\n");
    printf("=================================================\n");

    // só gera uma missão se ainda não tiver uma
    if (idMissao == -1){
        idMissao = rand() % MAX_TERRITORIO;
    }

    printf("\nDestruir o exército %s\n", territorio[idMissao].cor);

    return idMissao;
}

int validaMissao(Territorio *territorio){

    if (territorio[idMissao].tropas == 0){
        printf("\nMissão concluída!\n");
    } else {
        printf("\nVocê ainda não completou sua missão. Continue até finalizar a missão ou saia do jogo.\n");
    }

    return 0;
}

// Função para escolher o território atacante
int escolherAtacante(Territorio *territorio){

    printf("\n");
    printf("===============================================\n");
    printf("================ FASE DE ATAQUE ===============\n");
    printf("===============================================\n");

    printf("\n========= Escolha o território atacante =========\n\n");
    for (int i = 0; i < MAX_TERRITORIO; i++)
    {
        int indice = i + 1;
        printf("[%d] %s\n", indice, territorio[i].nome);
    };
    printf("[0] Sair do ataque\n\n");

    int escolhaAtacante;
    scanf("%d", &escolhaAtacante);
    cleanBuffer();

    return escolhaAtacante;
};

// Função para escolher o território defensor
int escolherDefensor(Territorio *territorio, int atacante){
    printf("\n===== Escolha o território defensor =====\n\n");
    for (int i = 0; i < MAX_TERRITORIO; i++)
    {
        if (i + 1 != atacante)
        {
            int indice = i + 1;
            printf("[%d] %s\n", indice, territorio[i].nome);
        }
    };

    printf("\n");

    int escolhaDefensor;
    scanf("%d", &escolhaDefensor);
    cleanBuffer();

    return escolhaDefensor;
};

// Função para rolar o dado
int rolarDado(){
    return (rand() % 6) + 1;
}

// Função para sortear o valor do atacante e do defensor
int sorteAtacante(){
    return rolarDado();
}
int sorteDefensor(){
    return rolarDado();
}

// Função para comparar os dados rolados
void compararDados(Territorio *territorio, int escolhaAtacante, int escolhaDefensor){

    printf("\n");
    printf("==================================================\n");
    printf("============== RESULTADO DA BATALHA ==============\n");
    printf("==================================================\n");
    printf("\n");

    int dadoA = sorteAtacante();
    int dadoD = sorteDefensor();
    
    printf("Ataque (%s): %d | Defesa (%s): %d\n", 
            territorio[escolhaAtacante - 1].nome, dadoA,
            territorio[escolhaDefensor - 1].nome, dadoD);
    if (dadoA > dadoD){
        printf("VITORIA DO ATAQUE! O defensor perdeu 1 tropa\n\n");
        territorio[escolhaDefensor - 1].tropas -= 1;
    }
    else {
        printf("VITORIA DA DEFESA! O atacante perdeu 1 tropa\n\n");
        territorio[escolhaAtacante - 1].tropas -= 1;
    }
}

// Função para simular ataque entre territórios
void atacarTerritorio(Territorio *territorio){

    int escolhaAtacante = escolherAtacante(territorio);
    if (escolhaAtacante == 0)
    {
        printf("Saindo do ataque...\n");
        return 0;
    }
    int escolhaDefensor = escolherDefensor(territorio, escolhaAtacante);

    char nextRound = "\n";
    while (nextRound)
    {
        compararDados(territorio, escolhaAtacante, escolhaDefensor);
        printf("\nPressione a tecla 'Enter' para o próximo round...");
        getchar();

        blocoFuncoes(territorio);

        cleanBuffer();
    }
}

// Função do menu de ações
void menuDeAcoes(Territorio *territorio){
    int escolhaAcao;

    do {
        printf("\n");
        printf("===================================================\n");
        printf("================== MENU DE AÇÕES ==================\n");
        printf("===================================================\n");
        printf("\n");
        printf("1 - Atacar\n");
        printf("2 - Verificar Missão\n");
        printf("0 - Sair\n");
        printf("\n");
        printf("Escolha sua ação: ");

        scanf("%d", &escolhaAcao);
        cleanBuffer();

        switch (escolhaAcao)
        {
            case 1:
                atacarTerritorio(territorio);
                break;
            case 2:
                validaMissao(territorio);
                mapaAtual(territorio);
                break;
            case 0:
                printf("\nSaindo do jogo...\n");
                return 0;
            default:
                printf("\nOpção inválida!\n");
        }

    } while (escolhaAcao != 0);
}


// Função que engloba 3 funções
void blocoFuncoes(Territorio *territorio){
    mapaAtual(territorio);
    missao(territorio);
    menuDeAcoes(territorio);
}

int main(){

    Territorio *territorio = NULL;
    alocMemoria(&territorio, MAX_TERRITORIO);
    srand(time(NULL));

    defineTerritorio(territorio);
    blocoFuncoes(territorio);

    free(territorio);
    printf("\nMemória liberada com sucesso!\n");

    return 0;
}