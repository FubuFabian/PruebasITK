#include "itkPointSet.h";

int main(int argc, char * argv){

    //Crear Nuevo pointset /////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////

    typedef itk::PointSet<unsigned short, 3> PointSetType; //Crea nuevo tipo de pointset
    PointSetType::Pointer pointset = PointSetType::New(); //Crea nueva instancia al nuevo tipo de pointset

    typedef PointSetType::PointType PointType; //Crea nuevos tipos de puntos para el pointsettype
    PointType p0; //crea nuevo punto y sus coordenadas
    p0[0] = -1.0;
    p0[1] = 0.0;
    p0[2] = 1.0;

    PointType p1; //crea nuevo punto y sus coordenadas
    p1[0] = 1.0;
    p1[1] = 0.0;
    p1[2] = -1.0;

    PointType p2; //crea nuevo punto y sus coordenadas
    p2[0] = 0.0;
    p2[1] = 0.0;
    p2[2] = 0.0;

    pointset->SetPoint(0, p0); //insterta los puntos en el pointset
    pointset->SetPoint(1, p1);
    pointset->SetPoint(2, p2);

    unsigned int numerodepuntos = pointset->GetNumberOfPoints(); //obtiene el numero de puntos en un pointset
    std::cout<<"Numero de Puntos: "<<numerodepuntos<<std::endl;

    PointType punto1;
    bool existe = pointset->GetPoint(4, &punto1); //obtiene el punto 1; recibe el identificador y la dir de memoria a guardar

    if (existe){
        std::cout<<"El punto 1 es: "<<punto1<<std::endl;
    }else{
        std::cout<<"No existe el punto"<<std::endl;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////

    //Accesar a un pointset ////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////

    typedef PointSetType::PointsContainer PointsContainer; //Crea un nuevo tipo de contenedor de puntos;
    PointsContainer::Pointer puntos = PointsContainer::New(); //Crea un contenedor de puntos

    puntos->InsertElement(0, p0); //inserta puntos en el contendedor, parecido a SetPoint pero más eficiente
    puntos->InsertElement(1, p1);

    pointset->SetPoints(puntos); //inserta los puntos del contenedor al pointset, borra los anteriores

    numerodepuntos = pointset->GetNumberOfPoints(); //obtiene el numero de puntos en un pointset
    std::cout<<"Numero de Puntos contenedor: "<<numerodepuntos<<std::endl;

    typedef PointsContainer::Iterator PointsIterator; //crea un nuevo tipo de iterador para el tipo pointscontainer
    PointsIterator iterador = puntos->Begin(); //crea un nuevo iterador y apuntando al primer punto del contendedor

    PointsIterator end = puntos->End(); //no a punta a ningun elemento del contenedor
	unsigned int x = 0;

    while (iterador!=end){
        PointType p = iterador.Value(); //obtiene el valor del punto en el contenedor
        std::cout<<"El punto "<<x<<" del contenedor es: "<<p<<std::endl;
        iterador++;
		x++;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////

    //Accesar a los datos de un point set //////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////

    typedef unsigned short PixelType; //Crea nuevo tipo de datos para los puntos

    PixelType valor = 10; //crea un nuevo dato para un punto
    unsigned int punto = 0; //identificador de los putnos en el pointset

    pointset->SetPointData(punto, valor); //inserta el valor al punto

    PixelType valor2;

    if(pointset->GetPointData(punto, &valor2)){
        std::cout<<"El dato del punto 0 es: "<<valor2<<std::endl;
    }else{
        std::cout<<"El punto no existe"<<std::endl;
    }

    typedef PointSetType::PointDataContainer PointDataContainer; //crea nuevo tipo de contenedores de datos
    PointDataContainer::Pointer datos = PointDataContainer::New(); //crea un nuevo contenedor de datos

    PixelType valor0 = 15;
    PixelType valor1 = 40;

    datos->InsertElement(punto++, valor0); //inserta los datos al contenedor de datos
    datos->InsertElement(punto++, valor1);

    pointset->SetPointData(datos); //inserta los datos a sus respectivos puntos

    PointDataContainer::Pointer datos2 = pointset->GetPointData(); //obtiene los datos de los puntos y los guarda en un contenedor

    typedef PointDataContainer::Iterator PointsDataIterator; //crea un nuevo tipo de iterador para datos
    PointsDataIterator iteradordatos = datos2->Begin(); //crea un nuevo iterador y apuntando al primer punto del contendedor de datos

    PointsDataIterator enddatos = datos->End(); //no a punta a ningun elemento del contenedor
    unsigned int xdatos = 0;

    while (iteradordatos!=enddatos){
        PixelType p = iteradordatos.Value(); //obtiene el valor del punto en el contenedor
        std::cout<<"El dato del punto "<<xdatos<<" del contenedor es: "<<p<<std::endl;
        iteradordatos++;
        xdatos++;
    }

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
