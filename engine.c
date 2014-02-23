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
|				- Bianca Albuquerque                                           |
|				- Fellipe Bravo Ribeiro Pimentel                               |
|				- Paulo Roberto Xavier                                         |
|                                                                                              |
------------------------------------------------------------------------------------------------
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_rotozoom.h"
#include "engine.h"
void Menu();
void Jogar();
void Pause();
void Utilidades();
void Habilidades();
void InformacoesJogador();
void CondicaoTeclado();
int EventosMenu();
int EventosPause();
int EventosHabilidades();
int EventosUtilidades();
int EventosGerais();
int EventosRanking();
void Sair();

int main(int argc, char *argv[]){
	// -----------------------------------------------------------------------------------------------------
	//               Antes de Iniciar o Jogo, é pedido para que o jogar insira seu nick no terminal
	// -----------------------------------------------------------------------------------------------------
	LogoASCII();
	printf("\t\t\t\t\t\t    Bem-vindo ao Projeto 2013 Asteroides.\n");
	printf("\t\t\t------------------------------------------------------------------------------------------------\n\n");
	printf("\t\t\t\tAntes de inciarmos o jogo,\n");
	printf("\t\t\t\tpor favor digite o nick que desejas utilizar: \n\n");
	printf("\t\t\t------------------------------------------------------------------------------------------------\n\n");
	scanf("%s",nick);
	printf("\n\n");
	printf("\t\t\t------------------------------------------------------------------------------------------------\n\n");
	printf("\t\t\t\tOlá %s, recomendamos que você veja todas as informacoes antes de jogar!\n", nick);
	printf("\t\t\t\t\t\t\t    Tenha um bom jogo!\n");

	SDL_Delay(1700);

	// -----------------------------------------------------------------------------------------------------
	//                                  Definições gerais para Inicialização
	// -----------------------------------------------------------------------------------------------------
	/* Inicialização da Janela */
	SDL_Init(SDL_INIT_VIDEO);
	/* Inicialização da Fonte */
	TTF_Init();

	/* Todas as Configurações Iniciais do SDL */
	ConfSDL();

	while(menuAberto == 1){
		Menu(); // Chamando a Função Menu
			while(ranking == 1){
				RankingVisual();
			}
	}

	while(jogando == 1){
		Jogar(); //Chamando a Função Jogar

		while(ranking == 1){
			RankingVisual();
		}

		while(pause == 1){
			Pause(); //Chamando o Modo de Espera
		}

		while(utilidades == 1){
			Utilidades(); //Chamando a Loja de Utilidades
		}

		while(habilidades == 1){
			Habilidades(); //Chamando a Janela de Habilidades
		}
	}

	TTF_Quit();
        SDL_Quit();
	system("clear");
	return 0;
}


