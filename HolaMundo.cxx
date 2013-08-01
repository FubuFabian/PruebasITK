#include "itkImage.h"  //para trabajar con imagenes
#include "itkImageFileReader.h" //para leer imagenes
#include <iostream> //para imprimir en pantalla


int main(int argc, char * argv[]){

        //Crear Nueva Imagen ///////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////////////

        typedef itk::Image<unsigned char, 2> ImageType; //nuevo tipo de imagen
        ImageType::Pointer image = ImageType::New(); //se crea una instancia al nuevo tipo de imagen

        ImageType::IndexType start; //el origen de la imagen
        start[0] = 0;
        start[1] = 0;
        start[2] = 0;

        ImageType::SizeType size; //el tamaÔøΩo de la imagen
        size[0] = 200;
        size[1] = 200;
        size[2] = 200;

        ImageType::RegionType region; //indica una nueva regiÔøΩn de la imagen
        region.SetSize(size);
        region.SetIndex(start);

        image->SetRegions(region); //indica que region va a ser el tamaÔøΩo de todos los tipos de regiones de imagen
        image->Allocate(); //asigna espacio en memoria para la informaciÔøΩn de los pixeles de la imagen

        ////////////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////////////

        //Leer Imagen //////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////////////

       typedef unsigned char PixelType; //indica el tipo de reppresentaciÔøΩn de los pixeles
        const unsigned int dimension = 2; //indica las dimensiones de la imagen
        typedef itk::Image<PixelType, dimension> ImageTypeReader; //crea un nuevo tipo de imagen

        typedef itk::ImageFileReader<ImageTypeReader> ReaderType; //crea un nuevo tipo de lector de imagen para ImageTypeReader
        ReaderType::Pointer reader = ReaderType::New(); //crea una nueva instancia a un lector de imagenes
		
		const char * filename = "../../Imagenes_Prueba/lena.jpg";
		std::cout<<filename<<std::endl;
		
		reader->SetFileName(filename); //le indica al lector que archivo leer
		
        try{
               reader->Update(); //actualiza la informaciÔøΩn del lector, en una aplicaciÔøΩn normal no se usa ya que los filtros hacen esta operaciÔøΩn  
        }catch(itk::ExceptionObject exp){
			std::cout<<"Excepcion de update"<<std::endl<<exp<<std::endl;
        }
	
        ImageTypeReader::Pointer imagenleida = reader->GetOutput(); //crea un objeto de imagen con la informaciÔøΩn leida por el lector

        ////////////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////////////

        //Modificar pixeles ////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////////////

        ImageType::IndexType pixelIndex; //crea un objeto de tipo index para indexar un pixel
        pixelIndex[0]=27; //x
        pixelIndex[1]=29; //y
        pixelIndex[2]=30; //z

        ImageType:PixelType pixelValue = image->GetPixel(pixelIndex); //obtiene el valor del pixel
		
        image->SetPixel(pixelIndex, pixelValue+1); //pone el valor del pixel

        ////////////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////////////

        //elementos geomÔøΩtricos de las imagenes ////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////////////

        const ImageType::SpacingType& spacing = image->GetSpacing(); //lee el spacing de la imagen
        std::cout<<"Spacing "<<spacing[0]<<", "<<spacing[1]<<", "<<spacing[2]<<std::endl;

        ImageType::SpacingType sp; //objeto de tipo spacing, indica el espacio entre el centro de los pixeles
        sp[0] = 1;
        sp[1] = 0.3;
        sp[2] = 1.2;

        image->SetSpacing(sp); //pone el spacing a la imagen

        const ImageType::PointType& origin = image->GetOrigin(); //lee el origen de la imagen
        std::cout<<"Origen "<<origin[0]<<", "<<origin[1]<<", "<<origin[2]<<std::endl;

        ImageType::PointType org; //objeto de tipo point. indica la posiciÔøΩn de un pixel
        org[0] = 0.0;
        org[1] = 0.0;
        org[2] = 0.0;

        image->SetOrigin(org); //pone el origen a la imagen
		
        ////////////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////////////

        //leer el contenido del pixel mas cercano //////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////////////

        typedef itk::Point<double, ImageType::ImageDimension> PointType; //se crea un nuevo tipo de punto

        PointType punto; //no se crea una nstancia proque es un objeto muy pequeÔøΩo
        punto[0] = 1.45;
        punto[1] = 7.21;
        punto[2] = 9.28;

        ImageType::IndexType pixelMCIndex;

        bool existe = image->TransformPhysicalPointToIndex(punto, pixelMCIndex); //transforma las coordenadas fisicas a las coordenadas del pixel mÔøΩs cercano

        if(existe){ //si existia un pixel de la imagen cerca de las coordenadas fisicas del punto
            ImageType::PixelType pixelMC = image->GetPixel(pixelMCIndex);
            std::cout<<"Pixel mÔøΩs cercano "<<pixelMC<<std::endl;
        }

        ////////////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////////////

        std::cout<<"Presiona Enter Para salir"<<std::endl;
		
		
        bool salir = true;

        while(salir){
            if(std::cin.get()=='\n')
                salir=false;
        }*/

        return 0;

}
