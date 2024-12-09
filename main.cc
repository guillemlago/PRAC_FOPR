#include <iostream>
#include <vector>
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

//DESC: Marcar amb X caselles en un rectangle delimitat per l'usuari.
//PRE: Entra la situació del tauler, la fila i columna de inici del rectangle i la fila i columna del final del rectangle.
//POST: Posa X totes les posicions dins del rectangle.
/*void marcarCaselles(vector<vector<char>>& tauler, int fila1, int columna1, int fila2, int columna2){
	int filaInici, filaFi, columnaInici, columnaFi;
	filaInici = fila1;
	filaFi = fila2;
	columnaInici = columna1;
	columnaFi = columna2;
	for(int i=filaInici;i<filaFi;++i){
		for(int j=columnaInici;i<columnaFi;++j){
			tauler[i - 1][j - 1] = 'X';
		}
	}
}*/

//DESC: Desmarcar amb . caselles en un rectangle delimitat per l'usuari.
//PRE: Entra la situació del tauler, la fila i columna de inici del rectangle i la fila i columna del final del rectangle.
//POST: Posa . totes les posicions dins del rectangle.
/*void desmarcarCaselles(vector<vector<char>>& tauler, int fila1, int columna1, int fila2, int columna2){
	int filaInici, filaFi, columnaInici, columnaFi;
	filaInici = fila1;
	filaFi = fila2;
	columnaInici = columna1;
	columnaFi = columna2;
	for(int i=filaInici;i<filaFi;++i){
		for(int j=columnaInici;i<columnaFi;++j){
			tauler[i - 1][j - 1] = '.';
		}
	}
}*/

//DESC: Funció per a mostrar el tauler del nanograma.
//PRE: 
//POST: 
void mostrarTauler(const vector<vector<char>>& tauler, const vector<vector<int>>& pistesFiles, const vector<vector<int>>& pistesColumnes) {
    int files = tauler.size();
    int columnes = tauler[0].size();

    // Mostra la numeració de les columnes del tauler
    cout << "    ";
    for (int j = 1; j <= columnes; ++j) {
        cout << " " << j << " ";
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
		if(i<9) {
			cout << " ";
		}
        cout << (i + 1) << " |"; // Numeración de files
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
                cout << " " << pistesColumnes[j][i] << " ";
            } else {
                cout << "   ";
            }
        }
        cout << endl;
    }
}

//DESC: Funció agafa sequencia (fila o columna) i un vector pista (tant pot ser del vector pistesFiles com del pistesColumnes)
//PRE: entren el vector sequencia actual i el vector pistes seleccionat.
//POST: surt un bool dient si la sequencia anterior és solució o no
bool validaSequencia(const vector<char>& sequencia, const vector<int>& pista){
	vector<int> blocs;
	int contador = 0;
	//Esquema recorregut, comprovem tot.
	for(char celda : sequencia){
		//Inv: Els elements de la sequencia vists fins ara han estat tractats i afegits al vector blocs.
		if(celda == 'X'){
			contador++; //Si celda de la sequencia ha estat seleccionada i element anterior no, es suma contador
		}
		else if(contador > 0){
			//Com en aquest cas celda != X; el bloc anterior es afegit al vector blocs i es reinicia el comptador.
			blocs.push_back(contador);
			contador = 0;
		}
	}
	
	if(contador > 0){
		blocs.push_back(contador);
	}
	
	return blocs == pista; //Bool. Si tots dos vectors son iguals, la seqüència és vàlida!
}