// -----------------------------------------------------------------------------------------------------
// Função para Iniciar o Jogo em si.
// -----------------------------------------------------------------------------------------------------
void Jogar(){
	// -----------------------------------------------------------------------------------------------------
	//                              Inicializações Fundamentais da Função Jogar();
	// -----------------------------------------------------------------------------------------------------
	Condicoes();
	while(SDL_PollEvent(&evento)){ EventosGerais(evento); }
	   SDL_UpdateRect(janela_Jogo, 0, 0, 0, 0);

	// ---------------------------------------------------------------------------
	/* Desenha o Espaço por completo */
	SDL_BlitSurface(espaco, NULL, janela_Jogo, NULL);

	// ---------------------------------------------------------------------------
	//    Controle de Frames
	//     ~ Feito por Gabriel Segobia
	// ---------------------------------------------------------------------------
		if(1000/FRAMERATE > SDL_GetTicks() - start){
			SDL_Delay(1000/FRAMERATE - (SDL_GetTicks() - start));
		}
		sprintf(notificacao, "FPS: %d", 1000/FRAMERATE);
		escreverTexto(1,LARGURA-60,5,notificacao,150,150,150,13);

	// ---------------------------------------------------------------------------
	/* Chama janela do Jogador com todas suas informações */
	InformacoesJogador();

	// ---------------------------------------------------------------------------
	/* Desenha Botão da Loja de Utilidades */
	SDL_BlitSurface(imgUtilidades, NULL, janela_Jogo, &imagemUtilidades);

	// ---------------------------------------------------------------------------	
	/* Desenha Botão da Loja de Utilidades */
	SDL_BlitSurface(imgHabilidades, NULL, janela_Jogo, &imagemHabilidades);

	// ---------------------------------------------------------------------------
	/* Desenha o Tiro da nave */
	if(atirar == 1){ SDL_BlitSurface(tiro, NULL, janela_Jogo, &tiroTotal); }

	// ---------------------------------------------------------------------------
	/* Modificar Ponto Central da Nave */
	SDL_Rect PosicaoNave={(int)x,(int)y,0,0};
	PosicaoNave.x -= naveAngulo->w/2-nave->w/2;
	PosicaoNave.y -= naveAngulo->h/2-nave->h/2;

	protecaoAngulo = rotozoomSurface(protecao,angulo,1.0,0);
	SDL_Rect PosicaoProtecao={(int)x,(int)y,0,0};
	PosicaoProtecao.x -= protecaoAngulo->w/2-nave->w/2;
	PosicaoProtecao.y -= protecaoAngulo->h/2-nave->w/2;

	acelerarAngulo = rotozoomSurface(acelerar,angulo,1.0,0);
	/* Desenha a Nave && Proteção */
 	if(imunidade == 1){ SDL_BlitSurface(protecaoAngulo, NULL, janela_Jogo, &PosicaoProtecao); }
	SDL_BlitSurface(naveAngulo, NULL, janela_Jogo, &PosicaoNave);
}



// -----------------------------------------------------------------------------------------------------
// Função para Iniciar o MENU
// -----------------------------------------------------------------------------------------------------
void Menu(){

	// -----------------------------------------------------------------------------------------------------
	//                            Inicializações Fundamentais da Função Menu();
	// -----------------------------------------------------------------------------------------------------
	while(SDL_PollEvent(&evento)){ EventosMenu(evento); }
	   SDL_UpdateRect(janela_Menu, 0, 0, 0, 0);

	// ---------------------------------------------------------------------------
	/* Desenha o Espaço por completo */
	SDL_BlitSurface(espaco, NULL, janela_Menu, NULL);

	/* Desenha LOGO */
	SDL_BlitSurface(logo, NULL, janela_Menu, &imagemLogo);

	/* Desenha Imagem JOGAR (MENU) */
	SDL_BlitSurface(botaoMenu1, NULL, janela_Menu, &imgbotaoMenu1);

	/* Desenha Imagem INFORMAÇÕES (MENU) */
	SDL_BlitSurface(botaoMenu2, NULL, janela_Menu, &imgbotaoMenu2);

	/* Desenha Imagem RANKING (MENU) */
	SDL_BlitSurface(botaoMenu3, NULL, janela_Menu, &imgbotaoMenu3);

	/* Desenha Imagem SAIR (MENU) */
	SDL_BlitSurface(botaoMenu4, NULL, janela_Menu, &imgbotaoMenu4);

}


