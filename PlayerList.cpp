#include "PlayerList.h"
#include <iostream>
#include "offsets.h"
        PlayerList::PlayerList()
        {

        }

        PlayerList::PlayerList(float aimbotAngle[], float myCoords[], float enemyCoords[])
        {

		Distance = Get3dDistance(myCoords[0], myCoords[1], myCoords[2],
				enemyCoords[0], enemyCoords[1], enemyCoords[2]);

		AimbotAngle[0] = aimbotAngle[0];
		AimbotAngle[1] = aimbotAngle[1];
		AimbotAngle[2] = aimbotAngle[2];

        }


	float PlayerList::Get3dDistance(float myCoordsX, float myCoordsZ, float myCoordsY,
						float enX, float enZ, float enY)
	{

		return sqrt(pow(double(enX - myCoordsX), 2.0) +
					pow(double(enY - myCoordsY), 2.0) +
				    pow(double(enZ - myCoordsZ), 2.0));

	}
void PlayerList::ReadInformation(CHackProcess h, int player)
	{
		ReadProcessMemory(h.__HandleProcess, (PBYTE*)(h.__dwordClient + dwEntityList + (player * 0x10)), &CbaseEntity, sizeof(DWORD), 0);
		ReadProcessMemory(h.__HandleProcess, (PBYTE*)(CbaseEntity + m_iTeamNum), &Team, sizeof(Team), 0);
		ReadProcessMemory(h.__HandleProcess, (PBYTE*)(CbaseEntity + m_iHealth), &Health, sizeof(int), 0);
		ReadProcessMemory(h.__HandleProcess, (PBYTE*)(CbaseEntity + m_vecOrigin), &Position, sizeof(float[3]), 0);
        ReadProcessMemory(h.__HandleProcess, (PBYTE*)(CbaseEntity + m_vecViewOffset), &eyePos, sizeof(float[3]), 0);
        ReadProcessMemory(h.__HandleProcess, (PBYTE*)(CbaseEntity + m_dwBoneMatrix), &boneMatrix, sizeof(float[3]), 0);
        ReadProcessMemory(h.__HandleProcess, (PBYTE*)(CbaseEntity + m_bSpotted), &spotted, sizeof(bool), 0);
        ReadProcessMemory(h.__HandleProcess, (PBYTE*)(CbaseEntity + m_bSpottedByMask), &spottedBy, sizeof(int), 0);
        ReadProcessMemory(h.__HandleProcess, (PBYTE*)(CbaseEntity + m_bDormant), &dormant, sizeof(bool), 0);
        ReadProcessMemory(h.__HandleProcess, (PBYTE*)(CbaseEntity + m_vecVelocity), &vecVel, sizeof(float[3]), 0);
        ReadProcessMemory(h.__HandleProcess, (PBYTE*)(CbaseEntity + dwGlowObjectManager), &GlowObj, sizeof(float[3]), 0);
        ReadProcessMemory(h.__HandleProcess, (PBYTE*)(CbaseEntity + m_iGlowIndex), &glowIndex, sizeof(float[3]), 0);



	}

	void PlayerList::ReadMyInformation(CHackProcess h)
{
    ReadProcessMemory(h.__HandleProcess, (PBYTE*)(h.__dwordClient + dwLocalPlayer), &CLocalPlayer, sizeof(DWORD), 0);
    ReadProcessMemory(h.__HandleProcess, (PBYTE*)(CLocalPlayer + m_iTeamNum), &myTeam, sizeof(int), 0);
   // std::cout << myTeam << std::endl << std::endl;
    ReadProcessMemory(h.__HandleProcess, (PBYTE*)(CLocalPlayer + m_iHealth), &myHealth, sizeof(int), 0);
    ReadProcessMemory(h.__HandleProcess, (PBYTE*)(CLocalPlayer + m_vecOrigin), &myPosition, sizeof(float[3]), 0);
    ReadProcessMemory(h.__HandleProcess, (PBYTE*)(CLocalPlayer + m_fFlags), &flags, sizeof(int), 0);
    memcpy(coords, myPosition, sizeof(float[3]));
    ReadProcessMemory(h.__HandleProcess, (PBYTE*)(CLocalPlayer + m_vecViewOffset), &myEyePosition, sizeof(float[3]), 0);
    ReadProcessMemory(h.__HandleProcess, (PBYTE*)(h.__dwordEngine + dwClientState), &clientState, sizeof(float[3]), 0);
    ReadProcessMemory(h.__HandleProcess, (PBYTE*)(clientState + dwClientState_ViewAngles), &myViewAngles, sizeof(float[3]), 0);
    ReadProcessMemory(h.__HandleProcess, (PBYTE*)(CLocalPlayer + m_iCrosshairId), &enemyInCross, sizeof(int), 0);
    ReadProcessMemory(h.__HandleProcess, (PBYTE*)(CLocalPlayer + m_viewPunchAngle), &punchAng, sizeof(float[3]), 0);


}
float * PlayerList::getVecVel()
{
    return vecVel;
}
bool PlayerList::isDormant()
{
    return dormant;
}
void PlayerList::setClampAngle(float * x)
{
    clampedAngle = x;
}
float * PlayerList::getClampAngle()
{
    return clampedAngle;
}


