#ifndef KRUSKAL_H_INCLUDED
#define KRUSKAL_H_INCLUDED

#include "graph.h"

class Kruskal
{
private:
    Graph* graph;
    List<Edge*> MST;

public:
    Kruskal();
    void SetGraph();
    void LayoutNodes();
    void LayoutEdges();
    void Resolve();
    void LayoutSolution();
};

Kruskal::Kruskal()
{
    graph = new Graph();
};

void Kruskal::SetGraph()
{
    /// ======================= INGRESO LOS NODOS ============================
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
    /// ======================================================================
    /// ====================== INGRESO LAS ARISTAS ===========================
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
    /// ======================================================================
};

void Kruskal::LayoutNodes()
{
    cout << "Etiqueta de los nodos: " << endl;
    for (int pos = 0; pos < graph->AmountOfNodes(); pos++)
    {
        cout << graph->GetNode(pos)->label << " ";
    };
    cout << endl << endl;
};

void Kruskal::LayoutEdges()
{
    Edge* arista;
    for (int pos = 0; pos < graph->AmountOfEdges(); pos++)
    {
        arista = graph->GetEdge(pos);
        cout << "Arista en la pos: " << pos << endl;
        cout << "Nodo A: " << arista->nodeA->label << endl;
        cout << "Nodo B: " << arista->nodeB->label << endl;
        cout << "Peso: " << arista->weigth << endl << endl;
    };
};

void Kruskal::Resolve()
{
    graph->SortEdgesAsc();
    Node* origen;
    Node* destino;
    int peso;

    /// ============ FOR DEBUGGING PURPOSES ==============

    LayoutEdges();

    /// ==================================================

    for(int pos = 0; pos < graph->AmountOfEdges(); pos++)
    {
        origen = graph->GetEdge(pos)->nodeA;
        destino = graph->GetEdge(pos)->nodeB;
        peso = graph->GetEdge(pos)->weigth;


        if ( MST.GetSize() <= 0) /// si la lista de solucion está vacia agrego la arista directamente
        {
            Edge* edge = new Edge(origen,destino,peso);
            MST.Insert(edge);
        }
        else /// verificar si estan en la misma componente conexa
        {
            bool noConexo = true;
            for (int pos = 0; pos < MST.GetSize(); pos++)
            {
                Edge* actual = MST.GetItem(pos);
                if ( actual->nodeA == origen || actual->nodeB == origen ||
                     actual->nodeA == destino || actual->nodeB == destino
                   )
                {
                    noConexo = noConexo*false;
                }
                else
                {
                    noConexo = noConexo*true;
                };
            };

            if (noConexo)
            {
                Edge* edge = new Edge(origen,destino,peso);
                MST.Insert(edge);
            }
            else
            {
              /// agregar si no forma ciclo

            };
        };
    };
};

void Kruskal::LayoutSolution()
{
  int total = 0;
  for (int idx = 0; idx < MST.GetSize(); idx++ )
  {
      Edge* actual = MST.GetItem(idx);
      total = total + actual->weigth;
  };

  cout << "Peso total: " << total << endl;
  for (int pos = 0; pos < MST.GetSize(); pos++)
  {
      Edge* actual = MST.GetItem(pos);
      cout << "(" << actual->nodeA->label << " ; " << actual->nodeB->label << ") : " << actual->weigth << endl;
  };
};

#endif // KRUSKAL_H_INCLUDED
