#include <iostream>
#include <string>
#include <vector>

// Clase Transaccion
class Transaccion {
private:
    std::string fecha;
    std::string hora;
    float cantidad;
    std::string categoriaCombustible;
    std::string metodoPago;
    std::string documentoCliente;
    float monto;

public:
    Transaccion() = default;
    // Métodos y lógica adicional para Transaccion se implementarán más adelante.
};

// Clase Surtidor
class Surtidor {
private:
    std::string codigo;
    std::string modelo;
    bool activo;
    std::vector<Transaccion> transacciones;

public:
    Surtidor() = default;

    void registrarVenta(const Transaccion& nuevaTransaccion);
    std::vector<Transaccion> consultarTransacciones() const;
    void simularVenta(const std::string& categoriaCombustible, float cantidad);
};

// Clase EstacionDeServicio
class EstacionDeServicio {
private:
    std::string nombre;
    std::string codigo;
    std::string gerente;
    std::string region;
    std::pair<float, float> ubicacionGPS;
    std::vector<std::pair<std::string, float>> capacidadTanque;
    std::vector<Surtidor> surtidores;

public:
    EstacionDeServicio() = default;

    void agregarSurtidor(const Surtidor& nuevoSurtidor);
    void eliminarSurtidor(const std::string& codigoSurtidor);
    void activarSurtidor(const std::string& codigoSurtidor);
    void desactivarSurtidor(const std::string& codigoSurtidor);
    std::vector<Transaccion> consultarHistoricoTransacciones(const std::string& codigoSurtidor) const;
    void simularVenta(const std::string& categoriaCombustible, float cantidad);
    void asignarCapacidadTanque();
};

// Clase RedNacional
class RedNacional {
private:
    std::vector<EstacionDeServicio> estaciones;
    std::vector<std::pair<std::string, float>> preciosPorRegion;

public:
    RedNacional() = default;

    void agregarEstacion(const EstacionDeServicio& nuevaEstacion);
    void eliminarEstacion(const std::string& codigoEstacion);
    void fijarPrecios(const std::vector<std::pair<std::string, float>>& nuevosPrecios);
    float calcularVentas(const std::string& codigoEstacion, const std::string& categoriaCombustible) const;
};

int main() {
    // Aquí se puede escribir código para pruebas iniciales y para interactuar con las clases.
    std::cout << "Sistema de Gestión de Red Nacional de Combustible Iniciado." << std::endl;
    return 0;
}
