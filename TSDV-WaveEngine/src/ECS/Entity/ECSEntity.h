#pragma once

class ECSEntity
{
private:

	int ID = 0;

public:

	int GetID() const
	{
		return ID;
	}

	explicit operator int() const
	{
		return GetID();
	}
};