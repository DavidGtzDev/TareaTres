#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Error.h"


int main() {
    std::ifstream archivo("bitacora.txt");

    if (!archivo.is_open()) {
        std::cerr << "No se pudo abrir el archivo." << std::endl;
        return 1;
    }

    std::string linea;
    std::vector<Error> listaDeErrores;
    
    while (std::getline(archivo, linea)) {
        std::vector<std::string> separado = Error::parserDeError(linea);
        listaDeErrores.push_back(Error(separado[0], separado[1], separado[2], separado[3]));
    }

    std::cout << listaDeErrores[12] << std::endl;
    
    
    archivo.close();
    return 0;
}
