#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

using namespace std;

// Definición de la estructura para el motor
struct Motor {
    string codigo;
    string tipo;
    string fechaSalida;
    string especialista;
    int defectos;
    // Datos específicos para cada tipo de motor
    double maxRev;
    double consumo;
    int caballosFuerza;
    bool esArtesanal;
    double precioCosto;
};

// Definición de la estructura para el carro
struct Carro {
    string tipo;
    Motor motor;
    int plazas;
    double velocidad;
    string fechaSalida;
    // Datos específicos para cada tipo de carro
    double pesoCarroceria;
    int cantidadPuertas;
    int cantidadVelocidades;
    bool cambioUniversal;
    double costoTapiceria;
    double precioVenta;
};
// Función para generar un número de serie automático de 12 dígitos
string generarNumeroSerie() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dis(0, 9);

    string serial;
    for (int i = 0; i < 12; ++i) {
        serial += to_string(dis(gen));
    }
    return serial;
}
// Función para ingresar los datos de un motor
Motor ingresarDatosMotor() {
    Motor motor;
    motor.codigo = generarNumeroSerie(); // Generar automáticamente el número de serie
    cout << "Ingrese el tipo de motor: ";
    cin >> motor.tipo;
    cout << "Ingrese la fecha de salida del motor: ";
    cin >> motor.fechaSalida;
    cout << "Código del motor: " << motor.codigo << endl;
    // Ingresar más datos específicos según el tipo de motor
    return motor;
}

// Función para ingresar los datos de un carro
Carro ingresarDatosCarro(const vector<Motor>& motores) {
    Carro carro;
    cout << "Ingrese el tipo de carro: ";
    cin >> carro.tipo;
    cout << "Ingrese la cantidad de plazas: ";
    cin >> carro.plazas;
    cout << "Ingrese la velocidad del carro (km/h): ";
    cin >> carro.velocidad;
    cout << "Ingrese la fecha de salida del carro: ";
    cin >> carro.fechaSalida;
    // Buscar y asignar un motor disponible para el carro
    cout << "Ingrese el código del motor para este carro: ";
    string codigoMotor;
    cin >> codigoMotor;
    auto it = find_if(motores.begin(), motores.end(), [&](const Motor& m) { return m.codigo == codigoMotor; });
    if (it != motores.end()) {
        carro.motor = *it;
    } else {
        cout << "El motor con el código ingresado no está disponible." << endl;
        // Aquí puedes añadir lógica adicional si el motor no está disponible
    }
    // Ingresar más datos específicos según el tipo de carro
    return carro;
}

// Función para mostrar el listado de los motores por tipo disponibles
void mostrarMotoresDisponibles(const vector<Motor>& motores, const string& tipo) {
    cout << "Motores disponibles de tipo " << tipo << ":" << endl;
    for (const auto& motor : motores) {
        if (motor.tipo == tipo) {
            cout << "Código: " << motor.codigo << ", Fecha de salida: " << motor.fechaSalida << endl;
        }
    }
}

// Función para mostrar los carros de mayor velocidad
void mostrarCarrosMayorVelocidad(const vector<Carro>& carros) {
    cout << "Carros de mayor velocidad (más de 150 km/h):" << endl;
    for (const auto& carro : carros) {
        if (carro.velocidad > 150) {
            cout << "Tipo: " << carro.tipo << ", Velocidad: " << carro.velocidad << " km/h" << endl;
        }
    }
}

// Función para mostrar Datos del ómnibus de mayor capacidad
void mostrarOmnibusMayorCapacidad(const vector<Carro>& carros) {
    int maxCapacidad = 0;
    Carro omnibusMayorCapacidad;
    for (const auto& carro : carros) {
        if (carro.tipo == "ómnibus" && carro.plazas > maxCapacidad) {
            maxCapacidad = carro.plazas;
            omnibusMayorCapacidad = carro;
        }
    }
    cout << "Datos del ómnibus de mayor capacidad:" << endl;
    cout << "Tipo: " << omnibusMayorCapacidad.tipo << ", Plazas: " << omnibusMayorCapacidad.plazas << endl;
}

// Función para mostrar la ficha técnica de todos los carros
void mostrarFichaTecnicaCarros(const vector<Carro>& carros) {
    cout << "Ficha técnica de todos los carros:" << endl;
    for (const auto& carro : carros) {
        cout << "Tipo: " << carro.tipo << ", Fecha de salida: " << carro.fechaSalida << endl;
        cout << "Motor - Código: " << carro.motor.codigo << ", Tipo: " << carro.motor.tipo << endl;
        // Mostrar más detalles del motor si es necesario
    }
}

// Función para dar de baja un carro que no pase la prueba
void darDeBajaCarro(vector<Carro>& carros) {
    string codigoCarro;
    cout << "Ingrese el código del carro a dar de baja: ";
    cin >> codigoCarro;
    auto it = find_if(carros.begin(), carros.end(), [&](const Carro& c) { return c.motor.codigo == codigoCarro; });
    if (it != carros.end()) {
        cout << "Carro dado de baja exitosamente." << endl;
        carros.erase(it);
    } else {
        cout << "El carro con el código ingresado no existe." << endl;
    }
}

