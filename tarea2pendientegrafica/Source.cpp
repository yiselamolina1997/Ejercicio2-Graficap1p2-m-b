#include <GL/glut.h>              // Incluir la biblioteca GLUT para OpenGL
#include <cmath>                   // Incluir funciones matemáticas
#include <sstream>                 // Incluir la biblioteca para convertir datos a cadenas
#include <string>                  // Incluir la biblioteca de cadenas
#include <iostream>                // Incluir la biblioteca para la entrada y salida estándar

// Variables para los puntos ingresados por el usuario
float xP1, yP1;                   // Coordenadas del primer punto P1
float xP2, yP2;                   // Coordenadas del segundo punto P2
std::string equationText;         // Texto que contendrá la ecuación de la recta

// Función para mostrar texto en la ventana en coordenadas (x, y)
void renderText(float x, float y, std::string text) {
    glRasterPos2f(x, y);         // Establecer la posición del texto
    for (char c : text) {        // Recorrer cada carácter en el texto
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c); // Mostrar el carácter
    }
}

// Función para calcular la ecuación de la recta a partir de los puntos P1 y P2
void calculateEquation() {
    float m = (yP2 - yP1) / (xP2 - xP1);  // Calcular la pendiente de la recta
    float b = yP1 - m * xP1;               // Calcular la intersección en Y

    std::ostringstream equationStream;     // Crear un flujo de salida para la ecuación
    equationStream << "y = " << m << "x + " << b; // Formatear la ecuación
    equationText = equationStream.str();   // Convertir el flujo a cadena
}

// Función para dibujar la cuadrícula del plano cartesiano
void drawGrid() {
    glColor3f(0.9f, 0.9f, 0.9f);  // Establecer color gris claro para la cuadrícula

    // Dibujar líneas verticales
    glBegin(GL_LINES);
    for (float i = -10.0f; i <= 10.0f; i += 1.0f) {
        glVertex2f(i, -10.0f);  // Punto de inicio
        glVertex2f(i, 10.0f);   // Punto de fin
    }

    // Dibujar líneas horizontales
    for (float i = -10.0f; i <= 10.0f; i += 1.0f) {
        glVertex2f(-10.0f, i);  // Punto de inicio
        glVertex2f(10.0f, i);   // Punto de fin
    }
    glEnd();
}

// Función para dibujar los números en los ejes
void drawAxisNumbers() {
    glColor3f(0.5f, 0.5f, 0.5f);  // Establecer color gris para los números

    // Números en el eje X
    for (int i = -9; i <= 9; i++) {
        if (i != 0) {  // No mostrar el número 0 en el origen
            std::ostringstream numberStream; // Crear un flujo para los números
            numberStream << i;                 // Convertir el número a cadena
            renderText(i, -0.5f, numberStream.str()); // Mostrar el número en el eje X
        }
    }

    // Números en el eje Y
    for (int i = -9; i <= 9; i++) {
        if (i != 0) {  // No mostrar el número 0 en el origen
            std::ostringstream numberStream; // Crear un flujo para los números
            numberStream << i;                 // Convertir el número a cadena
            renderText(-0.7f, i, numberStream.str()); // Mostrar el número en el eje Y
        }
    }
}

// Función que se llama para dibujar la escena
void display() {
    glClear(GL_COLOR_BUFFER_BIT);  // Limpiar el buffer de color

    // Dibujar la cuadrícula
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

    // Dibujar los números en los ejes
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

    // Dibujar la línea entre P1 y P2
    glColor3f(0.5f, 0.0f, 0.5f);  // Establecer color morado para la línea
    glBegin(GL_LINES);
    glVertex2f(xP1, yP1);
    glVertex2f(xP2, yP2);
    glEnd();

    // Color ecuacion
    glColor3f(0.0f, 0.0f, 0.0f);  // Establecer color negro para la ecuación
    renderText(3.0f, -9.5f, equationText);  // Dibujar la ecuación de la recta

    glFlush();  // Asegurarse de que todo se dibuje
}

// Función de inicialización
void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);  // Establecer color de fondo blanco
    glColor3f(0.0, 0.0, 0.0);          // Establecer color negro
    glPointSize(10.0);                 // Establecer tamaño de puntos

    glMatrixMode(GL_PROJECTION);      // Seleccionar la matriz de proyección
    glLoadIdentity();                 // Cargar la matriz identidad
    gluOrtho2D(-10.0, 10.0, -10.0, 10.0); // Definir la proyección ortográfica
}

int main(int argc, char** argv) {
    // Solicitar entrada de puntos al usuario
    std::cout << "Ingrese las coordenadas de P1 (x y): ";
    std::cin >> xP1 >> yP1;  // Leer coordenadas de P1

    std::cout << "Ingrese las coordenadas de P2 (x y): ";
    std::cin >> xP2 >> yP2;  // Leer coordenadas de P2

    // Calcular la ecuación de la recta
    calculateEquation();

    glutInit(&argc, argv);  // Inicializar GLUT
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);  // Establecer modo de visualización
    glutInitWindowSize(500, 500);  // Establecer tamaño de la ventana
    glutCreateWindow("Ejercicio 2");  // Crear ventana

    init();  // Inicializar configuraciones
    glutDisplayFunc(display);  // Asignar función de visualización
    glutMainLoop();  // Entrar en el bucle principal de GLUT

    return 0;  // Fin del programa
}

