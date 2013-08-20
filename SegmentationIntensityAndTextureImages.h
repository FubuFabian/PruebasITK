/* 
 * File:   SegmentationIntensityAndTextureImages.h
 * Author: Fabian
 *
 * Created on August 15, 2013, 1:13 PM
 */

#ifndef SEGMENTATIONINTENSITYANDTEXTUREIMAGES_H
#define	SEGMENTATIONINTENSITYANDTEXTUREIMAGES_H

#include <itkImage.h>
#include <itkRescaleIntensityImageFilter.h>

template<class TInputImage>
class SegmentationIntensityAndTextureImages
{
    
public:
    
    typedef TInputImage ImageType;
    
    static SegmentationIntensityAndTextureImages * New(){
        return new SegmentationIntensityAndTextureImages;
    }
        
    void setInput(typename ImageType::Pointer image);
    
    typename ImageType::Pointer getIntensityImage();
    
    typename ImageType::Pointer getTextureImage();
    
private:
    
    typename ImageType::Pointer inputImage;
    
    typedef typename itk::RescaleIntensityImageFilter<ImageType, ImageType> 
                                                              RescaleFilterType;
    
    
};

#ifndef ITK_MANUAL_INSTANTIATION
#include "SegmentationIntensityAndTextureImages.cpp"
#endif

#endif	/* SEGMENTATIONINTENSITYANDTEXTUREIMAGES_H */

