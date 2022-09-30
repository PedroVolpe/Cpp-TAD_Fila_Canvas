#ifndef __UTILS_H__
#define __UTILS_H__
#include "Canvas.h"
#include <string>

void ClearScreen();
void Pause(const std::string &message = "\nPressione ENTER para continuar...");

bool WriteStringToFile(const std::string &filename,
                       Fila &fila);
std::string ReadFileAsString(const std::string &filename, bool &isOK);
int GetIntFromString(const std::string& str);

#endif
