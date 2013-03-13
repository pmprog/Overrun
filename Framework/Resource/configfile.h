
#pragma once

#include "../consts.h"

typedef struct ConfigData
{
	std::string* Key;
	bool IsArray;
	std::list<std::string*>* Contents;
} ConfigData;


class ConfigFile
{
	private:
		std::list<ConfigData*> Contents;

		void ParseFile( std::string TextContents );
		bool IsNumber( std::string s );
		std::string* EscapeString( std::string s );

	public:
		ConfigFile();
		ConfigFile( std::string Filename );
		~ConfigFile();
		bool Save( std::string Filename );

		bool IsKeyAnArray( std::string Key );
		int GetArraySize( std::string Key );

		bool GetBooleanValue( std::string Key );
		bool GetBooleanValue( std::string Key, int ArrayIndex );
		int GetIntegerValue( std::string Key );
		int GetIntegerValue( std::string Key, int ArrayIndex );
		float GetFloatValue( std::string Key );
		float GetFloatValue( std::string Key, int ArrayIndex );
		std::string GetStringValue( std::string Key );
		std::string GetStringValue( std::string Key, int ArrayIndex );

};