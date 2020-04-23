/* =========================================================================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

#pragma once

namespace BinaryData
{
    extern const char*   question2_png;
    const int            question2_pngSize = 16962;

    extern const char*   ButtonOn_png;
    const int            ButtonOn_pngSize = 93263;

    extern const char*   ButtonOff_png;
    const int            ButtonOff_pngSize = 91950;

    extern const char*   drumface_png;
    const int            drumface_pngSize = 71059;

    extern const char*   Ubuntu_L_ttf;
    const int            Ubuntu_L_ttfSize = 415552;

    extern const char*   Reey_Regular_otf;
    const int            Reey_Regular_otfSize = 93076;

    extern const char*   Amagro_bold_ttf;
    const int            Amagro_bold_ttfSize = 54652;

    // Number of elements in the namedResourceList and originalFileNames arrays.
    const int namedResourceListSize = 7;

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
