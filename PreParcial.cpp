#include <iostream>
#include <stack>
#include <queue>

struct Node
{
    int data;
    Node *next;
    Node *prev;
};

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

void PrintForward(Node *head)
{
    Node *current = head;

    while (current != nullptr)
    {
        std::cout << current->data << " ";
        current = current->next;
    }

    std::cout << '\n';
}

void PrintBackward(Node *head)
{
    if (head == nullptr)
    {
        return;
    }

    Node *current = head;

    while (current->next != nullptr)
    {
        current = current->next;
    }

    while (current != nullptr)
    {
        std::cout << current->data << " ";
        current = current->prev;
    }

    std::cout << '\n';
}

bool InsertAfter(Node *head, int target, int value)
{

    Node *current = head;

    while (current != nullptr)
    {
        if (current->data == target)
        {
            Node *new_node = new Node{value, nullptr, nullptr};

            new_node->prev = current;
            new_node->next = current->next;

            if (current->next != nullptr)
            {
                current->next->prev = new_node;
            }

            current->next = new_node;
            return true;
        }
        current = current->next;
    }
    return false;
}

void MoveLastToFront(Node *&head)
{

    // 2. Buscamos el último nodo de la lista (el 50).
    Node *current = head;
    while (current->next != nullptr)
    {
        current = current->next;
    }
    Node *last = current; // 'last' ya tiene al 50

    // 3. Desconectamos al 50 de su penúltimo compañero (el 40).
    // El 40 ahora debe ser el nuevo final de la cola.
    last->prev->next = nullptr;

    // 4. Pegamos al 50 al principio de todo:
    last->next = head;    // El next del 50 apunta al viejo primero (el 10).
    head->prev = last;    // El prev del viejo primero (el 10) ahora apunta al 50.
    last->prev = nullptr; // Como el 50 ya es el rey, su prev apunta a la nada.

    // 5. Actualizamos el letrero oficial 'head' para que apunte al 50.
    head = last;
}

void RemoveFromStack(std::stack<int> &tasks, int target)
{
    std::stack<int> auxiliary;
    std::cout<<"la pila es: "<<std::endl;
    while (!tasks.empty())
    {
        int value = tasks.top();
        tasks.pop();

        if (value != target)
        {
            auxiliary.push(value);
        }
    }

    //aqui mete las cosas del auxiliar a tasks de nuevo, revirtiendo el orden
    while (!auxiliary.empty())
    {
        tasks.push(auxiliary.top());
        auxiliary.pop();
    }

    //aqui imprime lol
    std::stack<int> copiaParaImprimir = tasks; 
    
    while (!copiaParaImprimir.empty())
    {
        std::cout << copiaParaImprimir.top() << std::endl; // Imprime la de arriba (40, luego 30, luego 10)
        copiaParaImprimir.pop();                           // Saca la papa copiada
    }
}

void ImprimirCola(std::queue<int> q) {
    // Recibimos 'q' como copia (sin el '&'), así que podemos destruirla aquí dentro
    std::cout << "\nContenido de la cola:" << std::endl;
    
    while (!q.empty()) {
        std::cout << q.front() <<" "; // Mostramos el que está al frente
        q.pop();                             // Lo sacamos de la copia
    }
}


void RotateQueue(std::queue<int>& requests, int k) {
  
    std::queue<int> auxiliary;
    std::queue<int> rotate;
    int i = 1;

    if (requests.empty() || k <= 0) return; 
    while (!requests.empty() && i<=k)
    {
        int value = requests.front();
        requests.pop();
        requests.push(value);
        i++;
    }
}

void InsertionSort(int values[], int size, int start, int end) {

        if (start < 0 || end >= size || start >= end) {
        return; 
    } //validacion

  for (int i = start + 1; i < end; ++i) { //se cambia 1 por start +1 y el size por el end
    int key = values[i];
    int j = i - 1;

    while (j >= start && values[j] > key) {
      values[j + 1] = values[j];
      --j;
    }

    values[j + 1] = key;
  }
}

int BinarySearch(const int values[], int size, int target) {
  int left = 0;
  int right = size - 1;
  int result = -1;

  while (left <= right) {
    int mid = left + (right - left) / 2;

    if (values[mid] == target) {
      result = mid;
      right = mid - 1;
    } else if (values[mid] <target){
        right = mid -1;
    }else {
        left = mid +1;
    }
  }
    std::cout << "Buscando " << target << " -> Resultado: " << result << std::endl;

  return result;
}

