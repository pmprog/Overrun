
#include "wave.h"
#include "../Units/spinner.h"

Wave::Wave( ConfigFile* WaveData )
{
	int tmpI;
	float tmpF;

	WaveData->GetStringValue( "UnitClass", &UnitClass );
	WaveData->GetIntegerValue( "WaveDelay", &WaveDelay );
	WaveData->GetIntegerValue( "UnitCount", &UnitCount );
	WaveData->GetFloatValue( "SpawnDelay", &SpawnDelay );

	UnitSpec = new ConfigFile();

	WaveData->GetIntegerValue( "Health", &tmpI );
	UnitSpec->SetIntegerValue( "Health", tmpI );
	WaveData->GetIntegerValue( "DamageToBase", &tmpI );
	UnitSpec->SetIntegerValue( "DamageToBase", tmpI );
	WaveData->GetIntegerValue( "Reward", &tmpI );
	UnitSpec->SetIntegerValue( "Reward", tmpI );

	WaveData->GetIntegerValue( "Shields", &tmpI );
	UnitSpec->SetIntegerValue( "Shields", tmpI );
	WaveData->GetFloatValue( "ShieldRegenRate", &tmpF );
	UnitSpec->SetFloatValue( "ShieldRegenRate", tmpF );

	WaveData->GetFloatValue( "Acceleration", &tmpF );
	UnitSpec->SetFloatValue( "Acceleration", tmpF );
	WaveData->GetFloatValue( "Deceleration", &tmpF );
	UnitSpec->SetFloatValue( "Deceleration", tmpF );
	WaveData->GetFloatValue( "MaxNormalSpeed", &tmpF );
	UnitSpec->SetFloatValue( "MaxNormalSpeed", tmpF );
	WaveData->GetFloatValue( "MaxSlowSpeed", &tmpF );
	UnitSpec->SetFloatValue( "MaxSlowSpeed", tmpF );
}

Wave::~Wave()
{
	delete UnitSpec;
}

Unit* Wave::SpawnUnit( Path* FollowPath )
{
	if( UnitClass == "Spinner" )
		return new Spinner( UnitSpec, FollowPath );


	return new Spinner( UnitSpec, FollowPath );
}
