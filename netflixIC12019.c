#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>


struct movies_netflix {
	char title[100];
    char rating[100];
    char ratingLevel[300];
    char ratingDescription[300];
    int releaseYear;
    int userRatingScore;
    int userRatingSize;
};

typedef struct movies_netflix Movies;

void filmesporano(Movies *movie){

	int ano;
	int j = 0;
	int i;
			
	printf("\nDigite o ano (entre 1940 e 2017): ");
	scanf("%d", &ano);
	
	if (ano < 1940 || ano > 2017)
		printf("Invalido\n");
	else{
	
	for (i=0; i<1001; i++){
		if (movie[i].releaseYear == ano)
				j++;
 }
	printf("\nNo catalogo, ha %d filmes lancados em %d", j, ano);
 }	
}

void cabecalho (Movies *movie) {

	printf("FILMES DA NETFLIX\n");
}

void leitura (Movies *movie) {

	int i;

	printf("\nN - Title - Rating - RatingLevel - RatingDescription - ReleaseYear - UserRatingScore - UserRatingSize \n");
	for (i=0; i<1001; i++)
				
				printf("\n %d - %s - %s - %s - %s - %d - %d - %d", i, movie[i].title, movie[i].rating, movie[i].ratingLevel, movie[i].ratingDescription, movie[i].releaseYear, movie[i].userRatingScore, movie[i].userRatingSize);
				printf("\n");

}

void armazenamento(Movies *movie){

	char linha[400]; 
	int i = 0; //
	char *tok;
	char *result;
	
	FILE *netflix;
	netflix = fopen ("netflix_all.csv", "r");
	
		if (netflix == NULL) {
		printf("Erro de abertura.\n");
		exit(0);			
		}
		
		while (!feof(netflix)) {
			result = fgets(linha, 400, netflix);
			if (result) {
			tok = strtok(linha,";");
			strcpy(movie[i].title, tok);
			tok = strtok(NULL,";");
			strcpy(movie[i].rating, tok);
			tok = strtok(NULL,";");
			strcpy(movie[i].ratingLevel, tok);
			tok = strtok(NULL,";");
			strcpy(movie[i].ratingDescription, tok);
			
			tok = strtok(NULL,";");
			if (strcmp(tok, "NA") == 0) {
				movie[i].releaseYear = 0; 
				} else {
				movie[i].releaseYear = atoi(tok);
			}
			tok = strtok(NULL,";");
			if (strcmp(tok,"NA") == 0){
				movie[i].userRatingScore = 0;
				} else {
				movie[i].userRatingScore = atoi(tok);
			}
			tok = strtok(NULL,";");
			if (strcmp(tok,"NA") == 0){
				movie[i].userRatingSize = 0;
				} else {
				movie[i].userRatingSize = atoi(tok);
			}														
			i++; }
			else {				
			}
		}
		fclose(netflix);
}
	
void calculapercentual(Movies *movie){
	
	int i;
	float result1;
	float result2;
	float result3;
	int violencecont = 0;
	int sexualcontentcont = 0;
	int violentcont = 0;	
	float conversao1;
	float conversao2;
	float conversao3;

	for (i=0; i<1001; i++){
				if (strstr(movie[i].ratingLevel, "violence")){
				violencecont++;
				} else {
			}
		}
		for (i=0; i<1001; i++){
				if (strstr(movie[i].ratingLevel, "sexual content")){
				sexualcontentcont++;
				} else {
			}
		}
		
	for (i=0; i<1001; i++){
				if (strstr(movie[i].ratingLevel, "violent")){
				violentcont++;
				} else {
			}
		}

	conversao1 = (float)violencecont;
	conversao2 = (float)sexualcontentcont;
	conversao3 = (float)violentcont;
	result1 = (conversao1 / 10); 
	result2 = (conversao2 / 10);
	result3 = (conversao3 / 10);

	printf("\n");
	printf("Dentre 1000 entradas: \n");
	printf("O numero de ocorrencias 'violence' eh %d e o percentual eh de %.1f%%\n", violencecont, result1);
	printf("O numero de ocorrencias 'sexual content' eh %d e o percentual eh de %.1f%%\n", sexualcontentcont, result2);
	printf("O numero de ocorrencias 'violent' eh %d e o percentual eh de %.1f%%", violentcont, result3);
	printf("\n");

}

void procura(Movies *movie){

	int i;
	char filme[100];
	int cont = 1;
	
	printf("Obs: Recomenda-se o primeiro caractere maiusculo, devido ao case-sensitive. \n");
	printf("-------------------------");
	printf("\nEntre com o nome do filme: ");
	scanf("%s^\n", &filme);
	
	for (i=0; i<1001; i++){
		if (strstr(movie[i].title, filme) != NULL){
				printf("\n%d - Nome: %s", cont, movie[i].title);
				printf("\nFaixa etaria (numerica): %s", movie[i].ratingDescription);
				printf("\nDescricao sobre a faixa: %s", movie[i].ratingLevel);
				printf("\n");
		cont++;
			}			
		}		
	} 


int main (void){ 
	char filme[100];
	Movies movie[1001];
	armazenamento(movie);
	cabecalho(movie);
	int i;
	int menu;
		 do{   
				printf("\n1 - Leitura completa do arquivo");
				printf("\n2 - Estatistica: termos 'violence', 'sexual content' e 'violent'");
				printf("\n3 - Pesquisa de filmes");
				printf("\n4 - Numero de videos por ano");
				printf("\nEscolha uma opcao do menu: ");
				scanf("%d", &menu);

		switch(menu){
				case 1:
					leitura(movie);
				break;

				case 2:
					calculapercentual(movie);
				break;

				case 3:
					procura(movie);
				break;

				case 4:
					filmesporano(movie);
				break;
				
				case 0:
					return(0);
					break;

				default:
					printf("Opcao invalida!\n");
						}
			}while(1);
return(0);			
}
