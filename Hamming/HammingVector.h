#pragma once
#include <stdexcept>
#include <vector>

using namespace std;

class HammingVector
{
    vector<int> data; //p
    vector<int> message; //x
    vector<int> parity; //z
    vector<vector<int>> encode; //G
    vector<vector<int>> check; //H
    vector<vector<int>> decode; //R
    int totalBits;
    int dataBits;
    int parityBits;
    int eBit;


protected:
    void buildG();
    void buildH();
    void buildR();

public:
    explicit HammingVector( int bits );
    explicit HammingVector( vector<int> const &message );

    vector<int> getData() const;
    vector<int> getParity() const;
    vector<int> getMessage() const;
    vector<int> getEMessage() const;
    static bool isPowerOfTwo( int n );
    static vector<int> matrixCrossVector( const vector<vector<int>> &lhs, const vector<int> &rhs );
    
};

