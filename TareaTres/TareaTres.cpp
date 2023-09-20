#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Error.h"


int main() {
    std::ifstream archivo("bitacora.txt");
    std::string fechaInicio = "";
    std::string fechaFinal = "";

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

    Error::quickSort(listaDeErrores, 0, listaDeErrores.size() - 1);

    std::cout << "Dame la fecha de Inicio" << std::endl;
    std::getline(std::cin, fechaInicio);
    std::cout << "Dame la fecha de Final" << std::endl;
    std::getline(std::cin, fechaFinal);

    std::vector<Error> busqueda = Error::binarySearch(listaDeErrores, Error::stringDeFechaAEntero(fechaInicio), Error::stringDeFechaAEntero(fechaFinal));

   
 
    std::string filename = "output.txt";

    std::ofstream outFile(filename);

    if (!outFile.is_open()) {
        std::cerr << "Failed to open " << filename << " for writing." << std::endl;
        return 1;
    }

    for (int i = 0; i < busqueda.size(); i++) {
        outFile << busqueda[i] << std::endl;
    }

    std::cout << "Listo" << std::endl;

    outFile.close();
    
    archivo.close();
    return 0;
}
