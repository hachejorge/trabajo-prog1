/*********************************************************************************************\
 * Programación 1. Trabajo obligatorio
 * Autores: Héctor Barbancho Gómez y Jorge Hernández Aznar
 * Última revisión: 18/12/2022
 * Resumen: Fichero de prueba sobre los datos del fichero <usos-16.cvs> y <usos-17.cvs>
\*********************************************************************************************/
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

/*
* Pre:  ---
* Post: Tras la ejecución de este procedimiento, se imprimen en "nomCopia", las "numLineas"+1 primeras
*       líneas de "nomFichero"
*/
void copiar(istream& nomFichero, ostream& nomCopia, int numLineas){
    string linea;
    for(int i=0; i<numLineas; i++){
            getline(nomFichero,linea);
            nomCopia << linea << endl;
    }
}

/*
* Pre:  ---
* Post: Tras la ejecución de este procedimiento, se copian las "numLineas" primeras líneas del fichero de 
*       lectura "nomFichero", a un fichero de escritura "nomCopia"
*/
void seleccionarCopia(const string nomFichero, const string nomCopia, const int numLineas){
    // Creamos y abrimos el fichero de lectura
    ifstream original;
    original.open(nomFichero);
    // Empezamos a trabajar con él si se ha abierto correctamente
    if(original.is_open()){
        // Creamos y abrimos el fichero de escritura
        ofstream copia;
        copia.open(nomCopia);
        // Empezamos a trabajar con él si se ha abierto correctamente
        if(copia.is_open()){
            copiar(original, copia, numLineas);
            // Cerramos el flujo de escritura
            copia.close();
        }
        // Mensaje de error
        else{
            cerr<< "No se ha podido crear el fichero \"" << nomCopia << "\"." << endl;
        }
        // Cerramos el flujo de lectura
        original.close();
    }
    // Mensaje de error
    else{
        cerr<< "No se ha podido acceder a \"" << nomFichero << "\"." << endl;
    }
}

/*
*  Pre:  Existen los ficheros "usos-16.csv" y "usos-17.csv", y están estructurados 
*        como indica el enunciado.
*  Post: Tras la ejecución de este programa, en la carpeta "datos", se crean los 
*        ficheros "usos-t1.csv" y "usos-t2.csv" que almacenan las 10 primeras líneas 
*        de "usos-16.csv", incluyendo su cabecera, y las 2000 primeras línes de 
*        "usos-17.csv", incluyendo su cabecera, respectivamente.
*/
int main(){
    seleccionarCopia("datos/usos-16.csv","datos/usos-t1.csv",10);
    seleccionarCopia("datos/usos-17.csv","datos/usos-t2.csv",2000);
    return 0;
}