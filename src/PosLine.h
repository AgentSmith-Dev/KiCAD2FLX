#pragma once

#include <string>
#include <vector>

//  ****************************************************************************************************
///  @brief   base class for a line in a .pos file
//  ****************************************************************************************************
class clPosLine
{
public:
    clPosLine() = default;
    virtual ~clPosLine() = default;

    virtual bool bIsComment() const = 0;
    virtual std::string szToString() const = 0;

    clPosLine(const clPosLine&) = delete;
    clPosLine& operator=(const clPosLine&) = delete;

    clPosLine(clPosLine&&) = default;
    clPosLine& operator=(clPosLine&&) = default;
};

//  ****************************************************************************************************
///  @brief   represents a comment/header line in a .pos file (kept unchanged)
//  ****************************************************************************************************
class clPosCommentLine : public clPosLine
{
public:
    explicit clPosCommentLine(const std::string& rszLine);
    ~clPosCommentLine() override = default;

    bool bIsComment() const override;
    std::string szToString() const override;

private:
    std::string m_szLine;
};

//  ****************************************************************************************************
///  @brief   represents a component line in a .pos file
///           tokens: Ref, Val, Package, PosX, PosY, Rot, Side (whitespace separated)
//  ****************************************************************************************************
class clPosComponentLine : public clPosLine
{
public:
    explicit clPosComponentLine(const std::string& rszLine);
    ~clPosComponentLine() override = default;

    bool bIsComment() const override;
    std::string szToString() const override;

    const std::string& rszGetPackage() const;
    void vSetPackage(const std::string& rszPackage);

    bool bWasParsedOk() const;
    const std::string& rszGetRawLine() const;

private:
    void vParse(const std::string& rszLine);

    bool m_bParsedOk{false};

    std::string m_szRawLine;

    std::string m_szRef;
    std::string m_szVal;
    std::string m_szPackage;
    std::string m_szPosX;
    std::string m_szPosY;
    std::string m_szRot;
    std::string m_szSide;

    std::vector<std::string> m_vecszExtraTokens;
};
