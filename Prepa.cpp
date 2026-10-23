#include <iostream>

struct Node
{
    int data;
    Node *next;
    Node *prev;
};

// Tu función Append tradicional para iniciar la lista
void Append(Node *&head, int value)
{
    Node *new_node = new Node{value, nullptr, nullptr};

    if (head == nullptr)
    {
        head = new_node;
        return;
    }

    Node *current = head;
    while (current->next != nullptr)
    {
        current = current->next;
    }

    current->next = new_node;
    new_node->prev = current;
}

// Función auxiliar para conectar los extremos y volverla circular
void MakeCircular(Node *head)
{
    if (head == nullptr)
        return;

    Node *last = head;
    while (last->next != nullptr)
    {
        last = last->next;
    }

    // Cerramos el bucle
    last->next = head;
    head->prev = last;
}

// Impresión hacia adelante para lista circular (usando do-while)
void PrintCircularForward(Node *head)
{
    if (head == nullptr)
    {
        std::cout << "Lista vacia\n";
        return;
    }

    Node *current = head;
    do
    {
        std::cout << current->data << " ";
        current = current->next;
    } while (current != head);

    std::cout << '\n';
}

bool InsertAfter(Node *head, int target, int value)
{
    // 1. Si la lista está vacía, no hay dónde buscar
    if (head == nullptr)
    {
        return false;
    }

    Node *current = head;

    // 2. Usamos un do-while porque necesitamos revisar al menos una vez
    // y detenernos cuando volvamos a dar toda la vuelta al head.
    do
    {
        if (current->data == target)
        {
            // ¡Encontramos el target! Creamos el nuevo nodo
            Node *new_node = new Node{value, nullptr, nullptr};

            // Guardamos quién era el vecino de adelante
            Node *next_node = current->next;

            // Conectamos el nuevo nodo en medio de current y next_node
            current->next = new_node;
            new_node->prev = current;

            new_node->next = next_node;
            next_node->prev = new_node;

            return true; // Éxito
        }

        current = current->next;
    } while (current != head); // Si volvemos al inicio, la búsqueda terminó

    // 3. Si dimos toda la vuelta y no estaba el target, retornamos false
    return false;
}

// Impresión hacia atrás para lista circular
void PrintCircularBackward(Node *head)
{
    if (head == nullptr)
    {
        std::cout << "Lista vacia\n";
        return;
    }

    // Empezamos desde el último nodo (head->prev) y retrocedemos
    Node *last = head->prev;
    Node *current = last;

    do
    {
        std::cout << current->data << " ";
        current = current->prev;
    } while (current != last);

    std::cout << '\n';
}

void MoveLastToFront(Node *&head)
{
    // 1. Si la lista está vacía o solo tiene un nodo, no hay nada que mover
    if (head == nullptr || head->next == head)
    {
        return;
    }

    // 2. Como es circular, el último nodo está justo atrás del head (head->prev).
    // Para moverlo al frente, simplemente recorremos el head hacia atrás.
    head = head->prev;
}

#include <stack>

void RemoveFromStack(std::stack<int> &tasks, int target)
{
    std::stack<int> auxiliary;

    // 1. Sacamos todo de tasks y filtramos el target, guardándolo en auxiliary
    while (!tasks.empty())
    {
        int value = tasks.top();
        tasks.pop();

        if (value != target)
        {
            auxiliary.push(value);
        }
    }

    // 2. Devolvemos los elementos a la pila original para restaurar el orden
    while (!auxiliary.empty())
    {
        tasks.push(auxiliary.top());
        auxiliary.pop();
    }
}

// Función auxiliar para imprimir la pila 
// (Recibe la pila por valor 's' para hacer una copia y no destruir la original)
void PrintStack(std::stack<int> s) {
    while (!s.empty()) {
        std::cout << s.top() << " ";
        s.pop();
    }
    std::cout << '\n';
}

#include <iostream>
#include <stack>

void RotateStack(std::stack<int>& s, int k) {
    if (s.empty() || k <= 0) return;

    // 1. Contar elementos y pasar a una auxiliar para medir el tamaño
    int n = 0;
    std::stack<int> aux1;
    while (!s.empty()) {
        aux1.push(s.top());
        s.pop();
        n++;
    }

    // Ajustar k si supera el tamaño
    k = k % n;
    if (k == 0) {
        // Restaurar la pila original
        while (!aux1.empty()) {
            s.push(aux1.top());
            aux1.pop();
        }
        return;
    }

    // aux1 actualmente tiene el fondo en el top (orden original de abajo hacia arriba)
    // Queremos rotar k elementos.
    // Vamos a separar los elementos en dos grupos usando pilas auxiliares.
    
    std::stack<int> group1; // Contendrá los elementos que se mueven
    std::stack<int> group2; // Contendrá los elementos que se quedan

    // Pasamos todo a group2 para procesarlo cómodamente
    while (!aux1.empty()) {
        group2.push(aux1.top());
        aux1.pop();
    }

    // Separamos los primeros k elementos
    for (int i = 0; i < k; ++i) {
        group1.push(group2.top());
        group2.pop();
    }

    // Reconstruimos la pila original metiendo primero los que se quedaron (group2) 
    // y luego los que se movieron (group1), invirtiendo con otra auxiliar si es necesario
    std::stack<int> final_aux;
    while (!group2.empty()) {
        final_aux.push(group2.top());
        group2.pop();
    }
    while (!group1.empty()) {
        final_aux.push(group1.top());
        group1.pop();
    }

    // Finalmente pasamos todo a 's' respetando el orden de la pila
    while (!final_aux.empty()) {
        s.push(final_aux.top());
        final_aux.pop();
    }
}



int main()
{
    Node *head = nullptr;

    // 1. Usamos tu Append normal
    Append(head, 10);
    Append(head, 20);
    Append(head, 30);
    Append(head, 40);
    Append(head, 50);

    // ejercicio 1.1

    /*
    // --- CERRAMOS EL CÍRCULO (Paso obligatorio para lista circular) ---
    Node* last = head;
    while (last->next != nullptr) {
        last = last->next;
    }
    // Conectamos los extremos
    last->next = head;
    head->prev = last;
    // -----------------------------------------------------------------

    std::cout << "Lista circular original:\n";
    PrintCircularForward(head);

    // 2. Insertamos 25 después del 20
    InsertAfter(head, 20, 25);

    std::cout << "Despues de insertar 25:\n";
    PrintCircularForward(head);*/

    // ejercicio 1.3
    /*MakeCircular(head);
    PrintCircularForward(head);
    MoveLastToFront(head);
    PrintCircularForward(head);*/

    std::stack<int> tasks;

    tasks.push(10);
    tasks.push(20);
    tasks.push(30);
    tasks.push(20);
    tasks.push(40);

    PrintStack(tasks);
    RotateStack(tasks, 2);
    PrintStack(tasks);
    return 0;
}