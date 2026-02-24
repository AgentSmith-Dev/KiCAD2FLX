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
///	\date	02/18/2026  ChatGPT Start
///
///	\param	pszExeName	name of executable
///	\return	none
//  ----------------------------------------------------------------------------------------------------
static void vPrintUsage(const char* pszExeName)
{
    std::cout << "Usage: " << pszExeName << " <KiCAD.pos> <FLX.pos> [KiCADPackage2FLX.txt]\n";
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
        vPrintUsage(argv[0]);
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
        for (auto& rupLine : KiCadPosFile.rvecupGetLines())
        {
            iLineNo++;

            if (!rupLine->bIsComment())
            {
                auto* pclComp = dynamic_cast<clPosComponentLine*>(rupLine.get());
                if (pclComp != nullptr)
                {
                    if (pclComp->bWasParsedOk())
                    {
                        const std::string& rszPkg = pclComp->rszGetPackage();

                        std::string szFlxPkg;
                        if (PackageMapFile.bTryGetFlxPackage(rszPkg, &szFlxPkg))
                        {
                            pclComp->vSetPackage(szFlxPkg);

                            if (szFlxPkg.size() > 32)
                            {
                                std::cout << "WARNING: FLX package still > 32 chars (line " << iLineNo
                                          << "): " << szFlxPkg << "\n";
                            }
                        }
                        else
                        {
                            if (rszPkg.size() > 32)
                            {
                                std::cout << "WARNING: Unknown KiCad package > 32 chars (kept as-is, line "
                                          << iLineNo << "): " << rszPkg << "\n";
                                iWarnUnknownTooLong++;
                            }
                        }
                    }
                    else
                    {
                        std::cout << "WARNING: Could not parse line (kept as-is, line " << iLineNo
                                  << "): " << pclComp->rszGetRawLine() << "\n";
                    }
                }
            }
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
