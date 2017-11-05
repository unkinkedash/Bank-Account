#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct{
    string nome;
    float preco;
}Produto;


void Extrato(Produto* vetor, int qtd, string you){
    cout<<"Extrato referente ao usuario : "<<you<<endl;
    float total = 0;
    for (int i = 0; i < qtd; i++){
		cout<<vetor[i].nome<<"____"<<vetor[i].preco<<endl;
		total+=vetor[i].preco;
    }
    cout<<"total___"<<total<<endl;
}


void Novo_Usuario(string you, float& saldo){
    ofstream novo((you+".txt").c_str());
    novo << you<<' ';
    cout<<"Quantidade de dinheiro : ";
    float money;
    cin >> money;
    saldo = money;
    novo << money;

    novo.close();
    string filename = (you + "_gastos.txt");
    ofstream expenses(filename.c_str());

    expenses.close();
}

Produto* Inserir(Produto* vetor, int& qtd, float& saldo, string you){
    int quantos;
    cout<<"quantos produtos quer adicionar? : ";
    cin >> quantos;
    Produto* novo = new Produto[(qtd+quantos)];
    
    for (int i = 0; i < qtd; i++){
		novo[i].nome = vetor[i].nome;
		novo[i].preco = vetor[i].preco;
    }
    float discount=0;
    cout<<"Digite o nome e o proco do que comprou e pressione enter : ";
    
    for (int i = qtd; i < (qtd+quantos); i++){
		cin >> novo[i].nome;
		cin >> novo[i].preco;
		discount += novo[i].preco;
    }
    saldo-=discount;
    qtd+=quantos;
    
    if (saldo < 30){
		cout<<"CUIDADO! SALDO BAIXO!!"<<"APENAS "<<saldo<<" REAIS"<<endl<<endl;
    }
    ofstream transfer ((you + "_gastos.txt").c_str());
    
    for (int i = 0; i < qtd; i++){
		transfer << novo[i].nome << ' ' << novo[i].preco<<endl;
    }

    transfer.close();q
    
    delete[] vetor;
    return novo;
}

void Deposito(string you, float& saldo){
    float dep;
    cout<<"Valor do deposito : ";
    cin >> dep;
    saldo += dep;
    ofstream deposit((you + ".txt").c_str());
    deposit << you << saldo;
    
    deposit.close();
    cout<<"Deposito efetuado com sucesso!!"<<endl<<endl;
}

void Atualizacao(string you, float saldo){
    ofstream fim((you + ".txt").c_str());
    fim << you << ' ' << saldo;
    fim.close();
}


void Simulacao(float simulacao){
    cout<<"Seu saldo atual : "<<simulacao<<endl;
    float n1, n2;
    char operando;
    bool stop = false;

    cout<<"- Pressione a tecla 0 para sair da simulacao -"<<endl;
    while(!stop){
		cin >> n1;
		if(n1 != 0){
		     cin >> operando;
		     cin >> n2;
		    if(operando == '+'){
			cout<<n1<<" + "<<n2<<" = "<<n1+n2<<endl;
		    }
		    if (operando == '-'){
			cout<<n1<<" - "<<n2<<" = "<<n1-n2<<endl;
		    }
		    if (operando == '*'){
			cout<<n1<<" * "<<n2<<" = "<<n1*n2<<endl;
		    }
		    if (operando == '/'){
			cout<<n1<<" / "<<n2<<" = "<<n1/n2<<endl;
		    }
		}else{
		    cout<<"-Fim de simulacao-"<<endl<<endl;
		    stop = true;
		}
    }
}

int main(){
    char resposta;
    cout<<"JA POSSUI CONTA? S/N : ";
    cin >> resposta;
    string you;
    float saldo;
    if(resposta == 'S'){
		cout<<"DIGITE SEU NOME : ";
		cin >> you;
	    
		ifstream voce((you + ".txt").c_str());
	    
		if(voce.is_open()){
		    
		    while (voce){
			voce >> you;
			voce >> saldo;
		    }
		}
    }else{
		cout<<"DIGITE SEU NOME : ";
		cin >> you;
		Novo_Usuario(you, saldo);
    }
    
    
    ifstream arquivo((you + "_gastos.txt").c_str());
    int qtd = 0;
    string bio;
    while (arquivo){
		if (arquivo >> bio){
		    qtd++;
		}
    }
    qtd = qtd/2;
    arquivo.close();
    Produto* vetor = new Produto[qtd];
        
    ifstream leitura((you + "_gastos.txt").c_str());
    int i = 0;
    string descricao;
    int numero;

    while(leitura){
		if (leitura >> descricao){
		    vetor[i].nome = descricao;
		}
		if (leitura >> numero){
		    vetor[i].preco = numero;
		}
		i++;
    }

    leitura.close();
    
    int opcao=-1;
    while(opcao != 123){
		cout<<"--> Retirar extrato de compras : 1"<<endl<<endl;
		cout<<"--> Verificar saldo : 2"<<endl<<endl;
		cout<<"--> Registrar compras : 3"<<endl<<endl;
		cout<<"--> Efetuar Deposito : 4"<<endl<<endl;
		cout<<"--> Realizar Simulacao : 5"<<endl<<endl;
		cout<<"--> Sair : 123"<<endl<<endl;
		
		cin >> opcao;
		
		switch (opcao)
		{
		    case 1:
				Extrato(vetor, qtd, you);
				cout<<endl<<endl;
				break;
		    case 2:
				cout<<"Seu saldo eh de : "<< saldo <<endl<<endl;
				break;
		    case 3:
				vetor = Inserir(vetor, qtd, saldo, you);
				cout<<endl<<endl;
				break;
		    case 4:
				Deposito(you, saldo);
				cout<<endl<<endl;
				break;
		    case 5:
				Simulacao(saldo);
				cout<<endl<<endl;
				break;
		    case 123:
				break;
			
			default:
				cout<<"desculpe, opcao nao encontrada :( "<<endl<<endl;
		}
    }
    
    Atualizacao(you, saldo);
    delete[] vetor;
    return 0;
}
