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

    std::cout << "Leyendo base de datos..." << std::endl;
    
    while (std::getline(archivo, linea)) {
        std::vector<std::string> separado = Error::parserDeError(linea);
        listaDeErrores.push_back(Error(separado[0], separado[1], separado[2], separado[3]));
    }

    Error::quickSort(listaDeErrores, 0, listaDeErrores.size() - 1);

    std::cout << "Dame la fecha de Inicio, el formato es (Primeras tres letras de la fecha en Ingles) seguida del numero del día (Ejemplos: Aug 13, Sep 19, Oct 12)" << std::endl;
    std::getline(std::cin, fechaInicio);
    std::cout << "Dame la fecha de Final, el formato es (Primeras tres letras de la fecha en Ingles) seguida del numero del día (Ejemplos: Aug 13, Sep 19, Oct 12)" << std::endl;
    std::getline(std::cin, fechaFinal);
    std::vector<Error> busqueda;

    try {
        busqueda = Error::binarySearch(listaDeErrores, Error::stringDeFechaAEntero(fechaInicio), Error::stringDeFechaAEntero(fechaFinal));
        
        std::string filename = "output.txt";

        std::ofstream outFile(filename);

        if (!outFile.is_open()) {
            std::cerr << "Failed to open " << filename << " for writing." << std::endl;
            return 1;
        }

        for (int i = 0; i < busqueda.size(); i++) {
            outFile << busqueda[i] << std::endl;
        }

        std::cout << "El resultado fue escrito en el archivo output.txt" << std::endl;

        outFile.close();
    }
    catch (const std::invalid_argument& e) {
        std::cerr << "Error: " << "Fecha no valida, el formato es (Primeras tres letras de la fecha en Ingles) seguida del numero del día (Ejemplos: Aug 13, Sep 19, Oct 12)" << std::endl;
    }
    
    archivo.close();
    return 0;
}
