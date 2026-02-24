//  ****************************************************************************************************
///	\copyright  Agent Smith, Dresden Germany
///             www.agent-smith.dev
///
///  Initial code by ChatGPT, 2026
///
//  ****************************************************************************************************

#include "PosLine.h"

#include <sstream>

//  ----------------------------------------------------------------------------------------------------
/// \brief  create a comment line
///
/// \author ChatGPT
///	\date	02/18/2026  ChatGPT Start
///
///	\param	rszLine	line text
///	\return	none
//  ----------------------------------------------------------------------------------------------------
clPosCommentLine::clPosCommentLine(const std::string& rszLine)
    : m_szLine(rszLine)
{
    return;
}

//  ----------------------------------------------------------------------------------------------------
/// \brief  returns true if the line is a comment line
///
/// \author ChatGPT
///	\date	02/18/2026  ChatGPT Start
///
///	\param	none
///	\return	true if comment
//  ----------------------------------------------------------------------------------------------------
bool clPosCommentLine::bIsComment() const
{
    bool bRet{true};
    return bRet;
}

//  ----------------------------------------------------------------------------------------------------
/// \brief  converts the line back to text
///
/// \author ChatGPT
///	\date	02/18/2026  ChatGPT Start
///
///	\param	none
///	\return	line text
//  ----------------------------------------------------------------------------------------------------
std::string clPosCommentLine::szToString() const
{
    std::string szRet{m_szLine};
    return szRet;
}

//  ----------------------------------------------------------------------------------------------------
/// \brief  create a component line and parse it
///
/// \author ChatGPT
///	\date	02/18/2026  ChatGPT Start
///
///	\param	rszLine	line text
///	\return	none
//  ----------------------------------------------------------------------------------------------------
clPosComponentLine::clPosComponentLine(const std::string& rszLine)
{
    vParse(rszLine);
    return;
}

//  ----------------------------------------------------------------------------------------------------
/// \brief  returns true if the line is a comment line
///
/// \author ChatGPT
///	\date	02/18/2026  ChatGPT Start
///
///	\param	none
///	\return	true if comment
//  ----------------------------------------------------------------------------------------------------
bool clPosComponentLine::bIsComment() const
{
    bool bRet{false};
    return bRet;
}

//  ----------------------------------------------------------------------------------------------------
/// \brief  parse a component line into tokens
///
/// \author ChatGPT
///	\date	02/18/2026  ChatGPT Start
///
///	\param	rszLine	line text
///	\return	none
//  ----------------------------------------------------------------------------------------------------
void clPosComponentLine::vParse(const std::string& rszLine)
{
    m_szRawLine = rszLine;
    m_vecszExtraTokens.clear();

    std::istringstream iss(rszLine);

    iss >> m_szRef >> m_szVal >> m_szPackage >> m_szPosX >> m_szPosY >> m_szRot >> m_szSide;

    if (!iss.fail())
    {
        std::string szTok;
        while (iss >> szTok)
        {
            m_vecszExtraTokens.push_back(szTok);
        }

        m_bParsedOk = true;
    }
    else
    {
        m_bParsedOk = false;
    }

    return;
}

//  ----------------------------------------------------------------------------------------------------
/// \brief  returns whether parsing succeeded
///
/// \author ChatGPT
///	\date	02/18/2026  ChatGPT Start
///
///	\param	none
///	\return	true if ok
//  ----------------------------------------------------------------------------------------------------
bool clPosComponentLine::bWasParsedOk() const
{
    bool bRet{m_bParsedOk};
    return bRet;
}

//  ----------------------------------------------------------------------------------------------------
/// \brief  returns the original unmodified line text
///
/// \author ChatGPT
///	\date	02/18/2026  ChatGPT Start
///
///	\param	none
///	\return	raw line text
//  ----------------------------------------------------------------------------------------------------
const std::string& clPosComponentLine::rszGetRawLine() const
{
    const std::string& rszRet{m_szRawLine};
    return rszRet;
}

//  ----------------------------------------------------------------------------------------------------
/// \brief  returns the package token
///
/// \author ChatGPT
///	\date	02/18/2026  ChatGPT Start
///
///	\param	none
///	\return	package string
//  ----------------------------------------------------------------------------------------------------
const std::string& clPosComponentLine::rszGetPackage() const
{
    const std::string& rszRet{m_szPackage};
    return rszRet;
}

//  ----------------------------------------------------------------------------------------------------
/// \brief  set the package token
///
/// \author ChatGPT
///	\date	02/18/2026  ChatGPT Start
///
///	\param	rszPackage	new package
///	\return	none
//  ----------------------------------------------------------------------------------------------------
void clPosComponentLine::vSetPackage(const std::string& rszPackage)
{
    m_szPackage = rszPackage;
    return;
}

//  ----------------------------------------------------------------------------------------------------
/// \brief  converts the line back to text (reconstructed tokens if parsed ok)
///
/// \author ChatGPT
///	\date	02/18/2026  ChatGPT Start
///
///	\param	none
///	\return	line text
//  ----------------------------------------------------------------------------------------------------
std::string clPosComponentLine::szToString() const
{
    std::ostringstream oss;

    if (m_bParsedOk)
    {
        oss << m_szRef << " "
            << m_szVal << " "
            << m_szPackage << " "
            << m_szPosX << " "
            << m_szPosY << " "
            << m_szRot << " "
            << m_szSide;

        for (const auto& rszTok : m_vecszExtraTokens)
        {
            oss << " " << rszTok;
        }
    }
    else
    {
        oss << m_szRawLine;
    }

    std::string szRet{oss.str()};
    return szRet;
}
