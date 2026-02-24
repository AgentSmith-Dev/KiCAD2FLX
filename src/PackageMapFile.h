#pragma once

#include <string>
#include <unordered_map>

//  ****************************************************************************************************
///  @brief   reads KiCADPackage2FLX.txt and provides a lookup from KiCad package to FLX package
//  ****************************************************************************************************
class clPackageMapFile
{
public:
    clPackageMapFile() = default;
    ~clPackageMapFile() = default;

    bool bLoadFromFile(const std::string& rszFilename);
    bool bTryGetFlxPackage(const std::string& rszKiCadPackage, std::string* pszOutFlxPackage) const;

private:
    std::unordered_map<std::string, std::string> m_umapszKiCadToFlx;
};
