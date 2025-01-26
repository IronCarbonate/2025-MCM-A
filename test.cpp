#include "noise-reduction.hpp"
using namespace std;
int main()
{
    c=0;
    vector <double> Function = function_generation(-4,1,0,1);
    vector <double> Image = image_generation(Function);
    vector <double> Image_2 = movingAverage(Image,5);

    cout<<"Number of peaks in the original image: "<<find_Peak(Image)<<endl;
    return 0;
}