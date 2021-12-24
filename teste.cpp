#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



using namespace std;
using namespace std::chrono;

struct Registro
{
    char id[100]; 
    char review[1000];
    char upvotes[10];
    char version[20];
    char data[20];
};

int ehNum(char c)
{
    //retorna '1' se for caractere

    if (c == '0' || c == '1' || c == '2' || c == '3' || c == '4' || c == '5' || c == '6' || c == '7' || c == '8' || c == '9')
        return 1;
    else
        return 0;
}

// Funcao que remove virgulas do campo review_id quando começa com aspas
string removeVirgula(string str, int pos)
{
    // Quando o review_text contem virgulas, o campo comeca com aspas.
    // Desta forma, sempre que comecar com aspas vou retirar as virgulas de dentro do campo

    int asp = 0; // contador de aspas duplas

    // i comeca no 90, assim nao perde tempo percorrendo o review_id
    for (int i = 90; str[i] != '\0'; i++)
    {
        if (str[i] == '\"')
        {
            if (str[i] == ',')
                str[i] = ' ';
        }
        else if (str[i] == '\"')
            break;
    }

    /* for (int i = pos; str[i] != '\0';i++){
        str[i] = str[i+1];
    } */

    return str;
}

string removeQuebraLinha(string str)
{
    // Funcao que localiza e, se houver, remove carriage return e quebra de linha

    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] == '\r' && str[i + 1] == '\n')
        {
            str[i] = ' ';
            str[i + 1] = ' ';
        }
        else if (str[i] == '\n')
            str[i] = ' ';
    }

    return str;
}

void tratamento(string str, int pos){
    /* cout << str;
    int i=str.length() +1,tam=0,posi = pos;
    string aux;
    while(str[posi] != '\0'){
        aux[tam] = str[posi];
        tam++;
        posi++;
    }
    tam = 0;
    posi = pos;
    while(aux[tam] != '\0'){
        str[pos+1] = aux[tam];
    }
    str[pos] = '0';
    cout << str; */
}

void leArquivoCsv()
{

    ifstream inFile;
    inFile.open("reduzido.csv");

    if (!inFile.is_open())
        cout << "Não foi possível abrir o arquivo" << endl;

    ofstream arq1; // ponteiro do arquivo de review_id
    ofstream arq2; // ponteiro do arquivo de review_text
    ofstream arq3; // ponteiro do arquivo de upvotes
    ofstream arq4; // ponteiro do arquivo de app_version
    ofstream arq5; // ponteiro do arquivo de posted_date
    ofstream tiktok;

    arq1.open("review_id.bin", ios::out);
    arq2.open("review_text.bin", ios::out);
    arq3.open("upvotes.bin", ios::out);
    arq4.open("app_version.bin", ios::out);
    arq5.open("posted_date.bin", ios::out);
    tiktok.open("tiktok_app_reviews.bin", ios::out);

    string str;           // string que fará a leitura linha por linha do aquivo tiktok_app_reviews
    getline(inFile, str); // retirando o cabecalho do arquivo csv
    
    getline(inFile, str);

    while (!inFile.eof()){

        int cont;
        int tam = 0;

    // Armazenando o review_id do csv em um arquivo próprio:
        for (cont = 0; str[cont] != ','; cont++);

        for (int i = 0; i < cont; i++){
            arq1 << str[i];
            tiktok << str[i];
        }
            
        arq1 << endl;

        cont++;
        tam = cont;

    // Armazenando o review_text do csv em um arquivo próprio:
        while (true)
        {
            if(str[cont] == '\n'){
                cout << "Houve quebra de linha";
                str[cont] == ' ';
            }
            if (str[cont] == ',' && (ehNum(str[cont + 1]) == 1) && (ehNum(str[cont + 2]) == 1 || str[cont + 2] == ',') && (ehNum(str[cont + 3]) == 1 || str[cont + 3] == ',') && (ehNum(str[cont + 4]) == 1 || str[cont + 4] == ',') && ehNum(str[cont-1]) == 0){
                    break;
            }
                
            cont++;
        }

        for (int i = tam; i < cont; i++){
            arq2 << str[i];
            tiktok << str[i];    
        }
        arq2 << endl;

        

    // Armazenando upvotes do csv em um arquivo próprio:
        if(str[cont+1] == ','){
            tratamento(str,cont);
            str[cont] = '0';
        } 
        
        cont++;
        tam = cont;

        for (; str[cont] != ','; cont++);

        for (int i = tam; i < cont; i++){
            arq3 << str[i];
            tiktok<<str[i];
        }
        
        arq3 << endl;
        cont++;
        tam = cont;

    // Armazenando app_version do csv em um arquivo próprio:
        if(str[cont+1] == ','){
            tratamento(str,cont);
            str[cont] = '0';
        } 
        
        cont++;
        tam = cont;
        for (; str[cont] != ','; cont++);     

        for (int i = tam; i < cont; i++){
            arq4 << str[i];
            tiktok << str[i];
        }
        arq4 << endl;

        cont++;
        tam = cont;

    // Armazenando app_version do csv em um arquivo próprio:
        if(str[cont+1] == ','){
            tratamento(str,cont);
            str[cont] = '0';
        } 
        
        cont++;
        tam = cont;
        for (; str[cont] != '\0'; cont++);
        
        for (int i = tam; i < cont; i++){
            arq5 << str[i];
            tiktok << str[i];
        }
        arq5 << endl;
        
        tiktok << endl;
        getline(inFile, str);
    }
}

