#include "Matrice.h"
#include<thread>

/*
@file Matrice.cpp
@brief Bibliothèque de gestion de matrices
@author Augustin GIRAUDIER
@date 20 aout 2020


Pour un exemple de code / test de performance de l'opérateur multithread :
	https://github.com/AugustinGiraudier/Matrice_Bibliotheque_cpp
*/

AG::CMatrice::CMatrice(size_t largeur, size_t hauteur)
{
	m_size = AG::CCoordonnee(largeur, hauteur);
	m_Matrice.resize(largeur);
	for (size_t i = 0; i < largeur; ++i)
	{
		m_Matrice[i].resize(hauteur);
	}
}

AG::CMatrice::CMatrice(AG::CCoordonnee& coord)
{
	m_size = coord;
	m_Matrice.resize(m_size.getX());
	for (size_t i = 0; i < m_size.getX(); ++i)
	{
		m_Matrice[i].resize(m_size.getY());
	}
}

AG::CMatrice::CMatrice(const AG::CMatrice& matrice)
{
	m_size = matrice.getSize();
	m_Matrice = matrice.getVector();
}

AG::CMatrice::CMatrice(std::vector<std::vector<double>> matrice)
{
	m_size = AG::CCoordonnee(matrice.size(), matrice[0].size());
	m_Matrice = matrice;
}

AG::CMatrice AG::CMatrice::Identity(int dimention)
{
	AG::CMatrice mat(dimention, dimention);
	for (size_t j = 0; j < dimention; ++j)
	{
		for (size_t i = 0; i < dimention; ++i)
		{
			if (i == j)
				mat.setValue(i, j, 1);
			else
				mat.setValue(i, j, 0);
		}
	}
	return mat;
}



void AG::CMatrice::Compute_1_line(size_t ligneCalculee, const AG::CMatrice& A, const AG::CMatrice& B, AG::CMatrice& mResult)
{
	for (int j = 0; j < B.getSize().getY(); ++j)
		for (int k = 0; k < A.getSize().getY(); ++k)
		{
			mResult.getVector()[ligneCalculee][j] += A.getVector()[ligneCalculee][k] * B.getVector()[k][j];
		}
}
void AG::CMatrice::Compute_n_lines(size_t start, size_t end, const AG::CMatrice& A, const AG::CMatrice& B, AG::CMatrice& mResult)
{
	for (int i = start; i < end; i++) {
		AG::CMatrice::Compute_1_line(i, A, B, mResult);
	}
}

AG::CMatrice AG::CMatrice::MultWithThreads(AG::CMatrice& matA, AG::CMatrice& matB)
{
	size_t dimx = matA.getSize().getX();
	unsigned int nbrThreads = std::thread::hardware_concurrency();
	int nbrLignesParThread = dimx / nbrThreads;
	AG::CMatrice matRetour(dimx, matB.getSize().getY());
	std::vector<std::thread>tabThreads;
	int nbrIteration;
	

	//si la dimension est inférieure au nombre de threads
	if (nbrLignesParThread == 0) {
		nbrIteration = dimx;
		tabThreads.reserve(nbrIteration);
		for (int i = 0; i < nbrIteration; i++)
		{
			tabThreads.emplace_back(std::thread(&AG::CMatrice::Compute_1_line, i, matA, matB, std::ref(matRetour)));
		}
	}
	else {
		nbrIteration = nbrThreads;
		int Rest = dimx % nbrThreads;
		tabThreads.reserve(nbrIteration + Rest);
		for (int i = 0; i < nbrIteration; i++)
		{
			tabThreads.emplace_back(std::thread(&AG::CMatrice::Compute_n_lines, i * nbrLignesParThread, (i * nbrLignesParThread) + nbrLignesParThread, matA, matB, std::ref(matRetour)));
		}
		for (int i = nbrIteration; i < nbrIteration + Rest; i++) {
			tabThreads.emplace_back(std::thread(&AG::CMatrice::Compute_1_line, i, matA, matB, std::ref(matRetour)));
		}
		nbrIteration += Rest;
	}
	for (int i = 0; i < nbrIteration; i++)
	{
		tabThreads[i].join();
	}
	return matRetour;
}

