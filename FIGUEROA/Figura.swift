import Foundation

// Clase base Figura
class Figura {

    var nombre: String

    init(nombre: String) {
        self.nombre = nombre
    }

    func calcularArea() -> Double {
        return 0
    }

    func calcularPerimetro() -> Double {
        return 0
    }

    func dibujar() {
    }

    func mostrarInformacion() {
        print("Figura: \(nombre)")
        print("Área: \(calcularArea())")
        print("Perímetro: \(calcularPerimetro())")
    }
}

// Clase Cuadrado
class Cuadrado: Figura {

    var lado: Int

    init(lado: Int) {
        self.lado = lado
        super.init(nombre: "Cuadrado")
    }

    override func calcularArea() -> Double {
        return Double(lado * lado)
    }

    override func calcularPerimetro() -> Double {
        return Double(4 * lado)
    }

    override func dibujar() {

        for i in 0..<lado {

            for j in 0..<lado {

                if i == 0 || i == lado - 1 ||
                    j == 0 || j == lado - 1 {

                    print("*", terminator: " ")
                } else {
                    print(" ", terminator: " ")
                }
            }

            print()
        }
    }
}

// Clase Rectangulo
class Rectangulo: Figura {

    var ancho: Int
    var alto: Int

    init(ancho: Int, alto: Int) {
        self.ancho = ancho
        self.alto = alto
        super.init(nombre: "Rectangulo")
    }

    override func calcularArea() -> Double {
        return Double(ancho * alto)
    }

    override func calcularPerimetro() -> Double {
        return Double(2 * (ancho + alto))
    }

    override func dibujar() {

        for i in 0..<alto {

            for j in 0..<ancho {

                if i == 0 || i == alto - 1 ||
                    j == 0 || j == ancho - 1 {

                    print("*", terminator: " ")
                } else {
                    print(" ", terminator: " ")
                }
            }

            print()
        }
    }
}

// Programa principal

let figura1: Figura = Cuadrado(lado: 5)
let figura2: Figura = Rectangulo(ancho: 8, alto: 4)

figura1.mostrarInformacion()
figura1.dibujar()

print()

figura2.mostrarInformacion()
figura2.dibujar()