int numLinhas(ifstream &inFile){

    int lin = 0; // número de linhas do arquivo de entrada

    string str;

    while (! inFile.eof())
    {
        getline (inFile, str);
        lin++;
    }

    return lin -1;
}

void acessaRegistro(int i,int opc,ofstream &outFile)
{
    ifstream inFile;
    inFile.open("tiktok_app_reviews.bin", ios::app);

    if(!inFile.is_open()){
        cout << "Não foi possível abrir o arquivo!";
    }
    else{
        string linha;
        int j =0;
        while(j < i){
            if(inFile.eof())
                break;
            getline(inFile,linha);
            if(j+1 == i){
                if(opc == 1)
                    cout << linha <<endl;
                if(opc == 2)
                    outFile << linha <<endl;
            }
            j++;
        }

        inFile.close();
    }
    

}

void testeImportacao()
{
    int num = 0;

    leArquivoCsv();

    ifstream inFile;
    inFile.open("reduzido.csv");
    ofstream outFile("Importacao.txt",ios::out);

    int lin = numLinhas(inFile);

    do
    {
        cout << "Menu do teste de importacao:" << endl;
        cout << "Digite 1 - Para exibir a saida no console" << endl;
        cout << "Digite 2 - Para exibir a saida em um arquivo .txt" << endl;
        cout << "digite 3 - Para finalizar o programa" << endl;

        cin >> num;

        if (num == 1){
            // saida no console, n = 10

            int n; // contador do numero de registros
            string str; // string que vai armazenar a linha do arquivo

            int num;

            for(n = 0; n < 10; n++)
            {
                //num = rand()%lin;
                acessaRegistro(rand()%lin,1,outFile);
                // ainda não consegui fazer a impressao correta, algum erro ainda não identificado
                // a funcao acessaRegistro imprime a linha, no entanto, nao esta imprimindo.
            }


        }
        else if (num == 2){
            // saida no arquivo, n = 100


            int n; // contador do numero de registros

            for(n = 0; n < 100; n++)
                acessaRegistro(rand()%lin,2,outFile);
                //mesmo erro acima
            

            cout << "Arquivo gerado com sucesso!" << endl;
            break;


        }
        else{
            cout << "Valor invalido, por favor, digite novamente." << endl;
            cout << "############################################" << endl << endl;
        }

    }while(num != 3);


}

template <typename T>
void troca(T &a, T &b)
{
    T aux = a;
    a = b;
    b = aux;
}

