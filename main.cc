#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

//DESC: Funció per a entrar pistes.
//PRE: Entren enters que determinen la mida dels blocs, desprès la mesura de les pistes.
//POST: Surt la matriu de pistes
vector<vector<int>> entradaPistes(int n) {
    vector<vector<int>> pistes(n); // Declaració del vector de pistes
    for (int i = 0; i < n ; ++i) {
        int blocs;
        cin >> blocs; // Entrada de blocs
        pistes[i].resize(blocs); // Remodelació del vector posterior a l'entrada
        for (int j = 0; j < blocs ;++j) {
            cin >> pistes[i][j];
        }
    }
    return pistes;
}

//DESC: Funció per a mostrar el tauler del nanograma.
//PRE: 
//POST: 
void mostrarTauler(const vector<vector<char>>& tauler, const vector<vector<int>>& pistesFiles, const vector<vector<int>>& pistesColumnes) {
    int files = tauler.size();
    int columnes = tauler[0].size();

    // Mostra la numeració de les columnes del tauler
    cout << "    ";
    for (int j = 1; j <= columnes; ++j) {
        cout << setw(2) << j << " ";
    }
    cout << endl;

    // Linea separadora superior del tauler
    cout << "    ";
    for (int j = 1; j <= columnes; ++j) {
        cout << "---";
    }
    cout << "-" << endl;

    // Mostrar la numeració de les pistes de la part dreta de les files
    for (int i = 0; i < files; ++i) {
        cout << setw(2) << (i + 1) << " |"; // Numeración de files
        for (int j = 0; j < columnes; ++j) {
            cout << " " << tauler[i][j] << " ";
        }
        cout << "| ";
        for (int p : pistesFiles[i]) { // Mostrar pistes de files
            cout << p << " ";
        }
        cout << endl;
    }

    // Mostrar linea separadora inferior del tauler
    cout << "    ";
    for (int j = 1; j <= columnes; ++j) {
        cout << "---";
    }
    cout << "-" << endl;

    // Mostrar les pistes de columnes sota el tauler
    int maxpistesCol = 0;
    for (const auto& pista : pistesColumnes) {
        maxpistesCol = max(maxpistesCol, (int)pista.size());
    }

    for (int i = 0; i < maxpistesCol; ++i) {
        cout << "    ";
        for (int j = 0; j < columnes; ++j) {
            int sizepistesCol=pistesColumnes[j].size();
            if (sizepistesCol > i) {
                cout << setw(2) << pistesColumnes[j][i] << " ";
            } else {
                cout << "   ";
            }
        }
        cout << endl;
    }
}

int main() {

    /*APARTAT 1 de FUNCIONAMENT - LECTURA DE DADES*/

    // Llegir el tamany del tauler.
    int files, columnes;
    cin >> files >> columnes;

    // Llegir l'entrada de les pistes de les files i de columnes.
    vector<vector<int>> pistesFiles = entradaPistes(files);
    vector<vector<int>> pistesColumnes = entradaPistes(columnes);

    /*APARTAT 2 de FUNCIONAMENT - MOSTRAR EL TAULER INICIAL*/

    // Crear el tauler buit i guardar l'estat inicial.
    vector<vector<char>> tauler(files, vector<char>(columnes, '.'));
    vector<vector<char>> taulerInicial = tauler;

    // Mostrar el tauler inicial.
    mostrarTauler(tauler, pistesFiles, pistesColumnes);

    /*APARTAT 3 de FUNCIONAMENT - SWITCH D'OPCIONS PER INTERACTUAR AMB EL JOC*/

    char opc;
    int fila1, fila2, columna1, columna2;

    bool continuar=true;
    
    // Mostrar el menu d'opcions
    cout << "\nA - Marcar fila i columna." << endl;
    cout << "B - Marcar caselles." << endl;
    cout << "E - Desmarcar fila i columna." << endl;
    cout << "F - Desmarcar caselles." << endl;
    cout << "R - Restaurar el tauler." << endl;
    cout << "S - Estat del tauler.." << endl;
    cout << "Z - Sortir del joc." << endl;

    cout << "Opcio: ";
    
    while(continuar){
		cin >> opc;
        cout << endl;
		// Marcar fila columna - OPCIÓ A
		if (opc == 'A') {
			cin >> fila1 >> columna1;
            tauler[fila1 - 1][columna1 - 1] = 'X'; // Marcar una casella
		}
        // Marcar conjunt de caselles - OPCIÓ B
        else if (opc == 'B') {
			cin >> fila1 >> columna2 >> fila2 >> columna2;
            // Funcion para marcar area de caselles - PER FER!
		}   
        // Desmarcar fila i columna - OPCIÓ E
        else if (opc == 'E') {
			cin >> fila1 >> columna1;
            tauler[fila1 - 1][columna1 - 1] = '.'; // Marcar una casella
		}
        // Desmarcar conjunt de caselles - OPCIÓ F
        else if (opc == 'F') {
			cin >> fila1 >> columna2 >> fila2 >> columna2;
            // Funcion para marcar area de caselles - PER FER!
		}
        // Restaurar el tauler - OPCIÓ R
        else if (opc == 'R') {
			tauler = taulerInicial; // Iguala el tauler al tauler inicial
            cout << endl;
		}
        // Estat del tauler - OPCIÓ S
        else if (opc == 'S') {
			mostrarTauler(tauler, pistesFiles, pistesColumnes);
            cout << endl;
        }
        // Sortir del programa - OPCIÓ Z
        else if (opc == 'Z') {
			cout << "Has sortit del joc. Fins aviat!" << endl;
            continuar=false;
		} else {
			cout << "Opcio no vàlida!" << endl;
		}       
	}


    /*APARTAT 4 de FUNCIONAMENT - FINALITZACIÓ DEL JOC*/

    return 0;
}
