#include <iostream>
#include <fstream>
#include <sstream>
#include <string> 
#include "Utils.h"
#include "Canvas.h"

void ClearScreen()
{
#if _WIN32
    std::system("cls");
#else
    std::system("clear");
#endif
}

std::string __pause_hack__;
void Pause(const std::string& message)
{
	std::cout << message;
	std::getline(std::cin, __pause_hack__);
}

int GetIntFromString(const std::string& str)
{
    try
    {
        return std::stoi(str);
    }
    catch (...)
    {
        return -1;
    }
}

// WriteStringToFile()
// Tenta abrir o arquivo indicado no par�metro filename e, em caso positivo,
// salva o conte�do da string contents no arquivo.
// 
// Retorno:
// - true, se foi poss�vel salvar a string no arquivo.
// - false, caso contr�rio.
//
// Exemplo de uso:
// bool isOK = WriteStringToFile("arquivo.txt", "Hello, World!");
// if (isOK) std::cout << "String gravada no arquivo.";
// else std::cout << "Erro ao gravar string no arquivo.";
bool WriteStringToFile(const std::string& filename, Fila &fila)
{
	std::ofstream ofs;

	try
	{
		ofs.open(filename);
		if (ofs.is_open()){
      // Salva o conte�do da string contents no arquivo.
      while(fila.contador != 0){
        std::string coord1, coord2, coordenadas_string;
  
        Coordenada coordenadas_dadas = Front(fila).valor;
        coord1 = std::to_string(coordenadas_dadas.x);
        coord2 = std::to_string(coordenadas_dadas.y);
        coordenadas_string = coord1 + coord2;
        ofs << coordenadas_string;
        ofs << '\n';
        Dequeue(fila);
      
      }
      
			ofs.close();
			return true;
		}
	}
	catch (...)
	{
	}

	return false;
}

// ReadFileAsString()
// Tenta abrir o arquivo indicado no par�metro filename e, em caso positivo,
// monta uma string com todo o conte�do do arquivo separado por quebra de linha.
//
// Retorno:
// - Caso o arquivo seja lido com sucesso, retorna a string que cont�m o
// conte�do do arquivo e o par�metro de sa�da out_isOK sai da fun�o com o valor
// true.
// - Caso n�o seja poss�vel ler o arquivo, retorna uma string vazia e o
// par�metro de sa�da out_isOK sai da fun�o com o valor false.
//
// Exemplo de uso:
// bool isOK = false;
// std::string contents = ReadFileAsString("arquivo.txt", isOK);
// if (isOK) std::cout << contents;
std::string ReadFileAsString(const std::string& filename, bool& out_isOK)
{
	std::ifstream ifs;

	try
	{
		ifs.open(filename);
		if (ifs.is_open())
		{
			std::ostringstream oss;
			std::string str;

			// Cada string separada por espa�o em branco ou quebra de linha
			// � copiada na string str.
			while (ifs >> str)
			{
				// Monta uma �nica string contendo todas as strings
				// separadas por quebra de linha.
				oss << str << '\n';
			}

			ifs.close();

			out_isOK = true;
			return oss.str();
		}
	}
	catch (...)
	{
	}

	out_isOK = false;
	return "";
}
