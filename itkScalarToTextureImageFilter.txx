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

#include <vector>
#include <math.h>

namespace itk {

template <class TInputImage, class TMaskImage, class TOutputImage>
ScalarToTextureImageFilter<TInputImage, TMaskImage, TOutputImage>
::ScalarToTextureImageFilter()
{
  
    this->m_RegionSize.Fill( 13 );

  this->m_MaskImage = NULL;
}

template<class TInputImage, class TMaskImage, class TOutputImage>
void
ScalarToTextureImageFilter<TInputImage, TMaskImage, TOutputImage>
::GenerateData()
{
    
  this->AllocateOutputs();

  ProgressReporter progress( this, 0, 
        this->GetInput()->GetRequestedRegion().GetNumberOfPixels(), 100 );
  
  ImageRegionIteratorType itPad(this->GetInput(), this->GetInput()->GetRequestedRegion());
  itPad.GoToBegin();

  /*typedef typename NeighborhoodAlgorithm
    ::ImageBoundaryFacesCalculator<InputImageType> FaceCalculatorType;
  FaceCalculatorType faceCalculator;

  typename FaceCalculatorType::FaceListType faceList
    = faceCalculator( this->GetInput(),
    this->GetInput()->GetRequestedRegion(), this->m_NeighborhoodRadius );
  typename FaceCalculatorType::FaceListType::iterator fit;
  


  RealType minSpacing = this->GetInput()->GetSpacing()[0];
  for( unsigned int d = 0; d < ImageDimension; d++ )
    {
    if( this->GetInput()->GetSpacing()[d] < minSpacing )
      {
      minSpacing = this->GetInput()->GetSpacing()[d];
      }
    }
  
 

  std::vector<RealType> distances;
  std::vector<RealType> distancesFrequency;
  std::vector<RealType> averageAbsoluteIntensityDifference;

  for( fit = faceList.begin(); fit != faceList.end(); ++fit )
    {
    ConstNeighborhoodIteratorType It(
      this->m_NeighborhoodRadius, this->GetInput(), *fit );
    NeighborhoodIterator<OutputImageType> ItO(
      this->m_NeighborhoodRadius, this->GetOutput(), *fit );
    
  ////////////////////////////////

    for( It.GoToBegin(), ItO.GoToBegin(); !It.IsAtEnd(); ++It, ++ItO )
      {
      if( this->m_MaskImage &&
        !this->m_MaskImage->GetPixel( It.GetIndex() ) )
        {
        ItO.SetCenterPixel(
          NumericTraits<typename OutputImageType::PixelType>::Zero );
        progress.CompletedPixel();
        continue;
        }
      
      distances.clear();
      distancesFrequency.clear();
      averageAbsoluteIntensityDifference.clear();

      for( unsigned int i = 0; i < It.GetNeighborhood().Size(); i++ )
        {
        bool IsInBounds1;
        typename InputImageType::PixelType pixel1
          = It.GetPixel( i, IsInBounds1 );

        if( IsInBounds1 && ( !this->m_MaskImage || ( this->m_MaskImage &&
          this->m_MaskImage->GetPixel( It.GetIndex( i ) ) ) ) )
          {
          typename InputImageType::PointType point1;
          this->GetInput()->TransformIndexToPhysicalPoint(
            It.GetIndex( i ), point1 );

          for( unsigned int j = 0; j < It.GetNeighborhood().Size(); j++ )
            {
            if( i != j )
              {
              bool IsInBounds2;
              typename InputImageType::PixelType pixel2
                = It.GetPixel( j, IsInBounds2 );

              if( IsInBounds2 && ( !this->GetMaskImage() || 
                ( this->GetMaskImage() && this->GetMaskImage()->GetPixel( 
                It.GetIndex( j ) ) ) ) )
                {
                typename InputImageType::PointType point2;
                this->GetInput()->TransformIndexToPhysicalPoint(
                  It.GetIndex( j ), point2 );

                RealType distance
                  = point1.SquaredEuclideanDistanceTo( point2 );

                bool distanceFound = false;
                for( unsigned int k = 0; k < distances.size(); k++ )
                  {
                  if( vnl_math_abs( distances[k] - distance )
                    < 0.5 * minSpacing )
                    {
                    distancesFrequency[k]++;
                    averageAbsoluteIntensityDifference[k]
                      += vnl_math_abs( pixel1 - pixel2 );
                    distanceFound = true;
                    break;
                    }
                  }
                if( !distanceFound )
                  {
                  distances.push_back( distance );
                  distancesFrequency.push_back( 1 );
                  averageAbsoluteIntensityDifference.push_back(
                    vnl_math_abs( pixel1 - pixel2 ) );
                  }
                }
              }
            }
          }
        }
      RealType sumY = 0.0;
      RealType sumX = 0.0;
      RealType sumXY = 0.0;
      RealType sumXX = 0.0;

      for( unsigned int k = 0; k < distances.size(); k++ )
        {
        if( distancesFrequency[k] == 0 )
          {
          continue;
          }

        averageAbsoluteIntensityDifference[k]
          /= static_cast<RealType>( distancesFrequency[k] );
        averageAbsoluteIntensityDifference[k]
          = vcl_log( averageAbsoluteIntensityDifference[k] );

        RealType distance = vcl_log( vcl_sqrt( distances[k] ) );

        sumY += averageAbsoluteIntensityDifference[k];
        sumX += distance;
        sumXX += ( distance * distance );
        sumXY += ( averageAbsoluteIntensityDifference[k] * distance );
        }
      RealType N = static_cast<RealType>( distances.size() );

      RealType slope = ( N * sumXY - sumX * sumY )
        / ( N * sumXX - sumX * sumX );

      ItO.SetCenterPixel(
        static_cast<typename OutputImageType::PixelType>( 3.0 - slope ) );
      progress.CompletedPixel();
      }
    }*/
}

template<class TInputImage, class TMaskImage, class TOutputImage>
void
ScalarToTextureImageFilter<TInputImage, TMaskImage, TOutputImage>
::PrintSelf(std::ostream &os, Indent indent) const
{
  Superclass::PrintSelf( os, indent );

  os << indent << "Region size: "
    << this->m_RegionSize << std::endl;
}

}// end namespace itk

#endif	/* ITKSCALARTOTEXTUREIMAGEFILTER_TXX */

