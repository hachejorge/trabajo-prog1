/*********************************************************************************************\
 * Programación 1. Trabajo obligatorio
 * Autores: ¡¡¡PONED AQUÍ VUESTROS NOMBRES!!!
 * Ultima revisión: ¡¡¡!!!
 * Resumen: Fichero de implementación «estacion.hpp» de un módulo para trabajar con
 *          registros que representan estaciones del sistema Bizi Zaragoza.
 * Codificación de caracteres original de este fichero: UTF-8 con BOM
\*********************************************************************************************/

#include "estacion.hpp"
#include "uso.hpp"

/*
 * Pre:  La cadena de caracteres «nombreFicheroEstaciones» contiene la ruta de acceso y nombre
 *       de un fichero de estaciones Bizi que sigue la sintaxis de la regla
 *       <fichero-estaciones> establecida en el enunciado y que contiene información de
 *       «NUM_ESTACIONES» estaciones.
 *       El vector «estaciones» tiene «NUM_ESTACIONES» componentes.
 * Post: Si el fichero «nombreFicheroEstaciones» y se puede leer de él, la función devuelve
 *       «true» y lee los datos de las estaciones Bizi contenidos en el fichero indicado por
 *       «nombreFicheroEstaciones» y se han almacenado en el vector «estaciones» de forma tal
 *       que en cada componente «i» se almacena el identificador y el nombre de la estación de
 *       identificador «i» + 1 (es decir, en estaciones[0] se encuentra almacenada la
 *       información de la estación con identificador 1, en estaciones[1] se encuentra
 *       almacenada la estación con identificador 2 y así sucesivamente). La información sobre
 *       el número de usos de cada estación es 0 en todas ellas. Si no se puede leer el
 *       fichero «nombreFicheroEstaciones», se limita a devolver «false».
 */
bool leerEstaciones(const string nombreFicheroEstaciones, Estacion estaciones[]){
    ifstream f;
    f.open(nombreFicheroEstaciones);
    if(f.is_open()){
        string ignorar;
        getline(f,ignorar); // Se lee la cabecera
        for(unsigned i = 0; i < NUM_ESTACIONES; i++){ // Repetimos el proceso NUM_ESTACIONES veces
            unsigned idAux;
            getline(f,ignorar,'-');  
            getline(f,ignorar,'-'); 
            getline(f,ignorar,'/'); // Igonoramos hasta llegar a la id
            f >> idAux;
            estaciones[idAux-1].id=idAux; // Lo asignamos a la componente id-1
            f.ignore();
            f.ignore();
            getline(f,ignorar,';');
            f.ignore(); // Igonoramos hasta llegar al nombre de la estacion
            getline(f,estaciones[idAux-1].nombre,'"');
            getline(f,ignorar);
        }
        f.close();
        return true;
    }
    else{
        cerr << "No se ha podido abrir el fichero \"" << nombreFicheroEstaciones << "\"." << endl;
        return false;
    }
}


/*
 * Pre:  La cadena «nombreFicheroUsos» representa la ruta de acceso y el nombre de un
 *       fichero de texto con el formato de usos del sistema Bizi establecido en el enunciado.
 *       El vector «estaciones» tiene «NUM_ESTACIONES» componentes que almacenan información
 *       sobre estaciones Bizi de forma tal que en cada componente «i» se almacena la
 *       información de la estación de identificador «i» + 1 (es decir, en estaciones[0] se
 *       encuentra almacenada la información de la estación con identificador 1, en
 *       estaciones[1] se encuentra almacenada la estación con identificador 2 y así
 *       sucesivamente). La información sobre el número de usos de cada estación es 0 en todas
 *       ellas.
 * Post: Si no hay problemas de lectura del fichero «nombreFicheroUsos», la función devuelve
 *       «true» y actualiza el número de usos de cada estación del vector «estaciones» de
 *       acuerdo con el contenido del fichero «nombreFicheroUsos», contabilizando como un uso
 *       tanto la retirada como la devolución de bicicletas. En caso contrario, se limita a
 *       devolver «false».
 */
