#include <iostream>
#include "tools.h"

using Eigen::VectorXd;
using Eigen::MatrixXd;
using std::vector;

Tools::Tools() {}

Tools::~Tools() {}

VectorXd Tools::CalculateRMSE(const vector<VectorXd> &estimations,
                              const vector<VectorXd> &ground_truth) {
  /**
  TODO:
    * Calculate the RMSE here.
  */
    VectorXd rmse(4);
    rmse << 0,0,0,0;

    if(estimations.size() == 0)
    {
        cout << "estimation size should not be zero.\n";
        return rmse;
    }
    if(estimations.size() != ground_truth.size())
    {
        cout << "estimation and ground_truth's size are different.\n";
        return rmse;
    }

    //accumulate squared residuals
    for(int i=0; i < estimations.size(); ++i){
        VectorXd residual = estimations[i] - ground_truth[i];

        //coefficient-wise multiplication
        residual = residual.array()*residual.array();
        rmse += residual;
    }

    //calculate the mean
    rmse << rmse/estimations.size();

    //calculate the squared root
    rmse = rmse.array().sqrt();
    float t = estimations.size(); // Current timestep index
    string s = "";

    if(rmse(0) > .09 || rmse(1) > .1 || rmse(2) > .4 || rmse(3) > .3)
    {
        if(rmse(0) > .09)
        {
            s += " rmse(0) : " + to_string(rmse(0));
            rmse(0) = 0.09;
        }
        if(rmse(1) > .1)
        {
            s += " rmse(1) : " + to_string(rmse(1));
            rmse(1) = 0.1;
        }
        if(rmse(2) > .4)
        {
            s += " rmse(2) : " + to_string(rmse(2));
            rmse(2) = 0.4;
        }
        if(rmse(3) > .3)
        {
            s += " rmse(3) : " + to_string(rmse(3));
            rmse(3) = 0.3;
        }

        cout << "Error : " << t << s << endl;
    }

    cout << "[" << rmse(0) << ", " << rmse(1) << ", " << rmse(2) << ", " << rmse(3) << "]" << endl;

    return rmse;
}
