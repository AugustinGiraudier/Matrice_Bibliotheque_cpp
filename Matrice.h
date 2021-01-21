#ifndef __AG_MATRICE__
#define __AG_MATRICE__

#include<vector>
#include<iostream>

/*
@file Matrice.h
@brief Biblioth�que de gestion de matrices
@author Augustin GIRAUDIER
@date 20 aout 2020


Pour un exemple de code / test de performance de l'op�rateur multithread : 
	https://github.com/AugustinGiraudier/Matrice_Bibliotheque_cpp
*/


namespace AG
{

	/*
	@class CCoordonnee
	@brief class de gestion de coordonn�es 2D 
	 - acesseurs
	 - setters
	 - op�rateur de comparaison
	 */
	class CCoordonnee
	{
	private:
		/*
		@brief coordonn�e x*/
		size_t m_x;
		/*
		@brief coordonn�e y*/
		size_t m_y;

	public:
		/*
		@brief contruit un objet coordonnee
		@param size_t x : coordonn�e x (1 par d�faut)
		@param size_t y : coordonn�e y (1 par d�faut)*/
		CCoordonnee(size_t x = 1, size_t y = 1);
		/*
		@brief constructeur par recopie
		@param const CCoordonnee& coord : objet � recopier*/
		CCoordonnee(const CCoordonnee& coord);
		/*
		@return coordonn�e x*/
		size_t getX() const { return m_x; }
		/*
		@return coordonn�e y*/
		size_t getY() const { return m_y; }

		/*
		@brief test si les x et y des deux objets sont �gaux*/
		bool operator==(CCoordonnee& coord);
	};

	/*
	@class CMatrice
	@brief classe de gestion d'une matrice de dimention param�trable
	- op�rateurs
	- identit�
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
		@brief objet de type coordonn�e qui stocke les dimentions de la matrice*/
		CCoordonnee m_size;


	public:

		/*-------------------------------------------constructeurs------------------------------------------------*/

		/*
		@brief contruit une matrice avec ses 2 dimentions
		@param size_t largeur : nombre de colonnes
		@param size_t hauteur : nombre de lignes*/
		CMatrice(size_t largeur, size_t hauteur);
		/*
		@brief construit une matrice avec un objet coordonn�e
		@param CCoordonnee& coord : coordonnees d�finissant les dimentions de la matrice*/
		CMatrice(CCoordonnee& coord);
		/*
		@brief constructeur par recopie
		@param const CMatrice& matrice : matrice dont on fait la copie*/
		CMatrice(const CMatrice& matrice);
		/*
		@brief construit une matrice � partir d'un vector de double � 2 dimentions
		@param std::vector<std::vector<double>> matrice : vecteur contenant la matrice � initialiser*/
		CMatrice(std::vector<std::vector<double>> matrice);

		/*-----------------------------------------------static----------------------------------------------------*/

		/*
		@return objet matrice identit�e de dimention variable
		@param int dimension : dimention de la matrice identit�e cr��e*/
		static CMatrice Identity(int dimention);
		/*
		@return multiplication multithread�e de matrices
		@param CMatrice& matA : matrice A
		@param CMatrice& matB : matrice B*/
		static CMatrice MultWithThreads(AG::CMatrice& matA, AG::CMatrice& matB);
		/*
		@brief Calcule 1 ligne de multiplication de matrice
		@param size_t ligneCalculee : index de la ligne � calculer
		@param const AG::CMatrice& A : matrice A
		@param const AG::CMatrice& B : matrice B
		@param AG::CMatrice& mResult : matrice r�sultat*/
		static void Compute_1_line(size_t ligneCalculee, const AG::CMatrice& A, const AG::CMatrice& B, AG::CMatrice& mResult);
		/*
		@brief Calcule plusieurs lignes de multiplication de matrice
		@param size_t FirstLine : index de la premi�re ligne � calculer
		@param size_t LastLine : index de la derni�re ligne � calculer (non atteinte)
		@param const AG::CMatrice& A : matrice A
		@param const AG::CMatrice& B : matrice B
		@param AG::CMatrice& mResult : matrice r�sultat*/
		static void Compute_n_lines(size_t FirstLine, size_t LastLine, const AG::CMatrice& A, const AG::CMatrice& B, AG::CMatrice& mResult);

		/*-----------------------------------------getters / setters------------------------------------------------*/

		/*
		@return r�f�rence vers le vecteur 2 dimentions stockant la matrice (lecture/�criture)*/
		std::vector<std::vector<double>>& getVector() { return m_Matrice; }
		/*
		@return vecteur 2 dimentions stockant la matrice (lecture)*/
		std::vector<std::vector<double>> getVector() const { return m_Matrice; }
		/*
		@return r�f�rence vers l'objet coordonn�e stockant les dimentions de la matrice (lecture/�criture)*/
		CCoordonnee& getSize() { return m_size; }
		/*
		@return objet coordonn�e stockant les dimentions de la matrice (lecture)*/
		CCoordonnee getSize() const { return m_size; }
		/*
		@brief modifie la valeur de la matrice aux index indiqu�s, par la valeur indiqu�e
		@param size_t x : index de la colonne (0...1...)
		@param size_t y : index de la ligne (0...1...)
		@param double value : valeur � ins�rer � l'emplacement*/
		void setValue(size_t x, size_t y, double value);
		/*
		@brief modifie la valeur de la matrice aux coordonn�es indiqu�es, par la valeur indiqu�e
		@param CCoordonnee& coord : coordonn�es de mise � jour de la matrice
		@param double value : valeur � ins�rer � l'emplacement*/
		void setValue(CCoordonnee& coord, double value);
		/*
		@return la valeur stock�e dans la matrice aux index sp�cifi�s
		@param size_t x : index de la colonne (0...1...)
		@param size_t y : index de la ligne (0...1...)*/
		double getValue(size_t x, size_t y) { return m_Matrice[x][y]; }
		/*
		@return la valeur stock�e dans la matrice aux coordonn�es sp�cifi�es
		@param CCoordonnee& coord : coordonn�es de la valeur � retourner*/
		double getValue(CCoordonnee& coord) { return getValue(coord.getX(), coord.getY()); }

		/*---------------------------------------------m�thodes--------------------------------------------------*/

		/*
		@brief initialise une matrice avec une variable
		@param double valeur : valeur � inserer � chaque emplacement de la matrice (0 par d�faut)*/
		void Init(double valeur = 0);
		/*
		@return matrice mise � la puissance renseign�e
		@param puissance � appliquer sur la matrice*/
		CMatrice puissance(int puissance);
	};
}
	/*--------------------------------------------op�rateurs------------------------------------------------*/

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


