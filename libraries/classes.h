#include "interface.h"
#include "defaults.h"
#include <ctype.h>
#include "conio.h"

#ifndef CLASSES_H
#define CLASSES_H

void incluirClasse(){
    FILE *pArquivo = fopen(".\\database\\classes.info", "r+b");
    classe iClasse;
    int codClasse =1;

    system("cls");
    mostraTitulo();
		
		mostraPergaminho(3);
		
    if(pArquivo == NULL){

    	gotoxy(18, 73);
        printf("Erro ao abrir o arquivo!");
        Sleep(2000);
    } else{
        while(fread(&iClasse, sizeof(classe), 1, pArquivo)){
            if(iClasse.deletado == 0)
                codClasse = iClasse.codClasse;
        }

        iClasse.codClasse = codClasse+1;
        iClasse.deletado =0;

        gotoxy(13, 63);
        printf("ADICIONAR NOVA CLASSE");
        gotoxy(16, 40);
        printf("* Código: %d", iClasse.codClasse);
        gotoxy(17, 40);
        printf("* Nome:");
        gotoxy(18, 40);
        printf("* Quantidade de vida: ");
        gotoxy(19, 40);
        printf("* Quantidade de dano: ");
        gotoxy(20, 40);
        printf("* Nome da primeira habilidade: ");
        gotoxy(21, 40);
        printf("* Dano da primeira habilidade: ");
        gotoxy(22, 40);
        printf("* Nome da segunda habilidade: ");
        gotoxy(23, 40);
        printf("* Dano da segunda habilidade: ");
        gotoxy(24, 40);
        printf("* Nome da terceira habilidade: ");
        gotoxy(25, 40);
        printf("* Dano da terceira habilidade: ");

        showcursor(TRUE);
        gotoxy(17, 48);
        fflush(stdin);
        gets(iClasse.nome);
        gotoxy(18, 62);
        scanf("%d", &iClasse.vidaBase);
        gotoxy(19, 62);
        scanf("%d", &iClasse.danoBase);
        gotoxy(20, 71);
        fflush(stdin);
        gets(iClasse.nomeH1);
        gotoxy(21, 71);
        scanf("%d", &iClasse.danoH1);
        gotoxy(22, 70);
        fflush(stdin);
        gets(iClasse.nomeH2);
        gotoxy(23, 70);
        scanf("%d", &iClasse.danoH2);
        gotoxy(24, 71);
        fflush(stdin);
        gets(iClasse.nomeH3);
        gotoxy(25, 71);
        scanf("%d", &iClasse.danoH3);
        showcursor(FALSE);

        fwrite(&iClasse, sizeof(classe), 1, pArquivo);
        fclose(pArquivo);

        gotoxy(27, 63);
        printf("CLASSE ADICIONADA!");
        Sleep(2000);
    }
}

void consultarClasse(){
    FILE *pArquivo = fopen(".\\database\\classes.info", "rb");
    char nomeClasse[21];
    int status;
    classe iClasse;

    system("cls");
    mostraTitulo();

    if(pArquivo == NULL){
        
		mostraPergaminho(3);
		gotoxy(18, 73);
        printf("Erro ao abrir o arquivo!");
        Sleep(2000);
        
    } else{
    	
        gotoxy(13, 63);
        printf(" CONSULTAR CLASSES ");
        gotoxy(16, 40);
        printf(" Digite o nome da classe:");
        gotoxy(17, 40);
        printf(" Código | Nome                 | Qtd. Vida Base | Qtd. Dano Base");
        gotoxy(19, 40);
        printf(" Habilidade 1: %32s | Dano: ", " ");
        gotoxy(20, 40);
        printf(" Habilidade 2: %32s | Dano: ", " ");
        gotoxy(21, 40);
        printf(" Habilidade 3: %32s | Dano: ", " ");
        gotoxy(22, 40);
        printf(" ---------------------------------------------------------------");
        gotoxy(16, 66);
        showcursor(TRUE);
        gets(nomeClasse);
        showcursor(FALSE);
        
        do{
            status = fread(&iClasse, sizeof(classe), 1, pArquivo);
        }while(!(strcmp(nomeClasse, iClasse.nome) == 0 && iClasse.deletado == 0) && status == 1 );
        if(strcmp(nomeClasse, iClasse.nome) == 0 && iClasse.deletado == 0){
            gotoxy(18, 40);
            printf(" %6d  ", iClasse.codClasse);
            printf(" %-20s  ", iClasse.nome);
            printf(" %14d  ", iClasse.vidaBase);
            printf(" %13d ", iClasse.danoBase);
            gotoxy(19, 56);
            printf("%s", iClasse.nomeH1);
            gotoxy(20, 56);
            printf("%s", iClasse.nomeH2);
            gotoxy(21, 56);
            printf("%s", iClasse.nomeH3);
            gotoxy(19, 96);
            printf("%d", iClasse.danoH1);
            gotoxy(20, 96);
            printf("%d", iClasse.danoH2);
            gotoxy(21, 96);
            printf("%d", iClasse.danoH3);
            
        } else{
            gotoxy(19, 26);
            printf("Não foi possivel encontrar a classe informada!");
        }
        
        fclose(pArquivo);
        gotoxy(21, 28);
    }
    
    gotoxy(32, 55);
    system("pause");
}

