#ifndef SINGLE_SLIT_H
#define SINGLE_SLIT_H


class single_slit : public obstacle
{
public:
    single_slit();
    void generate_calc_data();
    void generate_img_data();
};

#endif // SINGLE_SLIT_H
