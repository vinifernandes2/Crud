#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>

//Implementar PostgreSQL

using namespace std;

class Produto {
private:
    int numero_id;
    string nome;
    string categoria;
    double preco;
    int quantidade;

public:
    Produto(int numero_id, string nome, string categoria, double preco, int quantidade) {
        this->numero_id = numero_id;
        this->nome = nome;
        this->categoria = categoria;
        this->preco = preco;
        this->quantidade = quantidade;
    }

    int getNumero_id() const {
        return numero_id;
    }

    void setNumero_id(int numero_id) {
        this->numero_id = numero_id;
    }

    string getNome() const {
        return nome;
    }

    void setNome(string nome) {
        this->nome = nome;
    }

    string getCategoria() const {
        return categoria;
    }

    void setCategoria(string categoria) {
        this->categoria = categoria;
    }

    double getPreco() const {
        return preco;
    }

    void setPreco(double preco) {
        this->preco = preco;
    }

    int getQuantidade() const {
        return quantidade;
    }

    void setQuantidade(int quantidade) {
        this->quantidade = quantidade;
    }
};

class Inventario {
private:
    vector<Produto> produtos;

public:
    void addProduto(Produto produto) {
        bool achar = false;
        for (auto& p : produtos) {
            if (p.getNumero_id() == produto.getNumero_id()) {
                cout << "\nNumero de identificacao ja existe." << endl;
                achar = true;
                break;
            }
        }
        if (!achar) {
            produtos.push_back(produto);
            cout << "\nProduto adicionado com sucesso!\n" << endl;
            cout << "-----------------------------------------------------------" << endl;
        }
    }

    void removerProduto(int numero_id) {
        bool achar = false;
        for (auto i = produtos.begin(); i != produtos.end();) {
            if (i->getNumero_id() == numero_id) {
                i = produtos.erase(i);
                achar = true;
                cout << "\nProduto removido com sucesso!\n" << endl;
                cout << "-----------------------------------------------------------" << endl;
                break;
            } else {
                ++i;
            }
        }
        if (!achar) {
            cout << "\nEste numero id nao existe" << endl;
        }
    }

    Produto* acharProduto(int numero_id) {
        for (auto& produto : produtos) {
            if (produto.getNumero_id() == numero_id) {
                return &produto;
            }
        }
        return nullptr;
    }

    void modificarProduto(int numero_id, string nome, string categoria, double preco, int quantidade) {
        bool achar = false;
        for (auto& produto : produtos) {
            if (produto.getNumero_id() == numero_id) {
                produto.setNome(nome);
                produto.setCategoria(categoria);
                produto.setPreco(preco);
                produto.setQuantidade(quantidade);
                achar = true;
                cout << "\nProduto modificado com sucesso!\n" << endl;
                cout << "-----------------------------------------------------------" << endl;
                break;
            }
        }
        if (!achar) {
            cout << "\nEste numero de identificacao nao existe!" << endl;
        }
    }

    void printProduto() const {
        for (const auto& produto : produtos) {
            cout << "\nNumero de identificacao: " << produto.getNumero_id() << endl;
            cout << "Nome: " << produto.getNome() << endl;
            cout << "Categoria: " << produto.getCategoria() << endl;
            cout << "Preco: R$ " << produto.getPreco() << endl;
            cout << "Quantidade: " << produto.getQuantidade() << endl;
            cout << "-----------------------------------------------------------" << endl;
        }
    }

    void salvarInventarioEmArquivo(string nome_arquivo) {
        ofstream arquivo(nome_arquivo);
        if (arquivo.is_open()) {
            for (const auto& produto : produtos) {
                arquivo << produto.getNumero_id() << "," << produto.getNome() << "," << produto.getCategoria() << "," << produto.getPreco() << "," << produto.getQuantidade() << endl;
            }
            arquivo.close();
            cout << "\nInventario salvo no arquivo!\n" << endl;
            cout << "-----------------------------------------------------------" << endl;
        } else {
            cout << "\nErro: nao foi possivel abrir o arquivo " << nome_arquivo << endl;
        }
    }

