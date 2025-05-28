/**
  ******************************************************************************
  * @file           : Util
  * @brief          : Class Util define use Utility function 
  ******************************************************************************
  * Made in GreenOasis  
  * https://github.com/jungkyeong
  * CopyRigth MIT License
  ******************************************************************************
  * Release History
  * branch name, working description, time
  * version_001: define add version  2024-09-22
  ******************************************************************************
  */

#ifndef __UTIL_HPP
#define __UTIL_HPP

#include <iostream>

class Util {
private:

public:

    /**
     * @brief file read data
     * @param filename input file root
     * @param data output data
     * @return Success data_len, Fail -1
     */
    int read_from_file(const char *filename, void **data);

    /**
     * @brief file write and save
     * @param filename input file name
     * @param data input data
     * @param data_len input data size
     * @return Success 0, Fail -1
     */
    int write_to_file(const char *filename, const void *data, size_t data_len);

};

#endif /* __UTIL_HPP */