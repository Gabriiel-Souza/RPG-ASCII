#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h>

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_ESC 27
#define KEY_ENTER 13

#ifndef DEFAULTS_H
#define DEFAULTS_H

typedef struct tPersonagem {
	char nickname[21];
	int codClasse;
	int vida;
	int dano;
	int moeda;
	int danoH1;
	int danoH2;
	int danoH3;
	int fase;
} personagem;

typedef struct tClasse {
    int codClasse;
	char nome[21];
	int vidaBase;
	int danoBase;
    char nomeH1[31];
    char nomeH2[31];
    char nomeH3[31];
    int danoH1;
    int danoH2;
    int danoH3;
    int deletado;
} classe;

typedef struct tMonstro {
	int codMonstro;
	int taxaSpawn;
	char nome[21];
	int vida;
	int dano;
	char categoria;
	int codItem;
	int deletado;
} monstro;

typedef struct tComerciante {
	int codComerciante;
	char nome[21];
	int itens[5];
	int valores[5];
	int deletado;
} comerciante;

typedef struct tItem {
	int codItem;
	char nome[31];
	int probItem;
	char categoria;
	int moeda;
	int vida;
	int dano;
	int deletado;
} item;

void criaArquivosPadrao(){
    FILE *dArquivo; // d = default

    monstro dMonstros[14];
    classe dClasses[3];
    classe dClassesTeste[3];
    item dItens[2];
    comerciante dComerciantes;

    system("mkdir .\\database");
    system("mkdir .\\saves");
    system("cls");

// ***************** Definições de Classes padrão **************************

    dClasses[0].codClasse = 1;
    strcpy(dClasses[0].nome, "Mago");
    dClasses[0].vidaBase = 40;
    dClasses[0].danoBase = 10;
    strcpy(dClasses[0].nomeH1, "Rajada Congelante");
    strcpy(dClasses[0].nomeH2, "Rajada de Raios");
    strcpy(dClasses[0].nomeH3, "Obliteração Flamejante");
    dClasses[0].danoH1 = 200;
    dClasses[0].danoH2 = 250;
    dClasses[0].danoH3 = 300;
    dClasses[0].deletado = 0;

    dClasses[1].codClasse = 2;
    strcpy(dClasses[1].nome, "Guerreiro");
    dClasses[1].vidaBase = 100;
    dClasses[1].danoBase = 70;
    strcpy(dClasses[1].nomeH1, "Estocada");
    strcpy(dClasses[1].nomeH2, "Impulso");
    strcpy(dClasses[1].nomeH3, "Espada Boomerang");
    dClasses[1].danoH1 = 100;
    dClasses[1].danoH2 = 120;
    dClasses[1].danoH3 = 150;
    dClasses[1].deletado = 0;

    dClasses[2].codClasse = 3;
    strcpy(dClasses[2].nome, "Arqueiro");
    dClasses[2].vidaBase = 60;
    dClasses[2].danoBase = 30;
    strcpy(dClasses[2].nomeH1, "Rajada de Flechas");
    strcpy(dClasses[2].nomeH2, "Tiro Concentrado");
    strcpy(dClasses[2].nomeH3, "Flecha Flamejante");
    dClasses[2].danoH1 = 100;
    dClasses[2].danoH2 = 150;
    dClasses[2].danoH3 = 200;
    dClasses[2].deletado = 0;

    dArquivo = fopen(".\\database\\classes.info", "rb");
    if(dArquivo == NULL){
        fclose(dArquivo);
        dArquivo = fopen(".\\database\\classes.info", "wb");
        fwrite(&dClasses, sizeof(classe), 3, dArquivo);
    }
    fclose(dArquivo);

// ************************************************************************

// ***************** Definições de Monstros padrão ************************

    dMonstros[0].codMonstro = 1;
    strcpy(dMonstros[0].nome, "Slime");
    dMonstros[0].vida = 10;
    dMonstros[0].dano = 1;
    dMonstros[0].categoria = 'F';
    dMonstros[0].taxaSpawn = 70;
    dMonstros[0].deletado = 0;

    dMonstros[1].codMonstro = 2;
    strcpy(dMonstros[1].nome, "Goblin");
    dMonstros[1].vida = 20;
    dMonstros[1].dano = 5;
    dMonstros[1].categoria = 'E';
    dMonstros[1].taxaSpawn = 40;
    dMonstros[1].deletado = 0;

    dMonstros[2].codMonstro = 3;
    strcpy(dMonstros[2].nome, "Lobo");
    dMonstros[2].vida = 25;
    dMonstros[2].dano = 20;
    dMonstros[2].categoria = 'E';
    dMonstros[2].taxaSpawn = 10;
    dMonstros[2].deletado = 0;

    dMonstros[3].codMonstro = 4;
    strcpy(dMonstros[3].nome, "Orc");
    dMonstros[3].vida = 50;
    dMonstros[3].dano = 50;
    dMonstros[3].categoria = 'D';
    dMonstros[3].taxaSpawn = 40;
    dMonstros[3].deletado = 0;

    dMonstros[4].codMonstro = 5;
    strcpy(dMonstros[4].nome, "Ogro");
    dMonstros[4].vida = 50;
    dMonstros[4].dano = 50;
    dMonstros[4].categoria = 'D';
    dMonstros[4].taxaSpawn = 40;
    dMonstros[4].deletado = 0;

    dArquivo = fopen(".\\database\\monstros.info", "rb");
    if(dArquivo == NULL){
        fclose(dArquivo);
        dArquivo = fopen(".\\database\\monstros.info", "wb");
        fwrite(&dMonstros, sizeof(monstro), 5, dArquivo);
    }
    fclose(dArquivo);

// ************************************************************************

// ******************** Definições de Itens padrão ************************
    setlocale(LC_ALL, "");
    dItens[0].codItem = 1;
    strcpy(dItens[0].nome, "Poção de Vida");
    dItens[0].probItem = 50;
    dItens[0].categoria = 'F';
    dItens[0].moeda = 0;
    dItens[0].vida = 10;
    dItens[0].dano = 0;
    dItens[0].deletado =0;

    dItens[1].codItem = 2;
    strcpy(dItens[1].nome, "Espada Longa");
    dItens[1].probItem = 20;
    dItens[1].categoria = 'E';
    dItens[1].moeda = 0;
    dItens[1].vida = 0;
    dItens[1].dano = 10;
    dItens[1].deletado =0;

    dArquivo = fopen(".\\database\\itens.info", "rb");
    if(dArquivo == NULL){
        fclose(dArquivo);
        dArquivo = fopen(".\\database\\itens.info", "wb");
        fwrite(&dItens, sizeof(item), 2, dArquivo);
        fclose(dArquivo);
        dArquivo = fopen(".\\database\\numItens.info", "wb");
        fwrite(&dItens[1].codItem, sizeof(int), 1, dArquivo);
    }
    fclose(dArquivo);


// ************************************************************************

// ******************** Definições de Comerciantes padrão ************************

    dComerciantes.codComerciante = 1;
    strcpy(dComerciantes.nome, "Silvia");
    dComerciantes.itens[0] = 1;
    dComerciantes.itens[1] = 1;
    dComerciantes.itens[2] = 1;
    dComerciantes.itens[3] = 2;
    dComerciantes.itens[4] = 2;
    dComerciantes.valores[0] = 2;
    dComerciantes.valores[1] = 2;
    dComerciantes.valores[2] = 2;
    dComerciantes.valores[3] = 5;
    dComerciantes.valores[4] = 5;
    dComerciantes.deletado = 0;

    dArquivo = fopen(".\\database\\comerciantes.info", "rb");
    if(dArquivo == NULL){
        fclose(dArquivo);
        dArquivo = fopen(".\\database\\comerciantes.info", "wb");
        fwrite(&dComerciantes, sizeof(comerciante), 1, dArquivo);
    }
    fclose(dArquivo);

// ************************************************************************
}

