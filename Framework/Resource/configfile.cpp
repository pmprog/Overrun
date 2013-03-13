
#include "configfile.h"
#include <ctype.h>

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
	ALLEGRO_FILE* fileHnd;
	std::string document;
	bool dataNum;
	std::string* escstr;

	fileHnd = al_fopen( Filename.c_str(), "w" );
	if( fileHnd == 0 )
		return false;

	document.clear();
	for( std::list<ConfigData*>::iterator i = Contents.begin(); i != Contents.end(); i++ )
	{
		ConfigData* cd = (ConfigData*)(*i);
		document.append( cd->Key->c_str() );
		if( cd->IsArray )
		{
			document.append( " [ " );

			bool isFirst = true;
			for( std::list<std::string*>::iterator s = cd->Contents->begin(); s != cd->Contents->end(); s++ )
			{
				if( isFirst )
					isFirst = false;
				else
					document.append( ", " );

				std::string* cs = (std::string*)(*s);
				dataNum = IsNumber( *cs );
				if( !dataNum )
				{
					document.append( "\"" );
					escstr = EscapeString(*cs);
					document.append( escstr->c_str() );
					delete escstr;
					document.append( "\"" );
				} else {
					document.append( cs->c_str() );
				}
			}

			document.append( " ]\n" );
		} else {
			document.append( " = " );
			dataNum = IsNumber( *cd->Contents->front() );
			if( !dataNum )
			{
				document.append( "\"" );
				escstr = EscapeString(*cd->Contents->front());
				document.append( escstr->c_str() );
				delete escstr;
				document.append( "\"" );
			} else {
				document.append( cd->Contents->front()->c_str() );
			}
			document.append( "\n" );
		}

	}

	al_fputs( fileHnd, document.c_str() );
	al_fclose( fileHnd );
	
	return true;
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
	cd->IsArray = false;

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
			case ',':
			case '\n':
			case '\r':
			// case ']':
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
							if( token != "]" )
								cd->Contents->push_back( new std::string(token) );
							break;
					}
					if( (!cd->IsArray && (TextContents.at( charPos ) == '\n' || TextContents.at( charPos ) == '\r')) || token == "]" )
					{
						Contents.push_back( cd );
						cd = (ConfigData*)malloc( sizeof( ConfigData ) );
						cd->Contents = new std::list<std::string*>();
						cd->IsArray = false;
						TokenStep = 0;
					}
					token.clear();
					wasQuoted = false;
				}
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

bool ConfigFile::IsNumber(std::string s)
{
	if( s.empty() )
		return false;
	for( std::string::iterator i = s.begin(); i != s.end(); i++ )
	{
		if( !isdigit(*i) && (*i) != '.' && (*i) != '+' && (*i) != '-' )
			return false;
	}
	return true;
}

std::string* ConfigFile::EscapeString( std::string s )
{
	std::string* out = new std::string();
	if( !s.empty() )
	{
		for( int i = 0; i < s.size(); i++ )
		{
			if( s.at(i) == '\\' || s.at(i) == '\"' )
				out->append( "\\" );
			out->append( s.substr( i, 1 ) );
		}
	}
	return out;
}
