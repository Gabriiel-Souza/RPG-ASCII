#include "interface.h"
#include "defaults.h"
#include <ctype.h>

#ifndef COMERCIANTES_H
#define COMERCIANTES_H

void incluirComerciante(){
    FILE *pArquivo = fopen(".\\database\\comerciantes.info", "r+b");
    FILE *pNumItens, *pItens = fopen(".\\database\\itens.info", "r+b");
    comerciante iComerciante;
    item iItem;
    int codComerciante = 1, i;
    char itens[5][31];
    int codMaximo =0;

    system("cls");
    mostraTitulo();

    if(pArquivo == NULL || pItens == NULL){
        gotoxy(9, 40);
        printf("Erro ao abri o arquivo!");
        Sleep(2000);
    } else{
        pNumItens = fopen(".\\database\\numItens.info", "rb");
        if(pNumItens != NULL){
            while(fread(&codMaximo, sizeof(int), 1, pNumItens));
            fclose(pNumItens);
        }else{
            pNumItens = fopen(".\\database\\numItens.info", "wb");
            while(fread(&iItem, sizeof(item), 1, pItens)){
                if(iItem.deletado == 0)
                    codMaximo = iItem.codItem;
            }
            fseek(pItens,0, SEEK_SET);
        }

        for(i =0; i < 5; i++){
            do{
                iComerciante.itens[i] = (rand()%codMaximo) + 1;
                fseek(pItens,0, SEEK_SET);
                while(fread(&iItem, sizeof(item), 1, pItens) && iItem.codItem != iComerciante.itens[i]);
            }while(!(iItem.codItem == iComerciante.itens[i] && iItem.deletado == 0));
            strcpy(itens[i], iItem.nome);
        }

        while(fread(&iComerciante, sizeof(comerciante), 1, pArquivo)){
            if(iComerciante.deletado == 0)
                codComerciante = iComerciante.codComerciante;
        }

        iComerciante.codComerciante = codComerciante+1;
        iComerciante.deletado =0;

        gotoxy(9, 40);
        printf("Código: %d", iComerciante.codComerciante);
        gotoxy(10, 40);
        printf("Nome:");
        gotoxy(11, 40);
        printf("1º item:");
        gotoxy(12, 40);
        printf("Valor:");
        gotoxy(13, 40);
        printf("2º item:");
        gotoxy(14, 40);
        printf("Valor:");
        gotoxy(15, 40);
        printf("3º item:");
        gotoxy(16, 40);
        printf("Valor:");
        gotoxy(17, 40);
        printf("4º item:");
        gotoxy(18, 40);
        printf("Valor:");
        gotoxy(19, 40);
        printf("5º item:");
        gotoxy(20, 40);
        printf("Valor:");

        showcursor(TRUE);
        gotoxy(10, 46);
        fflush(stdin);
        gets(iComerciante.nome);
        gotoxy(11, 49);
        printf("%s", itens[0]);
        gotoxy(12, 47);
        scanf("%d", &iComerciante.valores[0]);
        gotoxy(13, 49);
        printf("%s", itens[1]);
        gotoxy(14, 47);
        scanf("%d", &iComerciante.valores[1]);
        gotoxy(15, 49);
        printf("%s", itens[2]);
        gotoxy(16, 47);
        scanf("%d", &iComerciante.valores[2]);
        gotoxy(17, 49);
        printf("%s", itens[3]);
        gotoxy(18, 47);
        scanf("%d", &iComerciante.valores[3]);
        gotoxy(19, 49);
        printf("%s", itens[4]);
        gotoxy(20, 47);
        scanf("%d", &iComerciante.valores[4]);
        showcursor(FALSE);

        fwrite(&iComerciante, sizeof(comerciante), 1, pArquivo);
        fclose(pArquivo);

        gotoxy(22, 40);
        printf("COMERCIANTE ADICIONADO!");
        Sleep(2000);
        fflush(stdin);
    }
}

