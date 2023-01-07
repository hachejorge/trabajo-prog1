/*********************************************************************************************\
 * Programación 1. Trabajo obligatorio
 * Autores: ¡¡¡PONED AQUÍ VUESTROS NOMBRES!!!
 * Ultima revisión: ¡¡¡!!!
 * Resumen: Fichero de implentación «usos-usuario.hpp» de un módulo para trabajar con registros que
 *          permiten contabilizar el número de usos que cada usuario hace del sistema Bizi.
\*********************************************************************************************/

#include "usos-usuario.hpp"
#include "uso.hpp"

/*
 * Pre:  ---
 * Post: Devuelve el número total de usos del sistema Bizi correspondiente a «usuario».
 */
unsigned numUsosTotales(const UsosUsuario usuario){
    return usuario.usosDistEstacion+usuario.usosMismaEstacion;
}

int indiceEncontrado(const UsosUsuario usuarios[], const unsigned numUsuarios, 
                        const unsigned idUsuario, unsigned& i){
    i=0;
    bool encontrado=false;
    while(!encontrado && i<numUsuarios){
        if(idUsuario==usuarios[i].idUsuario){
            encontrado=true;
        }
        else{
            i++;
        }
    }
    if(encontrado){
        return i;
    }
    else{
        return -1;
    }
}

int indiceCorrespondiente(const UsosUsuario usuarios[], const unsigned numUsuarios, const unsigned idUsuario){
    unsigned i=0;
    if(indiceEncontrado(usuarios,numUsuarios,idUsuario,i)==-1){
        return i++;
    }
    else{
        return indiceEncontrado(usuarios,numUsuarios,idUsuario,i);
    }
}

/*
 * Pre:  «nombreFicheroUsos» contiene la ruta y nombre de un fichero de texto con información
 *       sobre usos del sistema Bizi Zaragoza y con el formato establecido en el enunciado.
 *       El vector «usuarios» tiene al menos tantas componentes como número de usuarios
 *       distintos aparecen  en el fichero de nombre «nombreFicheroUsos». El valor del
 *       parámetro «numUsuarios» no está definido.
 * Post: Si se puede leer del fichero «nombreFicheroUsos», el vector «usuarios» almacena, en
 *       sus primeras «numUsuarios» componentes, la información relativa a identificadores de
 *       usuario y número de usos (entre estaciones distintas y entre la misma estación)
 *       extraída del fichero «nombreFicheroUsos» de acuerdo con las consideraciones
 *       establecidas en el enunciado. No es necesario que los registros del vector estén
 *       ordenados por ningún criterio en concreto. Devuelve «true» si el fichero puede ser
 *       leído sin problemas y «false» en caso contrario.
 */
bool obtenerUsosPorUsuario(const string nombreFicheroUsos,
                           UsosUsuario usuarios[], unsigned& numUsuarios){
    numUsuarios=0;
    ifstream f;
    f.open(nombreFicheroUsos);
    if(f.is_open()){
        string cabecera;
        getline(f,cabecera);
        UsoBizi usos;
        while(leerUso(f,usos)){
            usuarios[indiceCorrespondiente(usuarios,numUsuarios,usos.idUsuario)].idUsuario=usos.idUsuario;
            if(usos.idAnclaje==usos.idRetiro){
                usuarios[indiceCorrespondiente(usuarios,numUsuarios,usos.idUsuario)].usosMismaEstacion++;
            }
            else{
                usuarios[indiceCorrespondiente(usuarios,numUsuarios,usos.idUsuario)].usosDistEstacion++;
            }
            if(indiceCorrespondiente(usuarios,numUsuarios,usos.idUsuario)>=numUsuarios){
                numUsuarios++;
            }
        }
        f.close();
        return true;
    }
    else{
        cerr << "No se ha podido abrir el fichero \"" << nombreFicheroUsos << "\"." << endl;
        return false;
    }
}

void permutar(UsosUsuario& a, UsosUsuario& b){
    UsosUsuario aux;
    aux.idUsuario=a.idUsuario;
    aux.usosDistEstacion=a.usosDistEstacion;
    aux.usosMismaEstacion=a.usosMismaEstacion;
    a.idUsuario=b.idUsuario;
    a.usosDistEstacion=b.usosDistEstacion;
    a.usosMismaEstacion=b.usosMismaEstacion;
    b.idUsuario=aux.idUsuario;
    b.usosDistEstacion=aux.usosDistEstacion;
    b.usosMismaEstacion=aux.usosMismaEstacion;
}

/*
 * Pre:  numUsuarios > 0; numOrdenar > 0
 * Post: El vector usuarios[0..numUsuarios-1] es una permutación de los datos iniciales del
 *       vector, de forma que los «numOrdenar» primeros son los usuarios de mayor número de
 *       usos y están ordenados por número de usos decreciente.
 */
void ordenar(UsosUsuario usuarios[], const unsigned numUsuarios, 
             const unsigned numOrdenar){
    for (unsigned i = 0; i < numOrdenar; i++) {
        unsigned iMayor = i;
        for (unsigned j = i+1; j < numUsuarios; j++) {
            if ( numUsosTotales(usuarios[j]) > numUsosTotales(usuarios[iMayor]) ) {
                iMayor=j;
            }
            permutar(usuarios[i], usuarios[iMayor]);
        }
    }
}
