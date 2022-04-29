#include <iostream>
#include <fstream>
#include "Forca.hpp"

using namespace std;
int main(int argc, char *argv[])
{
    fstream arquivoPonto;
    Forca forca = Forca(argv[1], argv[2]);
    cout << ">>> Lendo arquivos de palavras"
         << " [" << argv[1] << "] "
         << "e scores"
         << " [" << argv[2] << "] ,"
         << "por favor aguarde.." << endl;
    forca.carregar_arquivos();
    auto valid = forca.eh_valido();
    if (!valid.first)
    { // sai do programa ao encontrar um erro
        cout << "Erro " << valid.second << endl;
        exit(-1);
    }
    cout << "--------------------------------------------------------------------" << endl;
    cout << ">>> Arquivos OK!" << endl;

    while (true)
    {
        /*imprime o menu principal e a escolha do usuário*/
        int pontos = 0;
        int escolha;
        int escolhaD;
        cout << "--------------------------------------------------------------------" << endl
             << "Bem vindo ao Jogo Forca! Por favor escolha uma das opções" << endl
             << "1 - Iniciar Jogo" << endl
             << "2 - Ver scores anteriores" << endl
             << "3 - Sair do Jogo" << endl
             << "sua escolha:";
        cin >> escolha;
        if (escolha == 1)
        {
            cout << "Vamos iniciar o jogo! Por favor escolha o nível de dificuldade" << endl
                 << "1 - Fácil" << endl
                 << "2 - Médio" << endl
                 << "3 - Difícil" << endl
                 << "Sua escolha de dificuldade: ";
            cin >> escolhaD;
            if (escolhaD == 1)
                forca.set_dificuldade(forca.FACIL);
            else if (escolhaD == 2)
                forca.set_dificuldade(forca.MEDIO);
            else if (escolhaD == 3)
                forca.set_dificuldade(forca.DIFICIL);
            
            while (true)
            {
                forca.proxima_palavra();
                string palpite;
                cout << forca.get_tentativas_restantes() << " tentativas disponive" << endl;
                while (!forca.rodada_terminada()){
                    cout << "Digite uma letra: " << endl;
                    cin >> palpite;
                    auto result = forca.palpite(palpite);
                    cout << "chances:" << forca.get_tentativas_restantes() << endl;
                    cout << "resultado: "<< result.first << "ja escolhido: " << result.second << endl;
                }
                if(forca.get_palavra_jogada().find_first_of('_') == std::string::npos){
                    /*imprime interface de continuar / parar*/
                    int escolhaC;
                    cout << "Parabens voce acertou a palavra! deseja continuar jogando?" << endl
                            << "1 - Claro!" << endl
                            << "2 - Quero nao" << endl
                            << "Sua escolha: ";
                    cin >> escolhaC;
                    if(escolhaC == 2){
                        break;
                    } else {

                    }
                } else { /*perdeu*/
                    /*imprime gameover e a palavra que estava sendo jogada*/
                    cout << "GAME OVER. A palavra era " << forca.get_palavra_atual() << endl;
                    break;
                }
            }
        }
        else if (escolha == 2)
        {
            arquivoPonto.open(argv[2], ios::in);
            string pontos;
            while (!arquivoPonto.eof())
            {
                getline(arquivoPonto, pontos);
                cout << pontos << endl;
            }
            cout << "Voltar ao menu?" << endl
                 << "1 - Sim" << endl
                 << "2 - Não" << endl;
            int decisao;
            cout << "Escolha: ";
            cin >> decisao;
            if (decisao == 2)
            {
                break;
            }
        }
        else if (escolha = 3)
        {
            exit(3);
        }
        // if (escolha == 1)
        // {
        //     cout << "Vamos iniciar o jogo! Por favor escolha o nível de dificuldade" << endl
        //         << "1 - Fácil" << endl
        //         << "2 - Médio" << endl
        //         << "3 - Difícil" << endl;
        //     cout << "Sua escolha de dificuldade: ";
        //     cin >> escolhaD;
        /*Seleciona dificuldade*/
        Forca::Dificuldade d;
        // forca.set_dificuldade(d);
        //            while(true){ //
        //                string p = forca.proxima_palavra();
        /*exibe interface do jogo*/
        //                while (!forca.rodada_terminada()){ //loop da rodada
        /*ler palpite*/
        //                    string palpite;
        //                    auto result = forca.palpite(palpite);
        /*testa palpite e atualiza a interface dependendo do resultado*/
        //                }
        //                if(true){ /*acertou a palavra inteira*/
        /*imprime interface de continuar / parar*/
        //                    if (/*parar*/)
        //                        break;
        //                    else
        //                        forca.reset_rodada();
        //                }
        //                else{ /*perdeu*/
        /*imprime gameover e a palavra que estava sendo jogada*/
        //                    break;
        //                }
        //            }
        /*ler informações do jogador para o score e gravar no arquivo*/
        //        }
        //        else if(/*mostrar score*/)
        /*mostrar score*/
        //        else //qualquer outro número sai do jogo
        //            break
    }
    return 0;
}