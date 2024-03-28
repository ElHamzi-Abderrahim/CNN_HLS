
#ifndef LST_NET
#define LST_NET

struct Reshape_out_struct {
    double out_fmap[180];
    };

struct Percep_out_struct {
    double out_fmap[10];
    };


struct SoftMax_out_struct {
    double out_fmap[10];
    };


Reshape_out_struct Reshape(double matrice_in[3*3*20]);


Percep_out_struct Perceptron(double matrice_in[180]) ;


SoftMax_out_struct Softmax(double matrice_in[10]) ;


#endif