#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>

using namespace std;



struct Fruta{
	char nome[15];
	float preco;
	char cor[15];
};

void ler(FILE *arquivo, string nomeDoArquivo){
    int registro;
    Fruta fruta;
    string enter;

    //convert nomeDoArquivo to const char* with the function c_str()
    arquivo = fopen(nomeDoArquivo.c_str(),"r+");

    if(arquivo == NULL){
        cout << "O arquivo nao existe." << endl;
    }
    else{
        cout << "Digite o numero do registro que deseja ler: " << endl;

        cin >> registro;

        //consume the \n
        getline(cin,enter);

        //move the pointer to the position required
        //registro - 1 because it begins from position 0
        fseek(arquivo,(registro-1)*sizeof(Fruta),SEEK_SET);

        fread(&fruta,sizeof(Fruta),1,arquivo);

        //user puts a number that not correspond to the size of file
        if(fruta.preco == 0){
            cout << "Registro invalido." << endl;
        }

        cout << "Nome: " << fruta.nome << endl;
        cout << "Preco: " << fruta.preco << endl;
        cout << "Cor: " << fruta.cor << endl;


        fclose(arquivo);
    }
}

void escrever(FILE *arquivo, string nomeDoArquivo){
            string name = "", color = "";
            string enter;
            double price;
            int quantidade, comando,registro;

            cout << "Quantas frutas deseja adicionar?" << endl;

            cin >> quantidade;

                        //consume the \n
            getline(cin,enter);

            Fruta fruta[quantidade];

            //remove trashes of the char[]
            for(int i = 0;i < quantidade; i++){
                for(int j = 0; j < 15; j++){
                    fruta[i].nome[j] = ' ';
                    fruta[i].cor[j] = ' ';
                }
            }

            //it could be a substitution of an register
            if(quantidade == 1){
                cout << "1 - Editar um registro" << endl;
                cout << "2 - Criar um novo registro" << endl;

                cin >> comando;
                getline(cin,enter);

                if(comando == 1){
                    arquivo = fopen(nomeDoArquivo.c_str(),"w+");

                    cout << "Digite o numero do registro que deseja editar" << endl;

                    cin >> registro;
                    getline(cin,enter);

                    fseek(arquivo,(registro-1)*sizeof(Fruta),SEEK_SET);

                    cout << "Digite o nome da fruta:" << endl;

                    getline(cin,name);

                    //pass the string name to char[] fruta.nome
                    for(int j = 0;j < name.size(); j++){
                        fruta[0].nome[j] = name[j];
                    }

                    cout << "Digite o preco da fruta:" << endl;

                    cin >> price;

                    //consume the \n
                    getline(cin,enter);

                    fruta[0].preco = price;

                    cout << "Digite a cor da fruta:" << endl;

                    getline(cin,color);

                    //pass the string color to char[] fruta.cor
                    for(int j = 0;j < color.size(); j++){
                        fruta[0].cor[j] = color[j];
                    }

                    fwrite(fruta,sizeof(Fruta),1,arquivo);
                }
                else if(comando == 2){

                    //a+ goes to the end of file
                    arquivo = fopen(nomeDoArquivo.c_str(),"a+");

                    cout << "Digite o nome da fruta:" << endl;

                    getline(cin,name);

                    //pass the string name to char[] fruta.nome
                    for(int j = 0;j < name.size(); j++){
                        fruta[0].nome[j] = name[j];
                    }

                    cout << "Digite o preco da fruta:" << endl;

                    cin >> price;

                    //consume the \n
                    getline(cin,enter);

                    fruta[0].preco = price;

                    cout << "Digite a cor da fruta:" << endl;

                    getline(cin,color);

                    //pass the string color to char[] fruta.cor
                    for(int j = 0;j < color.size(); j++){
                        fruta[0].cor[j] = color[j];
                    }

                    fwrite(fruta,sizeof(Fruta),1,arquivo);
                }
                else{
                    cout << "comando invalido" << endl;
                }
            }

            // quantidade > 1
            else{

                //a+ goes to the end of file
                arquivo = fopen(nomeDoArquivo.c_str(),"a+");

                 for(int i = 0;i < quantidade; i++){
                    cout << "Digite o nome da fruta:" << endl;

                    getline(cin,name);

                    //pass the string name to char[] fruta.nome
                    for(int j = 0;j < name.size(); j++){
                        fruta[i].nome[j] = name[j];
                    }

                    cout << "Digite o preco da fruta:" << endl;

                    cin >> price;

                    //consume the \n
                    getline(cin,enter);

                    fruta[i].preco = price;

                    cout << "Digite a cor da fruta:" << endl;

                    getline(cin,color);

                    //pass the string color to char[] fruta.cor
                    for(int j = 0;j < color.size(); j++){
                        fruta[i].cor[j] = color[j];
                    }

                }

                fwrite(fruta,sizeof(Fruta),quantidade,arquivo);
            }

            fclose(arquivo);
}


int main() {
    FILE *arquivo;
    int comando;
    string nomeDoArquivo, enter;

    cout << "Digite o nome do arquivo a ser manipulado" << endl;

    getline(cin,nomeDoArquivo);

    cout << "Comandos:" << endl;
    cout << "1 - ler conteudo do arquivo" << endl;
    cout << "2 - escrever conteudo no arquivo" << endl;
    cout << "3 - mudar para outro arquivo" << endl;
    cout << "4 - fechar o programa" << endl;

    while(cin >> comando, comando != 4){

        //consume the \n
        getline(cin,enter);

        if(comando == 1){
                ler(arquivo,nomeDoArquivo);
        }

        else if(comando == 2){
                escrever(arquivo,nomeDoArquivo);

        }

        else if(comando == 3){
                cout << "Digite o nome do arquivo a ser manipulado" << endl;

                getline(cin,nomeDoArquivo);
        }

        //invalid command
        else{
            cout << "comando invalido" << endl;
        }

        cout << "Comandos:" << endl;
        cout << "1 - ler conteudo do arquivo" << endl;
        cout << "2 - escrever conteudo no arquivo" << endl;
        cout << "3 - mudar para outro arquivo" << endl;
        cout << "4 - fechar o programa" << endl;
    }
}