void AG::CMatrice::Init(double valeur)
{
	for (size_t i = 0; i < m_size.getX(); ++i)
	{
		for (size_t j = 0; j < m_size.getY(); ++j)
		{
			m_Matrice[i][j] = valeur;
		}
	}
}

AG::CMatrice AG::CMatrice::puissance(int puissance)
{
	AG::CMatrice mat = *this;
	for (int i = 0; i < puissance - 1; ++i)
	{
		mat = mat * *this;
	}
	return mat;
}

void AG::CMatrice::setValue(size_t x, size_t y, double value)
{
	if (x < m_size.getX() && y < m_size.getY())
	{
		m_Matrice[x][y] = value;
	}
	else
	{
		std::cout << "impossible de changer la valeur aux coordonnees " << x << ";" << y
			<< " les dimensions de la matrices sont " << m_size.getX() << " * " << m_size.getY() << std::endl;
	}
}

void AG::CMatrice::setValue(AG::CCoordonnee& coord, double value)
{
	this->setValue(coord.getX(), coord.getY(), value);
}

std::ostream& operator<<(std::ostream& out, AG::CMatrice& mat)
{
	std::vector<std::vector<double>>* pVec = &mat.getVector();
	for (size_t j = 0; j < (*pVec)[0].size(); ++j)
	{
		for (size_t i = 0; i < pVec->size(); ++i)
		{
			out << (*pVec)[i][j] << " ";
		}
		out << std::endl;
	}
	out << std::endl;
	return out;
}

AG::CMatrice operator+(AG::CMatrice& matA, AG::CMatrice& matB)
{
	if (matA.getSize() == matB.getSize())
	{
		AG::CMatrice a(matA.getSize());
		for (size_t i = 0; i < matA.getSize().getX(); ++i)
		{
			for (size_t j = 0; j < matA.getSize().getY(); ++j)
			{
				a.setValue(i, j, (matA.getVector()[i][j]) + (matB.getVector()[i][j]));
			}
		}
		return a;
	}
	std::cout << "Addition impossible, les deux matrices ne sont pas de meme dimension !" <<std::endl;
	AG::CMatrice a (matA.getSize());
	a.Init();
	return a;
}

AG::CMatrice operator-(AG::CMatrice& matA, AG::CMatrice& matB)
{
	if (matA.getSize() == matB.getSize())
	{
		AG::CMatrice a(matA.getSize());
		for (size_t i = 0; i < matA.getSize().getX(); ++i)
		{
			for (size_t j = 0; j < matA.getSize().getY(); ++j)
			{
				a.setValue(i, j, (matA.getVector()[i][j]) - (matB.getVector()[i][j]));
			}
		}
		return a;
	}
	std::cout << "Soustraction impossible, les deux matrices ne sont pas de meme dimension !" << std::endl;
	AG::CMatrice a(matA.getSize());
	a.Init();
	return a;
}

AG::CMatrice operator*(AG::CMatrice& matA, AG::CMatrice& matB)
{
	if (matB.getSize().getX() == matA.getSize().getY())
	{
		AG::CMatrice matC(matA.getSize().getX(), matB.getSize().getY());
	
		for (int i = 0; i < matA.getSize().getX(); ++i)
			AG::CMatrice::Compute_1_line(i, matA, matB, matC);
		return matC;
	}
	throw EXIT_FAILURE;
}

AG::CMatrice operator*(AG::CMatrice& matA, double b)
{
	AG::CCoordonnee* size = &matA.getSize();
	AG::CMatrice mat{ size->getX(), size->getY() };
	for (int i = 0; i < size->getX(); i++) {
		for (int j = 0; j < size->getY(); j++) {
			mat.setValue(i, j, matA.getValue(i, j) * b);
		}
	}
	return mat;
}

AG::CCoordonnee::CCoordonnee(size_t x, size_t y)
	:m_x(x)
	, m_y(y)
{}

AG::CCoordonnee::CCoordonnee(const AG::CCoordonnee & coord)
{
	m_x = coord.getX();
	m_y = coord.getY();
}

bool AG::CCoordonnee::operator==(AG::CCoordonnee& coord)
{
	if (m_x == coord.getX() && m_y == coord.getY())
		return true;
	return false;
}
