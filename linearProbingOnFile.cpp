#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <math.h>

using namespace std;

int h1(int c, int m){
    return c%m;
}

int h2(int c, int m){
    if(c < m){
        return 1;
    }
    return floor(c/m);
}

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

int linearProbingInsertion(FILE *arquivo, string nomeDoArquivo){

            int number, currentNumber, quantidade, index;

            cout << "Quantos numeros deseja adicionar?" << endl;

            cin >> quantidade;

            arquivo = fopen(nomeDoArquivo.c_str(),"wb");

            for(int i = 0;i < quantidade; i++){

                cout << "Digite um numero inteiro maior que 0:" << endl;

                cin >> number;

                fseek(arquivo,h1(number,quantidade)*sizeof(int),SEEK_SET);

                if(fread(&currentNumber,sizeof(int),1,arquivo) == 0){
                    cout << "entrou" << endl;
                    //fseek(arquivo,0,SEEK_CUR);
                    fwrite(&number,sizeof(int),1,arquivo);

                }

                else{

                    fseek(arquivo,sizeof(int),SEEK_CUR);

                    while(fread(&currentNumber,sizeof(int),1,arquivo) != 0){

                        if(ftell(arquivo) == quantidade*sizeof(int)){
                            fseek(arquivo,0,SEEK_SET);
                            continue;
                        }
                        fseek(arquivo,sizeof(int),SEEK_CUR);

                    }

                    index = ftell(arquivo);

                    cout << index << endl;

                    fseek(arquivo,index,SEEK_SET);
                    fwrite(&number,sizeof(int),1,arquivo);

                }

            }
            //fwrite(&number,sizeof(int),1,arquivo);

            fclose(arquivo);

            arquivo = fopen(nomeDoArquivo.c_str(),"r+");

            for(int i = 0;i < quantidade; i++){

                fseek(arquivo,i*sizeof(int),SEEK_SET);
                fread(&currentNumber,sizeof(int),1,arquivo);
                cout << i << " " << currentNumber << endl;
            }

            fclose(arquivo);

            return quantidade;
}

/*
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
*/

int linearProbingQuery(FILE *arquivo, string nomeDoArquivo, int element,int quantidade){
    int searchNumber,index;

    arquivo = fopen(nomeDoArquivo.c_str(),"r+");

    if(arquivo == NULL){
        return -2;
    }

    index = h1(element,quantidade);

    fseek(arquivo,h1(element,quantidade)*sizeof(int),SEEK_SET);
    fread(&searchNumber,sizeof(int),1,arquivo);

    if(searchNumber == element)
        return index;
    if(index == quantidade - 1)
        index = 0;
    else
        index++;

    fseek(arquivo,index*sizeof(int),SEEK_SET);
    fread(&searchNumber,sizeof(int),1,arquivo);

    while( searchNumber != element){

        if(fread(&searchNumber,sizeof(int),1,arquivo) == 0);
            break;

        if(index == quantidade - 1)
            index = 0;
        else
            index++;
    }

    return index;
}



int main() {
    FILE *arquivo;
    int comando,quantidade, element,result;
    string nomeDoArquivo, enter;

    cout << "Digite o nome do arquivo a ser manipulado" << endl;

    getline(cin,nomeDoArquivo);

    cout << "Comandos:" << endl;
    cout << "1 - ler conteudo do arquivo" << endl;
    cout << "2 - escrever conteudo no arquivo por enderecamento" << endl;
    cout << "3 - mudar para outro arquivo" << endl;
    cout << "4 - fechar o programa" << endl;
    cout << "5 - consulta por hashing" << endl;

    while(cin >> comando, comando != 4){

        //consume the \n
        getline(cin,enter);

        if(comando == 1){
                ler(arquivo,nomeDoArquivo);
        }

        else if(comando == 2){
                quantidade = linearProbingInsertion(arquivo,nomeDoArquivo);

        }

        else if(comando == 3){
                cout << "Digite o nome do arquivo a ser manipulado" << endl;

                getline(cin,nomeDoArquivo);
        }

        else if(comando == 5){

            //quantidade = countQuantity(arquivo,nomeDoArquivo);

            cout << "Digite o elemento que deseja consultar" << endl;

            cin >> element;

            result = linearProbingQuery(arquivo,nomeDoArquivo,element,quantidade);

            if(result == -1)
                cout << "O elemento " << element << " nao esta contido no vetor" << endl;
            else if(result == -2)
                cout << "Erro na leitura do arquivo" << endl;
            else
                cout << "O elemento " << element << " esta contido no vetor, no indice " <<  result << endl;
        }

        //invalid command
        else{
            cout << "comando invalido" << endl;
        }

        cout << "Comandos:" << endl;
        cout << "1 - ler conteudo do arquivo" << endl;
        cout << "2 - escrever conteudo no arquivo por enderecamento" << endl;
        cout << "3 - mudar para outro arquivo" << endl;
        cout << "4 - fechar o programa" << endl;
        cout << "5 - consulta por hashing" << endl;
    }
}
