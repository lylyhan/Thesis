/* =========================================================================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

#pragma once

namespace BinaryData
{
    extern const char*   stringOn_png;
    const int            stringOn_pngSize = 43217;

    extern const char*   question2_png;
    const int            question2_pngSize = 16962;

    extern const char*   boxOff_png;
    const int            boxOff_pngSize = 50431;

    extern const char*   drumOff_png;
    const int            drumOff_pngSize = 49772;

    extern const char*   stringOff_png;
    const int            stringOff_pngSize = 50781;

    extern const char*   boxOn_png;
    const int            boxOn_pngSize = 42497;

    extern const char*   drumOn_png;
    const int            drumOn_pngSize = 42026;

    extern const char*   ExistenceLight_otf;
    const int            ExistenceLight_otfSize = 39392;

    // Number of elements in the namedResourceList and originalFileNames arrays.
    const int namedResourceListSize = 8;

    // Points to the start of a list of resource names.
    extern const char* namedResourceList[];

    // Points to the start of a list of resource filenames.
    extern const char* originalFilenames[];

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding data and its size (or a null pointer if the name isn't found).
    const char* getNamedResource (const char* resourceNameUTF8, int& dataSizeInBytes);

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding original, non-mangled filename (or a null pointer if the name isn't found).
    const char* getNamedResourceOriginalFilename (const char* resourceNameUTF8);
}
