#include <stdio.h>
#include <stdlib.h>

#include "dao_usuario.h"
#include "funcoes.h"

USERLOGIN usuarioLogado;

int gravarUsuario(USER usuario){
	char linha[2000];
	char id[100];

	sprintf(id, "%d", usuario.id);

	FILE *file;
  	file = fopen("arquivos\\usuario.txt", "a");

  	if(file == NULL){
  		printf("N�o foi possivel abrir o arquivo.");
  		return 0;
	}

  	strcpy(linha, id);
  	strcat(linha, "|");
	strcat(linha, usuario.nome);
	strcat(linha, "|");
	strcat(linha, usuario.sobrenome);
	strcat(linha, "|");
	strcat(linha, usuario.CPF);
	strcat(linha, "|");
	strcat(linha, usuario.login);
	strcat(linha, "|");
	strcat(linha, usuario.senha);
	strcat(linha, "|");
	strcat(linha, DateToString(usuario.dt_nascimento));
	strcat(linha, "|");
	strcat(linha, DateToString(usuario.dt_cadastro));
	strcat(linha, "|");
	strcat(linha, floatToString(usuario.salario));
	strcat(linha, "|");
	strcat(linha, usuario.cargo);
	strcat(linha, "|");
	strcat(linha, usuario.endereco);
	strcat(linha, "|");
	strcat(linha, IntToString(usuario.numeroDaCasa));
	strcat(linha, "|");
	strcat(linha, usuario.bairro);
	strcat(linha, "|");
	strcat(linha, usuario.cidade);
	strcat(linha, "|");
	strcat(linha, usuario.estado);
	strcat(linha, "\n");

	fprintf(file, linha);

	return 1;
}

USER procurarUsuarioId(int id){
	char linha[2000];
	char** tokens;
	char convert[100];
	USER usuario;
	usuario.id = 0;

	sprintf(convert, "%d", id);

	FILE *file;
  	file = fopen("arquivos\\usuario.txt", "a+");

  	if(file == NULL){
  		printf("N�o foi possivel abrir o arquivo.");
  		return usuario;
	}

	while(fgets(linha, 2000, file) != NULL){
        tokens = strSplit(linha, '|');
        if (tokens){
            int i;
            if(strcmp(*(tokens), convert) == 0){
                usuario = tokenToUser(tokens);
            }
            free(tokens);
        }
	}
	fclose(file);

    return usuario;
}

USER procurarUsuarioLogin(char* cLogin){
    char linha[2000];
	char** tokens;
	USER usuario;
	usuario.id = 0;

	FILE *file;
  	file = fopen("arquivos\\usuario.txt", "a+");

  	if(file == NULL){
  		printf("N�o foi possivel abrir o arquivo.");
  		return usuario;
	}

	while(fgets(linha, 2000, file) != NULL){
        tokens = strSplit(linha, '|');
        if (tokens){
            int i;
            if(strcmp(*(tokens + 4), cLogin) == 0){
                usuario = tokenToUser(tokens);
            }
            free(tokens);
        }
	}
	fclose(file);

    return usuario;
}

USER tokenToUser(char** tokens){
    USER usuario;

    //int id;
    usuario.id = stringToINT(*(tokens + 0));
    //char nome[150];
    strcpy(usuario.nome, *(tokens + 1));
    //char sobrenome[150];
    strcpy(usuario.sobrenome, *(tokens + 2));
    //char CPF[12];
    strcpy(usuario.CPF, *(tokens + 3));
    //char login[50];
    strcpy(usuario.login, *(tokens + 4));
    //char senha[50];
    strcpy(usuario.senha, *(tokens + 5));
    //DATEC dt_nascimento;
    usuario.dt_nascimento = stringToDate(*(tokens + 6));
    //DATEC dt_cadastro;
    usuario.dt_cadastro = stringToDate(*(tokens + 7));
    //float salario;
    usuario.salario = stringToFloat(*(tokens + 8));
    //char cargo[20];
    strcpy(usuario.cargo, *(tokens + 9));
    //char endereco[150];
    strcpy(usuario.endereco, *(tokens + 10));
    //int numeroDaCasa;
    usuario.numeroDaCasa = *(tokens + 11);
    //char bairro[50];
    strcpy(usuario.bairro, *(tokens + 12));
    //char cidade[50];
    strcpy(usuario.cidade, *(tokens + 13));
    //char estado[50];
    strcpy(usuario.estado, *(tokens + 14));

    return usuario;
}

int retornaUltimoIdUsuario(){
    char linha[2000];
	char** splitLinha;
	char convert[100];
	int id = 0;

	FILE *file;
  	file = fopen("arquivos\\usuario.txt", "a+");

  	if(file == NULL){
  		printf("N�o foi possivel abrir o arquivo.");
  		return 0;
	}

	while(fgets(linha, 2000, file) != NULL){
        splitLinha = strSplit(linha, '|');
        if (splitLinha){
            int i;
            for (i = 0; *(splitLinha + i); i++)            {
                if(i == 0 && (stringToINT(*(splitLinha + i)) > id)){
                    id = stringToINT(*(splitLinha + i));
                }
            }
            free(splitLinha);
        }
	}
	fclose(file);

	return id;
}

USERLOGIN realizarLogin(USERLOGIN login, char* error){
    USER usuario;

    usuario = procurarUsuarioLogin(login.login);

    if(usuario.id != 0 && strcmp(usuario.senha, login.senha) == 0){
        login.idUsuario = usuario.id;
        strcpy(login.nome, usuario.nome);
        strcpy(login.login, usuario.login);
        strcpy(login.senha, "");
        strcpy(login.cargo, usuario.cargo);
        login.logado = true;
    }else{
        strcpy(error, "Usu�rio ou senha inv�lido");
        login.logado = false;
        strcpy(login.senha, "");
    }
    usuarioLogado = login;
    return login;
}

USERLOGIN realizarLogout(){
    usuarioLogado.idUsuario = 0;
    strcpy(usuarioLogado.cargo, "");
    strcpy(usuarioLogado.login, "");
    strcpy(usuarioLogado.nome, "");
    strcpy(usuarioLogado.senha, "");
    usuarioLogado.logado = false;

    return usuarioLogado;
}

USERLOGIN retornaUsuarioLogado(){
    return usuarioLogado;
}