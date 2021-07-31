#include "interface.h"
#include "defaults.h"
#include <ctype.h>
#include "conio.h"

#define KEY_LEFT 75
#define KEY_RIGHT 77

#ifndef ITENS_H
#define ITENS_H

void incluirItem() {
	FILE *pArquivo = fopen(".\\database\\itens.info", "r+b");
	item iItem;
	int codItem = 1;
	
	setlocale(LC_ALL,"");

	system("cls");
	mostraTitulo();

	if(pArquivo == NULL) {
		gotoxy(9, 40);
		printf("Erro ao abrir o arquivo!");
		Sleep(2000);
	} else {
		while(fread(&iItem, sizeof(item), 1, pArquivo)) {
			if(iItem.deletado == 0)
				codItem = iItem.codItem;
		}

		iItem.codItem = codItem+1;
		iItem.deletado = 0;

		gotoxy(9, 40);
		printf("INCLUIR NOVO ITEM", iItem.codItem);
		gotoxy(11, 40);
		printf("Código: %d", iItem.codItem);
		gotoxy(12, 40);
		printf("Nome:");
		gotoxy(13, 40);
		printf("Adição de vida:");
		gotoxy(14, 40);
		printf("Adição de dano:");
		gotoxy(15, 40);
		printf("Adição de moeda:");
		gotoxy(16, 40);
		printf("Categoria:");
		gotoxy(17, 40);
		printf("Probalidade de aquisição (%%):");

		showcursor(TRUE);
		gotoxy(12, 46);
		fflush(stdin);
		gets(iItem.nome);
		gotoxy(13, 56);
		scanf("%d", &iItem.vida);
		gotoxy(14, 56);
		scanf("%d", &iItem.dano);
		gotoxy(15, 57);
		scanf("%d", &iItem.moeda);
		gotoxy(16, 51);
		fflush(stdin);
		scanf("%c", &iItem.categoria);
		iItem.categoria = toupper(iItem.categoria);
		gotoxy(17, 70);
		scanf("%d", &iItem.probItem);
		showcursor(FALSE);

		fwrite(&iItem, sizeof(item), 1, pArquivo);
		fclose(pArquivo);

		gotoxy(19, 40);
		printf("ITEM ADICIONADO!");
		//Sleep(2000);
	}
}

void listarItems() {
	FILE *pArquivo = fopen(".\\database\\itens.info", "rb");
	int pos = 11, contador = 0, key = 0, status, pag = 0, codMAX;
	item iItem;

	setlocale(LC_ALL,"");

	system("cls");
	mostraTitulo();

	if(pArquivo == NULL) {
		gotoxy(9, 40);
		printf("Erro ao abrir o arquivo!");
		Sleep(2000);
	} else {
		gotoxy(9, 45);
		printf(" ITENS ");
		while(fread(&iItem, sizeof(item), 1, pArquivo)){
            if(iItem.deletado == 0)
                codMAX = iItem.codItem;
        }
        fseek(pArquivo, 0, SEEK_SET);
		while(key != KEY_ESC) {
			while (fread(&iItem, sizeof(item), 1, pArquivo) == 1 && contador < 5) {
				if(!iItem.deletado) {
					contador++;
					gotoxy(pos, 2);
					printf(" Código: %6d | Nome: %s", iItem.codItem, iItem.nome);
					gotoxy(++pos, 2);
					printf(" Adição de Vida | Adição de Dano | Adição de Moeda | Categoria | Probabilidade de Aquisição (%%)");
					gotoxy(++pos, 2);
					printf(" %-14d |", iItem.vida);
					printf(" %-14d |", iItem.dano);
					printf(" %-15d |", iItem.moeda);
					printf(" %-9c |", iItem.categoria);
					printf(" %d ", iItem.probItem);
					gotoxy(++pos, 2);
					printf(" -----------------------------------------------------------------------------------------------");
					pos++;

				}
			}
            gotoxy(++pos,35);
            printf("Pressione ESC para sair");
            if(pag == 0 && iItem.codItem != codMAX){
                gotoxy(pos,68);
                printf("->");
            }else if(iItem.codItem == codMAX && pag != 0){
                gotoxy(pos,25);
                printf("<-");
            }else if(pag > 0){
                gotoxy(pos,25);
                printf("<-");
                gotoxy(pos,68);
                printf("->");
            }

			fseek(pArquivo,(sizeof(item) * (-1)), SEEK_CUR);

			fflush(stdin);

			pos = 11;
			status = 0;

            do {
                key = getch();
                if (key == KEY_RIGHT && iItem.codItem != codMAX) {
                    status = 1;
                    pag++;
                    contador = 0;
                } else if(key == KEY_LEFT && pag > 0) {
                    status = 1;
                    contador = 0;
                    pag--;
                    if(pag >= 2)
                        fseek(pArquivo,(sizeof(item) * (pag * 5 + 1)), SEEK_SET);
                    else
                        fseek(pArquivo,(sizeof(item) * (pag * 5)), SEEK_SET);
                } else if (key == KEY_ESC)
                    status = 1;
            } while(status == 0);

			system("cls");
			mostraTitulo();
			gotoxy(9, 45);
			printf(" ITENS ");

		}
	}
	fclose(pArquivo);

}

