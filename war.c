#include <stdio.h>
#include <string.h>

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

int main(){

    // Limitando o território
    Territorio territorio[MAX_TERRITORIO];
    int totalTerritorio = 0;

    // Definindo o território
    printf("=================================================\n");
    printf("===========DEFINA OS CINCO TERRITÓRIOS===========\n");

    for (totalTerritorio; totalTerritorio < MAX_TERRITORIO; totalTerritorio++)
    {
        int indiceTerritorio = totalTerritorio + 1;
        printf("=================================================\n");
        printf("============Cadastre o território %d=============\n", indiceTerritorio);
        printf("=================================================\n");

        printf("Nome do território: ");
        fgets(territorio[totalTerritorio].nome, sizeof(territorio[totalTerritorio].nome), stdin);
        territorio[totalTerritorio].nome[strcspn(territorio[totalTerritorio].nome, "\n")] = '\0';

        printf("Cor do exército: ");
        fgets(territorio[totalTerritorio].cor, sizeof(territorio[totalTerritorio].cor), stdin);
        territorio[totalTerritorio].cor[strcspn(territorio[totalTerritorio].cor, "\n")] = '\0';

        printf("Número de tropas: ");
        scanf("%d", &territorio[totalTerritorio].tropas);

        cleanBuffer();
    }

    // Printando os territórios definidos
    printf("=================================================\n");
    printf("========ESTES SÃO OS TERRITÓRIOS DEFINIDOS=======\n");
    printf("=================================================\n");    

    for (int i = 0; i < totalTerritorio; i++)
    {
        printf("TERRITÓRIO %d\n", i + 1);
        printf("   - Nome do território: %s\n", territorio[i].nome);
        printf("   - Cor do exército: %s\n", territorio[i].cor);
        printf("   - Número de tropas: %s\n", territorio[i].nome);
        printf("=================================================\n");
    }

}