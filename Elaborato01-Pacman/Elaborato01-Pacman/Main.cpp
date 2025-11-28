/*
	Progetto di Barba Beatrice - Primo Elaborato per l'esame di Computer Graphics
	Simulazione del pacman molto semplificato
*/

#include "lib.h"				// Header file con tutte le librerie di configurazione del progetto necessarie			
#include "Gui.h"				// Header file della GUI personalizzata
#include "ShaderMaker.h"		// Header file della classe che gestisce gli Shader
#include "Rendering.h"			// Header file della funzione di rendering
#include "Scena.h"				// Header file per le funzioni sulla scena
#include "GestioneEventi.h"		// Header file per la gestione dei callback

/*----------------------------------------------------------------*/

/* Variabili globali */
/* Esterne */
extern float x_offset, y_offset;

/* Colori */
ImVec4 clear_color_1 = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);			// Colore di pulizia prima schermata (RGBA)
ImVec4 clear_color_2 = ImVec4(0.0f, 1.0f, 0.5f, 1.0f);			// Colore di pulizia seconda schermata (RGBA)

/* Finestra */
int window_width = 1000, window_height = 800;					// Risoluzione finesta iniziale
float window_width_background, window_height_background;		// Servono a cambiare la risoluzione della finestra solo per lo sfondo
float window_width_update, window_height_update;				// Servono a cambiare la risoluzione della finestra del gioco

/* Gui */
bool button_set = false;										// Flag per cambiare interfaccia

/* Shader */
unsigned int program_id;										// Identificativo del program shader
unsigned int program_id_background;								// Identificativo specifivco per il program shader dello sfondo

GLuint id_proj, id_model, id_proj_background;					// Identificativi per le matrici di modellazione e proiezione da usare negli shader
GLuint texture_id_channel0;										// Identificativo della texture da usare

/* Strutture e matrici di trasformazioni */
vector<Figura> Scena;											// Vettore per impostare le figure nella scena
mat4 projection, projection_background;							// Matrice che normalizza le coordinate del mondo in cordinate NDC

/* Rendering */
bool wireframe = false;											// Flag per decidere se disegnare solo i contorni di una figura 
bool showBB = false;											// Flag per decidere se disegnare il Bounding Box della figura

/* Tempi */
float currentTime;												// Variabile per tracciare il tempo
float delta_time;												// Tempo di rendering di un frame

/* Gioco */
int punteggio = 0;												// Serve a registrare il punteggio per poi essere mostrato a video
int counterCibo = 0;											// Conta gli oggetti nella scena per decidere la fine del gioco
bool check_collisione = false;									// Flag per decidere se effettuare lo spostamento o no del Pac-Man

int main(void) {

	/* Creazione della finestra */
	GLFWwindow* window;

	/* Inizializza libreria GLFW */
	if (!glfwInit()) {
		return -1;
	}

	/* Setta OpenGL e il profile core */
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);

	/* Inizializzazione della finestra con contesto OpenGL */
	window = glfwCreateWindow(window_width, window_height, "Pac - man", NULL, NULL);

	/* Controllo della creazione della finestra */
	if (!window) {
		cout << "Creazione della finestra fallita" << endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	/* Caricamento puntatori OpenGL tramite GLAD per la portabilità */
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		cout << "Caricamento dei puntatori OpenGl fallito" << endl;
		glfwTerminate();
		return -1;
	}

	/* Abilitazione del framebuffer sRGB */
	glEnable(GL_FRAMEBUFFER_SRGB);

	/* Inizializzazione ImGui con la finestra GLFW */
	InitializeImGui(window);

	/* Inizializzo gli shader */
	program_id = ShaderMaker::initShader((char*)"vertexShader.glsl", (char*)"fragmentShaderFigure.glsl");
	program_id_background = ShaderMaker::initShader((char*)"vertexShader.glsl", (char*)"fragmentShaderBackground.glsl");

	/* Inizializzazione finestra */
	window_height_background = (float)window_height;
	window_width_background = (float)window_width;
	window_height_update = (float)window_height;
	window_width_update = (float)window_width;

	/* Inizializzazione della scena */
	costruisciScena(&Scena);

	/* Inizializzazione della matrice di proiezione */
	projection = ortho(0.0f, (float)window_width, 0.0f, (float)window_height);
	projection_background = ortho(0.0f, (float)window_width_background, 0.0f, (float)window_height_background);

	/* Salvataggio ID matrice di modellazione e progettazione */
	id_proj = glGetUniformLocation(program_id, "Projection");
	id_model = glGetUniformLocation(program_id, "Model");
	id_proj_background = glGetUniformLocation(program_id_background, "Projection");

	/* Creazione della texture di sfondo */
	texture_id_channel0 = ShaderMaker::setupTexture("channel0.jpg");

	/* Registrazione dei callback per gli eventi */
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetKeyCallback(window, key_callback);

	/* Gameloop */
	while (!glfwWindowShouldClose(window)) {

		currentTime = glfwGetTime();

		/* Disegna la scena */
		rendering(currentTime);

		/* Renderizza la GUI ImGui */
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		/* Scambio dei buffer */
		glfwSwapBuffers(window);

		/* Cattura e processazione degli eventi input */
		glfwPollEvents();
	}

	/* Pulizia finale */
	closeGUI();
	glfwDestroyWindow(window);
	glDeleteProgram(program_id);
	for (int i = 0; i < Scena.size(); i++) {
		glDeleteBuffers(1, &Scena[i].VBO_vertices);
		glDeleteBuffers(1, &Scena[i].VBO_colors);
		glDeleteBuffers(1, &Scena[i].VAO);
	}
	glfwTerminate();
	return 0;
}
