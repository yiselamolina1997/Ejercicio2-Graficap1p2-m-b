#include <GL/glut.h>              // Incluir la biblioteca GLUT para OpenGL
#include <cmath>                   // Incluir funciones matem�ticas
#include <sstream>                 // Incluir la biblioteca para convertir datos a cadenas
#include <string>                  // Incluir la biblioteca de cadenas
#include <iostream>                // Incluir la biblioteca para la entrada y salida est�ndar

// Variables para los puntos ingresados por el usuario
float xP1, yP1;                   // Coordenadas del primer punto P1
float xP2, yP2;                   // Coordenadas del segundo punto P2
std::string equationText;         // Texto que contendr� la ecuaci�n de la recta

// Funci�n para mostrar texto en la ventana en coordenadas (x, y)
void renderText(float x, float y, std::string text) {
    glRasterPos2f(x, y);         // Establecer la posici�n del texto
    for (char c : text) {        // Recorrer cada car�cter en el texto
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c); // Mostrar el car�cter
    }
}

// Funci�n para calcular la ecuaci�n de la recta a partir de los puntos P1 y P2
void calculateEquation() {
    float m = (yP2 - yP1) / (xP2 - xP1);  // Calcular la pendiente de la recta
    float b = yP1 - m * xP1;               // Calcular la intersecci�n en Y

    std::ostringstream equationStream;     // Crear un flujo de salida para la ecuaci�n
    equationStream << "y = " << m << "x + " << b; // Formatear la ecuaci�n
    equationText = equationStream.str();   // Convertir el flujo a cadena
}

// Funci�n para dibujar la cuadr�cula del plano cartesiano
void drawGrid() {
    glColor3f(0.9f, 0.9f, 0.9f);  // Establecer color gris claro para la cuadr�cula

    // Dibujar l�neas verticales
    glBegin(GL_LINES);
    for (float i = -10.0f; i <= 10.0f; i += 1.0f) {
        glVertex2f(i, -10.0f);  // Punto de inicio
        glVertex2f(i, 10.0f);   // Punto de fin
    }

    // Dibujar l�neas horizontales
    for (float i = -10.0f; i <= 10.0f; i += 1.0f) {
        glVertex2f(-10.0f, i);  // Punto de inicio
        glVertex2f(10.0f, i);   // Punto de fin
    }
    glEnd();
}

// Funci�n para dibujar los n�meros en los ejes
void drawAxisNumbers() {
    glColor3f(0.5f, 0.5f, 0.5f);  // Establecer color gris para los n�meros

    // N�meros en el eje X
    for (int i = -9; i <= 9; i++) {
        if (i != 0) {  // No mostrar el n�mero 0 en el origen
            std::ostringstream numberStream; // Crear un flujo para los n�meros
            numberStream << i;                 // Convertir el n�mero a cadena
            renderText(i, -0.5f, numberStream.str()); // Mostrar el n�mero en el eje X
        }
    }

    // N�meros en el eje Y
    for (int i = -9; i <= 9; i++) {
        if (i != 0) {  // No mostrar el n�mero 0 en el origen
            std::ostringstream numberStream; // Crear un flujo para los n�meros
            numberStream << i;                 // Convertir el n�mero a cadena
            renderText(-0.7f, i, numberStream.str()); // Mostrar el n�mero en el eje Y
        }
    }
}

// Funci�n que se llama para dibujar la escena
void display() {
    glClear(GL_COLOR_BUFFER_BIT);  // Limpiar el buffer de color

    // Dibujar la cuadr�cula
    drawGrid();

    // Dibujar el plano cartesiano (ejes X e Y)
    glColor3f(0.0f, 0.0f, 0.0f);  // Establecer color negro para los ejes

    glBegin(GL_LINES);
    // Eje X
    glVertex2f(-10.0f, 0.0f);
    glVertex2f(10.0f, 0.0f);
    // Eje Y
    glVertex2f(0.0f, -10.0f);
    glVertex2f(0.0f, 10.0f);
    glEnd();

    // Dibujar los n�meros en los ejes
    drawAxisNumbers();

    // Graficar el punto P1
    glColor3f(0.0f, 0.0f, 1.0f);  // Establecer color azul para P1
    glPointSize(10.0f);
    glBegin(GL_POINTS);
    glVertex2f(xP1, yP1);
    glEnd();

    // Leyenda P1
    renderText(xP1 + 0.5f, yP1 + 0.5f, "P1");

    // Graficar el punto P2
    glBegin(GL_POINTS);
    glVertex2f(xP2, yP2);
    glEnd();

    // Leyenda P2
    renderText(xP2 + 0.5f, yP2 + 0.5f, "P2");

    // Dibujar la l�nea entre P1 y P2
    glColor3f(0.5f, 0.0f, 0.5f);  // Establecer color morado para la l�nea
    glBegin(GL_LINES);
    glVertex2f(xP1, yP1);
    glVertex2f(xP2, yP2);
    glEnd();

    // Color ecuacion
    glColor3f(0.0f, 0.0f, 0.0f);  // Establecer color negro para la ecuaci�n
    renderText(3.0f, -9.5f, equationText);  // Dibujar la ecuaci�n de la recta

    glFlush();  // Asegurarse de que todo se dibuje
}

// Funci�n de inicializaci�n
void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);  // Establecer color de fondo blanco
    glColor3f(0.0, 0.0, 0.0);          // Establecer color negro
    glPointSize(10.0);                 // Establecer tama�o de puntos

    glMatrixMode(GL_PROJECTION);      // Seleccionar la matriz de proyecci�n
    glLoadIdentity();                 // Cargar la matriz identidad
    gluOrtho2D(-10.0, 10.0, -10.0, 10.0); // Definir la proyecci�n ortogr�fica
}

int main(int argc, char** argv) {
    // Solicitar entrada de puntos al usuario
    std::cout << "Ingrese las coordenadas de P1 (x y): ";
    std::cin >> xP1 >> yP1;  // Leer coordenadas de P1

    std::cout << "Ingrese las coordenadas de P2 (x y): ";
    std::cin >> xP2 >> yP2;  // Leer coordenadas de P2

    // Calcular la ecuaci�n de la recta
    calculateEquation();

    glutInit(&argc, argv);  // Inicializar GLUT
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);  // Establecer modo de visualizaci�n
    glutInitWindowSize(500, 500);  // Establecer tama�o de la ventana
    glutCreateWindow("Ejercicio 2");  // Crear ventana

    init();  // Inicializar configuraciones
    glutDisplayFunc(display);  // Asignar funci�n de visualizaci�n
    glutMainLoop();  // Entrar en el bucle principal de GLUT

    return 0;  // Fin del programa
}

