#pragma once

enum Direction
{
	NORTH = 0,
	SOUTH,
	EAST,
	WEST
};

class IEntity
{
protected:
	int x, y;
public:
	virtual void Init() {}
	virtual void Update(float delta) {}
	virtual void Render() {}
};