int pivoAleatorio(int *v, int ini, int fim)
{
    int pos = ini + rand() % (fim - ini + 1);
    troca(v[pos], v[fim]);
    return v[fim];
}

template <typename T>
T medianaDeTres(T *v, int ini, int fim)
{
    int meio = (ini + fim) / 2;
    if (v[ini] > v[fim])
        troca(v[ini], v[fim]);
    if (v[meio] > v[fim])
        troca(v[meio], v[fim]);
    if (v[ini] > v[meio])
        troca(v[ini], v[meio]);
    troca(v[meio], v[fim]);
    return v[fim];
}

template <typename T>
int particiona(T *v, int ini, int fim)
{
    //T pivo = v[fim];
    //int pivo = pivoAleatorio(v, ini, fim);
    T pivo = medianaDeTres(v, ini, fim);

    int i = ini, j = fim - 1;
    while (true)
    {
        while (i < fim && v[i] < pivo)
            i++;
        while (j >= ini && v[j] > pivo)
            j--;
        if (i < j)
        {
            troca(v[i], v[j]);
            i++;
            j--;
        }
        else
            break;
    }
    troca(v[i], v[fim]);
    return i;
}

template <typename T>
void QuickSortRec(T *v, int ini, int fim)
{
    if (ini < fim)
    {
        int p = particiona(v, ini, fim);
        QuickSortRec(v, ini, p - 1);
        QuickSortRec(v, p + 1, fim);
        return;
    }
}

template <typename T>
void QuickSort(T *v, int n)
{
    high_resolution_clock::time_point inicio = high_resolution_clock::now();
    QuickSortRec(v, 0, n - 1);
    cout << "Tempo Quick Sort: ";
    high_resolution_clock::time_point fim = high_resolution_clock::now();
    cout << duration_cast<duration<double>>(fim - inicio).count() << " segundos" << endl;
}

template <typename T>
void Heapify(T *v, int i, int n)
{
    while (i < n)
    {
        int filho = 2 * i + 1;
        if (filho < n)
        {
            if (filho + 1 < n && v[filho + 1] > v[filho])
                filho++;
            if (v[filho] > v[i])
                troca(v[i], v[filho]);
        }
        i = filho;
    }
}

template <typename T>
void constroiHeap(T *v, int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
        Heapify(v, i, n);
}

template <typename T>
void HeapSortRec(T *v, int n)
{
    constroiHeap(v, n);
    while (n > 0)
    {
        troca(v[0], v[n - 1]);
        Heapify(v, 0, n - 1);
        n--;
    }
}

template <typename T>
void HeapSort(T *v, int n)
{
    high_resolution_clock::time_point inicio = high_resolution_clock::now();
    HeapSortRec(v, n);
    cout << "Tempo Heap Sort: ";
    high_resolution_clock::time_point fim = high_resolution_clock::now();
    cout << duration_cast<duration<double>>(fim - inicio).count() << " segundos" << endl;
}

int getProxGap(int gap)
{
    gap = (gap * 10) / 13;
    if (gap < 1)
        return 1;
    return gap;
}

template <typename T>
void CombSort(T *vet, int n)
{
    high_resolution_clock::time_point inicio = high_resolution_clock::now();
    int gap = n;
    bool troca = true;
    while (gap != 1 || troca == true)
    {
        gap = getProxGap(gap);
        troca = false;
        for (int i = 0; i < n - gap; i++)
        {
            if (vet[i] > vet[i + gap])
            {
                swap(vet[i], vet[i + gap]);
                troca = true;
            }
        }
    }
    cout << "Tempo Comb Sort: ";
    high_resolution_clock::time_point fim = high_resolution_clock::now();
    cout << duration_cast<duration<double>>(fim - inicio).count() << " segundos" << endl;
}

