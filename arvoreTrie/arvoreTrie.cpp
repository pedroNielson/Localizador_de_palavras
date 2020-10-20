#include <iostream>
#include <string> //biblioteca para manejo de strings 
#include <fstream> //biblioteca para manejo de arquivos.txt

using namespace std;

#define TAMANHO 27 //define o tamanho do alfabeto determinado 


struct trieNode //struct q no da arvore 
{    
    trieNode *letra[TAMANHO]; //vetor de letras (com todos os caracteres do alfabeto determinado)
    bool verificaFim;         //vefica o final da palavra, vendo se esse no aponta para o final   
};

trieNode *startNode() //funcao construtora do no
{
    trieNode *node = new trieNode; // cria um novo no da arvore trie 
    node->verificaFim = false;     // atribui falso a verificacao de final da palavra
    for(int i=0; i<TAMANHO; i++)
        node->letra[i] = NULL;     //atribuindo null a todas os ponteiros do vetor letras
    return node;
}

bool Inserir(trieNode *root, string key) //funcao para inserir uma string na arvore
{
    trieNode *atual = root; //criacao de um no auxiliar para insercao
    int x = key.length();  //atribui a x o tamanho da palavra a inserir
    int index;

    
    for (int i = 0; i < x ; i++) //andar por toda a plavra inserida 
    {
        if(key[i] >= 97) //verificando se eh letra minuscula 
           { 
               cout << "O codigo nao aceita letras minusculas, favor utilizar letras maiusculas." << endl;
               return false; 
           }

        index = key[i] - 'A'; //padrao para reconhecimento de cada letra
       
        if(index<0)           //verifica se eh hifen
        index=index + 46;     //corrige para a tag certa do hifen  
        if(atual->letra[index] == false) //verifica se o ponteiro foi iniciado, caso ele esteja NULL significa que foi, caso contrario nao foi, logo necessita inicializacao 
        {
            atual->letra[index] = startNode(); //cria um novo no pra letra do determinado indice 
        }
            atual = atual->letra[index]; //atual apontando para o mesmo lugar que letras
    }
    
    atual->verificaFim = true; //ponteiro aponta para a variavel que verifica final da palavra, logo atual aponta pra ultima letra do vetor
    return true;
}

bool verificaUltimoNo(trieNode *root) //verifica se eh o ultimo no
{
    for (int i = 0; i < TAMANHO; i++)
    {
       if (root->letra[i]) //se o no atual tiver um no em sequencia, retorna falso
       {
          return false;
       }
       
    }
    return true; // caso nao retorne falso pra os nos, verifica q esse no eh o ultimo 
}

bool buscaPalavraCompleta(trieNode *root, string key) //funcao que buscar por palavras completas na arvore 
{
    trieNode *atual = root; //criacao de um no auxiliar para insercao
    int x = key.length();  //atribui a x o tamanho da palavra a inserir 
    int index;
    string aux; 
    
    for (int i = 0; i < x ; i++) //andar por toda a plavra inserida 
    {
        if(key[i] >= 97) //verificando se eh letra minuscula 
        {
            cout << "O codigo nao aceita letras minusculas, favor utilizar letras maiusculas." << endl;
            return false; 
        }
        index = key[i] - 'A'; //padrao para reconhecimento de cada letra
        if(index<0)           //verifica se eh hifen
        index=index + 46;     //corrige para a tag certa do hifen

        if(atual->letra[index] == false) //verifica se o ponteiro foi iniciado, caso ele esteja NULL significa que foi, caso contrario nao foi, logo nao existe palavra
        {
            cout << " nao encontrada . . ." << endl; 
            return false; //sai da funcao pois nao existe a palavra determinada para busca
        }   
        else
        {
            atual = atual->letra[index]; // atual aponta para o mesmo lugar que o vetor letras, buscando assim em toda a arvore
            aux[i] = key[i]; //somente uma conversao para printar a palavra completa
            
            
        }
    }
    cout <<  endl; 
    
    if(atual->verificaFim) // verifica se palavra esta completa 
            {
                cout << "Palavra encontrada: "; //caso esteja, ela é escrita 
                for (int i = 0; i < x; i++) //rodando por toda a palavra
                {
        
                    cout << aux[i]; //printando a palavra toda, letra por letra
                }   
                cout <<  endl; 
                return true; //retorna true e sai da funcao, pois a palavra foi encotrada e escrita
            }
            else //caso a palavra nao esteja completa
            {
                cout << "Palavra nao encontrada ... " << endl; //a funcao retorna falso
                return false;
            } 
}