// -----------------------------------------------------------------------------------------------------
// Função para Iniciar a Janela de Utilidades
// -----------------------------------------------------------------------------------------------------
void Utilidades(){

	// -----------------------------------------------------------------------------------------------------
	//                            Inicializações Fundamentais da Função Utilidades();
	// -----------------------------------------------------------------------------------------------------
	while(SDL_PollEvent(&evento)){ EventosUtilidades(evento); }
	   SDL_UpdateRect(janela_Utilidades, 0, 0, 0, 0);

	// ---------------------------------------------------------------------------
	/* Desenha o Espaço por completo */
	SDL_BlitSurface(espaco2, NULL, janela_Utilidades, NULL);

	// ---------------------------------------------------------------------------
	/* Chama janela do Jogador com todas suas informações */
	InformacoesJogador();

	// ---------------------------------------------------------------------------
	/* Desenha Botão da Loja de Utilidades */
	SDL_BlitSurface(imgUtilidades, NULL, janela_Utilidades, &imagemUtilidades);

	/* Desenha Imagem SAIR (MENU) */
	SDL_BlitSurface(botaoMenu4, NULL, janela_Utilidades, &imgbotaoMenu4);

	// ---------------------------------------------------------------------------	
	/* Mensagem da Janela de Habilidades */
	sprintf(notificacao,"Você está na Loja de Utilidades");
	escreverTexto(3,330,200,notificacao,20,40,60,22);
	sprintf(notificacao,"Selecione abaixo o que desejas comprar para melhorar sua nave");
	escreverTexto(3,265,240,notificacao,20,40,60,14);
	sprintf(notificacao,"ou clique em sair, para voltar ao jogo.");
	escreverTexto(3,350,260,notificacao,20,40,60,14);

	// ---------------------------------------------------------------------------	
	sprintf(notificacao,"[Completar o Combustível]");
	escreverTexto(3,imgCombustivel.x-45,imgCombustivel.y-25,notificacao,255,60,0,14);
	/* Desenha Imagem de Combustível */
	SDL_BlitSurface(imgIconeCombustivel, NULL, janela_Utilidades, &imgCombustivel);

	sprintf(notificacao,"Preço: $ %.2f",Preco_Combustivel);
	escreverTexto(3,imgCombustivel.x-10,imgCombustivel.y+imgCombustivel.h,notificacao,255,60,0,14);

	// ---------------------------------------------------------------------------	
	sprintf(notificacao,"[Comprar uma Vida]");
	escreverTexto(3,imgVidas_Utilidade.x-25,imgVidas_Utilidade.y-30,notificacao,255,60,0,14);
	/* Desenha Imagem de Vida (LOJA) */
	SDL_BlitSurface(imgIconeVida, NULL, janela_Utilidades, &imgVidas_Utilidade);

	sprintf(notificacao,"Preço: $ %.2f",Preco_Vida);
	escreverTexto(3,imgVidas_Utilidade.x-10,imgVidas_Utilidade.y+imgCombustivel.h,notificacao,255,60,0,14);

}

// -----------------------------------------------------------------------------------------------------
// Função para Iniciar a Janela de Habilidades
// -----------------------------------------------------------------------------------------------------
void Habilidades(){

	// -----------------------------------------------------------------------------------------------------
	//                            Inicializações Fundamentais da Função Habilidades();
	// -----------------------------------------------------------------------------------------------------
	while(SDL_PollEvent(&evento)){ EventosHabilidades(evento); }
	   SDL_UpdateRect(janela_Habilidades, 0, 0, 0, 0);

	// ---------------------------------------------------------------------------
	/* Desenha o Espaço por completo */
	SDL_BlitSurface(espaco2, NULL, janela_Habilidades, NULL);

	// ---------------------------------------------------------------------------
	/* Chama janela do Jogador com todas suas informações */
	InformacoesJogador();

	// ---------------------------------------------------------------------------	
	/* Desenha Botão da Loja de Habilidades */
	SDL_BlitSurface(imgHabilidades, NULL, janela_Habilidades, &imagemHabilidades);

	// ---------------------------------------------------------------------------	
	/* Desenha Imagem SAIR (MENU) */
	SDL_BlitSurface(botaoMenu4, NULL, janela_Habilidades, &imgbotaoMenu4);

	// ---------------------------------------------------------------------------	
	/* Mensagem da Janela de Habilidades */
	sprintf(notificacao,"Você está na Janela de Habilidades");
	escreverTexto(3,310,200,notificacao,20,40,60,22);
	sprintf(notificacao,"Selecione abaixo o que desejas comprar para melhorar sua nave");
	escreverTexto(3,265,240,notificacao,20,40,60,14);
	sprintf(notificacao,"ou clique em sair, para voltar ao jogo.");
	escreverTexto(3,350,260,notificacao,20,40,60,14);

	// ---------------------------------------------------------------------------	
	/* Desenha Imagem de Combustível */
	sprintf(notificacao,"[Escudo de Proteção]");
	escreverTexto(3,imgCombustivel.x-30,imgCombustivel.y-25,notificacao,255,60,0,14);
	SDL_BlitSurface(imgHab1, NULL, janela_Utilidades, &imgHabilidade1);

	sprintf(notificacao,"Preço: $ %.2f",Preco_Hab1);
	escreverTexto(3,imgCombustivel.x-10,imgCombustivel.y+imgCombustivel.h,notificacao,255,60,0,14);

	// ---------------------------------------------------------------------------	
	/* Desenha Imagem das Vidas (LOJA) */
	sprintf(notificacao,"[Tiro Triplo]");
	escreverTexto(3,imgVidas_Utilidade.x+5,imgVidas_Utilidade.y-30,notificacao,255,60,0,14);
	SDL_BlitSurface(imgHab2, NULL, janela_Utilidades, &imgHabilidade2);

	sprintf(notificacao,"Preço: $ %.2f",Preco_Hab2);
	escreverTexto(3,imgVidas_Utilidade.x-10,imgVidas_Utilidade.y+imgCombustivel.h,notificacao,255,60,0,14);

}