void PegaLinha(int *v,int i){
    ifstream inFile("upvotes.bin");
    int numaleatorio = rand()%numLinhas(inFile);
    string linha;
    int j =0;
    //cout << "!inFile.eof() = " << boolalpha << !inFile.eof();
    //cout << "Numaleatorio = " << numaleatorio;
    while(true){
        //cout << "j+1 = " << j+1;
        getline(inFile,linha);
        if(j+1 == numaleatorio){
            cout << "Linha: " << linha;
            v[i] = atoi(linha.c_str());
            break;
        }
        j++;
    }
}

void menuPrincipal()
{
    /* O programa deve oferecer ao usuário um menu para permitir a escolha de qual etapa será executada:
        Ordenação
        Hash
        Módulo de Teste
         */

    int op;

    cout << "Digite uma opcao para continuar: " << endl;
    cout << "1 - Ordenação" << endl;
    cout << "2 - Hash" << endl;
    cout << "3 - Módulo teste" << endl;
    cout << "Digite: ";

    cin >> op;

    switch (op){
    case 1:
    {
        int M = 0;
        while(M<3){
            //Utilizando N = 5.000
            int N = 5000;
            int *vetQ = new int[N];
            int *vetH = new int[N];
            int *vetC = new int[N];

            for(int i = 0; i < N; i++){
                //PegaLinha(vet,i);
                vetQ[i] = rand() % 300;
                vetH[i] = vetQ[i];
                vetC[i] = vetQ[i];
            }

            
            /* cout <<endl<< "Vetor de upvotes: "<<endl;
            for(int i = 0; i< N; i++)
                cout << vetQ[i] << " "; */
            cout << endl;
            cout <<endl<< "Ordenação por Quick Sort"<<endl;
            QuickSort(vetQ,N);

            /* cout << "Vetor de upvotes ordenado com Quick Sort: "<<endl;
            for(int i = 0; i< N; i++)
                cout << vetQ[i] << " "; */

            cout <<endl<< "Ordenação por Heap Sort"<<endl;
            HeapSort(vetH,N);
            
            /* cout << "Vetor de upvotes ordenado com Heap Sort: "<<endl;
            for(int i = 0; i< N; i++)
                cout << vetH[i] << " "; */

            cout <<endl << "Ordenação por Comb Sort"<<endl;
            CombSort(vetC,N);

            /* cout << "Vetor de upvotes ordenado com Comb Sort: "<<endl;
            for(int i = 0; i< N; i++)
                cout << vetC[i] << " "; */

            M++;
        }
        
        menuPrincipal();
        break;
    };
    case 2:
    {
        
        menuPrincipal();
        break;
    };

    case 3:
    {
        /* O módulo de teste deve permitir a realização de algumas operações para garantir que as funções básicas do programa entregam resultados corretos sob quantidades menores de registros. 
        Esse módulo deve conter funções para escrever as saídas em um arquivo teste.txt das seguintes operações:
        O resultado de cada um dos algoritmos de ordenação.
        O resultado das versões do app mais frequentes
        Para estes testes, considere a ordenação de N=100 reviews aleatórios. */
        menuPrincipal();
        break;
    }

    default:
        break;
    }
}

int main()
{
    srand((unsigned)time(NULL));
    high_resolution_clock::time_point inicio = high_resolution_clock::now();

    /* ifstream inFile("tiktok_app_reviews.csv");
    ofstream outFile("reduzido.csv");

    int bufSize = 10000000;
    char *buffer = new char[bufSize];

    inFile.read(buffer,bufSize);
    outFile.write(buffer,bufSize);

    delete [] buffer; */


    //ifstream csv("tiktok_app_reviews.csv");
    ifstream csv("reduzido.csv");
    //ofstream bin("tiktok_app_reviews.bin");
    ofstream bin("reduzido.bin",ios::out);
    //leArquivoCsv();
    //testeImportacao();
    menuPrincipal();  
        
    bin.close();
    csv.close();

    //ifstream inBin("tiktok_app_reviews.bin");
    ifstream inBin("reduzido.bin");
    inBin.close();
    
    high_resolution_clock::time_point fim = high_resolution_clock::now();
    cout << duration_cast<duration<double>>(fim - inicio).count() << " segundos" << endl;

    return 0;
}
