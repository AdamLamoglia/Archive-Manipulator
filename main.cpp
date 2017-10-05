#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>

using namespace std;



struct Pessoa{
	string nome;
	int idade;
	string cpf;
	float altura;
};

int main() {

	//arquivo que sera manipulado
	FILE *arq;

	//comando para abrir, ler, escrever ou fechar arquivo
	int comando;

	//indice do registro
	int i;

	//contador de registros
	int registros = 0;

	Pessoa p;

	//abre/cria arquivo para manipular dados
	arq = fopen("arquivo.dat","w+");

	if(arq == NULL){
		cout << "Erro na criacao/abertura do arquivo" << endl;
		exit(1);
	}

	cout << "Comandos:" << endl;
	cout << "1 - Leitura de registros do arquivo" << endl;
	cout << "2 - Escrita de registros no arquivo" << endl;
	cout << "3 - Fechar arquivo" << endl;

	cin >> comando;

	//usuario digitou um comando invalido
	if(comando != 1 && comando != 2 && comando != 3){
		cout << "Comando Invalido" << endl;
	}
	else{
		//leitura
		if(comando == 1){
			cout << "Digite a posicao do registro (de 0 a n) que deseja ler" << endl;

			cin >> i;

			//desloca o arquivo para apontar para o registro desejado pelo usuario
			fseek(arq,i*sizeof(Pessoa),SEEK_SET);

			//passa as informacoes contidas em arq para o atributo p
			fread(&p,sizeof(Pessoa),1,arq);

			cout << "Nome: " << p.nome << endl;
			cout << "Idade: " << p.idade << endl;
			cout << "CPF: " << p.cpf << endl;
			cout << "Altura: " << p.altura << endl;
		}
		//escrita
		else if(comando == 2){
			cout << "Digite a posicao do registro (de 0 a n) que deseja escrever" << endl;

			cin >> i;

			if(i >= registros){
				cout << "posicao invalida" << endl;
			}
			else{

			}


		}
		//fechamento
		else{
			fclose(arq);

			exit(1);
		}
	}

}
