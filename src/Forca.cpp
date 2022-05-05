#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <random>
#include <algorithm>
#include <iterator>
#include <iomanip>
#include "Forca.hpp"
using namespace std;

Forca::Forca(string palavras, string scores)
{
	m_arquivo_palavras = palavras;
	m_arquivo_scores = scores;
}
string Forca::proxima_palavra()
{
	m_tentativas_restantes = 6;
	if (m_palavras_do_jogo.empty())
		return "4C4B0U"; //!< string para verifica se as palavras do jogo acabaram
	m_palavra_atual = m_palavras_do_jogo[m_palavras_do_jogo.size() - 1];
	m_palavras_do_jogo.pop_back(); //!< retira a proxima palavra a ser jogada
	m_palavra_jogada = {};		   //!< retorna "_ _ _ _ ... _"
	for (int i = 0; i < m_palavra_atual.size(); i++)
	{
		m_palavra_jogada += '_';
		if (i < m_palavra_atual.size() - 1)
			m_palavra_jogada += ' ';
	}
	string letras_reveladas = " -";
	string conso = "BCDFGHJKLMNPQRSTVWXYZ";
	vector<char> consoantes = {};
	vector<char> vogais = {};
	if (m_dificuldade == FACIL) //!< Sorteia a quantidades e as consoantes que serao reveladas para o jogador
	{
		for (int c = 0; c < m_palavra_atual.size(); c++)
			if (m_palavra_atual[c] != '-' && m_palavra_atual[c] != 'A' && m_palavra_atual[c] != 'E' && m_palavra_atual[c] != 'I' && m_palavra_atual[c] != 'O' && m_palavra_atual[c] != 'U')
				consoantes.push_back(m_palavra_atual[c]);
		for (int i = 0; i < m_palavra_atual.size() / 5; i++)
		{
			int temp_rand = rand() % consoantes.size();
			if (letras_reveladas.find_first_of(consoantes[temp_rand]) == string::npos)
				letras_reveladas += consoantes[temp_rand];
		}
	}
	else if (m_dificuldade == MEDIO) //!< Sorteia a quantidades e as vogais que serao reveladas para o jogador
	{
		for (int c = 0; c < m_palavra_atual.size(); c++)
			if (m_palavra_atual[c] == 'A' || m_palavra_atual[c] == 'E' || m_palavra_atual[c] == 'I' || m_palavra_atual[c] == 'O' || m_palavra_atual[c] == 'U')
				vogais.push_back(m_palavra_atual[c]);
		for (int i = 0; i < m_palavra_atual.size() / 5; i++)
		{
			int temp_rand2 = rand() % vogais.size();
			if (letras_reveladas.find_first_of(vogais[temp_rand2]) == string::npos)
				letras_reveladas += vogais[temp_rand2];
		}
	}
	for (int i = 0; i < letras_reveladas.size(); i++)
	{
		for (int j = 0; j < m_palavra_atual.size(); j++)
		{
			// adiciona as letras do handcap a palavra
			if (m_palavra_atual[j] == letras_reveladas[i])
			{
				m_palavra_jogada[j * 2] = letras_reveladas[i];
			}
			// adiciona o hifen a palavra
			if (m_palavra_atual[j] == '-')
			{
				m_palavra_jogada[j * 2] = '-';
			}
			// adiciona o espaço a palavra
			if (m_palavra_atual[j] == ' ')
			{
				m_palavra_jogada[j * 2] = ' ';
			}
		}
	}
	for (int c = 0; c < letras_reveladas.size(); c++)
	{
		m_letras_palpitadas.push_back(letras_reveladas[c]); //!< Coloca as letras previamente reveladas na lista de letras palpitadas
	}
	return m_palavra_atual;
}
void Forca::set_dificuldade(Dificuldade d)
{
	/* gera e sorteia o vetor com as palavras que serao usadas na partida */
	m_pontos = 0;
	m_dificuldade = d;
	m_palavras_do_jogo = {};
	int count = 0;
	int media = 0;
	for (int c = 0; c < m_palavras.size(); c++)
	{
		media += m_palavras[c].second; //!< calcula a soma das frequencias.
	}
	media = media / (m_palavras.size());				//!< calcula a media das frequencias.
	random_shuffle(begin(m_palavras), end(m_palavras)); //!< torna aleatorio a ordem das palavras
	// random_shuffle(m_palavras.begin(), m_palavras.end());
	if (d == FACIL)
	{
		/**
		 * Insire na base para a partida 10 palavras aleatórias diferentes
		 * cuja frequência seja maior do que a frequência média.
		 */
		for (int c = 0; c < m_palavras.size(); c++)
		{
			if (m_palavras[c].second < media && count < 10)
			{
				m_palavras_do_jogo.push_back(m_palavras[c].first);
				count++;
			}
		}
	}
	else if (d == MEDIO)
	{
		/**
		 * insere 20 palavras aleatórias diferentes; um terço dessas palavras sendo de palavras com frequência menor do que a média;
		 * o restante das palavras com frequência maior ou igual a frequência média.
		 */
		count = 0;
		for (int c = 0; c < m_palavras.size(); c++)
		{
			if (m_palavras[c].second < media && count < 6)
			{
				m_palavras_do_jogo.push_back(m_palavras[c].first);
				count++;
			}
		}
		for (int c = 0; c < m_palavras.size(); c++)
		{
			if (m_palavras[c].second >= media && count < 20)
			{
				m_palavras_do_jogo.push_back(m_palavras[c].first);
				count++;
			}
		}
	}
	else if (d == DIFICIL)
	{
		/**
		 * insere 30 palavras aleatórias diferentes;  3/4 dessas palavras deve ser de palavras com frequência menor do que a média;;
		 * o restante das palavras com frequência maior ou igual a frequência média.
		 */
		count = 0;
		for (int c = 0; c < m_palavras.size(); c++)
		{
			if (m_palavras[c].second < media && count < 22)
			{
				m_palavras_do_jogo.push_back(m_palavras[c].first);
				count++;
			}
		}
		for (int c = 0; c < m_palavras.size(); c++)
		{
			if (m_palavras[c].second >= media && count < 30)
			{
				m_palavras_do_jogo.push_back(m_palavras[c].first);
				count++;
			}
		}
	}
	// for (int i = 0; i < m_palavras_do_jogo.size(); i++)
	// {
	// 	cout << "palavras: " << m_palavras_do_jogo[i] << endl;
	// }
}

