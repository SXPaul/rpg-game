/**
 * @file	FileManager.h
 * @brief   �ļ��������ඨ�壬���ڹ�����Ŀ�ļ��ṹ�������ļ��Ĵ��������١���д
 * @author	Arty
 **/

#pragma once
#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>

namespace fs = std::filesystem;



/*----------------------------------
			  �ļ�������
  ----------------------------------*/
class FileManager
{
public:
    static void CreateFolder(std::string folderPath);

	static bool ReadFile(std::string fileName, std::string& line);

	static bool WriteFile(std::string fileName, std::string text);
};