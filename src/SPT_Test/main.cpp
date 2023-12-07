﻿#include <iostream>

#include "../../lib/GSD/SPT.h"
#include "../../lib/Rut/RxPath.h"
#include "../../lib/Rut/RxFile.h"
#include "../../lib/Rut/RxMem.h"
#include "../../lib/Rut/RxJson.h"
#include "../../lib/Rut/RxBench.h"
#include <format>

int main()
{
	//Rut::RxMem::Auto spt{ L"data_dec/0scene_pro003_h.spt" };
	//GSD::SPT::Parser parser;
	//parser.Parse(spt.GetPtr());
	try
	{
		Rut::RxPath::MakeDir(L"spt_json/");
		Rut::RxPath::MakeDir(L"spt_dump/");

		std::vector<std::wstring> file_list;
		Rut::RxPath::CurFileNames(L"spt_dec/", file_list, false);
		for (auto& file_name : file_list)
		{
			std::wcout << L"Parser: " << file_name << L"  ";
			{
				Rut::RxMem::Auto spt{ L"spt_dec/" + file_name };
				GSD::SPT::Parser parser;
				parser.Parse(spt.GetPtr());
				parser.Dump().SaveData(L"spt_dump/" + file_name);
				GSD::SPT::CheckDumpDataMatched(spt.GetPtr(), parser);
				auto json = parser.ToJson(932);
				Rut::RxJson::Parser::Save(json, L"spt_json/" + file_name + L".json", true, true);
			}
			std::wcout << L"OK" << L'\n';
		}
	}
	catch (const std::runtime_error& err)
	{
		std::cerr << err.what() << std::endl;
	}


	//std::vector<std::wstring> file_list;
	//Rut::RxPath::CurFileNames(L"data_dec/", file_list, false);
	//for (auto& file_name : file_list)
	//{
	//	GSD::SPT::Text_Editor editor{ L"data_dec/" + file_name };
	//	editor.Extract(L"data_json/" + file_name + L".json", 932);
	//}
}