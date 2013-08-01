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
    
    typedef itk::Image<float, 2> ImageType;
    
    
    typedef itk::ImageFileReader<ImageType> ReaderType;
    const char*  filenamereader = "xy14.bmp";  
    ReaderType::Pointer reader = ReaderType::New();
    reader->SetFileName(filenamereader);
    reader->Update();   
    
    ImageType::Pointer image = reader->GetOutput();
    
    ImageType::IndexType pixel;
    pixel[0] = 5;
    pixel[1] = 6;
    
    //std::cout<<"Pixel Value: "<<image->GetPixel(pixel)<<std::endl;
    
    typedef itk::ScalarToTextureImageFilter<ImageType,ImageType> FilterType;
    FilterType::Pointer filter = FilterType::New();
    filter->SetInput(reader->GetOutput());
    FilterType::RegionSizeType size;
    size.Fill(11);
    filter->SetRegionSize(size);
    //filter->Update();*/
    
    /*typedef itk::MirrorPadImageFilter<ImageType, ImageType> PadFilterType;
    PadFilterType::Pointer padFilter = PadFilterType::New();
    ImageType::SizeType bound;
    bound[0] = 6;
    bound[1] = 6;
    padFilter->SetPadBound(bound);
    padFilter->SetInput(image);
    padFilter->Update();
    
    ImageType::Pointer padImage = padFilter->GetOutput();
    
    typedef itk::Statistics::ScalarImageToCooccurrenceMatrixFilter<ImageType> GLCMGeneratorType;
    
    GLCMGeneratorType::Pointer glcm = GLCMGeneratorType::New();
    
    glcm->SetNumberOfBinsPerAxis(16); //reasonable number of bins
    glcm->SetPixelValueMinMax(0, 255);
    
    typedef ImageType::OffsetType OffsetType;
    
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
    
    typedef GLCMGeneratorType::OffsetVector OffsetVectorType;
    OffsetVectorType::Pointer offsets = OffsetVectorType::New();
    
    offsets->reserve(4);
    offsets->InsertElement(0,offset1);
    offsets->InsertElement(1,offset2);
    offsets->InsertElement(2,offset3);
    offsets->InsertElement(3,offset4);
    
    glcm->SetOffsets(offsets);
    
    typedef GLCMGeneratorType::HistogramType HistogramType;
    typedef itk::Statistics::HistogramToTextureFeaturesFilter<HistogramType> TextureFeaturesType;
    TextureFeaturesType::Pointer textureFeatures = TextureFeaturesType::New();
    
    
    typedef itk::ExtractImageFilter<ImageType,ImageType> ExtractFilterType;
    ExtractFilterType::Pointer extractFilter = ExtractFilterType::New();

    extractFilter->SetInput(padImage);
    
    ImageType::Pointer outputImage = ImageType::New();
    outputImage->CopyInformation(image);
    outputImage->SetRegions(image->GetLargestPossibleRegion());
    outputImage->Allocate();
    outputImage->FillBuffer(0);
    
    typedef itk::ImageRegionIterator<ImageType> IteratorType;
    IteratorType itPad(padImage, padImage->GetLargestPossibleRegion());
    itPad.GoToBegin();
    
    typedef itk::ImageRegionIterator<ImageType> IteratorType;
    IteratorType itOut(outputImage, outputImage->GetLargestPossibleRegion());
    itOut.GoToBegin();
    
    ImageType::RegionType region;
    ImageType::IndexType regionIndex;
    ImageType::SizeType regionSize;
    
    regionSize[0] = 13;
    regionSize[1] = 13;   
    
    region.SetSize(regionSize);
    
    while(!itPad.IsAtEnd()){

        ImageType::IndexType index = itPad.GetIndex();
        regionIndex[0] = index[0];
        regionIndex[1] = index[1];
        
        region.SetIndex(regionIndex);
        
     
        if(padImage->GetLargestPossibleRegion().IsInside(region)){ 
            
            extractFilter->SetExtractionRegion(region);
            extractFilter->UpdateLargestPossibleRegion();
            
            glcm->SetInput(extractFilter->GetOutput());
            glcm->Update();
            
            textureFeatures->SetInput(glcm->GetOutput());
            textureFeatures->Update();
            
            outputImage->SetPixel(itOut.GetIndex(),textureFeatures->GetFeature(TextureFeaturesType::Inertia));
            
            ++itOut;
        }
        
        ++itPad;
        
        
    }
    
    std::cout<<"Input Image Size: "<<image->GetLargestPossibleRegion().GetSize()[0]<<","<<
            image->GetLargestPossibleRegion().GetSize()[1]<<std::endl;
    
    std::cout<<"Padded Image Size: "<<padImage->GetLargestPossibleRegion().GetSize()[0]<<","<<
            padImage->GetLargestPossibleRegion().GetSize()[1]<<std::endl;
    
    std::cout<<"Output Image Size: "<<outputImage->GetLargestPossibleRegion().GetSize()[0]<<","<<
            outputImage->GetLargestPossibleRegion().GetSize()[1]<<std::endl;
    
    //std::cout<<"Pixel Value: "<<outputImage->GetPixel(pixel)<<std::endl;
    
    typedef itk::RescaleIntensityImageFilter<ImageType, ImageType> RescaleFilterType;
    RescaleFilterType::Pointer normalizeFilter = RescaleFilterType::New();
    normalizeFilter->SetOutputMaximum(255);
    normalizeFilter->SetOutputMinimum(0);
    normalizeFilter->SetInput(outputImage);
    normalizeFilter->Update();
    
    ImageType::Pointer normalizeImage = normalizeFilter->GetOutput();
    
    std::cout<<"Pixel Value: "<<normalizeImage->GetPixel(pixel)<<std::endl;
    
    
    typedef itk::Image<unsigned char,2> OutputImageType;
    
    typedef itk::CastImageFilter<ImageType, OutputImageType> CastFilterType;
    CastFilterType::Pointer castFilter = CastFilterType::New();
    castFilter->SetInput(normalizeImage);
    
    typedef itk::ImageFileWriter<OutputImageType> WriterType;
    const char*  filenamewriter = "xy14_texture.bmp";
    WriterType::Pointer writer = WriterType::New();
    writer->SetFileName(filenamewriter);
    writer->SetInput(castFilter->GetOutput());
    writer->Update();*/
    
    return 0;
}

