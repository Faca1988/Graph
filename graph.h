#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

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

    bool IsItMultiGraph();          /// PENDIENTE
    bool IsItConnected();           /// PENDIENTE
    bool IsItCyclical();            /// PENDIENTE
    Graph SplitGrapgh();            /// PENDIENTE
    void MergeGraph(Graph* graph);  /// PENDIENTE

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

    /*Edge* newEdge;
    for(int pos = 0; pos < edgeslist.GetSize(); pos++)
    {
        Edge* target = edgeslist.GetItem(pos);
        if ( (target->nodeA == nodoX && target->nodeB == nodoY) || (target->nodeA == nodoY && target->nodeB == nodoX) )
        {
            newEdge = target;
        };
    };*/

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
    return edgeslist.GetItem(pos);
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
    for(int pos = 0; pos < AmountOfEdges(); pos++)
    {
        if (
            ( edgeslist.GetItem(pos)->nodeA == pA && edgeslist.GetItem(pos)->nodeB == pB )
                                                  ||
            ( edgeslist.GetItem(pos)->nodeA == pB && edgeslist.GetItem(pos)->nodeB == pA )
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



#endif // GRAPH_H_INCLUDED
