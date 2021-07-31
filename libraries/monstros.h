#include "interface.h"
#include "defaults.h"
#include <ctype.h>

#ifndef MONSTROS_H
#define MONSTROS_H

void incluirMonstro(){
    FILE *pArquivo = fopen(".\\database\\monstros.info", "r+b");
    monstro iMonstro;
    int codMonstro =1;

    system("cls");
    mostraTitulo();

    if(pArquivo == NULL){
        gotoxy(18, 73);
        printf("Erro ao abrir o arquivo!");
        Sleep(2000);
    } else{
        while(fread(&iMonstro, sizeof(monstro), 1, pArquivo)){
            if(iMonstro.deletado == 0)
                codMonstro = iMonstro.codMonstro;
        }

        iMonstro.codMonstro = codMonstro+1;
        iMonstro.codItem =0;
        iMonstro.deletado =0;

        gotoxy(13, 63);
        printf("ADICIONAR NOVO MONSTRO", iMonstro.codMonstro);
        gotoxy(16, 40);
        printf("Código: %d", iMonstro.codMonstro);
        gotoxy(17, 40);
        printf("Nome:");
        gotoxy(18, 40);
        printf("Quantidade de vida: ");
        gotoxy(19, 40);
        printf("Quantidade de dano: ");
        gotoxy(20, 40);
        printf("Categoria: ");
        gotoxy(21, 40);
        printf("Taxa de spawn: ");

        showcursor(TRUE);
        gotoxy(17, 46);
        fflush(stdin);
        gets(iMonstro.nome);
        gotoxy(18, 60);
        scanf("%d", &iMonstro.vida);
        gotoxy(19, 60);
        scanf("%d", &iMonstro.dano);
        gotoxy(20, 51);
        fflush(stdin);
        scanf("%c", &iMonstro.categoria);
        iMonstro.categoria = toupper(iMonstro.categoria);
        gotoxy(21, 55);
        scanf("%d", &iMonstro.taxaSpawn);
        showcursor(FALSE);

        fwrite(&iMonstro, sizeof(monstro), 1, pArquivo);
        fclose(pArquivo);

        gotoxy(23, 40);
        printf("MONSTRO ADICIONADO!");
        Sleep(2000);
    }
}

void listarMonstros() {
	FILE *pArquivo = fopen(".\\database\\monstros.info", "rb");
    int pos = 17, contador=0, pag =0, key=0, status, codMAX;
    monstro iMonstro;

    system("cls");
    mostraTitulo();

    if(pArquivo == NULL){
        gotoxy(18, 73);
        printf("Erro ao abrir o arquivo!");
        Sleep(2000);
    } else{
		gotoxy(13, 73);
        printf(" LISTA DE MONSTROS ");
        while(fread(&iMonstro, sizeof(monstro), 1, pArquivo)){
            if(iMonstro.deletado == 0)
                codMAX = iMonstro.codMonstro;
        }
        fseek(pArquivo, 0, SEEK_SET);
		while(key != KEY_ESC) {
            gotoxy(16, 40);
            printf(" Código |         Nome         | Qtd. Vida | Qtd. Dano | Categoria | Taxa de spawn \n");
            while((fread(&iMonstro, sizeof(monstro), 1, pArquivo) == 1) && (contador < 5)){
                if(iMonstro.deletado == 0){
                    gotoxy(pos, 40);
                    contador++;
                    printf(" %6d |", iMonstro.codMonstro);
                    printf(" %-20s |", iMonstro.nome);
                    printf(" %9d |", iMonstro.vida);
                    printf(" %9d |", iMonstro.dano);
                    printf(" %9c |", iMonstro.categoria);
                    printf(" %13d ", iMonstro.taxaSpawn);
                    gotoxy(++pos, 33);
                    printf(" -----------------------------------------------------------------------------------------------");
                    pos++;
                }
            }

            gotoxy(++pos,40);
            printf("Pressione ESC para sair");
            if(pag == 0 && iMonstro.codMonstro != codMAX){
                gotoxy(pos,68);
                printf("->");
            }else if(iMonstro.codMonstro == codMAX && pag != 0){
                gotoxy(pos,25);
                printf("<-");
            }else if(pag > 0){
                gotoxy(pos,25);
                printf("<-");
                gotoxy(pos,68);
                printf("->");
            }

			fseek(pArquivo,(sizeof(monstro) * (-1)), SEEK_CUR);
			fflush(stdin);

			pos = 17;
			status = 0;

            do {
                key = getch();
                if (key == KEY_RIGHT && iMonstro.codMonstro != codMAX) {
                    status = 1;
                    pag++;
                    contador = 0;
                } else if(key == KEY_LEFT && pag > 0) {
                    status = 1;
                    contador = 0;
                    pag--;
                    if(pag >= 2)
                        fseek(pArquivo,(sizeof(monstro) * (pag * 5 + 1)), SEEK_SET);
                    else
                        fseek(pArquivo,(sizeof(monstro) * (pag * 5)), SEEK_SET);
                } else if (key == KEY_ESC)
                    status = 1;

            } while(status == 0);

			system("cls");
			mostraTitulo();
			gotoxy(13, 73);
			printf(" LISTA DE MONSTROS ");

		}
	}
	fclose(pArquivo);
}