// -----------------------------------------------------------------------------------------------------
// Função para Pausar o Jogo
// -----------------------------------------------------------------------------------------------------
void Pause(){

	// -----------------------------------------------------------------------------------------------------
	//                            Inicializações Fundamentais da Função Habilidades();
	// -----------------------------------------------------------------------------------------------------
	while(SDL_PollEvent(&evento)){ EventosPause(evento); }
	   SDL_UpdateRect(janela_Pause, 0, 0, 0, 0);

	// ---------------------------------------------------------------------------
	/* Desenha o Espaço por completo */
	SDL_BlitSurface(espaco2, NULL, janela_Pause, NULL);

	// ---------------------------------------------------------------------------
	/* Chama janela do Jogador com todas suas informações */
	InformacoesJogador();

	// ---------------------------------------------------------------------------	
	/* Desenha Imagem SAIR (MENU) */
	SDL_BlitSurface(botaoMenu4, NULL, janela_Pause, &imgbotaoMenu4);

	// ---------------------------------------------------------------------------	
	/* Mensagem da Janela de Habilidades */
	sprintf(notificacao,"Você está com o Jogo em Modo de Espera.");
	escreverTexto(5,110,200,notificacao,20,40,60,40);
}


// -----------------------------------------------------------------------------------------------------
// Todas as informações do Jogador na Tela (HUD)
// -----------------------------------------------------------------------------------------------------
void InformacoesJogador(){

	// ---------------------------------------------------------------------------
	/* Desenha a Imagem do Jogador */
	SDL_BlitSurface(imgJogador, NULL, janela_Jogo, &imagemJogador);
	/* Escreve o nick do jogador, em cima da imagem */
	escreverTexto(1,25,20,nick,255,158,80,13);

	// ---------------------------------------------------------------------------
	/* Escreve a Pontuação na tela */
	sprintf(txtpontos, "Pontuação: %d", pontuacao);
	escreverTexto(1,170,5,txtpontos,255,158,80,14);

	// ---------------------------------------------------------------------------
	/* Escreve o Dinheiro na tela */
	sprintf(txtpontos, "Dinheiro: $ %.2f", dinheiro);
	escreverTexto(1,170,25,txtpontos,255,158,80,14);

	// ---------------------------------------------------------------------------
	/* Escreve o Combustivel na tela */				
	sprintf(txtcombustivel, "Combustível: %d", combustivel);
	escreverTexto(1,170,45,txtcombustivel,255,158,80,14);

	// ---------------------------------------------------------------------------
	/* Escreve a Vida na tela */
	sprintf(txtvidas, "Vidas:");
	escreverTexto(1,170,65,txtvidas,255,0,0,16);
		SDL_BlitSurface(imgVida1, NULL, janela_Jogo, &vida1);
		if(vida >= 2){ SDL_BlitSurface(imgVida2, NULL, janela_Jogo, &vida2); }
		if(vida == 3){ SDL_BlitSurface(imgVida3, NULL, janela_Jogo, &vida3); }
}



