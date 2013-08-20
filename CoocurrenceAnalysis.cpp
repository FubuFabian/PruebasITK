#include <itkImage.h>
#include <itkImageFileReader.h>
#include <itkImageFileWriter.h>
#include <itkImageRegionIterator.h>
#include <itkMirrorPadImageFilter.h>
#include <itkScalarImageToCooccurrenceMatrixFilter.h>
#include <itkHistogramToTextureFeaturesFilter.h>
#include <itkExtractImageFilter.h>
#include <itkRescaleIntensityImageFilter.h>
#include <itkCastImageFilter.h>
#include "itkScalarToTextureImageFilter.h"
#include <iostream>

int main(int argc, char* argv[])
{
    itk::MultiThreader::SetGlobalMaximumNumberOfThreads(1);
    
    typedef itk::Image<float, 3> ImageType;
    
    
    typedef itk::ImageFileReader<ImageType> ReaderType;
    const char*  filenamereader = "/Users/Fabian/Documents/Pruebas/Prueba ITK/Archivo Binary/m27.mhd";  //Users/Fabian/Documents/Pruebas/Prueba ITK/Archivo Binary/m27.mhd";  
    ReaderType::Pointer reader = ReaderType::New();
    reader->SetFileName(filenamereader);
    reader->Update();   
    
    ImageType::Pointer image = reader->GetOutput();
    
    typedef itk::ScalarToTextureImageFilter<ImageType,ImageType> FilterType;
    FilterType::Pointer filter = FilterType::New();
    filter->SetInput(reader->GetOutput());
    filter->SetTextureFeature(0);
    FilterType::RegionSizeType size;
    size.Fill(11);
    //filter->SetFilterRegionSize(size);
    
    filter->Update();
//    
//    typedef itk::RescaleIntensityImageFilter<ImageType, ImageType> RescaleFilterType;
//    RescaleFilterType::Pointer normalizeFilter = RescaleFilterType::New();
//    normalizeFilter->SetOutputMaximum(255);
//    normalizeFilter->SetOutputMinimum(0);
//    normalizeFilter->SetInput(filter->GetOutput());
//    normalizeFilter->Update();
//    
//    ImageType::Pointer normalizeImage = normalizeFilter->GetOutput();
//    
//    typedef itk::Image<unsigned char,3> OutputImageType;
//    
//    typedef itk::CastImageFilter<ImageType, OutputImageType> CastFilterType;
//    CastFilterType::Pointer castFilter = CastFilterType::New();
//    castFilter->SetInput(normalizeImage);
//    
//    typedef itk::ImageFileWriter<OutputImageType> WriterType;
//    const char*  filenamewriter = "xy14_variance.bmp";
//    WriterType::Pointer writer = WriterType::New();
//    writer->SetFileName(filenamewriter);
//    writer->SetInput(castFilter->GetOutput());
//    writer->Update();

    return 0;
}

