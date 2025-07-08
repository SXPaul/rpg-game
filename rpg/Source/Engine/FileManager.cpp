#include "FileManager.h"



void FileManager::CreateFolder(std::string folderName)
{
    fs::path folderPath = fs::current_path() / folderName;

    if (fs::create_directory(folderPath)) std::cout << "�ļ��д����ɹ�: " << folderPath << std::endl;
}

bool FileManager::ReadFile(std::string fileName, std::string& line)
{
    std::ifstream inFile;
    
    inFile.open(fileName);

    if (inFile.is_open()) 
    {
        while (getline(inFile, line)) 
        {
            std::cout << line << std::endl;
        }
        inFile.close();
        return true;
    }
    else 
    {
        std::cerr << "�޷����ļ����ж�ȡ��" << std::endl;
        return false;
    }
}

bool FileManager::WriteFile(std::string fileName, std::string text)
{
    std::ofstream outFile;

    outFile.open(fileName);

    if (outFile.is_open())
    {
        outFile << text;
        outFile.close();
        std::cout << "�ļ��ѳɹ�д�롣" << std::endl;
        return true;
    }
    else 
    {
        std::cerr << "�޷����ļ�����д������" << std::endl;
        return false;
    }
}