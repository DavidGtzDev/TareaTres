#include "Error.h"
#include <iostream>
#include <string>
#include <stdexcept>
#include <fstream>
#include <sstream>
#include <vector>

Error::Error(std::string fch, std::string hr, std::string ip, std::string log)
{
    this->fechaNum = stringDeFechaAEntero(fch);
    this->horaNum = stringDeHoraAEntero(hr);
    this->fecha = fch;
    this->hora = hr;
    this->ip = ip;
    this->log = log;
}
    
std::vector<std::string> Error::parserDeError(std::string str)
{
    std::vector<std::string> words;
    std::string temp = "";

    for (int i = 0; i < str.length(); i++) {
        if (str[i] == ' ') {
            words.push_back(temp);
            temp = "";
        }
        else {
            temp += str[i];
        }
    }

    words.push_back(temp);
    words[0] = words[0] + " " + words[1];
    words.erase(words.begin() + 1);
    std::string tempPhrase = "";

    for (int i = 3; i < words.size(); i++) {
        tempPhrase = tempPhrase + " " + words[i];
    }

    for (int i = 0; i < 11; i++) {
        try {
            if (words.begin() + 3 >= words.end()) {
                //throw std::out_of_range("Index out of range");
            }
            else {
                words.erase(words.begin() + 3);
            }

        }
        catch (const std::out_of_range& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }

    words.push_back(tempPhrase);
    return words;
}

int Error::stringDeFechaAEntero(std::string fecha)
{
    std::ifstream archivo("Meses.txt");
    std::string linea;
    if (!archivo.is_open()) {
        std::cerr << "No se pudo abrir el archivo." << std::endl;
        return 1;
    }

    std::istringstream iss(fecha);
    std::string mes, dia;
    iss >> mes >> dia;
    int mesInt;
    int diaInt;
    diaInt = std::stoi(dia);
    int fechaInt = 0;

    while (std::getline(archivo, linea)) {
        if (linea.find(mes) != std::string::npos) {
            std::string valor = linea.substr(linea.find(mes) + 4);
            mesInt = std::stoi(valor);
            fechaInt = (mesInt * 1000) + diaInt;
            break;
        }
    }

    archivo.close();
    return fechaInt;
}

int Error::stringDeHoraAEntero(std::string hora)
{
    return 0;
}

int Error::getIntFecha()
{
    return this->fechaNum;
}

std::ostream& operator<<(std::ostream& os, const Error& obj)
{
    os << "Fecha: " << obj.fecha << "   ";
    os << "Hora: " << obj.hora << "   ";
    os << "IP: " << obj.ip << "   ";
    os << "Error: " << obj.log << "   ";
    return os;
}

void Error::quickSort(std::vector<Error>& vectorDeErrores, int bajo, int alto)
{
    if (bajo < alto)
    {
        int pivotIndex = partition(vectorDeErrores, bajo, alto);

        // Recursively sort the subvectors
        quickSort(vectorDeErrores, bajo, pivotIndex - 1);
        quickSort(vectorDeErrores, pivotIndex + 1, alto);
    }
}

int Error::partition(std::vector<Error>& vectorDeErrores, int bajo, int alto)
{
    Error pivot = vectorDeErrores[alto]; 
    int i = bajo - 1;                    

    for (int j = bajo; j < alto; ++j)
    {
        if (vectorDeErrores[j].getIntFecha() < pivot.getIntFecha())
        {
            ++i;
            std::swap(vectorDeErrores[i], vectorDeErrores[j]);
        }
    }

    std::swap(vectorDeErrores[i + 1], vectorDeErrores[alto]);
    return i + 1;
}

std::vector<Error> Error::binarySearch(std::vector<Error>& vectorDeErrores, int fechaInicio, int fechaFin)
{
    int low = 0;
    int high = vectorDeErrores.size() - 1;
    int indiceInicio = 0;
    int indiceFinal = 0;
    std::vector<Error> resultado;

    while (low <= high)
    {
        int mid = low + (high - low) / 2;
        Error& currentError = vectorDeErrores[mid];
  
        if (fechaInicio == currentError.getIntFecha())
        {
            indiceInicio = mid;
            break;
        }
        else if (fechaInicio < currentError.getIntFecha())
        {
            high = mid - 1;
        }
        else
        {
            low = mid + 1; 
        }
    }

    low = 0;
    high = vectorDeErrores.size() - 1;

    while (low <= high)
    {
        int mid = low + (high - low) / 2;
        Error& currentError = vectorDeErrores[mid];

        if (fechaFin == currentError.getIntFecha())
        {
            indiceFinal = mid;
            break;
        }
        else if (fechaFin < currentError.getIntFecha())
        {
            high = mid - 1;
        }
        else
        {
            low = mid + 1;
        }
    }

    for (int i = indiceInicio; i <= indiceFinal; i++) {
        resultado.push_back(vectorDeErrores[i]);
    }

    return resultado;
}