void consultarMonstro(){
    FILE *pArquivo = fopen(".\\database\\monstros.info", "rb");
    char nomeMonstro[21];
    int status;
    monstro iMonstro;

    system("cls");
    mostraTitulo();

    if(pArquivo == NULL){
        gotoxy(18, 73);
        printf("Erro ao abrir o arquivo!");
        gotoxy(19, 45);
    } else{
        gotoxy(13, 73);
        printf(" CONSULTAR MONSTROS ");
        gotoxy(16, 40);
        printf(" Digite o nome do monstro:");
        gotoxy(17, 40);
        printf(" Código |         Nome         | Qtd. Vida | Qtd. Dano | Categoria | Taxa de spawn \n");
       	gotoxy(18, 40);
        printf(" --------------------------------------------------------------------------------- \n");
        gotoxy(16, 66);
        showcursor(TRUE);
        gets(nomeMonstro);
        showcursor(FALSE);
        do{
            status = fread(&iMonstro, sizeof(monstro), 1, pArquivo);
        }while(!(strcmp(nomeMonstro, iMonstro.nome) == 0 && iMonstro.deletado == 0) && status == 1 );
        if(strcmp(nomeMonstro, iMonstro.nome) == 0 && iMonstro.deletado == 0){
            gotoxy(19, 40);
            printf(" %6d |", iMonstro.codMonstro);
            printf(" %20s |", iMonstro.nome);
            printf(" %9d |", iMonstro.vida);
            printf(" %9d |", iMonstro.dano);
            printf(" %9c |", iMonstro.categoria);
            printf(" %13d \n", iMonstro.taxaSpawn);
        } else{
            gotoxy(19, 45);
            printf("Não foi possivel encontrar o monstro informado!");
        }
        fclose(pArquivo);
        gotoxy(20, 45);
    }
    system("pause");
}

void excluirMonstro(){
    FILE *pArquivo = fopen(".\\database\\monstros.info", "r+b");
    char nomeMonstro[21], resposta;
    int status;
    monstro iMonstro;

    system("cls");
    mostraTitulo();

    if(pArquivo == NULL){
        gotoxy(18, 73);
        printf("Erro ao abrir o arquivo!");
        gotoxy(19, 45);
    } else{
        gotoxy(13, 73);
        printf(" EXCLUIR MONSTROS ");
        gotoxy(16, 40);
        printf(" Digite o nome do monstro:");
        gotoxy(17, 40);
        printf(" Código |         Nome         | Qtd. Vida | Qtd. Dano | Categoria | Taxa de spawn \n");
       	gotoxy(18, 40);
        printf(" --------------------------------------------------------------------------------- \n");
        gotoxy(16, 66);
        showcursor(TRUE);
        gets(nomeMonstro);
        showcursor(FALSE);
        do{
            status = fread(&iMonstro, sizeof(monstro), 1, pArquivo);
        }while(!(strcmp(nomeMonstro, iMonstro.nome) == 0 && iMonstro.deletado == 0) && status == 1 );
        if(strcmp(nomeMonstro, iMonstro.nome) == 0 && iMonstro.deletado == 0){
            gotoxy(19, 40);
            printf(" %6d |", iMonstro.codMonstro);
            printf(" %20s |", iMonstro.nome);
            printf(" %9d |", iMonstro.vida);
            printf(" %9d |", iMonstro.dano);
            printf(" %9c |", iMonstro.categoria);
            printf(" %13d \n", iMonstro.taxaSpawn);
            gotoxy(21, 45);
            printf("Deseja excluir? (S/N): ");
            showcursor(TRUE);
            resposta = getchar();
            showcursor(FALSE);
            resposta = toupper(resposta);
            
            gotoxy(21, 45);
            	printf("                         ");
            	
            if(resposta == 'S'){
            	
                iMonstro.deletado = 1;
                fseek(pArquivo, -1*(sizeof(monstro)), SEEK_CUR);
                fwrite(&iMonstro, sizeof(monstro), 1, pArquivo);
                gotoxy(21, 45);
                printf("Monstro excluído!");
            }else{
                gotoxy(21, 45);
                printf("Monstro não foi excluído!");
            }
            gotoxy(23, 45);
        } else{
            gotoxy(21, 45);
            printf("Não foi possivel encontrar o monstro informado!");
            gotoxy(23, 45);
        }
        fclose(pArquivo);
    }
    system("pause");
}

