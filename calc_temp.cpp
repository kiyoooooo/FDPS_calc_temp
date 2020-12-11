#include <iostream>
#include <fstream>
#include <unistd.h>
#include <sys/stat.h>
#include <stdio.h>
#include <vector>
#include <cmath>
#include <random>
#include <string.h>      //文字列の代入に使う
#include <bits/stdc++.h> //piの利用で必要(M_PI)

class ParticleInfo
{
public:
    uint32_t id;
    uint32_t type;
    /*position*/
    double posx;
    double posy;
    double posz;
    /*velocity*/
    double velx;
    double vely;
    double velz;
    /*結合*/
    uint32_t bond_pair[2];
    uint32_t bond_type[2];
    uint32_t nbond = 0;
    /*アングル*/
    uint32_t angle_pair[2][3];
    uint32_t angle_type[2];
    uint32_t nangle = 0;

    //sortを利用するために定義
    bool operator<(const ParticleInfo &another) const
    {
        //メンバ変数であるnum1で比較した結果を
        //この構造体の比較とする
        return id < another.id;
    }
};

int main(int argc, char *argv[])
{
    std::vector<ParticleInfo> pinfo;
    ParticleInfo temp_info;
    /*
    
    
    
    
    座標の読み込みを行う．*/
    std::ifstream ifs0(argv[1]);
    if (!ifs0)
    {
        std::cerr << "error0" << std::endl;
        std::exit(EXIT_FAILURE);
    }
    //いらないはじめの3行を捨てる．
    std::string delete_str[3];
    for (uint32_t i = 0; i < 3; i++)
    {
        std::getline(ifs0, delete_str[i]);
    }
    //ファイルの読み込み　粒子番号,粒子種は0から開始する．
    while (ifs0 >> temp_info.id >> temp_info.type >> temp_info.posx >> temp_info.posy >> temp_info.posz)
    {
        temp_info.id--;
        temp_info.type--;
        pinfo.push_back(temp_info);
    }
    ifs0.close();
    //はじめの文字列を読み込む
    double box_sx, box_sy, box_sz, box_ex, box_ey, box_ez, box_wt;
    sscanf(delete_str[0].c_str(), "'box_sx=%lf box_sy=%lf box_sz=%lf box_ex=%lf box_ey=%lf box_ez=%lf box_wt=%lf",
           &box_sx, &box_sy, &box_sz, &box_ex, &box_ey, &box_ez, &box_wt);
    //    std::cout <<std::setprecision(10)<< box_sx << " " << box_sy << " " << box_sz << " " << box_ex << " " << box_ey << " " << box_ez << " " << box_wt << std::endl;
    std::sort(pinfo.begin(), pinfo.end()); //classでオペレータを定義して利用している．
    /*
    
    
    
    
    速度の読み込みを行う．*/
    std::ifstream ifs1(argv[2]);
    if (!ifs1)
    {
        std::cerr << "error1" << std::endl;
        std::exit(EXIT_FAILURE);
    }
    //ファイルの読み込み
    while (ifs1 >> temp_info.id >> temp_info.velx >> temp_info.vely >> temp_info.velz)
    {
        temp_info.id--;
        pinfo.at(temp_info.id).velx = temp_info.velx;
        pinfo.at(temp_info.id).vely = temp_info.vely;
        pinfo.at(temp_info.id).velz = temp_info.velz;
    }
    ifs1.close();
    /*
    
    
    
    
    温度の計算を行う．*/
    double aav = 0.0;
    double ke;
    double temperture;
    for (int i = 0; i < pinfo.size(); i++)
    {
        aav+=pow(pinfo.at(i).velx,2.0)+pow(pinfo.at(i).vely,2.0)+pow(pinfo.at(i).velz,2.0);
    }
    ke = 0.5*aav;
    temperture = ke/1.5/(double)pinfo.size();
    std::cout<<temperture<<std::endl;
    return 0;
}