// Examen 2 progra Isaac Munoz.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <set>
#include <algorithm> // para std::transform y std::tolower / std::toupper
using namespace std;

class Candidato {
public:
    string nombre;
    string partido;
    char plataforma[100];
    int votos;

    Candidato() : votos(0) {}
};

class Votante {
public:
    string nombre;
    int cedula;
    bool haVotado;

    Votante() : haVotado(false) {}

    void votar(Candidato candidatos[], int cantidadCandidatos, set<int>& votantesQueHanVotado) {
        if (haVotado) {
            cout << "El votante ya ha votado." << endl;
            return;
        }

        string nombreCandidato;
        cout << "Digite el nombre del candidato a votar: ";
        cin.ignore();  //limpiar antes de leer una linea 
        getline(cin, nombreCandidato);

        // poder usar minuscular y mayusculas 
        transform(nombreCandidato.begin(), nombreCandidato.end(), nombreCandidato.begin(), ::tolower);

        for (int i = 0; i < cantidadCandidatos; i++) {
            string nombreCandidatoActual = candidatos[i].nombre;
            transform(nombreCandidatoActual.begin(), nombreCandidatoActual.end(), nombreCandidatoActual.begin(), ::tolower);

            if (nombreCandidatoActual == nombreCandidato) {
                candidatos[i].votos++;
                haVotado = true;
                votantesQueHanVotado.insert(cedula); // Registrar que el votante voto 
                cout << "Voto registrado para " << candidatos[i].nombre << endl;
                return;
            }
        }
        cout << "Candidato no encontrado." << endl;
    }
};

int main() {
    Votante votantes[100];
    Candidato candidatos[10];
    int cantidadVotantes = 0;
    int cantidadCandidatos = 0;
    int menu = 0;
    set<int> votantesQueHanVotado; // registro de los votantes que ya votaron
    while (menu != 4) {
        cout << "1. Registrar votante y votar" << endl;
        cout << "2. Registrar candidato" << endl;
        cout << "3. Ver votaciones y resultados" << endl;
        cout << "4. Salir" << endl;
        cout << "\n"; // meter otro salto de linea
        cout << "Digite una opcion: ";
        cin >> menu;

        if (menu == 1) {
            if (cantidadVotantes < 100) {
                Votante nuevoVotante;
                cout << "Digite el nombre del votante: ";
                cin.ignore(); // limpiar antes de que lea la línea
                getline(cin, nuevoVotante.nombre);
                cout << "Digite la cedula del votante: ";
                cin >> nuevoVotante.cedula;

                // Verificar si el votante ya estas registrado
                bool yaRegistrado = false;
                for (int i = 0; i < cantidadVotantes; i++) {
                    if (votantes[i].cedula == nuevoVotante.cedula) {
                        cout << "El votante ya esta registrado." << endl;
                        yaRegistrado = true;
                        break;
                    }
                }

                if (!yaRegistrado) {
                    votantes[cantidadVotantes++] = nuevoVotante;
                    nuevoVotante.votar(candidatos, cantidadCandidatos, votantesQueHanVotado);
                }
            }
            else {
                cout << "No se pueden registrar mas votantes." << endl;
            }
        }
        else if (menu == 2) {
            if (cantidadCandidatos < 10) {
                Candidato nuevoCandidato;
                cout << "Digite el nombre del candidato: ";
                cin.ignore(); // limpiar antes de leer la linea 
                getline(cin, nuevoCandidato.nombre);
                cout << "Digite el partido del candidato: ";
                getline(cin, nuevoCandidato.partido);
                cout << "Digite la plataforma del candidato: ";
                cin.getline(nuevoCandidato.plataforma, 100);
                candidatos[cantidadCandidatos++] = nuevoCandidato;
                cout << "Candidato registrado exitosamente." << endl;
            }
            else {
                cout << "No se pueden registrar mas candidatos." << endl;
            }
        }
        else if (menu == 3) {
            int totalVotos = 0;
            for (int i = 0; i < cantidadCandidatos; i++) {
                totalVotos += candidatos[i].votos;
            }

            cout << "Resultados de la elección:" << endl;
            for (int i = 0; i < cantidadCandidatos; i++) {
                double porcentaje = (totalVotos > 0) ? (double)candidatos[i].votos / totalVotos * 100 : 0;
                cout << "Candidato: " << candidatos[i].nombre << endl;
                << ", Votos: " << candidatos[i].votos << endl;
                << ", Porcentaje: " << porcentaje << "%" << endl;
            }

            if (totalVotos > 0) {
                Candidato ganador = candidatos[0];
                for (int i = 1; i < cantidadCandidatos; i++) {
                    if (candidatos[i].votos > ganador.votos) {
                        ganador = candidatos[i];
                    }
                }
                cout << "Ganador: " << ganador.nombre
                    << " con " << ganador.votos << " votos." << endl;
            }
            else {
                cout << "No se han registrado votos." << endl;
            }
        }
        else if (menu == 4) {
            cout << "Hasta Luego, Gracias por votar." << endl;
        }
        else {
            cout << "Opcion no valida." << endl;
        }
        cout << endl;
    }

    return 0;
}
