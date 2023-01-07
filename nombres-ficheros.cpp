/*********************************************************************************************\
 * Programación 1. Trabajo obligatorio
 * Autores: Héctor Barbancho Gómez y Jorge Hernández Aznar
 * Ultima revisión: 
 * Resumen: Fichero de implementación «nombres-ficheros.hpp» de un módulo que contiene constantes 
 *          con los nombres o partes de nombres de los ficheros que se van a utilizar y un
 *          procedimiento denominado «construirNombreFicheroUsos» que facilita la construcción
 *          del nombre de un fichero de usos a partir de la opción sobre el fichero de usos que
 *          haya escrito el usuario. 
\*********************************************************************************************/

#include "nombres-ficheros.hpp"

/*
 * Pre:  ---
 * Post: Devuelve una ruta de acceso relativa a un fichero de usos partiendo del valor del 
 *       parámetro «opcion», concatenando la ruta relativa de acceso al directorio de datos con
 *       el prefijo común a los ficheros de usos, la opción y la extensión de los fichero de
 *       usos.
 *       Por ejemplo, si «opcion» tiene el valor "16", devuelve la ruta "datos/usos-16.csv".
 *       Si «opcion» tiene el valor "t2", devuelve la ruta "datos/usos-t2.csv".
 */
string construirNombreFicheroUsos(const string opcion){
    return RUTA_DATOS+PREFIJO_USOS+opcion+EXTENSION;
}

