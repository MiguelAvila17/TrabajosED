// Para usar la entrada interactiva en JavaScript, generalmente se usa Node.js con 'readline' o 'prompt'
const readline = require('readline');
const rl = readline.createInterface({
    input: process.stdin,
    output: process.stdout
});

class Node {
    constructor(data) {
        this.data = data;
        this.left = null;
        this.right = null;
    }
}

// Función recursiva con callbacks para manejar la entrada asíncrona de Node.js
function createTreeAsync(callback) {
    console.log("Presiona 0 para salir");
    console.log("Presiona 1 para un nuevo nodo");
    
    rl.question("Ingresa la opción: ", (choiceInput) => {
        const choice = parseInt(choiceInput);

        if (choice === 0) {
            return callback(null);
        } else if (choice === 1) {
            rl.question("Ingresa los datos: ", (dataInput) => {
                const data = parseInt(dataInput);
                const temp = new Node(data);

                console.log(`Ingresa el nodo hijo izquierdo de ${data}`);
                createTreeAsync((leftNode) => {
                    temp.left = leftNode;

                    console.log(`Ingresa el nodo hijo derecho de ${data}`);
                    createTreeAsync((rightNode) => {
                        temp.right = rightNode;
                        callback(temp);
                    });
                });
            });
        } else {
            console.log("Opción no válida. Intenta de nuevo.");
            createTreeAsync(callback);
        }
    });
}

/*
// Ejemplo de uso:
// createTreeAsync((root) => {
//     console.log("Árbol creado:", root);
//     rl.close();
// });
*/