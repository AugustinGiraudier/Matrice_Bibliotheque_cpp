#include"../Matrice.h"
#include "ExecutionTime.hpp"

void AfficherMatrice(AG::CMatrice& mat);

/*-----/!\ Pensez à tester ce code en mode Release /!\-----*/

int main() {
	AG::CMatrice mat = AG::CMatrice{ 100, 100 };
	AG::CMatrice mat2 = AG::CMatrice{ 100, 100 };

	mat.Init(3);
	mat2.Init(3);
	std::cout << "fin initialisation..." << std::endl;

	//calcul de multiplication classique :
	ExecutionTime Et{};
	AG::CMatrice mat4 = mat * mat2;
	float TimeMono = Et.End();
	std::cout << "fin calcul mono... (en "<< TimeMono << " secondes)" << std::endl;

	//calcul de multiplication multithread : 
	Et.Start();
	AG::CMatrice mat3 = AG::CMatrice::MultWithThreads(mat, mat2);
	float TimeMulti = Et.End();
	std::cout << "fin calcul multi... (en " << TimeMulti << " secondes)" << std::endl;

	//calcul du rapport de gain de temps
	std::cout << "Le rapport est de " << TimeMono / TimeMulti << std::endl;
}

void AfficherMatrice(AG::CMatrice& mat)
{
	AG::CCoordonnee* size = &mat.getSize();
	for (int i = 0; i < size->getX(); i++) {
		for (int j = 0; j < size->getY(); j++) {
			std::cout << mat.getValue(i, j) << " ";
		}
		std::cout << std::endl;
	}

	std::cout << std::endl << std::endl;
}