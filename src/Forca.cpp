#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <random>
#include <algorithm>
#include <iterator>
#include "Forca.hpp"
using namespace std;

/**
         * Cria a classe Forca
         * O construtor pode ou não validar os arquivos de entrada, no entanto, mesmo com 
         * os arquivos inválidos o objeto deve ser construído. Para o caso de arquivos de palavras
         * ou scores inválidos, use o método eh_valido.
         * @param palavras o arquivo que contém as palavras
         * @param scores o nome do arquivo que contém os scores
         * @see eh_valido
         */
Forca::Forca(string palavras, string scores)
{
  m_arquivo_palavras = palavras;
  m_arquivo_scores = scores;
};

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
  
  while(!ValidaPalavras.eof()){
    ValidaPalavras  >> frequencia >> palavra ;
    line++;
    if (palavra.size() <= 4)
    {
        oss << "Uma das palavras possui frequência menor que 4. Palavra: " << palavra << " Linha: "<< line;
        return make_pair(false, oss.str());
    }
    if (frequencia.find_first_not_of("0123456789") != string::npos)
    {
      oss << "Frequência de uma das palavras Inválida. Palavra: "  << palavra << " Linha: "<< line;
      return make_pair(false, oss.str());
    }
    if (palavra.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ-") != string::npos)
    {
      oss << "Palavras com caracteres inválidos. Palavra: "  << palavra << " Linha: "<< line;
      return make_pair(false, oss.str());
    }
  }
  ValidaScores.open(m_arquivo_scores, ios::in);
  string dificulty;
  string nome;
  string pontuacao;
  string array;
  while (!ValidaScores.eof())
  {
    getline(ValidaScores,dificulty,';');  
    getline(ValidaScores,nome,';');
    getline(ValidaScores,array,';');
    getline(ValidaScores,pontuacao),'\n';
    if (dificulty.empty()||nome.empty()||pontuacao.empty())
    {
      return  make_pair(false,"Um dos campos está vazio");
    }
  }
  ValidaScores2.open(m_arquivo_scores, ios::in);
  while (!ValidaScores2.eof())
  { 
    getline(ValidaScores2,array);
    int quantidade = 0;
    for(int i =0;i<array.size();i++)
    {
      if(array[i]==';')
      {
        quantidade +=1;
      }
    }
    if(quantidade>=4)
    {
      return make_pair(false,"Quantidade de ; maior que o esperado");
    }
  }
  return make_pair(true, "");
}