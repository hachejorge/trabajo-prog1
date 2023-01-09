/*********************************************************************************************\
 * Programación 1. Trabajo obligatorio
 * Autores: Héctor Barbancho Gómez y Jorge Hernández Aznar
 * Ultima revisión:
 * Resumen: Fichero de implementación del módulo principal que implementa el trabajo
 *          obligatorio de Programación 1 del curso 2022-23.
\*********************************************************************************************/

#include "nombres-ficheros.hpp"
#include "uso.hpp"
#include "usuarios.hpp"
#include "usos-usuario.hpp"
#include "estacion.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;


/*
 * Pre:  ---
 * Post: Tras su ejecución escribe por pantalla todo el contenido asociado al flujo f
 */
void escribirCadaLinea(ifstream& f, string linea){
    while(getline(f,linea)){
        cout << linea << endl;
    }
}

/*
 * Pre:  FICHERO_OPCIONES está asocidado a un fichero con la sintaxis del enunciado
 * Post: Tras la ejecución, escribe por pantalla el contenido del FICHERO_OPCIONES 
 *       y fichero almacena una cadena de caracteres introducidos por el usuario
 */
void mostrarFicheros(string& fichero){
    cout << "Elección de ficheros de usos y usuarios. Opciones disponibles:" << endl;
    ifstream f;
    f.open(FICHERO_OPCIONES);
    if(f.is_open()){
        string linea;
        escribirCadaLinea(f,linea);
        f.close();
        cout << endl;
        cout << "Introduzca una opción: ";
        cin >> fichero;
    }
    else{
        cerr << "No se ha podido acceder a \"" + FICHERO_OPCIONES + "\" ." << endl;
    }
}

/*
 * Pre:  ---
 * Post: Tras la ejecución de esta función, se solitica al usuario reiteradamente un fichero
 *       hasta que se selecciona uno que exista y fichero almacena el dato introducido
 */
void presentarFicheros(string& fichero){
    mostrarFicheros(fichero);
    fichero=construirNombreFicheroUsos(fichero);
    ifstream f;
    f.open(fichero);
    while(!f.is_open()){
        cerr << "No se ha podido abrir el fichero \"" << fichero << "\"" << endl;
        cout << endl;
        mostrarFicheros(fichero);
        fichero=construirNombreFicheroUsos(fichero);
        f.open(fichero);
    }
    cout << "El fichero \"" << fichero << "\" existe y ha sido seleccionado." << endl;
    f.close();
}

/*
 * Pre:  El valor del parámetro «rangoEdad» es uno de los valores válidos según la regla 
 *       <rango-edad> establecida en el enunciado ("<=25", "26-35", "36-50", "51-65" o ">65")
 * Post: Devuelve, dependiendo del valor del parámetro «rangoEdad»
 *       ("<=25", "26-35", "36-50", "51-65" o ">65"), respectivamente, 0, 1, 2, 3 o 4.
 */
void palabraAux(const string orden, string& fraseAux, unsigned& numAux){
    if(orden=="USUARIO"){
        cin >> numAux;
    }
    else if(orden=="MAYORES"){
        cin >> numAux;
    }
    else if(orden=="INFORME"){
        cin >> fraseAux;
    }
}

void cadenaEnMayusculas(string& frase){
    for(unsigned i=0; i<frase.length(); i++){
        frase[i]=toupper(frase[i]);
    }
}

void mostrarAyuda(){
    ifstream f;
    f.open(FICHERO_AYUDA);
    if(f.is_open()){
        string linea;
        escribirCadaLinea(f,linea);
        f.close();
    }
    else{
        cerr << "No se ha podido acceder a \"" << FICHERO_AYUDA << "\" ." << endl;
    }
}

void seleccionarOrden(string& orden, string& fraseAux, unsigned& numAux){
    cout << endl;
    cout << "Orden: ";
    cin >> orden;
    string ignorar;
    cadenaEnMayusculas(orden);
    palabraAux(orden,fraseAux,numAux);
    getline(cin,ignorar);
}

void ejecutarUsos(const string fichero){
    cout << "Fichero de usos seleccionado actualmente: " << fichero << endl;
    unsigned traslados=0, circulares=0;
    contarUsos(fichero,traslados,circulares);
    cout << "Número de usos como traslado:" << setw(9) << right << traslados << endl;
    cout << "Número de usos circulares:" << setw(12) << right << circulares << endl;
    cout << "Número total de usos:" << setw(17) << right << traslados+circulares << endl;
}

void ejecutarEstadisticas(){
    unsigned estadisticas[NUM_EDADES][NUM_GENEROS];
    for(unsigned i=0; i<NUM_EDADES; i++){
        for(unsigned j=0; j<NUM_GENEROS; j++){
            estadisticas[i][j]=0;
        }
    }
    if(obtenerEstadisticas(FICHERO_USUARIOS,estadisticas)){
        cout << "Distribución de los usuarios" << endl;
        cout << setw(7) << "|" << setw(5) << "M" << setw(8) << "F" << setw(3) << endl;
        cout <<  setfill('-') << setw(7) << '+'  << "----------------" << endl;
        for(unsigned i=0; i<NUM_EDADES; i++){
            cout << setfill(' ') << left << setw(6) << RANGO_EDADES[i] << '|' << right 
                << setw(6) << estadisticas[i][0] << setw(8) << estadisticas[i][1] << endl;
        }
    }
}