void Forca::carregar_arquivos()
{
	/* Limpa os vetores antes de carregar os arquivos*/
	m_scores.clear();
	m_palavras.clear();
	/* Carrega o arquivo de palavras em um vetor*/
	fstream palavrasfile;
	palavrasfile.open(m_arquivo_palavras, ios::in);
	string palavra;
	string frase;
	bool swap = true;
	int frequencia;
	while (getline(palavrasfile, frase)) //!< salva os arquivos em um vetor de pares de palavra e frequencia.
	{
		istringstream iss(frase);
		string token;
		while (getline(iss, token, '\t'))
		{
			if (swap)
			{
				palavra = token;
				swap = false;
			}
			else
			{
				frequencia = atoi(token.c_str());
				swap = true;
			}
		}
		m_palavras.push_back(make_pair(palavra, frequencia));
	}
	for (int g = 0; g < m_palavras.size(); g++)
	{
		/* deixa todas as palavras em maiusculo */
		transform(m_palavras[g].first.begin(), m_palavras[g].first.end(), m_palavras[g].first.begin(), ::toupper);
	}
	/* Carrega o arquivo de scores em um vetor*/
	fstream scoresfile;
	scoresfile.open(m_arquivo_scores, ios::in);
	string fraseS;
	string dificuldade;
	string nome;
	Scores_base data; //!< Struct tipo do vetor (dificuldade, nome, palavras acertadas e pontuação).
	int pontos;
	while (getline(scoresfile, fraseS))
	{
		istringstream issS(fraseS);
		string tokenS;
		int count = 0;
		data.s_palavras.clear(); //!< limpa o atributo das palavras acertadas
		while (getline(issS, tokenS, ';'))
		{
			if (count == 0) //!< armazena o dado da dificuldade
			{
				data.s_dificuldade = tokenS;
				count++;
			}
			else if (count == 1) //!< armazena o dado do nome do jogador.
			{
				data.s_nome = tokenS;
				count++;
			}
			else if (count == 2) //!< armazena todas as palavras acertas em um vetor de string dentro do struct (separado por virgulas).
			{
				istringstream issTS(tokenS);
				string tokenTS;
				while (getline(issTS, tokenTS, ','))
				{
					data.s_palavras.push_back(tokenTS);
				}
				count++;
			}
			else if (count == 3) //!< armazena o dado da pontuacao final do jogador
			{
				data.s_pontos = atoi(tokenS.c_str());
				count++;
			}
		}
		m_scores.push_back(data);
	}
}

