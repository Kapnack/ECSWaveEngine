#pragma once

#include "Export.h"

#include "WaveMath/Vector3/Vector3.h"
#include "WaveMath/Quaternion/Quaternion.h"

WAVEEXPORT class Transform final
{
private:

	Vector3 localPosition;
	Quaternion localRotation;
	Vector3 localScale;
};

