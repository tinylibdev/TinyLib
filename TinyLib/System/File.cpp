#include "File.h"


namespace tl
{
    /// @brief New file reader, path must be set with tl::File::open().
    File::File()
    {
        this->path = nullptr;
    }


    /// @brief New file reader, preset with a path.
    /// @param path File path to read from.
    File::File(const char* path)
    {
        this->path = path;
    }


    /// @brief Nothing to clean up for now.
    File::~File()
    {

    }


    /// @brief Open a new file path on this file.
    /// @param path File path to read from.
    void File::open(const char* path)
    {
        this->path = path;
    }


    /// @brief Close the file path.
    void File::close()
    {
        this->path = nullptr;
    }


    /// @brief Read char data from this file objects file path.
    /// @param data Data from file will go in here. nullptr if invalid path.
    void File::read(char** data)
    {
        if (this->path == nullptr)
        {
            *data = nullptr;
            return;
        }

        HANDLE file = CreateFileA(this->path, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
        if (file == INVALID_HANDLE_VALUE)
        {
            *data = nullptr;
            return;
        }

        DWORD fileSize = GetFileSize(file, NULL);
        if (fileSize == INVALID_FILE_SIZE)
        {
            CloseHandle(file);
            *data = nullptr;
            return;
        }

        // +1 for null-termination character.
        char* buffer = new char[fileSize + 1];
        DWORD bytesRead;
        if (ReadFile(file, buffer, fileSize, &bytesRead, NULL))
        {
            buffer[bytesRead] = '\0';
            *data = buffer;
        }
        else
        {
            delete[] buffer;
            *data = nullptr;
        }

        CloseHandle(file);
    }


    /*
    void File::write()
    {

    }
    */


    /// @brief Get length of file data.
    /// @return File length.
    size_t File::length()
    {
        if (this->path == nullptr)
            return 0;

        HANDLE file = CreateFileA(this->path, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
        if (file == INVALID_HANDLE_VALUE)
            return 0;

        return GetFileSize(file, NULL);
    }
}
