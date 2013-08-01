#include "itkSpatialObject.h"
#include "itkSpatialObjectTreeContainer.h"
#include "itkGroupSpatialObject.h"

int main(int argc, char * argv[]){

    // Crear nuevo SpatialObject ///////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////

    typedef itk::SpatialObject<3> SpatialObjectType; //CREA NUEVO TIPO DE OBJETO ESPACIAL
    SpatialObjectType::Pointer objeto1 = SpatialObjectType::New(); //crea nuevo objeto spatial object
    SpatialObjectType::Pointer objeto2 = SpatialObjectType::New();

    objeto1->GetProperty()->SetName("Primer Objeto"); //Le da nombre al objeto espacial
    objeto2->GetProperty()->SetName("Segundo Objeto");

    objeto1->AddSpatialObject(objeto2); //hace que el objeto 1 sea el padre del objeto dos

    if(objeto2->HasParent()){ //Checa si el objeto tiene padre
        std::cout<<"El padre de "<<objeto2->GetProperty()->GetName()
                          <<" es: "<<objeto2->GetParent()->GetProperty()->GetName()<<std::endl; //obtiene el nombre del padre del objeto 2
    }

    objeto1->RemoveSpatialObject(objeto2);

    ////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////

    // Crear arbol de jerarquia ////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////

    typedef itk::GroupSpatialObject<2> NodeType; //crea un nuevo tipo de nodo para el arbol de jerarquia
    typedef itk::SpatialObjectTreeContainer<2> TreeType; //crea un nuevo tipo de arbol

    NodeType::Pointer nodo0 = NodeType::New(); //cre un nuevo nodo, poadre de los objetos
    nodo0->SetId(0); //le da el identificador al nodo

    NodeType::Pointer nodo1 = NodeType::New(); //cre un nuevo nodo, poadre de los objetos
    nodo1->SetId(1);

    nodo0->AddSpatialObject(nodo1);

    std::cout<<"El nodo 0 tiene "<<nodo0->GetNumberOfChildren()<<" hijo"<<std::endl;

    TreeType::Pointer tree = TreeType::New(); //Crea un nuevo arbol
    tree->SetRoot(nodo0); //indica el nodo raiz

    //se navega en el arbol como en un container, tiene que crearse un iterador

    ////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////

    std::cout<<"Presiona Enter Para salir"<<std::endl;


    bool salir = true;

    while(salir){
        if(std::cin.get()=='\n')
            salir=false;
    }

    return 0;





}