void consultarItem() {
	FILE *pArquivo = fopen(".\\database\\itens.info", "rb");
	char nomeItem[31];
	int status;
	item iItem;

	system("cls");
	mostraTitulo();

	if(pArquivo == NULL) {
		gotoxy(9, 30);
		printf("Erro ao abrir o arquivo!");
		gotoxy(11, 30);
	} else {
		gotoxy(9, 37);
		printf(" CONSULTAR ITEM ");
		gotoxy(11, 9);
		printf(" Digite o nome do item:");
		gotoxy(13, 2);
		printf(" -----------------------------------------------------------------------------------------------");
		gotoxy(14, 2);
		printf(" Código:        | Nome: ");
		gotoxy(15, 2);
		printf(" Adição de Vida | Adição de Dano | Adição de Moeda | Categoria | Probabilidade de Aquisição (%%)");
		gotoxy(17, 2);
		printf(" -----------------------------------------------------------------------------------------------");
		gotoxy(11, 33);
		showcursor(TRUE);
		gets(nomeItem);
		showcursor(FALSE);
		do {
			status = fread(&iItem, sizeof(item), 1, pArquivo);
		} while(!(strcmp(nomeItem, iItem.nome) == 0 && iItem.deletado == 0) && status == 1 );
		if(strcmp(nomeItem, iItem.nome) == 0 && iItem.deletado == 0) {
			gotoxy(14, 9);
			printf(" %6d ", iItem.codItem);
			gotoxy(14, 24);
			printf(" %s ", iItem.nome);
			gotoxy(16, 2);
			printf(" %-14d |", iItem.vida);
			printf(" %-14d |", iItem.dano);
			printf(" %-15d |", iItem.moeda);
			printf(" %-9c |", iItem.categoria);
			printf(" %d ", iItem.probItem);
		} else {
			gotoxy(16, 26);
			printf("Não foi possivel encontrar o item informado!");
		}
		fclose(pArquivo);
		gotoxy(19, 28);
	}
	system("pause");
}

void excluirItem() {
	FILE *pArquivo = fopen(".\\database\\itens.info", "r+b");
	char nomeItem[31], resposta;
	int status;
	item iItem;

	system("cls");
	mostraTitulo();

	if(pArquivo == NULL) {
		gotoxy(9, 30);
		printf("Erro ao abrir o arquivo!");
		gotoxy(11, 30);
	} else {
		gotoxy(9, 37);
		printf(" EXCLUIR ITEM ");
		gotoxy(11, 9);
		printf(" Digite o nome do item:");
		gotoxy(13, 2);
		printf(" -----------------------------------------------------------------------------------------------");
		gotoxy(14, 2);
		printf(" Código:        | Nome: ");
		gotoxy(15, 2);
		printf(" Adição de Vida | Adição de Dano | Adição de Moeda | Categoria | Probabilidade de Aquisição (%%)");
		gotoxy(17, 2);
		printf(" -----------------------------------------------------------------------------------------------");
		gotoxy(11, 33);
		showcursor(TRUE);
		gets(nomeItem);
		showcursor(FALSE);
		do {
			status = fread(&iItem, sizeof(item), 1, pArquivo);
		} while(!(strcmp(nomeItem, iItem.nome) == 0 && iItem.deletado == 0) && status == 1 );
		if(strcmp(nomeItem, iItem.nome) == 0 && iItem.deletado == 0) {
			gotoxy(14, 9);
			printf(" %6d ", iItem.codItem);
			gotoxy(14, 24);
			printf(" %s ", iItem.nome);
			gotoxy(16, 2);
			printf(" %-14d |", iItem.vida);
			printf(" %-14d |", iItem.dano);
			printf(" %-15d |", iItem.moeda);
			printf(" %-9c |", iItem.categoria);
			printf(" %d ", iItem.probItem);
			gotoxy(19, 35);
			printf("Deseja excluir? (S/N): ");
			showcursor(TRUE);
			resposta = getchar();
			showcursor(FALSE);
			resposta = toupper(resposta);
			if(resposta == 'S') {
				iItem.deletado = 1;
				fseek(pArquivo, -1*(sizeof(item)), SEEK_CUR);
				fwrite(&iItem, sizeof(item), 1, pArquivo);
				gotoxy(20, 38);
				printf("Item excluído!");
			} else {
				gotoxy(20, 35);
				printf("Item não foi excluído!");
			}
			gotoxy(22, 28);
		} else {
			gotoxy(16, 26);
			printf("Não foi possivel encontrar o item informado!");
			gotoxy(19, 28);
		}
		fclose(pArquivo);
	}
	system("pause");
}

