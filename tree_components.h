#ifndef TREE_COMPONENTS_H_INCLUDED
#define TREE_COMPONENTS_H_INCLUDED

#include "list.h"

template < class Type>
struct Edge
{
    Type* nodeA;
    Type* nodeB;
    int* weigth;
};

template < class Type>
class TreeComponents
{
private:
    List<Type>* nodesList;
    vector< vector<int> > distances;
    vector< Edge<Type> > EdgesList;

    void __UpdateDistanceDimension();

public:
    TreeComponents();

    void NewNode(Type node);
    Type DeleteNode(Type* node);
    Type DeleteNode(int nodePos);
    Type* GetNode(int pos);
    int GetNode(Type node);
    int GetAmountsOfNodes();

    void SetEdge(Type* nodeA, Type* nodeB, int weight);
    int GetAmountsOfEdges();
    Edge<Type>* GetEdge(int pos);
    int GetEdge(Type nodeA, Type nodeB);
    Edge<Type> DeleteEdge(int pos);

    vector<Edge<Type> > Layout();
    List<Type> ShowNodes();
};

template < class Type>
void TreeComponents<Type>::__UpdateDistanceDimension()
{
    distances.resize(nodesList->GetSize());
    for (int fila = 0; fila < nodesList->GetSize(); fila++)
    {
        distances[fila].resize(nodesList->GetSize());
    };
};

template < class Type>
TreeComponents<Type>::TreeComponents()
{
    nodesList = new List<Type>;
};

template < class Type>
void TreeComponents<Type>::NewNode(Type node)
{
    nodesList->Insert(node);
    __UpdateDistanceDimension();
};

template < class Type>
Type TreeComponents<Type>::DeleteNode(int pos)
{
    /// ====== BORRAR EN LA MATRIZ "DISTANCIA" TODAS SUS INCIDENCIAS =====
    for(int columna = 0; columna < (int) distances[pos].size(); columna++) // Borra, en "distancias", la fila completa perteneciente al elemento a eliminar
    {
        vector<int>* fila = &distances[pos];
        fila->erase( fila->begin() );
    };
    distances.erase( distances.begin()+ pos );

    for(int fila = 0; fila < nodesList->GetSize(); fila++) // Borra de las filas restantes, el elemento ( representado por una columna )
    {
        distances[fila].erase(distances[fila].begin() + pos);
    };
    /// ============== BORRAR ARISTAS CON ESE NODO =========================
    for(int idx = 0; idx < GetAmountsOfEdges(); idx++)
    {
      if (EdgesList[idx].nodeA == GetNode(pos) || EdgesList[idx].nodeB == GetNode(pos) )
      {
          // borro la arista que contiene el nodo
          DeleteEdge(pos);
          //EdgesList.erase( EdgesList.begin() + idx );
      };
    };
    /// ================ FINALMENTE BORRO EL NODO ==========================
    Type* item = nodesList->GetItem(pos);
    nodesList->EraseItem(pos);
    /// ====================================================================
    //distances.push_back( vector<int>(0) );
    __UpdateDistanceDimension();


    return *item;
};

template < class Type>
Type TreeComponents<Type>::DeleteNode(Type* node)
{
    int pos = nodesList->GetItem(node);
    return DeleteNode(pos);
};

template < class Type>
Type* TreeComponents<Type>::GetNode(int pos)
{
    return nodesList->GetItem(pos);
}

template < class Type>
int TreeComponents<Type>::GetNode(Type node)
{
    int target = -1;
    for (int pos = 0; pos < GetAmountsOfNodes(); pos++)
    {
        if ( *GetNode(pos) == node )
        {
            target = pos;
        };
    };
    return target;
}

template < class Type>
int TreeComponents<Type>::GetAmountsOfNodes()
{
    return nodesList->GetSize();
}

template < class Type>
int TreeComponents<Type>::GetAmountsOfEdges()
{
    return (int) EdgesList.size();
}

template < class Type>
void TreeComponents<Type>::SetEdge(Type* nodeA, Type* nodeB, int _weight)
{
   int posA = nodesList->GetItem(nodeA);
   int posB = nodesList->GetItem(nodeB);

   distances[posA][posB] = _weight;

   int* weight = &distances[posA][posB];

   EdgesList.push_back( { nodeA, nodeB, weight } );
}

template < class Type>
Edge<Type>* TreeComponents<Type>::GetEdge(int pos)
{
    return &EdgesList[pos];
}

template < class Type>
int TreeComponents<Type>::GetEdge(Type nodeX, Type nodeY)
{
    int target = -1;
    for (int pos = 0; pos < GetAmountsOfEdges(); pos++)
    {
        Edge<Type>* edge = &EdgesList[pos];
        if (*edge->nodeA == nodeX && *edge->nodeB == nodeY)
        {
            target = pos;
        };

        if (*edge->nodeA == nodeY && *edge->nodeB == nodeX)
        {
            target = pos;
        };
    };
    return target;
}

template < class Type>
Edge<Type> TreeComponents<Type>::DeleteEdge(int pos)
{
    Edge<Type> edge = EdgesList[pos];
    EdgesList.erase( EdgesList.begin() + pos );
    return edge;
}

template < class Type>
vector< Edge<Type> > TreeComponents<Type>::Layout()
{
    /** ================ FOR TESTS ====================== */
    for (int pos = 0; pos < GetAmountsOfEdges(); pos++)
    {
        Edge<Type>* edge = &EdgesList[pos];
        cout << endl;
        cout << "Pos. de la Arista: " << pos << endl;
        cout << "Nodo A: " << *edge->nodeA << endl;
        cout << "Nodo B: " << *edge->nodeB << endl;
        cout << "Peso: " << *edge->weigth << endl;
    };
    /// ===================================================
    return EdgesList;
};

template < class Type>
List<Type> TreeComponents<Type>::ShowNodes()
{
    cout << "Nodos Cargados: ";
    for (int pos = 0; pos < nodesList->GetSize(); pos++)
    {
      cout << *nodesList->GetItem(pos) << " ";
    };
    cout << endl;

    return *nodesList;
};

#endif // TREE_COMPONENTS_H_INCLUDED
