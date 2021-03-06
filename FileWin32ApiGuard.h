//
// Created by AAI2002 on 05.12.2021.
//

#ifndef HT3_FileWin32ApiGuard_H
#define HT3_FileWin32ApiGuard_H

#include <fileapi.h>
#include <windows.h>
#include <stdexcept>

namespace my_std {
    class FileWin32ApiGuard final{
        HANDLE hFile;
    public:
        FileWin32ApiGuard() = delete;

        FileWin32ApiGuard(FileWin32ApiGuard &) = delete;

        FileWin32ApiGuard(FileWin32ApiGuard &&other) noexcept : hFile(other.hFile) { other.hFile = nullptr; }

        FileWin32ApiGuard& operator=(FileWin32ApiGuard &) = delete;

        FileWin32ApiGuard& operator=(FileWin32ApiGuard &&other) noexcept {
            hFile = other.hFile;
            other.hFile = nullptr;
        }

        explicit FileWin32ApiGuard(const char * filename,
                  DWORD DwDesiredAccess = GENERIC_READ,
                  DWORD DwShareMode = 0,
                  LPSECURITY_ATTRIBUTES IpSecurityAttributes = NULL,
                  DWORD DwCreationDisposition = OPEN_EXISTING,
                  DWORD DwFlagsAndAttributes = FILE_ATTRIBUTE_NORMAL,
                  HANDLE HTemplateFile = NULL) {

            hFile = CreateFile(filename,
                               DwDesiredAccess,
                               DwShareMode,
                               IpSecurityAttributes,
                               DwCreationDisposition,
                               DwFlagsAndAttributes,
                               HTemplateFile);
            if (hFile == INVALID_HANDLE_VALUE) {
                throw std::runtime_error("error: failed create file (INVALID_HANDLE_VALUE) [FileGuard]. Error code: " +
                                                 std::to_string(GetLastError()));
            }
        }

        operator HANDLE() const { return hFile; }

        ~FileWin32ApiGuard() {
            CloseHandle(hFile);
        }
    };
}

#endif //HT3_FileWin32ApiGuard_H
