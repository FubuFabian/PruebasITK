#include "itkImage.h"  //para trabajar con imagenes
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"//para leer imagenes
#include "itkBinaryThresholdImageFilter.h" //filtro de umbralziación
#include "itkVector.h"

int main(int argc, char * argv[]){

    //Leer Imagen //////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////

    typedef unsigned char PixelType; //indica el tipo de reppresentación de los pixeles
    const unsigned int dimension = 2; //indica las dimensiones de la imagen
    typedef itk::Image<PixelType, dimension> ImageTypeReader; //crea un nuevo tipo de imagen
	
    typedef itk::ImageFileReader<ImageTypeReader> ReaderType; //crea un nuevo tipo de lector de imagen para ImageTypeReader
    ReaderType::Pointer reader = ReaderType::New(); //crea una nueva instancia a un lector de imagenes

    const char * filename = "../../Imagenes_Prueba/lena.jpg";
    std::cout<<filename<<std::endl;

    reader->SetFileName(filename); //le indica al lector que archivo leer
	
    try{
       reader->Update(); //actualiza la información del lector, en una aplicación normal no se usa ya que los filtros hacen esta operación
    }catch(itk::ExceptionObject exp){
       std::cout<<"Excepcion de update"<<std::endl<<exp<<std::endl;
    }
	
    ImageTypeReader::Pointer imagenleida = reader->GetOutput(); //crea un objeto de imagen con la información leida por el lector

	ImageTypeReader::IndexType punto;
	punto[0] = 150;
	punto[1] = 200;

	std::cout<<"Valor del pixel 23,23: "<<(unsigned int)imagenleida->GetPixel(punto)<<std::endl;

    ////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////

    //Crear imagen de salida ///////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////

    typedef itk::Image<PixelType, dimension> ImageTypeWriter;

    ////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////

    //Usar filtro de umbralización /////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////
	
	typedef itk::BinaryThresholdImageFilter<ImageTypeReader, ImageTypeWriter> FilterType; //crea nuevvo tipo de filtro	
	FilterType::Pointer filtro = FilterType::New();


    filtro->SetInput(imagenleida); //indica la imagen a procesar con el filtro
    filtro->SetOutsideValue((unsigned char)256); //indica la intensidad de los pixeles que se encuentran fuera de los umbrales
    filtro->SetInsideValue((unsigned char)0); //indica la intensidad de los pixeles que se encuentran dentro de los umbrales
    filtro->SetUpperThreshold((unsigned char)80); //INDICA EL UMBRAL SUPERIOR
    filtro->SetLowerThreshold((unsigned char)50); //indica el umbral inferior

    filtro->Update(); //dispara el filtro

    ImageTypeWriter::Pointer imagenfiltrada = filtro->GetOutput();


    ////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////

    //Guardar la imagen ////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////

    typedef itk::ImageFileWriter<ImageTypeWriter> WriterType;
    WriterType::Pointer writer = WriterType::New();

    const char * filename2 = "../../Imagenes_Prueba/lena_filter.jpg";
    writer->SetFileName(filename2);
    writer->SetInput(imagenfiltrada);

    try{
       writer->Update(); //actualiza la información del lector, en una aplicación normal no se usa ya que los filtros hacen esta operación
    }catch(itk::ExceptionObject exp){
       std::cout<<"Excepcion de update"<<std::endl<<exp<<std::endl;
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
