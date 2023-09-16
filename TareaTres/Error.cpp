#include "Error.h"
#include <iostream>
#include <string>
#include <stdexcept>
#include <fstream>
#include <sstream>

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
            fechaInt = (mesInt * 10) + diaInt;
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

std::ostream& operator<<(std::ostream& os, const Error& obj)
{
    os << "Fecha: " << obj.fecha << "   ";
    os << "Hora: " << obj.hora << "   ";
    os << "IP: " << obj.ip << "   ";
    os << "Error: " << obj.log << "   ";
    return os;
}