pair<bool, string> Forca::eh_valido()
{
	/* validacao do arquivo de palavras */
	fstream ValidaScores;
	fstream ValidaScores2;
	fstream ValidaPalavras;
	string frequencia;
	string palavra;
	ostringstream oss;
	string frase;
	bool swap = true;
	int line = 0;
	ValidaPalavras.open(m_arquivo_palavras, ios::in);
	if (ValidaPalavras.fail()) //!< Verifica se o arquivo existe.
	{
		oss << "Arquivo " << m_arquivo_palavras << " nao encontrado";
		return make_pair(false, oss.str());
	}
	while (getline(ValidaPalavras, frase))
	{
		istringstream iss(frase);
		string token;
		while (getline(iss, token, '\t'))
		{
			if (swap)
			{
				palavra = token;
				swap = false;
			}
			else
			{
				frequencia = token;
				swap = true;
			}
		}
		line++;
		if (palavra.size() <= 4) //!< verifica se a palavra é maior que 4.
		{
			oss << "Uma das palavras possui frequência menor que 4. Palavra: " << palavra << " Linha: " << line;
			return make_pair(false, oss.str());
		}
		if (frequencia.find_first_not_of("0123456789") != string::npos) //!< verifica se a frequencia é composta apenas de numeros.
		{
			oss << "Frequência de uma das palavras Inválida. Palavra: " << palavra << " Linha: " << line;
			return make_pair(false, oss.str());
		}
		if (palavra.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ- ") != string::npos) //!< verifica se a caracteres invalidos na palavra.
		{
			oss << "Palavras com caracteres inválidos. Palavra: " << palavra << " Linha: " << line;
			return make_pair(false, oss.str());
		}
	}
	/* validacao do arquivo de scores */
	ValidaScores.open(m_arquivo_scores, ios::in);
	if (ValidaScores.fail())
	{
		oss << "Arquivo " << m_arquivo_scores << " nao encontrado";
		return make_pair(false, oss.str());
	}
	string dificulty, nome, pontuacao, array;
	line = 0;
	while (!ValidaScores.eof())
	{
		line++;
		getline(ValidaScores, dificulty, ';');
		getline(ValidaScores, nome, ';');
		getline(ValidaScores, array, ';');
		getline(ValidaScores, pontuacao), '\n';
		if (dificulty.empty() || nome.empty() || pontuacao.empty()) /* Verifica se algum campo esta vazio (exeto o de palavras acertadas) */
		{
			oss << "Um dos campos está vazio. Linha: " << line;
			return make_pair(false, oss.str());
		}
	}
	ValidaScores2.open(m_arquivo_scores, ios::in);
	line = 0;
	/* verifica a quantidades de ; por linha */
	while (!ValidaScores2.eof())
	{
		line++;
		int quantidade = 0;
		getline(ValidaScores2, array);
		for (int i = 0; i < array.size(); i++)
		{
			if (array[i] == ';')
				quantidade++;
		}
		if (quantidade >= 4)
		{
			oss << "Quantidade de ; maior que o esperado. Linha: " << line;
			return make_pair(false, oss.str());
		}
	}
	return make_pair(true, "");
}
pair<bool, bool> Forca::palpite(string palpite)
{
	// Este método deve atualizar os atributos m_tentativas, m_palavra_jogada e m_letras_palpitadas, para refletir
	// as situações citadas. No caso da letra já ter sido escolhida, o método não deve atualizar m_tentativas.
	bool nao_palpitada_antes = true;
	for (int i = 0; i < m_letras_palpitadas.size(); i++)
	{
		if (palpite[0] == m_letras_palpitadas[i]) //!< verifica se a letra ja foi escolhida antes.
		{
			nao_palpitada_antes = false;
			break;
		}
	}
	if (nao_palpitada_antes)
	{
		m_letras_palpitadas.push_back(palpite[0]); //!< adiciona a lista de letras palpitadas caso seja a primeira escolha.
	}
	if (m_palavra_atual.find_first_of(palpite) != string::npos)
	{
		for (int i = 0; i < m_palavra_atual.size(); i++)
		{
			if (m_palavra_atual[i] == palpite[0])
			{
				m_palavra_jogada[i * 2] = palpite[0];
				// adicionar m_pontos no hpp
				if (nao_palpitada_antes)
				{
					m_pontos++; //!< adiciona 1 ponto para cada letra da palavra que corresponda ao palpite.
				}
			}
		}
		return make_pair(true, nao_palpitada_antes);
	}
	else
	{
		if (nao_palpitada_antes)
			m_tentativas_restantes--; //!< reduz uma tentativa caso o palpite nao pertenca a palavra
		return make_pair(false, nao_palpitada_antes);
	}
}
string Forca::get_palavra_jogada()
{
	return m_palavra_jogada;
}

string Forca::get_palavra_atual()
{
	return m_palavra_atual;
}

int Forca::get_tentativas_restantes()
{
	return m_tentativas_restantes;
}
bool Forca::rodada_terminada()
{
	if (m_tentativas_restantes == 0) //!< checa se as tentativas acabaram.
	{
		return true;
	}
	if (m_palavra_jogada.find_first_of('_') == std::string::npos) //!< checa se ha lacunas nao preenchidas na palavra.
	{
		m_pontos += 2;
		cout << " +2 pontos por acertar a ultima letra! Seus pontos: " << m_pontos << endl;
		m_palavras_acertadas.push_back(m_palavra_atual);
		return true;
	}
	return false;
}
int Forca::get_reset_pontos()
{
	int temp = m_pontos;
	m_palavras_acertadas.clear(); //<! limpa o vetor de palavras acertas para o proximo jogador.
	m_pontos = 0;				  //<! reseta a quantidade de pontos para o proximo jogador.
	return temp;
}
void Forca::reset_rodada()
{
	m_letras_palpitadas = {};	//<! limpa o vetor de letras palpitadas para a proxima palavra.
	m_tentativas_restantes = 6; //<! reseta as tentativas restantes.
}

string Forca::get_dificuldade()
{
	/* retorna a dificuldade em formato de string */
	if (m_dificuldade == FACIL)
		return "Fácil";
	if (m_dificuldade == MEDIO)
		return "Médio";
	if (m_dificuldade == DIFICIL)
		return "Difícil";
	return " ";
}

vector<string> Forca::get_palavras_acertadas()
{
	return m_palavras_acertadas; //<! vetor com as palavras acertadas.
}

void Forca::imprimirForca()
{
	/* Imprime o boneco da forca pelas tentativas restantes */
	switch (m_tentativas_restantes)
	{
	case 6:
		cout << endl
			 << endl
			 << endl
			 << endl
			 << endl;
		break;
	case 5:
		cout << " O" << endl
			 << endl
			 << endl
			 << endl;
		break;
	case 4:
		cout << " O" << endl
			 << " |" << endl
			 << endl
			 << endl;
		break;
	case 3:
		cout << " O" << endl
			 << "/|" << endl
			 << endl
			 << endl;
		break;
	case 2:
		cout << " O" << endl
			 << "/|\\" << endl
			 << endl
			 << endl;
		break;
	case 1:
		cout << " O" << endl;
		cout << "/|\\" << endl;
		cout << "/" << endl
			 << endl;
		;
		break;
	case 0:
		cout << " O" << endl;
		cout << "/|\\" << endl;
		cout << "/ \\" << endl
			 << endl;
		break;
	}
	/* exibe a interface para escolher o palpite */
	// cout << "TEMPORARIO ------------------------------------- palavra_atual: " << m_palavra_atual << endl;
	cout << m_palavra_jogada << endl;
	cout << "Pontos: " << m_pontos << endl;
}

void Forca::imprimirScores()
{
	cout.flush();
	string b_dificuldade = "Dificuldade";
	string b_nome = "Jogador";
	string b_palavra = "<nenhuma>";
	string b_pontos = "Pontos";
	for (int j = 0; j < m_scores.size(); j++)
	{
		if (m_scores[j].s_dificuldade.size() > b_dificuldade.size())
		{
			b_dificuldade = m_scores[j].s_dificuldade; //<! seleciona a maior palavra da coluna dificuldade.
		}
		if (m_scores[j].s_nome.size() > b_nome.size())
		{
			b_nome = m_scores[j].s_nome; //<! seleciona a maior palavra da coluna nome.
		}

		for (int i = 0; i < m_scores[j].s_palavras.size(); i++)
		{
			if (m_scores[j].s_palavras[i].size() > b_palavra.size())
			{
				b_palavra = m_scores[j].s_palavras[i]; //<! seleciona a maior palavra da coluna palavras.
			}
		}

		if (to_string(m_scores[j].s_pontos).size() > b_pontos.size())
		{
			b_pontos = to_string(m_scores[j].s_pontos); //<! seleciona a maior palavra da coluna pontos.
		}
	}
	// Dificuldade | Jogador | Palavras  | Pontos
	cout << setfill(' ')
		 << "Dificuldade" << setw(b_dificuldade.size() - 10 + 1) << "|"
		 << "Jogador" << setw(b_nome.size() - 6 + 2) << "|"
		 << "Palavras" << setw(b_palavra.size() - 8 + 2) << "|"
		 << "Pontos" << setw(b_palavra.size() - 6 + 2) << endl;
	for (int c = 0; c < m_scores.size(); c++) //<! Imprime os scores com o alinhamento da tabela
	{
		cout << setfill(' ')
			 << m_scores[c].s_dificuldade << setw((b_dificuldade.size() - m_scores[c].s_dificuldade.size()) + 3) << "|"
			 << m_scores[c].s_nome << setw((b_nome.size() - m_scores[c].s_nome.size()) + 3) << "|";
		if (m_scores[c].s_palavras.empty())
		{
			cout << " <nenhuma>" << setw(b_palavra.size() - 10 + 2) << "|";
		}
		else
		{
			cout << m_scores[c].s_palavras[0] << setw((b_palavra.size() - m_scores[c].s_palavras[0].size()) + 2) << "|";
		}

		cout << m_scores[c].s_pontos << endl;
		if (m_scores[c].s_palavras.size() > 1)
		{
			for (int o = 0; o < m_scores[c].s_palavras.size(); o++)
			{
				cout << setw(b_dificuldade.size() + 2) << "|"
					 << setw(b_nome.size() + 3) << "|"
					 << m_scores[c].s_palavras[o] << setw((b_palavra.size() - m_scores[c].s_palavras[o].size()) + 2) << "|" << endl;
			}
		}
		cout << setfill('-')
			 << setw(b_dificuldade.size() + 2) << "+"
			 << setw(b_nome.size() + 3) << "+"
			 << setw(b_palavra.size() + 2) << "+";
		cout << "-------" << endl;
	}
}