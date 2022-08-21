//
// Created by plotb on 8/19/22.
//

#ifndef PATHPLANNER_MATRIXMATH_H
#define PATHPLANNER_MATRIXMATH_H





struct Pose
{
    int x;
    int y;
};

struct IMatrix
{
    int Rows;
    int Cols;

    virtual float getValue(int row, int col) = 0;
    virtual void setValue(int row, int col) = 0;


};


struct Matrix : public IMatrix
{

    float getValue(int row, int col) override
    {
        return mData[row * Cols + col];
    }

    void setValue(int row, int col, float value)
    {
        mData[row * Cols + col] = value;
    }

private:
    std::vector<float> mData;
};



struct SparseMatrix
{

    SparseMatrix(int rows, int cols, std::vector<float>dataset)
    {
        Rows = rows;
        Cols = cols;
        int LastSize = 0;

        RowSpace = std::vector<unsigned int>(Rows +1, 0);

        for(int r = 0;  r< Rows; ++r )
        {
            for(int c = 0;  c < Cols; c++)
            {
                if( dataset[r*Cols + c] != 0) {
                    ColSpace.push_back(c);
                    mData.push_back(dataset[r * Cols + c]);
                }
            }
            RowSpace[r+1] = ColSpace.size();
        }

    }

    std::vector<float> getRow(int row)
    {
        std::vector<float> rowData(Cols, 0);
        for(int i = RowSpace[row]; i < RowSpace[row+1]; ++i)
        {
            rowData[ColSpace[i]] = mData[i];
        }
        return rowData;
    }

    int Rows;
    int Cols;
    std::vector<unsigned int>RowSpace;
    std::vector<unsigned int>ColSpace;
    std::vector<float>mData;


};






#endif //PATHPLANNER_MATRIXMATH_H
