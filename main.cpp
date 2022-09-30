#include <iostream>
#include <string>
#include <sstream>

#include "Utils.h"
#include "Canvas.h"

int GetIntFromString(const std::string& str);
void UpdateCanvas(const Canvas& canvas);

void UpdateCanvas(const Canvas& canvas)
{
    ClearScreen();
    std::cout << canvas; // PrintCanvas(canvas);
}

int main(){
  
    Canvas canvas;
    Fila fila;
    fila = Create();
  
    SetupCanvas(canvas);
    ClearCanvas(canvas);

    // Exemplo de como ativar/desativar um elemento da matriz.
    //ToggleCanvas(canvas, 3, 3);
    //ToggleCanvas(canvas, 3, 3);

    std::string input = "";
    int option = -1;

    do
    {
        UpdateCanvas(canvas);
      
        PrintFila(fila);
      
        std::cout << "\n\n*** OPCOES ***\n"
            << "1 - Alterar uma coordenada.\n"
            << "2 - Executar sequencia de comandos.\n"
            << "3 - Salvar comandos em um arquivo.\n"
            << "4 - Carregar comandos de um arquivo.\n"
            << "5 - Encerrar programa.\n"
            << "Opcao: ";
        
        std::getline(std::cin, input);

        option = GetIntFromString(input);
        switch (option)
        {
        case 1:
            //Implementar opção "1 - Alterar uma coordenada".
        
            Coordenada coordenadas_dadas;
            armazenaCoord(coordenadas_dadas);
            Enqueue(fila, coordenadas_dadas);
          
            ToggleCanvas(canvas, coordenadas_dadas);
            Pause();
            break;
        
        case 2:
            //Implementar opção "2 - Executar sequencia de comandos".
            if (IsEmpty(fila)){
              std::cout << "Nenhuma alteração foi realizada";
              break;
            }
            else{
              ClearScreen();
              ClearCanvas(canvas);
              executaComandos(canvas, fila);
            }
            
            break;
        
        case 3:
            //Implementar opção "3 - Salvar comandos em um arquivo".
          
            salvaArquivo(fila);
            Pause();
            break;
        
        case 4:
            //Implementar opção "4 - Carregar comandos de um arquivo".

            lerArquivo(canvas, fila);
            Pause();
            break;
        
        case 5:
            std::cout << "Fim.\n\n";
            break;
        
        default:
            std::cout << "*** ERRO: Opcao invalida!\n\n";
          
            Pause();
            break;
        }

    } while (option != 5);
}
