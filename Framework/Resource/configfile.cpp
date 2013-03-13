
#include "configfile.h"

ConfigFile::ConfigFile()
{
}

ConfigFile::ConfigFile( std::string Filename )
{
	ALLEGRO_FILE* fileHnd;
	std::string document;
	char buf[1024];

	fileHnd = al_fopen( Filename.c_str(), "r" );
	if( fileHnd != 0 )
	{
		document.clear();
		while( !al_feof( fileHnd ) )
		{
			al_fgets( fileHnd, (char*)&buf, 1024 );
			document.append( (char*)&buf );
		}
		ParseFile( document );
		al_fclose( fileHnd );
	}
}

ConfigFile::~ConfigFile()
{
	while( Contents.size() > 0 )
	{
		ConfigData* cd = Contents.back();
		delete cd->Key;
		while( cd->Contents->size() > 0 )
		{
			delete cd->Contents->back();
			cd->Contents->pop_back();
		}
		free( (void*)Contents.back() );
		Contents.pop_back();
	}
}

bool ConfigFile::Save( std::string Filename )
{
	return false;
}

bool ConfigFile::IsKeyAnArray( std::string Key )
{
	return false;
}

int ConfigFile::GetArraySize( std::string Key )
{
	return 0;
}

bool ConfigFile::GetBooleanValue( std::string Key )
{
	return false;
}

bool ConfigFile::GetBooleanValue( std::string Key, int ArrayIndex )
{
	return false;
}

int ConfigFile::GetIntegerValue( std::string Key )
{
	return 0;
}

int ConfigFile::GetIntegerValue( std::string Key, int ArrayIndex )
{
	return 0;
}

float ConfigFile::GetFloatValue( std::string Key )
{
	return 0.0;
}

float ConfigFile::GetFloatValue( std::string Key, int ArrayIndex )
{
	return 0.0;
}

std::string ConfigFile::GetStringValue( std::string Key )
{
	return "";
}

std::string ConfigFile::GetStringValue( std::string Key, int ArrayIndex )
{
	return "";
}

void ConfigFile::ParseFile( std::string TextContents )
{
	ConfigData* cd;
	int charPos = 0;
	std::string token;
	bool charQuoted = false;
	bool wasQuoted = false;
	int TokenStep = 0;

	cd = (ConfigData*)malloc( sizeof( ConfigData ) );
	cd->Contents = new std::list<std::string*>();

	while( charPos < TextContents.size() )
	{
		switch( TextContents.at( charPos ) )
		{
			case '#':
				while( charPos < TextContents.size() && TextContents.at( charPos ) != '\n' && TextContents.at( charPos ) != '\r' )
					charPos++;
				break;

			case ' ':
			case '\t':
			case '\r':
			case '\n':
			case ',':
			case ']':
				if( charQuoted )
				{
					token.append( TextContents.substr( charPos, 1 ) );
				} else if( token.size() > 0 || wasQuoted ) {
					switch( TokenStep )
					{
						case 0:
							cd->Key = new std::string( token );
							TokenStep++;
							break;
						case 1:
							if( token == "[" )
								cd->IsArray = true;
							else
								cd->IsArray = false;
							TokenStep++;
							break;
						case 2:
							cd->Contents->push_back( new std::string(token) );
							break;
					}
					token.clear();
					wasQuoted = false;

				}
				break;

			case ';':
				if( token.size() > 0 || wasQuoted )
					cd->Contents->push_back( new std::string(token) );
				Contents.push_back( cd );
				cd = (ConfigData*)malloc( sizeof( ConfigData ) );
				cd->Contents = new std::list<std::string*>();
				wasQuoted = false;
				TokenStep = 0;
				token.clear();
				break;

			case '\\':
				if( charQuoted )
				{
					token.append( TextContents.substr( charPos + 1, 1 ) );
					charPos++;
				}
				break;

			case '"':
				if( TextContents.at( charPos - 1 ) != '\\' )
				{
					charQuoted = !charQuoted;
					wasQuoted = true;
				}
				break;

			default:
				token.append( TextContents.substr( charPos, 1 ) );
				break;
		}
		charPos++;
	}
	free( cd );

}