void listarComerciantes() {
    FILE *pComerciante = fopen(".\\database\\comerciantes.info", "r+b");
    FILE *pItens = fopen(".\\database\\itens.info", "rb");
    int pos = 11, i, status, achei, contador=0, pag =0, key=0, funfando, codMAX;
    char itens[5][31];
    int valores[5];
    comerciante iComerciante;
    item iItem;

    system("cls");
    mostraTitulo();

    if(pComerciante == NULL){
        gotoxy(9, 40);
        printf("Erro ao abrir o arquivo!");
        Sleep(2000);
    } else{
		gotoxy(9, 45);
        printf(" COMERCIANTES ");
        while(fread(&iComerciante, sizeof(comerciante), 1, pComerciante)){
            if(iComerciante.deletado == 0)
                codMAX = iComerciante.codComerciante;
        }
        fseek(pComerciante, 0, SEEK_SET);
		while(key != KEY_ESC) {
            while(fread(&iComerciante, sizeof(comerciante), 1, pComerciante) && contador < 2){
                if(iComerciante.deletado == 0){
                    for(i = 0; i < 5; i++){
                        fseek(pItens, 0, SEEK_SET);
                        achei =0;
                        do{
                            status = fread(&iItem, sizeof(item), 1, pItens);
                            if(iItem.codItem == iComerciante.itens[i])
                                achei =1;
                        }while(achei == 0 && status != 0);
                        if(achei == 0){
                            strcpy(itens[i], "INEXISTENTE");
                            valores[i] = 0;
                        }else{
                            strcpy(itens[i], iItem.nome);
                            valores[i] = iComerciante.valores[i];
                        }
                    }
                    gotoxy(pos, 15);
                    printf(" Código: %6d | Nome: %s", iComerciante.codComerciante, iComerciante.nome);
                    gotoxy(++pos, 15);
                    printf(" 1º Item: %-31s | Valor: %4d moedas", itens[0], valores[0]);
                    gotoxy(++pos, 15);
                    printf(" 2º Item: %-31s | Valor: %4d moedas", itens[1], valores[1]);
                    gotoxy(++pos, 15);
                    printf(" 3º Item: %-31s | Valor: %4d moedas", itens[2], valores[2]);
                    gotoxy(++pos, 15);
                    printf(" 4º Item: %-31s | Valor: %4d moedas", itens[3], valores[3]);
                    gotoxy(++pos, 15);
                    printf(" 5º Item: %-31s | Valor: %4d moedas", itens[4], valores[4]);
                    gotoxy(++pos, 15);
                    printf(" -----------------------------------------------------------------------");
                    pos++;
                }

            }
            gotoxy(++pos,35);
            printf("Pressione ESC para sair");
            if(pag == 0 && iComerciante.codComerciante != codMAX){
                gotoxy(pos,68);
                printf("->");
            }else if(iComerciante.codComerciante == codMAX && pag != 0){
                gotoxy(pos,25);
                printf("<-");
            }else if(pag > 0){
                gotoxy(pos,25);
                printf("<-");
                gotoxy(pos,68);
                printf("->");
            }

			fseek(pComerciante,(sizeof(comerciante) * (-1)), SEEK_CUR);
			fflush(stdin);

			pos = 11;
			funfando = 0;

            do {
                key = getch();
                if (key == KEY_RIGHT && iComerciante.codComerciante != codMAX) {
                    funfando = 1;
                    pag++;
                    contador = 0;
                } else if(key == KEY_LEFT && pag > 0) {
                    funfando = 1;
                    contador = 0;
                    pag--;
                    if(pag >= 2)
                        fseek(pComerciante,(sizeof(item) * (pag * 2 + 1)), SEEK_SET);
                    else
                        fseek(pComerciante,(sizeof(comerciante)*(pag*2)), SEEK_SET);
                } else if (key == KEY_ESC)
                    funfando = 1;
            } while(funfando == 0);
			system("cls");
			mostraTitulo();
			gotoxy(9, 45);
            printf(" COMERCIANTES ");
		}
	}
	fclose(pComerciante);
}

