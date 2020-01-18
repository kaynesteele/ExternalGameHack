#include <iostream>
#include "PlayerList.h"
#include <vector>
#include <algorithm>

CHackProcess fProcess;
PlayerList myPerson;

float Get3dDistance(float myCoordsX, float myCoordsZ, float myCoordsY,
                    float enX, float enZ, float enY)
{

    return sqrt(pow(double(enX - myCoordsX), 2.0) +
            pow(double(enY - myCoordsY), 2.0) +
            pow(double(enZ - myCoordsZ), 2.0));

}

float flAngleNormalize(float angle)
{
	while (angle < -180)    angle += 360;
	while (angle > 180)    angle -= 360;
	return angle;
}
float * ClampAngle(float * angles){
	angles[1] = flAngleNormalize(angles[1]);
	angles[0] = flAngleNormalize(angles[0]);
	if (angles[0] > 89.0f)
		angles[0] = 89.0f;
	if (angles[0] < -89.0f)
		angles[0] = -89.0f;

	angles[2] = 0;
	return angles;

}

struct TargetList_t
{
	float Distance;
	float vecVel[3];
	float AimbotAngle[3];

	TargetList_t()
	{
	}

	TargetList_t(float aimbotAngle[], float myCoords[], float enemyCoords[], float vecV[])
	{
		Distance = Get3dDistance(myCoords[0], myCoords[1], myCoords[2],
				aimbotAngle[0], aimbotAngle[1], aimbotAngle[2]);

        vecVel[0] = vecV[0];
        vecVel[1] = vecV[1];
        vecVel[2] = vecV[2];
				//Distance = DifferenceOfAngles(myCoords, aimbotAngle);

		AimbotAngle[0] = aimbotAngle[0];
		AimbotAngle[1] = aimbotAngle[1];
		AimbotAngle[2] = aimbotAngle[2];

	}



};

struct CompareTargetEnArray
{
bool operator () (TargetList_t & lhs, TargetList_t & rhs)
	{

		return lhs.Distance < rhs.Distance;

	}

};

float * subArrs(float* arr1, float *arr2, int x) const
{
    float * finalResult = new float[3];
    for(int i = 0; i < x; i++)
    {
        finalResult[i] = (arr1[i] - arr2[i]);
    }
    return finalResult;
}
float * addArrs(float* arr1, float *arr2, int x, float dist)
{
    float * finalResult = new float[3];
    for(int i = 0; i < x; i++)
    {
        finalResult[i] = (arr1[i] + arr2[i]) / dist;
    }
    return finalResult;
}

float * CalcAngle(float *src, float *dst,float *angles)
{
	double delta[3] = {(src[0]-dst[0]), (src[1]-dst[1]), (src[2]-dst[2])};
	double hyp = sqrt(delta[0]*delta[0] + delta[1]*delta[1]);
	angles[0] = (float) (atan(delta[2]/hyp) * 57.295779513682f);
	angles[1] = (float) (atanf(delta[1]/delta[0]) * 57.295779513682f);
	angles[2] = 0;

	if(delta[0] >= 0.0)
	{
		angles[1] += 180.0f;
	}
	return angles;

}

void bot(PlayerList player)
{
            system("cls");
        PlayerList *pl=new PlayerList[64];
        TargetList_t lowest;
        TargetList_t * TargetList = new TargetList_t[64];
        float * aimAngle = new float[3];
        float * punch = new float[3];
        float * test = new float[3];

        int x=0;
        myPerson.ReadMyInformation(fProcess);
        for(int i =0; i<64; i++)
        {
            pl[i].ReadInformation(fProcess,i);
            //std::cout << pl[i].getTeam() << std::endl;

            punch = myPerson.getPunch();

            //pl[i].glow();

            if(pl[i].getLocalPlayerPointer()!=NULL)
            {
                std::cout << pl[i].getPos()[1] << std::endl;
                if(pl[i].getHealth() > 0 && !pl[i].isDormant() && pl[i].getTeam() != myPerson.getMyTeam());
                {
                   // std::cout << pl[i].getHealth() << std::endl;

                    CalcAngle(player.getMyEyePos(), (pl[i].GetBonePos(8)),aimAngle);
                    ClampAngle(aimAngle);
                    myPerson.setAimAngle(aimAngle);
                    test = addArrs(pl[i].GetBonePos(8), pl[i].getVecVel(),3,Get3dDistance(myPerson.getPos()[0],myPerson.getPos()[1],myPerson.getPos()[2],pl[i].GetBonePos(8)[0],pl[i].GetBonePos(8)[1], pl[i].GetBonePos(8)[2]));
                    ClampAngle(test);
                    TargetList[x] = TargetList_t((aimAngle), player.getMyViewAng(), pl[i].getPos(), pl[i].getVecVel());

                    x++;

                   // targets[x] = PlayerList(aimAngle, player.getMyEyePos(), pl[i].getPos());
                }
            }

        }

        if(x > 0)
        {
            std::sort(TargetList, TargetList+x, CompareTargetEnArray());

            if((TargetList[0].Distance < 2))
            {
                myPerson.setMyAim(subArrs(TargetList[0].AimbotAngle, punch,2));
            }
        }

		x = 0;
//        delete[] targets;
        delete[] aimAngle;
        delete[] punch;
        delete[] test;
        delete[] TargetList;
       // delete[] aimAngle;

}


using namespace std;

int main()
{
    fProcess.RunProcess();
    int jumpVar = 6;
    int noJump = 5;
    bool lag = false;

	while(!GetAsyncKeyState(VK_F4))
    {
        myPerson.ReadMyInformation(fProcess);

        //std::cout << myPerson.getMyTeam() << std::endl;
        //std::cout << myPerson.getEnemyInCross() << std::endl;
        if(GetAsyncKeyState(VK_MENU))
        {
            bot(myPerson);
        }



       if(GetAsyncKeyState(VK_SPACE))
        {
          //  std::cout << myPerson.getFlags() << std::endl;
            if(myPerson.getFlags()==257)
            {
                //std::cout << "Jump" << std::endl;
                myPerson.jump(jumpVar);

            }

        }
        Sleep(1);
    }




    return 0;
}
