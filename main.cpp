#include <iostream>
#include <string>
#include <ctime>

using namespace std;

// Clase Transaccion para registrar una transacción de combustible
class Transaccion {
private:
    string fecha;  // Formato: YYYY-MM-DD
    string hora;   // Formato: HH:MM:SS
    float cantidad;
    string categoriaCombustible;
    string metodoPago;
    string documentoCliente;
    float monto;

public:
    Transaccion(float cantidad, string categoriaCombustible, string metodoPago, string documentoCliente, float monto) {
        this->cantidad = cantidad;
        this->categoriaCombustible = categoriaCombustible;
        this->metodoPago = metodoPago;
        this->documentoCliente = documentoCliente;
        this->monto = monto;

        // Obtener la fecha y hora actual
        time_t t = time(0); // Obtener el tiempo actual
        struct tm* now = localtime(&t);

        // Formatear la fecha como YYYY-MM-DD
        fecha = to_string(now->tm_year + 1900) + "-" +
                to_string(now->tm_mon + 1) + "-" +
                to_string(now->tm_mday);

        // Formatear la hora como HH:MM:SS
        hora = to_string(now->tm_hour) + ":" +
               to_string(now->tm_min) + ":" +
               to_string(now->tm_sec);
    }

    // Métodos getter para los atributos
    string getFecha() const {
        return fecha;
    }

    string getHora() const {
        return hora;
    }

    float getCantidad() const {
        return cantidad;
    }

    string getCategoriaCombustible() const {
        return categoriaCombustible;
    }

    string getMetodoPago() const {
        return metodoPago;
    }

    string getDocumentoCliente() const {
        return documentoCliente;
    }

    float getMonto() const {
        return monto;
    }
};

// Clase Surtidor para manejar los surtidores de combustible
class Surtidor {
private:
    string codigo;
    string modelo;
    bool activo;
    Transaccion** transacciones; // Puntero a un arreglo dinámico de transacciones
    int numTransacciones; // Contador de transacciones

public:
    Surtidor(string codigo, string modelo) {
        this->codigo = codigo;
        this->modelo = modelo;
        this->activo = true;
        this->transacciones = nullptr; // Inicialmente sin transacciones
        this->numTransacciones = 0;
    }

    ~Surtidor() {
        // Liberar memoria de transacciones
        for (int i = 0; i < numTransacciones; ++i) {
            delete transacciones[i];
        }
        delete[] transacciones;
    }

    void registrarVenta(Transaccion* nuevaTransaccion) {
        // Crear un nuevo arreglo dinámico con un espacio adicional
        Transaccion** nuevoArreglo = new Transaccion*[numTransacciones + 1];

        // Copiar las transacciones existentes al nuevo arreglo
        for (int i = 0; i < numTransacciones; ++i) {
            nuevoArreglo[i] = transacciones[i];
        }

        // Agregar la nueva transacción al arreglo
        nuevoArreglo[numTransacciones] = nuevaTransaccion;

        // Liberar la memoria del arreglo anterior
        delete[] transacciones;

        // Actualizar el puntero y el contador de transacciones
        transacciones = nuevoArreglo;
        numTransacciones++;
    }

};

// Clase EstacionDeServicio para gestionar las estaciones de servicio
class EstacionDeServicio {
private:
    string nombre;
    string codigo;
    string gerente;
    string region;
    float* capacidadTanque; // Puntero a un arreglo dinámico de capacidades
    int numCategorias; // Cantidad de categorías
    Surtidor** surtidores; // Puntero a un arreglo dinámico de surtidores
    int numSurtidores; // Contador de surtidores

public:
    EstacionDeServicio(string nombre, string codigo, string gerente, string region, int numCategorias) {
        this->nombre = nombre;
        this->codigo = codigo;
        this->gerente = gerente;
        this->region = region;
        this->numCategorias = numCategorias;
        this->capacidadTanque = new float[numCategorias]; // Asignar espacio para capacidades
        this->surtidores = nullptr; // Inicialmente sin surtidores
        this->numSurtidores = 0;
    }

