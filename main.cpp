#include <iostream>
#include <string>
#include <ctime>

using namespace std;

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

    void registrarVenta(Transaccion* nuevaTransaccion) {
    }

    // Otros métodos...
};

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
        delete[] capacidadTanque; // Liberar memoria
        // Liberar memoria de surtidores
        for (int i = 0; i < numSurtidores; ++i) {
            delete surtidores[i];
        }
        delete[] surtidores;
    }

    void agregarSurtidor(Surtidor* nuevoSurtidor) {
    }

    // Otros métodos...
};

class RedNacional {
private:
    EstacionDeServicio** estaciones; // Puntero a un arreglo dinámico de estaciones de servicio
    int numEstaciones; // Contador de estaciones
    float* preciosPorRegion; // Puntero a un arreglo dinámico para precios por región
    int numRegiones; // Cantidad de regiones

public:
    RedNacional(int numRegiones) {
        this->numEstaciones = 0;
        this->estaciones = nullptr; // Inicialmente sin estaciones
        this->numRegiones = numRegiones;
        this->preciosPorRegion = new float[numRegiones]; // Asignar espacio para precios
    }

    ~RedNacional() {
        delete[] preciosPorRegion; // Liberar memoria
        // Liberar memoria de estaciones
        for (int i = 0; i < numEstaciones; ++i) {
            delete estaciones[i];
        }
        delete[] estaciones;
    }

    void agregarEstacion(EstacionDeServicio* nuevaEstacion) {

    }

};

int main() {
    // Prueba de funcionalidad aquí
    return 0;
}
