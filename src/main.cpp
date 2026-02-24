//  ****************************************************************************************************
///	\copyright  Agent Smith, Dresden Germany
///             www.agent-smith.dev
///
///  Initial code by ChatGPT, 2026
///
//  ****************************************************************************************************

#include "PackageMapFile.h"
#include "PosFile.h"
#include "PosLine.h"

#include <iostream>
#include <string>

//  ----------------------------------------------------------------------------------------------------
/// \brief  print commandline usage information
///
/// \author ChatGPT
///	\date	02/24/2026  ChatGPT Extended help text with parameter details
///	\date	02/18/2026  ChatGPT Start
///
///	\param	pszExeName	name of executable
///	\return	none
//  ----------------------------------------------------------------------------------------------------
static void PrintUsage(const char* pszExeName)
{
    std::cout << "Usage:\n";
    std::cout << "  " << pszExeName << " <KiCAD.pos> <FLX.pos> [KiCADPackage2FLX.txt]\n";
    std::cout << "\n";
    std::cout << "Parameters:\n";
    std::cout << "  <KiCAD.pos>              Input .pos file exported from KiCAD.\n";
    std::cout << "                           Contains one component per line; comment lines start with '#'.\n";
    std::cout << "  <FLX.pos>                Output .pos file for the Essemtec FLX machine.\n";
    std::cout << "                           Package values are mapped/truncated via the mapping file.\n";
    std::cout << "  [KiCADPackage2FLX.txt]   Optional package mapping file.\n";
    std::cout << "                           If omitted, default is: KiCADPackage2FLX.txt\n";
    std::cout << "\n";
    std::cout << "Behavior:\n";
    std::cout << "  - Unknown packages are kept unchanged.\n";
    std::cout << "  - A warning is printed if an unknown package exceeds 32 characters.\n";
    std::cout << "  - Conversion continues; program does not abort on unknown packages.\n";
    return;
}

//  ----------------------------------------------------------------------------------------------------
/// \brief  application entry point
///
/// \author ChatGPT
///	\date	02/18/2026  ChatGPT Start
///
///	\param	argc	argument count
///	\param	argv	argument vector
///	\return	0 ok, !0 nok
//  ----------------------------------------------------------------------------------------------------
int main(int argc, char** argv)
{
    int iRet{1};

    bool bOk{true};

    if ((argc != 3) && (argc != 4))
    {
        PrintUsage(argv[0]);
        bOk = false;
    }

    std::string szKiCadPosFilename;
    std::string szFlxPosFilename;
    std::string szMapFilename;

    if (bOk)
    {
        szKiCadPosFilename = argv[1];
        szFlxPosFilename = argv[2];
        szMapFilename = (argc == 4) ? argv[3] : "KiCADPackage2FLX.txt";
    }

    clPosFile KiCadPosFile;
    clPackageMapFile PackageMapFile;

    if (bOk)
    {
        if (!KiCadPosFile.bLoadFromFile(szKiCadPosFilename))
        {
            std::cout << "ERROR: Cannot read input pos file: " << szKiCadPosFilename << "\n";
            bOk = false;
        }
    }

    if (bOk)
    {
        if (!PackageMapFile.bLoadFromFile(szMapFilename))
        {
            std::cout << "ERROR: Cannot read mapping file: " << szMapFilename << "\n";
            bOk = false;
        }
    }

    if (bOk)
    {
        int iWarnUnknownTooLong{0};

        int iLineNo{0};

        // Structural programming: no dynamic_cast and no continue.
        // Each line knows how to apply mapping (component lines will do the work).
        for (auto& rupLine : KiCadPosFile.rvecupGetLines())
        {
            iLineNo++;
            rupLine->ApplyPackageMapping(PackageMapFile, iLineNo, iWarnUnknownTooLong, std::cout);
        }

        if (!KiCadPosFile.bSaveToFile(szFlxPosFilename))
        {
            std::cout << "ERROR: Cannot write output pos file: " << szFlxPosFilename << "\n";
            bOk = false;
        }
        else
        {
            std::cout << "Done. Wrote: " << szFlxPosFilename << "\n";
            if (iWarnUnknownTooLong > 0)
            {
                std::cout << "Warnings (unknown package > 32 chars): " << iWarnUnknownTooLong << "\n";
            }
        }
    }

    iRet = bOk ? 0 : 1;
    return iRet;
}
