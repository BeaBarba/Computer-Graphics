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

GLuint ShaderMaker::setupTexture(const char* image_name) {
	GLuint texture_id;
	int image_width, image_height, nrChannels;
	unsigned char* image_data = stbi_load(image_name, &image_width, &image_height, &nrChannels, 0);	// Puntatore ai dati dell'immagine

	if (image_data) {
		// Determina il formato corretto 
		GLenum internal_format = GL_SRGB;
		GLenum data_format = GL_RGB;
		if (nrChannels == 1) {
			data_format = GL_RGB;
			internal_format = GL_SRGB;
		}
		else if (nrChannels == 4) {
			data_format = GL_RGBA;
			internal_format = GL_SRGB_ALPHA;
		}

		/* Genera una texture */
		glGenTextures(1, &texture_id);

		/* Collega la texture al suo slot */
		glBindTexture(GL_TEXTURE_2D, texture_id);

		/* Prende in input:
			- Target,
			- Livello di dettaglio,
			- Formato di come OpenGL deve salvare,
			- Dimensione x dell'immagine,
			- Dimensione y,
			- Border --> Deve essere sempre impostato a 0
			- Formato dell'immagine
			- Tipo dei dati dei pixel sorgente
			- Puntatore ai dati dell'immagine
		*/
		glTexImage2D(GL_TEXTURE_2D, 0, internal_format, image_width, image_height, 0, data_format, GL_UNSIGNED_BYTE, image_data);
		//glGenerateMipmap(GL_TEXTURE_2D);

		/* Parametri di wrapping e filtraggio */
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}
	else {
		std::cerr << "ERRORE: Impossibile caricare l'immagine: " << image_name << std::endl;
		texture_id = 0; // Segnala un errore
	}

	// Libera la memoria della CPU
	stbi_image_free(image_data);

	return texture_id;
}

void ShaderMaker::useShaderWithUniform(unsigned int shader_program_id, mat4& projection, mat4& model, float currentTime, vec2 resolution, bool texture, bool date) {

	/*
		Imposta il programma shader creato come corrente nella pipeline OpenGL.
		Tutte le operazioni di rendering useranno questo programma finché non cambierà
	*/
	glUseProgram(shader_program_id);

	/* Collega il puntatore della matrice al suo identificativo */
	glUniformMatrix4fv(id_proj, 1, GL_FALSE, value_ptr(projection));
	glUniformMatrix4fv(id_model, 1, GL_FALSE, value_ptr(model));

	GLuint id_time_delta = glGetUniformLocation(shader_program_id, "iTimeDelta");
	glUniform1f(id_time_delta, delta_time);

	/* Controllo l'esistenza e nel caso affermativo collego la variabile nella GPU con la variabile in CPU */

	/* Risoluzione */
	if (resolution.x > 0.0f && resolution.y > 0.0f) {
		GLuint id_res = glGetUniformLocation(shader_program_id, "iResolution");
		glUniform2f(id_res, resolution.x, resolution.y);
	}

	/* Tempo */
	if (currentTime > 0.0f) {
		GLuint id_time = glGetUniformLocation(shader_program_id, "iTime");
		glUniform1f(id_time, currentTime);
	}

	if (texture && texture_id_channel0 != 0) {
		GLuint id_texture;
		/* Seleziona lo slot della texture e collego la texture allo slot */
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture_id_channel0);

		/* Passa la texture appena generata alla GPU */
		id_texture = glGetUniformLocation(shader_program_id, "iChannel0");
		//cout <<"id_texture" << id_texture << endl;
		glUniform1i(id_texture, 0);
	}

	if (date) {
		float* year, * month, * day, * seconds;
		time_t now = time(NULL);
		struct tm* now_tm = localtime(&now);

		vec4 date = vec4(now_tm->tm_year, now_tm->tm_mon, now_tm->tm_mday, (now % 86400));
		GLuint id_date = glGetUniformLocation(shader_program_id, "iDate");
		glUniform4f(id_date, date.x, date.y, date.z, date.w);

	}
}