void consultarComerciante(){
    FILE *pComerciante = fopen(".\\database\\comerciantes.info", "rb");
    FILE *pItens = fopen(".\\database\\itens.info", "rb");
    char buffer[21], nomeComerciante[21];
    int i, status, achei;
    char itens[5][31];
    int valores[5];
    comerciante iComerciante;
    item iItem;

    system("cls");
    mostraTitulo();

    if(pComerciante == NULL || pItens == NULL){
        gotoxy(9, 30);
        printf("Erro ao abri o arquivo!");
        gotoxy(11, 30);
    } else{
        gotoxy(9, 37);
        printf(" CONSULTAR COMERCIANTES ");
        gotoxy(11, 15);
        printf(" Digite o nome do comerciante:");
        gotoxy(13, 15);
        printf(" Código: %6s | Nome:", " ");
        gotoxy(14, 15);
        printf(" 1º Item: %-31s | Valor:", " ");
        gotoxy(15, 15);
        printf(" 2º Item: %-31s | Valor:", " ");
        gotoxy(16, 15);
        printf(" 3º Item: %-31s | Valor:", " ");
        gotoxy(17, 15);
        printf(" 4º Item: %-31s | Valor:", " ");
        gotoxy(18, 15);
        printf(" 5º Item: %-31s | Valor:", " ");
        gotoxy(19, 15);
        printf(" -----------------------------------------------------------------------");

        gotoxy(11, 46);
        showcursor(TRUE);
        gets(nomeComerciante);
        showcursor(FALSE);

        do{
            status = fread(&iComerciante, sizeof(comerciante), 1, pComerciante);
            strcpy(buffer, iComerciante.nome);
        }while(!(strcmp(nomeComerciante, buffer) == 0 && iComerciante.deletado == 0) && status == 1 );
        if(strcmp(nomeComerciante, buffer) == 0 && iComerciante.deletado == 0){
            for(i = 0; i < 5; i++){
                fseek(pItens, 0, SEEK_SET);
                achei =0;
                do{
                    status = fread(&iItem, sizeof(item), 1, pItens);
                    if(iItem.codItem == iComerciante.itens[i])
                        achei =1;
                }while(achei == 0 && status != 0);
                if(achei == 0){
                    strcpy(itens[i], "~INEXISTENTE~");
                    valores[i] = 0;
                }else{
                    strcpy(itens[i], iItem.nome);
                    valores[i] = iComerciante.valores[i];
                }
            }
            gotoxy(13, 24);
            printf("%6d", iComerciante.codComerciante);
            gotoxy(13, 39);
            printf("%s", iComerciante.nome);
            gotoxy(14, 25);
            printf("%-31s", itens[0]);
            gotoxy(14, 66);
            printf("%d moedas", valores[0]);
            gotoxy(15, 25);
            printf("%-31s", itens[1]);
            gotoxy(15, 66);
            printf("%d moedas", valores[1]);
            gotoxy(16, 25);
            printf("%-31s", itens[2]);
            gotoxy(16, 66);
            printf("%d moedas", valores[2]);
            gotoxy(17, 25);
            printf("%-31s", itens[3]);
            gotoxy(17, 66);
            printf("%d moedas", valores[3]);
            gotoxy(18, 25);
            printf("%-31s", itens[4]);
            gotoxy(18,66);
            printf("%d moedas", valores[4]);
            gotoxy(21, 28);
        } else{
            gotoxy(20, 26);
            printf("Não foi possivel encontrar o comerciante informado!");
            gotoxy(22, 28);
        }
    }
    fclose(pComerciante);
    fclose(pItens);
    system("pause");
}

