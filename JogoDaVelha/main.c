#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

char **criarTabuleiro(){ 
    int i,j;
    char **tabuleiro = (char **)malloc(3 * sizeof(char *));
    for (i = 0; i < 3; i++){
        tabuleiro[i] = (char *)malloc(3 * sizeof(char));
        for (j = 0; j < 3; j++){
            tabuleiro[i][j] = ' ';
        }
    }
    return tabuleiro;
}

void mostrarTabuleiro(char **tabuleiro){
    int i,j;
    printf("\n     0  1  2\n\n");
    for (i = 0; i < 3; i++){
        printf("%d  ", i);
        for (j = 0; j < 3; j++){
            printf(" %c ", tabuleiro[i][j]);
            if (j < 2){
                printf("|");
            }
        }
        printf("\n");
        if (i < 2) {
            printf("    ---------\n");
        }
    }
    printf("\n");
}

int checarVencedor(char **tabuleiro, char letra){
    int i;
    for (i = 0; i < 3; i++){
        if ((tabuleiro[i][0] == letra && tabuleiro[i][1] == letra && tabuleiro[i][2] == letra) ||
            (tabuleiro[0][i] == letra && tabuleiro[1][i] == letra && tabuleiro[2][i] == letra)){
            return 1;
        }
    }
    if ((tabuleiro[0][0] == letra && tabuleiro[1][1] == letra && tabuleiro[2][2] == letra) ||
        (tabuleiro[0][2] == letra && tabuleiro[1][1] == letra && tabuleiro[2][0] == letra)){
        return 1;
    } 
    return 0;
}

int checarFinalDoJogo(char **tabuleiro){
    int i,j;
    for (i = 0; i < 3; i++){
        for (j = 0; j < 3; j++){
            if (tabuleiro[i][j] == ' '){
                return 0;
            }
        }
    }
    return 1;
}

int checarJogada(char **tabuleiro, int linha, int coluna){
    if (linha >= 0 && linha < 3 && coluna >= 0 && coluna < 3 && tabuleiro[linha][coluna] == ' '){
		return 1;
	}
	return 0;
}

void jogadorJoga(char **tabuleiro, char letra){
    int linha, coluna;
    do {
        printf("--> Informe a linha e a coluna: ");
        scanf("%d %d", &linha, &coluna);

        if (checarJogada(tabuleiro,linha,coluna) == 0){
            printf("Linha e Coluna inválidas\n\n");
        }

    } while (checarJogada(tabuleiro, linha, coluna) == 0);
    
    tabuleiro[linha][coluna] = letra;
}

void pcJoga(char **tabuleiro, char letra){
    int linha, coluna;
    do {
        linha = rand() % 3;
        coluna = rand() % 3;
        
    } while (checarJogada(tabuleiro, linha, coluna) == 0);
    
    tabuleiro[linha][coluna] = letra;
}

int main(){
	setlocale(LC_ALL,"Portuguese");
	
    int op = 0;
    char **tabuleiro;
    int jogadorAtual;
    int fim;
    int jogarNovamente;

    do{
        printf("------\t MENU\t------\n");
        printf("Escolha o modo de jogo:\n");
        printf("1. Jogador vs Jogador\n");
        printf("2. Jogador vs PC\n");
        printf("----------------------\n");
        printf("--> ");
        scanf("%d", &op);
		
        switch (op){
            case 1:
                system("cls");
                break;
            case 2:
                system("cls");
                break;
            default:
                printf("\nModo inválido. Por favor, escolha novamente.\n\n");
                continue;
        }
            tabuleiro = criarTabuleiro();
            jogadorAtual = 0;
            fim = 0;

            do{
                mostrarTabuleiro(tabuleiro);

                if (op == 1 || (op == 2 && jogadorAtual == 0)){
                    printf("Jogador %d (%c) ", jogadorAtual + 1, (jogadorAtual == 0) ? 'X' : 'O');
                    jogadorJoga(tabuleiro, (jogadorAtual == 0) ? 'X' : 'O');
                } else {
                    printf("PC:\n");
                    pcJoga(tabuleiro, 'O');
                }
                if (checarVencedor(tabuleiro, 'X')){
                    system("cls");
                    mostrarTabuleiro(tabuleiro);
                    printf("Jogador 1 venceu!\n\n");
                    fim = 1;

                } else if (checarVencedor(tabuleiro, 'O')){
                    system("cls");
                    mostrarTabuleiro(tabuleiro);
                    if (op == 1 || (op == 2 && jogadorAtual == 0)){
                        printf("Jogador 2 venceu!\n\n");
                    } else {
                        printf("PC venceu!\n\n");
                    }
                    fim = 1;

                } else if (checarFinalDoJogo(tabuleiro)){
                    system("cls");
                    mostrarTabuleiro(tabuleiro);
                    printf("Deu Velha!\n");
                    fim = 1;
                }

                jogadorAtual = (jogadorAtual + 1) % 2;

            } while (!fim);

            free(tabuleiro);

            printf("Deseja jogar novamente? 1 = Sim / 0 = Não\n--> ");
            scanf("%d", &jogarNovamente);
            if (jogarNovamente != 1){
                return 0;
            }
            else{
                op = 0;
            }
            system("cls");

    } while (op != 1 && op != 2);

    return 0;
}