void excluirClasse(){
    FILE *pArquivo = fopen(".\\database\\classes.info", "r+b");
    char nomeClasse[21], resposta;
    int status;
    classe iClasse;

    system("cls");
    mostraTitulo();

    if(pArquivo == NULL){
        gotoxy(18, 63);
        printf("Erro ao abrir o arquivo!");
        gotoxy(19, 45);
    } else{
        gotoxy(13, 63);
        printf(" CONSULTAR CLASSES ");
        gotoxy(16, 40);
        printf(" Digite o nome da classe:");
        gotoxy(17, 40);
        printf(" Código | Nome                 | Qtd. Vida Base | Qtd. Dano Base");
        gotoxy(18, 40);
        printf(" Habilidade 1: %32s | Dano: ", " ");
        gotoxy(19, 40);
        printf(" Habilidade 2: %32s | Dano: ", " ");
        gotoxy(20, 40);
        printf(" Habilidade 3: %32s | Dano: ", " ");
        gotoxy(21, 40);
        printf(" ---------------------------------------------------------------");
        gotoxy(16, 66);
        showcursor(TRUE);
        gets(nomeClasse);
        showcursor(FALSE);
        do{
            status = fread(&iClasse, sizeof(classe), 1, pArquivo);
        }while(!(strcmp(nomeClasse, iClasse.nome) == 0 && iClasse.deletado == 0) && status == 1 );
        if(strcmp(nomeClasse, iClasse.nome) == 0 && iClasse.deletado == 0){
            gotoxy(18, 40);
            printf(" %6d  ", iClasse.codClasse);
            printf(" %-20s  ", iClasse.nome);
            printf(" %14d  ", iClasse.vidaBase);
            printf(" %13d ", iClasse.danoBase);
            gotoxy(19, 56);
            printf("%s", iClasse.nomeH1);
            gotoxy(20, 56);
            printf("%s", iClasse.nomeH2);
            gotoxy(21, 56);
            printf("%s", iClasse.nomeH3);
            gotoxy(19, 96);
            printf("%d", iClasse.danoH1);
            gotoxy(20, 96);
            printf("%d", iClasse.danoH2);
            gotoxy(21, 96);
            printf("%d", iClasse.danoH3);
            gotoxy(23, 63);
            printf("Deseja excluir? (S/N): ");
            showcursor(TRUE);
            resposta = getchar();
            showcursor(FALSE);
            resposta = toupper(resposta);
            if(resposta == 'S'){
                iClasse.deletado = 1;
                fseek(pArquivo, -1*(sizeof(classe)), SEEK_CUR);
                fwrite(&iClasse, sizeof(classe), 1, pArquivo);
                gotoxy(23, 63);
                printf("                        ");
                gotoxy(23, 63);
                printf("Classe excluída!");
            }else{
                gotoxy(23, 35);
                printf("                      ");
                gotoxy(23, 63);
                printf("Classe não foi excluída!");
            }
            gotoxy(24, 45);
        } else{
            gotoxy(23, 63);
            printf("Não foi possivel encontrar a classe informada!");
            gotoxy(24, 45);
        }
        fclose(pArquivo);
    }
    system("pause");
}

