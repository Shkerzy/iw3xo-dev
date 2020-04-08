#pragma once



namespace Components
{
	// add new modules here
	struct activeModules_s
	{
		bool _CG;
		bool _UI;
		bool _Pmove;
		bool _Debug;
		bool _Game;
		bool _Map;
		bool Command;
		bool GScr_Methods;
		bool QuickPatch;
		bool MenuEdit;
		bool PM_Movement;
		bool XO_Console;
		bool RB_DrawCollision;
		bool RB_ShaderOverlays;
		bool RadiantRemote;
		bool Scheduler;
	};

	extern activeModules_s active;

#define REGISTER_MODULE(name)			\
	if(active.##name)					\
		Loader::Register(new name())

	class Component
	{
	public:
		Component() {};
		virtual ~Component() {};
		virtual const char* getName() { return "Unknown"; };
	};

	class Loader
	{
	public:
		static void Initialize();
		static void Uninitialize();
		static void Register(Component* component);//, bool& registered);
		static bool Registered(const char *componentName);

		static Utils::Memory::Allocator* GetAlloctor();
		
	private:
		static std::vector<Component*> Components;
		static Utils::Memory::Allocator MemAllocator;
	};
}

// General modules that have to be included
#include "Modules/_CG.hpp"
#include "Modules/_UI.hpp"
#include "Modules/_Pmove.hpp"
#include "Modules/_Debug.hpp"
#include "Modules/_Game.hpp"
#include "Modules/_Map.hpp"

#include "Modules/Command.hpp"
#include "Modules/QuickPatch.hpp"
#include "Modules/GScr_Methods.hpp"

// Addons
#include "Modules/PM_Movement.hpp"
#include "Modules/XO_Console.hpp"
#include "Modules/RB_DrawCollision.hpp"
#include "Modules/RB_ShaderOverlays.hpp"
#include "Modules/RadiantRemote.hpp"
#include "Modules/MenuEdit.hpp"

// General Modules with dynamic hooks depending on addon component loading
#include "Modules/Scheduler.hpp"