void excluirComerciante(){
    FILE *pComerciante = fopen(".\\database\\comerciantes.info", "r+b");
    FILE *pItens = fopen(".\\database\\itens.info", "rb");
    char buffer[21], nomeComerciante[21], resposta;
    int i, status, achei;
    char itens[5][31];
    int valores[5];
    comerciante iComerciante;
    item iItem;

    system("cls");
    mostraTitulo();

    if(pComerciante == NULL || pItens == NULL){
        gotoxy(9, 30);
        printf("Erro ao abri o arquivo!");
        gotoxy(11, 30);
    } else{
        gotoxy(9, 37);
        printf(" EXCLUIR COMERCIANTES ");
        gotoxy(11, 15);
        printf(" Digite o nome do comerciante:");
        gotoxy(13, 15);
        printf(" Código: %6s | Nome:", " ");
        gotoxy(14, 15);
        printf(" 1º Item: %-31s | Valor:", " ");
        gotoxy(15, 15);
        printf(" 2º Item: %-31s | Valor:", " ");
        gotoxy(16, 15);
        printf(" 3º Item: %-31s | Valor:", " ");
        gotoxy(17, 15);
        printf(" 4º Item: %-31s | Valor:", " ");
        gotoxy(18, 15);
        printf(" 5º Item: %-31s | Valor:", " ");
        gotoxy(19, 15);
        printf(" -----------------------------------------------------------------------");

        gotoxy(11, 46);
        showcursor(TRUE);
        gets(nomeComerciante);
        showcursor(FALSE);

        do{
            status = fread(&iComerciante, sizeof(comerciante), 1, pComerciante);
            strcpy(buffer, iComerciante.nome);
        }while(!(strcmp(nomeComerciante, buffer) == 0 && iComerciante.deletado == 0) && status == 1 );
        if(strcmp(nomeComerciante, buffer) == 0 && iComerciante.deletado == 0){
            for(i = 0; i < 5; i++){
                fseek(pItens, 0, SEEK_SET);
                achei =0;
                do{
                    status = fread(&iItem, sizeof(item), 1, pItens);
                    if(iItem.codItem == iComerciante.itens[i])
                        achei =1;
                }while(achei == 0 && status != 0);
                if(achei == 0){
                    strcpy(itens[i], "~INEXISTENTE~");
                    valores[i] = 0;
                }else{
                    strcpy(itens[i], iItem.nome);
                    valores[i] = iComerciante.valores[i];
                }
            }
            fseek(pComerciante, 0, SEEK_SET);
            do{
                status = fread(&iComerciante, sizeof(comerciante), 1, pComerciante);
                strcpy(buffer, iComerciante.nome);
            }while(!(strcmp(nomeComerciante, buffer) == 0 && iComerciante.deletado == 0) && status == 1 );
            gotoxy(13, 25);
            printf("%6d", iComerciante.codComerciante);
            gotoxy(13, 40);
            printf("%s", iComerciante.nome);
            gotoxy(14, 25);
            printf("%-31s", itens[0]);
            gotoxy(14, 66);
            printf("%d moedas", valores[0]);
            gotoxy(15, 25);
            printf("%-31s", itens[1]);
            gotoxy(15, 66);
            printf("%d moedas", valores[1]);
            gotoxy(16, 25);
            printf("%-31s", itens[2]);
            gotoxy(16, 66);
            printf("%d moedas", valores[2]);
            gotoxy(17, 25);
            printf("%-31s", itens[3]);
            gotoxy(17, 66);
            printf("%d moedas", valores[3]);
            gotoxy(18, 25);
            printf("%-31s", itens[4]);
            gotoxy(18,66);
            printf("%d moedas", valores[4]);
            gotoxy(21, 35);
            printf("Deseja excluir? (S/N): ");
            showcursor(TRUE);
            resposta = getchar();
            showcursor(FALSE);
            resposta = toupper(resposta);
            if(resposta == 'S'){
                iComerciante.deletado = 1;
                fseek(pComerciante, ((-1)*sizeof(comerciante)), SEEK_CUR);
                fwrite(&iComerciante, sizeof(comerciante), 1, pComerciante);
                gotoxy(22, 37);
                printf("comerciante excluído!");
            }else{
                gotoxy(22, 35);
                printf("comerciante não foi excluído!");
            }
            gotoxy(24, 28);
        } else{
            gotoxy(20, 26);
            printf("Não foi possivel encontrar o comerciante informado!");
            gotoxy(22, 28);
        }
    }
    fclose(pComerciante);
    fclose(pItens);
    system("pause");
}