bool contarUsosEstaciones(const string nombreFicheroUsos, Estacion estaciones[]){
    ifstream f;
    f.open(nombreFicheroUsos);
    if(f.is_open()){
        string cabecera;
        getline(f,cabecera);
        UsoBizi uso;
        while(leerUso(f,uso)){
            estaciones[uso.idRetiro-1].usos++;
            estaciones[uso.idAnclaje-1].usos++;
        }
        f.close();
        return true;
    }
    else{
        cerr << "No se ha podido abrir el fichero \"" << nombreFicheroUsos << "\"." << endl;
        return false;
    }    
}

void permutar(Estacion& a, Estacion& b){
    Estacion aux;
    aux=a;
    a=b;
    b=aux;
}

/*
 * Pre:  El vector «estaciones» tiene «NUM_ESTACIONES» componentes.
 * Post: El contenido del vector «estaciones» es una permutación del contenido inicial del
 *       mismo que está ahora ordenado de mayor a menor número de usos de las estaciones.
 */
void ordenarPorUso(Estacion estaciones[]){
    for(unsigned i = 0; i < NUM_ESTACIONES; i++){
        unsigned iMayor=i;
        for(unsigned j = 0; j < NUM_ESTACIONES; j++){
            if(estaciones[j].usos < estaciones[iMayor].usos){
                iMayor=j;
            }
            permutar(estaciones[i],estaciones[iMayor]);
        }
    }
}


/*
 * Pre:  ---
 * Post: Si la función puede crear un fichero de texto cuyo nombre es el contenido de la cadena
 *       de caracteres «nombreFichero», la función devuelve «true» y escribe en el fichero
 *       creado la siguiente información sobre cada estación almacenada en el vector
 *       «estaciones»: puesto, número de usos, identificador de la estación y
 *       nombre, con un formato similar al siguiente:
 *
 *           Puesto    Usos  Id Nombre
 *           ------ ------- --- --------------------------------------------------
 *                1   47064  16 Plaza España
 *                2   42306  67 Avda. G. Gómez de Avellaneda - C/ Clara Campoamor
 *                3   40251  47 Plaza San Francisco - Universidad
 *           ...
 */
bool escribirInformeEstaciones(const string nombreFichero, const Estacion estaciones[]){
    ofstream f;
    f.open(nombreFichero);
    if(f.is_open()){
        f << "Puesto" << setw(8) << "Usos" << setw(4) << "Id" << " Nombre" << endl;
        f << setfill('-') << setw(7) << " " << setw(8) << " " << setw(4) << " " 
            << setw(51) << " " << setfill(' ') << endl;
        for(unsigned i = 0; i < NUM_ESTACIONES; i++){
            f << setw(6) << i+1 << setw(8) << estaciones[i].usos << setw(4) 
                << estaciones[i].id << " " << estaciones[i].nombre << endl;
        } 
        f.close();
        return true;
    }
    else{
        cerr << "No se ha podido crear el fichero \"" << nombreFichero << "\"." << endl;
        return false;
    }
}


/*
 * Pre:  La cadena «nombreFicheroUsos» representa la ruta de acceso y el nombre de un
 *       fichero de texto con el formato de usos del sistema Bizi establecido en el enunciado.
 *       La matriz «viajes» tiene «NUM_ESTACIONES» filas de «NUM_ESTACIONES» columnas cada una.
 * Post: Si no hay problemas de lectura del fichero «nombreFicheroUsos», la función devuelve
 *       «true» y asigna a cada componente de la matriz «viajes» valores de forma que la
 *       componente viajes[i][j] contiene el número de viajes que en dicho fichero aparece un
 *       uso que tiene como origen la estación de código «i» + 1 y como destino la estación de
 *       código «j» + 1. En caso contrario, se limita a devolver «false».
 */
