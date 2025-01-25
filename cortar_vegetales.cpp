#include <thread>
#include <chrono>
#include <iostream>
#include <atomic>

using namespace std;

std::atomic<bool> chopping(true);
std::atomic<unsigned int> vegetable_count(0);

void vegetable_chopper(const char* name) {
    while (chopping) {
        vegetable_count++;
    }
    printf("%s chopped %u vegetables.\n", name, vegetable_count/2);
}

// Función para simular carga de CPU (antes era cpu_waster)
void calculadora() {
    int a, b;
    cout << "Ingrese dos numeros: ";
    while (!(cin >> a >> b)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Entrada invalida. Intente de nuevo: ";
    }
    cout << "Suma: " << a + b << endl;
}

// Función para imprimir "Hola" y "Adios" en orden
void imprimirMensajes() {
    while (true) {
        cout << "Hola " << flush;
        this_thread::sleep_for(chrono::milliseconds(500));
        cout << "Adios " << flush;
        this_thread::sleep_for(chrono::milliseconds(500));
    }
}

int main() {
    std::thread olivia(vegetable_chopper, "Olivia");
    std::thread barron(vegetable_chopper, "Barron");
    
    printf("Barron and Olivia are chopping vegetables...\n");
    std::this_thread::sleep_for(std::chrono::seconds(1));
    chopping = false;
    
    barron.join();
    olivia.join();

    // Ejecutar la calculadora
    calculadora();

    // Crear hilo para imprimir mensajes
    thread hiloMensajes(imprimirMensajes);

    hiloMensajes.join();

    return 0;
}