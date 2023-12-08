/*****************************************************************************************************************
	UNIVERSIDAD NACIONAL AUTONOMA DE MEXICO
	FACULTAD DE ESTUDIOS SUPERIORES -ARAGON-

	Computadoras y programacion. 
	(c) Aarón jimenez robles. 32125951
	
	Quiso decir: Programa principal de la aplicacion de la distancia de Levenstein.
	
******************************************************************************************************************/


#include "stdafx.h"
#include <string.h>
#include "corrector.h"
#define DEPURAR 0


void Burbujazo(char arr[][TAMTOKEN], int iEstadisticas[], int* n) {
	for (int i = 0; i < (*n) - 1; ++i) {
		for (int j = 0; j < (*n) - i - 1; ++j) {
			// Comparar palabras e intercambiar
			if (strcmp(arr[j], arr[j + 1]) > 0) {
				// Intercambiar palabras
				char temp[TAMTOKEN];
				strcpy_s(temp, arr[j]);
				strcpy_s(arr[j], arr[j + 1]);
				strcpy_s(arr[j + 1], temp);
			}
		}
	}

	// Eliminar palabras duplicadas
	int newSize = 0;
	for (int i = 0; i < *n; ++i) {
		if (i == 0 || strcmp(arr[i], arr[i - 1]) != 0) {
			// Copiar palabras no repetidas
			strcpy_s(arr[newSize], arr[i]);
			newSize++;


			int contador = 1;
			for (int j = i + 1; j < *n; ++j) {
				if (strcmp(arr[i], arr[j]) == 0) {
					// La palabra actual es igual a la siguiente
					contador++;
				}
				else {
					// La palabra actual es diferente a la siguiente
					iEstadisticas[newSize - 1] = contador;
					break;
				}
			}
		}
	}


	*n = newSize;
}



//Funciones publicas del proyecto
/*****************************************************************************************************************
	DICCIONARIO: Esta funcion crea el diccionario completo
	char *	szNombre				:	Nombre del archivo de donde se sacaran las palabras del diccionario	
	char	szPalabras[][TAMTOKEN]	:	Arreglo con las palabras completas del diccionario
	int		iEstadisticas[]			:	Arreglo con el numero de veces que aparecen las palabras en el diccionario
	int &	iNumElementos			:	Numero de elementos en el diccionario
******************************************************************************************************************/
void	Diccionario			(char *szNombre, char szPalabras[][TAMTOKEN], int iEstadisticas[], int &iNumElementos)
{
	FILE* fpDicc;
	char linea[4000];
	int i;
	iNumElementos = 0;
	// abrir el achivo
	if (DEPURAR == 1)
		printf("%s", szNombre);

	fopen_s(&fpDicc, szNombre, "r");
	if (fpDicc != NULL)
	{
		
		if (DEPURAR == 1)
			printf("\nSi lo pude abrir");

		while (!feof(fpDicc))
		{
			fgets(linea, sizeof(linea), fpDicc);
			if (DEPURAR == 1)
				printf("\n%s\n", linea);
			for (i = 0; i < strlen(linea); i++)
			{
				// Detectar una palabra
				if (linea[i] == ' ' || linea[i] == '\t' || linea[i] == '\n')

				{
					palabraDetectada[indicePD] = '\0';
					strcpy_s(szPalabras[iNumElementos], TAMTOKEN, palabraDetectada);
					iEstadisticas[iNumElementos+1]++;
					if (DEPURAR == 1)
						//printf("\np: %s", palabraDetectada);
						indicePD = 0;
					iNumElementos++;


					// eliminar los espacios en blanco
					// tabuladores y saltos de linea consecutivos

					int contadorEspacios = 1;
					int espaciosAEliminar = 100000;
					while (linea[i + 1] == ' ' && contadorEspacios < espaciosAEliminar) {
						i++;
						contadorEspacios++;
					}

				}
				else
				{
					if (linea[i] != '(' && linea[i] != ')' && linea[i] != ',' && linea[i] != '.')

					{
						palabraDetectada[indicePD] = towlower(linea[i]);
						indicePD++;
					}
				}
			}
			if (DEPURAR == 1)
				printf("\nNumPalabras: %i\n", iNumElementos);
                         

// burbujazo
			Burbujazo(szPalabras, iEstadisticas, &iNumElementos);


			




		}

		fclose(fpDicc);
	}
	else
	{
		if (DEPURAR == 1)
			printf("\nNo lo pude abrir");
	}
}

}

/*****************************************************************************************************************
	ListaCandidatas: Esta funcion recupera desde el diccionario las palabras validas y su peso
	Regresa las palabras ordenadas por su peso
	char	szPalabrasSugeridas[][TAMTOKEN],	//Lista de palabras clonadas
	int		iNumSugeridas,						//Lista de palabras clonadas
	char	szPalabras[][TAMTOKEN],				//Lista de palabras del diccionario
	int		iEstadisticas[],					//Lista de las frecuencias de las palabras
	int		iNumElementos,						//Numero de elementos en el diccionario
	char	szListaFinal[][TAMTOKEN],			//Lista final de palabras a sugerir
	int		iPeso[],							//Peso de las palabras en la lista final
	int &	iNumLista)							//Numero de elementos en la szListaFinal
******************************************************************************************************************/
void	ListaCandidatas		(
	char	szPalabrasSugeridas[][TAMTOKEN],	//Lista de palabras clonadas
	int		iNumSugeridas,						//Lista de palabras clonadas
	char	szPalabras[][TAMTOKEN],				//Lista de palabras del diccionario
	int		iEstadisticas[],					//Lista de las frecuencias de las palabras
	int		iNumElementos,						//Numero de elementos en el diccionario
	char	szListaFinal[][TAMTOKEN],			//Lista final de palabras a sugerir
	int		iPeso[],							//Peso de las palabras en la lista final
	int &	iNumLista)							//Numero de elementos en la szListaFinal
{

	//Sustituya estas lineas por su código
	strcpy(szListaFinal[0], szPalabrasSugeridas[ 0] ); //la palabra candidata
	iPeso[0] = iEstadisticas[0];			// el peso de la palabra candidata
	
	iNumLista = 1;							//Una sola palabra candidata
}

/*****************************************************************************************************************
	ClonaPalabras: toma una palabra y obtiene todas las combinaciones y permutaciones requeridas por el metodo
	char *	szPalabraLeida,						// Palabra a clonar
	char	szPalabrasSugeridas[][TAMTOKEN], 	//Lista de palabras clonadas
	int &	iNumSugeridas)						//Numero de elementos en la lista
******************************************************************************************************************/
void	ClonaPalabras(
	char *	szPalabraLeida,						// Palabra a clonar
	char	szPalabrasSugeridas[][TAMTOKEN], 	//Lista de palabras clonadas
	int &	iNumSugeridas)						//Numero de elementos en la lista
{
	//Sustituya estas lineas por su código
	strcpy(szPalabrasSugeridas[0], szPalabraLeida); //lo que sea que se capture, es sugerencia
	iNumSugeridas = 1;							//Una sola palabra sugerida
}
