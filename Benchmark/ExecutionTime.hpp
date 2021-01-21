#include<chrono>
/*
@file ExecutionTime.hpp
@brief Biblioth�que de calcul de dur�e
@author Augustin GIRAUDIER
@date 21 janvier 2021
*/

/*
@enum TimeUnit
@brief unit�es de mesure de temps disponibles
*/
enum class TimeUnit {
	minutes,
	seconds,
	milliseconds,
	microseconds
};

/*
@class ExecutionTime
@brief Class permettant de mesurer la dur�e d'execution d'un processus

////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////Exemple d'utilisation/////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////

	#include<iostream>
	#include"ExecutionTime.hpp"

	int main(){

		ExecutionTime ExT{};  // le premier point temporel est plac� � la cr�ation de l'objet
		//VotreFonctionATester1();
		std::cout << "Dur�e de la prmeiere fonction : " << ExT.End() << std::endl;
		// La m�thode End() renvoie le temps (en secondes) �coul� depuis le dernier point dans le temps

		ExT.Start(); // La m�thode Start() place un nouveau point dans le temps
		//VotreFonctionATester2();
		std::cout << "Dur�e de la deuxieme fonction : " << ExT.End(TimeUnit::milliseconds) << std::endl;
		// La m�thode End() peut renvoyer la dur�e dans d'autres unit�s vial l'enum�ration TimeUnit.

		return 0;
	}

////////////////////////////////////////////////////////////////////////////////////////////
*/
class ExecutionTime {

private:
	/*
	@brief Donn�e stockant un point t�moin dans le temps
	*/
	std::chrono::steady_clock::time_point Time;
public:

	/*
	@brief Cr�e le point t�moin dans le temps lors de la construction de l'objet
	*/
	ExecutionTime()
	{
		Start();
	}
	/*
	@brief Cr�e un nouveau point dans le temps
	*/
	void Start() {
		Time = std::chrono::high_resolution_clock::now();
	}
	/*
	@brief renvoie la dur�e �coul�e depuis le dernier point dans le temps
	@param TimeUnit unit : unit� de temps renvoy�e*/
	float End(TimeUnit unit = TimeUnit::seconds) {

		std::chrono::duration<float> fs = std::chrono::high_resolution_clock::now() - Time;
		switch (unit) {
		case TimeUnit::seconds:
			return fs.count();
		case TimeUnit::milliseconds:
			std::chrono::milliseconds d = std::chrono::duration_cast<std::chrono::milliseconds>(fs);
			return (float)d.count();
		case TimeUnit::microseconds:
			std::chrono::microseconds d2 = std::chrono::duration_cast<std::chrono::microseconds>(fs);
			return (float)d2.count();
		case TimeUnit::minutes:
			std::chrono::minutes d3 = std::chrono::duration_cast<std::chrono::minutes>(fs);
			return (float)d3.count();
		default:
			return fs.count();
		}
	}
};
