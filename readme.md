## Description of Program
Creates a HammingVector (Hamming Code) with a user-defined number of data bits.
After creation, prints the randomized data and the calculated message.
Then an errored version of the message is "sent" to a new HammingVector.
Finally, the program prints the errored message, the parity vector of the error message, the corrected message, and the derived data.

## Description of algorithms and libraries used
Algorithms used:
- matrixCrossVector function uses a bog standard matrix multiplication algorithm and as such is O(n^2). 
- buildG function builds the G matrix based on whether or not the current row is a power of 2; it is O(n^2). 
- buildH and buildR functions are used to decode a message in different ways. Both should be O(n^2).

Libraries used:
- stdexcept
    - "defines a set of standard exceptions that both the library and programs can use to report common errors"
    - From https://cplusplus.com/reference/stdexcept/
    - Used to handle invalid input to HammingVector class methods.
- vector
    - "sequence containers representing arrays that can change in size"
    - From https://cplusplus.com/reference/vector/vector/?kw=vector
    - Used to build the necessary vectors and matrices.
- random
    - "allows [one] to produce random numbers using combinations of generators and distributions"
    - From https://cplusplus.com/reference/random/?kw=random 
    - Used to randomly generate the data vector and create the error message.
- iostream
    - "inherits all members from its two parent classes istream and ostream, thus being able to perform both input and output operations"
    - From https://cplusplus.com/reference/istream/iostream/?kw=iostream
    - Used to used to receive user input, output results, as well as some debugging purposes.
- iomanip
    - "provides parametric manipulators"
    - From https://cplusplus.com/reference/iomanip/?kw=iomanip
    - Used to format console outputs

## Description of functions and program structure
**_int main()_** \
controls all the I/O and creates the HammingVectors \
calls: \
&emsp;HammingVector(int) \
&emsp;vector<int> HammingVector.getData() \
&emsp;vector<int> HammingVector.getMessage() \
&emsp;vector<int> HammingVector.getEMessage() \
&emsp;void printVector(vector<int>) \
&emsp;HammingVector(vector<int>) \
&emsp;HammingVector.getParity()

**_HammingVector(int)_** \
Returns a new instance of HammingVector. First, checks to make sure the number of data bits is large enough. Then, it calculates the number appropriate number of parity bits. Next, it randomly generates the data vector and builds the G, H, and R matrices. Finally, it uses matrix multiplication to calculate the message and parity of the HammingVector. \
calls: \
&emsp;void HammingVector.buildG() \
&emsp;void HammingVector.buildH() \
&emsp;void HammingVector.buildR() \
&emsp;vector<int> HammingVector::matrixCrossVector(vector<vector<int>>, vector<int>)

**_vector<int> HammingVector.getData()_** \
Returns the instance's data vector

**_vector<int> HammingVector.getMessage()_** \
Returns the instance's message vector

**_vector<int> HammingVector.getEMessage()_** \
First, creates a copy of the instance's message. If the instance's parity vector is a zero vector, then a random bit in the copy is flipped and the copy is returned. Else, a bit in the copy is flipped based on the instance's parity vector and the copy is returned.

**_void printVector(vector<int>)_** \
Prints the given vector to the screen

**_HammingVector(vector<int>)_** \
Returns a new instance of HammingVector. First, this function checks that the input vector is long enough. Then, given that the vector is indeed long enough, the number of data and parity bits is calculated based on the size of the vector. Then the G, H, and R, matrices are calculated. Then the parity vector is calculated and the message is corrected based on the parity vector. Finally, the data is derived from the corrected message. \
calls: \
&emsp;void HammingVector.buildG() \
&emsp;void HammingVector.buildH() \
&emsp;void HammingVector.buildR() \
&emsp;vector<int> HammingVector::matrixCrossVector(vector<vector<int>>, vector<int>)

**_vector<int> HammingVector.getParity()_** \
Returns the instance's parity vector

**_void HammingVector.buildG()_** \
Builds the instance's G matrix (encoding matrix) with a size of totalBits x dataBits. \
calls: \
&emsp;bool HammingVector::isPowerOfTwo(int)

**_void HammingVector.buildH()_** \
Builds the instance's H matrix (check matrix) with a size of parityBits x totalBits.

**_void HammingVector.buildR()_** \
Builds the instance's R matrix (decoding matrix) with a size of dataBits x totalBits. \
calls: \
&emsp;bool HammingVector::isPowerOfTwo(int)

**_vector<int> HammingVector::matrixCrossVector(vector<vector<int>>, vector<int>)_** \
Takes in a matrix of size m x n and vector of size n x 1. Returns a vector of size m x 1. Used to calculate the data, message, and parity vectors.

**_bool HammingVector::isPowerOfTwo(int)_** \
Returns a boolean indicating whether or not the input is a power of two

## Description of testing and verification process
The only part of the program susceptible to error is user input. The expected behavior on invalid input is to print the thrown exception then reprint the input prompt.
These input scenarios were tested:

- input <1 resulted in expected behavior
- input as NAN resulted in expected behavior
- input as float resulted in the float getting rounded down and automatically cast to an integer and the program ran without exception

## How run it
There are two ways to run this program. Both assume that you have extracted the zip file into an empty folder and are currently in said folder.

1. Go to .\x64\Debug
2. Run .\Hamming.exe
3. Use the program as described in the project description

If unable to to do that for any reason, you may try the following instead.
1. Open the Visual Studio solution in Visual Studio 2019 (other versions might work, but I make no guarantees)
2. In Visual Studio, click on Debug > Start Without Debugging
3. Use the program as described in the project description
