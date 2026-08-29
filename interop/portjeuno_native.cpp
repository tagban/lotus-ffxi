// The C ABI PortJeuno's managed client calls into.
//
// Right now this is deliberately one function. Its job is to prove that
// ffxi-lib links and runs from something that is not ffxi.exe - the whole
// reason the game was split out of the add_executable target - and to prove it
// against the real retail DATs rather than against a stub.

#include <cstring>
#include <exception>
#include <filesystem>
#include <string>

import ffxi;

#if defined(_WIN32)
#define PORTJEUNO_API __declspec(dllexport)
#else
#define PORTJEUNO_API __attribute__((visibility("default")))
#endif

extern "C"
{
// Opens the DAT archive at install_path and reports whether it could be read.
// Returns 0 on success, 1 if the DATs could not be opened, 2 on anything else.
// error_out, when given, receives a null-terminated message of at most
// error_size bytes.
PORTJEUNO_API int portjeuno_dat_probe(const char* install_path, char* error_out, int error_size)
{
    auto report = [&](const char* message)
    {
        if (error_out && error_size > 0)
        {
            std::strncpy(error_out, message, static_cast<size_t>(error_size) - 1);
            error_out[error_size - 1] = '\0';
        }
    };

    if (!install_path)
    {
        report("install_path was null");
        return 1;
    }

    try
    {
        FFXI::DatLoader loader{std::filesystem::path{install_path}};
        report("");
        return 0;
    }
    catch (const std::exception& e)
    {
        report(e.what());
        return 1;
    }
    catch (...)
    {
        report("unknown error");
        return 2;
    }
}
}
