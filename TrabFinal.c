/* **************************************************************** *
 * Síntese                                                          *
 * Objetivo: Desenvolver um Role-Playing Game (RPG)                 *
 * Data: 18/11/2019                                                 *
 * Autores: Vitor Gledison Oliveira de Souza                        *
 *          Gabriel Souza Araujo                                    *
 * **************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <windows.h>
#include <time.h>
#include <unistd.h>
#include <ctype.h>
#include ".\libraries\interface.h"
#include ".\libraries\defaults.h"
#include ".\libraries\classes.h"
#include ".\libraries\monstros.h"
#include ".\libraries\comerciantes.h"
#include ".\libraries\itens.h"

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_ESC 27
#define KEY_ENTER 13

#define M_PRINCIPAL 1
#define M_JOGADOR 2
#define M_ADMIN 3
#define M_MONSTROS 4
#define M_ITENS 5
#define M_COMERCIANTES 6
#define M_CLASSES 7

#define BACKUP 'B'
#define RESTORE 'R'

int mostraMenuPrincipal();
int mostraMenuAdmin();
int mostraMenuJogador();
int validarLogin(char []);
int mostraClasses();
void criarPersonagem(char []);
int mostraMenu(char []);
void consultaNomePersonagem(char [], char []);
void listarJogadores();
int pegaInformacao (personagem *, item *, char []);
void jogar(personagem *, item *, char[]);
void mostraVida_e_Dano(personagem, monstro, int, int);
void escolheInimigo (monstro *, int, int *, int *);
int mostraCombate(personagem, item, classe);
int escolheOpcaoLuta();

int main() {
	
	// Inicializar em tela cheia
	keybd_event(VK_MENU,0x36,0,0);
	keybd_event(VK_RETURN,0x1C,0,0);
	keybd_event(VK_RETURN,0x1C,KEYEVENTF_KEYUP,0);
	keybd_event(VK_MENU,0x38,KEYEVENTF_KEYUP,0);

	setlocale(LC_ALL,"");
	resolucao_da_tela();
	showcursor(FALSE);
	srand(time(NULL));

	int opcao, finalizarJogo = 0, menus = 1, key;
	char nick_login[21], nPersonagem[21], resposta;
	
	personagem iPersonagem;
	item iEquipamento;

	criaArquivosPadrao();

	while(!finalizarJogo) {
		switch(menus) {
// ******************************  Menu Principal ***************************************
			case M_PRINCIPAL:
				fflush(stdin);
				opcao = mostraMenuPrincipal();
				
				if (opcao == KEY_ESC)
					finalizarJogo = 1;
					
				system("cls");
				
				switch (opcao) {
					case 1:
						mostraTitulo();
						switch(validarLogin(nick_login)) { //Login de Administrador -> "admin"
							case 0:
								menus = M_ADMIN;
								break;
							case 1:
								showcursor(TRUE);
								gotoxy(22,62);
								printf("Essa conta não existe!");
								gotoxy(23,68);
								printf("Criar uma?");
								gotoxy(25,72);
								printf("Sim");
								gotoxy(26,72);
								printf("Não");
								
								int pos = 25;
								
								showcursor(FALSE);
								
								do {
									
									gotoxy(pos,70);
									printf(">>");
							
									key = getch();
							
									if(key == KEY_DOWN) {
										pos++;
										gotoxy(pos-1,70);
										printf("  ");
									} else if(key == KEY_UP) {
										pos--;
										gotoxy(pos+1,70);
										printf("  ");
									}
							
								} while(key != KEY_ENTER && key != KEY_ESC);
								
								if(pos == 25 && key == KEY_ENTER)
									resposta = 'S';

								if(resposta == 'S') {
									criarPersonagem(nick_login);
									menus = M_JOGADOR;
								}
								break;
							case 2:
								menus = M_JOGADOR;
								break;
						}
						break;

					case 2:
						mostraTitulo();
						switch(validarLogin(nick_login)) {
							case 0:
								gotoxy(22,62);
								printf("Esse login não pode");
								gotoxy(23,68);
								printf("ser usado!");
								Sleep(2000);
								fflush(stdin);
								break;
							case 1:
								criarPersonagem(nick_login);
								menus = M_JOGADOR;
								break;
							case 2:
								gotoxy(22,62);
								printf("Essa conta já existe!\n");
								Sleep(2000);
								fflush(stdin);
								break;
						}
						break;

					case 3:
						mostraCreditos();
						fflush(stdin);
						break;

					case 4:
						finalizarJogo = 1;
						
				}
				break;

// ******************************   Menu Jogador  ***************************************
			case M_JOGADOR:
				consultaNomePersonagem(nPersonagem, nick_login);
				opcao = mostraMenuJogador(nPersonagem);
				if (opcao == KEY_ESC)
					opcao = 7;
				switch(opcao) {
					case 1:
						if(pegaInformacao (&iPersonagem, &iEquipamento, nick_login)) {
							gotoxy(19, 24);
							printf("Não foi possível abrir um dos arquivos do personagem!");
							Sleep(2000);
						} else {
							jogar(&iPersonagem, &iEquipamento, nick_login);
						}
						break;
					case 2:
						criarPersonagem(nick_login);
						consultaNomePersonagem(nPersonagem, nick_login);
						if(pegaInformacao (&iPersonagem, &iEquipamento, nick_login)) {
							gotoxy(18, 73);
							printf("Não foi possível abrir um dos arquivos do personagem!");
							Sleep(2000);
						} else {
							jogar(&iPersonagem, &iEquipamento, nick_login);
						}
						break;
					case 3:
						if (pegaInformacao (&iPersonagem, &iEquipamento, nick_login) == 0){
						}
						system("cls");
						setlocale(LC_ALL,"");
						mostraTitulo();
						mostraLore();
						break;
					case 4:
						//Backup
						break;
					
					case 5:
						//Restauração
						break;
					case 6:
						menus = M_PRINCIPAL;
						
				}
				break;

// ****************************  Menu Administrador *************************************
			case M_ADMIN:
				fflush(stdin);
				opcao = mostraMenuAdmin();
				if (opcao == KEY_ESC)
					opcao = 6;
				switch(opcao) {
					case 1:
						
						listarJogadores();
						break;
					case 2:
						menus = M_CLASSES;
						break;
					case 3:
						menus = M_MONSTROS;
						break;
					case 4:
						menus = M_ITENS;
						break;
					case 5:
						menus = M_COMERCIANTES;
						break;
					case 6:
						menus = M_PRINCIPAL;
				}
				break;

// ****************************  Menu de Classes *************************************
			case M_CLASSES:
				fflush(stdin);
				opcao = mostraMenu("CLASSES");
				if (opcao == KEY_ESC)
					opcao = 8;
				switch(opcao) {
					case 1:
						incluirClasse();
						break;
					case 2:
						listarClasses();
						break;
					case 3:
						consultarClasse();
						break;
					case 4:
						alterarClasse();
						break;
					case 5:
						excluirClasse();
						break;
					case 6:
						bkpRst(BACKUP, ".\\database\\classes.info", ".\\database\\classes.bkp");
						break;
					case 7:
						bkpRst(RESTORE, ".\\database\\classes.bkp", ".\\database\\classes.info");
						break;
					case 8:
						menus = M_ADMIN;
				}
				break;

// ****************************  Menu de Monstros *************************************
			case M_MONSTROS:
				fflush(stdin);
				opcao = mostraMenu("MONSTROS");
				if (opcao == KEY_ESC)
					opcao = 8;
				switch(opcao) {
					case 1:
						incluirMonstro();
						break;
					case 2:
						listarMonstros();
						break;
					case 3:
						consultarMonstro();
						break;
					case 4:
						alterarMonstro();
						break;
					case 5:
						excluirMonstro();
						break;
					case 6:
						bkpRst(BACKUP, ".\\database\\monstros.info", ".\\database\\monstros.bkp");
						break;
					case 7:
						bkpRst(RESTORE, ".\\database\\monstros.bkp", ".\\database\\monstros.info");
						break;
					case 8:
						menus = M_ADMIN;
				}
				break;

// ****************************  Menu de Itens *************************************
			case M_ITENS:
				fflush(stdin);
				opcao = mostraMenu("ITENS");
				if (opcao == KEY_ESC)
					opcao = 8;
				switch(opcao) {
					case 1:
						incluirItem();
						break;
					case 2:
						listarItems();
						break;
					case 3:
						consultarItem();
						break;
					case 4:
						alterarItem();
						break;
					case 5:
						excluirItem();
						break;
					case 6:
						bkpRst(BACKUP, ".\\database\\itens.info", ".\\database\\itens.bkp");
						break;
					case 7:
						bkpRst(RESTORE, ".\\database\\itens.bkp", ".\\database\\itens.info");
						break;
					case 8:
						menus = M_ADMIN;
				}
				break;

// ****************************  Menu de Comerciantes *************************************
			case M_COMERCIANTES:
				fflush(stdin);
				opcao = mostraMenu("COMERCIANTES");
				if (opcao == KEY_ESC)
					opcao = 8;
				switch(opcao) {
					case 1:
						incluirComerciante();
						break;
					case 2:
						listarComerciantes();
						break;
					case 3:
						consultarComerciante();
						break;
					case 4:
						alterarComerciante();
						break;
					case 5:
						excluirMonstro();
						break;
					case 6:
						bkpRst(BACKUP, ".\\database\\comerciantes.info", ".\\database\\comerciantes.bkp");
						break;
					case 7:
						bkpRst(RESTORE, ".\\database\\comerciantes.bkp", ".\\database\\comerciantes.info");
						break;
					case 8:
						menus = M_ADMIN;
				}
		}
	}
	return 0;
}

int mostraMenuPrincipal() {
	int pos = 24, key, y = 72;

	system("cls");
	mostraTitulo();
	mostraPergaminho(1);
	
	do {
		gotoxy(20,y);
		printf("MENU PRINCIPAL");
		gotoxy(24,y);
		printf("Login");
		gotoxy(25,y);
		printf("Nova Conta");
		gotoxy(26,y);
		printf("Créditos\n");
		gotoxy(27,y);
		printf("Sair\n");

		gotoxy(pos,y-2);
		printf(">>");

		key = getch();

		if(key == KEY_DOWN) {
			pos++;
			gotoxy(pos-1,y-2);
			printf("  ");
		} else if(key == KEY_UP) {
			pos--;
			gotoxy(pos+1,y-2);
			printf("  ");
		}
		if(pos < 24)
			pos = 27;
		else if (pos > 27)
			pos = 24;

	} while(key != KEY_ENTER && key != KEY_ESC);

	if (key == KEY_ESC)
		pos = KEY_ESC + 23;

	return pos - 23;
}

int validarLogin(char nick_login[]) {
FILE *arq;
	char buffer[21];
	int status, condicao;
	
	mostraPergaminho(2);
	showcursor(TRUE);
	gotoxy(15,71);
	printf("Login");
	gotoxy(20,63);
	fflush(stdin);
	gets(nick_login);
	
	while(strlen(nick_login) > 20) {
		system("cls");
		mostraTitulo();
		mostraPergaminho(2);
		gotoxy(15,71);
		printf("Login");
		gotoxy(34,48);
		textcolor(12);
		printf("Tamanho máximo para o nome é de 20 caracteres, digite novamente...\n");
		textcolor(15);
		gotoxy(20,63);
		fflush(stdin);
		gets(nick_login);
	}
	
	showcursor(FALSE);

	if(strcmp(nick_login, "admin") == 0)
		status = 0;
	else {
		arq = fopen(".\\database\\logins.info", "rb");
		if(arq == NULL)
			status = 1;
		else {
			do {
				condicao = fread(buffer, sizeof(char), 21, arq);
			} while(condicao != 0 && strcmp(buffer, nick_login) != 0);
			if(strcmp(buffer, nick_login) == 0)
				status = 2;
			else
				status = 1;
		}
		fclose(arq);
	}
	return status;
}

void criarPersonagem(char nick_login[]) {
	FILE *pPersonagem = NULL, *pClasse = NULL, *pItensPersonagem = NULL, *pLogin; // p = ponteiro
	int login = 0, status;
	char buf_path[100];
	personagem iPersonagem; // i = informação
	classe iClasse; // i = informação

	pLogin = fopen(".\\database\\logins.info", "ab");
	fwrite(nick_login, sizeof(char), 21, pLogin);
	fclose(pLogin);

	sprintf(buf_path, "mkdir .\\saves\\save_%s", nick_login);
	system(buf_path);

	system("cls");
	mostraTitulo();
	
	mostraPergaminho(2);
	showcursor(TRUE);
	gotoxy(15,71);
	printf("Nickname");
	gotoxy(20,63);
	fflush(stdin);
	gets(iPersonagem.nickname);

	while(strlen(iPersonagem.nickname) > 20) {
		system("cls");
		mostraTitulo();
		mostraPergaminho(2);
		gotoxy(15,71);
		printf("Nickname");
		gotoxy(34,48);
		textcolor(12);
		printf("Tamanho máximo para o nome é de 20 caracteres, digite novamente...\n");
		textcolor(15);
		gotoxy(20,63);
		fflush(stdin);
		gets(iPersonagem.nickname);
	}
	showcursor(FALSE);

	// Adquire a classe do personagem

	iPersonagem.codClasse = mostraClasses();

	// Seleciona as informações da classe do personagem

	pClasse = fopen(".\\database\\classes.info", "rb");
	do {
		fread(&iClasse, sizeof(classe), 1, pClasse);
	} while(iClasse.codClasse != iPersonagem.codClasse);
	
	iPersonagem.vida = iClasse.vidaBase;
	iPersonagem.dano = iClasse.danoBase;
	iPersonagem.moeda = 0;
	iPersonagem.fase = 1;
	iPersonagem.danoH1 = iClasse.danoH1;
	iPersonagem.danoH2 = iClasse.danoH2;
	iPersonagem.danoH3 = iClasse.danoH3;
	fclose(pClasse);

	//Cria o arquivos de com as informações do personagem

	sprintf(buf_path, ".\\saves\\save_%s\\personagem.info", nick_login);
	pPersonagem = fopen(buf_path, "wb");
	fwrite(&iPersonagem, sizeof(personagem), 1, pPersonagem);
	fclose(pPersonagem);

	//Cria o arquivos de itens do personagem

	sprintf(buf_path, ".\\saves\\save_%s\\itensPersonagem.info", nick_login);
	pItensPersonagem = fopen(buf_path, "wb");
	fclose(pItensPersonagem);

	//Mensagem de sucesso na criação do personagem
	
	setlocale(LC_ALL,"");

	system("cls");
	mostraTitulo();
	gotoxy(20,0);
	mostraPergaminho(3);
	gotoxy(13, 40);
	printf("O personagem \"%s\" foi criado com sucesso!", iPersonagem.nickname);
	gotoxy(15, 40);
	textcolor(3);
	printf("Classe: %s", iClasse.nome);
	textcolor(4);
	gotoxy(16, 40);
	printf("Vida: %d", iPersonagem.vida);
	textcolor(8);
	gotoxy(17, 40);
	printf("Ataque básico: %d", iPersonagem.dano);
	textcolor(10);
	gotoxy(18, 73);
	printf("Habilidades");
	textcolor(7);
	gotoxy(19, 40);
	printf("* %s", iClasse.nomeH1);
	gotoxy(20, 40);
	printf("* %s", iClasse.nomeH2);
	gotoxy(21, 40);
	printf("* %s", iClasse.nomeH3);
	
	gotoxy(30, 53);
	system("pause");

	//==============================================================
}

int mostraClasses () {
	int pos = 1, key;
	do {
		system("cls");
		mostraTitulo();

		gotoxy(12,73);
		printf("Classe\n");

		switch (pos) {
			case 1:
				textcolor(1);
				gotoxy(13,74);
				printf("Mago\n");
				
				gotoxy(21,0);
				mostraImagemClasses(1);
				textcolor(15);		
				break;
				
			case 2:
				textcolor(14);
				gotoxy(13,72);
				printf("Guerreiro\n");
				
				gotoxy(15,0);
				mostraImagemClasses(2);
				
				textcolor(15);
				break;
				
			case 3:
				textcolor(5);
				gotoxy(13,72);
				printf("Arqueiro\n");
				
				gotoxy(15,0);
				mostraImagemClasses(3);
				
				textcolor(15);
					
		}
		
		if (pos < 3) {
			gotoxy(24,133);
			printf("|\\");
			gotoxy(25,133);
			printf("| \\");
			gotoxy(26,126);
			printf("_______|  \\");
			gotoxy(27,125);
			printf("|           \\");
			gotoxy(28,125);
			printf("|_______    /");
			gotoxy(29,133);
			printf("|  /");
			gotoxy(30,133);
			printf("| /");
			gotoxy(31,133);
			printf("|/");
		
		} 
		
			if (pos > 1) {
			gotoxy(24,20);
			printf("/|");
			gotoxy(25,19);
			printf("/ |");
			gotoxy(26,18);
			printf("/  |_______");
			gotoxy(27,17);
			printf("/           |");
			gotoxy(28,17);
			printf("\\    _______|");
			gotoxy(29,18);
			printf("\\  |");
			gotoxy(30,19);
			printf("\\ |");
			gotoxy(31,20);
			printf("\\|");
		}

		key = getch();

		if(key == KEY_RIGHT)
			pos++;
		else if(key == KEY_LEFT)
			pos--;
		if(pos < 1)
			pos = 1;
		else if (pos > 3)
			pos = 3;
	}	while(key != KEY_ENTER);
	

	return pos;
}

int mostraMenuAdmin() {
	int pos = 24, key, y = 72;

	system("cls");
	mostraTitulo();
	
	mostraPergaminho(1);

	gotoxy(20,y);
	printf("ADMINISTRADOR");
	gotoxy(24,y);
	printf("Listar usuários");
	gotoxy(25,y);
	printf("Classes");
	gotoxy(26,y);
	printf("Monstros");
	gotoxy(27,y);
	printf("Itens");
	gotoxy(28,y);
	printf("Comerciantes");
	gotoxy(29,y);
	printf("Sair\n");

	do {
		gotoxy(pos,y-2);
		printf(">>");

		key = getch();

		if(key == KEY_DOWN) {
			pos++;
			gotoxy(pos-1,y-2);
			printf("  ");
		} else if(key == KEY_UP) {
			pos--;
			gotoxy(pos+1,y-2);
			printf("  ");
		}
		if(pos < 24)
			pos = 29;
		else if (pos > 29)
			pos = 24;

	} while(key != KEY_ENTER && key != KEY_ESC);
	
	if (key == KEY_ESC)
		pos = KEY_ESC + 23;

	return pos - 23;
}

int mostraMenuJogador(char nPersonagem[]) {
	int pos = 24, key, y = 72;

	system("cls");
	mostraTitulo();
	mostraPergaminho(1);

	gotoxy(20,y);
	printf("JOGADOR: %s", nPersonagem);
	gotoxy(24,y);
	printf("Contiuar");
	gotoxy(25,y);
	printf("Novo Jogo");
	gotoxy(26,y);
	printf("Informações do Personagem");
	gotoxy(27,y);
	printf("Backup");
	gotoxy(28,y);
	printf("Restauração");
	gotoxy(29,y);
	printf("Sair\n");

	do {
		gotoxy(pos,y-2);
		printf(">>");

		key = getch();

		if(key == KEY_DOWN) {
			pos++;
			gotoxy(pos-1,y-2);
			printf("  ");
		} else if(key == KEY_UP) {
			pos--;
			gotoxy(pos+1,y-2);
			printf("  ");
		}
		if(pos < 24)
			pos = 29;
		else if (pos > 29)
			pos = 24;

	} while(key != KEY_ENTER && key != KEY_ESC);
	
	if (key == KEY_ESC)
		pos = KEY_ESC + 23;

	return pos - 23;
}

int mostraMenu(char nomeMenu[]) {
	int pos = 24, key, y = 72;
	
	mostraPergaminho(1);

	gotoxy(20,y);
	printf("MENU DE %s", nomeMenu);
	gotoxy(24,y);
	printf("Inclusão");
	gotoxy(25,y);
	printf("Listagem");
	gotoxy(26,y);
	printf("Consulta\n");
	gotoxy(27,y);
	printf("Alteração");
	gotoxy(28,y);
	printf("Exclusão\n");
	gotoxy(29,y);
	printf("Backup\n");
	gotoxy(30,y);
	printf("Restauração\n");
	gotoxy(31,y);
	printf("Sair\n");
	
	do {
		gotoxy(pos,y-2);
		printf(">>");

		key = getch();

		if(key == KEY_DOWN) {
			pos++;
			gotoxy(pos-1,y-2);
			printf("  ");
		} else if(key == KEY_UP) {
			pos--;
			gotoxy(pos+1,y-2);
			printf("  ");
		}
		if(pos < 24)
			pos = 31;
		else if (pos > 31)
			pos = 24;

	} while(key != KEY_ENTER && key != KEY_ESC);
	
	if (key == KEY_ESC)
		pos = KEY_ESC + 23;

	return pos - 23;
}

void consultaNomePersonagem(char nPersonagem[], char nLogin[]) {
	FILE *pArquivo;
	char bufferPath[100];
	personagem iPersonagem;

	sprintf(bufferPath, ".\\saves\\save_%s\\personagem.info", nLogin);
	pArquivo = fopen(bufferPath, "rb");
	fread(&iPersonagem, sizeof(personagem), 1, pArquivo);
	strcpy(nPersonagem, iPersonagem.nickname);
	fclose(pArquivo);
}

int pegaInformacao (personagem *iPersonagem, item *iEquipamento, char nLogin[]) {
	FILE *pPersonagem = NULL, *pEquipamento = NULL;
	char procura[30], buffer[21];
	int status =0;

	sprintf(buffer,".\\saves\\save_%s\\personagem.info", nLogin);
	pPersonagem = fopen(buffer, "rb");
	sprintf(buffer,".\\saves\\save_%s\\itensPersonagem.info", nLogin);
	pEquipamento = fopen(buffer, "rb");

	if(pPersonagem == NULL || pEquipamento == NULL)
		status =1;
	else {
		fread(iPersonagem, sizeof(personagem), 1, pPersonagem);
		fread(iEquipamento, sizeof(item), 1, pEquipamento);
	}
	fclose(pPersonagem);
	fclose(pEquipamento);
	return status;
}

void jogar(personagem *iPersonagem, item *iEquipamento, char nick_login[]) {
	int escolha, posXMonstro, posYMonstro, contaMonstros = 1, terminou = 0;
	int i, j, status, dado, acheiItem, codMAX;
	char buf_path[200];
	FILE* pClasse, *pItem, *pPersonagem, *pNumItens;
	monstro iMonstro;
	classe persClasse;
	item iItem;
	personagem procuraPersonagem;

	pItem = fopen(".\\database\\itens.info", "rb");

	carregamento();
	
	// Faz grama
	setlocale(LC_ALL,"C");
	textbackground(2);
	for (i = 32; i < 40; i++) {
		for (j = 1; j < 167; j++) {
			gotoxy(i,j);
			printf("%c", 176);
			
		}
	}
	textbackground(0);
	
	setlocale(LC_ALL,"");
	
	gotoxy(0,0);
	mostraPersonagem();
	mostraMonstro();

	pClasse = fopen(".\\database\\classes.info", "rb");
	while((fread(&persClasse, sizeof(classe), 1, pClasse) == 1) && (persClasse.codClasse != iPersonagem->codClasse));
	fclose(pClasse);

	gotoxy(2,4);
	printf("%s", iPersonagem->nickname);
	gotoxy(3,4);
	printf("%s", persClasse.nome);
	do {
		escolheInimigo(&iMonstro, iPersonagem->fase, &posXMonstro, &posYMonstro);
		do {
			mostraVida_e_Dano(*iPersonagem, iMonstro, posXMonstro, posYMonstro);
			escolha = mostraCombate(*iPersonagem, *iEquipamento, persClasse);

			if(escolha == KEY_ESC) {
				system("cls");
				sprintf(buf_path, ".\\saves\\save_%s\\personagem.info", nick_login);
				pPersonagem = fopen(buf_path, "wb");
                fwrite(iPersonagem, sizeof(personagem), 1, pPersonagem);
                fclose(pPersonagem);
                terminou = 1;
			}else{
                switch(escolha) {
                    case 1:
                        iMonstro.vida = iMonstro.vida - iPersonagem->dano;
                        break;
                    case 2:
                        iMonstro.vida = iMonstro.vida - iPersonagem->danoH1;
                        break;
                    case 3:
                        iMonstro.vida = iMonstro.vida - iPersonagem->danoH2;
                        break;
                    case 4:
                        iMonstro.vida = iMonstro.vida - iPersonagem->danoH3;
                        break;
                    case 5:
                        iPersonagem->vida = iPersonagem->vida + 15;
                }
                if(iMonstro.vida > 0) {
                    mostraVida_e_Dano(*iPersonagem, iMonstro, posXMonstro, posYMonstro);
                    gotoxy(posXMonstro-2, posYMonstro-15);
                    printf("O %s está prestes a te atacar!", iMonstro.nome);
                    Sleep(1000);
                    gotoxy(posXMonstro-2, posYMonstro-15);
                    printf("%40s", " ");
                    iPersonagem->vida -= iMonstro.dano;
                } else {
                    iMonstro.vida = 0;
                    mostraVida_e_Dano(*iPersonagem, iMonstro, posXMonstro, posYMonstro);
                    gotoxy(5, 50);
                    printf("Você eliminou o %s!", iMonstro.nome);
                    fseek(pItem, 0, SEEK_SET);
                    while(fread(&iItem, sizeof(item), 1, pItem)){
                        if(iItem.deletado != 1)
                            codMAX = iItem.codItem;
                    }
                    acheiItem =0;
                    fseek(pItem, 0, SEEK_SET);
                    do{
                        dado = (rand()%codMAX)+1;
                        status = fread(&iItem, sizeof(item), 1, pItem);
                        if(acheiItem == 0 && status == 0){
                            fseek(pItem, 0, SEEK_SET);
                            status = fread(&iItem, sizeof(item), 1, pItem);
                        }
                        if(iItem.categoria == iMonstro.categoria && iItem.codItem == dado && iItem.deletado == 0)
                            acheiItem =1;
                    }while(!acheiItem);
                    gotoxy(6, 50);
                    printf("Você recebeu um(a): %s!", iItem.nome);

                    int posBonus = 6;

                    if (iItem.dano > 0) {
                        posBonus++;
                        iPersonagem->dano += iItem.dano;
                        gotoxy(posBonus,50);
                        printf("+ %d de Ataque!", iItem.dano);
                    }
                    if (iItem.vida > 0) {
                        posBonus++;
                        iPersonagem->vida += iItem.vida;
                        gotoxy(posBonus,50);
                        printf("+ %d de Vida!", iItem.vida);
                    }
                    if (iItem.moeda > 0) {
                        posBonus++;
                        iPersonagem->moeda += iItem.moeda;
                        gotoxy(posBonus,50);
                        printf("+ %d Moedas!", iItem.moeda);
                    }

                    if (contaMonstros == 10)
                        iPersonagem->fase++;

                    Sleep(2000);
                    gotoxy(5, 50);
                    printf("%26s", " ");
                    gotoxy(6, 50);
                    printf("%46s", " ");
                    gotoxy(posXMonstro, posYMonstro+5);
                    printf("     ");
                    gotoxy(posXMonstro+1, posYMonstro+5);
                    printf("     ");
                    gotoxy(13, 69);
                    printf("                ");
                    do {
                        gotoxy(posBonus, 50);
                        printf("                   ");
                        posBonus--;
                    } while(posBonus > 6);
                    contaMonstros++;
                }
			}
		} while(iMonstro.vida > 0 && iPersonagem->vida > 0 && terminou == 0);
	} while(iPersonagem->vida > 0 && terminou == 0);
	fclose(pItem);
	system("cls");
}

int mostraCombate(personagem iPersonagem, item iEquipamento, classe iClasse) {
	int key;

	fazMolduras();

	//Permite acentuação novamente
	setlocale(LC_ALL,"");

	//Habilidades
	gotoxy(41,6);
	printf("Habilidades");
	gotoxy(42,6);
	printf("Ataque Básico: %d", iPersonagem.dano);
	gotoxy(43,6);
	printf("%s: %d", iClasse.nomeH1, iClasse.danoH1);
	gotoxy(44,6);
	printf("%s: %d", iClasse.nomeH2, iClasse.danoH2);
	gotoxy(45,6);
	printf("%s: %d\n", iClasse.nomeH3, iClasse.danoH3);

	//Poção
	gotoxy(41,70);
	printf("Poções", iEquipamento.nome);
	gotoxy(42,70);
	printf("Poção de Vida: +15 de Vida");

	key = escolheOpcaoLuta();

	return key;
}

void escolheInimigo (monstro *iMonstro, int fase, int *posXMonstro, int *posYMonstro) {
	int dadoMonstro, dadoItem, i, leu, monstroCerto, itemCerto;
	char categoria, limite;
	item iItem;

	srand(time(NULL));

	*posXMonstro = 9;  //Linha de onde será exibido a vida
	*posYMonstro = 120; //Coluna de onde será exibido a vida

	//Define a dificuldade
	switch (fase) {
		case 1:
			categoria = 'F';
			break;

		case 2:
			categoria = 'E';
			break;

		case 3:
			categoria = 'D';
			break;

		case 4:
			categoria = 'C';
			break;

		case 5:
			categoria = 'B';
			break;

		case 6:
			categoria = 'A';
			break;

		case 7:
			categoria = 'S';
	}

	if (categoria != 'S')
		limite = 'F';

	else
		limite = 'S';

	FILE *pMonstro = fopen(".\\database\\monstros.info", "rb"); // p = ponteiro
	FILE *pItem = fopen(".\\database\\itens.info", "rb");

// Sorteia o inimigo

	do {
		dadoMonstro = rand() % 5 + 1;

		for (i=1; i<= dadoMonstro; i++)
			leu = fread(iMonstro, sizeof(monstro), 1, pMonstro);

		if (!leu) {
			fclose(pMonstro);
			pMonstro = fopen(".\\database\\monstros.info", "rb");
			dadoMonstro = rand() % 5 + 1;

			for (i=1; i<= dadoMonstro; i++)
				fread(iMonstro, sizeof(monstro), 1, pMonstro);
		}

		if (iMonstro->categoria < categoria || iMonstro->categoria > limite || iMonstro->codMonstro != dadoMonstro)
			monstroCerto = 0;

		else
			monstroCerto = 1;

	} while(!monstroCerto || iMonstro->deletado);

	gotoxy(8, 120);
	printf("%s", iMonstro->nome);
	
	fclose(pMonstro);
	
// Sorteia o Item
	do {

		dadoItem = rand() % 32 + 1;

		for (i=1; i<= dadoItem; i++)
			leu = fread(&iItem, sizeof(item), 1, pItem);

		if (!leu || iItem.categoria != categoria || iItem.codItem != dadoItem) {
			fclose(pItem);
			pItem = fopen(".\\database\\itens.info", "rb");
			
			itemCerto = 0;
		} else
			itemCerto = 1;

	} while (!itemCerto || iItem.deletado);

	iMonstro->codItem = iItem.codItem;
	
	fclose(pItem);
}

int escolheOpcaoLuta() {
	int posX = 42, posY = 3, opcao, key;

	do {
		gotoxy(posX,posY);
		printf(">>");
		key = getch();
		if(key == KEY_DOWN) {
			gotoxy(posX,posY);
			printf("  ");
			posX++;
			if(posY == 3) {
				if(posX > 45)
					posX = 42;
			} else {
				if(posX != 42)
					posX = 42;
			}
		} else if(key == KEY_UP) {
			gotoxy(posX,posY);
			printf("  ");
			posX--;
			if(posY == 3) {
				if(posX < 42)
					posX = 45;
			} else {
				if(posX != 42)
					posX = 42;
			}
		} else if(key == KEY_RIGHT) {
			gotoxy(posX,posY);
			printf("  ");
			posX = 42;
			posY = 67;
		} else if(key == KEY_LEFT) {
			gotoxy(posX,posY);
			printf("  ");
			posX = 42;
			posY = 3;
		}
	} while(key != KEY_ENTER && key!= KEY_ESC);

	gotoxy(42, 67);
	printf("  ");
	gotoxy(42, 3);
	printf("  ");
	gotoxy(43, 3);
	printf("  ");
	gotoxy(44, 3);
	printf("  ");

	if(key != KEY_ESC) {
		opcao = posX + posY;
		switch (opcao) {
			case 45:
				opcao = 1;
				break;
			case 46:
				opcao = 2;
				break;
			case 47:
				opcao = 3;
				break;
			case 48:
				opcao = 4;
				break;
			case 109:
				opcao = 5;
		}
	} else
		opcao = KEY_ESC;
	return opcao;
}

void mostraVida_e_Dano(personagem iPersonagem, monstro iMonstro, int x, int y) {

	//Monstro
	gotoxy(x,y);
	printf("Vida: %02d", iMonstro.vida);
	gotoxy(x+1,y);
	printf("Dano: %02d", iMonstro.dano);

	//Personagem
	gotoxy(4,4);
	printf("Vida: %02d", iPersonagem.vida);
	gotoxy(5,4);
	printf("Dano: %02d", iPersonagem.dano);

}

void listarJogadores(){
    FILE *pLogins = fopen(".\\database\\logins.info", "rb");
    FILE *pPersonagem;
    int counter =0, posLayout = 12;
    int pos = posLayout+2;
    char login[21];
    char buffer[150];
    personagem iPersonagem;

    system("cls");
    mostraTitulo();

    if(pLogins != NULL){
        gotoxy(posLayout, 65);
        printf("LISTA DE USUÁRIOS");
        while(fread(login, sizeof(login), 1, pLogins)){
            counter++;
            sprintf(buffer, ".\\saves\\save_%s\\personagem.info", login);
            pPersonagem = fopen(buffer, "rb");
            fread(&iPersonagem, sizeof(personagem), 1, pPersonagem);
            fclose(pPersonagem);
            gotoxy(pos, 40);
            printf("Usuário: %-21s | Nome do personagem: %s\n", login, iPersonagem.nickname);
            gotoxy(++pos, 40);
            printf("---------------------------------------------------------------------------");
            pos++;
        }
        if(counter == 0){
            gotoxy(posLayout, 65);
            printf("Não existem usuários!");
            gotoxy(posLayout+2, 52);
        }else
            gotoxy(++pos, 52);
    }else{
        gotoxy(posLayout, 51);
        printf("Não foi possível abrir os arquivos!");
        gotoxy(posLayout+2, 52);
    }

    system("pause");
}