void alterarMonstro(){
    FILE *pArquivo = fopen(".\\database\\monstros.info", "r+b");
    char nomeMonstro[21], resposta;
    int status;
    monstro iMonstro;

    system("cls");
    mostraTitulo();

    if(pArquivo == NULL){
        gotoxy(18, 73);
        printf("Erro ao abrir o arquivo!");
        gotoxy(19, 45);
    } else{
        gotoxy(13, 73);
        printf(" EXCLUIR MONSTROS ");
        gotoxy(16, 40);
        printf(" Digite o nome do monstro:");
        gotoxy(17, 40);
        printf(" Código |         Nome         | Qtd. Vida | Qtd. Dano | Categoria | Taxa de spawn \n");
       	gotoxy(18, 40);
        printf(" --------------------------------------------------------------------------------- \n");
        gotoxy(16, 66);
        showcursor(TRUE);
        gets(nomeMonstro);
        showcursor(FALSE);
        do{
            status = fread(&iMonstro, sizeof(monstro), 1, pArquivo);
        }while(!(strcmp(nomeMonstro, iMonstro.nome) == 0 && iMonstro.deletado == 0) && status == 1 );
        if(strcmp(nomeMonstro, iMonstro.nome) == 0 && iMonstro.deletado == 0){
            gotoxy(19, 40);
            printf(" %6d |", iMonstro.codMonstro);
            printf(" %20s |", iMonstro.nome);
            printf(" %9d |", iMonstro.vida);
            printf(" %9d |", iMonstro.dano);
            printf(" %9c |", iMonstro.categoria);
            printf(" %13d \n", iMonstro.taxaSpawn);
            gotoxy(21, 45);
            printf("Deseja Alterar? (S/N): ");
            showcursor(TRUE);
            resposta = getchar();
            showcursor(FALSE);
            resposta = toupper(resposta);
            
            gotoxy(21, 45);
            printf("                             ");
            
            if(resposta == 'S'){
                gotoxy(22, 56);
                printf("NOVAS INFORMAÇÕES");
                gotoxy(24, 40);
                printf("Nome:");
                gotoxy(25, 40);
                printf("Quantidade de vida: ");
                gotoxy(26, 40);
                printf("Quantidade de dano: ");
                gotoxy(27, 40);
                printf("Categoria: ");
                gotoxy(28, 40);
                printf("Taxa de spawn: ");

                showcursor(TRUE);
                gotoxy(24, 46);
                fflush(stdin);
                gets(iMonstro.nome);
                gotoxy(25, 60);
                scanf("%d", &iMonstro.vida);
                gotoxy(26, 60);
                scanf("%d", &iMonstro.dano);
                gotoxy(27, 51);
                fflush(stdin);
                scanf("%c", &iMonstro.categoria);
                iMonstro.categoria = toupper(iMonstro.categoria);
                gotoxy(28, 55);
                scanf("%d", &iMonstro.taxaSpawn);
                showcursor(FALSE);

                fseek(pArquivo, -1*(sizeof(monstro)), SEEK_CUR);
                fwrite(&iMonstro, sizeof(monstro), 1, pArquivo);
                gotoxy(30, 56);
                printf("Monstro alterado!");
                gotoxy(32, 45);
            }else{
                gotoxy(30, 56);
                printf("Monstro não foi alterado!");
                gotoxy(32, 45);
            }
        } else{
            gotoxy(22, 45);
            printf("Não foi possivel encontrar o monstro informado!");
            gotoxy(24, 45);
        }
        fclose(pArquivo);
    }
    system("pause");
}

#endif // MONSTROS_H
