#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <math.h>

using namespace std;



void ler(FILE *arquivo, string nomeDoArquivo){
    int registro;
    int number;
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
        fseek(arquivo,(registro-1)*sizeof(int),SEEK_SET);

        fread(&number,sizeof(int),1,arquivo);

        cout << "Numero: " << number << endl;


        fclose(arquivo);
    }
}

int escrever(FILE *arquivo, string nomeDoArquivo){

            string enter;
            int number;
            int quantidade, comando,registro;

            cout << "Quantos numeros deseja adicionar?" << endl;

            cin >> quantidade;

            //consume the \n
            getline(cin,enter);

            int v[quantidade];

            //a+ goes to the end of file
            arquivo = fopen(nomeDoArquivo.c_str(),"a+");

            for(int i = 0;i < quantidade; i++){
                cout << "Digite um numero inteiro maior que 0:" << endl;

                cin >> v[i];

            }

            fwrite(v,sizeof(int),quantidade,arquivo);

            fclose(arquivo);

            return quantidade;

}

int sequencialSearch(FILE *arquivo, string nomeDoArquivo, int searchNumber){

    int v,index = 1;

    //convert nomeDoArquivo to const char* with the function c_str()
    arquivo = fopen(nomeDoArquivo.c_str(),"r+");

    if(arquivo == NULL)
        return -2;

    while(fread(&v,sizeof(int),1,arquivo) != 0){

        if(v == searchNumber){
            return (index-1);
        }

        index++;
    }

    return -1;
}

int binarySearch(FILE *arquivo, string nomeDoArquivo, int x, int quantidade){
    int i = 0, f = quantidade - 1,searchNumber;
    double m1,m;

    arquivo = fopen(nomeDoArquivo.c_str(),"r+");

    if(arquivo == NULL)
        return -2;

    while(i <= f){
        m1 = (i+f)/2;
        m = ceil(m1);

        fseek(arquivo,m*sizeof(int),SEEK_SET);

        fread(&searchNumber,sizeof(int),1,arquivo);

        if(searchNumber == x)
            return m;

        else if(x < searchNumber)
            f = m - 1;

        else
            i = m + 1;
    }

    fclose(arquivo);

    return -1;
}

int countQuantity(FILE *arquivo, string nomeDoArquivo){
    int quantidade = 0,v;

    //convert nomeDoArquivo to const char* with the function c_str()
    arquivo = fopen(nomeDoArquivo.c_str(),"r+");

    if(arquivo == NULL)
        return -1;

    while(fread(&v,sizeof(int),1,arquivo) != 0){
        quantidade++;
    }

    fclose(arquivo);

    return quantidade;
}

int main() {
    FILE *arquivo;
    int comando,quantidade;
    string nomeDoArquivo, enter;

    cout << "Digite o nome do arquivo a ser manipulado" << endl;

    getline(cin,nomeDoArquivo);

    cout << "Comandos:" << endl;
    cout << "1 - ler conteudo do arquivo" << endl;
    cout << "2 - escrever conteudo no arquivo" << endl;
    cout << "3 - mudar para outro arquivo" << endl;
    cout << "4 - fechar o programa" << endl;
    cout << "5 - realizar busca no arquivo" << endl;

    while(cin >> comando, comando != 4){

        //consume the \n
        getline(cin,enter);

        if(comando == 1){
                ler(arquivo,nomeDoArquivo);
        }

        else if(comando == 2){
                quantidade = escrever(arquivo,nomeDoArquivo);

        }

        else if(comando == 3){
                cout << "Digite o nome do arquivo a ser manipulado" << endl;

                getline(cin,nomeDoArquivo);
        }

        //search
        else if(comando == 5){
            int tipo,searchNumber, result;

            cout << "Digite o tipo de busca que deseja realizar (ao escolher 2, os elementos contidos no arquivos devem estar organizados em ordem crescente): " << endl;
            cout << "1 - Busca sequencial" << endl;
            cout << "2 - Busca Binaria" << endl;

            cin >> tipo;

            cout << "Digite o numero que deseja buscar no arquivo: " << endl;

            cin >> searchNumber;

            //sequencial search
            if(tipo == 1){

                result = sequencialSearch(arquivo,nomeDoArquivo,searchNumber);

                //arquivo == NULL
                if(result == -2)
                    cout << "erro na leitura do arquivo" << endl;

                //the number is not in the array
                else if(result == -1)
                    cout << "O numero " << searchNumber << " nao esta contido no arquivo" << endl;

                //the number is in the array
                else
                    cout << "O numero " << searchNumber << " esta contido no arquivo, e se encontra no indice " << result << endl;
            }

            //binary search
            else if(tipo == 2){
                quantidade = countQuantity(arquivo,nomeDoArquivo);

                result = binarySearch(arquivo,nomeDoArquivo,searchNumber,quantidade);

                if(result == -2)
                    cout << "erro na leitura do arquivo" << endl;

                //the number is not in the array
                else if(result == -1)
                    cout << "O numero " << searchNumber << " nao esta contido no arquivo" << endl;

                //the number is in the array
                else
                    cout << "O numero " << searchNumber << " esta contido no arquivo, e se encontra no indice " << result << endl;

            }
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
        cout << "5 - realizar busca no arquivo" << endl;
    }
}