void SplitByPosition(Node*& head, Node*& even_head, Node*& odd_head)
{
    // 1. Inicializamos las listas de destino vacías
    even_head = nullptr;
    odd_head = nullptr;

    if (head == nullptr)
    {
        return; // Si la lista está vacía, nos salimos
    }

    // Punteros para saber siempre cuál es el último nodo (cola) de cada lista nueva
    Node* even_tail = nullptr;
    Node* odd_tail = nullptr;

    Node* current = head;
    int pos = 0;

    // 2. Recorremos la lista original nodo por nodo
    while (current != nullptr)
    {
        // Guardamos el siguiente nodo antes de movernos o desconectar
        Node* next_node = current->next;

        // Limpiamos los punteros del nodo actual para aislarlo
        current->next = nullptr;
        current->prev = nullptr;

        if (pos % 2 == 0) // Posiciones pares (0, 2, 4...)
        {
            if (even_head == nullptr)
            {
                even_head = current; // Si es el primero, es la cabeza y la cola
                even_tail = current;
            }
            else
            {
                even_tail->next = current; // Lo pegamos al final de la lista par
                current->prev = even_tail;
                even_tail = current;       // Actualizamos la cola par
            }
        }
        else // Posiciones impares (1, 3, 5...)
        {
            if (odd_head == nullptr)
            {
                odd_head = current; // Si es el primero, es la cabeza y la cola
                odd_tail = current;
            }
            else
            {
                odd_tail->next = current;  // Lo pegamos al final de la lista impar
                current->prev = odd_tail;
                odd_tail = current;        // Actualizamos la cola impar
            }
        }

        current = next_node;
        pos++;
    }

    // 3. Por requisito, la lista original debe quedar en nullptr al terminar
    head = nullptr;
}

using namespace std;

int main()
{

    Node *head = nullptr;

    /*
    Append(head, 10);
    Append(head, 20);
    Append(head, 30);
    Append(head, 40);
    Append(head, 50);*/

    // pruebas 1.1
    /*PrintForward(head);
    InsertAfter(head, 10, 25);
    PrintForward(head);
    PrintBackward(head);*/

    // pruebas 1.3
    /*PrintForward(head);
    MoveLastToFront(head);
    PrintForward(head);*/

    // pruebas 2.1  y 2.2 en realidad es queue y stack
    /*std::queue<int> tasks;

    tasks.push(10);
    tasks.push(20);
    tasks.push(30);
    tasks.push(40);
    tasks.push(50);*/

    /*
    RemoveFromStack(tasks, 20);*/

    /*
    ImprimirCola(tasks);
    RotateQueue(tasks, 2);
    ImprimirCola(tasks);*/

    //prueba 3.1
    /*int values[] = {9, 7, 5, 4, 3, 8, 1, 6};
    InsertionSort(values, 8, 2, 5);

    //solo para imprimirlo
    std::cout << "Resultado obtenido: ";
    for (int i = 0; i < 8; ++i) {
        std::cout << values[i] << " ";
    }
    std::cout << std::endl;*/

    //prueba 3.2
    /*
    int values[] = {9, 7, 7, 7, 5, 3, 1};
    BinarySearch(values, 7, 7);
    BinarySearch(values, 7, 4);
    BinarySearch(values, 7, 9);*/

    //prueba 1.2

    Node* even_head = nullptr;
    Node* odd_head = nullptr;

    // 1. Llenamos la lista original
    Append(head, 10);
    Append(head, 20);
    Append(head, 30);
    Append(head, 40);
    Append(head, 50);
    Append(head, 60);
    Append(head, 70);

    // Imprimimos la original antes de separarla (para verificar)
    std::cout << "Lista original:\n";
    PrintForward(head);
    std::cout << "\n";

    // 2. Ejecutamos tu función para separar
    SplitByPosition(head, even_head, odd_head);

    // 3. Imprimimos la lista de posiciones pares (Even)
    std::cout << "Lista de posiciones pares (even_head):\n";
    PrintForward(even_head);
    std::cout << "Hacia atras:\n";
    PrintBackward(even_head);
    std::cout << "\n";

    // 4. Imprimimos la lista de posiciones impares (Odd)
    std::cout << "Lista de posiciones impares (odd_head):\n";
    PrintForward(odd_head);
    std::cout << "Hacia atras:\n";
    PrintBackward(odd_head);
    std::cout << "\n";

    // 5. Verificamos que la original quedó en nullptr
    if (head == nullptr) {
        std::cout << "La lista original esta ahora en nullptr\n";
    }

    return 0;

    //n(n-1)/2
}