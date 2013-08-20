/* 
 * File:   PruebasVarianza.cpp
 * Author: Fabian
 *
 * Created on August 7, 2013, 6:55 PM
 */

#include <cstdlib>
#include <vnl/vnl_matrix.h>
#include <vnl/algo/vnl_determinant.h>
#include <iostream>

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {

    vnl_matrix<float> matriz;
    matriz.set_size(3,3);
    
    matriz[0][0] = 3; matriz[0][1] = 0; matriz[0][2] = 0;
    matriz[1][0] = 0; matriz[1][1] = 3; matriz[1][2] = 0;
    matriz[2][0] = 0; matriz[2][1] = 0; matriz[2][2] = 3;

    
    matriz.print(std::cout);
    std::cout<<std::endl;
    
    float mean = matriz.mean();
    
    float variance = 0;
    
    for(int i=0; i<3;i++){
        for(int j=0; j<3; j++)
        {
            variance += (matriz[i][j]-mean)*(matriz[i][j]-mean);
        }
    }      
    
    variance = variance/8;
    
    std::cout<<"Variance1 "<<variance<<std::endl;
    
    vnl_matrix<float> I;
    I.set_size(3,1);
    
    I.fill(1);
    
    I.print(std::cout);    
    std::cout<<std::endl;
    
    vnl_matrix<float> It = I.transpose();
    
    It.print(std::cout);
    std::cout<<std::endl;
    
    vnl_matrix<float> temp = (It*matriz*I)/9;
    
    temp.print(std::cout);
    std::cout<<std::endl;
    
    vnl_matrix<float> x = matriz - temp.get(0,0);
    
    vnl_matrix<float> cov = (x*x.transpose())/2;
    
    cov.print(std::cout);
    
    float det = vnl_determinant(cov);
    
    std::cout<<"Variance2 "<<det<<std::endl;
    
    return 0;
}

