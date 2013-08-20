/* 
 * File:   CrecimientoRegiones.cpp
 * Author: Fabian
 *
 * Created on August 8, 2013, 6:08 PM
 */

#include <itkImage.h>
#include <itkImageFileReader.h>
#include <itkImageFileWriter.h>
#include <itkCastImageFilter.h>
#include <itkConnectedThresholdImageFilter.h>
#include <itkNeighborhoodIterator.h>
#include <itkGrayscaleFillholeImageFilter.h>

#include <cstdlib>

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    
    typedef itk::Image<float, 2> ImageType;
    
    
    typedef itk::ImageFileReader<ImageType> ReaderType;
    const char*  filenamereader = "yz7_prob.bmp";  
    ReaderType::Pointer reader = ReaderType::New();
    reader->SetFileName(filenamereader);
    reader->Update();   
    
    ImageType::Pointer image = reader->GetOutput();

    typedef itk::ConnectedThresholdImageFilter<ImageType,ImageType> RegionGrowingType;
    RegionGrowingType::Pointer regionGrowing = RegionGrowingType::New();
    
    regionGrowing->SetInput(image);
    
    ImageType::IndexType seed;
    seed[0] = 82;
    seed[1] = 24;
    
    regionGrowing->SetSeed(seed);
    regionGrowing->SetReplaceValue(255);
    
    typedef itk::NeighborhoodIterator<ImageType> NeighborhoodIterator;
    NeighborhoodIterator::RadiusType radius;
    radius.Fill(1);
    
    ImageType::RegionType seedRegion;
    
    ImageType::RegionType::IndexType seedRegionIndex;
    seedRegionIndex[0] = seed[0] - 1;
    seedRegionIndex[1] = seed[1] - 1;
    seedRegion.SetIndex(seedRegionIndex);
    
    ImageType::RegionType::SizeType seedRegionSize;
    seedRegionSize.Fill(3); 
    
    NeighborhoodIterator it(radius,image,seedRegion);
    
    float accum = 0;
    for (unsigned int i = 0; i < it.Size(); ++i){    
        accum += it.GetPixel(i);  
    }
    
    float seedRegionMean = accum/(float)it.Size();
    
    float upperThreshold = seedRegionMean + seedRegionMean*0.55;
    float lowerThreshold = seedRegionMean - seedRegionMean*0.55;
    
    regionGrowing->SetUpper(upperThreshold);
    regionGrowing->SetLower(lowerThreshold);

    regionGrowing->Update();
    
    typedef itk::GrayscaleFillholeImageFilter<ImageType,ImageType> FillHolesType;
    FillHolesType::Pointer fillHoles = FillHolesType::New();
    fillHoles->SetInput(regionGrowing->GetOutput());
    fillHoles->Update();
    
    typedef itk::Image<unsigned char,2> OutputImageType;
    
    typedef itk::CastImageFilter<ImageType, OutputImageType> CastFilterType;
    CastFilterType::Pointer castFilter = CastFilterType::New();
    castFilter->SetInput(fillHoles->GetOutput());
    castFilter->Update();
    
    
    
    typedef itk::ImageFileWriter<OutputImageType> WriterType;
    const char*  filenamewriter = "yz7_rg.bmp";
    WriterType::Pointer writer = WriterType::New();
    writer->SetFileName(filenamewriter);
    writer->SetInput(castFilter->GetOutput());
    writer->Update();
    
    
    
    
    
    return 0;
}

