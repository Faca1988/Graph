#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

#include <stack>
#include <queue>
#include <set>
#include "list.h"

struct Edge;
struct Node;

struct Edge
{
    Node* nodeA;
    Node* nodeB;
    int weigth;
    Edge(Node* pA, Node* pB, int _weigth)
    {
        this->nodeA = pA;
        this->nodeB = pB;
        this->weigth = _weigth;
    }
};

struct Node
{
    string label;
    List<Edge*> connections;
    Node(string _label)
    {
        this->label = _label;
        //this->connections = _connection;
    }
};

class Graph
{
private:
    List<Node*> nodeslist;
    List<Edge*> edgeslist;

    vector<bool> mark;
    void DFS(int nodePos);
    bool IsConnectedWithAll(Node* target);


public:
    Graph();

    void NewNode(string labelNode);
    int AmountOfNodes();
    Node* GetNode(int pos);
    int GetNodePos(string labelNode);
    int GetNodePos(Node* dirNode);
    Node DelNode(int pos);
    Node DelNode(string labelNode);
    Node DelNode(Node* node);

    void NewEdge(Node* pA, Node* pB, int weight); /// AGREGAR CREACION EN LA LISTA DE CONEXIONES DE LOS NODOS AFECTADOS (L: 141)
    void NewEdge(string labelNodeA, string labelNodeB, int weight);
    int AmountOfEdges();
    Edge* GetEdge(int pos);
    int GetEdgePos(Edge* dirEdge);
    int GetEdgePos(Node* pA, Node* pB);
    void DelEdge(int pos); /// AGREGAR ELIMINACION EN LA LISTA DE CONEXIONES DE LOS NODOS AFECTADOS (L: 208)
    void DelEdge(Edge* target);
    void DelEdge(Node* pA, Node* pB);

    bool IsItConnected();           /// Modificacion pendiente
    bool IsItMultiGraph();          /// Esperando resolucion IsItConnected()
    Graph SplitGraph();             /// Esperando resolucion IsItConnected()
    bool IsItCyclical();            /// PENDIENTE
    void MergeGraph(Graph* graph);

    void SortEdgesAsc();
    void SortEdgesDes();
};

Graph::Graph()
{
};

void Graph::NewNode(string labelNode)
{
    Node* n = new Node(labelNode);
    nodeslist.Insert( n );
};

Node Graph::DelNode(int pos)
{
    Node* deletedNode = nodeslist.GetItem(pos);

    /// BORRAR EDGES DONDE SE ENCUENTRE LA REFERENCIA A ESE NODO
    for(int idx = 0; idx < AmountOfEdges(); idx++)
    {
        Node* target = nodeslist.GetItem(pos);
        if (
            GetEdge(idx)->nodeA->label == target->label ||
            GetEdge(idx)->nodeB->label == target->label
           )
        {
          DelEdge(idx);
        };
    };

    nodeslist.EraseItem(pos);
    return  *deletedNode;
};

Node Graph::DelNode(string labelNode)
{
    int target;
    Node* nodo;
    for (int pos = 0; pos < AmountOfNodes(); pos++)
    {
        nodo = nodeslist.GetItem(pos);
        if (nodo->label == labelNode)
        {
            target = pos;
        };
    };
    return DelNode(target);
};

Node Graph::DelNode(Node* node)
{
    return DelNode(node->label);
};

Node* Graph::GetNode(int pos)
{
    return nodeslist.GetItem(pos);
};

int Graph::GetNodePos(string labelNode)
{
    int target;
    Node* nodo;
    for (int pos = 0; pos < AmountOfNodes(); pos++)
    {
        nodo = nodeslist.GetItem(pos);
        if ( nodo->label == labelNode )
        {
            target = pos;
        };
    };
    return target;
};

int Graph::GetNodePos(Node* dirNode)
{
    int target;
    for (int pos = 0; pos < AmountOfEdges(); pos++)
    {
        if (nodeslist.GetItem(pos) == dirNode)
        {
            target = pos;
        };
    };
    return target;
};

int Graph::AmountOfNodes()
{
    return nodeslist.GetSize();
};

