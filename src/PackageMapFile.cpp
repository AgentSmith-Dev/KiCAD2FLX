//  ****************************************************************************************************
///	\copyright  Agent Smith, Dresden Germany
///             www.agent-smith.dev
///
///  Initial code by ChatGPT, 2026
///
//  ****************************************************************************************************

#include "PackageMapFile.h"

#include <fstream>
#include <sstream>

//  ----------------------------------------------------------------------------------------------------
/// \brief  load mapping data from file
///
/// \author ChatGPT
///	\date	02/18/2026  ChatGPT Start
///
///	\param	rszFilename	filename
///	\return	true ok, false nok
//  ----------------------------------------------------------------------------------------------------
bool clPackageMapFile::bLoadFromFile(const std::string& rszFilename)
{
    bool bRet{false};

    m_umapszKiCadToFlx.clear();

    std::ifstream ifs(rszFilename);
    if (ifs.is_open())
    {
        std::string szLine;
        while (std::getline(ifs, szLine))
        {
            if (szLine.empty())
            {
                continue;
            }

            if (szLine[0] == '#')
            {
                continue;
            }

            std::istringstream iss(szLine);
            std::string szKiCad;
            std::string szFlx;

            iss >> szKiCad >> szFlx;
            if (!iss.fail() && !szKiCad.empty() && !szFlx.empty())
            {
                m_umapszKiCadToFlx[szKiCad] = szFlx;
            }
        }

        bRet = true;
    }

    return bRet;
}

//  ----------------------------------------------------------------------------------------------------
/// \brief  try to map KiCad package to FLX package
///
/// \author ChatGPT
///	\date	02/18/2026  ChatGPT Start
///
///	\param	rszKiCadPackage		input package
///	\param	pszOutFlxPackage		output package (modified on success)
///	\return	true if found, false if not found / invalid out pointer
//  ----------------------------------------------------------------------------------------------------
bool clPackageMapFile::bTryGetFlxPackage(const std::string& rszKiCadPackage, std::string* pszOutFlxPackage) const
{
    bool bRet{false};

    if (pszOutFlxPackage != nullptr)
    {
        auto it = m_umapszKiCadToFlx.find(rszKiCadPackage);
        if (it != m_umapszKiCadToFlx.end())
        {
            *pszOutFlxPackage = it->second;
            bRet = true;
        }
    }

    return bRet;
}
