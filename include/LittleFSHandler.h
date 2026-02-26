/**
 * @file LittleFSHandler.h
 * @author Your Name
 * @brief Utility library for managing and visualizing the LittleFS file system.
 */

#ifndef LITTLEFSHANDLER_H
#define LITTLEFSHANDLER_H

#include <Arduino.h>
#include <LittleFS.h>
#include <string.h>
#include <vector>
#include <ArduinoJson.h>

#pragma once
using namespace std;

/**
 * @class LittleFS_Handler
 * @brief Static class providing tools for LittleFS operations.
 */
class LittleFS_Handler {
public:
    /**
     * @enum fs_status
     * @brief Result codes for LittleFS operations.
     */
    typedef enum {
        OPERATION_DONE,         ///< Operation completed successfully.
        FS_NOT_FOUND,           ///< LittleFS system or root path not found.
        CANNOT_OPEN_DIRECTORY,  ///< Target exists but is not a directory.
        WRONG_INPUT_FORMAT,      ///< String given is missing ' ' divisor
        FAILED_WRITING,         ///< Writing operation failed.
        FAILED_READING          ///< Reading operation failed.
    } fs_status;

    /**
     * @brief Recursively prints the file system structure to the Serial Monitor.
     * * This function traverses the directory tree starting from the specified root.
     * It visualizes the hierarchy using indentation and differentiates between 
     * files and directories.
     * @param dirname The starting path (e.g., "/" for root).
     * @param depth   Maximum recursion depth to prevent stack overflow.
     * @return fs_status Returns OPERATION_DONE on success, or an error code.
     * @note Directory entries are marked with [DIR], files with [FILE] plus size.
     */
    static fs_status printFS(const char* dirname, int depth);

    /**
     * @brief Parses a list of formatted strings and saves them as a JSON file in LittleFS.
     * * This function iterates through a vector of strings, splitting each string at the first 
     * space character to create Key-Value pairs. These pairs are then stored in a JSON 
     * document and written to the specified file system path.
     * * @param data A vector of Strings where each element must follow the "Key Value" format.
     * @param path The file system path where the JSON file will be created or overwritten.
     * * @return StatusCode (or int): 
     * - OPERATION_DONE: File saved successfully.
     * - WRONG_INPUT_FORMAT: Returned if a string in 'data' does not contain a space.
     * - FAILED_WRITING: Returned if LittleFS fails to open the file for writing.
     * * @note This function overwrites any existing file at the given path ("w" mode).
     */
    static fs_status saveFS_json(vector<String> data, const char* path);

    /**
     * @brief Loads specific values from a JSON file stored in LittleFS.
     * * This function opens a JSON file at the specified path, parses its content, 
     * and extracts values corresponding to the keys provided in the 'data' vector.
     * * @param data A vector of Strings representing the JSON keys to be retrieved.
     * @param path A constant char pointer representing the file system path to the JSON file.
     * * @return std::vector<String> A vector containing the retrieved values as Strings. 
     * Returns an empty vector {} if:
     * - The file path does not exist.
     * - The file cannot be opened for reading.
     * - The JSON deserialization fails.
     */
    static vector<String>  loadFS_json(vector<String> data, const char* path);

    static fs_status new_file(JsonDocument new_file_data, const char* path);

};



#endif