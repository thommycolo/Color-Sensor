
#ifndef LITTLEFSHANDLER_H
#define LITTLEFSHANDLER_H



#pragma once

/**
 * @class LittleFS_Handler
 * @brief Static class providing tools for common LittleFS operations.
 * This class simplifies file hierarchy visualization and manages JSON data 
 * persistence for ESP8266/ESP32 microcontrollers.
 */
class LittleFSHandler {
public:
    /**
     * @enum fs_status
     * @brief Result codes for file system operations.
     */
    typedef enum {
        OPERATION_DONE,         ///< Operation completed successfully.
        FS_NOT_FOUND,           ///< LittleFS system or root path not found.
        CANNOT_OPEN_DIRECTORY,  ///< Target exists but is not a directory.
        WRONG_INPUT_FORMAT,     ///< Input string missing the ' ' (space) delimiter.
        FAILED_WRITING,         ///< Error during file opening or writing.
        FAILED_READING          ///< Error during file opening or reading.
    } fs_status;

    /**
     * @brief Initializes the LittleFS file system.
     * @note If mounting fails, the system will attempt to format the storage automatically.
     */
    static void begin(); 

    /**
     * @brief Recursively prints the file system structure to the Serial Monitor.
     * Traverses the directory tree, visualizing the hierarchy via indentation 
     * and differentiating between files and folders.
     * @param dirname Starting path (e.g., "/" for root).
     * @param depth   Maximum recursion depth to prevent stack overflow.
     * @return fs_status Returns OPERATION_DONE on success, or an error code.
     * @note Directories are marked with [DIR], files with [FILE] and their size.
     */
    static fs_status printFS(const char * dirname, uint8_t levels, int indent);

    /**
     * @brief Converts a list of formatted strings into a JSON file.
     * Splits each string in the vector at the first space character to create 
     * Key-Value pairs, then saves them into a .json file.
     * @param data Vector of strings in "Key Value" format.
     * @param path File system path where the JSON file will be saved.
     * @return fs_status 
     * - OPERATION_DONE: Save successful.
     * - WRONG_INPUT_FORMAT: A string in 'data' does not contain a space.
     * - FAILED_WRITING: Could not open the file for writing.
     * @warning This function overwrites existing files (mode "w").
     */
    fs_status saveFS_json(JsonDocument& nuoviDati, const char* path);

    /**
     * @brief Loads specific values from a saved JSON file.
     * Opens the JSON file at the specified path and retrieves values associated 
     * with the keys provided in the 'data' vector.
     * @param data Vector of JSON keys to retrieve.
     * @param path File system path of the JSON file to read.
     * @return std::vector<String> A vector containing the retrieved values. 
     * Returns an empty vector if the file is missing, unreadable, or the JSON is invalid.
     */
    static std::vector<String> loadFS_json(std::vector<String> data, const char* path);

    /**
     * @brief Creates a new file from an existing JsonDocument object.
     * @param new_file_data JsonDocument object containing the data to write.
     * @param path Destination path in the file system.
     * @return fs_status OPERATION_DONE if saved correctly, FAILED_WRITING otherwise.
     */
    static fs_status new_file(JsonDocument new_file_data, const char* path);

};

#endif