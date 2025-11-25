#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAX_TERRITORIO 5

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

// Função para escolher o território atacante
int escolherAtacante(Territorio *territorio){

    printf("=================================================\n");
    printf("================= FASE DE ATAQUE ================\n");
    printf("=================================================\n");

    printf("\n======= Escolha o território atacante =======\n\n");
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
int compararDados(Territorio *territorio, int escolhaAtacante, int escolhaDefensor, int dadoAtacante, int dadoDefensor){

    printf("\n");
    printf("==================================================\n");
    printf("============== RESULTADO DA BATALHA ==============\n");
    printf("==================================================\n");
    printf("\n");
    printf("\n");

    printf("O atacante (%s) rolou um dado e tirou: %d\n",
           territorio[escolhaAtacante - 1].nome,
           dadoAtacante);

    printf("O defensor (%s) rolou um dado e tirou: %d\n\n",
           territorio[escolhaDefensor - 1].nome,
           dadoDefensor);

    return dadoAtacante > dadoDefensor;
}

// Função para simular ataque entre territórios
void atacarTerritorio(Territorio *territorio, int escolhaAtacante, int escolhaDefensor){

    int dadoA = sorteAtacante();
    int dadoD = sorteDefensor();
    int resultado = compararDados(territorio, escolhaAtacante, escolhaDefensor, dadoA, dadoD);

    if (resultado){
        printf("VITORIA DO ATAQUE! O Defensor (%s) perdeu 1 tropa\n\n", territorio[escolhaDefensor - 1].nome);
        territorio[escolhaDefensor - 1].tropas -= 1;
    }
    else {
        printf("VITORIA DO DEFENSOR! O Atacante (%s) perdeu 1 tropa\n\n",territorio[escolhaAtacante - 1].nome);
        territorio[escolhaAtacante - 1].tropas -= 1;
    }
}

int main(){

    Territorio *territorio = NULL;
    alocMemoria(&territorio, MAX_TERRITORIO);
    
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

    char nextRound = "\n";
    while (nextRound)
    {
        printf("=================================================\n");
        printf("===========MAPA DO MUNDO - ESTADO ATUAL==========\n");
        printf("=================================================\n");    
    
        for (int i = 0; i < totalTerritorio; i++)
        {
            int numero = i + 1;
            printf("\n[%d] %s (Exército %s, Tropas: %d)\n", numero, territorio[i].nome, territorio[i].cor, territorio[i].tropas);
        }
        printf("\n");
        
        int escolhaAtacante = escolherAtacante(territorio);
        if (escolhaAtacante == 0)
        {
            printf("Saindo do ataque...\n");
            return 0;
        }
        int escolhaDefensor = escolherDefensor(territorio, escolhaAtacante);

        atacarTerritorio(territorio, escolhaAtacante, escolhaDefensor);
       
        if (territorio[escolhaAtacante - 1].tropas == 0)
        {
            printf("==================================================\n");
            printf("\n============== CONQUISTA COMPLETA! =============\n");
            printf("O território %s foi dominado pelo Exército %s\n", territorio[escolhaAtacante - 1].nome, territorio[escolhaDefensor - 1].cor, territorio[escolhaDefensor - 1].nome);
            printf("==================================================\n");
            printf("\n\n============== Fim do jogo ==============\n\n\n");
            break;
        }
        if (territorio[escolhaDefensor - 1].tropas == 0)
        {
            printf("==============================================================\n");
            printf("==================== CONQUISTA COMPLETA! ===================\n\n");
            printf("O território %s foi dominado pelo Exército %s do território %s\n", territorio[escolhaDefensor - 1].nome, territorio[escolhaAtacante - 1].cor, territorio[escolhaAtacante - 1].nome);
            printf("==============================================================\n");
            printf("\n\n==================== Fim do jogo ====================\n\n\n");
            break;
        }
        
        printf("\nPressione a tecla 'Enter' para o próximo round...");
        getchar();
        cleanBuffer();
    }
    
    free(territorio);

    return 0;
}