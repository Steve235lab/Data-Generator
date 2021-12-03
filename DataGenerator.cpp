// DataGenerator.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
// A data generator to create random data based on given original data and range.
// Written by Steve on 2021/7/7.
// Copyright (c) 2021 Steve D. J.. All rights reserved.
// Version 1.1

#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include  <iomanip>

using namespace std;

int checkMode(string buffer, int old_mode)
{
    if (buffer == "mode = 0" || buffer == "mode=0" || buffer == "mode0") {
        cout << "已切换至简单模式";
        
        return 0;
    }

    else if (buffer == "mode = 1" || buffer == "mode=1" || buffer == "mode1") {
        cout << "已切换至高级模式";
        
        return 1;
    }

    else {
        return old_mode;
    }
}

int checkMode_new(string buffer, int old_mode)
{
    if (buffer == "settings") {
        cout << "已进入设定模式" << endl;

        return 1;
    }

    else {
        return old_mode;
    }
}

double get_randnum(double og_data, double range)
{
    srand((unsigned)time(NULL)); //设置随机数种子，time(NULL)是用来获取当前系统时间，srand()以每次当前系统时间保证随机数种子不同，使每次产生的随机数不同
    double randnum = og_data, temp_num = 0;
    int temp_range, p_n = 0;
    temp_range = range * 1000;
    temp_num = rand() % temp_range;
    temp_num = temp_num / 1000;
    p_n = rand() % 2;

    if (p_n == 0){
        randnum = og_data + temp_num;
    }

    else if (p_n == 1) {
        randnum = og_data - temp_num;
    }
    return randnum;
}

int main()
{
    cout << "Data Generator v1.1" << endl
        << "Copyright (c) 2021 Steve D. J.. All rights reserved." << endl 
        << endl;

    // mode:：模式选择，0为数据生成模式，1为设定模式
    int mode = 0;
    // buffer：输入缓冲
    string buffer;
    // og_data：原始数据
    double og_data;
    // range：变化范围
    double range = 0.02;
    // digit：保留的小数点后位数
    int digit = 3;
    // data：生成的数据
    double data;

    while (true){
        cout << "键入'settings'来重新设置生成器参数。" << endl;

        // 数据生成模式
        while (mode == 0) {
            cout << "数据生成模式__输入原始数据：";
            cin >> buffer;

            // 模式切换检查
            int old_mode = mode;
            mode = checkMode_new(buffer, mode);
            if (mode != old_mode) {
                break;
            }

            // 生成在原始数据附近的随机数据
            og_data = atof(buffer.c_str());
            data = get_randnum(og_data, range);

            // 保留小数点后3位输出
            cout << fixed << setprecision(digit)
                << data << endl;
        }

        // 设定模式
        if (mode == 1) {
            cout << "设定模式__输入新的数据变化范围（原始默认值为0.02）：";
            cin >> buffer;

            // 模式切换检查
            int old_mode = mode;
            mode = checkMode_new(buffer, mode);
            if (mode != old_mode) {
                continue;
            }
            
            // 变更数据变化范围参数
            range = atof(buffer.c_str());

            cout << "设定模式__输入新的小数点后位数（整数，原始默认值为3）：";
            cin >> buffer;

            // 模式切换检查
            old_mode = mode;
            mode = checkMode(buffer, mode);
            if (mode != old_mode) {
                continue;
            }

            // 变更小数点后位数参数
            digit = atof(buffer.c_str());

            mode = 0;

            cout << "已通过设定模式完成参数更改" << endl
                << "新的参数为：" << endl
                << "数据变化范围：" << range << endl
                << "保留小数点后位数：" << digit << endl
                << "已为您自动切换为数据生成模式！" << endl;
        }
    }

    return 0;
}

