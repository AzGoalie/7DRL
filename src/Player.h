#pragma once

#include "IEntity.h"

class Player : public IEntity
{
private:
	Direction dir;
public:
	void Init();
	void Update(float delta);
	void Render();
};