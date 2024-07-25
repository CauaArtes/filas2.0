#include <iostream>
#include <queue>
#include <list>

using namespace std;

// Estrutura para representar um guichê
struct Guiche {
    int id;
    queue<int> senhasAtendidas; // Fila de senhas atendidas por este guichê
};

int main() {
    queue<int> senhasGeradas; // Fila de senhas geradas
    list<Guiche> guichesAbertos; // Lista de guichês abertos

    int opcao = -1;
    
    while (opcao != 0 || !senhasGeradas.empty()) {
        cout << "Selecione uma opção:" << endl;
        cout << "0. Sair" << endl;
        cout << "1. Gerar senha" << endl;
        cout << "2. Abrir guichê" << endl;
        cout << "3. Realizar atendimento" << endl;
        cout << "4. Listar senhas atendidas" << endl;
        
        // Exibir quantidade de senhas aguardando atendimento e número de guichês abertos
        cout << "Senhas aguardando atendimento: " << senhasGeradas.size() << endl;
        cout << "Guichês abertos para atendimento: " << guichesAbertos.size() << endl;
        
        cin >> opcao;

        switch(opcao) {
            case 1: {
                // Gerar senha
                static int proximaSenha = 1;
                senhasGeradas.push(proximaSenha++);
                break;
            }
            case 2: {
                // Abrir guichê
                Guiche novoGuiche;
                novoGuiche.id = guichesAbertos.size() + 1;
                guichesAbertos.push_back(novoGuiche);
                break;
            }
            case 3: {
                // Realizar atendimento
                if (guichesAbertos.empty()) {
                    cout << "Não há guichês abertos para atendimento." << endl;
                    break;
                }
                
                int idGuiche;
                cout << "Digite o ID do guichê que está chamando a senha: ";
                cin >> idGuiche;
                
                // Encontrar o guichê pelo ID
                auto it = find_if(guichesAbertos.begin(), guichesAbertos.end(), 
                                  [idGuiche](const Guiche& g) { return g.id == idGuiche; });
                
                if (it != guichesAbertos.end()) {
                    // Verificar se há senhas geradas
                    if (!senhasGeradas.empty()) {
                        int senhaAtual = senhasGeradas.front();
                        senhasGeradas.pop();
                        
                        // Adicionar a senha atendida ao guichê correspondente
                        it->senhasAtendidas.push(senhaAtual);
                        cout << "Senha " << senhaAtual << " atendida pelo guichê " << idGuiche << endl;
                    } else {
                        cout << "Não há senhas para atender no momento." << endl;
                    }
                } else {
                    cout << "Guichê não encontrado." << endl;
                }
                break;
            }
            case 4: {
                // Listar senhas atendidas por um guichê
                int idGuiche;
                cout << "Digite o ID do guichê para listar as senhas atendidas: ";
                cin >> idGuiche;
                
                // Encontrar o guichê pelo ID
                auto it = find_if(guichesAbertos.begin(), guichesAbertos.end(), 
                                  [idGuiche](const Guiche& g) { return g.id == idGuiche; });
                
                if (it != guichesAbertos.end()) {
                    // Exibir as senhas atendidas pelo guichê
                    cout << "Senhas atendidas pelo guichê " << idGuiche << ":" << endl;
                    queue<int> copiaSenhas = it->senhasAtendidas;
                    while (!copiaSenhas.empty()) {
                        cout << copiaSenhas.front() << " ";
                        copiaSenhas.pop();
                    }
                    cout << endl;
                } else {
                    cout << "Guichê não encontrado." << endl;
                }
                break;
            }
            case 0: {
                // Sair
                if (senhasGeradas.empty()) {
                    cout << "Programa encerrado. Quantidade de senhas atendidas: " << endl;
                    int totalSenhasAtendidas = 0;
                    for (const auto& guiche : guichesAbertos) {
                        totalSenhasAtendidas += guiche.senhasAtendidas.size();
                    }
                    cout << totalSenhasAtendidas << endl;
                } else {
                    cout << "Ainda há senhas geradas aguardando atendimento." << endl;
                }
                break;
            }
            default:
                cout << "Opção inválida. Por favor, selecione uma opção válida." << endl;
                break;
        }
        
        cout << endl;
    }
    
    return 0;
}
