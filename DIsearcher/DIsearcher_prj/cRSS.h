#ifndef CRSS_H
#define CRSS_H

#include "utils.h"

class cRSS
{
public:
    string orig_loc_pos; // = 40687000
    string orig_abs_pos; // = 87084616
    string orig_complement; // = 0
    string orig_spacer; //= 12
    string orig_matrix; // = cacagaa-acagaagcaatg-acaaaaacc
    string orig_par6; // = 0
    string orig_par7; // = ccagcagcacatcaaaaagcttatctaccatgatcaactcggcttcatacctgggatgcaaggctggttcaacatatgcaaatcattaaaagtaatccatcacagaaacagaagcaatgacaaaaacc
    string orig_spacer1; // = 12
    string orig_heptamer; // = 2
    string orig_nanomer;	// = 0
    string orig_perrcent;	//%	= 91.49
    string orig_exon;	// = 341
    string orig_intron; //	= -
    string orig_five;	//5' = -
    string orig_thri;	//3' = -
    string orig_numer; //#  = 2


    //производные
    bool isExon;
    bool isIntron;
    bool isFive;
    bool isThri;
    bool isDel;
    bool isInv;
    tExonPos loc_pos;
    tCountExon numer;
    tGenLen A;
    tGenLen B;

    bool fSaveToDelInv;



    string toString();

    void detectKoefA(cRSS r) {}
    //void detectKoefB(cRSS &r){}

    cRSS():
        orig_loc_pos(""),
        orig_abs_pos(""),
        orig_complement(""),
        orig_spacer(""),
        orig_matrix(""),
        orig_par6(""),
        orig_par7(""),
        orig_spacer1(""),
        orig_heptamer(""),
        orig_nanomer(""),
        orig_perrcent(""),
        orig_exon(""),
        orig_intron(""),
        orig_five(""),
        orig_thri(""),
        orig_numer(""),


        isExon(false),
        isIntron(false),
        isFive(false),
        isThri(false),
        isDel(false),
        isInv(false),
        loc_pos(0),
        numer(0),
        A(0),
        B(0),
        fSaveToDelInv(false)
    {};

    ~cRSS() {}
protected:
private:
};

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
// подавить "warning: base class 'struct ' has a non-virtual destructor [-Weffc++]"

///определение коэфициентов А и В
///тоже но через функторы
struct detectKoefA: public unary_function<cRSS,  void>
{
    void operator() (cRSS &r);
};

struct detectKoefB: public unary_function<cRSS,  void>
{
    void operator() (cRSS &r);
};

/// создает ли данный cRSS  Del inv
struct cRSS_isDel: public unary_function<cRSS,  bool>
{
    bool operator() (cRSS &r);
};
struct cRSS_isInv: public unary_function<cRSS,  bool>
{
    bool operator() (cRSS &r);
};
struct cRSS_isDelInv: public unary_function<cRSS,  bool>
{
    bool operator() (cRSS &r);
};
#pragma GCC diagnostic pop



#endif // CRSS_H
