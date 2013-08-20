/* 
 * File:   itkScalarToTextureImageFilter.txx
 * Author: Fabian
 *
 * Created on July 29, 2013, 4:09 PM
 */

#ifndef ITKSCALARTOTEXTUREIMAGEFILTER_TXX
#define	ITKSCALARTOTEXTUREIMAGEFILTER_TXX

#include "itkScalarToTextureImageFilter.h"

#include <itkMirrorPadImageFilter.h>
#include <itkScalarImageToCooccurrenceMatrixFilter.h>
#include <itkHistogramToTextureFeaturesFilter.h>
#include <itkExtractImageFilter.h>
#include <itkImage.h>
#include <itkSmartPointer.h>

#include <vector>
#include <math.h>
#include <iostream>

namespace itk {

template <class TInputImage, class TMaskImage, class TOutputImage>
ScalarToTextureImageFilter<TInputImage, TMaskImage, TOutputImage>
::ScalarToTextureImageFilter()
{
    this->m_RegionSize.Fill( 13 );
    this->m_MaskImage = NULL;
    this->m_NumberofBins = 16;
    this->m_PixelMaxValue = 255;
    this->m_PixelMinValue = 0;
    this->m_TextureFeature = 0;
    
}

template<class TInputImage, class TMaskImage, class TOutputImage>
void
ScalarToTextureImageFilter<TInputImage, TMaskImage, TOutputImage>
::GenerateData()
{
    
  this->AllocateOutputs();

  std::cout<<"hola";
  
  ProgressReporter progress( this, 0, 
        this->GetInput()->GetRequestedRegion().GetNumberOfPixels(), 100 );
  
  typedef MirrorPadImageFilter<InputImageType,InputImageType> PadFilterType;
  typename PadFilterType::Pointer padFilter = PadFilterType::New();
  
  int boundSize = floor(this->m_RegionSize[1]/2);
  
  RegionSizeType bound;
  bound.Fill(boundSize);
  
  padFilter->SetPadBound(bound);
  padFilter->SetInput(this->GetInput());
  padFilter->Update();
  
  typename InputImageType::Pointer padImage = padFilter->GetOutput();
  
  typedef Statistics::ScalarImageToCooccurrenceMatrixFilter<InputImageType>
          GLCMGeneratorType;
  typename GLCMGeneratorType::Pointer glcmGenerator = GLCMGeneratorType::New();
  
  glcmGenerator->SetNumberOfBinsPerAxis(this->m_NumberofBins);
  glcmGenerator->SetPixelValueMinMax(this->m_PixelMinValue,m_PixelMaxValue);
  
  typedef typename InputImageType::OffsetType OffsetType;
    
  OffsetType offset1;
  offset1[0] = 1;
  offset1[1] = 0;
   
  OffsetType offset2;
  offset2[0] = 1;
  offset2[1] = -1;
    
  OffsetType offset3;
  offset3[0] = 0;
  offset3[1] = -1;
    
  OffsetType offset4;
  offset4[0] = -1;
  offset4[1] = -1;
  
  typedef typename GLCMGeneratorType::OffsetVector OffsetVectorType;
  typename OffsetVectorType::Pointer offsets = OffsetVectorType::New();  
  
  offsets->reserve(4);
  offsets->InsertElement(0,offset1);
  offsets->InsertElement(1,offset2);
  offsets->InsertElement(2,offset3);
  offsets->InsertElement(3,offset4);
  
  glcmGenerator->SetOffsets(offsets);
  
  typedef typename GLCMGeneratorType::HistogramType HistogramType;
  typedef Statistics::HistogramToTextureFeaturesFilter<HistogramType> 
          TextureFeaturesType;
  typename TextureFeaturesType::Pointer textureFeatures;
  
  if(this->m_TextureFeature<=8 && this->m_TextureFeature>=0){  
      textureFeatures = TextureFeaturesType::New();
  }else{
      textureFeatures = NULL;
  }
  
  typedef ExtractImageFilter<InputImageType,InputImageType> ExtractFilterType;
  typename ExtractFilterType::Pointer extractFilter = ExtractFilterType::New();
  
  typename InputImageType::RegionType region;
  typename InputImageType::IndexType regionIndex;
    
  region.SetSize(this->m_RegionSize);
  
  extractFilter->SetInput(padImage);
  
  ImageRegionIteratorType itPad(padImage, padImage->GetLargestPossibleRegion());
  itPad.GoToBegin();

  ImageRegionIteratorType itOut(this->GetOutput(), 
          this->GetOutput()->GetLargestPossibleRegion());
  itOut.GoToBegin();
  
  while(!itPad.IsAtEnd()){

        regionIndex = itPad.GetIndex();
        region.SetIndex(regionIndex);
        
        if(padImage->GetLargestPossibleRegion().IsInside(region)){ 
            
            extractFilter->SetExtractionRegion(region);
            extractFilter->UpdateLargestPossibleRegion();
            
            glcmGenerator->SetInput(extractFilter->GetOutput());
            glcmGenerator->UpdateLargestPossibleRegion();
            
            if(this->m_TextureFeature == 0){
                textureFeatures->SetInput(glcmGenerator->GetOutput());
                textureFeatures->UpdateLargestPossibleRegion();
                this->GetOutput()->SetPixel(itOut.GetIndex(),
                        textureFeatures->GetFeature(TextureFeaturesType::Energy));
            }else if(this->m_TextureFeature == 1){
                textureFeatures->SetInput(glcmGenerator->GetOutput());
                textureFeatures->UpdateLargestPossibleRegion();
                this->GetOutput()->SetPixel(itOut.GetIndex(),
                        textureFeatures->GetFeature(TextureFeaturesType::Entropy));
            }else if(this->m_TextureFeature == 2){
                textureFeatures->SetInput(glcmGenerator->GetOutput());
                textureFeatures->UpdateLargestPossibleRegion();
                this->GetOutput()->SetPixel(itOut.GetIndex(),
                        textureFeatures->GetFeature(TextureFeaturesType::Correlation));
            }else if(this->m_TextureFeature == 3){
                textureFeatures->SetInput(glcmGenerator->GetOutput());
                textureFeatures->UpdateLargestPossibleRegion();
                this->GetOutput()->SetPixel(itOut.GetIndex(),
                        textureFeatures->GetFeature(TextureFeaturesType::InverseDifferenceMoment));
            }else if(this->m_TextureFeature == 4){
                textureFeatures->SetInput(glcmGenerator->GetOutput());
                textureFeatures->UpdateLargestPossibleRegion();
                this->GetOutput()->SetPixel(itOut.GetIndex(),
                        textureFeatures->GetFeature(TextureFeaturesType::Inertia)); 
            }else if(this->m_TextureFeature == 5){
                textureFeatures->SetInput(glcmGenerator->GetOutput());
                textureFeatures->UpdateLargestPossibleRegion();
                this->GetOutput()->SetPixel(itOut.GetIndex(),
                        textureFeatures->GetFeature(TextureFeaturesType::ClusterShade));
            }else if(this->m_TextureFeature == 6){
                textureFeatures->SetInput(glcmGenerator->GetOutput());
                textureFeatures->UpdateLargestPossibleRegion();
                this->GetOutput()->SetPixel(itOut.GetIndex(),
                        textureFeatures->GetFeature(TextureFeaturesType::ClusterProminence));
            }else if(this->m_TextureFeature == 7){
                textureFeatures->SetInput(glcmGenerator->GetOutput());
                textureFeatures->UpdateLargestPossibleRegion();
                this->GetOutput()->SetPixel(itOut.GetIndex(),
                        textureFeatures->GetFeature(TextureFeaturesType::HaralickCorrelation));
            }else if(this->m_TextureFeature == 8){
                
                typename HistogramType::ConstPointer hist = glcmGenerator->GetOutput();
                
                typename HistogramType::ConstIterator it = hist->Begin();
                
                float mean = 0;
                while(it != hist->End()){
                    mean += it.GetFrequency();
                    ++it;
                }
                
                float nBins = hist->GetSize(0);
                nBins *= nBins;
                
                mean /= nBins;
                
                float variance = 0;
                it = hist->Begin();
                while( it != hist->End()){
                    variance += pow(it.GetFrequency()-mean,2);
                    ++it;
                }
                
                variance /= (nBins - 1);
                
                this->GetOutput()->SetPixel(itOut.GetIndex(),variance);
                
                hist = NULL;
                
            }
                
            ++itOut;
            
            progress.CompletedPixel();
            std::cout<<".";
        }
        
        ++itPad;
  }
  
  std::cout<<std::endl;
  
  
}

template<class TInputImage, class TMaskImage, class TOutputImage>
void
ScalarToTextureImageFilter<TInputImage, TMaskImage, TOutputImage>
::PrintSelf(std::ostream &os, Indent indent) const
{
  Superclass::PrintSelf( os, indent );

  os << indent << "Region size: "
    << this->m_RegionSize << std::endl;
  os << indent << "Number of Bins: "
    << this->m_NumberofBins << std::endl;
  os << indent << "Maximum Pixel Value: "
    << this->m_PixelMaxValue << std::endl;
  os << indent << "Minimum Pixel Value: "
    << this->m_PixelMinValue << std::endl;
  
  if(this->m_TextureFeature == 0){
     os << indent << "Texture Feature: Energy"<<std::endl;
  }else if(this->m_TextureFeature == 1){
     os << indent << "Texture Feature: Entropy"<<std::endl;
  }else if(this->m_TextureFeature == 2){
     os << indent << "Texture Feature: Correlation"<<std::endl;
  }else if(this->m_TextureFeature == 3){
     os << indent << "Texture Feature: Inverse Different Moment"<<std::endl;
  }else if(this->m_TextureFeature == 4){
     os << indent << "Texture Feature: Inertia"<<std::endl;
  }else if(this->m_TextureFeature == 5){
     os << indent << "Texture Feature: Cluster Shade"<<std::endl;
  }else if(this->m_TextureFeature == 6){
     os << indent << "Texture Feature: Cluster Prominence"<<std::endl;
  }else if(this->m_TextureFeature == 7){
     os << indent << "Texture Feature: Haralick Correlation"<<std::endl;
  }
  
}

}// end namespace itk

#endif	/* ITKSCALARTOTEXTUREIMAGEFILTER_TXX */

