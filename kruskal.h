#ifndef KRUSKAL_H_INCLUDED
#define KRUSKAL_H_INCLUDED

#include "graph.h"

class Kruskal
{
private:
    Graph* graph;
    Graph* MST;

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
    MST = new Graph();
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


        if ( MST->AmountOfEdges() <= 0) /// si la lista de solucion está vacia agrego la arista directamente
        {
            MST->NewNode(origen->label);
            MST->NewNode(destino->label);
            MST->NewEdge(origen->label, destino->label, peso);

        }
        else /// verificar si estan en la misma componente conexa
        {
            bool noConexo = true;
            for (int pos = 0; pos < MST->AmountOfEdges(); pos++)
            {
                Edge* actual = MST->GetEdge(pos);
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
                MST->NewNode(origen->label);
                MST->NewNode(destino->label);
                MST->NewEdge(origen->label, destino->label, peso);
            }
            else
            {
                /// agregar si no forma ciclo (NO SE REPITE OTRO VERTICE QUE EL INICIAL COMO FINAL)
                Node* X = graph->GetNode( graph->GetNodePos(origen->label) );
                Node* Y = graph->GetNode( graph->GetNodePos(destino->label) );

                bool xNoEsta = true;
                bool yNoEsta = true;

                for (int pos = 0; pos < MST->AmountOfEdges(); pos++)
                {
                    Edge* cheked = MST->GetEdge(pos);

                    if (cheked->nodeA->label == X->label || cheked->nodeB->label == X->label ) xNoEsta = xNoEsta*false;
                    if (cheked->nodeA->label == Y->label || cheked->nodeB->label == Y->label ) yNoEsta = yNoEsta*false;
                }

                if ( xNoEsta )
                {
                    if ( yNoEsta )
                    {
                        /// como estan los dos nodos no puedo agregar la arista
                        /// porque se forma ciclo
                    }
                    else
                    {
                        MST->NewNode(Y->label);
                        MST->NewEdge(X->label, Y->label, peso);
                    };
                }
                else
                {
                    if ( yNoEsta )
                    {
                        MST->NewNode(X->label);
                        MST->NewEdge(X->label, Y->label, peso);
                    }
                    else
                    {
                        MST->NewNode(X->label);
                        MST->NewNode(Y->label);
                        MST->NewEdge(X->label, Y->label, peso);
                    };
                };
            };
        };
    };
};

void Kruskal::LayoutSolution()
{
  int total = 0;
  for (int idx = 0; idx < MST->AmountOfEdges(); idx++ )
  {
      Edge* actual = MST->GetEdge(idx);
      total = total + actual->weigth;
  };

  cout << "Peso total: " << total << endl;
  for (int pos = 0; pos < MST->AmountOfEdges(); pos++)
  {
      Edge* actual = MST->GetEdge(pos);
      cout << "(" << actual->nodeA->label << " ; " << actual->nodeB->label << ") : " << actual->weigth << endl;
  };
};

#endif // KRUSKAL_H_INCLUDED
