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
    int f = floor(c/m);

    if(c < m || f%m == 0){
        return 1;
    }
    return f%m;
}

int doubleHashingInsertion(FILE *arquivo, string nomeDoArquivo){

            int number,quantidade, index, deslocamento;

            cout << "Quantos numeros deseja adicionar?" << endl;

            cin >> quantidade;

            int v[quantidade];

            for(int i = 0;i < quantidade; i++){
                v[i] = 0;
            }

            //a+ goes to the end of file
            arquivo = fopen(nomeDoArquivo.c_str(),"a+");

            for(int i = 0;i < quantidade; i++){
                cout << "Digite um numero inteiro maior que 0:" << endl;

                cin >> number;

                if(v[h1(number,quantidade)] == 0)
                    v[h1(number,quantidade)] = number;

                else{

                    index = h1(number,quantidade);
                    deslocamento = h2(number,quantidade);


                    if(index + deslocamento >= quantidade)
                        index+=deslocamento - quantidade;

                    else
                        index+=deslocamento;


                    while(v[index] != 0){

                        if(index + deslocamento >= quantidade){
                            index += deslocamento - quantidade;
                            continue;
                        }
                        index+=deslocamento;
                    }

                    v[index] = number;
                }

            }

            for(int i = 0;i < quantidade; i++){
                cout << v[i] << " ";
            }
            cout << endl;

            fwrite(v,sizeof(int),quantidade,arquivo);

            fclose(arquivo);

            return quantidade;
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

bool doubleHashingQuery(FILE *arquivo, string nomeDoArquivo){
    int searchNumber,index,read,element,quantidade,deslocamento;

    quantidade = countQuantity(arquivo,nomeDoArquivo);

    cout << "Digite o elemento que deseja consultar" << endl;

    cin >> element;

    arquivo = fopen(nomeDoArquivo.c_str(),"r+");

    if(arquivo == NULL){
        cout << "erro na leitura do arquivo" << endl;
        return false;
    }

        index = h1(element,quantidade);
        deslocamento = h2(element,quantidade);

        fseek(arquivo,h1(element,quantidade)*sizeof(int),SEEK_SET);

        fread(&searchNumber,sizeof(int),1,arquivo);

        if(searchNumber == element){
            cout << "O elemento " << element << " esta contido no vetor, no indice " <<  index << endl;
            return true;
        }
        if(index + deslocamento >= quantidade)
            index+=deslocamento - quantidade;

        else
            index+=deslocamento;


        fseek(arquivo,index*sizeof(int),SEEK_SET);

        fread(&searchNumber,sizeof(int),1,arquivo);

        while( index != h1(element,quantidade)){
            if(searchNumber != element){
                    if(index + deslocamento >= quantidade){
                        index+=deslocamento - quantidade;
                        fseek(arquivo,index*sizeof(int),SEEK_SET);
                        fread(&searchNumber,sizeof(int),1,arquivo);
                        continue;
                    }

                    index+=deslocamento;
                    fseek(arquivo,index*sizeof(int),SEEK_SET);
                    fread(&searchNumber,sizeof(int),1,arquivo);
                    continue;
            }

            cout << "O elemento " << element << " esta contido no vetor, no indice " <<  index << endl;
            return true;
        }

        cout << "O elemento " << element << " nao esta contido no vetor" << endl;

        fclose(arquivo);

        return false;
}


int main(){

    FILE *arquivo;
    int comando,quantidade, element,result;
    string nomeDoArquivo, enter;

    cout << "Digite o nome do arquivo a ser manipulado" << endl;

    getline(cin,nomeDoArquivo);

    cout << "comandos: " << endl;
    cout << "1 - Insercao" << endl;
    cout << "2 - Consulta" << endl;
    cout << "4 - Fechar programa" << endl;

    while(cin >> comando, comando != 4){
        switch(comando){
        case 1:
            quantidade = doubleHashingInsertion(arquivo,nomeDoArquivo);
            break;
        case 2:
            doubleHashingQuery(arquivo,nomeDoArquivo);
            break;

        }

        cout << "comandos: " << endl;
        cout << "1 - Insercao" << endl;
        cout << "2 - Consulta" << endl;
        cout << "4 - Fechar programa" << endl;
    }

}