// -----------------------------------------------------------------------------------------------------
// Função para verificar todos os eventos (mouse, teclado) enquanto está dentro do JOGO.
// -----------------------------------------------------------------------------------------------------
int EventosGerais(SDL_Event evento){

	switch (evento.type) {

		/* Fecha o "looping" do programa ao clicar no "X" de fechar o programa */
		case SDL_QUIT: Sair(); break;

		// -----------------------------------
		// -- Eventos relacionados ao Mouse --
		// -----------------------------------
		case SDL_MOUSEBUTTONDOWN:
			switch (evento.button.button){
				case SDL_BUTTON_LEFT:

			// ----------------------------------------------------------
			//               Abrir Loja de Utilidades (JOGANDO)
			// ----------------------------------------------------------
			if(
			   evento.button.x >= imagemUtilidades.x &&
			   evento.button.x <= (imagemUtilidades.w+imagemUtilidades.x) &&
			   evento.button.y >= imagemUtilidades.y &&
			   evento.button.y <= (imagemUtilidades.h+imagemUtilidades.y)
			){
			   utilidades = 1;
			}

			// ----------------------------------------------------------
			//               Abrir Janela de Habilidades (JOGANDO)
			// ----------------------------------------------------------
			if(
			   evento.button.x >= imagemHabilidades.x &&
			   evento.button.x <= (imagemHabilidades.w+imagemHabilidades.x) &&
			   evento.button.y >= imagemHabilidades.y &&
			   evento.button.y <= (imagemHabilidades.h+imagemHabilidades.y)
			){
			   habilidades = 1;
			}
			break;	
			}
		break;


		// -----------------------------------
		// - Eventos relacionados ao Teclado -
		// -----------------------------------

		/* Pressionar tecla */
		case SDL_KEYDOWN:
			switch (evento.key.keysym.sym) {

				/* Fecha o "looping" do programa, e pula para o SDL_Quit() */
				case SDLK_ESCAPE: CondicaoTeclado(); break;

				/* Adiciona 2 no total do angulo da nave, SEM deslocamento */
				case SDLK_LEFT: angulo += 2; break;

				/* Remove 2 no total do angulo da nave, SEM deslocamento */
				case SDLK_RIGHT: angulo -= 2; break;

				/* Subtrai 1 para o Y da nave, deslocamento SUPERIOR */
				case SDLK_UP:
					if(velocidade < ACELERACAO_MAX){ velocidade += 0.3; }
					combustivel -= velocidade;
				break;

				case SDLK_RETURN:
					pause = 1;
				break;

				case SDLK_SPACE:
					atirar = 1;
					anguloTiro = angulo;
					tiroTotal.x = centroNave.x;
					tiroTotal.y = centroNave.y;
				break;

				/* Qualquer outra tecla que se aperte, nada acontecerá */
				default: break;
	}
	break;
}
return 0;
}


// -----------------------------------------------------------------------------------------------------
// Função para verificar todos os eventos (mouse, teclado) enquanto está dentro do MENU.
// -----------------------------------------------------------------------------------------------------
int EventosMenu(SDL_Event evento){

	switch (evento.type) {

		/* Fecha o "looping" do programa ao clicar no "X" de fechar o programa */
		case SDL_QUIT: Sair(); break;

		// -----------------------------------
		// -- Eventos relacionados ao Mouse --
		// -----------------------------------
		case SDL_MOUSEBUTTONDOWN:
			switch (evento.button.button){
				case SDL_BUTTON_LEFT:
			// ----------------------------------------------------------
			//               Abrir o Jogo - BOTÃO JOGAR (MENU)
			// ----------------------------------------------------------
			if(
			   evento.button.x >= imgbotaoMenu1.x &&
			   evento.button.x <= (imgbotaoMenu1.w+imgbotaoMenu1.x) &&
			   evento.button.y >= imgbotaoMenu1.y &&
			   evento.button.y <= (imgbotaoMenu1.h+imgbotaoMenu1.y)
			){
			   menuAberto = 0;
			   jogando = 1;
			}


			// ----------------------------------------------------------
			//       Abrir as Informações - BOTÃO INFORMAÇÕES (MENU)
			// ----------------------------------------------------------
			if(
			   evento.button.x >= imgbotaoMenu2.x &&
			   evento.button.x <= (imgbotaoMenu2.w+imgbotaoMenu2.x) &&
			   evento.button.y >= imgbotaoMenu2.y &&
			   evento.button.y <= (imgbotaoMenu2.h+imgbotaoMenu2.y)
			){
			  LogoASCII();
			}


			// ----------------------------------------------------------
			//            Abrir o Ranking - BOTÃO RANKING (MENU)
			// ----------------------------------------------------------
			if(
			   evento.button.x >= imgbotaoMenu3.x &&
			   evento.button.x <= (imgbotaoMenu3.w+imgbotaoMenu3.x) &&
			   evento.button.y >= imgbotaoMenu3.y &&
			   evento.button.y <= (imgbotaoMenu3.h+imgbotaoMenu3.y)
			){
			  ranking = 1;
			  RankingVisual();
			}


			// ----------------------------------------------------------
			//             Sair do Jogo - BOTÃO SAIR (MENU)
			// ----------------------------------------------------------
			if(
			   evento.button.x >= imgbotaoMenu4.x &&
			   evento.button.x <= (imgbotaoMenu4.w+imgbotaoMenu4.x) &&
			   evento.button.y >= imgbotaoMenu4.y &&
			   evento.button.y <= (imgbotaoMenu4.h+imgbotaoMenu4.y)
			){
			   Sair();
			}
			break;	
			}
		break;
}
return 0;
}