    void carregarInventarioDoArquivo(string nome_arquivo) {
        ifstream arquivo(nome_arquivo);
        if (arquivo.is_open()) {
            produtos.clear(); // Limpa o vetor atual antes de carregar do arquivo
            string linha;
            while (getline(arquivo, linha)) {
                stringstream ss(linha);
                string numero_idStr, nome, categoria, precoStr, quantidadeStr;
                getline(ss, numero_idStr, ',');
                getline(ss, nome, ',');
                getline(ss, categoria, ',');
                getline(ss, precoStr, ',');
                getline(ss, quantidadeStr, ',');

                int numero_id = stoi(numero_idStr);
                double preco = stod(precoStr);
                int quantidade = stoi(quantidadeStr);

                Produto p(numero_id, nome, categoria, preco, quantidade);
                produtos.push_back(p);
            }
            arquivo.close();
            cout << "\nInventario carregado do arquivo!\n" << endl;
            cout << "-----------------------------------------------------------" << endl;
        } else {
            cout << "\nErro: nao foi possivel abrir o arquivo " << nome_arquivo << endl;
        }
    }
};

int main() {

    Inventario inventario;
    cout << "-----------------------------------------------------------" << endl;
    cout << "---------------Sistema de Cadastro de Estoque----------------" << endl;
    cout << "-----------------------------------------------------------" << endl;
    cout << "-------------------------Bem vindo!------------------------" << endl;
    cout << "-----------------------------------------------------------" << endl;
    string escolha;

    do {
        cout << "\nPor favor escolha uma opcao:" << endl;
        cout << "1. Adicione um produto" << endl;
        cout << "2. Remova um produto" << endl;
        cout << "3. Encontre um produto" << endl;
        cout << "4. Modifique um produto" << endl;
        cout << "5. Visualize todos os produtos" << endl;
        cout << "6. Salve o inventario no arquivo" << endl;
        cout << "7. Carregue o inventario do arquivo" << endl;
        cout << "Q. Sair" << endl;
        cin >> escolha;

        switch (escolha[0]) {
            case '1': {
                int numero_id;
                string nome, categoria;
                double preco;
                int quantidade;
                cout << "\nInsira um numero de identificacao: ";
                cin >> numero_id;

                cin.ignore(); // Limpa o buffer de entrada

                cout << "\nInsira o nome do produto: ";
                getline(cin, nome);

                cout << "\nInsira a categoria do produto: ";
                getline(cin, categoria);

                cout << "\nInsira o preco do produto: R$ ";
                cin >> preco;
                
                cout << "\nInsira a quantidade de produtos: ";
                cin >> quantidade;

                Produto produto(numero_id, nome, categoria, preco, quantidade);
                inventario.addProduto(produto);
                break;
            }  
            case '2': {
                int numero_id;
                cout << "\nInsira o numero de identificacao do produto: ";
                cin >> numero_id;
                inventario.removerProduto(numero_id);
                break;
            }

            case '3': {
                int numero_id;
                cout << "\nInsira o numero de identificacao do produto: ";
                cin >> numero_id;
                Produto* produto = inventario.acharProduto(numero_id);
                if (produto) {
                    cout << "Nome: " << produto->getNome() << endl;
                    cout << "Categoria: " << produto->getCategoria() << endl;
                    cout << "Preco: R$ " << produto->getPreco() << endl;
                    cout << "Quantidade: " << produto->getQuantidade() << endl;
                    cout << "-----------------------------------------------------------" << endl;
                } else {
                    cout << "\nProduto nao encontrado\n" << endl;
                    cout << "-----------------------------------------------------------" << endl;
                }
                break;
            }

            case '4': {
                int numero_id;
                string nome, categoria;
                double preco;
                int quantidade;
                cout << "\nInsira o numero de identificacao do produto: ";
                cin >> numero_id;
                cout << "\nInsira o nome do produto: ";
                cin.ignore(); // Limpa o buffer de entrada
                getline(cin, nome);
                cout << "\nInsira a categoria do produto: ";
                getline(cin, categoria);
                cout << "\nInsira o preco do produto : R$ ";
                cin >> preco;
                cout << "\nInsira a quantidade do produto: ";
                cin >> quantidade;
                inventario.modificarProduto(numero_id, nome, categoria, preco, quantidade);
                break;
            }

            case '5': {
                inventario.printProduto();
                break;
            }

            case '6': {
                inventario.salvarInventarioEmArquivo("inventario.csv");
                break;
            }

            case '7': {
                inventario.carregarInventarioDoArquivo("inventario.csv");
                break;
            }

            case 'q': {
                cout << "\nAte mais!" << endl;
                return 0;

            }
            case 'Q': {
                cout << "\nAte mais!" << endl;
                return 0;
            }
            default: {
                cout << "\nEscolha errada, por favor tente novamente.\n" << endl;
                break;
            }
        }
    } while (true);

    return 0;
}