void alterarClasse(){
    FILE *pArquivo = fopen(".\\database\\classes.info", "r+b");
    char nomeClasse[21], resposta;
    int status;
    classe iClasse;

    system("cls");
    mostraTitulo();

    if(pArquivo == NULL){
        gotoxy(18, 73);
        printf("Erro ao abrir o arquivo!");
    } else{
        gotoxy(13, 63);
        printf(" CONSULTAR CLASSES ");
        gotoxy(16, 40);
        printf(" Digite o nome da classe:");
        gotoxy(17, 40);
        printf(" Código | Nome                 | Qtd. Vida Base | Qtd. Dano Base");
        gotoxy(19, 40);
        printf(" Habilidade 1: %32s | Dano: ", " ");
        gotoxy(20, 40);
        printf(" Habilidade 2: %32s | Dano: ", " ");
        gotoxy(21, 40);
        printf(" Habilidade 3: %32s | Dano: ", " ");
        gotoxy(22, 40);
        printf(" ---------------------------------------------------------------");
        gotoxy(16, 66);
        showcursor(TRUE);
        gets(nomeClasse);
        showcursor(FALSE);
        do{
            status = fread(&iClasse, sizeof(classe), 1, pArquivo);
        }while(!(strcmp(nomeClasse, iClasse.nome) == 0 && iClasse.deletado == 0) && status == 1 );
        if(strcmp(nomeClasse, iClasse.nome) == 0 && iClasse.deletado == 0){
            gotoxy(18, 40);
            printf(" %6d  ", iClasse.codClasse);
            printf(" %-20s  ", iClasse.nome);
            printf(" %14d  ", iClasse.vidaBase);
            printf(" %13d ", iClasse.danoBase);
            gotoxy(19, 56);
            printf("%s", iClasse.nomeH1);
            gotoxy(20, 56);
            printf("%s", iClasse.nomeH2);
            gotoxy(21, 56);
            printf("%s", iClasse.nomeH3);
            gotoxy(19, 96);
            printf("%d", iClasse.danoH1);
            gotoxy(20, 96);
            printf("%d", iClasse.danoH2);
            gotoxy(21, 96);
            printf("%d", iClasse.danoH3);
            gotoxy(23, 63);
            printf("Deseja Alterar? (S/N): ");
            showcursor(TRUE);
            resposta = getchar();
            showcursor(FALSE);
            resposta = toupper(resposta);
            if(resposta == 'S'){
            	
            	gotoxy(23, 45);
            	printf("            ");
                gotoxy(23, 63);
                printf("NOVAS INFORMAÇÔES");
                gotoxy(26, 40);
                printf("Nome:");
                gotoxy(27, 40);
                printf("Quantidade de vida: ");
                gotoxy(28, 40);
                printf("Quantidade de dano: ");
                gotoxy(29, 40);
                printf("Nome da primeira habilidade: ");
                gotoxy(30, 40);
                printf("Dano da primeira habilidade: ");
                gotoxy(31, 40);
                printf("Nome da segunda habilidade: ");
                gotoxy(32, 40);
                printf("Dano da segunda habilidade: ");
                gotoxy(33, 40);
                printf("Nome da terceira habilidade: ");
                gotoxy(34, 40);
                printf("Dano da terceira habilidade: ");

                showcursor(TRUE);
                gotoxy(26, 46);
                fflush(stdin);
                gets(iClasse.nome);
                gotoxy(27, 60);;
                scanf("%d", &iClasse.vidaBase);
                gotoxy(28, 60);
                scanf("%d", &iClasse.danoBase);
                gotoxy(29, 69);
                fflush(stdin);
                gets(iClasse.nomeH1);
                gotoxy(30, 69);
                scanf("%d", &iClasse.danoH1);
                gotoxy(31, 68);
                fflush(stdin);
                gets(iClasse.nomeH2);
                gotoxy(32, 68);
                scanf("%d", &iClasse.danoH2);
                gotoxy(33, 69);
                fflush(stdin);
                gets(iClasse.nomeH3);
                gotoxy(34, 69);
                scanf("%d", &iClasse.danoH3);
                showcursor(FALSE);

                fseek(pArquivo, -1*(sizeof(classe)), SEEK_CUR);
                fwrite(&iClasse, sizeof(classe), 1, pArquivo);
                gotoxy(35, 63);
                printf("Classe alterada!");
                gotoxy(36, 45);
            }else{
                gotoxy(35, 63);
                printf("Classe não foi alterada!");
                gotoxy(36, 45);
            }
        } else{
            gotoxy(23, 45);
            printf("Não foi possivel encontrar a classe informada!");
            gotoxy(24, 45);
        }
        fclose(pArquivo);
    }
    system("pause");
}

