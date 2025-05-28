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

#include "Util.h"

/**
 * @brief file read data
 * @param filename input file root
 * @param data output data
 * @return Success data_len, Fail -1 Nothing 0
 */
int Util::read_from_file(const char *filename, void **data){

    int data_len = 0;

    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        printf("file open fail : %s \n", filename);
        return 0;
    }

    // get file size
    fseek(file, 0, SEEK_END); // file pointer goto move end 
    data_len = ftell(file); // get file size from file pointer position 
    fseek(file, 0, SEEK_SET); // set file pointer clear set move init position 

    // read data
    *data = malloc(data_len+1);
    if (*data == NULL) {
        printf("memory malloc fail \n");
        free(*data);
        fclose(file);
        return -1;
    }

    int read_len = fread(*data, 1, data_len, file);
    if (read_len != data_len) {
        printf("file read fail \n");
        free(*data);
        fclose(file);
        return -1;
    }

    ((char*)*data)[data_len] = '\0'; 

    fclose(file);
    return data_len;
}

/**
* @brief file create
* @param filename input file root
* @param data input file data
* @param data_len input file length 
* @return Success 0, Fail 1
*/
int Util::write_to_file(const char *filename, const void *data, size_t data_len){
    FILE *file = fopen(filename, "wb");
    if (file == NULL) {
        printf("Error opening file \n");
        return 1;
    }
    size_t written = fwrite(data, 1, data_len, file);
    if (written != data_len) {
        printf("Error writing to file \n");
        fclose(file);
        return 1;
    }
    fclose(file);
    return 0;
}