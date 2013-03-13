
#pragma once

#include <list>
#include <string>

class ConfigFile
{
	private:
		

	public:
		ConfigFile();
		ConfigFile( std::string Filename );
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