void bkpRst(char selFunc, char pathOrigem[], char pathDestino[]){
    FILE *pArquivoOrigem;
    FILE *pArquivoDestino;
    char buffer[31];
    item iItem;

    if(selFunc == 'B')
        pArquivoOrigem = fopen(pathOrigem, "rb");
    else if(selFunc == 'R')
        pArquivoOrigem = fopen(pathOrigem, "rb");

    system("cls");
    mostraTitulo();

    if(pArquivoOrigem == NULL){
        gotoxy(13, 65);
        if(selFunc == 'B')
            printf("Não foi possível realizar o Backup!");
        else if(selFunc == 'R')
            printf("Não existe arquivo de Backup!");
        gotoxy(14, 40);
    } else{
        if(selFunc == 'B'){
            pArquivoDestino = fopen(pathDestino, "wb");
            strcpy(buffer, "Backup");
        }else if(selFunc == 'R'){
            pArquivoDestino = fopen(pathDestino, "wb");
            strcpy(buffer, "Restauração");
        }

        while(fread(&iItem, sizeof(item), 1, pArquivoOrigem)){
            if(iItem.deletado != 1)
                fwrite(&iItem, sizeof(item), 1, pArquivoDestino);
        }
        gotoxy(13, 65);
        printf("%s realizado com sucesso!", buffer);
        gotoxy(14, 45);
        fclose(pArquivoDestino);
    }
    fclose(pArquivoOrigem);
    system("pause");
}

#endif // DEFAULTS_H

