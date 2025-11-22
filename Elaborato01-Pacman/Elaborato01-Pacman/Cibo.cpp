#include "Cibo.h"

vector<Cibo> checkCiboInMatrice(int tipo_cibo) {
	int rows = height_matrice;
	int columns = width_matrice;

	vector<Cibo> cibo_matrice;

	for (int i = 0; i < rows; i++) {
		int start = -1;
		for (int j = 0; j < columns - 1; j++) {
			if (campo[i][j] == tipo_cibo && start == -1) {
				start = j;
			}
			if (campo[i][j] != tipo_cibo && start != -1) {
				if (start != j - 1) {
					Cibo cibo = { i, i, start, j - 1 };
					cibo_matrice.push_back(cibo);
				}
				start = -1;
			}
		}
		if (start != -1) {
			Cibo cibo = { i, i, start, columns - 1 };
			cibo_matrice.push_back(cibo);
		}
	}

	vector<Cibo> cibo_coordinate;

	for (int i = 0; i < cibo_matrice.size() - 1; i++) {
		for (int j = i + 1; j < cibo_matrice.size(); j++) {
			if (cibo_matrice[i].column_start == cibo_matrice[j].column_start && cibo_matrice[i].column_end == cibo_matrice[j].column_end) {
				if (cibo_matrice[i].row_start + 1 == cibo_matrice[j].row_start || cibo_matrice[i].row_start - 1 == cibo_matrice[j].row_start) {
					Cibo farfalla = {
						std::min(cibo_matrice[i].row_start,cibo_matrice[j].row_start),
						std::max(cibo_matrice[i].row_start,cibo_matrice[j].row_start),
						cibo_matrice[i].column_start, cibo_matrice[i].column_end
					};
					cibo_coordinate.push_back(farfalla);
				}
			}
		}

	}
	/* Debug
	for (Cibo_farfalla farfalla : farfalleTot) {
		cout << "row_start: " << farfalla.row_start << ",\nrow_end: " << farfalla.row_end << ",\ncolumn_start: " << farfalla.column_start << ",\ncolumn_end: " << farfalla.column_end << "\n\n" << endl;
	}
	*/
	return cibo_coordinate;
}

vector<CiboCoord> calcolaCoordinateFarfalle(vector<vec3> vertices) {

	/* Dimensione di una cella della finestra se fosse sovrapposta alla matrice */
	float altezza_cella = vertices[2].y / height_matrice;
	float larghezza_cella = vertices[2].x / width_matrice;

	vector<CiboCoord> farfalleCoord;

	vector<Cibo> farfalle = checkCiboInMatrice(FARFALLA);

	for (Cibo farfalla : farfalle) {
		CiboCoord farfallaCoord;

		farfallaCoord.raggio = larghezza_cella;

		/* Coordinate del centro */
		farfallaCoord.centro_x = (farfalla.column_start + farfalla.column_end) / 2 * larghezza_cella;
		farfallaCoord.centro_y = (farfalla.row_start + farfalla.row_end) / 2 * altezza_cella;

		farfalleCoord.push_back(farfallaCoord);
		/* Debug
		cout << "top_start: (" << farfallaCoord.centro_x << " , " << farfallaCoord.centro_y << ")\n raggio: (" << farfallaCoord.raggio << "\n\n" << endl;
	   */
	}

	return farfalleCoord;
}

vector<CiboCoord> calcolaCoordinateCerchi(vector<vec3> vertices) {
	/* Dimensione di una cella della finestra se fosse sovrapposta alla matrice */
	float altezza_cella = vertices[2].y / height_matrice;
	float larghezza_cella = vertices[2].x / width_matrice;

	vector<CiboCoord> cerchiCoord;

	vector<Cibo> cerchi = checkCiboInMatrice(CERCHIO);

	for (Cibo cerchio : cerchi) {
		CiboCoord cerchioCoord;

		cerchioCoord.raggio = larghezza_cella;

		/* Coordinate del centro */
		cerchioCoord.centro_x = (cerchio.column_start + cerchio.column_end) / 2 * larghezza_cella;
		cerchioCoord.centro_y = (cerchio.row_start + cerchio.row_end) / 2 * altezza_cella;

		cerchiCoord.push_back(cerchioCoord);
		/* Debug
		cout << "top_start: (" << farfallaCoord.centro_x << " , " << farfallaCoord.centro_y << ")\n raggio: (" << farfallaCoord.raggio << "\n\n" << endl;
	   */
	}
	return cerchiCoord;
}