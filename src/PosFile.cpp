//  ****************************************************************************************************
///	\copyright  Agent Smith, Dresden Germany
///             www.agent-smith.dev
///
///  Initial code by ChatGPT, 2026
///
//  ****************************************************************************************************

#include "PosFile.h"

#include <fstream>

//  ----------------------------------------------------------------------------------------------------
/// \brief  load .pos file from disk
///
/// \author ChatGPT
///	\date	02/18/2026  ChatGPT Start
///
///	\param	rszFilename	filename
///	\return	true ok, false nok
//  ----------------------------------------------------------------------------------------------------
bool clPosFile::bLoadFromFile(const std::string& rszFilename)
{
    bool bRet{false};

    m_vecupLines.clear();

    std::ifstream ifs(rszFilename);
    if (ifs.is_open())
    {
        std::string szLine;
        while (std::getline(ifs, szLine))
        {
            if (!szLine.empty() && (szLine[0] == '#'))
            {
                m_vecupLines.push_back(std::make_unique<clPosCommentLine>(szLine));
            }
            else
            {
                m_vecupLines.push_back(std::make_unique<clPosComponentLine>(szLine));
            }
        }

        bRet = true;
    }

    return bRet;
}

//  ----------------------------------------------------------------------------------------------------
/// \brief  save .pos file to disk
///
/// \author ChatGPT
///	\date	02/18/2026  ChatGPT Start
///
///	\param	rszFilename	filename
///	\return	true ok, false nok
//  ----------------------------------------------------------------------------------------------------
bool clPosFile::bSaveToFile(const std::string& rszFilename) const
{
    bool bRet{false};

    std::ofstream ofs(rszFilename, std::ios::trunc);
    if (ofs.is_open())
    {
        for (const auto& rupLine : m_vecupLines)
        {
            ofs << rupLine->szToString() << "\n";
        }

        bRet = true;
    }

    return bRet;
}

//  ----------------------------------------------------------------------------------------------------
/// \brief  get modifiable list of line objects
///
/// \author ChatGPT
///	\date	02/18/2026  ChatGPT Start
///
///	\param	none
///	\return	reference to lines
//  ----------------------------------------------------------------------------------------------------
std::vector<std::unique_ptr<clPosLine>>& clPosFile::rvecupGetLines()
{
    return m_vecupLines;
}

//  ----------------------------------------------------------------------------------------------------
/// \brief  get read-only list of line objects
///
/// \author ChatGPT
///	\date	02/18/2026  ChatGPT Start
///
///	\param	none
///	\return	const reference to lines
//  ----------------------------------------------------------------------------------------------------
const std::vector<std::unique_ptr<clPosLine>>& clPosFile::rvecupGetLines() const
{
    return m_vecupLines;
}