void listarClasses() {
    FILE *pArquivo = fopen(".\\database\\classes.info", "rb");
    int pos = 20, contador = 0, key = 0, status, pag = 0, codMAX;
	classe iClasse;

	setlocale(LC_ALL,"");

	system("cls");
	mostraTitulo();

	if(pArquivo == NULL) {
		gotoxy(18, 73);
		printf("Erro ao abrir o arquivo!");
		Sleep(2000);
	} else {
		gotoxy(18, 73);
		printf(" CLASSES ");
		while(fread(&iClasse, sizeof(classe), 1, pArquivo)){
            if(iClasse.deletado == 0)
                codMAX = iClasse.codClasse;
        }
        fseek(pArquivo, 0, SEEK_SET);
		while(key != KEY_ESC) {
			while (fread(&iClasse, sizeof(classe), 1, pArquivo) == 1 && contador < 3) {
				if(!iClasse.deletado){
                    contador++;
                    gotoxy(pos, 40);
                    printf(" Código | Nome                 | Qtd. Vida Base | Qtd. Dano Base");
                    gotoxy(++pos, 40);
                    printf(" %6d  ", iClasse.codClasse);
                    printf(" %-20s  ", iClasse.nome);
                    printf(" %14d  ", iClasse.vidaBase);
                    printf(" %13d ", iClasse.danoBase);
                    gotoxy(++pos, 40);
                    printf(" Habilidade 1: %-32s | Dano: %d", iClasse.nomeH1, iClasse.danoH1);
                    gotoxy(++pos, 40);
                    printf(" Habilidade 2: %-32s | Dano: %d", iClasse.nomeH2, iClasse.danoH2);
                    gotoxy(++pos, 40);
                    printf(" Habilidade 3: %-32s | Dano: %d", iClasse.nomeH3, iClasse.danoH3);
                    gotoxy(++pos, 40);
                    printf(" ---------------------------------------------------------------");
                    pos++;
                }
			}

            gotoxy(++pos,40);
            printf("Pressione ESC para sair");
            if(pag == 0 && iClasse.codClasse != codMAX){
                gotoxy(pos,68);
                printf("->");
            }else if(iClasse.codClasse == codMAX && pag != 0){
                gotoxy(pos,25);
                printf("<-");
            }else if(pag > 0){
                gotoxy(pos,25);
                printf("<-");
                gotoxy(pos,68);
                printf("->");
            }

			fseek(pArquivo,(sizeof(classe) * (-1)), SEEK_CUR);
			fflush(stdin);

			pos = 20;
			status = 0;

            do {
                key = getch();
                if (key == KEY_RIGHT && iClasse.codClasse != codMAX) {
                    status = 1;
                    pag++;
                    contador = 0;
                } else if(key == KEY_LEFT && pag > 0) {
                    status = 1;
                    contador = 0;
                    pag--;
                    if(pag >= 2)
                        fseek(pArquivo,(sizeof(classe) * (pag * 3 + 1)), SEEK_SET);
                    else
                        fseek(pArquivo,(sizeof(classe) * (pag * 3)), SEEK_SET);
                } else if (key == KEY_ESC)
                    status = 1;
            } while(status == 0);

			system("cls");
			mostraTitulo();
			gotoxy(18, 73);
			printf(" CLASSES ");

		}
	}
	fclose(pArquivo);

}

#endif // CLASSES_H
