#include <cstdio>
#include <cstring>
#include <vector>
#include <cmath>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
using namespace std;

const double PI = acos(-1.0);
//global variable
fstream output_f;
//define complex struct 
struct C{
    //real and image part
    double real,image;
    // constructor
    C(double _real,double _image){ real = _real; image = _image; }
    //overload operator sign +
    C friend operator + (const C c1,const C c2){
        return C(c1.real + c2.real,c1.image + c2.image);
    }

    //overload operator sign -
    C friend operator - (const C c1,const C c2){
        return C(c1.real - c2.real,c1.image - c2.image);
    }

    //overload operator sign *
    C friend operator * (const C c1,const C c2){
        return C(c1.real * c2.real - c1.image * c2.image,c1.real * c2.image + c1.image * c2.real);
    }

    //get string for complex just for ouput
    string toString(){
        stringstream ss;
        ss<<showpoint<<real<<"+"<<showpoint<<image<<"i ";
        return ss.str();
    }
};
//define FFT struct
class FFT{
    vector<C> Wx;
    int log_num;
public:
    FFT(){

    }
    // constructor 
    FFT( vector<double> Ax){
        // clear vector
        Wx.clear();
        for(int i = 0; i < Ax.size(); i++){
            Wx.push_back( C(Ax[i],0.0) );
        }
        log_num = (int)(log2(Ax.size()));
        cout<<log_num<<endl;
    }
    // test
    void test(ostream ci){
        ci << "good" <<endl;
    }
    // get FFT
    vector<C> get_FFT(){
        // reverse to bit get correct index
        reverse();
        // i for length of each segment
        for(int i = 2; i <= Wx.size(); i = i * 2){

            C wc = C( cos(2*PI/(i*2.0)) , sin(2*PI/(i*1.0)));
            // j for start index
            for(int j = 0; j < Wx.size(); j += i){
                C w = C(1.0,0);
                // use k to traverse current segment
                // only traverse half of segment
                for(int k = j; k - j < i/2; k++){
                    C tmp1 = Wx[k];
                    C tmp2 = w * Wx[k + (i/2)] ;
                    Wx[k] = tmp1 + tmp2;
                    Wx[k + (i/2)] = tmp1 - tmp2;
                    w = w * wc;
                }
            }
        }
        return Wx;
    }
private:
    //get bit reverse
    vector<int> get_bit_reverse(vector<int> v1){
        if(v1.size() == 2) return v1;
        vector<int> v_0;
        v_0.clear();
        vector<int> v_1;
        v_1.clear();
        for(int i = 0; i < v1.size(); i++){
            if(i&1) v_1.push_back(v1[i]);
            else v_0.push_back(v1[i]);
        }
        v_0 = get_bit_reverse(v_0);
        v_1 = get_bit_reverse(v_1);
        v1.clear();
        for(int i = 0; i < v_0.size(); i++) v1.push_back(v_0[i]);
        for(int i = 0; i < v_1.size(); i++) v1.push_back(v_1[i]);
        return v1;
    }
    // reverse index
    void reverse(){
        vector<int> v1;
        v1.clear();
        puts("good");
        for(int i = 0; i < Wx.size(); i++) v1.push_back(i);
        v1 = get_bit_reverse(v1);
        for(int i = 0; i < v1.size() / 2; i++){
            cout<<v1[i]<<endl;
            swap(Wx[i],Wx[ v1[i] ]);
        }
        puts("bad");
    }
};
//get data input use ifstream
vector<double> get_input(string filepath,int size){
    fstream fs;
    fs.open(filepath.c_str(),fstream::in);
    vector<double> input;
    input.clear();
    int count = 0;
    for(int i = 0; i < size; i++){
        int tmp; 
        fs>>tmp;
        input.push_back(tmp);
    }
    cout<<"cout : "<<input.size()<<endl;
    fs.close();
    return input;
}
//put ouput data into "output.txt"
void write_file(vector<C> ans){
    output_f<<"\n----------------------------------------------------"<<"\n";
    for(int i = 0; i < ans.size(); i++){
        output_f<<ans[i].toString();
    }
    output_f<<"\n----------------------------------------------------"<<"\n";
}
void solve(string inputpath,int size){
    vector<double> input = get_input(inputpath,size);
    FFT test = FFT(input);
    vector<C> ans = test.get_FFT();
    write_file(ans);
}
int main(){
    cout<<PI<<endl;
    output_f.open("output.txt",fstream::out);
   // solve("./Project_2_test/4.txt");
   // solve("./Project_2_test/8.txt");
   // solve("./Project_2_test/16.txt");
    solve("./Project_2_test/32.txt",32);
   // solve("./Project_2_test/64.txt");
    //solve("./Project_2_test/128.txt");
 //   solve("./Project_2_test/256.txt",256);
    output_f.close();
    return 0;
}
