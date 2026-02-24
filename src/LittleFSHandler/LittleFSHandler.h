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

    static fs_status saveFS_json(const char* path, const char* data);

    static vector<String> loadFS_json(const char* path);
};

#endif