// -----------------------------------------------------------------------------------------------------
// Função para verificar todos os eventos (mouse, teclado) enquanto está dentro da Loja de UTILIDADES.
// -----------------------------------------------------------------------------------------------------
int EventosUtilidades(SDL_Event evento){

	switch (evento.type) {

		// -----------------------------------
		// -- Eventos relacionados ao Mouse --
		// -----------------------------------
		case SDL_MOUSEBUTTONDOWN:
			switch (evento.button.button){
				case SDL_BUTTON_LEFT:
			// ----------------------------------------------------------
			//             Comprar Combustível - Ícone de Combustível
			// ----------------------------------------------------------
			if(
			   evento.button.x >= imgCombustivel.x &&
			   evento.button.x <= (imgCombustivel.w+imgCombustivel.x) &&
			   evento.button.y >= imgCombustivel.y &&
			   evento.button.y <= (imgCombustivel.h+imgCombustivel.y)
			){
			 if(combustivel < COMBUSTIVEL_MAX){
			   if(Comprar(Preco_Combustivel) == 1){ combustivel = COMBUSTIVEL_MAX; }
			 }
			 else if(combustivel == COMBUSTIVEL_MAX){
				sprintf(notificacao,"Você está com o tanque completo!");
				escreverTexto(3,imgCombustivel.x+30,imgCombustivel.y+160,notificacao,255,0,0,16);
				SDL_Flip(janela_Utilidades);
				SDL_Delay(1000);
			 }
			}
			// ----------------------------------------------------------
			//                 Comprar Vida - Ícone de Vida
			// ----------------------------------------------------------
			if(
			   evento.button.x >= imgVidas_Utilidade.x &&
			   evento.button.x <= (imgVidas_Utilidade.w+imgVidas_Utilidade.x) &&
			   evento.button.y >= imgVidas_Utilidade.y &&
			   evento.button.y <= (imgVidas_Utilidade.h+imgVidas_Utilidade.y)
			){
			 if(vida < 3){
			   if(Comprar(Preco_Vida) == 1){ vida += 1; }
			 }
			 else if(vida == 3){
				sprintf(notificacao,"Você está com suas vidas completas!");
				escreverTexto(3,imgCombustivel.x+30,imgCombustivel.y+160,notificacao,255,0,0,16);
				SDL_Flip(janela_Utilidades);
				SDL_Delay(1000);
			 }
			}
			// ----------------------------------------------------------
			//             Sair do Jogo - BOTÃO SAIR (MENU)
			// ----------------------------------------------------------
			if(
			   evento.button.x >= imgbotaoMenu4.x &&
			   evento.button.x <= (imgbotaoMenu4.w+imgbotaoMenu4.x) &&
			   evento.button.y >= imgbotaoMenu4.y &&
			   evento.button.y <= (imgbotaoMenu4.h+imgbotaoMenu4.y)
			){
			   utilidades = 0;
			}
			break;	
			}
		break;
}
return 0;
}


