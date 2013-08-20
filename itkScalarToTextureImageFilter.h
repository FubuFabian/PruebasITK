/* 
 * File:   itkScalarToTextureImageFilter.h
 * Author: Fabian
 *
 * Created on July 29, 2013, 4:06 PM
 */

#ifndef ITKSCALARTOTEXTUREIMAGEFILTER_H
#define	ITKSCALARTOTEXTUREIMAGEFILTER_H

#include "itkImageToImageFilter.h"
#include <itkScalarImageToCooccurrenceMatrixFilter.h>
#include <itkImageRegionConstIterator.h>

namespace itk {

/** \class ScalarToTextureImageFilter. This class generates a texture image, 
 * by processing the texture value of each pixel using 
 * itkScalarImageToCooccurrenceMatrixFilter.h and itkHistogramToTextureFeaturesFilter.h
 * classes.  
 */
template<class TInputImage, class TMaskImage = Image<unsigned char, 
  ::itk::GetImageDimension<TInputImage>::ImageDimension>, 
  class TOutputImage = TInputImage>
class ITK_EXPORT ScalarToTextureImageFilter :
    public ImageToImageFilter<TInputImage, TOutputImage>
{
public:
  /** Standard class typedefs. */
  typedef ScalarToTextureImageFilter                      Self;
  typedef ImageToImageFilter<TInputImage, TOutputImage>   Superclass;
  typedef SmartPointer<Self>                              Pointer;
  typedef SmartPointer<const Self>                        ConstPointer;

  /** Standard New method. */
  itkNewMacro( Self );

  /** ImageDimension constants */
  itkStaticConstMacro( ImageDimension, unsigned int,
                       TInputImage::ImageDimension );

  /** Some convenient typedefs. */
  typedef float                                   RealType;
  typedef TInputImage                             InputImageType;
  typedef TMaskImage                              MaskImageType;
  typedef TOutputImage                            OutputImageType;
  typedef typename Statistics::ScalarImageToCooccurrenceMatrixFilter<InputImageType>
          GLCMGeneratorType;
  typedef typename GLCMGeneratorType::HistogramType HistogramType;

  /** Runtime information support. */
  itkTypeMacro( ScalarToTextureImageFilter,
                ImageToImageFilter );

  typedef ImageRegionConstIterator<InputImageType>
  ImageRegionIteratorType;
  typedef typename ImageRegionIteratorType::SizeType RegionSizeType;
  
  itkSetMacro( RegionSize, RegionSizeType );
  itkGetConstMacro( RegionSize, RegionSizeType );
  

  void SetMaskImage( const MaskImageType *mask )
    {
    this->SetNthInput( 1, const_cast<MaskImageType *>( mask ) ); 
    }
  const MaskImageType* GetMaskImage() const
    {
    return static_cast<MaskImageType*>( const_cast<DataObject *>
      ( this->ProcessObject::GetInput( 1 ) ) ); 
    }  
  void SetInput1( const TInputImage *input )
    {
    this->SetInput( input ); 
    }  
  void SetInput2( const TMaskImage *mask )
    {
    this->SetMaskImage( mask );
    }  
  void SetFilterRegionSize(RegionSizeType size)
    {
    this->m_RegionSize = size;  
    }
  void SetFilterPixelMinValue(int min)
    {
    this->m_PixelMinValue = min;  
    }
  void SetFilterPixelMaxValue(int max)
    {
    this->m_PixelMaxValue = max;  
    }
  void SetFilterNumberofBins(int bins)
    {
    this->m_NumberofBins = bins;  
    }
  void SetTextureFeature(int feature)
    {
     if(feature<=8 && feature>=0){  
        this->m_TextureFeature = feature;
     }else{
        std::cerr<<"Texture feature incorrect, using default feature"<<std::endl; 
     }
        
    }
  void HistogramVariance(typename HistogramType::Pointer histogram);

protected:
  ScalarToTextureImageFilter();
  ~ScalarToTextureImageFilter() {};
  void PrintSelf( std::ostream& os, Indent indent ) const;

  void GenerateData();

private:
  ScalarToTextureImageFilter( const Self& ); //purposely not implemented
  void operator=( const Self& ); //purposely not implemented

  RegionSizeType                       m_RegionSize;
  typename MaskImageType::Pointer      m_MaskImage;
  int                                  m_NumberofBins;
  int                                  m_PixelMinValue;
  int                                  m_PixelMaxValue;
  int                                  m_TextureFeature;

}; // end of class

} // end namespace itk

#ifndef ITK_MANUAL_INSTANTIATION
#include "itkScalarToTextureImageFilter.txx"
#endif

#endif	/* ITKSCALARTOTEXTUREIMAGEFILTER_H */

