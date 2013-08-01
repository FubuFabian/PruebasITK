#include "itkMesh.h";
#include "itkLineCell.h";
#include "itkDefaultStaticMeshTraits.h";
#include "itkMatrix.h";

int main(int argc, char * argv){

    //Crear Nuevoa Mesh ////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////

    typedef float PixelType; //crea nuevo tipo de pixel

    typedef itk::Mesh<PixelType, 3> MeshType; //crea nuevo tipo de Mesh
    MeshType::Pointer mesh= MeshType::New(); //crea nueva instancia mesh

    typedef MeshType::PointType PointType; //Nuevo tipo de puntos para mesh

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

    typedef MeshType::PointsContainer PointsContainer;//nuevo tipo de contenedor para puntos
    PointsContainer::Pointer puntos = PointsContainer::New();

    puntos->InsertElement(0, p0); //inserta los puntos en el contenedor
    puntos->InsertElement(1, p1);
    puntos->InsertElement(2, p2);

    mesh->SetPoints(puntos); //inserta el contenedor en mesh

    typedef PointsContainer::Iterator PointsIterator; //iterador de puntos para mesh

    PointsIterator iterador = mesh->GetPoints()->Begin(); //obtiene el primer punto en mesh
    PointsIterator end = mesh->GetPoints()->End();
    unsigned int x = 0;

    while (iterador!=end){
        PointType p = iterador.Value();
        std::cout<<"El punto "<<x<<" es: "<<p<<std::endl;
        x++;
        iterador++;
    }

    typedef MeshType::CellType CellType; //crea un nuevo tipo del celda para mestype
    typedef itk::LineCell<CellType> LineType; //crea nuevo tipoo de celda lineal

    typedef CellType::CellAutoPointer CellAutoPointer; //crea nuevo tipo de apuntadores a las celdas
    CellAutoPointer line0; //crea nuevos apuntadores a celdas
    CellAutoPointer line1;
    CellAutoPointer line2;

    line0.TakeOwnership(new LineType); //asigna un nuevo objeto (celda) al apuntador. Indica que ese apuntado esta encargado del manejo de memoria
    line1.TakeOwnership(new LineType);
    line2.TakeOwnership(new LineType);

    line0->SetPointId(0,0); //asocia los puntos de la celda con los puntos de la malla
    line0->SetPointId(1,1);

    line1->SetPointId(0,0);
    line1->SetPointId(1,2);

    line2->SetPointId(0,1);
    line2->SetPointId(1,2);

    typedef MeshType::CellsContainer CellsContainer; //Crea nuevo tipo de contenedor de celdas
    
    CellsContainer::Pointer celdas = CellsContainer::New();

    try{
        celdas->InsertElement(0, line0.ReleaseOwnership()); //Inserta celda al contenedor
        celdas->InsertElement(1, line1.ReleaseOwnership());
        celdas->InsertElement(2, line2.ReleaseOwnership());
    }catch (itk::ExceptionObject e){
        std::cout<<"Excepcion en insert Element"<<std::endl;
        std::cout<<e<<std::endl;
    }

    mesh->SetCells(celdas); //Inserta contenedo a la malla

    typedef CellsContainer::Iterator CellsIterator; //iterador de puntos para mesh

    CellsIterator iteradorceldas = mesh->GetCells()->Begin(); //obtiene el primer punto en mesh
    CellsIterator endceldas = mesh->GetCells()->End();
    unsigned int xceldas = 0;

    while (iteradorceldas!=endceldas){
        CellType * p = iteradorceldas.Value();
        LineType * linea = dynamic_cast<LineType *>(p);
        std::cout<<"La linea "<<xceldas<<" tiene "<<linea->GetNumberOfPoints()<<" puntos."<<std::endl;
        xceldas++;
        iteradorceldas++;
    }


    ////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////

    //Manejo de Datos //////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////

    // Los puntos y las celdas en las mallas se manejan exactamente igual que los puntos en PoinSet

    typedef MeshType::PointDataContainer PointDataContainer;
    PointDataContainer::Pointer datospuntos = PointDataContainer::New();

    PixelType valor0 = 10;
    PixelType valor1 = 20;
    PixelType valor2 = 30;

    datospuntos->InsertElement(0, valor0);
    datospuntos->InsertElement(1, valor1);
    datospuntos->InsertElement(2, valor2);

    mesh->SetPointData(datospuntos);

    typedef PointDataContainer::Iterator PointDataIterator; //iterador de datos de los puntos para mesh

    PointDataIterator iteradordatos = mesh->GetPointData()->Begin(); //obtiene el dato del primer punto en mesh
    PointDataIterator enddatos = mesh->GetPointData()->End();
    unsigned int xdatos = 0;

    while (iteradordatos!=enddatos){
        PixelType p = iteradordatos.Value();
        std::cout<<"El dato del punto "<<xdatos<<" es: "<<p<<std::endl;
        xdatos++;
        iteradordatos++;
    }
	
    /*for (unsigned int celda = 0; celda<mesh->GetNumberOfCells(); celda++){
        mesh->SetCellData(celda, static_cast<PixelType>(celda*celda)); //inserta datos a la celda
    }*/

    typedef MeshType::CellDataContainer CellDataContainer;
    CellDataContainer::Pointer datos = CellDataContainer::New();

    PixelType celda0 = 5;
    PixelType celda1 = 15;
    PixelType celda2 = 25;

    datos->InsertElement(0, celda0);
    datos->InsertElement(1, celda1);
    datos->InsertElement(2, celda2);

    mesh->SetCellData(datos);

    typedef CellDataContainer::Iterator CellDataIterator;

    CellDataIterator iteradorcelldatos = mesh->GetCellData()->Begin();
    CellDataIterator endcelldatos = mesh->GetCellData()->End();
    unsigned int xcelldatos = 0;

    while(iteradorcelldatos!=endcelldatos){
        PixelType p = iteradorcelldatos.Value();
        std::cout<<"El dato de la celda "<<xcelldatos<<" es: "<<p<<std::endl;
        xcelldatos++;
        iteradorcelldatos++;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////

    // Modifcar traits para constumizar la malla ///////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////

    const unsigned int PointDimension = 3; //indica las dimensiones de la malla
    const unsigned int MaxTopologicalDimension = 2; //indica la max dimendión de las celdas en la malla

    typedef itk::Vector<double, 4> PixelTypeTrait; //indica el tipo de datos que guarda cada punto en la malla
    typedef itk::Matrix<double,4,3> CellDataType; //indica el tipo de datos que guarda cada celda en la malla

    typedef double CoordRepType; //indica el tipo de coordenadas a usar en el spacio
    typedef double InterpolationWeight; //indica el pedo de la interpolación

    typedef itk::DefaultStaticMeshTraits<
            PixelTypeTrait, PointDimension, MaxTopologicalDimension,
            CoordRepType, InterpolationWeight, CellDataType> MeshTraits; //cre un nuevo tipo de trait default para utilizarlo con una malla

    typedef itk::Mesh<PixelTypeTrait, PointDimension, MeshTraits> meshcostumized; //crea una malla con las características indicadas en el trait
    //se utiliza como cualquier otra malla

    ////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////

    //Indicar Relaciones entre celdas //////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////

    mesh->SetBoundaryAssignment(1, 0, 0, 1); //asigna la relación entre la celda 0 y la celda 1
    mesh->SetBoundaryAssignment(1, 0, 1, 2);
	
    unsigned int n0 = mesh->GetNumberOfCellBoundaryFeatures(0,0); //indica cuantas realciones de n dimensión tiene la malla

    std::cout<<"La malla 0 tiene "<<n0<<" relacónes de dimensión 1."<<std::endl;

    for(unsigned int boundary = 0; boundary < n0; boundary++){
        MeshType::CellIdentifier id; //identificador de la malla
        if (mesh->GetBoundaryAssignment(1, 0, boundary, &id)) //obtiene el identificador de la celda con la que tiene relación
                std::cout<<"La celda 0 tiene relación de dimensión 1 con: "<<id<<std::endl;
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


