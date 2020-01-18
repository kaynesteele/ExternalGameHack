#ifndef MYPLAYER_H
#define MYPLAYER_H
#pragma once


#include "HackProcess.h"
#include <math.h>

class PlayerList
{

private:
	DWORD CbaseEntity;
	DWORD CLocalPlayer;
	DWORD GlowObj;
	DWORD clientState;
	int glowIndex;
	int Team;
	int myTeam;
	int local;
	int Health;
	int myHealth;
	int flags;
	float Position[3];
	float eyePos[3];
    float myPosition[3];
    float myEyePosition[3];
    DWORD boneMatrix;
    float coords[3];
    float Distance;
    float myViewAngles[3];
    int enemyInCross;
    bool spotted;
    int spottedBy;
    float punchAng[3];
    float *clampedAngle;
    bool dormant;
    float vecVel[3];



public:
    float *AimbotAngle;
    bool isDormant();
    void setClampAngle(float*);
    float * getClampAngle();
    PlayerList(float[], float[], float[]);
    PlayerList();
    float Get3dDistance(float, float, float,
						float, float, float);
	void ReadInformation(CHackProcess h, int player);
	void ReadMyInformation(CHackProcess h);
	float* getPos();
	float * readViewAngle();
	int getHealth();
	int getTeam();
	int getMyTeam();
	float* getMyPos();
	void setAimAngle(float*);
	float * getAimAngle();
	float * GetBonePos(int);
	float * getMyEyePos();
    bool isSpotted();
	float getDist(float*);
	float * getMyViewAng();
	DWORD getBoneMatrix();
	int getEnemyInCross();
	int getFlags();
    int getSpottedBy();
    bool isLocal();
    void setSpotted(CHackProcess,int);
    DWORD getLocalPlayerPointer();
    void glow();
    void setMyAim(float*);
    float * getPunch();
    float * getVecVel();
    void jump(int);
    void fakeLag();
};

#endif