void alterarComerciante(){
    FILE *pComerciante = fopen(".\\database\\comerciantes.info", "r+b");
    FILE *pItens = fopen(".\\database\\itens.info", "rb");
    char buffer[21], nomeComerciante[21], resposta;
    int i, status, achei;
    char itens[5][31];
    int valores[5];
    comerciante iComerciante;
    item iItem;

    system("cls");
    mostraTitulo();

    if(pComerciante == NULL || pItens == NULL){
        gotoxy(9, 30);
        printf("Erro ao abri o arquivo!");
        gotoxy(11, 30);
    } else{
        gotoxy(9, 37);
        printf("  ALTERAR COMERCIANTES ");
        gotoxy(11, 15);
        printf(" Digite o nome do comerciante:");
        gotoxy(13, 15);
        printf(" Código: %6s | Nome:", " ");
        gotoxy(14, 15);
        printf(" 1º Item: %-31s | Valor:", " ");
        gotoxy(15, 15);
        printf(" 2º Item: %-31s | Valor:", " ");
        gotoxy(16, 15);
        printf(" 3º Item: %-31s | Valor:", " ");
        gotoxy(17, 15);
        printf(" 4º Item: %-31s | Valor:", " ");
        gotoxy(18, 15);
        printf(" 5º Item: %-31s | Valor:", " ");
        gotoxy(19, 15);
        printf(" -----------------------------------------------------------------------");

        gotoxy(11, 46);
        showcursor(TRUE);
        gets(nomeComerciante);
        showcursor(FALSE);

        do{
            status = fread(&iComerciante, sizeof(comerciante), 1, pComerciante);
            strcpy(buffer, iComerciante.nome);
        }while(!(strcmp(nomeComerciante, buffer) == 0 && iComerciante.deletado == 0) && status == 1 );
        if(strcmp(nomeComerciante, buffer) == 0 && iComerciante.deletado == 0){
            for(i = 0; i < 5; i++){
                fseek(pItens, 0, SEEK_SET);
                achei =0;
                do{
                    status = fread(&iItem, sizeof(item), 1, pItens);
                    if(iItem.codItem == iComerciante.itens[i])
                        achei =1;
                }while(achei == 0 && status != 0);
                if(achei == 0){
                    strcpy(itens[i], "~INEXISTENTE~");
                    valores[i] = 0;
                }else{
                    strcpy(itens[i], iItem.nome);
                    valores[i] = iComerciante.valores[i];
                }
            }
            gotoxy(13, 25);
            printf("%6d", iComerciante.codComerciante);
            gotoxy(13, 40);
            printf("%s", iComerciante.nome);
            gotoxy(14, 25);
            printf("%-31s", itens[0]);
            gotoxy(14, 66);
            printf("%d moedas", valores[0]);
            gotoxy(15, 25);
            printf("%-31s", itens[1]);
            gotoxy(15, 66);
            printf("%d moedas", valores[1]);
            gotoxy(16, 25);
            printf("%-31s", itens[2]);
            gotoxy(16, 66);
            printf("%d moedas", valores[2]);
            gotoxy(17, 25);
            printf("%-31s", itens[3]);
            gotoxy(17, 66);
            printf("%d moedas", valores[3]);
            gotoxy(18, 25);
            printf("%-31s", itens[4]);
            gotoxy(18,66);
            printf("%d moedas", valores[4]);
            gotoxy(21, 35);
            printf("Deseja alterar? (S/N): ");
            showcursor(TRUE);
            resposta = getchar();
            showcursor(FALSE);
            resposta = toupper(resposta);
            if(resposta == 'S'){
                gotoxy(23, 30);
                printf("NOVAS INFORMAÇÕES:");

                gotoxy(24, 30);
                printf("Nome:");
                gotoxy(25, 30);
                printf("Código do 1º item:");
                gotoxy(26, 30);
                printf("Valor:");
                gotoxy(27, 30);
                printf("Código do 2º item:");
                gotoxy(28, 30);
                printf("Valor:");
                gotoxy(29, 30);
                printf("Código do 3º item:");
                gotoxy(30, 30);
                printf("Valor:");
                gotoxy(31, 30);
                printf("Código do 4º item:");
                gotoxy(32, 30);
                printf("Valor:");
                gotoxy(33, 30);
                printf("Código do 5º item:");
                gotoxy(34, 30);
                printf("Valor:");

                showcursor(TRUE);
                gotoxy(24, 36);
                fflush(stdin);
                gets(iComerciante.nome);
                gotoxy(25, 49);
                scanf("%d", &iComerciante.itens[0]);
                gotoxy(26, 37);
                scanf("%d", &iComerciante.valores[0]);
                gotoxy(27, 49);
                scanf("%d", &iComerciante.itens[1]);
                gotoxy(28, 37);
                scanf("%d", &iComerciante.valores[1]);
                gotoxy(29, 49);
                scanf("%d", &iComerciante.itens[2]);
                gotoxy(30, 37);
                scanf("%d", &iComerciante.valores[2]);
                gotoxy(31, 49);
                scanf("%d", &iComerciante.itens[3]);
                gotoxy(32, 37);
                scanf("%d", &iComerciante.valores[3]);
                gotoxy(33, 49);
                scanf("%d", &iComerciante.itens[4]);
                gotoxy(34, 37);
                scanf("%d", &iComerciante.valores[4]);
                showcursor(FALSE);

                fseek(pComerciante, (sizeof(comerciante)*(-1)), SEEK_CUR);
                fwrite(&iComerciante, sizeof(comerciante), 1, pComerciante);
                gotoxy(36, 38);
                printf("comerciante alterado!");
                gotoxy(38, 28);
            }else{
                gotoxy(22, 35);
                printf("comerciante não foi alterado!");
                gotoxy(24, 28);
            }
        } else{
            gotoxy(20, 26);
            printf("Não foi possivel encontrar o comerciante informado!");
            gotoxy(22, 28);
        }
    }
    fclose(pComerciante);
    fclose(pItens);
    system("pause");
}

#endif // COMERCIANTES_H