bool contarViajesOrigenDestino(const string nombreFicheroUsos, 
                               unsigned viajes[][NUM_ESTACIONES]){
    ifstream f;
    f.open(nombreFicheroUsos);
    if(f.is_open()){
        for(unsigned i = 0; i < NUM_ESTACIONES; i++){
            for(unsigned j = 0; j < NUM_ESTACIONES; j++){
                viajes[i][j]=0;
            }
        }
        string cabecera;
        getline(f,cabecera);
        UsoBizi uso;
        while(leerUso(f,uso)){
            viajes[uso.idRetiro-1][uso.idAnclaje-1]++;
        }
        f.close();
        return true;
    }
    else{
        cerr << "No se ha podido abrir el fichero \"" << nombreFicheroUsos << "\"." << endl;
        return false;
    }  
}


/*
 * Pre:  La matriz «viajes» tiene «NUM_ESTACIONES» filas de «NUM_ESTACIONES» columnas cada una.
 *       Cada componente viajes[i][j] contiene un valor que representa el número de usos
 *       que tienen como origen la estación de código «i» + 1 y como destino la estación de
 *       código «j» + 1. El vector «destinosMasFrecuentes» tiene «NUM_ESTACIONES» componentes.
 * Post: Asigna a cada componente destinosMasFrecuentes[i] el índice j de la fila viajes[i] de
 *       valor máximo. Es decir, asigna a destinosMasFrecuentes[0] el índice de la columna
 *       donde se encuentra el mayor valor de entre viajes[0][0], viajes[0][1], ... y 
 *       viajes[0][NUM_ESTACIONES-1]; asigna a destinosMasFrecuentes[1] el índice de la columna
 *       donde se encuentra el mayor valor de entre viajes[1][0], viajes[1][1], ... y 
 *       viajes[1][NUM_ESTACIONES-1] y así sucesivamente.
 */
void calcularDestinosMasFrecuentes(const unsigned viajes[][NUM_ESTACIONES],
                                   unsigned destinosMasFrecuentes[]){
    for(unsigned i = 0; i < NUM_ESTACIONES; i++){
        unsigned iMayor=0;
        for(unsigned j = 0; j < NUM_ESTACIONES; j++){
            if(viajes[j][iMayor] < viajes[j][j+1]){
                iMayor = j + 1;
            }
        }
        destinosMasFrecuentes[i]=iMayor;
    }
}

/*
 * Pre:  El flujo de escritura «f» ya está asociado con un dispositivo (ya sea fichero o
 *       pantalla) y se puede escribir en él. La matriz «viajes» tiene «NUM_ESTACIONES» filas
 *       de «NUM_ESTACIONES» columnas cada una. Cada componente viajes[i][j] contiene un valor
 *       que representa el número de usos que tienen como origen la estación de código «i» + 1
 *       y como destino la estación de código «j» + 1. El vector «destinosMasFrecuentes» tiene
 *       «NUM_ESTACIONES» componentes, donde cada componente destinosMasFrecuentes[i] el índice
 *       j de la fila viajes[i] de valor máximo.
 * Post: Escribe en el flujo f un informe donde se muestra, para cada estación del sistema, la
 *       estación que mayor número de viajes es destino de los viajes que parten de la primera.
 *       El informe está ordenado por identificadores crecientes de estación de origen y tiene
 *       el formato establecido en el enunciado.
 */
void escribirInformeDestinos(ostream& f, const unsigned viajes[][NUM_ESTACIONES], 
                             const unsigned destinosMasFrecuentes[], const Estacion estaciones[]){
    f << "Viajes Origen --> Destino" << endl;
    f << "--------------------------------------------------------------------------------------------------------" << endl;
    for(unsigned i = 0; i < NUM_ESTACIONES; i++){
    f << setw(4) << viajes[i+1][destinosMasFrecuentes[i]] << setw(5) << estaciones[i].id << '-' << 
        estaciones[i].nombre << "  -->  " << estaciones[destinosMasFrecuentes[i]].id << '-' <<
        estaciones[destinosMasFrecuentes[i]].nombre << endl;
    }
}
