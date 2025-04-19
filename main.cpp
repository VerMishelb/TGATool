/**
 * TGATool v1.4.3.1, 19.04.2025
 * A tool for converting CIU TGA files to readable format and back.
 * Copyright © 2020-2025 VerMishelb <vermishelb535@gmail.com>. All rights reserved.
 * Licensed under the Apache License, Version 2.0. Please refer to the "LICENSE" file or an online copy.
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

void callPause(const std::string& message = "Press Enter to continue...") {
	std::cout << message;
	char c = 0;
	c = getchar();
}

#define TGATool_VER "v1.4.3.1"
#define STR_HAS(name, arg) (name.find(arg) != std::string::npos)
#define ARG_IS(x) (!strcmp(argv[i], x))
#define ARG_ISi(x, i) (!strcmp(argv[i], x))
#define ERRMSG_NOT_ENOUGH_ARGS(x) "Incorrect " x " usage: not enough arguments.\nRun without parameters to see usage examples.\n"

enum FORCE_CONVERSION {
	FORCECONV_AUTO = 0,
	FORCECONV_NORMAL,
	FORCECONV_CIU
};

int gForceConversion = FORCECONV_AUTO;
bool gPause = false;
bool gOmitPrefix = false;
std::string gOutFolder = "no";
std::vector<std::string> files;

void PrintHelp() {
	std::cout << 
		"To use the tool, drag and drop a TGA file on it. It will be converted to either normal or CIU format according to the input file.\n"
		"Bad files will be skipped.\n"
		"Fixed TGA will be named *_f.tga\n"
		"Chicken Invaders TGA will be named *_c.tga\n\n"
		"FLAGS:\n"
		"-f, --force [normal|ciu|auto] - Forcing CIUed, un-CIUed TGAs conversion, or leave it to the program.\n"
		"-k, --keep - TGATool window won't close after finishing the task.\n"
		"--folder [path] - Override the output folder path.\n"
		"--omit-prefix - Don't add _c _f, overwrite the original file.\n"
		"Credits:\n"
		"VerMishelb (Discord: vmlb) - Coding, idea.\n"
		"Francis - Motivation, idea (they didn't know I already planned it lol)\n"
		"Jade - Help with the CIU TGA format.\n"
		"Partially based on https://aluigi.altervista.org/bms/chicken_invaders_tga.bms\n"
		"\n"
	;
}

int ParseArgs(int& argc, char**& argv) {
	if (argc <= 1 || (!strcmp(argv[1], "-h") || !strcmp(argv[1], "--help"))) {
		PrintHelp();
		gPause = true;
		return 1;
	}
	else {
		std::string exe_name_args = "";
		std::string exe_name =
			std::string(argv[0]).substr(std::string(argv[0]).find_last_of("\\/") + 1);
		if (exe_name.find('(') != std::string::npos &&
			exe_name.find(')') > exe_name.find('('))
		{
			exe_name_args = exe_name.substr(exe_name.find('(') + 1, exe_name.rfind(')'));
		}
		else if (argc < 2) {
			PrintHelp();
			return 1;
		}

		if (STR_HAS(exe_name_args, "-f normal"))
			gForceConversion = FORCECONV_NORMAL;
		if (STR_HAS(exe_name_args, "-f ciu"))
			gForceConversion = FORCECONV_CIU;
		if (STR_HAS(exe_name_args, "-k"))
			gPause = !gPause;
		if (STR_HAS(exe_name_args, "--omit-prefix"))
			gOmitPrefix = !gOmitPrefix;

		for (int i = 1; i < argc; ++i) {
			if (ARG_IS("-f") || ARG_IS("--force")) {
				if (i + 1 >= argc) {
					printf_s(ERRMSG_NOT_ENOUGH_ARGS("-p"));
					return 1;
				}
				if (ARG_ISi("normal", i+1)) { gForceConversion = FORCECONV_NORMAL; }
				else if (ARG_ISi("ciu", i+1)) { gForceConversion = FORCECONV_CIU; }
				else if (ARG_ISi("auto", i+1)) { gForceConversion = FORCECONV_AUTO; }
				continue;
			}
			else if (ARG_IS("-k") || ARG_IS("--keep")) {
				gPause = !gPause;
				continue;
			}
			else if (ARG_IS("--folder")) {
				if (i + 1 >= argc) {
					printf_s(ERRMSG_NOT_ENOUGH_ARGS("--folder"));
					return 1;
				}
				gOutFolder = argv[i + 1];
				continue;
			}
			else if (ARG_IS("--omit-prefix")) {
				gOmitPrefix = !gOmitPrefix;
				continue;
			}
			else {
				//if (i + 1 >= argc) { continue; }
				files.push_back(argv[i]);
			}
		}
		return 1;
	}
}


int main(int argc, char* argv[])
{
	std::cout << "TGATool " TGATool_VER " by VerMishelb (" __DATE__ ")\n\n";
	
	std::string name;
	std::string new_name;
	std::fstream tga;
	uint16_t width;
	uint16_t height;
	uint8_t colors;
	uint8_t mode;
	uint32_t size;
	uint32_t type;
	uint32_t errors = 0;
	bool fixed;
	char* buffer;

	if (!ParseArgs(argc, argv)) {
		std::exit(1);
	}

	for (uint32_t i = 0; i < files.size(); i++)
	{
		name = files[i];
		if (name.rfind('.') != std::string::npos && name.rfind('.') > name.rfind('\\'))
			new_name = name.substr(name.rfind('\\') + 1, name.rfind('.') - name.rfind('\\') - 1);
		else
			new_name = name.substr(name.rfind('\\') + 1, name.size() - name.rfind('\\') - 1);

		std::cout << "File " << i + 1 << "\nPath: " << name << '\n';
		tga.open(name, std::ios::in | std::ios::binary);
		if (!tga)
		{
			std::cerr << "[Error] Can't open " << name << ". Skipping...\n\n";
			tga.clear();
			errors++;
			continue;
		}
		tga.read(reinterpret_cast<char*>(&type), sizeof(type));
		if (type == 0x20000 || type == 0x30000)
			fixed = true;
		else if (type == 0xA0000 || type == 0xB0000) {
			std::cerr << "[Error] This file is compressed and can't be read correctly. Resave it without an RLE and try again. Skipping...\n\n";
			tga.clear();
			tga.close();
			continue;
		}
		else
			fixed = false;
		if (fixed == true && ((gForceConversion == FORCECONV_CIU) || (gForceConversion == FORCECONV_AUTO)))
		{
			std::cout << "Type: Regular\n";
			tga.seekg(2);
			tga.read(reinterpret_cast<char*>(&mode), sizeof(mode));
			if (mode == 2)
				std::cout << "Mode: TrueColor image\n";
			else if (mode == 3)
				std::cout << "Mode: Monochrome image\n";
			else
			{
				std::cerr << "[Error] Unknown mode. Skipping...\n\n";
				tga.clear();
				tga.close();
				errors++;
				continue;
			}
			tga.seekg(0xC);
			tga.read(reinterpret_cast<char*>(&width), sizeof(width));
			std::cout << "Width: " << width << '\n';
			tga.read(reinterpret_cast<char*>(&height), sizeof(height));
			std::cout << "Height: " << height << '\n';
			tga.read(reinterpret_cast<char*>(&colors), sizeof(colors));
			std::cout << "Color depth: " << static_cast<unsigned int>(colors) << "\nConverting to Chicken Invaders TGA...\n";

			//Breaking TGA 18
			//tga.seekg(-18, std::ios::end);
			size = width * height * (colors >> 3);//tga.tellg();
			tga.seekg(18);
			buffer = new char[size];
			tga.read(buffer, size);
			tga.close();

			std::string new_path = (gOutFolder == "no") ?
				(name.substr(0, name.find_last_of("\\/") + 1) + new_name + ((gOmitPrefix) ? ".tga" : "_c.tga")) :
				(gOutFolder + '/' + new_name + ((gOmitPrefix) ? ".tga" : "_c.tga"));

			std::cout << "Saving as: " << new_path << "\n";
			tga.open(new_path, std::ios::out | std::ios::binary);
			if (!tga)
			{
				std::cerr << "[Error] Can't create file. Try running the tool as administrator. Skipping...\n\n";
				tga.clear();
				errors++;
				continue;
			}
			tga.write((char*)&width, sizeof(width));
			tga.put(0);
			tga.put(0);
			tga.write((char*)&height, sizeof(height));
			tga.put(0);
			tga.put(0);
			tga.put(colors);
			tga.put(0);
			tga.put(0);
			tga.put(0);
			tga.write(buffer, width*height*(colors>>3));
			tga.close();
			delete[] buffer;
			std::cout << "Converted successfully.\n\n";
		}
		else if (fixed == false && ((gForceConversion == FORCECONV_NORMAL) || (gForceConversion == FORCECONV_AUTO)))
		{
			tga.seekg(0);
			std::cout << "Type: Chicken Invaders TGA\n";
			tga.read(reinterpret_cast<char*>(&width), sizeof(width));
			std::cout << "Width: " << width << '\n';
			tga.seekg(4);
			tga.read(reinterpret_cast<char*>(&height), sizeof(height));
			std::cout << "Height: " << height << '\n';
			tga.seekg(8);
			tga.read(reinterpret_cast<char*>(&colors), sizeof(colors));
			std::cout << "Color depth: " << static_cast<unsigned int>(colors) << "\nConverting to regular TGA...\n";

			//Fixing TGA
			if (colors == 32 || colors == 24)
				mode = 2;//32 24
			else if (colors == 0x8 )
				mode = 3;//mono
			else
			{
				std::cerr << "[Error] Bad color depth. Skipping...\n\n";
				tga.clear();
				tga.close();
				errors++;
				continue;
			}
			tga.seekg(-12, std::ios::end);//12
			size = tga.tellg();
			tga.seekg(12);
			buffer = new char[size];
			tga.read(buffer, size);
			tga.close();

			std::string new_path = (gOutFolder == "no") ? 
				(name.substr(0, name.find_last_of("\\/") + 1) + new_name + ((gOmitPrefix) ? ".tga" : "_f.tga")) :
				(gOutFolder + '/' + new_name + ((gOmitPrefix) ? ".tga" : "_f.tga"));
			std::cout << "Saving as: " << new_path <<"\n";

			tga.open(new_path, std::ios::out | std::ios::binary);
			if (!tga)
			{
				std::cerr << "[Error] Can't create file. Try running the tool as administrator. Skipping...\n\n";
				tga.clear();
				errors++;
				continue;
			}
			tga.put(0);
			tga.put(0);
			tga.write((char*)&mode, sizeof(mode));
			for (int j = 0; j < 9; j++)
				tga.put(0);
			tga.write((char*)&width, sizeof(width));
			tga.write((char*)&height, sizeof(height));
			tga.write((char*)&colors, sizeof(colors));
			if (mode == 2 && colors == 32 || mode == 3)
				tga.put(8);//8 bits of alpha (0b00001000)
			else/* (mode == 3) */
				tga.put(0);
			tga.write(buffer, size);
			tga.close();
			delete[] buffer;
			std::cout << "Converted successfully.\n\n";
		}
	}
	std::cout << "Errors: " << errors << "\nSuccess: " << (uint32_t)files.size() - errors << "\nTotal: " << files.size() << "\n\n";
	if (gPause)
		callPause();
	std::exit(0);
}