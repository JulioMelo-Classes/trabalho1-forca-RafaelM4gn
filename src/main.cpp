#include <iostream>
#include <fstream>
#include "Forca.hpp"
#include <iomanip>

using namespace std;
int main(int argc, char *argv[])
{
	string arquivoPalavras = argv[1];
	string arquivoScores = argv[2];
	Forca forca = Forca(argv[1], argv[2]);
	cout << ">>> Lendo arquivos de palavras"
		 << " [" << argv[1] << "] "
		 << "e scores"
		 << " [" << argv[2] << "] ,"
		 << "por favor aguarde.." << endl;
	forca.carregar_arquivos(); //!< Carrega os arquivos em vetores.
	auto valid = forca.eh_valido();
	if (!valid.first)
	{
		//! sai do programa ao encontrar um erro
		cout << "Erro " << valid.second << endl;
		exit(-1);
	}
	cout << "--------------------------------------------------------------------" << endl;
	cout << ">>> Arquivos OK!" << endl;
	//! Execucao do jogo
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
		if (escolha == 1) //! escolha de Jogar.
		{
			cout << "Vamos iniciar o jogo! Por favor escolha o nível de dificuldade" << endl
				 << "1 - Fácil" << endl
				 << "2 - Médio" << endl
				 << "3 - Difícil" << endl
				 << "Sua escolha de dificuldade: ";
			cin >> escolhaD;
			if (escolhaD == 1) //! Facil
			{
				forca.set_dificuldade(forca.FACIL);
				cout << "Iniciando o Jogo no nível Fácil, será que você conhece essa palavra?" << endl;
			}
			else if (escolhaD == 2) //! medio
			{
				forca.set_dificuldade(forca.MEDIO);
				cout << "Iniciando o Jogo no nível Médio, será que você conhece essa palavra?" << endl;
			}
			else if (escolhaD == 3) //! dificil
			{
				forca.set_dificuldade(forca.DIFICIL);
				cout << "Iniciando o Jogo no nível Difícil, será que você conhece essa palavra?" << endl;
			}
			while (true)
			{
				if (forca.proxima_palavra() == "4C4B0U") //!< Verifica se as palavras sorteadas acabaram.
				{
					cout << "Todas as palavras foram completadas!";
					break;
				}
				string palpite;
				while (!forca.rodada_terminada()) //!< Verifica se a rodada(uma palavra) terminou.
				{
					forca.imprimirForca();
					cout << "Palpite: " << endl;
					cin >> palpite;
					auto result = forca.palpite(palpite);
				}
				forca.imprimirForca(); //!> Imprime o personagem da forca baseado na quantidade de tentativas restantes.
				if (forca.get_palavra_jogada().find_first_of('_') == std::string::npos)
				{
					/*imprime interface de continuar / parar*/
					int escolhaC;
					cout << "Parabens voce acertou a palavra! deseja continuar jogando?" << endl
						 << "1 - Claro!" << endl
						 << "2 - Quero nao" << endl
						 << "Sua escolha: ";
					cin >> escolhaC;
					if (escolhaC == 2)
					{
						break; //!< direciona para registrar o score
					}
					else
					{
						forca.reset_rodada(); //!< reinicia a rodada
					}
				}
				else
				{ /*perdeu*/
					/*imprime gameover e a palavra que estava sendo jogada*/
					cout << "O jogo acabou, a palavra era " << forca.get_palavra_atual() << "!" << endl;
					break;
				}
			}
			cout << "Digite seu nome para podermos Guardar a sua pontuaçao" << endl;
			string nomeUsuario;
			cin.ignore(); //
			getline(cin, nomeUsuario, '\n');
			fstream EscreverPontos;
			EscreverPontos.open(arquivoScores, ios::app);
			EscreverPontos << endl
						   << forca.get_dificuldade() << "; " << nomeUsuario << "; "; //!< regista o nome e a dificuldade no arquivo scores
			for (int i = 0; i < forca.get_palavras_acertadas().size(); i++)			  //!< regista todas as palavras acertadas pelo jogador
			{
				EscreverPontos << forca.get_palavras_acertadas()[i];
				if (i < forca.get_palavras_acertadas().size() - 1)
				{
					EscreverPontos << ", ";
				}
			}
			EscreverPontos << ";" << forca.get_reset_pontos();
		}
		else if (escolha == 2) //! escolha de Ver os scores;
		{
			forca.carregar_arquivos(); //!< atualiza os dados com os ultimos jogos
			forca.imprimirScores();
			cout << "Voltar ao menu?" << endl
				 << "1 - Sim" << endl
				 << "2 - Não" << endl;
			int decisao;
			cout << "Escolha: ";
			cin >> decisao;
			if (decisao == 2) //!< Sai do jogo
			{
				break;
			}
		}
		else if (escolha = 3) //! Escolha Sair do jogo
		{
			exit(3);
		}
	}
	return 0;
}