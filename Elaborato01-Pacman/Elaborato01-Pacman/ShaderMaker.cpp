#pragma once


#include "ShaderMaker.h"

extern GLuint id_proj, id_model;
extern ImVec4 clear_color;
extern float delta_time;
extern GLuint texture_id_channel0;

#pragma warning(disable:4996)
/* Funzione che legge il file shader */
char* ShaderMaker::readShaderSource(const char* shaderFile)
{
	FILE* fp = fopen(shaderFile, "rb");		// Apertura del file in modalità letttura binaria

	if (fp == NULL) { return NULL; }		// Controllo dell'apertura

	fseek(fp, 0L, SEEK_END);				// Posizionamento del puntatore di file alla fine del file
	long size = ftell(fp);					// Determinazione della lunghezza del file in byte

	fseek(fp, 0L, SEEK_SET);				// Posizionamento del puntatore di file all'inizio
	char* buf = new char[size + 1];			// Allocazione di memoria per il file
	fread(buf, 1, size, fp);				// Legge il contenuto del file e lo mette nel buffer

	buf[size] = '\0';						// Viene impostato il carattere nullo come ultimo dle file
	fclose(fp);								// Chiusura del file

	return buf;								// Ritorna il buffer contenente il contenuto del file
}

GLuint ShaderMaker::createProgram(char* vertexfilename, char* fragmentfilename) {

	int success;
	char infoLog[512];

	/* Creazione e lettura del Vertex Shader */
	const GLchar* VertexShader = readShaderSource(vertexfilename);

	/* Generazione del suo identificativo */
	GLuint vertexShaderId = glCreateShader(GL_VERTEX_SHADER);

	/* Associazione fra identificativo e codice */
	glShaderSource(vertexShaderId, 1, (const char**)&VertexShader, NULL);

	/* Compilazione del Vertex Shader */
	glCompileShader(vertexShaderId);

	/* Controllo della compilazione */
	glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShaderId, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	/* Creazione e lettura del Fragment Shader */
	const GLchar* FragmentShader = readShaderSource(fragmentfilename);

	/* Generazione del suo identificativo */
	GLuint fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);

	/* Associazione fra identificativo e codice */
	glShaderSource(fragmentShaderId, 1, (const char**)&FragmentShader, NULL);

	/* Compilazione del Fragment Shader */
	glCompileShader(fragmentShaderId);

	/* Controllo della compilazione */
	glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShaderId, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	/* Creazione di un identificativo per un eseguibile */
	GLuint programId = glCreateProgram();

	/* Associazione degli shader per collegarli al programma */
	glAttachShader(programId, vertexShaderId);
	glAttachShader(programId, fragmentShaderId);

	/* Collegamento degli shader al programma e crea un eseguibile per il rendering */
	glLinkProgram(programId);

	glGetProgramiv(programId, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(programId, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	return programId;
}

/* Funzione che inizializza lo shader*/
GLuint ShaderMaker::initShader(char* vertexShader, char* fragmentShader) {

	GLuint programId;

	/* Controllo su errori di OpenGL */
	/* GlGetError restituisce il codice di errore corrente, se c'è uno ancora non gestito */
	GLenum ErrorCheckValue = glGetError();

	/* Setto il percorso dei file degli shader */
	char* vertexShaderFile = vertexShader;
	char* fragmentShaderFile = fragmentShader;

	/* Creazione del programma shader */
	programId = ShaderMaker::createProgram(vertexShaderFile, fragmentShaderFile);

	return programId;
}