int PlayerList::getHealth()
{
    return Health;
}

int PlayerList::getSpottedBy()
{
    return spottedBy;
}

int PlayerList::getTeam()
{
    return Team;
}
int PlayerList::getMyTeam()
{
    return myTeam;
}
float *PlayerList::getPos()
{
    return Position;
}
float *PlayerList::getMyPos()
{
    return myPosition;
}
void PlayerList::setAimAngle(float * x)
{
    AimbotAngle=x;

}
float * PlayerList::getAimAngle()
{
    return AimbotAngle;
}
float * PlayerList::GetBonePos(int boneID)
	{
		float* bonePos = new float[3];
    ReadProcessMemory(fProcess.__HandleProcess, (PBYTE*)(boneMatrix + 0x30 * boneID + 0xC), &bonePos[0], sizeof(float), 0);
    ReadProcessMemory(fProcess.__HandleProcess, (PBYTE*)(boneMatrix + 0x30 * boneID + 0x1C), &bonePos[1], sizeof(float), 0);
    ReadProcessMemory(fProcess.__HandleProcess, (PBYTE*)(boneMatrix + 0x30 * boneID+ 0x2C), &bonePos[2], sizeof(float), 0);

		return bonePos;
	}
DWORD PlayerList::getBoneMatrix()
{
    return boneMatrix;
}
float * PlayerList::getMyEyePos()
{
    float * test = new float[3];
    for(int i =0; i < 3; i++)
    {
        test[i] = myPosition[i] + myEyePosition[i];
    }
    return test;
}
float PlayerList::getDist(float* myPos)
{
    return Get3dDistance(myPos[0],myPos[1],myPos[2],Position[0],Position[1],Position[2]);

}

int PlayerList::getFlags()
{
    return flags;
}

float* PlayerList::getMyViewAng()
{
    return myViewAngles;
}
float* PlayerList::readViewAngle()
{
    ReadProcessMemory(fProcess.__HandleProcess, (PBYTE*)(clientState + dwClientState_ViewAngles), &myViewAngles, sizeof(float[3]), 0);
    return myViewAngles;

}
bool PlayerList::isSpotted()
{
    return spotted;
}
int PlayerList::getEnemyInCross()
{
    return enemyInCross;
}
bool PlayerList::isLocal()
{
    return local;
}
DWORD PlayerList::getLocalPlayerPointer()
{
    return CbaseEntity;
}

void PlayerList::setMyAim( float * aimAngle)
{

    WriteProcessMemory(fProcess.__HandleProcess,
                    (PBYTE*)(clientState+dwClientState_ViewAngles),
                    aimAngle, sizeof(float[3]), 0);

}
float* PlayerList::getPunch()
{
    return punchAng;
}
void PlayerList::jump(int jump)
{
    WriteProcessMemory(fProcess.__HandleProcess,
                        (PBYTE*)(fProcess.__dwordClient+dwForceJump),
                        &jump, sizeof(int), 0);
}

void PlayerList::glow()
{
    WriteProcessMemory(fProcess.__HandleProcess, (PBYTE*)(GlowObj+((glowIndex * 0x38) + 0x4)), (PBYTE*)2, sizeof(float), 0);
    WriteProcessMemory(fProcess.__HandleProcess, (PBYTE*)(GlowObj+((glowIndex * 0x38) + 0x8)), (PBYTE*)2, sizeof(float), 0);
    WriteProcessMemory(fProcess.__HandleProcess, (PBYTE*)(GlowObj+((glowIndex * 0x38) + 0xC)), (PBYTE*)2, sizeof(float), 0);
    WriteProcessMemory(fProcess.__HandleProcess, (PBYTE*)(GlowObj+((glowIndex * 0x38) + 0x10)), (PBYTE*)100, sizeof(float), 0);
    WriteProcessMemory(fProcess.__HandleProcess, (PBYTE*)(GlowObj+((glowIndex * 0x38) + 0x24)), (PBYTE*)true, sizeof(bool), 0);
    WriteProcessMemory(fProcess.__HandleProcess, (PBYTE*)(GlowObj+((glowIndex * 0x38) + 0x25)), (PBYTE*)false, sizeof(bool), 0);

}
