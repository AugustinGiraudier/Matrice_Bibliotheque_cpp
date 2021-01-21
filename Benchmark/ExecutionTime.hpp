#include<chrono>
/*
@file ExecutionTime.hpp
@brief Bibliothèque de calcul de durée
@author Augustin GIRAUDIER
@date 21 janvier 2021
*/

/*
@enum TimeUnit
@brief unitées de mesure de temps disponibles
*/
enum class TimeUnit {
	minutes,
	seconds,
	milliseconds,
	microseconds
};

/*
@class ExecutionTime
@brief Class permettant de mesurer la durée d'execution d'un processus

////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////Exemple d'utilisation/////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////

	#include<iostream>
	#include"ExecutionTime.hpp"

	int main(){

		ExecutionTime ExT{};  // le premier point temporel est placé à la création de l'objet
		//VotreFonctionATester1();
		std::cout << "Durée de la prmeiere fonction : " << ExT.End() << std::endl;
		// La méthode End() renvoie le temps (en secondes) écoulé depuis le dernier point dans le temps

		ExT.Start(); // La méthode Start() place un nouveau point dans le temps
		//VotreFonctionATester2();
		std::cout << "Durée de la deuxieme fonction : " << ExT.End(TimeUnit::milliseconds) << std::endl;
		// La méthode End() peut renvoyer la durée dans d'autres unités vial l'enumération TimeUnit.

		return 0;
	}

////////////////////////////////////////////////////////////////////////////////////////////
*/
class ExecutionTime {

private:
	/*
	@brief Donnée stockant un point témoin dans le temps
	*/
	std::chrono::steady_clock::time_point Time;
public:

	/*
	@brief Crée le point témoin dans le temps lors de la construction de l'objet
	*/
	ExecutionTime()
	{
		Start();
	}
	/*
	@brief Crée un nouveau point dans le temps
	*/
	void Start() {
		Time = std::chrono::high_resolution_clock::now();
	}
	/*
	@brief renvoie la durée écoulée depuis le dernier point dans le temps
	@param TimeUnit unit : unité de temps renvoyée*/
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
