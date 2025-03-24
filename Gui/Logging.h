#pragma once
#include <iostream>
#include <string>

/// Logs info to the console.
/// @param msg The message to display.
inline void logInfo(std::string msg)
{
    std::cout << "[INFO] " << msg << "\n";
}

/// Logs an error to the console.
/// @param msg Message describing what went wrong.
inline void logError(std::string msg)
{
    std::cout << "[ERROR] " << msg << "\n";
}
