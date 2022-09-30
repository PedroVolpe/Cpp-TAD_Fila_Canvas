#include <iostream>
#include "Canvas.h"
#include "Utils.h"

void SetupCanvas(Canvas& canvas, char on, char off)
{
    canvas.on = on;
    canvas.off = off;
}

void ClearCanvas(Canvas& canvas)
{
    for (int row = 0; row < CANVAS_ROWS; ++row)
        for (int col = 0; col < CANVAS_COLS; ++col)
            canvas.data[row][col] = false;
}

void ToggleCanvas(Canvas& canvas, Coordenada coordenadas){
    //Alterei pra adicionar a struct de Coordenadas
    canvas.data[coordenadas.x][coordenadas.y] = !canvas.data[coordenadas.x][coordenadas.y];
}

void PrintCanvas(const Canvas& canvas)
{
    std::cout << "  ";
    for (int col = 0; col < CANVAS_COLS; ++col)
        std::cout << col;
    std::cout << '\n';

    for (int row = 0; row < CANVAS_ROWS; ++row)
    {
        std::cout << row << ' ';
        for (int col = 0; col < CANVAS_COLS; ++col)
            std::cout << (canvas.data[row][col] ? canvas.on : canvas.off);
        std::cout << ' ' << row << '\n';
    }

    std::cout << "  ";
    for (int col = 0; col < CANVAS_COLS; ++col)
        std::cout << col;
    std::cout << '\n';
}

// Essa função sobrescreve (overload) o operador << que é usado em instruções
// como std::cout, std::ofstream e std::ostringstream.
// Observe que, diferente da PrintCanvas(), essa função não faz nenhuma
// referência a std::cout.
// O código dessa função é executado, por exemplo, se uma variável do tipo
// Canvas é passada para std::cout, sendo que o parâmetro std::ostream& os se
// torna std::cout, nesse caso.
std::ostream& operator<<(std::ostream& os, const Canvas& canvas)
{
    os << "  ";
    for (int col = 0; col < CANVAS_COLS; ++col)
        os << col;
    os << '\n';

    for (int row = 0; row < CANVAS_ROWS; ++row)
    {
        os << row << ' ';
        for (int col = 0; col < CANVAS_COLS; ++col)
            os << (canvas.data[row][col] ? canvas.on : canvas.off);
        os << ' ' << row << '\n';
    }

    os << "  ";
    for (int col = 0; col < CANVAS_COLS; ++col)
        os << col;
    os << '\n';

    return os;
}

Fila Create()
{
	Fila fila;
  Coordenada Coordenadas;
	fila.inicio = fila.fim = fila.contador = 0;
	for (int i = 0; i < TAMANHO_FILA; ++i)
		fila.vetor[i] = Coordenadas;
	
	return fila;
}

bool Enqueue(Fila& fila, Coordenada Coordenadas)
{
	if (IsFull(fila))
		return false;
	
	fila.vetor[fila.fim] = Coordenadas;
	fila.fim = (fila.fim + 1) % TAMANHO_FILA;
	++fila.contador;
	return true;
}

Retorno Dequeue(Fila& fila)
{
	Retorno retorno;
  Coordenada coordenadas;
	if (IsEmpty(fila))
	{
		retorno.codigo = -1;
		retorno.valor = {-1,-1};
	}
	else
	{
		retorno.codigo = 0;
		retorno.valor = fila.vetor[fila.inicio];
		
		fila.vetor[fila.inicio] = coordenadas;
		fila.inicio = (fila.inicio + 1) % TAMANHO_FILA;
		--fila.contador;
	}
	
	return retorno;
}

Retorno Front(const Fila& fila)
{
	Retorno retorno = { -1, - 1 };
	if (!IsEmpty(fila))
	{
		retorno.codigo = 0;
		retorno.valor = fila.vetor[fila.inicio];
	}
	
	return retorno;
}

bool IsFull(const Fila& fila)
{
	return fila.contador == TAMANHO_FILA;
}

bool IsEmpty(const Fila& fila)
{
	return fila.contador == 0;
}

void armazenaCoord(Coordenada &coordenadas_dadas){
  int x, y;
  bool errox = true;
  bool erroy = true;
  //Verificação para valor invalido de x
  while(errox){
    std::cout << "Digite a coordenada X:\n"; 
    std::cin >> x;
    if (x >= CANVAS_ROWS){
      std::cout << "Valor Invalido\n";

    } else errox = false;
  } 
  //Verificação para valor invalido de y
  while (erroy){
    std::cout << "Digite a coordenada Y:\n"; 
    std::cin >> y;
    if (y >= CANVAS_COLS){
      std::cout << "Valor Invalido\n";

    } else erroy = false;
  }
  //Armazena os valores
  coordenadas_dadas.x = x;
  coordenadas_dadas.y = y;
  
}

void PrintFila(const Fila fila){
  Fila copiaFila;
  copiaFila = fila;
  
  std::cout << "\nAlteracoes realizadas (" << fila.contador << " de 32):\n";

	if (IsEmpty(copiaFila))
		std::cout << "Nenhuma.";

  else{
    
    while(copiaFila.contador != 0){
      
      Retorno coordenada_dada = Front(copiaFila);
      std::cout << '(' << coordenada_dada.valor.x << ',' << coordenada_dada.valor.y << ')';
      Dequeue(copiaFila);
    }
  }
}
void executaComandos(Canvas &canvas, Fila &fila){
  
  PrintCanvas(canvas);
  PrintFila(fila);
  Pause();
  while (fila.contador != 0){
    ClearScreen();
    Retorno coordenadas_dadas = Front(fila);
    ToggleCanvas(canvas, coordenadas_dadas.valor);
    Dequeue(fila);
    PrintCanvas(canvas);
    PrintFila(fila);
    Pause();
  }
}
void salvaArquivo(Fila &fila){
  
  WriteStringToFile("arquivo_coordenadas.txt", fila);

}
void lerArquivo(Canvas &canvas, Fila &fila){
  Coordenada coordenada;
  bool isOK = false;
  std::string aux_x, aux_y;
  std::string coordenadas_arquivo = ReadFileAsString("arquivo_coordenadas.txt", isOK);
  
  if (isOK){
    int tam = coordenadas_arquivo.length();
    for(int i = 0; i < tam; i++){
      aux_x = coordenadas_arquivo[i];
      aux_y = coordenadas_arquivo[i+1];
      coordenada.x = GetIntFromString(aux_x);
      coordenada.y = GetIntFromString(aux_y);
    
      Enqueue(fila, coordenada);
      ToggleCanvas(canvas, coordenada);
      i += 2;
    }
  }
  else std::cout << "ERRO\nNÃO FOI POSSIVEL CARREGAR AS INFORMAÇÕES DO ARQUIVO!!";
}
