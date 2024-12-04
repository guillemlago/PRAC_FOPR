#include <iostream>
#include <vector>
using namespace std;
//ESTE DOCUMENTO TESTEA AMBAS FUNCIONES Y AMBAS FUNCIONAN NO SE QUE COÑO PASA COLEGA
bool validaSequencia(const vector<char>& sequencia, const vector<int>& pista){
	vector<int> blocs;
	int contador = 0;
	
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
	
	return blocs == pista; //Si tots dos vectors son iguals, la seqüència és vàlida!
}


bool validaNanograma(const vector<vector<char>>& tauler,const vector<vector<int>>& pistesFiles, const vector<vector<int>>& pistesColumnes) {
	int files = tauler.size();
	int columnes = tauler[0].size();
	bool parar = false; 
	bool resultat = false;
	
	while(!parar){
		// Validació de les files
		for (int i = 0; i < files; ++i) {
			//Inv: 'i' fa referència a la filera actual. Totes les fileres passades fins ara son vàlides.
        		if (!validaSequencia(tauler[i], pistesFiles[i])) {
            			parar = true;
        		}
    		}	

		// Validació de les columnes
    		for (int j = 0; j < columnes; ++j) {
    			//Inv: 'j' fa referència a la columna actual. Totes les columnes passades fins ara són vàlides.
    			//Posem en vector tots els elements de la columna per validar amb validaSequencia
        		vector<char> columna;
        		for (int i = 0; i < files; ++i) {
        			//Tots els elements fins ara de la columna 'j' han estat afegits a vector columna.
            			columna.push_back(tauler[i][j]);
        		}
        		
        		if (!validaSequencia(columna, pistesColumnes[j])) {
            			parar = true;
        		}
    		}
    		
		resultat = true;
		parar = true; // És vàlid si totes les files i columnes compleixen
	}
	
	return resultat;
}

int main(){

	vector<vector<char>> tauler = {
		{'X', '.', '.', '.', 'X'},
		{'X', 'X', '.', '.', '.'},
		{'.', '.', 'X', 'X', '.'},
		{'.', '.', '.', 'X', 'X'},
		{'X', '.', '.', '.', 'X'}
	};
	
	vector<vector<int>> pistesFiles = {
    {1, 1}, // Fila 1: un grupo de 1 "X", luego otro grupo de 1 "X".
    {2},    // Fila 2: un grupo de 2 "X".
    {2},    // Fila 3: un grupo de 2 "X".
    {2},    // Fila 4: un grupo de 2 "X".
    {1, 1}  // Fila 5: un grupo de 1 "X", luego otro grupo de 1 "X".
};

vector<vector<int>> pistesColumnes = {
    {2},    // Columna 1: un grupo de 2 "X".
    {1},    // Columna 2: un grupo de 1 "X".
    {1, 1}, // Columna 3: dos grupos de 1 "X".
    {1, 1}, // Columna 4: dos grupos de 1 "X".
    {2}     // Columna 5: un grupo de 2 "X".
};


cout << validaNanograma(tauler, pistesFiles, pistesColumnes) << endl; // Debería imprimir 1 (true).






}
