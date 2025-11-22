#include "Muri.h"

extern int campo[height_matrice][width_matrice];

vector<Muro> trasformaMatriceInMuri() {
    int rows = height_matrice;
    int columns = width_matrice;

    vector<Muro> muri;

    for (int i = 0; i < rows; i++) {
        int start = -1;
        for (int j = 0; j < columns - 1; j++) {
            if (campo[i][j] == MURO && start == -1) {
                start = j;
            }
            if (campo[i][j] != MURO && start != -1) {
                if (start != j - 1) {
                    Muro muro_attuale = { i,i,start, j - 1 };
                    muri.push_back(muro_attuale);
                }
                start = -1;
            }
        }
        if (start != -1) {
            Muro muro_attuale = { i,i,start, columns - 1 };
            muri.push_back(muro_attuale);
        }
    }

    for (int j = 0; j < columns; j++) {
        int start = -1;
        for (int i = 0; i < rows - 1; i++) {
            if (campo[i][j] == MURO && start == -1) {
                start = i;
            }
            if (campo[i][j] != MURO && start != -1) {
                if (start != i - 1) {
                    Muro muro_attuale = { start,i - 1,j, j };
                    muri.push_back(muro_attuale);
                }
                start = -1;
            }
        }
        if (start != -1) {
            Muro muro_attuale = { start,rows - 1,j, j };
            muri.push_back(muro_attuale);
        }
    }
    /* Debug
    for (Muro muro : muri) {
        cout << "x_start: " << muro.colonna_start << " x_end: " << muro.colonna_end << " y_start: " << muro.riga_start << " y_end: " << muro.riga_end << "\n" << endl;
    }
    */
    return muri;
}

vector<MuroCoord> creaMuri(vector<vec3> vertices) {

    /* Spessore del muro */
    float altezza_cella = vertices[2].y / height_matrice;
    float larghezza_cella = vertices[2].x / width_matrice;

    vector<Muro> muri = trasformaMatriceInMuri();
    vector<MuroCoord> muri_coord;

    for (Muro muro : muri) {
        MuroCoord muroCoord;

        /* Coordinate punto basso a sinistra */
        muroCoord.bottom_start = vec3(muro.colonna_start * larghezza_cella, (muro.riga_end + 1) * altezza_cella, 0.0);

        /* Coordinate punto basso a destra */
        muroCoord.bottom_end = vec3((muro.colonna_end + 1) * larghezza_cella, (muro.riga_end + 1) * altezza_cella, 0.0);

        /* Cooridnate punto alto a sinistra */
        muroCoord.top_start = vec3(muro.colonna_start * larghezza_cella, muro.riga_start * altezza_cella, 0.0);

        /* Coordinate punto alto a destra */
        muroCoord.top_end = vec3((muro.colonna_end + 1) * larghezza_cella, muro.riga_start * altezza_cella, 0.0);

        muri_coord.push_back(muroCoord);
        /* Debug
        cout << "top_start: (" << muroCoord.top_start.x << " , " << muroCoord.top_start.y << ")\n top_end: (" << muroCoord.top_end.x << " , " << muroCoord.top_end.y
            << ")\n bottom_start: (" << muroCoord.bottom_start.x << " , " << muroCoord.bottom_start.y << ") \nbottom_end: (" << muroCoord.bottom_end.x << " , " << 
            muroCoord.bottom_end.y << ")\n\n" << endl;
       */
    }

    return muri_coord;
}


