#include <iostream>
#include <vector>
#include <string>
#include "libs/MatrixMath/MatrixMath.h"

void printData(std::vector<float> data)
{
    for(int i = 0; i < data.size(); ++i )
    {
        std::cout<<data[i]<<" ";
    }
    std::cout<<std::endl;
}

struct Mat
{
    int rows;
    int cols;
    std::vector<float> Data;
};

int main() {

    std::vector<float> MatData = { 0.0f, 0.0f, 0.0f, 1.0f, 3.0f, 0.0f, 0.0f, 0.0f,
                                   0.0f, 2.0f, 3.0f, 0.0f, 0.0f, 0.0f, 0.0f , 0.0f,
                                   0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
                                   2.0f, 3.44f, 7.0f, 1.0f, 0.0f, 0.0f, 0.0f,0.0f};
    SparseMatrix myMat(4, 8, MatData);

    std::vector<float> DataSet = myMat.getRow(2);
    printData(myMat.getRow(0));
    printData(myMat.getRow(3));


    /*
     * Some basic matrix math
     *
     * When working with matrix math on a computer cpu make sure to not use the default way of doing matrix math taught in schools
     * It too cache inefficient on large matrix items such a photos, using this index method we can remove several
     */

    Mat m1 = {2, 3, {1.0, 3.0, 4.0, 2.0, 1.0, 1.5}};
    Mat m2 = {2, 3, {3.0, 1.0, 2.5,
                                      2.5, 23.3, 7.5  }};

    Mat resultData = {m2.cols, m1.rows, std::vector<float>(m2.cols*m1.rows)};

    int rowOffsetM1 = 0;
    for(int RightRow = 0; RightRow < m1.rows; ++RightRow) {
        int resultOffset = RightRow *m2.cols;
        for (int RightCol = 0; RightCol < m1.cols; ++RightCol, ++rowOffsetM1) {
            int rowOffsetM2 = RightCol*m2.cols;
            for (int LeftCol = 0; LeftCol < m2.cols; ++LeftCol) {
                float mat1 = m1.Data[rowOffsetM1];
                float mat2 = m2.Data[rowOffsetM2 + LeftCol];
                resultData.Data[resultOffset + LeftCol] += mat1*mat2;
            }
        }
    }




    return 0;
}
