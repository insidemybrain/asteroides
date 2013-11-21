/*
------------------------------------------------------------------------------------------------
|                                                                                              |
|               _______                                   _      _                             |             
|              (_______)         _                       (_)    | |                            |             
|               _______   ___  _| |_  _____   ____  ___   _   __| | _____   ___                |
|              |  ___  | /___)(_   _)| ___ | / ___)/ _ \ | | / _  || ___ | /___)               |
|              | |   | ||___ |  | |_ | ____|| |   | |_| || |( (_| || ____||___ |               |
|              |_|   |_|(___/    \__)|_____)|_|    \___/ |_| \____||_____)(___/                |
|                                         Projeto 2013                                         |
|                                                                                              |
|                     Trabalho de Laboratório de Computação 1 - IM-UFRRJ 2013                  |
|                          Participantes                                                       |
|				- Fellipe Bravo Ribeiro Pimentel                               |
|				- Paulo Roberto Xavier                                         |
|				- Bianca Albuquerque                                           |
|                                                                                              |
------------------------------------------------------------------------------------------------
*/


#include <stdio.h>
#include <stdlib.h>
#define NOME_MAX 21 //Define o máximo de caracteres possíveis para o Nick do jogador
#define PONTUACAO_MAX 999999 //Define o máximo de pontos que um jogador conseguirá obter

int main(){
	//int menu = 0;
	int opcao = 0;
	/*
	-- Apenas deixar definido para utilização posterior
	int i = 0;
	while(i < 10){ i = i+1; printf("Valor de I: %d \n",i); };
	int pontuacao = 0;*/
		printf("\t-----------------------------------------------------------------------\n");
		printf("\t|   _______                                   _      _                |\n");
		printf("\t|  (_______)         _                       (_)    | |               |\n");
		printf("\t|   _______   ___  _| |_  _____   ____  ___   _   __| | _____   ___   |\n");
		printf("\t|  |  ___  | /___)(_   _)| ___ | / ___)/ _ \\ | | / _  || ___ | /___)  |\n");
		printf("\t|  | |   | ||___ |  | |_ | ____|| |   | |_| || |( (_| || ____||___ |  |\n");
		printf("\t|  |_|   |_|(___/    \\__)|_____)|_|    \\___/ |_| \\____||_____)(___/   |\n");
		printf("\t|                           Projeto 2013                              |\n");
		printf("\t|       Trabalho de Laboratorio de Computação 1 - IM-UFRRJ 2013       |\n");
		printf("\t|---------------------------------------------------------------------|\n");
		printf("\t|                   Fellipe Bravo Ribeiro Pimentel                    |\n");
		printf("\t|                      Paulo Roberto Xavier                           |\n");
		printf("\t|                       Bianca Albuquerque                            |\n");
		printf("\t-----------------------------------------------------------------------\n\n");

		//while(menu == 0) { -- Retirado Temporariamente, pois ainda não há necessidade
			printf("\t\t     ---------------------------------------------\n");
			printf("\t\t     |               MENU DE JOGO                |\n");
			printf("\t\t     ---------------------------------------------\n");
			printf("\t\t     | 1. Jogar!                                 |\n");
			printf("\t\t     | 2. Ranking                                |\n");
			printf("\t\t     | 3. Loja de Utilidades                     |\n");
			printf("\t\t     | 4. Opção 4 (Pensar em Algo)               |\n");
			printf("\t\t     | 0. Sair do Jogo                           |\n");
			printf("\t\t     ---------------------------------------------\n");


			printf("\t\t\t   Digite o número da sua opção: ");
			scanf("%d",&opcao);

			switch(opcao){
			case 0:
				printf("\t\t\t       Até mais!\n");
				break;
			case 1:
				printf("\t\t\t       JOGO - Ainda em criação!\n");
				break;
			case 2:
				system("clear");
				printf("\t\t   -------------------------------------------------------\n");
				printf("\t\t   |                 Ranking de Jogadores                |\n");
				printf("\t\t   -------------------------------------------------------\n");
				printf("\t\t   |     COLOCAÇÃO  |    NICKNAME    |     PONTUAÇÃO     |\n");
				printf("\t\t   -------------------------------------------------------\n");
				/*
				     Futuramente utilização de:
				printf("\t\t   | Nº Lugar - %s   PONTOS: %u   |\n",jogadorN,pontosN);
				
					E também alguma função para verificar quantidade de caracteres em nomes e pontos,
					completando-os com espaços, para que não seja perdida a formatação do Ranking.
					Algo como:
						ESPAÇOS = NICK-NOME_MAX
						if(NICK < NOME_MAX){
							NICK = NICK+ESPAÇOS
						}
				*/
				printf("\t\t   | 1º Lugar -   NOMEDEATE21CARACTERES   PONTOS: %u |\n",PONTUACAO_MAX);
				printf("\t\t   | --------------------------------------------------- |\n");
				printf("\t\t   | 2º Lugar -   NOMEDEATE21CARACTERES   PONTOS: %u |\n",PONTUACAO_MAX);
				printf("\t\t   | --------------------------------------------------- |\n");
				printf("\t\t   | 3º Lugar -   NOMEDEATE21CARACTERES   PONTOS: %u |\n",PONTUACAO_MAX);
				printf("\t\t   | --------------------------------------------------- |\n");
				printf("\t\t   | 4º Lugar -   NOMEDEATE21CARACTERES   PONTOS: %u |\n",PONTUACAO_MAX);
				printf("\t\t   | --------------------------------------------------- |\n");
				printf("\t\t   | 5º Lugar -   NOMEDEATE21CARACTERES   PONTOS: %u |\n",PONTUACAO_MAX);
				printf("\t\t   | --------------------------------------------------- |\n");
				printf("\t\t   | 6º Lugar -   NOMEDEATE21CARACTERES   PONTOS: %u |\n",PONTUACAO_MAX);
				printf("\t\t   | --------------------------------------------------- |\n");
				printf("\t\t   | 7º Lugar -   NOMEDEATE21CARACTERES   PONTOS: %u |\n",PONTUACAO_MAX);
				printf("\t\t   | --------------------------------------------------- |\n");
				printf("\t\t   | 8º Lugar -   NOMEDEATE21CARACTERES   PONTOS: %u |\n",PONTUACAO_MAX);
				printf("\t\t   | --------------------------------------------------- |\n");
				printf("\t\t   | 9º Lugar -   NOMEDEATE21CARACTERES   PONTOS: %u |\n",PONTUACAO_MAX);
				printf("\t\t   | --------------------------------------------------- |\n");
				printf("\t\t   | 10º Lugar -  NOMEDEATE21CARACTERES   PONTOS: %u |\n",PONTUACAO_MAX);
				printf("\t\t   | --------------------------------------------------- |\n");
				break;

			/*
			 -- Ao terminar o jogo, caso a pontuação seja maior que o alguma pontuação, adiciona o nick no Ranking --
			 -- Utilização posterior --

			if(pontuacao > pontuacao){
			printf("Favor digite um nick para ser lembrado: ");
			scanf("%s",nome);
			return 0;
			} else {
			return 0;
			}
			*/
			case 3:
				printf("\t\t\t       LOJA - Ainda em criação!\n");
				break;
			case 4:
				printf("\t\t\t       OPÇÃO 4 - Ainda em criação!\n");
				break;
			default:
				printf("\t\t\t       Opção inválida, digite uma das opções.\n");
				break;
			}
		//return 0;
		//}
return 0;	
}
