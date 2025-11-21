#include "InitVAO.h"

void INIT_VAO(Figura* fig) {

	/* Creazione dello spazio di memoria del VAO e salvataggio dell' ID */
	glGenVertexArrays(1, &fig->VAO);

	/* Attivazione del VAO */
	glBindVertexArray(fig->VAO);

	/*------------------- Vertici ---------------------------*/
	/* Generazione del VBO */
	glGenBuffers(1, &fig->VBO_vertices);

	/* Attivazione del VBO */
	glBindBuffer(GL_ARRAY_BUFFER, fig->VBO_vertices);

	/* Riempimento del VBO */
	/* Prende in input: 1. Tipologia di buffer, 2. Dimensione, 3. Elementi, 4. Gestione dei dati */
	glBufferData(GL_ARRAY_BUFFER, sizeof(vec3) * fig->vertices.size(), fig->vertices.data(), GL_STATIC_DRAW);

	/* Descrizione del formato e della posizione dei dati */
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	/* Abilitazione dell'attributo */
	glEnableVertexAttribArray(0);

	/*------------------- Colori ---------------------------*/
	/* Generazione del VBO */
	glGenBuffers(1, &fig->VBO_colors);

	/* Attivazione del VBO */
	glBindBuffer(GL_ARRAY_BUFFER, fig->VBO_colors);

	/* Riempimento del VBO */
	/* Prende in input: 1. Tipologia di buffer, 2. Dimensione, 3. Elementi, 4. Gestione dei dati */
	glBufferData(GL_ARRAY_BUFFER, sizeof(vec4) * fig->colors.size(), fig->colors.data(), GL_STATIC_DRAW);

	/* Descrizione del formato e della posizione dei dati */
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);

	/* Abilitazione dell'attributo */
	glEnableVertexAttribArray(1);
}