    ~EstacionDeServicio() {
        delete[] capacidadTanque; // Liberar memoria de capacidad del tanque
        for (int i = 0; i < numSurtidores; ++i) {
            delete surtidores[i];
        }
        delete[] surtidores; // Liberar memoria de surtidores
    }

    void agregarSurtidor(Surtidor* nuevoSurtidor) {
        // Crear un nuevo arreglo dinámico con un espacio adicional
        Surtidor** nuevoArreglo = new Surtidor*[numSurtidores + 1];

        // Copiar los surtidores existentes al nuevo arreglo
        for (int i = 0; i < numSurtidores; ++i) {
            nuevoArreglo[i] = surtidores[i];
        }

        // Agregar el nuevo surtidor al arreglo
        nuevoArreglo[numSurtidores] = nuevoSurtidor;

        // Liberar la memoria del arreglo anterior
        delete[] surtidores;

        // Actualizar el puntero y el contador de surtidores
        surtidores = nuevoArreglo;
        numSurtidores++;
    }

};

// Clase RedNacional para gestionar la red nacional de estaciones de servicio
class RedNacional {
private:
    EstacionDeServicio** estaciones; // Puntero a un arreglo dinámico de estaciones de servicio
    int numEstaciones; // Contador de estaciones
    float* preciosPorRegion; // Puntero a un arreglo dinámico para precios por región
    int numRegiones; // Cantidad de regiones

public:
    RedNacional(int numRegiones) {
        this->numEstaciones = 0;
        this->estaciones = nullptr; // Inicialmente esta sin estaciones
        this->numRegiones = numRegiones;
        this->preciosPorRegion = new float[numRegiones]; // Asignar espacio para precios
    }

    ~RedNacional() {
        delete[] preciosPorRegion; // Liberar memoria de precios por región
        for (int i = 0; i < numEstaciones; ++i) {
            delete estaciones[i];
        }
        delete[] estaciones; // Liberar memoria de estaciones
    }

    void agregarEstacion(EstacionDeServicio* nuevaEstacion) {
        // Crear un nuevo arreglo dinámico con un espacio adicional
        EstacionDeServicio** nuevoArreglo = new EstacionDeServicio*[numEstaciones + 1];

        // Copiar las estaciones existentes al nuevo arreglo
        for (int i = 0; i < numEstaciones; ++i) {
            nuevoArreglo[i] = estaciones[i];
        }

        // Agregar la nueva estación al arreglo
        nuevoArreglo[numEstaciones] = nuevaEstacion;

        // Liberar la memoria del arreglo anterior
        delete[] estaciones;

        // Actualizar el puntero y el contador de estaciones
        estaciones = nuevoArreglo;
        numEstaciones++;
    }

};

int main() {
    //Estamos realizando una prueba del programa desde aquí
    RedNacional redNacional(3);

    // Crear una nueva estación de servicio
    EstacionDeServicio* estacion1 = new EstacionDeServicio("Estacion 1", "E001", "Juan Perez", "Centro", 3);
    redNacional.agregarEstacion(estacion1);

    // Crear un surtidor y agregarlo a la estación
    Surtidor* surtidor1 = new Surtidor("S001", "Modelo A");
    estacion1->agregarSurtidor(surtidor1);

    // Registrar una venta
    Transaccion* transaccion1 = new Transaccion(20.5, "Regular", "Efectivo", "123456789", 50000);
    surtidor1->registrarVenta(transaccion1);

    // Mostrar información de la transacción
    cout << "Fecha de la transaccion: " << transaccion1->getFecha() << endl;
    cout << "Hora de la transaccion: " << transaccion1->getHora() << endl;
    cout << "Cantidad de combustible: " << transaccion1->getCantidad() << " litros" << endl;

    return 0;
}
