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


void linearProbingInsertion(vector<int> &v, FILE *arquivo, string nomeDoArquivo, int quantidade){

        int element,read,count;

        arquivo = fopen(nomeDoArquivo.c_str(),"r+");

        if(arquivo == NULL){
            cout << "erro na execucao do arquivo" << endl;
        }

        else{
            read = fread(&element,sizeof(int),1,arquivo);

            //insertion
            while(read != 0){
                //contains a element on the address
                if(v[h1(element,quantidade)] != 0){
                    count = h1(element,quantidade) + 1;

                    if(count == quantidade)
                        count = 0;

                    //goes to next index
                    while(count != quantidade){
                        if(v[count] != 0){
                            count++;
                            continue;
                        }
                        v[count] = element;
                        break;
                    }
                }

                //the address is free
                else
                    v[h1(element,quantidade)] = element;

                read = fread(&element,sizeof(int),1,arquivo);
            }
        }

        fclose(arquivo);
}

int linearProbingQuery(vector<int> &v,int element){
    int index,originalIndex;

    index = h1(element,v.size());

    if(element == v[index])
        return index;

    originalIndex = index;

    index++;

    while(index != originalIndex){

        if(index == v.size())
            index = 0;
        else{
            if(v[index] != element){
                index++;
                continue;
            }
            return index;
        }

    }

    return -1;
}



int main() {
    FILE *arquivo;
    int comando,quantidade, element;
    string nomeDoArquivo, enter;
    vector<int> v;

    cout << "Digite o nome do arquivo a ser manipulado" << endl;

    getline(cin,nomeDoArquivo);

    cout << "Comandos:" << endl;
    cout << "1 - ler conteudo do arquivo" << endl;
    cout << "2 - escrever conteudo no arquivo" << endl;
    cout << "3 - mudar para outro arquivo" << endl;
    cout << "4 - fechar o programa" << endl;
    cout << "5 - Hashing" << endl;

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

        else if(comando == 5){
            int opcao;

            quantidade = countQuantity(arquivo,nomeDoArquivo);
            v.resize(quantidade);

            cout << "Escolha uma das opcoes:" << endl;
            cout << "1 - Insercao" << endl;
            cout << "2 - Consulta" << endl;

            cin >> opcao;

            if(opcao == 1){
                linearProbingInsertion(v,arquivo,nomeDoArquivo,quantidade);
            }
            else{
                cout << "Digite o elemento que deseja consultar" << endl;

                cin >> element;

                if(linearProbingQuery(v,element) == -1)
                    cout << "O elemento " << element << " nao esta contido no vetor" << endl;
                else
                    cout << "O elemento " << element << " esta contido no vetor, no indice " <<  linearProbingQuery(v,element) << endl;
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
        cout << "5 - Hashing" << endl;
    }
}
