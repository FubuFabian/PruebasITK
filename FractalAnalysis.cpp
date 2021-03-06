#include <itkImage.h>
#include <itkImageFileReader.h>
#include <itkImageFileWriter.h>
#include "itkScalarToFractalImageFilter.h"
#include <iostream>

int main(int argc, char* argv[])
{
    
    typedef itk::Image<float, 3> ImageType;
    
    
    typedef itk::ImageFileReader<ImageType> ReaderType;
    const char*  filenamereader = "/Users/Fabian/Documents/Pruebas/Prueba ITK/Archivo Binary/m1.mhd";  
    ReaderType::Pointer reader = ReaderType::New();
    reader->SetFileName(filenamereader);
    reader->Update();    
    
    typedef itk::ScalarToFractalImageFilter<ImageType,ImageType> FilterType;
    FilterType::Pointer filter = FilterType::New();
    filter->SetInput(reader->GetOutput());
    FilterType::RadiusType radius;
    radius.Fill(3);
    filter->SetNeighborhoodRadius(radius);
    filter->Update();
    
//    typedef itk::ImageFileWriter<ImageType> WriterType;
//    const char*  filenamewriter = "xy14_filter.bmp";
//    WriterType::Pointer writer = WriterType::New();
//    writer->SetFileName(filenamewriter);
//    writer->SetInput(filter->GetOutput());
//    writer->Update();
    
    return 0;
}
