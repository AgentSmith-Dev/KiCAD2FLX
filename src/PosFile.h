#pragma once

#include "PosLine.h"

#include <memory>
#include <string>
#include <vector>

//  ****************************************************************************************************
///  @brief   represents a .pos file as a list of line objects
//  ****************************************************************************************************
class clPosFile
{
public:
    clPosFile() = default;
    ~clPosFile() = default;

    bool bLoadFromFile(const std::string& rszFilename);
    bool bSaveToFile(const std::string& rszFilename) const;

    std::vector<std::unique_ptr<clPosLine>>& rvecupGetLines();
    const std::vector<std::unique_ptr<clPosLine>>& rvecupGetLines() const;

private:
    std::vector<std::unique_ptr<clPosLine>> m_vecupLines;
};
