#ifndef SEGMENTATIONINTENSITYANDTEXTUREIMAGES_CPP
#define	SEGMENTATIONINTENSITYANDTEXTUREIMAGES_CPP

#include "SegmentationIntensityAndTextureImages.h"
#include "itkHistogramEqualizationFilter.h"
#include "itkScalarToTextureImageFilter.h"

#include <itkGradientAnisotropicDiffusionImageFilter.h>

template<class TInputImage>
void SegmentationIntensityAndTextureImages<TInputImage>::setInput(typename ImageType::Pointer image)
{
    typename RescaleFilterType::Pointer normalizeFilter = RescaleFilterType::New();
    normalizeFilter->SetOutputMaximum(255);
    normalizeFilter->SetOutputMinimum(0);
    normalizeFilter->SetInput(image);
    normalizeFilter->Update();   
    
    this->inputImage = normalizeFilter->GetOutput();
}

template<class TInputImage>
typename TInputImage::Pointer SegmentationIntensityAndTextureImages<TInputImage>::getIntensityImage()
{
    typedef itk::HistogramEqualizationFilter<ImageType,ImageType> EqualizationFilterType;
    
    typename EqualizationFilterType::Pointer equalizationFilter = EqualizationFilterType::New(); 
    equalizationFilter->SetInput(inputImage);
    equalizationFilter->Update();
    
    typedef itk::GradientAnisotropicDiffusionImageFilter<ImageType,ImageType> AnisotropicFilterType;
    
    typename AnisotropicFilterType::Pointer anisotropicFilter = AnisotropicFilterType::New();
    anisotropicFilter->SetInput(equalizationFilter->GetOutput());
    anisotropicFilter->SetNumberOfIterations(25);
    anisotropicFilter->SetTimeStep(0.125);
    anisotropicFilter->SetConductanceParameter(3);
    anisotropicFilter->Update();
    
    typename RescaleFilterType::Pointer normalizeFilter = RescaleFilterType::New();
    normalizeFilter->SetOutputMaximum(255);
    normalizeFilter->SetOutputMinimum(0);
    normalizeFilter->SetInput(anisotropicFilter->GetOutput());
    normalizeFilter->Update();     
    
    return normalizeFilter->GetOutput();
    
}

template<class TInputImage>
typename TInputImage::Pointer SegmentationIntensityAndTextureImages<TInputImage>::getTextureImage()
{    
    typedef itk::ScalarToTextureImageFilter<ImageType,ImageType> FilterType;
    
    typename FilterType::Pointer textureFilter = FilterType::New();
    textureFilter->SetInput(inputImage);
    textureFilter->SetTextureFeature(8);
    
    typename FilterType::RegionSizeType size;
    size.Fill(13);
   
    textureFilter->SetFilterRegionSize(size);
    textureFilter->Update();
    
    typename RescaleFilterType::Pointer normalizeFilter = RescaleFilterType::New();
    normalizeFilter->SetOutputMaximum(255);
    normalizeFilter->SetOutputMinimum(0);
    normalizeFilter->SetInput(textureFilter->GetOutput());
    normalizeFilter->Update();     
    
    return normalizeFilter->GetOutput();
    
}
#endif
