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
//#include <itkImageToHistogramFilter.h>
//#include <itkImageRegionConstIterator.h>
//#include <itkGradientAnisotropicDiffusionImageFilter.h>
//
//#include "itkHistogramEqualizationFilter.h"
//
#include <cstdlib>
#include <math.h>

#include "SegmentationIntensityAndTextureImages.h"

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
    
    SegmentationIntensityAndTextureImages<ImageType> * preprocessedImages =
            SegmentationIntensityAndTextureImages<ImageType>::New();
    
    preprocessedImages->setInput(image);
            
    ImageType::Pointer intensityImage = preprocessedImages->getIntensityImage();
    
    ImageType::Pointer textureImage = preprocessedImages->getTextureImage();
        
    typedef itk::Image<unsigned char, 2> OutputImageType;
    
    typedef itk::CastImageFilter<ImageType, OutputImageType> CastFilterType;
    CastFilterType::Pointer castFilter = CastFilterType::New();
    castFilter->SetInput(intensityImage);
    castFilter->Update();
    
    typedef itk::ImageFileWriter<OutputImageType> WriterType;
    
    const char*  filenameIntensity = "xy14_intensity_prueba.bmp";
    WriterType::Pointer writer = WriterType::New();
    writer->SetFileName(filenameIntensity);
    writer->SetInput(castFilter->GetOutput());
    writer->Update();
    
    castFilter->SetInput(textureImage);
    castFilter->Update();
    
    const char*  filenameTexture = "xy14_texture_prueba.bmp";
    WriterType::Pointer writerT = WriterType::New();
    writerT->SetFileName(filenameTexture);
    writerT->SetInput(castFilter->GetOutput());
    writerT->Update();
    

    return 0;
}

