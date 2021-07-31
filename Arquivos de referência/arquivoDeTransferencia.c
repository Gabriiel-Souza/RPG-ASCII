int mostraCombate (personagem combate, itens equipamento) {
	FILE *itens = NULL;
	int posX = 27, posY = 3, key, opcao;

//	fazBorda();

	//Habilidades
	gotoxy(26,6);
	printf("Habilidades");
	gotoxy(27,6);
	printf("Ataque Básico: %d\n", combate.dano);
	gotoxy(28,6);
	printf("%s: %d\n", combate.nh1, combate.h1);
	gotoxy(29,6);
	printf("%s: %d\n", combate.nh2, combate.h2);
	gotoxy(30,6);
	printf("%s: %d\n\n", combate.nh3, combate.h3);

	//Poção
	gotoxy(26,70);
	printf("Poção\n");
	gotoxy(27,70);
	printf("Pot. Vida: %d", equipamento.probItem);

	do {

		gotoxy(posX,posY);
		printf(">>");

		key = getch();

		if(key == KEY_DOWN) {
			gotoxy(posX,posY);
			printf("  ");
			posX++;

			if (posY == 3) {

				if (posX > 30)
					posX = 27;

			} else {

				if (posX != 27)
					posX = 27;

			}

		}

		else if(key == KEY_UP) {
			gotoxy(posX,posY);
			printf("  ");
			posX--;

			if (posY == 3) {
				if(posX < 27)
					posX = 30;

			} else {

				if (posX != 27)
					posX = 27;

			}

		}

		else if(key == KEY_RIGHT) {
			gotoxy(posX,posY);
			printf("  ");
			posX = 27;
			posY = 67;
		}

		else if(key == KEY_LEFT) {
			gotoxy(posX,posY);
			printf("  ");
			posX = 27;
			posY = 3;
		}

	}	while(key != KEY_ENTER);

	opcao = posX + posY;

	switch (opcao) {
		case 32:
			opcao = 1;

			break;

		case 33:
			opcao = 2;

			break;

		case 34:
			opcao = 3;

			break;

		case 35:
			opcao = 4;

			break;

		case 93:
			opcao = 5;

	}

	return opcao;

}
void escolheInimigo (monstro *inimigo, int fase) {
	int dado;

	switch (fase) {
		case 1:
			dado = rand() % 10 + 1;
			break;
		case 2:
			dado = rand() % 20 + 1;
			break;
		case 3:
			dado = rand() % 30 + 1;

	}

	FILE *monstros = NULL;
	monstros = fopen("monstros.txt", "r");

	if (dado < 11) {
		do {
			fscanf(monstros,"%s",inimigo->nome);
		} while (strcmp(inimigo->nome, "Slime") != 0);
		fscanf(monstros,"%d", &inimigo->vida);
		fscanf(monstros,"%d", &inimigo->dano);

		gotoxy(10,25);
		mostraSlime();
	}
}

void pegaInformacao (personagem *info, item *equipamento) {
	FILE *pers = NULL, *itens = NULL;
	int d;
	char procura[30];

	pers = fopen("personagem.txt", "r");

	fscanf(pers,"%d", &d);
	fscanf(pers,"%s%s", info->nome, info->classe);
	fscanf(pers,"%s");
	fscanf(pers,"%d%d", &info->vida, &info->dano);
	fscanf(pers,"%s%d", info->nh1, &info->h1);
	fscanf(pers,"%s%d", info->nh2, &info->h2);
	fscanf(pers,"%s%d", info->nh3, &info->h3);

	fclose(pers);

	itens = fopen("itens.txt", "r");

	do {
		fscanf(itens,"%s", procura);

	} while (strcmp(procura, "PotVida") != 0);

	fscanf(itens,"%d", &equipamento->probItem);

	fclose(itens);

}