void Graph::NewEdge(Node* pA, Node* pB, int weight)
{
    /// AGREGO LA NUEVA ARISTA A LA LISTA DE ARISTAS

    Edge* edge = new Edge(pA,pB,weight);
    edgeslist.Insert( edge );

    /// AGREGO LA NUEVA ARISTA A LAS CONEXIONES DE CADA NODO INVOLUCRADO
    int posX, posY;
    posX = nodeslist.GetItemPos(pA);
    posY = nodeslist.GetItemPos(pB);

    Node* nodoX = nodeslist.GetItem( posX );
    Node* nodoY = nodeslist.GetItem( posY );

    nodoX->connections.Insert( edge );
    nodoY->connections.Insert( edge );
};

void Graph::NewEdge(string labelNodeA, string labelNodeB, int weight)
{
    Node* nodoA;
    Node* nodoB;

    for(int idx = 0; idx < AmountOfNodes(); idx++)
    {
        if ( GetNode(idx)->label == labelNodeA )
        {
            nodoA = GetNode(idx);
        };

        if ( GetNode(idx)->label == labelNodeB )
        {
             nodoB = GetNode(idx);
        };
    };
    NewEdge(nodoA, nodoB, weight);
}

int Graph::AmountOfEdges()
{
    return edgeslist.GetSize();
};

Edge* Graph::GetEdge(int pos)
{
    Edge* result;
    /*(pos == NULL) ? result = nullptr :*/ result = edgeslist.GetItem(pos);
    return result;
};

int Graph::GetEdgePos(Edge* dirEdge)
{
    int target;
    for (int pos = 0; pos < AmountOfEdges(); pos++)
    {
        if ( edgeslist.GetItem(pos) == dirEdge )
        {
            target = pos;
        };
    };
    return target;
};

int Graph::GetEdgePos(Node* pA, Node* pB)
{
    int target;
    Edge* arista;
    for(int pos = 0; pos < AmountOfEdges(); pos++)
    {
        arista = GetEdge(pos);

        if (
            ( arista->nodeA == pA && arista->nodeB == pB )
                                  ||
            ( arista->nodeA == pB && arista->nodeB == pA )
           )
        {
            target = pos;
        };
    };
    return target;
};

void Graph::DelEdge(int pos)
{
    /// BORRAR PRIMERAMENTE LA ARISTA DE LA LISTA DE CONEXIONES DE CADA NODO INVOLUCRADO
    Node* nodoX = edgeslist.GetItem(pos)->nodeA;
    Node* nodoY = edgeslist.GetItem(pos)->nodeB;

    for (int posConn = 0; posConn < nodoX->connections.GetSize(); posConn++)
    {
        Edge* edge = nodoX->connections.GetItem(posConn);

        if ( edge->nodeA == nodoY || edge->nodeB == nodoY )
            nodoX->connections.EraseItem( posConn );
    };

    for (int posConn = 0; posConn < nodoY->connections.GetSize(); posConn++)
    {
        Edge* edge = nodoY->connections.GetItem(posConn);

        if ( edge->nodeA == nodoX || edge->nodeB == nodoX)
            nodoY->connections.EraseItem( posConn );
    };

    /// LUEGO BORRAR LA ARISTA DE LA LISTA DE ARISTAS
    edgeslist.EraseItem(pos);
};

void Graph::DelEdge(Edge* target)
{
    for(int pos = 0; pos < AmountOfEdges(); pos++)
    {
        if ( edgeslist.GetItem(pos) == target )
        {
            DelEdge(pos);
        };
    };
};

void Graph::DelEdge(Node* pA, Node* pB)
{
    DelEdge( GetEdgePos( pA, pB ) );
};

