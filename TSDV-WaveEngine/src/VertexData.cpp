#include "VertexData.h"

VertexData::VertexData()
{
}

VertexData::VertexData(const float& x, const float& y, const float& z, const float& r, const float& g, const float& b, const float& a)
{
	position.x = x;
	position.y = y;
	position.z = z;

	color.r = r;
	color.g = g;
	color.b = b;
	color.a = a;
}

VertexData::VertexData(const Vector3& position, const Color& color)
{
	this->position = position;
	this->color = color;
}

VertexData::VertexData(const Vector3& position, const Color& color, const Vector2& textureCordinates)
{
	this->position = position;
	this->color = color;
	this->textureCordinates = textureCordinates;
}

VertexData::VertexData(const Vector3& position, const Color& color, const Vector2& textureCordinates, const Vector3& normal)
{
	this->position = position;
	this->color = color;
	this->textureCordinates = textureCordinates;
	this->normal = normal;
}

void VertexData::SetColor(const Color& color)
{
	this->color = color;
}