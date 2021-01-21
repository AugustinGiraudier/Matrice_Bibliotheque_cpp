#ifndef __AG_MATRICE__
#define __AG_MATRICE__

#include<vector>
#include<iostream>

/*
@file Matrice.h
@brief Bibliothèque de gestion de matrices
@author Augustin GIRAUDIER
@date 20 aout 2020


Pour un exemple de code / test de performance de l'opérateur multithread : 
	https://github.com/AugustinGiraudier/Matrice_Bibliotheque_cpp
*/


namespace AG
{

	/*
	@class CCoordonnee
	@brief class de gestion de coordonnées 2D 
	 - acesseurs
	 - setters
	 - opérateur de comparaison
	 */
	class CCoordonnee
	{
	private:
		/*
		@brief coordonnée x*/
		size_t m_x;
		/*
		@brief coordonnée y*/
		size_t m_y;

	public:
		/*
		@brief contruit un objet coordonnee
		@param size_t x : coordonnée x (1 par défaut)
		@param size_t y : coordonnée y (1 par défaut)*/
		CCoordonnee(size_t x = 1, size_t y = 1);
		/*
		@brief constructeur par recopie
		@param const CCoordonnee& coord : objet à recopier*/
		CCoordonnee(const CCoordonnee& coord);
		/*
		@return coordonnée x*/
		size_t getX() const { return m_x; }
		/*
		@return coordonnée y*/
		size_t getY() const { return m_y; }

		/*
		@brief test si les x et y des deux objets sont égaux*/
		bool operator==(CCoordonnee& coord);
	};

	/*
	@class CMatrice
	@brief classe de gestion d'une matrice de dimention paramétrable
	- opérateurs
	- identité
	- multiplication multithread
	- puissance
	*/
	class CMatrice
	{
	private:
		/*
		@brief Vector 2 dimention qui stocke la matrice de double*/
		std::vector<std::vector<double>> m_Matrice;
		/*
		@brief objet de type coordonnée qui stocke les dimentions de la matrice*/
		CCoordonnee m_size;


	public:

		/*-------------------------------------------constructeurs------------------------------------------------*/

		/*
		@brief contruit une matrice avec ses 2 dimentions
		@param size_t largeur : nombre de colonnes
		@param size_t hauteur : nombre de lignes*/
		CMatrice(size_t largeur, size_t hauteur);
		/*
		@brief construit une matrice avec un objet coordonnée
		@param CCoordonnee& coord : coordonnees définissant les dimentions de la matrice*/
		CMatrice(CCoordonnee& coord);
		/*
		@brief constructeur par recopie
		@param const CMatrice& matrice : matrice dont on fait la copie*/
		CMatrice(const CMatrice& matrice);
		/*
		@brief construit une matrice à partir d'un vector de double à 2 dimentions
		@param std::vector<std::vector<double>> matrice : vecteur contenant la matrice à initialiser*/
		CMatrice(std::vector<std::vector<double>> matrice);

		/*-----------------------------------------------static----------------------------------------------------*/

		/*
		@return objet matrice identitée de dimention variable
		@param int dimension : dimention de la matrice identitée créée*/
		static CMatrice Identity(int dimention);
		/*
		@return multiplication multithreadée de matrices
		@param CMatrice& matA : matrice A
		@param CMatrice& matB : matrice B*/
		static CMatrice MultWithThreads(AG::CMatrice& matA, AG::CMatrice& matB);
		/*
		@brief Calcule 1 ligne de multiplication de matrice
		@param size_t ligneCalculee : index de la ligne à calculer
		@param const AG::CMatrice& A : matrice A
		@param const AG::CMatrice& B : matrice B
		@param AG::CMatrice& mResult : matrice résultat*/
		static void Compute_1_line(size_t ligneCalculee, const AG::CMatrice& A, const AG::CMatrice& B, AG::CMatrice& mResult);
		/*
		@brief Calcule plusieurs lignes de multiplication de matrice
		@param size_t FirstLine : index de la première ligne à calculer
		@param size_t LastLine : index de la dernière ligne à calculer (non atteinte)
		@param const AG::CMatrice& A : matrice A
		@param const AG::CMatrice& B : matrice B
		@param AG::CMatrice& mResult : matrice résultat*/
		static void Compute_n_lines(size_t FirstLine, size_t LastLine, const AG::CMatrice& A, const AG::CMatrice& B, AG::CMatrice& mResult);

		/*-----------------------------------------getters / setters------------------------------------------------*/

		/*
		@return référence vers le vecteur 2 dimentions stockant la matrice (lecture/écriture)*/
		std::vector<std::vector<double>>& getVector() { return m_Matrice; }
		/*
		@return vecteur 2 dimentions stockant la matrice (lecture)*/
		std::vector<std::vector<double>> getVector() const { return m_Matrice; }
		/*
		@return référence vers l'objet coordonnée stockant les dimentions de la matrice (lecture/écriture)*/
		CCoordonnee& getSize() { return m_size; }
		/*
		@return objet coordonnée stockant les dimentions de la matrice (lecture)*/
		CCoordonnee getSize() const { return m_size; }
		/*
		@brief modifie la valeur de la matrice aux index indiqués, par la valeur indiquée
		@param size_t x : index de la colonne (0...1...)
		@param size_t y : index de la ligne (0...1...)
		@param double value : valeur à insérer à l'emplacement*/
		void setValue(size_t x, size_t y, double value);
		/*
		@brief modifie la valeur de la matrice aux coordonnées indiquées, par la valeur indiquée
		@param CCoordonnee& coord : coordonnées de mise à jour de la matrice
		@param double value : valeur à insérer à l'emplacement*/
		void setValue(CCoordonnee& coord, double value);
		/*
		@return la valeur stockée dans la matrice aux index spécifiés
		@param size_t x : index de la colonne (0...1...)
		@param size_t y : index de la ligne (0...1...)*/
		double getValue(size_t x, size_t y) { return m_Matrice[x][y]; }
		/*
		@return la valeur stockée dans la matrice aux coordonnées spécifiées
		@param CCoordonnee& coord : coordonnées de la valeur à retourner*/
		double getValue(CCoordonnee& coord) { return getValue(coord.getX(), coord.getY()); }

		/*---------------------------------------------méthodes--------------------------------------------------*/

		/*
		@brief initialise une matrice avec une variable
		@param double valeur : valeur à inserer à chaque emplacement de la matrice (0 par défaut)*/
		void Init(double valeur = 0);
		/*
		@return matrice mise à la puissance renseignée
		@param puissance à appliquer sur la matrice*/
		CMatrice puissance(int puissance);
	};
}
	/*--------------------------------------------opérateurs------------------------------------------------*/

	/*
	@brief affiche la matrice en ligne et colonnes sur la console*/
	std::ostream& operator<<(std::ostream& out, AG::CMatrice& mat);
	/*
	@brief addition de deux matrice*/
	AG::CMatrice operator+(AG::CMatrice& matA, AG::CMatrice& matB);
	/*
	@brief soustraction de deux matrices*/
	AG::CMatrice operator-(AG::CMatrice& matA, AG::CMatrice& matB);
	/*
	@brief multiplication de deux matrices*/
	AG::CMatrice operator*(AG::CMatrice& matA, AG::CMatrice& matB);
	/*
	@brief multiplication d'une matrice par un double*/
	AG::CMatrice operator*(AG::CMatrice& matA, double b);

#endif // !__AG_MATRICE__