/*
bool Graph::IsItConnected()
{
    Node* originNode = GetNode(0); /// DEFINO COMO ORIGEN EL PRIMER NODO DE LA LISTA DE NODOS
    Node* targetNode = nullptr;
    /// Node* originNode->previousNode = null
    Node* currentNode = originNode;
    bool allConnected = true;
    List<Node*> visitedNodes;

    for (int index = 0; index < AmountOfNodes(); index++)
    {
        targetNode = GetNode(index); ///nodes[index]

        while( ( currentNode != null ) && ( currentNode != targetNode) )
         {
            Node* nextNode = nullptr;
            visitedNodes.Insert(currentNode);
            for (int idx = 0; idx < currentNode->connections.GetSize(), idx++)
            {

                Node* connectedNode;
                /// De la conexion de currentNode en la que estoy tomo el nodo con el que se asocia y lo asigno a connectedNode
                (currentNode->connections->GetItem(idx)->nodeA == currentNode)
                    ? connectedNode = currentNode->connections->GetItem(idx)->nodeB
                    : connectedNode = currentNode->connections->GetItem(idx)->nodeA;

                bool exist = false;
                for (int i = 0; i < visitedNodes.GetSize(); i++)
                {
                    if ( visitedNodes.GetItem(i) == connectedNode ) exist = true; /// si existe el connectedNode dentro de la lista de nodos visitados exist = true
                }

                if (!exist) /// si NO existe el connectedNode en la lista de visitados
                {
                    nextNode = connectedNode; /// el siguiente nodo (nextNode) es el connectedNode
                    break;
                }
            }
            if (nextNode == nullptr) /// si el siguiente nodo es nulo
            {
                currentNode = currentNode.previousNode
            }
            else /// si NO es nulo
            {
                previousNode = currentNode
                currentNode = nextNode
            }

         }
         if (currentNode == nullptr) /// si el currentNode es nulo quiere decir que no llegue al target
         {
            allConnected = false;
            break;
         }
    }
    return allConnected;
}
*/
bool Graph::IsItMultiGraph()
{
    bool result = true;

    /// if ( IsItConnected() ) result = false;

    return result;
}


void Graph::SortEdgesAsc()
{
    for (int pos = 0; pos < AmountOfNodes(); pos++)
    {
        for (int rev = pos+1; rev < AmountOfEdges(); rev++)
        {
            if ( GetEdge(pos)->weigth > GetEdge(rev)->weigth )
            {
                Edge* mayor = GetEdge(pos);

                GetEdge(pos)->nodeA = GetEdge(rev)->nodeA;
                GetEdge(pos)->nodeB = GetEdge(rev)->nodeB;
                GetEdge(pos)->weigth = GetEdge(rev)->weigth;

                GetEdge(rev)->nodeA = mayor->nodeA;
                GetEdge(rev)->nodeB = mayor->nodeB;
                GetEdge(rev)->weigth = mayor->weigth;
            };
        };
    };
}

void Graph::SortEdgesDes()
{
    for (int pos = 0; pos < AmountOfNodes(); pos++)
    {
        for (int rev = pos+1; rev < AmountOfEdges(); rev++)
        {
            if ( GetEdge(pos)->weigth < GetEdge(rev)->weigth )
            {
                Edge* menor = GetEdge(pos);

                GetEdge(pos)->nodeA = GetEdge(rev)->nodeA;
                GetEdge(pos)->nodeB = GetEdge(rev)->nodeB;
                GetEdge(pos)->weigth = GetEdge(rev)->weigth;

                GetEdge(rev)->nodeA = menor->nodeA;
                GetEdge(rev)->nodeB = menor->nodeB;
                GetEdge(rev)->weigth = menor->weigth;
            };
        };
    };
}

void Graph::MergeGraph(Graph* graph)
{
    for(int posG = 0; posG < graph->AmountOfNodes(); posG++)
    {
        nodeslist.Insert(graph->GetNode(posG));
    }
    for (int posG = 0; posG < graph->AmountOfEdges(); posG++)
    {
        edgeslist.Insert(graph->GetEdge(posG));
    }
}

Graph Graph::SplitGraph()
{
    cout << "Ingrese la cantidad de aristas a desconectar: ";
    int cantAristas = 0;
    cin >> cantAristas;
    cout << endl;
    for (int i = 0; i < cantAristas; i++)
    {
        string nodeX, nodeY;
        cout << "Ingrese los nodos involucrados en la " << i <<"º arista a desconectar: ";
        cin >> nodeX >> nodeY;

        Node* A = GetNode( GetNodePos(nodeX) );
        Node* B = GetNode( GetNodePos(nodeY) );

        DelEdge(A,B); // int pos - Node* A, Node* b - Edge* e
    }

    Graph* graph = new Graph();
    int exportedNodes = 0;
    cout << "Ingrese la cantidad de nodos a exportar ";
    cin >> exportedNodes;
    cout << endl;

    for (int i = 0; i < exportedNodes; i++)
    {
        string nodoExportado;
        cout << "Nodo a exportar: " << endl;
        cin >> nodoExportado;

        graph->NewNode(nodoExportado);
        DelNode( GetNodePos(nodoExportado) ); /// borra el nodo y sus conexiones con lo cual debo volver a cargar aristas despues. REVER CON IsItConnected()
    }


    return *graph;
}
#endif // GRAPH_H_INCLUDED