void buscaPrefixo(trieNode *root, string prefixo)//funcao que busca palavras a partir de um determinado prefixo
{
    int aux;
    trieNode *atual = root; //criacao de um no auxiliar para insercao 
    for(int i=0; i < TAMANHO; i++)
    {
        if(atual->letra[i]) //verifica se a posicao atual do vetor letra nao aponta para null
        {
             
            aux = i + 65; // leva a variavel aux para o decimal equivalente a 'A' na tabela ascii
            if(aux > 90) // verifica se é um caracter superior ao 'Z'
            {
                aux -= 46; //corrige para o hifen
            }

            prefixo.push_back(aux); // insere a determinada letra no vetor de string  
            buscaPrefixo(atual->letra[i], prefixo); // funcao recursiva pra conseguir verificar todos os prefixos das palavras 
            prefixo.pop_back(); // tira o ultimo caracter do vetor de string

        }
    
    }

    if(atual->verificaFim) //verifica se é a ultima letra da palavra
        cout << prefixo << endl; //se for entao esse prefixo é a propria palavra, podendo mostrar ele na tela
    
}

int imprimeBusca(trieNode *root, string auxiliar) //funcao que faz verificacoes e imprime os prefixos encontrados
{
    trieNode *atual = root; //criacao de um no auxiliar para insercao
    int x = auxiliar.length(); //atribui a x o tamanho da palavra a inserir
    int index;
    string prefixo; 
    
    for (int i = 0; i < x ; i++)
    {
        if(auxiliar[i] >= 97) //verificando se eh letra minuscula 
        {
            cout << "O codigo nao aceita letras minusculas, favor utilizar letras maiusculas." << endl;
            return -1;  
        }
        index = auxiliar[i] - 'A'; 
        if(index<0) //verifica se eh hifen
        index=index + 46; //corrige para a tag certa do hifen 
        if(atual->letra[index] == false) //verifica se o ponteiro foi iniciado, caso ele esteja NULL significa que foi, caso contrario nao foi, logo nao existe palavras a comparar 
            return -1; //como nao existe pode terminar a funcao
        atual = atual->letra[index]; //atual apontando para o mesmo lugar que letras
    }

    if(atual->verificaFim == true && verificaUltimoNo(atual)) //verifca se a letra atual eh a ultima da palavra e se o no de atual eh o ultimo
    {   
        cout << auxiliar << endl; // imprime a propria entrada
        return 0;  //termina a funcao pois achou somente 1 palavra pro determinado prefixo
    }    
    if(verificaUltimoNo(atual) == false) //verifica se atual nao eh o ultimo no 
    {
         
        buscaPrefixo(atual, auxiliar); //busca prefixos ainda existentes na arvore
        return 1; //termina a funcao pois todos os prefixos ja foram registrados
    }

}

void menu() //mostra na tela um menu para o usuario
{
    cout << "-------- Corretor ortografico -------- \n\n\n";
    cout << "(1) Inserir arquivos: \n";
    cout << "(2) Procurar palavras completas: \n";
    cout << "(3) Procurar palavras por prefixo: \n";
    cout << "(4) Corrigir palavra: \n";
    cout << "(5) Sair: \n\n";

}

void leArquivoInsereArvore(trieNode *root) //funcao que le o arquivo .txt e insere as palavras deste na arvore
{
    string aux;
    ifstream listaPalavras; //criacao da variavel que recebera a lista
    trieNode *atual = root; //criacao de um no auxiliar para insercao
    

    listaPalavras.open("palavras_atualizado.txt"); //abrindo o arquivo .txt

     
    while(listaPalavras.eof() == false) //enquanto o final da lista for falso (end of file)
    {
        getline(listaPalavras, aux); //copia a linha atual da lista para a string aux;       
        Inserir(root, aux); //insere na arvore trie a palavra do arquivo
    }
    listaPalavras.close(); //depois de inserir a lista toda, fecha-se o arquivo

}





int main()
{
    
    trieNode *root = startNode(); //constroi-se o no
    int comparador, operador;  
    string x;
    
    cout << "ESCREVA SUA PALAVRA EM LETRA MAIUSCULA ... " << endl << endl;
    

    while(operador!=5)//enquanto operador for diferente de 5
    {
       
       
        menu(); //executa a funcao menu
        cout << "Escolha uma opcao: ";
        cin >> operador;
        cout << endl;
        
        switch (operador)
        {
        case 1:
            
            leArquivoInsereArvore(root); //executa a funcao de leitura e insercao
            cout << "Arquivos inseridos com sucesso! " << endl << endl;
            break;
        case 2:
            cout << "Insira uma palavra a ser buscada: ";
            cin >> x; //recebe string para comparacao
            cout << endl; 
            buscaPalavraCompleta(root, x); //executa a funcao de busca de palavras completas
            cout << endl << endl;

            break;
        case 3:
            cout << "Insira um prefixo a ser buscado: ";
            cin >> x; //recebe a string pra comparacao
            comparador = imprimeBusca(root, x); //recebe o valor da funcao inteira de impressao 
            
            if(comparador == 0) //verifica se eh o caso 0
            cout << "somente essa palavra foi encontrada com determinado prefixo" << endl;
            if(comparador == -1) //verifica se eh o caso -1
            cout << "nenhuma palavra encontrada com este prefixo" << endl; 

            break;
        case 4:
            cout << "Funcao nao desenvolvida ... " << endl << endl;
            break;
        case 5: 
            cout << endl << "Saindo ... " << endl << endl; 
            return 0;
        
        }




    }

    
   
 

}