//DESC: Funció comprova si la matriu tauler és solució segons matrius pistesFiles i pistesColumnes. Empra funció anterior "validaSequencia" iterant fila per fila i columna per columna.
//PRE: Entren una matriu tauler actual entrat per l'usuari, la matriu pistesFiles i pistesColumnes.
//POST: Surt un bool que determina si la matriu és solució o no.
bool validaNanograma(const vector<vector<char>>& tauler,const vector<vector<int>>& pistesFiles, const vector<vector<int>>& pistesColumnes) {
	int files = tauler.size();
	int columnes = tauler[0].size();
	bool parar = false; 
	bool resultat = false;
	int i = 0, j = 0;
	
	while(i < files and !parar){ // Validació de les files
		//Inv: 'i' fa referència a l'índex de la filera actual. Totes les fileres passades fins ara son vàlides.
		if (!validaSequencia(tauler[i], pistesFiles[i])) {
			parar = true;
        }
        ++i;
	}

	while(j < columnes and !parar){
		//Inv: 'j' fa referència a la columna actual. Totes les columnes passades fins ara són vàlides.
		//Posem en vector tots els elements de la columna per validar amb validaSequencia. ESQUEMA RECORREGUT.
		vector<char> columna;
        for (int i = 0; i < files; ++i) {
        	//Tots els elements fins ara de la columna 'j' han estat afegits a vector columna.
		columna.push_back(tauler[i][j]);
        }
        	
        if(!validaSequencia(columna, pistesColumnes[j])){
			parar = true;
        }
		++j;
	}
	
	if(!parar){
		resultat = true;
	}
	parar = true; // És vàlid si totes les files i columnes compleixen
	return resultat;
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
    int moviments = 0;
    
    // Mostrar el menu d'opcions
    cout << "\nA - Marcar fila i columna." << endl;
    cout << "B - Marcar caselles." << endl;
    cout << "E - Desmarcar fila i columna." << endl;
    cout << "F - Desmarcar caselles." << endl;
    cout << "R - Restaurar el tauler." << endl;
    cout << "S - Estat del tauler." << endl;
    cout << "Z - Sortir del joc." << endl;

    cout << "Opcio: ";
    
	while(continuar){

		cin >> opc;
        	cout << endl;
		// Marcar fila columna - OPCIÓ A
		if (opc == 'A') {
			cin >> fila1 >> columna1;
            tauler[fila1 - 1][columna1 - 1] = 'X'; // Marcar una casella
            moviments++;
		}
		
        // Marcar conjunt de caselles - OPCIÓ B
        else if (opc == 'B') {
			cin >> fila1 >> columna2 >> fila2 >> columna2;
			moviments++;
            //marcarCaselles(tauler, fila1 - 1, columna1 - 1, fila2 - 1, columna2 - 1);
            int filaInici, filaFi, columnaInici, columnaFi;
			filaInici = fila1;
			filaFi = fila2;
			columnaInici = columna1;
			columnaFi = columna2;
			for(int i = filaInici; i < filaFi; ++i){
				for(int j = columnaInici; j < columnaFi; ++j){
					tauler[i - 1][j - 1] = 'X';
				}
			}
		}   
        
        // Desmarcar fila i columna - OPCIÓ E
        else if (opc == 'E') {
			cin >> fila1 >> columna1;
            tauler[fila1 - 1][columna1 - 1] = '.'; // Marcar una casella
            moviments++;
		}
        	
        // Desmarcar conjunt de caselles - OPCIÓ F
        else if (opc == 'F') {
			cin >> fila1 >> columna2 >> fila2 >> columna2;
			moviments++;
			//desmarcarCaselles(tauler, fila1 - 1, columna1 - 1, fila2 - 1, columna2 - 1);
			int filaInici, filaFi, columnaInici, columnaFi;
			filaInici = fila1;
			filaFi = fila2;
			columnaInici = columna1;
			columnaFi = columna2;
			for(int i = filaInici; i < filaFi; ++i){
				for(int j = columnaInici; j < columnaFi; ++j){
					tauler[i - 1][j - 1] = '.';
				}
			}
		}
        
        // Restaurar el tauler - OPCIÓ R
        else if (opc == 'R') {
			tauler = taulerInicial; // Iguala el tauler al tauler inicial
			moviments = 0;
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
			cout << "Moviments: " << moviments << endl;
            continuar=false;
            
		} else {
			cout << "Opcio no vàlida!" << endl;
		}  
		
		/*APARTAT 4 de FUNCIONAMENT - FINALITZACIÓ DEL JOC*/
    	
		if(validaNanograma(tauler, pistesFiles, pistesColumnes)){
			mostrarTauler(tauler, pistesFiles, pistesColumnes);
			cout << "Has guanyat!" << endl;
			cout << "Moviments: " << moviments << endl;
			continuar = false;
		}
	     
	}
	
}
