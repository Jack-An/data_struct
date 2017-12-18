//
// Created by Jack on 2017/11/27.
//
#include <algorithm>
#include <iostream>
#include <cmath>
#include <random>
#include <ctime>
#include <vector>

void maxmin(const std::vector<double> &golds, size_t lo, size_t hi, double &fmax, double &fmin) {
    double lmax, lmin, rmax, rmin;
    if (lo == hi) {
        fmax = fmin = golds[lo];
    } else if (lo == hi - 1) {
        if (golds[lo] < golds[hi]) {
            fmax = golds[hi];
            fmin = golds[lo];
        } else {
            fmax = golds[lo];
            fmin = golds[hi];
        }
    } else {
        size_t mid = (lo + hi) / 2;
        maxmin(golds, lo, mid, lmax, lmin);
        maxmin(golds, mid + 1, hi, rmax, rmin);
        if (lmax > rmax) {
            fmax = lmax;
        } else {
            fmax = rmax;
        }
        if (lmin > rmin) {
            fmin = rmin;
        } else {
            fmin = lmin;
        }
    }
}


void maxmin2(const std::vector<double> &golds, double &max, double &min) {
    max = golds[0];
    min = golds[0];
    for (size_t i = 1; i < golds.size(); ++i) {
        if (max < golds[i]) {
            max = golds[i];
        }
        if (min > golds[i]) {
            min = golds[i];
        }
    }
}

/**
 * 更加严谨的蛮力算法
 * @tparam ForwordIt
 * @param first
 * @param last
 * @return
 */

template<typename ForwordIt>
std::pair<ForwordIt, ForwordIt> maxmin3(ForwordIt first, ForwordIt last) {
    std::pair<ForwordIt, ForwordIt> result(first, last);
    if (first == last) return result;
    if (++first == last) return result;
    if (*first < *result.first) {
        result.first = first;
    } else {
        result.second = first;
    }
    while (++first != last) {
        ForwordIt i = first;
        if (++first == last) {
            if (*i < *result.first) result.first = i;
            else if (!(*i < *result.second)) result.second = i;
            break;
        } else {
            if (*first < *i) {
                if (*first < *result.first) result.first = first;
                if (!(*i < *result.second)) result.second = i;
            } else {
                if (*i < *result.first) result.first = i;
                if (!(*first < *result.second)) result.second = first;
            }
        }
    }
    return result;
}


int main() {
    int exp;
    std::cin >> exp;
    auto len = static_cast<std::size_t >(pow(2, exp));
    std::vector<double> arr;
    arr.resize(len);
    std::default_random_engine e;        //随机数引擎对象
    std::uniform_real_distribution<double> u(0.0, 100000.0);   //使用实数分布模板类
    //赋值
    for (size_t i = 0; i < len; ++i) {
        arr[i] = u(e);
    }
    auto start = clock();  //计时
    double fmax = 0.0;
    double fmin = 0.0;
    maxmin2(arr, fmax, fmin);
    auto end = clock();
    std::cout << "最大值：" << fmax << "     最小值： " << fmin
              << "   数据量为2的" << exp << "次方时，蛮力算法 const time: " << (end - start) / 1000.0
              << " s" << std::endl;
    fmax = fmin = 0.0;
    start = clock();
    maxmin(arr, 0, len - 1, fmax, fmin);
    end = clock();
    std::cout << "最大值：" << fmax << "     最小值： " << fmin
              << "   数据量为2的" << exp << "次方时，分治算法 const time: " << (end - start) / 1000.0
              << " s" << std::endl;
    start = clock();
    auto result = maxmin3(arr.begin(), arr.end());
    end = clock();
    std::cout << "最大值：" << *(result.second) << "     最小值： " << *(result.first)
              << "   数据量为2的" << exp << "次方时，标准库算法 const time: " << (end - start) / 1000.0
              << " s" << std::endl;

    return 0;
}