void ejecutarUsuario(const unsigned numAux){
    string genero, edad;
    if(buscarUsuario(FICHERO_USUARIOS,numAux,genero,edad)){
        if(genero=="M"){
            cout << "El usuario " << numAux;
        }
        else if (genero=="F"){
            cout << "La usuaria " << numAux;
        }
        else{
            cout << "El/la usuario/a " << numAux;
        }
        cout << " está en el rango de edad " << "\"" << edad << "\"." << endl;
    }
    else{
        cout << "El/la usuario/a " << numAux << " no aparece en el fichero \"" << FICHERO_USUARIOS << "\"." << endl;
    }
    
}

void ejecutarMayores(const unsigned numAux, const string fichero){
    cout << endl;
    UsosUsuario usuarios[23111];
    for(unsigned i=0; i<23111; i++){
        usuarios[i].usosDistEstacion=0;
        usuarios[i].usosMismaEstacion=0;
    }
    unsigned numUsuarios;
    if(obtenerUsosPorUsuario(fichero,usuarios,numUsuarios)){
        cout << "Número usuarios distintos: " << numUsuarios << endl;
        cout << endl;
        ordenar(usuarios,numUsuarios,numAux);
        cout << setw(9) << "Usuario" << " " << "Traslados" << setw(10) << "Circular" << setw(10) << "Total" << endl;
        for(unsigned i=0; i<4; i++){
            cout << setfill('=') << setw(10) << " ";
        }
        cout << endl;
        unsigned cont=0;
        while( cont<numAux && cont<numUsuarios){
            cout << setfill(' ') << setw(9) << usuarios[cont].idUsuario << setw(10) << usuarios[cont].usosDistEstacion 
                << setw(10) << usuarios[cont].usosMismaEstacion << setw(10) << numUsosTotales(usuarios[cont]) << endl;
            cont++;
        }
    }
    
}

void ejecutarInforme(const string fichero, const string fraseAux){
    Estacion estaciones[NUM_ESTACIONES];
    if(leerEstaciones(FICHERO_ESTACIONES,estaciones)){
        if(contarUsosEstaciones(fichero,estaciones)){
            ordenarPorUso(estaciones);
            if(escribirInformeEstaciones(fraseAux,estaciones)){
                cout << "Informe \"" << fraseAux << "\" generado correctamente." << endl;
            }
        }
    }
}

void ejecutarDestinos(const string fichero){
    cout << "Escriba el nombre del fichero del informe" << endl;
    cout << "(presione solo ENTRAR para escribirlo en la pantalla): ";
    string ficheroDestinos;
    getline(cin,ficheroDestinos);
    Estacion estaciones[NUM_ESTACIONES];
    if(leerEstaciones(FICHERO_ESTACIONES,estaciones)){
        unsigned viajes[NUM_ESTACIONES][NUM_ESTACIONES], destinosFrecuentes[NUM_ESTACIONES];
        if(contarUsosEstaciones(fichero, estaciones)){
            calcularDestinosMasFrecuentes(viajes, destinosFrecuentes);
            if(ficheroDestinos==""){
                cout << endl;    
                escribirInformeDestinos(cout,viajes,destinosFrecuentes,estaciones);
            }
            else{
                ofstream f;
                f.open(ficheroDestinos);
                if(f.is_open()){
                    escribirInformeDestinos(f,viajes,destinosFrecuentes,estaciones);
                    f.close();
                    cout << "Informe \"" << ficheroDestinos << "\" creado correctamente." << endl;
                }
                else{
                    cerr << "No se ha podido crear el fichero \"" << ficheroDestinos << "\"." << endl; 
                }
            }
        }
    }
}

void ejecutarOrden(const string orden, const string fraseAux, const unsigned numAux, string& fichero){
    if(orden=="AYUDA"){
        cout << endl;
        mostrarAyuda();
    }
    else if(orden=="FICHERO"){
        presentarFicheros(fichero);
    }
    else if(orden=="USOS"){
        ejecutarUsos(fichero);
    }
    else if(orden=="ESTADISTICAS"){
        ejecutarEstadisticas();
    }
    else if(orden=="USUARIO"){
        ejecutarUsuario(numAux);
    }
    else if(orden=="MAYORES"){
        ejecutarMayores(numAux,fichero);
    }
    else if(orden=="INFORME"){
        ejecutarInforme(fichero,fraseAux);
    }
    else if(orden=="DESTINOS"){
        ejecutarDestinos(fichero);
    }
}

void presentarOrdenes(string& orden, string& fraseAux, unsigned& numAux, string& fichero){
    cout << endl;
    mostrarAyuda();
    seleccionarOrden(orden,fraseAux,numAux);
    while(orden!="FIN"){
        if(orden=="AYUDA" || orden=="FICHERO" || orden=="USOS" || orden=="ESTADISTICAS" || orden=="USUARIO"
                || orden=="MAYORES" || orden=="INFORME" || orden=="DESTINOS"){
            ejecutarOrden(orden,fraseAux,numAux,fichero);

        }
        else{
            cerr << "Orden " << orden << " desconocida" << endl;
        }
        seleccionarOrden(orden,fraseAux,numAux);
    }
        
}


int main(){
    string fichero,orden,fraseAux;
    unsigned numAux;
    presentarFicheros(fichero);
    presentarOrdenes(orden,fraseAux,numAux,fichero);
    return 0;
}
