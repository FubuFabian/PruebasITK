/* 
 * File:   IntensityImage.cpp
 * Author: Fabian
 *
 * Created on August 5, 2013, 11:03 AM
 */
#include <itkImage.h>
#include <itkImageFileReader.h>
#include <itkImageFileWriter.h>
#include <itkCastImageFilter.h>
#include <itkImageToHistogramFilter.h>
#include <itkImageRegionConstIterator.h>
#include <itkGradientAnisotropicDiffusionImageFilter.h>

#include "itkHistogramEqualizationFilter.h"

#include <cstdlib>
#include <math.h>


using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    
    typedef itk::Image<float, 2> ImageType;
    
    
    typedef itk::ImageFileReader<ImageType> ReaderType;
    const char*  filenamereader = "xy14.bmp";  
    ReaderType::Pointer reader = ReaderType::New();
    reader->SetFileName(filenamereader);
    reader->Update();   
    
    ImageType::Pointer image = reader->GetOutput();
    
    typedef itk::HistogramEqualizationFilter<ImageType,ImageType> EqualizationFilterType;
    EqualizationFilterType::Pointer equalizationFilter = EqualizationFilterType::New(); 
    equalizationFilter->SetInput(image);
    equalizationFilter->Update();
    
    typedef itk::GradientAnisotropicDiffusionImageFilter<ImageType,ImageType> AnisotropicFilterType;
    AnisotropicFilterType::Pointer anisotropicFilter = AnisotropicFilterType::New();
    
    anisotropicFilter->SetInput(equalizationFilter->GetOutput());
    anisotropicFilter->SetNumberOfIterations(25);
    anisotropicFilter->SetTimeStep(0.125);
    anisotropicFilter->Update();
    anisotropicFilter->SetConductanceParameter(3);

    typedef itk::Image<unsigned char,2> OutputImageType;
    
    typedef itk::CastImageFilter<ImageType, OutputImageType> CastFilterType;
    CastFilterType::Pointer castFilter = CastFilterType::New();
    castFilter->SetInput(anisotropicFilter->GetOutput());
    castFilter->Update();
    
    
    
    typedef itk::ImageFileWriter<OutputImageType> WriterType;
    const char*  filenamewriter = "xy14_intensity.bmp";
    WriterType::Pointer writer = WriterType::New();
    writer->SetFileName(filenamewriter);
    writer->SetInput(castFilter->GetOutput());
    writer->Update();
    

    return 0;
}

