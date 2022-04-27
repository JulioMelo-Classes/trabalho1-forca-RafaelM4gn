#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <random>
#include <algorithm>
#include <iterator>
#include "Forca.hpp"
using namespace std;

Forca::Forca(string palavras, string scores)
{
    m_arquivo_palavras = palavras;
    m_arquivo_scores = scores;
}
string Forca::proxima_palavra(){
    m_palavra_atual = m_palavras_do_jogo[m_palavras_do_jogo.size() - 1];
    m_palavras_do_jogo.pop_back();
    m_palavra_jogada ={};//!< retorna "_ _ _ _ ... _"
    for (int i = 0; i < m_palavra_atual.size(); i++)
    {
        m_palavra_jogada += '_';
        if(i < m_palavra_atual.size()-1) m_palavra_jogada += ' ';
    }

    string letras_reveladas = "";
    string conso = "BCDFGHJKLMNPQRSTVWXYZ";
    vector<char> consoantes = {};
    vector<char> vogais = {};
    cout << "chegou aqui" << endl;
    if(m_dificuldade == FACIL){
        for (int c = 0; c < m_palavra_atual.size(); c++)
            if( m_palavra_atual[c] !='-' && m_palavra_atual[c] !='A' && m_palavra_atual[c] !='E' && m_palavra_atual[c] !='I' && m_palavra_atual[c] !='O' && m_palavra_atual[c] !='U')
                consoantes.push_back(m_palavra_atual[c]);
        for (int i = 0; i < m_palavra_atual.size()/5; i++)
        {
            int temp_rand = rand()%consoantes.size();
            if(letras_reveladas.find_first_of(consoantes[temp_rand]) == std::string::npos)
                letras_reveladas += consoantes[temp_rand];
        }
    } else if (m_dificuldade == MEDIO){
        for (int c = 0; c < m_palavra_atual.size(); c++)
            if( m_palavra_atual[c] =='A' || m_palavra_atual[c] =='E' || m_palavra_atual[c] =='I' || m_palavra_atual[c] =='O' || m_palavra_atual[c] =='U')
                vogais.push_back(m_palavra_atual[c]);
        for (int i = 0; i < m_palavra_atual.size()/5; i++)
        {
            int temp_rand2 = rand()%vogais.size();
            if(letras_reveladas.find_first_of(vogais[temp_rand2]) == std::string::npos)
                letras_reveladas += vogais[temp_rand2];
        }
    }
    cout << "chegou aqui 2" << endl;

    for (int i = 0; i < letras_reveladas.size(); i++){
        for (int j = 0; j < m_palavra_atual.size(); j++){
            if(m_palavra_atual[j] == letras_reveladas[i])
            {
                m_palavra_jogada[j*2] = letras_reveladas[i];
                break;
            }
        }
    }










    for (int i = 0; i < consoantes.size(); i++) cout << "consoantes "<< consoantes[i]<< endl;
    cout << "palavra_atual "<< m_palavra_atual<< endl;
    cout << "palavra_jogada "<< m_palavra_jogada << endl;
    cout << "letras reveladas "<< letras_reveladas << endl;
    
    return m_palavra_atual;
}
void Forca::set_dificuldade(Dificuldade d)
{
    m_dificuldade = d;
    m_palavras_do_jogo = {};
    int count= 0;
    int media = 0;
    for (int c = 0; c < m_palavras.size(); c++) {
        media += m_palavras[c].second;
    }
    media = media / (m_palavras.size());
    random_shuffle(m_palavras.begin(), m_palavras.end());
    if (d == FACIL){
        for (int c = 0; c < m_palavras.size(); c++)
        {
            if (m_palavras[c].second < media && count < 10)
            {
                m_palavras_do_jogo.push_back(m_palavras[c].first);
                count++;
            }
            
        }
        
    } else if (d == MEDIO){
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
    } else if (d == DIFICIL){
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
    for (int i = 0; i < m_palavras.size() ; i++)
    {
      cout << m_palavras[i].first << " " << m_palavras[i].second << endl;
    }
    for (int i = 0; i < m_palavras_do_jogo.size() ; i++)
    {
      cout << "palavras do jogo:" << m_palavras_do_jogo[i] << endl;
    }
}

void Forca::carregar_arquivos()
  {
    fstream palavrasfile;
    palavrasfile.open(m_arquivo_palavras, ios::in);
    string palavra;
    int frequencia;
    while (!palavrasfile.eof())
    {
      palavrasfile >> palavra  >> frequencia ;
      m_palavras.push_back(make_pair(palavra, frequencia));
    }
    for (int c = 0; c < m_palavras.size(); c++) {
        transform(m_palavras[c].first.begin(), m_palavras[c].first.end(), m_palavras[c].first.begin(), ::toupper);
    }
  }

pair<bool, string> Forca::eh_valido()
{
    fstream ValidaScores;
    fstream ValidaScores2;
    fstream ValidaPalavras;
    string frequencia;
    string palavra;
    ostringstream oss;

    int line = 0;
    ValidaPalavras.open(m_arquivo_palavras, ios::in);
    if (ValidaPalavras.fail())
    {
        oss << "Arquivo " << m_arquivo_palavras << " nao encontrado";
        return make_pair(false, oss.str());
    }

    while (!ValidaPalavras.eof())
    {
        ValidaPalavras >> palavra >> frequencia ;
        line++;
        if (palavra.size() <= 4)
        {
            oss << "Uma das palavras possui frequência menor que 4. Palavra: " << palavra << " Linha: " << line;
            return make_pair(false, oss.str());
        }
        if (frequencia.find_first_not_of("0123456789") != string::npos)
        {
            oss << "Frequência de uma das palavras Inválida. Palavra: " << palavra << " Linha: " << line;
            return make_pair(false, oss.str());
        }
        if (palavra.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ-") != string::npos)
        {
            oss << "Palavras com caracteres inválidos. Palavra: " << palavra << " Linha: " << line;
            return make_pair(false, oss.str());
        }
    }
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
        if (dificulty.empty() || nome.empty() || pontuacao.empty())
        {
            oss << "Um dos campos está vazio. Linha: " << line;
            return make_pair(false, oss.str());
        }
    }
    ValidaScores2.open(m_arquivo_scores, ios::in);
    line = 0;
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