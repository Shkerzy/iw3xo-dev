#pragma once

namespace Components
{
	class PM_Movement : public Component
	{
	public:
		PM_Movement();
		~PM_Movement();
		const char* getName() override { return "PM_Movement"; };
		


	private:
		float positionSaved = false;
		float savedOrigin[3];
		float savedAngle[3];
	};
}