// Función para mostrar un listado con los carros que tengan motores reenzamblados
void mostrarCarrosMotoresReenzamblados(const vector<Carro>& carros) {
    cout << "Carros con motores reenzamblados y su disminución de precio de venta:" << endl;
    for (const auto& carro : carros) {
        if (carro.motor.defectos > 0) {
            double disminucion = carro.motor.defectos * 100; // Supongamos que cada defecto disminuye el precio en 100 unidades
            cout << "Tipo: " << carro.tipo << ", Disminución de precio: " << disminucion << endl;
        }
    }
}

// Función para calcular el porcentaje de cumplimiento del plan de motores y carros de la planta
void calcularPorcentajeCumplimiento(const vector<Motor>& motores, const vector<Carro>& carros, int totalMotores, int totalCarros) {
    int motoresProducidos = motores.size();
    int carrosProducidos = carros.size();
    double porcentajeMotores = (motoresProducidos / static_cast<double>(totalMotores)) * 100;
    double porcentajeCarros = (carrosProducidos / static_cast<double>(totalCarros)) * 100;
    cout << "Porcentaje de cumplimiento del plan de motores: " << porcentajeMotores << "%" << endl;
    cout << "Porcentaje de cumplimiento del plan de carros: " << porcentajeCarros << "%" << endl;
}

// Función para calcular la ganancia total de la ensambladora dividida por tipo de carro
void calcularGananciaTotal(const vector<Carro>& carros) {
    double gananciaFormula1 = 0, gananciaSport = 0, gananciaOmnibus = 0, gananciaLujo = 0;
    for (const auto& carro : carros) {
        if (carro.tipo == "formula1") {
            gananciaFormula1 += carro.precioVenta;
        } else if (carro.tipo == "sport") {
            gananciaSport += carro.precioVenta;
        } else if (carro.tipo == "ómnibus") {
            gananciaOmnibus += carro.precioVenta;
        } else if (carro.tipo == "lujo") {
            gananciaLujo += carro.precioVenta;
        }
    }
    cout << "Ganancia total dividida por tipo de carro:" << endl;
    cout << "Formula1: " << gananciaFormula1 << endl;
    cout << "Sport: " << gananciaSport << endl;
    cout << "Ómnibus: " << gananciaOmnibus << endl;
    cout << "Lujo: " << gananciaLujo << endl;
}

int main() {
    vector<Motor> motores;
    Motor motor = ingresarDatosMotor();
    vector<Carro> carros;
    int totalMotores, totalCarros;

    cout << "Ingrese el número total de motores que se planea producir: ";
    cin >> totalMotores;
    cout << "Ingrese el número total de carros que se planea producir: ";
    cin >> totalCarros;

    // Entrada de datos para motores
    for (int i = 0; i < totalMotores; ++i) {
        cout << "Ingrese los datos del motor " << i + 1 << ":" << endl;
        Motor motor = ingresarDatosMotor();
        motores.push_back(motor);
    }

    // Entrada de datos para carros
    for (int i = 0; i < totalCarros; ++i) {
        cout << "Ingrese los datos del carro " << i + 1 << ":" << endl;
        Carro carro = ingresarDatosCarro(motores);
        carros.push_back(carro);
    }

    // Menú de opciones
    int opcion;
    do {
        cout << "\nMenú de opciones:" << endl;
        cout << "1. Mostrar listado de motores por tipo disponibles." << endl;
        cout << "2. Mostrar los carros de mayor velocidad." << endl;
        cout << "3. Mostrar datos del ómnibus de mayor capacidad." << endl;
        cout << "4. Mostrar la ficha técnica de todos los carros." << endl;
        cout << "5. Dar de baja un carro que no pase la prueba." << endl;
        cout << "6. Mostrar un listado con los carros que tengan motores reenzamblados y su disminución de precio de venta." << endl;
        cout << "7. Calcular porcentaje de cumplimiento del plan de motores y carros de la planta." << endl;
        cout << "8. Calcular ganancia total de la ensambladora dividida por tipo de carro." << endl;
        cout << "9. Salir." << endl;
        cout << "Ingrese la opción deseada: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                mostrarMotoresDisponibles(motores, "alta");
                mostrarMotoresDisponibles(motores, "fuerza");
                mostrarMotoresDisponibles(motores, "trabajo");
                break;
            case 2:
                mostrarCarrosMayorVelocidad(carros);
                break;
            case 3:
                mostrarOmnibusMayorCapacidad(carros);
                break;
            case 4:
                mostrarFichaTecnicaCarros(carros);
                break;
            case 5:
                darDeBajaCarro(carros);
                break;
            case 6:
                mostrarCarrosMotoresReenzamblados(carros);
                break;
            case 7:
                calcularPorcentajeCumplimiento(motores, carros, totalMotores, totalCarros);
                break;
            case 8:
                calcularGananciaTotal(carros);
                break;
            case 9:
                cout << "Saliendo del programa..." << endl;
                break;
            default:
                cout << "Opción no válida. Por favor, seleccione una opción válida." << endl;
                break;
        }
    } while (opcion != 9);

    return 0;
}
