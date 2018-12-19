#include <iostream>
#include "graph.h"

using namespace std;

int test()
{
    Graph* graph = new Graph();

    /// ==================== INGRESO DE NODOS =============================
    cout << "Ingrese la cantidad de nodos que seran ingresados: " << endl;
    int cant;
    cin >> cant;

    for(int pos = 0; pos < cant; pos++)
    {
        string nodo;
        cout << "Ingrese nombre del nuevo nodo: " << endl;
        cin >> nodo;
        graph->NewNode(nodo);
    };


    /// ================ MUESTRO LOS NODOS INGRESADOS ======================
    cout << "Etiqueta de los nodos: " << endl;
    for (int pos = 0; pos < graph->AmountOfNodes(); pos++)
    {
        cout << graph->GetNode(pos)->label << " ";
    };
    cout << endl << endl;


    /// ==================== INGRESO LAS ARISTAS ===========================
    cout << "Ingrese la cantidad de ARISTAS que seran ingresadas: " << endl;
    int cantEdges;
    cin >> cantEdges;

    for(int pos = 0; pos < cantEdges; pos++)
    {
        string edgeNodoA, edgeNodoB;
        int peso;
        cout << "Ingrese la nueva Arista (NodoA NodoB Peso): " << endl;
        cin >> edgeNodoA >> edgeNodoB >> peso;

        graph->NewEdge(edgeNodoA, edgeNodoB, peso);
    };


    /// ================ MUESTRO LAS ARISTAS INGRESADOS ======================
    Edge* arista;
    for (int pos = 0; pos < graph->AmountOfEdges(); pos++)
    {
        arista = graph->GetEdge(pos);
        cout << "Arista en la pos: " << pos << endl;
        cout << "Nodo A: " << arista->nodeA->label << endl;
        cout << "Nodo B: " << arista->nodeB->label << endl;
        cout << "Peso: " << arista->weigth << endl << endl;
    };


    /// ================ EL GRAFO ES CONEXO? ======================
    /*if (graph->IsItConnected())
    {
        cout << "EL grafo es conexo" << endl;
    }
    else
    {
        cout << "EL grafo NO es conexo" << endl;
    };*/

    /// MUESTRO LAS ARISTAS INGRESADAS EN LA LISTA DE CONEXIONES DEL NODO ELEGIDO
    cout << "Ingrese un nodo para ver sus conexiones:" << endl;
    string nodoSeleccinado;
    cin >> nodoSeleccinado;

    Node* nodo = graph->GetNode( graph->GetNodePos(nodoSeleccinado) );

    int tamano = nodo->connections.GetSize();
    cout << "Cantidad de elementos: " << tamano << endl;

    int posConn = 0;
    while ( posConn < tamano)
    {
        arista = nodo->connections.GetItem(posConn);
        Node* pA = arista->nodeA;
        Node* pB = arista->nodeB;

        string labelA = pA->label;
        string labelB = pB->label;

        cout << "Conexion: " << posConn << endl;
        cout << labelA << " " << labelB << " " << arista->weigth << endl;

        posConn++;
    };


    /// ======================== BORRO UNA ARISTA ===============================
    string nodoX, nodoY;

    cout << "Ingrese los nodos de la arista a borrar: " << endl;
    cout << "Ingrese el primer nodo: ";
    cin >> nodoX;
    cout << endl << "Ingrese el segundo nodo: ";
    cin >> nodoY;
    cout << endl;

    Edge* targetEdge;
    // busco la arista
    for (int pos = 0; pos < graph->AmountOfEdges(); pos++)
    {
        Node* nA = graph->GetEdge(pos)->nodeA;
        Node* nB = graph->GetEdge(pos)->nodeB;
        if ( (nA->label == nodoX && nB->label == nodoY) || (nB->label == nodoX && nA->label == nodoY) )
        {
            targetEdge = graph->GetEdge(pos);
        }
    }

    graph->DelEdge(targetEdge);


    /// ================ EL GRAFO ES CONEXO? ======================
    /*if (graph->IsItConnected())
    {
        cout << "EL grafo es conexo" << endl;
    }
    else
    {
        cout << "EL grafo NO es conexo" << endl;
    };*/



    /// ================ MUESTRO LAS ARISTAS INGRESADOS ======================

    for (int pos = 0; pos < graph->AmountOfEdges(); pos++)
    {
        arista = graph->GetEdge(pos);
        cout << "Arista en la pos: " << pos << endl;
        cout << "Nodo A: " << arista->nodeA->label << endl;
        cout << "Nodo B: " << arista->nodeB->label << endl;
        cout << "Peso: " << arista->weigth << endl << endl;
    };

    posConn = 0;
    tamano = nodo->connections.GetSize();
    while ( posConn < tamano)
    {
        arista = nodo->connections.GetItem(posConn);
        Node* pA = arista->nodeA;
        Node* pB = arista->nodeB;

        string labelA = pA->label;
        string labelB = pB->label;

        cout << "Conexion: " << posConn << endl;
        cout << labelA << " " << labelB << " " << arista->weigth << endl;

        posConn++;
    };



/// ======================== BORRO UNA ARISTA ===============================
    cout << "Ingrese los nodos de la arista a borrar: " << endl;
    cout << "Ingrese el primer nodo: ";
    cin >> nodoX;
    cout << endl << "Ingrese el segundo nodo: ";
    cin >> nodoY;
    cout << endl;

    //Edge* targetEdge;
    // busco la arista
    for (int pos = 0; pos < graph->AmountOfEdges(); pos++)
    {
        Node* nA = graph->GetEdge(pos)->nodeA;
        Node* nB = graph->GetEdge(pos)->nodeB;
        if ( (nA->label == nodoX && nB->label == nodoY) || (nB->label == nodoX && nA->label == nodoY) )
        {
            targetEdge = graph->GetEdge(pos);
        }
    }

    graph->DelEdge(targetEdge);


    /// ================ EL GRAFO ES CONEXO? ======================
    /*if (graph->IsItConnected())
    {
        cout << "EL grafo es conexo" << endl;
    }
    else
    {
        cout << "EL grafo NO es conexo" << endl;
    };*/



    /// ================ MUESTRO LAS ARISTAS INGRESADOS ======================

    for (int pos = 0; pos < graph->AmountOfEdges(); pos++)
    {
        arista = graph->GetEdge(pos);
        cout << "Arista en la pos: " << pos << endl;
        cout << "Nodo A: " << arista->nodeA->label << endl;
        cout << "Nodo B: " << arista->nodeB->label << endl;
        cout << "Peso: " << arista->weigth << endl << endl;
    };

    posConn = 0;
    tamano = nodo->connections.GetSize();
    while ( posConn < tamano)
    {
        arista = nodo->connections.GetItem(posConn);
        Node* pA = arista->nodeA;
        Node* pB = arista->nodeB;

        string labelA = pA->label;
        string labelB = pB->label;

        cout << "Conexion: " << posConn << endl;
        cout << labelA << " " << labelB << " " << arista->weigth << endl;

        posConn++;
    };


    return 0;
}
