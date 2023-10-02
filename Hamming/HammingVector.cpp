#include "HammingVector.h"
#include <random>

bool HammingVector::isPowerOfTwo( int n )
{
    int i = 0;
    int curr = pow( 2, i );

    if ( n < 1 )
        throw invalid_argument( "n must be greater than or equal to 1" );

    while ( curr <= n )
    {
        if ( curr == n )
            return true;
        else
            curr = pow( 2, ++i );
    }
    return false;
}

void HammingVector::buildG()
{
    int currDataRow = 0;
    int currParityMod = 2;
    int i;
    int j;
    for ( i = 0; i < totalBits; ++i ) //select row
    {
        encode.emplace_back();
        if ( isPowerOfTwo( i + 1 ) )
        {

            for ( j = 1; j <= totalBits; ++j )
            {
                if ( !isPowerOfTwo( j ) )
                {
                    encode.at( i ).push_back( ( ( j % currParityMod ) >= ( currParityMod / 2 ) ) ? 1 : 0 );
                }
            }
            currParityMod *= 2;
        }
        else
        {
            for ( j = 0; j < dataBits; ++j )
            {
                encode.at( i ).push_back( currDataRow == j ? 1 : 0 );
            }
            ++currDataRow;
        }
    }

}

void HammingVector::buildH()
{
    int i;
    int j;
    int currParityMod;
    for ( i = 0; i < parityBits; ++i )
    {
        check.emplace_back();
        currParityMod = pow( 2, i + 1 );
        for ( j = 1; j <= totalBits; ++j )
            check.at( i ).push_back( ( ( j % currParityMod ) >= ( currParityMod / 2 ) ) ? 1 : 0 );
    }

}

void HammingVector::buildR()
{
    int i;
    int j;
    int currDataCol;
    for ( i = 0; i < dataBits; ++i )
    {
        decode.emplace_back();
        currDataCol = 0;
        for ( j = 0; j < totalBits; ++j )
        {
            if ( !isPowerOfTwo( j + 1 ) )
            {
                decode.at( i ).push_back( i == currDataCol ? 1 : 0 );
                ++currDataCol;
            }
            else
            {
                decode.at( i ).push_back( 0 );
            }
        }
    }

}

vector<int> HammingVector::matrixCrossVector( const vector<vector<int>> &lhs, const vector<int> &rhs )
{
    vector<int> res;
    int i;
    int j;

    if ( lhs.at( 0 ).size() != rhs.size() )
        throw invalid_argument( "lhs[0].size() must equal rhs.size()" );

    for ( i = 0; i < lhs.size(); ++i ) {
        res.emplace_back();
        for ( j = 0; j < rhs.size(); ++j )
            res.at( i ) += lhs.at( i ).at( j ) * rhs.at( j );
        res.at( i ) %= 2;
    }

    return res;
}

HammingVector::HammingVector( int bits )
{
    random_device rando;
    int currParity = 3;
    int i;

    if ( bits < 2 )
        throw invalid_argument( "bits must be 2 or greater" );
    dataBits = bits;

    while ( pow( 2, currParity ) - currParity - 1 < bits )
        ++currParity;
    parityBits = currParity;
    totalBits = parityBits + dataBits;
    eBit = -1;

    data.resize( bits );
    for ( i = 0; i < bits; ++i )
        data.at( i ) = rando() % 2;

    buildG();
    buildH();
    buildR();

    message = matrixCrossVector( encode, data );
    parity = matrixCrossVector( check, message );
}

HammingVector::HammingVector( const vector<int> &eMessage )
{
    vector<int>::const_iterator rit;
    vector<int> checkVector;
    int i = 0;

    if ( eMessage.size() < 5 )
        throw invalid_argument( "parameter must have a min size of 5" );

    message = eMessage;
    totalBits = eMessage.size();
    parityBits = ceil( log( totalBits + 1 ) / log( 2 ) );
    dataBits = totalBits - parityBits;
    eBit = 0;

    buildG();
    buildH();
    buildR();

    parity = matrixCrossVector( check, eMessage );
    for ( rit = parity.cbegin(); rit != parity.cend(); ++rit, ++i )
        eBit += ( pow( 2, i ) * *rit );

    if ( --eBit >= 0 )
        message.at( eBit ) ^= 1;

    data = matrixCrossVector( decode, message );

}

vector<int> HammingVector::getData() const
{
    return data;
}

vector<int> HammingVector::getParity() const
{
    return parity;
}

vector<int> HammingVector::getMessage() const
{
    return message;
}

vector<int> HammingVector::getEMessage() const
{
    vector<int> eMessage = message;
    random_device rando;
    int corrupted = rando() % ( eMessage.size() + 1 );

    if ( eBit >= 0 )
        eMessage.at( eBit ) ^= 1;
    else if ( corrupted < eMessage.size() )
        eMessage.at( corrupted ) ^= 1;

    return eMessage;
}

