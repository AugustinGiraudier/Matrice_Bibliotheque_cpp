#include"../Matrice.h"
#include<time.h>

void AfficherMatrice(AG::CMatrice& mat);

int main() {
	AG::CMatrice mat = AG::CMatrice{ 120, 120 };
	AG::CMatrice mat2 = AG::CMatrice{ 120, 120 };

	mat.Init(3);
	mat2.Init(3);
	std::cout << "fin initialisation..." << std::endl;

	//calcul de multiplication classique : 
	clock_t t1, t2;
	t1 = clock();
	AG::CMatrice mat4 = mat * mat2;
	t2 = clock();
	float temps1 = (float)(t2 - t1) / CLOCKS_PER_SEC;
	std::cout << "fin calcul mono..." << std::endl;

	//calcul de multiplication multithread : 
	clock_t t3, t4;
	t3 = clock();
	AG::CMatrice mat3 = AG::CMatrice::MultWithThreads(mat, mat2);
	t4 = clock();
	float temps2 = (float)(t4 - t3) / CLOCKS_PER_SEC;
	std::cout << "fin calcul multi..." << std::endl;

	std::cout << "multiplication classique : (en "<<temps1<<" secondes)" << std::endl;
	std::cout << "multiplication multithread : (en " << temps2 << " secondes)" << std::endl;
	std::cout << "Le rapport est de " << temps1 / temps2 << std::endl;
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