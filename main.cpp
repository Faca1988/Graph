#include <iostream>
#include "kruskal.h"

using namespace std;

int main()
{
   Kruskal* k = new Kruskal();

   k->SetGraph();
   k->LayoutNodes();
   k->LayoutEdges();
   k->Resolve();
   k->LayoutSolution();


    return 0;
}
