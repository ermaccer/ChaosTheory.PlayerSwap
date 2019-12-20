// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"
#include "MemoryMgr.h"
#include <iostream>
using namespace Memory::VP;


struct MySamData
{
	int SamValue1;
	int SamValue2;
};


enum eSamMeshes
{
	SamA,
	SamB,
	SamC,
	SamD,
	Sam_Naked,
};

MySamData* Sam = new MySamData();


int    modelEax = 0;
int    jumpPoint = 0x10CE4839;
char*  hookedName;
int    searchesDone = 0;
bool   searchDone = false;

int         SamMeshPointer;
int         CurrentSamMesh;
const char* NewSamMeshName;


bool KeyHit(unsigned int keyCode)
{
	return (GetKeyState(keyCode) & 0x8000) != 0;
}


void __declspec(naked) HookOne()
{
	_asm {
		mov eax, edx
		add eax, ecx
		mov modelEax, eax
		mov cl, [eax - 1]
		pushad
	}
	hookedName = (char*)(modelEax - 10);
	if (!searchDone && (hookedName[0] == 'E' && hookedName[1] == 'S' && hookedName[2] == 'a' && hookedName[3] == 'm'
		&& hookedName[4] == '.' && hookedName[5] == 'S' && hookedName[6] == 'a' && hookedName[7] == 'm' &&
		(hookedName[8] == 'A' || (hookedName[8] == 'B' && !hookedName[9] == 'a') || hookedName[8] == 'C' || hookedName[8] == 'D' || hookedName[8] == '_')))
	{
		searchesDone++;
		switch (hookedName[8])
		{
		case 'A': CurrentSamMesh = SamA;
			SamMeshPointer = modelEax;
			break;
		case 'B': CurrentSamMesh = SamB;
			SamMeshPointer = modelEax;
			break;
		case 'C': CurrentSamMesh = SamC;
			SamMeshPointer = modelEax;
			break;
		case 'D': CurrentSamMesh = SamD;
			SamMeshPointer = modelEax;
			break;
		case '_': CurrentSamMesh = Sam_Naked;
			SamMeshPointer = modelEax;
			break;
		default:
			break;
		}

		Sam->SamValue1 = *(int*)((modelEax + 2));
		Sam->SamValue2 = *(int*)((modelEax + 2) + 4);

		//if (searchesDone == 2)
		//searchDone = true;
	}
	_asm{
		popad
		jmp jumpPoint
	}
}

void Init()
{
	InjectHook(0x10CE4832,HookOne, PATCH_JUMP);

	while (true)
	{
		if (KeyHit(VK_MENU))
		{
			if (KeyHit(49))
			{
				NewSamMeshName = "ESam.SamA";
				sprintf((char*)(SamMeshPointer - 10), NewSamMeshName);
				*(short*)((SamMeshPointer - 10) + strlen(NewSamMeshName) + 1) = 0x0020;
				*(int*)((SamMeshPointer - 10) + strlen(NewSamMeshName) + 1 + 2) = Sam->SamValue1;
				*(int*)((SamMeshPointer - 10) + strlen(NewSamMeshName) + 1 + 2 + 4) = Sam->SamValue2;
				Sleep(130);
			}

			if (KeyHit(50))
			{
				NewSamMeshName = "ESam.SamB";
				sprintf((char*)(SamMeshPointer - 10), NewSamMeshName);
				*(short*)((SamMeshPointer - 10) + strlen(NewSamMeshName) + 1) = 0x0020;
				*(int*)((SamMeshPointer - 10) + strlen(NewSamMeshName) + 1 + 2) = Sam->SamValue1;
				*(int*)((SamMeshPointer - 10) + strlen(NewSamMeshName) + 1 + 2 + 4) = Sam->SamValue2;
				Sleep(130);
			}

			if (KeyHit(51))
			{
				NewSamMeshName = "ESam.SamC";
				sprintf((char*)(SamMeshPointer - 10), NewSamMeshName);
				*(short*)((SamMeshPointer - 10) + strlen(NewSamMeshName) + 1) = 0x0020;
				*(int*)((SamMeshPointer - 10) + strlen(NewSamMeshName) + 1 + 2) = Sam->SamValue1;
				*(int*)((SamMeshPointer - 10) + strlen(NewSamMeshName) + 1 + 2 + 4) = Sam->SamValue2;
				Sleep(130);
			}

			if (KeyHit(52))
			{
				NewSamMeshName = "ESam.SamD";
				sprintf((char*)(SamMeshPointer - 10), NewSamMeshName);
				*(short*)((SamMeshPointer - 10) + strlen(NewSamMeshName) + 1) = 0x0020;
				*(int*)((SamMeshPointer - 10) + strlen(NewSamMeshName) + 1 + 2) = Sam->SamValue1;
				*(int*)((SamMeshPointer - 10) + strlen(NewSamMeshName) + 1 + 2 + 4) = Sam->SamValue2;
				Sleep(130);
			}

			if (KeyHit(53))
			{
				NewSamMeshName = "ESam.Sam_Naked";
				sprintf((char*)(SamMeshPointer - 10), NewSamMeshName);
				*(short*)((SamMeshPointer - 10) + strlen(NewSamMeshName) + 1) = 0x0020;
				*(int*)((SamMeshPointer - 10) + strlen(NewSamMeshName) + 1 + 2) = Sam->SamValue1;
				*(int*)((SamMeshPointer - 10) + strlen(NewSamMeshName) + 1 + 2 + 4) = Sam->SamValue2;
				Sleep(130);
			}
		}
		Sleep(1);
	}
}

extern "C"
{
	__declspec(dllexport) void InitializeASI()
	{
		CreateThread(nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(Init), nullptr, 0, nullptr);
	}
}