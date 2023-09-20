#pragma once
#include <string>
#include <vector>

class Error
{
private:
	int fechaNum;
	int horaNum;
	std::string fecha;
	std::string hora;
	std::string ip;
	std::string log;
public:
	Error(std::string fch, std::string hr, std::string ip, std::string log);
	static std::vector<std::string> parserDeError(std::string str);
	friend std::ostream& operator<<(std::ostream& os, const Error& obj);
	static int stringDeFechaAEntero(std::string fecha);
	int stringDeHoraAEntero(std::string hora);
	static void quickSort(std::vector<Error>& vectorDeErrores, int bajo, int alto);
	int getIntFecha();
	static int partition(std::vector<Error>& vectorDeErrores, int bajo, int alto);
	static std::vector<Error> binarySearch(std::vector<Error>& vectorDeErrores, int fechaInicio, int fechaFin);
};