// -----------------------------------------------------------------------------------------------------
// Função para verificar todos os eventos (mouse, teclado) enquanto está dentro da Loja de HABILIDADES.
// -----------------------------------------------------------------------------------------------------
int EventosHabilidades(SDL_Event evento){

	switch (evento.type) {

		// -----------------------------------
		// -- Eventos relacionados ao Mouse --
		// -----------------------------------
		case SDL_MOUSEBUTTONDOWN:
			switch (evento.button.button){
				case SDL_BUTTON_LEFT:
			// ----------------------------------------------------------
			//             Sair do Jogo - BOTÃO SAIR (MENU)
			// ----------------------------------------------------------
			if(
			   evento.button.x >= imgbotaoMenu4.x &&
			   evento.button.x <= (imgbotaoMenu4.w+imgbotaoMenu4.x) &&
			   evento.button.y >= imgbotaoMenu4.y &&
			   evento.button.y <= (imgbotaoMenu4.h+imgbotaoMenu4.y)
			){
			   habilidades = 0;
			}
			break;	
			}
		break;
}
return 0;
}


// -----------------------------------------------------------------------------------------------------
// Função para verificar todos os eventos (mouse, teclado) enquanto está dentro da Loja de HABILIDADES.
// -----------------------------------------------------------------------------------------------------
int EventosRanking(SDL_Event evento){

	switch (evento.type) {

		// -----------------------------------
		// -- Eventos relacionados ao Mouse --
		// -----------------------------------
		case SDL_MOUSEBUTTONDOWN:
			switch (evento.button.button){
				case SDL_BUTTON_LEFT:
			// ----------------------------------------------------------
			//             Sair do Jogo - BOTÃO SAIR (MENU)
			// ----------------------------------------------------------
			if(
			   evento.button.x >= imgbotaoMenu4.x &&
			   evento.button.x <= (imgbotaoMenu4.w+imgbotaoMenu4.x) &&
			   evento.button.y >= imgbotaoMenu4.y &&
			   evento.button.y <= (imgbotaoMenu4.h+imgbotaoMenu4.y)
			){
			   ranking = 0;
			   if(jogando == 1){ jogando = 0; }
			}
			break;	
			}
		break;
}
return 0;
}


// -----------------------------------------------------------------------------------------------------
// Função para verificar todos os eventos (mouse, teclado) enquanto está em MODO DE ESDPERA.
// -----------------------------------------------------------------------------------------------------
int EventosPause(SDL_Event evento){

	switch (evento.type) {

		// -----------------------------------
		// -- Eventos relacionados ao Mouse --
		// -----------------------------------
		case SDL_MOUSEBUTTONDOWN:
			switch (evento.button.button){
				case SDL_BUTTON_LEFT:
			// ----------------------------------------------------------
			//             Sair do Jogo - BOTÃO SAIR (MENU)
			// ----------------------------------------------------------
			if(
			   evento.button.x >= imgbotaoMenu4.x &&
			   evento.button.x <= (imgbotaoMenu4.w+imgbotaoMenu4.x) &&
			   evento.button.y >= imgbotaoMenu4.y &&
			   evento.button.y <= (imgbotaoMenu4.h+imgbotaoMenu4.y)
			){
			   pause = 0;
			}
			break;	
			}
		break;
}
return 0;
}


// -----------------------------------------------------------------------------------------------------
// Função para verificar condições no Teclado.
// -----------------------------------------------------------------------------------------------------
void CondicaoTeclado(){
	if(jogando == 1 && (utilidades != 1 || habilidades != 1)){ Sair(); }
	else if(menuAberto == 1 && (utilidades != 1 || habilidades != 1)){ Sair(); }
	else if(habilidades == 1){ habilidades = 0; }
	else if(utilidades == 1){ utilidades = 0; }
	else if(pause == 1){ pause = 0; }
}

// -----------------------------------------------------------------------------------------------------
// Função para Sair do Jogo/Menu.
// -----------------------------------------------------------------------------------------------------
void Sair(){
	menuAberto = 0;
	jogando = 0;
}
