#include "HammingVector.h"
#include <iostream>
#include <iomanip>

using namespace std;

void printVector( const vector<int> &v);

int main() {
    bool done = false;

    while ( !done ) 
    {
        int bits;
        cout << "Enter number of databits: ";
        cin >> bits;

        try 
        {
            HammingVector test1( bits );
            vector<int> data = test1.getData();
            vector<int> message = test1.getMessage();
            vector<int> received = test1.getEMessage();

            cout << setw( 17 ) << left;
            cout << "Message" << ": [";
            printVector( data );
            cout << "]" << endl << setw( 17 ) << "Send Vector" << ": [";
            printVector( message );
            cout << "]" << endl;

            HammingVector test2( received );

            cout << setw( 17 ) ;
            cout << "Received Message" << ": [";
            printVector( test2.getEMessage() );
            cout << "]" << endl << setw( 17 ) << "Parity Check" << ": [";
            printVector( test2.getParity() );
            cout << "]" << endl << setw( 17 ) << "Corrected Message: [";
            printVector( test2.getMessage() );
            cout << "]" << endl << setw( 17 ) << "Decoded Message" << ": [";
            printVector( test2.getData() );
            cout << "]" << endl;

            done = true;
        }
        catch ( exception const &e )
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Exception: " << e.what() << endl << endl;
        }
    }

    return 0;
}

void printVector( const vector<int> &v )
{
    int i;
    for ( i = 0; i < v.size(); ++i )
    {
        if ( i == 0 )
            cout << v.at( i );
        else
            cout << " " << v.at( i );
    }
}