void alterarItem() {
	FILE *pArquivo = fopen(".\\database\\itens.info", "r+b");
	char buffer[21], nomeItem[21], resposta;
	int status;
	item iItem;

	system("cls");
	mostraTitulo();

	if(pArquivo == NULL) {
		gotoxy(9, 30);
		printf("Erro ao abrir o arquivo!");
		gotoxy(11, 30);
	} else {
		gotoxy(9, 37);
		printf(" ALTERAR ITEM ");
		gotoxy(11, 9);
		printf(" Digite o nome do item:");
		gotoxy(13, 2);
		printf(" -----------------------------------------------------------------------------------------------");
		gotoxy(14, 2);
		printf(" Código:        | Nome: ");
		gotoxy(15, 2);
		printf(" Adição de Vida | Adição de Dano | Adição de Moeda | Categoria | Probabilidade de Aquisição (%%)");
		gotoxy(17, 2);
		printf(" -----------------------------------------------------------------------------------------------");
		gotoxy(11, 33);
		showcursor(TRUE);
		gets(nomeItem);
		showcursor(FALSE);
		do {
			status = fread(&iItem, sizeof(item), 1, pArquivo);
		} while(!(strcmp(nomeItem, iItem.nome) == 0 && iItem.deletado == 0) && status == 1 );
		if(strcmp(nomeItem, iItem.nome) == 0 && iItem.deletado == 0) {
			gotoxy(14, 9);
			printf(" %6d ", iItem.codItem);
			gotoxy(14, 24);
			printf(" %s ", iItem.nome);
			gotoxy(16, 2);
			printf(" %-14d |", iItem.vida);
			printf(" %-14d |", iItem.dano);
			printf(" %-15d |", iItem.moeda);
			printf(" %-9c |", iItem.categoria);
			printf(" %d ", iItem.probItem);

			gotoxy(19, 38);
			printf("Deseja Alterar? (S/N): ");
			showcursor(TRUE);
			resposta = getchar();
			showcursor(FALSE);
			resposta = toupper(resposta);
			if(resposta == 'S') {
				gotoxy(21, 38);
				printf("NOVAS INFORMAÇÕES");

				gotoxy(22, 38);
				printf("Nome:");
				gotoxy(23, 38);
				printf("Adição de vida: ");
				gotoxy(24, 38);
				printf("Adição de dano: ");
				gotoxy(25, 38);
				printf("Adição de moeda: ");
				gotoxy(26, 38);
				printf("Categoria: ");
				gotoxy(27, 38);
				printf("Probabilidade de Aquisição (%%): ");

				showcursor(TRUE);
				gotoxy(22, 44);
				fflush(stdin);
				gets(iItem.nome);
				gotoxy(23, 54);
				scanf("%d", &iItem.vida);
				gotoxy(24, 54);
				scanf("%d", &iItem.dano);
				gotoxy(25, 55);
				scanf("%d", &iItem.moeda);
				gotoxy(26, 49);
				fflush(stdin);
				scanf("%c", &iItem.categoria);
				iItem.categoria = toupper(iItem.categoria);
				gotoxy(27, 70);
				scanf("%d", &iItem.probItem);
				showcursor(FALSE);

				fseek(pArquivo, -1*(sizeof(item)), SEEK_CUR);
				fwrite(&iItem, sizeof(item), 1, pArquivo);
				gotoxy(29, 38);
				printf("Item alterado!");
				gotoxy(31, 31);
			} else {
				gotoxy(20, 38);
				printf("Item não foi alterado!");
				gotoxy(22, 31);
			}
		} else {
			gotoxy(16, 24);
			printf("Não foi possível encontrar o item informado!");
			gotoxy(19, 28);
		}
		fclose(pArquivo);
	}
	system("pause");
}

#endif // ITENS_H
