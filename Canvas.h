#ifndef __CANVAS_H__
#define __CANVAS_H__

const int CANVAS_ROWS = 8;
const int CANVAS_COLS = 8;

struct Canvas
{
	bool data[CANVAS_ROWS][CANVAS_COLS];
	char on;
	char off;
};

//Struct para armazenar as coordenadas dadas pelo usuario
struct Coordenada{
  int x;
  int y;
};
const int TAMANHO_FILA = 32;

struct Fila{
  Coordenada vetor[TAMANHO_FILA];
	int inicio;
	int fim;
	int contador;
};
//struct para retornar valores nas funções front e dequeue
struct Retorno{
	int codigo;
	Coordenada valor;
};

void SetupCanvas(Canvas& canvas,
#if _WIN32
	char on = (char)219,
	char off = (char)176
#else
	char on = '#',
	char off = '.'
#endif
);

//bloco de funções da Fila
Fila Create();
bool Enqueue(Fila& fila, Coordenada valores);
Retorno Dequeue(Fila& fila);
Retorno Front(const Fila& fila);
bool IsFull(const Fila& fila);
bool IsEmpty(const Fila& fila);

void ClearCanvas(Canvas& canvas);
void ToggleCanvas(Canvas& canvas, Coordenada coordenadas);
void PrintCanvas(const Canvas& canvas);

std::ostream& operator<<(std::ostream& os, const Canvas& canvas);

void armazenaCoord(Coordenada &coordenadas_dadas);
void PrintFila(const Fila fila);
void executaComandos(Canvas &canvas, Fila &fila);
void salvaArquivo(Fila &fila);
void lerArquivo(Canvas &canvas, Fila &fila);

#endif
