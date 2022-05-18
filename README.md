# Trabalho-1
Repositório contendo as especificações do Trabalho 1 da disciplina de LP1

# Avaliação e Feedback

## Geral

- Implementção da Classe forca ou similar | 10 / 10 pontos
	- ok

- Implementação da Interface textual | 10 / 10 pontos
	- ok

- Execução completa do jogo | 14 / 15 pontos
	- Sorteio correto de paralavras para o jogo: cp1
	- Configuração correta da palavra jogada, dependendo da dificuldade:  5 / 5 
	- Execução correta do jogo (não pode repetir palpites, contabilização correta dos pontos e loop): 2 / 3
        - Vocês estão considerando letras minúsculas como se não fizessem parte da palavra (embora alguns casos deu certo o.O)
	- Salvamento correto do score: 2 / 2
	- Exibição correta dos scores: 5 / 5

- Validação dos arquivos de texto | 5 / 5 pontos
	- ok

- Arquivos de teste de validação dos casos de erro | 4 / 5 pontos
	- vou considerar parcialmente pois não fica claro quais testes devem ser executados e qual a saída esperada

## Código

- Documentação do código e readme | 8 / 10 pontos
	- Vocês não documentaram o processo de compilação vou tirar 2 pontos

- Organização e indentação do código | 10 / 10 pontos
	- ok

- Compilação automatizada | 5 / 5 pontos
    - vou considerar mesmo não estando documentado
	
## Comentários
- Eu faria mais alum arquivo .hpp/.cpp para tentar reduzir e modularizar um pouco o main.
- Gostei dos comentários nos .cpp, ainda poderia ser um pouco menos mas ainda assim ficaram bem organizados/entendíveis.

# Compilação
- cd trabalho-1-RafaelM4gn
- mkdir build
- cd build
- cmake ../
- make

# Execução
- ./jogo ../data/palavras.txt ../data/scores.txt

# Arquivos de teste
- /data/palavras.txt
- /data/palavrasHifen.txt
- /data/palavrasSeparadas.txt
- /data/Scores.txt
- /data/ScoresErro_1.txt
- /data/ScoresErro_2.txt

# Limitações ou funcionalidades não implementadas no programa
- alinhamento da primeira linha do quando exibe o score.


# Documento de Especificação

Leia o documento de especificação contido em [Especificação do Trabalho 1](https://docs.google.com/document/d/1aa51VNLQ_jpZaEuGkMz2KE8feAkE48-TENZ9eqn48nk/edit?usp=sharing). Preencha o autor.md com as informações relativas ao grupo/autor.
