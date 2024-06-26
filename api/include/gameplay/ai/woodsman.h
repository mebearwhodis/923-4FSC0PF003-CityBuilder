#ifndef API_GAMEPLAY_AI_WOODSMAN_H_
#define API_GAMEPLAY_AI_WOODSMAN_H_
#include "walker.h"
#include "../../graphics/sprite_entity.h"

class Woodsman : public Walker
{
public:
	Woodsman(const float x, const float y, const float linear_speed);

protected:
	void DefineTexture() override;
};
#endif // API_GAMEPLAY_AI_WOODSMAN_H_
