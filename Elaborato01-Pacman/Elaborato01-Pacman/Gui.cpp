
#include "Gui.h"

/* Variabili Da Importare */
/* Colori */
extern ImVec4 clear_color_2;

/* Finestra */
extern int window_width, window_height;

/* Gui */
extern bool button_set;

int ghost_number = 0;

/* Funzione che inizializzazione la ImGui con GLW e OpenGL */
void InitializeImGui(GLFWwindow* window) {
    IMGUI_CHECKVERSION();                           // Controlla compatibilità versione ImGui
    ImGui::CreateContext();                         // Crea il contesto ImGui (necessario)
    ImGuiIO& io = ImGui::GetIO();                   // Ottiene l’oggetto IO di ImGui (config e input)
    io.FontGlobalScale = 2.0f;                      // Scala globale del font (doppio delle dimensioni)
    ImGui::StyleColorsDark();                       // Imposta tema scuro predefinito

    // Inizializza l’integrazione con GLFW per OpenGL
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330 core");    // Inizializza renderer OpenGL3 con versione 330 core
}

/* Funzione di rendering dell'interfaccia grafica del menu iniziale */
void interfaceMenu(void) {

    /* Preparazione nuovo frame per input GLFW e rendering OpenGL */
    ImGui_ImplGlfw_NewFrame();
    ImGui_ImplOpenGL3_NewFrame();
    ImGui::NewFrame();

    /* Imposta posizione della finestra successiva */
    ImGui::SetNextWindowPos(ImVec2(1, 1));

    /* Contenuto della finestra */
    ImGui::Begin("Scelta fantasmini", NULL,         // Apre finestra "Impostazioni"
        ImGuiWindowFlags_NoResize |                 // Impedisce ridimensionamento utente
        ImGuiWindowFlags_AlwaysAutoResize |         // Ridimensionamento automatico al contenuto
        ImGuiWindowFlags_NoBackground |             // Sfondo trasparente
        ImGuiWindowFlags_NoMove                     // Impedisce lo spostamento finestra
    );
    ImGui::InputInt("Numero fantasmi desiderato", &ghost_number);
    if (ImGui::Button("Start")) {
        button_set = !button_set;
    }

    ImGui::End();                                   // Chiude la finestra
    ImGui::Render();                                // Compila i dati UI per il rendering finale
}

/* Funzione di rendering dell'interfaccia grafica per i frame del gioco */
void interfaceGame(void) {

    /* Preparazione nuovo frame per input GLFW e rendering OpenGL */
    ImGui_ImplGlfw_NewFrame();
    ImGui_ImplOpenGL3_NewFrame();
    ImGui::NewFrame();

    /* Imposta posizione della finestra successiva */
    ImGui::SetNextWindowPos(ImVec2(1, 1));

    /* Contenuto della finestra */
    ImGui::Begin("Area di Gioco", NULL,                             // Apre finestra "Impostazioni"
        ImGuiWindowFlags_NoResize |                                 // Impedisce ridimensionamento utente
        ImGuiWindowFlags_AlwaysAutoResize |                         // Ridimensionamento automatico al contenuto
        ImGuiWindowFlags_NoBackground |                             // Sfondo trasparente
        ImGuiWindowFlags_NoTitleBar |                               // Nasconde barra titolo
        ImGuiWindowFlags_NoMove                                     // Impedisce lo spostamento finestra
    );
    ImGui::SetNextWindowPos(ImVec2(0.0, 0.0));
    //ImGui::ColorEdit4("Colore sfondo", (float*)&clear_color_2);   // Mostra a video i valori RGBA del colore 

    ImGui::End();                                                  // Chiude la finestra
    ImGui::Render();                                               // Compila i dati UI per il rendering finale
}

/* Funzione per chiudere e pulire ImGui correttamente */
void closeGUI() {
    ImGui_ImplOpenGL3_Shutdown();   // Rilascia risorse renderer OpenGL3
    ImGui_ImplGlfw_Shutdown();      // Rilascia risorse integrazione GLFW
    ImGui::DestroyContext();        // Distrugge contesto ImGui liberando memoria
}

