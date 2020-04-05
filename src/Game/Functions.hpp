#pragma once
#include "Utils/function.hpp"

namespace Game
{
	//extern bool DEBUG
	namespace Globals
	{
		// INIT
		extern std::string loadedModules;

		// RADIANT ----------------------------------------------------------------
		extern Game::cgsAddon cgsAddons;
		extern Game::savedRadiantBrushes rad_savedBrushes;
		extern Game::dynBrushesArray_t dynBrushes;
		extern Game::dynBrushModelsArray_t dynBrushModels;

		// MOVEMENT ---------------------------------------------------------------
		extern bool locPmove_checkJump; // if Jumped in Check_Jump, reset after x frames in PmoveSingle

		extern glm::vec3 locPmove_playerVelocity;	// grab local player velocity
		extern glm::vec3 locPmove_playerOrigin;		// grab local player origin
		extern glm::vec3 locPmove_playerAngles;		// grab local player angles
		extern glm::vec3 locPmove_cameraOrigin;		// grab local camera origin

		// COLLISION ---------------------------------------------------------------
		extern int drawnBrushAmount; // total amount of brushes used for calculations of planes 
		extern int drawnPlanesAmount; // total amount of planes rendered 
		extern int drawnPlanesAmountTemp; // total amount of planes rendered used to count while drawing

		// FAMETIME
		extern int serverTime;
		extern int serverTimeOld;
		extern int serverFrameTime;

		extern int pmlFrameTime;
		
		// MISC
		extern int Q3_LastProjectileWeaponUsed; // ENUM Q3WeaponNames :: this var holds the last proj. weapon that got fired
	}

	extern float COLOR_WHITE[4];
	extern float COLOR_BLACK[4];

	// ---------------
	// RADIANT / CGAME

	extern const char* g_entityBeginParsePoint;
	extern const char* g_entityEndParsePoint;
	extern int* clientActive_cmdNumber;
	extern Game::cg_s *cgs;

	char* Com_Parse(const char **data_p /*edi*/); // ASM
	bool CL_GetUserCmd(int cmdNumber /*eax*/, Game::usercmd_s *ucmd);

	// ---------
	// FASTFILES

	extern HANDLE dbHandle;

	extern const char** zone_code_post_gfx_mp;
	extern const char** zone_localized_code_post_gfx_mp;
	extern const char** zone_ui_mp;
	extern const char** zone_common_mp;
	extern const char** zone_localized_common_mp;
	extern const char** zone_mod;

	static utils::function<void()> R_BeginRemoteScreenUpdate = 0x5F78A0;
	static utils::function<void()> R_EndRemoteScreenUpdate = 0x5F78F0;
	static utils::function<void()> DB_SyncXAssets = 0x48A120;

	extern bool DB_FileExists(const char* fileName, Game::DB_FILE_EXISTS_PATH);
	
	// ---------
	// COLLISION 

	extern int* vertexCount;
	extern void* frontEndDataOut;

	extern int* polyVertColor_Minus_0x4;
	extern int* polyVertColor;
	extern int* polyVertColor_Plus_0xC;
	extern char* indices;
	extern int* indices_plus_0x2;
	extern int* indices_plus_0x4;
	extern char* initStringDvarValue;

	extern Game::clipMap_t* cm;
	extern Game::ComWorld* com;
	
	extern Game::MaterialTechniqueType* OverflowTessTech;
	extern Game::Material* OverflowTessSurf;
	extern Game::Material* builtIn_material_unlit;
	extern Game::Material* builtIn_material_unlit_depth;
	extern Game::materialCommands_t* tess;
	
	extern Game::DebugGlobals* debugGlob;
	extern Game::GfxBackEndData *_frontEndDataOut;
	extern Game::GfxBackEndData *_backEndData;
	extern Game::GfxWorld * _gfxWorld; // 0xCC9A320

	static utils::function<bool()> CreateDebugStringsIfNeeded = 0x461EC0;
	static utils::function<void(Game::DebugGlobals *debugGlobalsEntry, const float *origin, const float *color, float scale, const char *string)> R_AddDebugString = 0x60DD10; // not working currently, or well, not displaying a thing because front/backend is empty?
	static utils::function<void(int count, int width, Game::GfxPointVertex *verts, bool depthTest)> RB_DrawLines3D = 0x613040;
	static utils::function<void __fastcall (const float *colorFloat, char *colorBytes)> R_ConvertColorToBytes = 0x493530;

	// print3d // DebugStrings / Lines
	extern int* clsDebugFromServer;
	extern bool* ifRendererStarted;
	extern Game::clientStatic_t *cls;
	extern Game::clientDebugStringInfo_t *clsDebugSV_Strings;
	extern Game::clientDebugStringInfo_t *clsDebugCL_Strings;
	

	void R_AddDebugPolygon(int pointCount, const float(*points)[3]);
	void R_AddDebugPolygonNew(Game::DebugGlobals* debugGlobalsEntry, int pointCount, const float(*points)[3]);

	// --------
	// RENDERER

	extern bool* gfxRenderTargets;
	extern bool* tessSurface;
	extern int* tessSurfaceInt;

	extern int* RenderTargetWidth;
	extern int* RenderTargetHeight;
	extern int* RenderTargetArray;

	extern int* wnd_SceneHeight;
	extern float* wnd_SceneAspect;

	extern Game::Material* floatz_display;
	extern GfxCmdBufSourceState* gfxCmdBufSourceState;
	extern Game::clientDebugLineInfo_t* clientDebugLineInfo_client;
	extern Game::clientDebugLineInfo_t* clientDebugLineInfo_server;

	static utils::function<void()> RB_ShowFbColorDebug_Screen = 0x64A5A0;
	static utils::function<void()> RB_ShowFbColorDebug_Feedback = 0x64A710;
	static utils::function<void()> RB_ShowFloatZDebug = 0x64AAA0;
	static utils::function<void()> RB_ShowShadowsDebug = 0x64AB60;
	static utils::function<void(float radius, int srcRenderTargetId)> RB_GaussianFilterImage = 0x6517A0;
	static utils::function<int(float radiusX, float radiusY, int srcWidth, int srcHeight, int dstWidth, int dstHeight, Game::GfxImageFilterPass *filterPass)> RB_GenerateGaussianFilterChain = 0x651310;
	static utils::function<void(Game::GfxImageFilter *filter)> RB_FilterImage = 0x6516A0;
	static utils::function<void(std::int32_t a1, std::int32_t a2, std::int32_t a3)> DrawXModelSkinnedCached = 0x646870;
	static utils::function<bool()> CreateDebugLinesIfNeeded = 0x462080;

	typedef void*(*R_RegisterFont_t)(char* fontName, int fontSize);
		extern R_RegisterFont_t R_RegisterFont;

	typedef void*(*Material_RegisterHandle_t)(char* fontName, int fontSize);
		extern Material_RegisterHandle_t Material_RegisterHandle;

	typedef void(*RB_EndTessSurface_t)();
		extern RB_EndTessSurface_t RB_EndTessSurface;

	Game::MaterialTechnique * RB_BeginSurface(Game::MaterialTechniqueType techType, Game::Material material); // ASM
	Game::MaterialTechnique * RB_BeginSurface_CustomMaterial(Game::MaterialTechniqueType techType, Game::Material *material); // ASM

	void DrawTextWithEngine(float x, float y, float scaleX, float scaleY, char* font, const float *color, const char* text);
	void R_AddCmdDrawTextASM(const char *text, int maxChars, void *font, float x, float y, float xScale, float yScale, float rotation, const float *color, int style);
	void RB_StandardDrawCommands(Game::GfxViewInfo *viewInfo);																															
	void R_AddCmdDrawStretchPic(void *material, float x, float y, float w, float h, float null1, float null2, float null3, float null4, float *color); // ASM
	void R_SetRenderTarget(int target); // ASM
	void R_Set2D(); // ASM
	void RB_DrawStretchPic(Game::Material *material, float x, float y, float w, float h, float a6, float a7, float a8, float a9 /*-1 pushed*/);
	void CG_DrawRotatedPicPhysical(ScreenPlacement* place, float a2, float a3, float a4, float a5, float a6, float *color, void *material);
	int R_TextWidth(const char *text /*<eax*/, int maxChars, Game::Font_s *font); // ASM

	// ---------
	// UI / MENU

	extern int* gameTypeEnum; 
	extern int* mapNameEnum;
	extern Game::UiContext* _uiContext;
	extern Game::PlayerKeyState* playerKeys; // 0x8F1DB8 (missing field_t)
	extern Game::clientUIActive_t* clientUI;

	extern ScreenPlacement* scrPlace;
	extern ScreenPlacement* scrPlaceFull;

	static utils::function<void(int clientNum, int menuNum)> UI_SetActiveMenu = 0x549540;
	static utils::function<void()> Key_SetCatcher = 0x4686A0;

	extern int String_Parse(const char **p /*eax*/, char *outStr, int len);
	extern void Menus_OpenByName(const char* menuName, Game::UiContext *uiDC);
	extern void Menus_CloseByName(const char* menuName, Game::UiContext *uiDC);
	extern void Menus_CloseAll(Game::UiContext *uiDC);
	extern void Item_Text_Paint(itemDef_s *a1 /*esi*/, UiContext *a2);
	
	// ---
	// GSC 

	extern DWORD*	gScrMemTreePub;
	extern DWORD*	scrVarPub;
	extern int*		scrVarPub_p4;
	extern char*	error_message;
	extern char*	errortype;
	extern int*		scr_numParam;

	extern Game::gentity_s* scr_g_entities;
	extern Game::level_locals_t* level_locals;

	static utils::function<void()> Scr_Error_Internal = 0x51D1F0;
	static utils::function<void(bool)> Scr_AddBool = 0x523AB0;
	static utils::function<void(int)> Scr_AddInt = 0x523AB0;
	static utils::function<Game::gentity_s*()> G_Spawn = 0x4E37F0;
	static utils::function<bool(Game::gentity_s*)> G_CallSpawnEntity = 0x4DFFA0;
	static utils::function<void(Game::trajectory_t *pTr, const float *vPos, float fTotalTime, float fAccelTime, float fDecelTime, float *vCurrPos, float *pfSpeed, float *pfMidTime, float *pfDecelTime, float *vPos1, float *vPos2, float *vPos3)> ScriptMover_SetupMove = 0x4D9440;

	void G_SetOrigin(Game::gentity_s* ent, float *origin);
	void G_SetAngles(Game::gentity_s* ent, float *angles);

	std::int16_t G_ModelIndex(const char *modelName /*eax*/); // ASM
	void SV_LinkEntity(Game::gentity_s* ent /*edi*/); // ASM

	void Scr_ObjectError(const char *string /*eax*/); // ASM
	void Scr_GetVector(unsigned int argIndex /*eax*/, float *floatOut /*edx*/);

	int isButtonPressed(int button, int buttonData);

	// ----
	// IWDs

	extern const char* fs_gamedir;
	extern Game::searchpath_s* fs_searchpaths;

	static utils::function<Game::iwd_t*(const char *zipfile, const char *basename)> FS_LoadZipFile = 0x55C6F0;
	static utils::function<const char *(const char *lang)> IwdFileLanguage = 0x55D700;
	static utils::function<BOOL(LPVOID lpAddress)> FS_FreeFileList = 0x564520;
	static utils::function<void(void *lpMem)> free = 0x670DA6;

	char ** Sys_ListFiles(const char *filter, const char *directory, const char *extension, int *numfiles, int wantsubs); //ASM
	int SEH_GetLanguageIndexForName(const char *pszLanguageName, int *piLanguageIndex); //ASM
	int unzClose(const char *file /*edi*/); //ASM

	// --------
	// MOVEMENT

	extern int* g_entities;
	extern int* g_clients;
	extern int* currentTime;
	extern int* CanDamageContentMask;
	
	static utils::function<void(Game::pmove_t *pm)> PmoveSingle = 0x4143A0;
	static utils::function<void(Game::pmove_t *pm)> PM_UpdateSprint = 0x40E6A0;
	static utils::function<void(Game::pmove_t *pm, Game::pml_t *pml)> PM_WalkMove = 0x40F7A0;
	static utils::function<void(Game::pmove_t *pm, Game::pml_t *pml)> PM_AirMove = 0x40F680;
	static utils::function<bool(Game::pmove_t *pm, Game::pml_t *pml, bool gravity)> PM_SlideMove = 0x414F40;
	static utils::function<void(Game::pmove_t *pm, Game::pml_t *pml, bool gravity)> PM_StepSlideMove = 0x4155C0;
	static utils::function<void(Game::pmove_t *pm, Game::pml_t *pml)> PM_SetMovementDir = 0x40F2D0;
	static utils::function<bool(Game::pmove_t *pm, Game::pml_t *pml, int gravity)> PM_SlideMove_Internal = 0x414F40;
	static utils::function<void(Game::pmove_t *pm, Game::pml_t *pml)> PM_GroundTrace_Internal = 0x410660;
	static utils::function<void(std::int32_t nodeIndex, Game::areaParms_t *ap)> CM_AreaEntities = 0x4F7A80;
	
	void PM_Friction(Game::playerState_s *ps, Game::pml_t *pml); // ASM
	void PM_ClipVelocity_Call(const float *velocityIn, const float *traceNormal, float *velocityOut);
	bool PM_CorrectAllSolid(Game::pmove_t *pm /*eax*/, Game::pml_t *pml, Game::trace_t *trace); // ASM
	void PM_GroundTraceMissed(Game::pmove_t *pm /*eax*/, Game::pml_t *pml); // ASM
	void PM_CrashLand(Game::pmove_t *pm /*bl-nomoveneeded*/, Game::playerState_s *ps /*esi*/, Game::pml_t *pml); // ASM
	void PM_AddTouchEnt(Game::pmove_t *pm /*eax*/, int entityNum /*edi*/); // ASM
	void PM_playerTrace(Game::pmove_t *pm /*esi*/, Game::trace_t *results, const float *start, const float *mins, const float *maxs, const float *end, std::int32_t passEntityNum, std::int32_t contentMask); // ASM
	
	void G_Damage(float *dir /*eax*/, Game::gentity_s *targ, Game::gentity_s *inflictor, Game::gentity_s *attacker, float *point, int damage, int flags, int mod, int self_client, int hitloc, /*hitLocation_t*/ int a11, unsigned int a12, unsigned int timeOffset); // ASM
	float CanDamage(Game::gentity_s *inflictor, float *centerPos, Game::gentity_s *ent, float coneAngleCos, float *coneDirection, int contentmask); // ASM
	void Scr_PlayerDamage(float *dir, Game::gentity_s *targ, Game::gentity_s *inflictor, Game::gentity_s *attacker, int damage, int dflags, int mod, int weapon, float *point, Game::hitLocation_t hitLoc, int timeOffset); // ASM
	Game::gentity_s* G_FireRocket(float *kickBack, Game::gentity_s *ent, signed int weapindex, float *dir, float *gunVel, Game::gentity_s *target, float *targetOffset); // ASM

	// -----------------------------------------------------------------------
	// DVARs 

	struct dvar_s;

	static utils::function<void(dvar_s* dvar, float value, int source)> Dvar_SetFloat = 0x56C960;

	static utils::function<dvar_s* (const char *dvarName, float defaultValue, float minValue, float maxValue, std::uint16_t flags, const char *description)>
		Dvar_RegisterFloat_r = 0x56C460;

	inline dvar_s* Dvar_RegisterFloat(const char* dvarName, const char* description, float defaultValue, float minValue, float maxValue, std::uint16_t flags) {
		return Dvar_RegisterFloat_r(dvarName, defaultValue, minValue, maxValue, flags, description);
	}

	// using RegisterNew - FLOAT / VEC2 / VEC3 / VEC4 (01)
	static utils::function<dvar_s * (const char* dvarName, DvarType typeFloat2, std::uint16_t flags, const char* description, float x, float y, std::int32_t null1, std::int32_t null2, float min, float max)>
		Dvar_RegisterVec2_r = 0x56C130;

	inline dvar_s* Dvar_RegisterVec2(const char* dvarName, const char* description, float x, float y, float minValue, float maxValue, std::uint16_t flags) {
		return Dvar_RegisterVec2_r(dvarName, DvarType::DVAR_TYPE_FLOAT_2, flags, description, x, y, 0, 0, minValue, maxValue);
	}

	// using RegisterNew - FLOAT / VEC2 / VEC3 / VEC4 (01)
	static utils::function<dvar_s * (const char* dvarName, DvarType typeFloat3, std::uint16_t flags, const char* description, float x, float y, float z, std::int32_t null, float min, float max)>
		Dvar_RegisterVec3_r = 0x56C130;

	inline dvar_s* Dvar_RegisterVec3(const char* dvarName, const char* description, float x, float y, float z, float minValue, float maxValue, std::uint16_t flags) {
		return Dvar_RegisterVec3_r(dvarName, DvarType::DVAR_TYPE_FLOAT_3, flags, description, x, y, z, 0, minValue, maxValue);
	}

	// using RegisterNew - FLOAT / VEC2 / VEC3 / VEC4 (01)
	static utils::function<dvar_s* (const char *dvarName, DvarType typeFloat4, std::uint16_t flags, const char *description, float x, float y, float z, float w, float min, float max)>
		Dvar_RegisterVec4_r = 0x56C130;

	inline dvar_s* Dvar_RegisterVec4(const char* dvarName, const char* description, float x, float y, float z, float w, float minValue, float maxValue, std::uint16_t flags) {
		return Dvar_RegisterVec4_r(dvarName, DvarType::DVAR_TYPE_FLOAT_4, flags, description, x, y, z, w, minValue, maxValue);
	}

	// using RegisterNew - INT / BOOL (02)
	static utils::function<dvar_s* (const char *dvarName, DvarType typeInt, std::uint16_t flags, const char *description, std::int32_t defaultValue, std::int32_t null1, std::int32_t null2, std::int32_t null3, std::int32_t minValue, std::int32_t maxValue)>
		Dvar_RegisterInt_r = 0x56C130;

	inline dvar_s* Dvar_RegisterInt(const char* dvarName, const char* description, std::int32_t defaultValue, std::int32_t minValue, std::int32_t maxValue, std::uint16_t flags) {
		return Dvar_RegisterInt_r(dvarName, DvarType::DVAR_TYPE_INT, flags, description, defaultValue, 0, 0, 0, minValue, maxValue);
	}

	// using RegisterNew - INT / BOOL (02)
	static utils::function<dvar_s* (const char *dvarName, DvarType typeBool, std::uint16_t flags, const char *description, std::int32_t defaultValue, std::int32_t null1, std::int32_t null2, std::int32_t null3, std::int32_t null4, std::int32_t null5)>
		Dvar_RegisterBool_r = 0x56C130;

	inline dvar_s* Dvar_RegisterBool(const char* dvarName, const char* description, std::int32_t defaultValue, std::uint16_t flags) {
		return Dvar_RegisterBool_r(dvarName, DvarType::DVAR_TYPE_BOOL, flags, description, defaultValue, 0, 0, 0, 0, 0);
	}

	// using RegisterNew - ENUM (04)
	static utils::function<dvar_s* (const char *dvarName, DvarType typeEnum, std::uint16_t flags, const char *description, std::int32_t defaultIndex, std::int32_t null1, std::int32_t null2, std::int32_t null3, std::int32_t enumSize, char** enumData)>
		Dvar_RegisterEnum_r = 0x56C130;

	inline dvar_s* Dvar_RegisterEnum(const char* dvarName, const char* description, std::int32_t defaultValue, std::int32_t enumSize, char** enumData, std::uint16_t flags) {
		return Dvar_RegisterEnum_r(dvarName, DvarType::DVAR_TYPE_ENUM, flags, description, defaultValue, 0, 0, 0, enumSize, enumData);
	}

	// using RegisterNew - STRING (03)
	static utils::function<dvar_s * (const char* dvarName, DvarType typeString, std::uint16_t flags, const char* description, const char* defaultValue, std::int32_t null1, std::int32_t null2, std::int32_t null3, std::int32_t null4, std::int32_t null5)>
		Dvar_RegisterString_r = 0x56C130;

	// * do not use on module load (crash)
	inline dvar_s* Dvar_RegisterString(const char* dvarName, const char* description, const char* defaultValue, std::uint16_t flags) {
		return Dvar_RegisterString_r(dvarName, DvarType::DVAR_TYPE_STRING, flags, description, defaultValue, 0, 0, 0, 0, 0);
	}

	void Dvar_SetValue(dvar_s* _dvar, int _dvarValue);
	void Dvar_SetValue(dvar_s* _dvar, bool _dvarValue);
	void Dvar_SetValue(dvar_s* _dvar, const float _dvarValue);
	void Dvar_SetValue(dvar_s* _dvar, const char *_dvarValue);

	//dvar_s* Dvar_RegisterVariant(int dvarName /*eax*/, int dvarType, int flags, int description, int defaultValue, int y, int z, int w, float min, int max); // ASM

	Game::dvar_s* Dvar_RegisterString_hacky(const char *dvarName, const char *dvarValue, const char *description);
	char* Dvar_EnumToString(const dvar_s *a1);

	void Dvar_SetString(const char *text /*eax*/, dvar_s *dvar /*esi*/); //ASM
	dvar_s* Dvar_FindVar(const char* dvar);
	
	// -------
	// CONSOLE 

	extern float* con_matchtxtColor_currentDvar;
	extern float* con_matchtxtColor_currentValue;
	extern float* con_matchtxtColor_defaultValue;
	extern float* con_matchtxtColor_dvarDescription;
	extern float* con_matchtxtColor_domainDescription;

	// console structs
	extern ConDrawInputGlob* conDrawInputGlob;
	extern Console* con;
	extern field_t* g_consoleField;

	// console variables
	extern Font_s* con_font;
	extern bool* Key_IsCatcherActive;

	// con->screenMin / Max manual defines for use in asm
	extern float*	conScreenMin0; // left
	extern float*	conScreenMin1; // top
	extern float*	conScreenMax0; // right
	extern float*	conScreenMax1; // bottom

	extern bool*	extvar_con_ignoreMatchPrefixOnly;

	// cmd args
	extern int* argc_1410B84;
	extern int* argc_1410B40;
	extern char* argv_6BFEA7;
	extern int* argv_1410BA4;
	extern cmd_function_s* cmd_functions;

	typedef void(*SCR_DrawSmallStringExt_t)(int x, int y, const char* text);
		extern SCR_DrawSmallStringExt_t SCR_DrawSmallStringExt;

	typedef bool(*Sys_IsMainThread_t)();
		extern Sys_IsMainThread_t Sys_IsMainThread;

	typedef char*(*Con_TokenizeInput_t)();
		extern Con_TokenizeInput_t Con_TokenizeInput;

	typedef void(*Con_CancelAutoComplete_t)();
		extern Con_CancelAutoComplete_t Con_CancelAutoComplete;

	typedef void(*Con_DrawInputPrompt_t)();
		extern Con_DrawInputPrompt_t Con_DrawInputPrompt;

	typedef void(*Cmd_EndTokenizedString_t)();
		extern Cmd_EndTokenizedString_t Cmd_EndTokenizedString;

	typedef void(*ConDrawInput_IncrMatchCounter_t)(const char *);
		extern ConDrawInput_IncrMatchCounter_t ConDrawInput_IncrMatchCounter;

	typedef void(*Con_DrawInputPrompt_t)();
		extern Con_DrawInputPrompt_t Con_DrawInputPrompt;
	
	typedef bool(*Con_AnySpaceAfterCommand_t)();
		extern Con_AnySpaceAfterCommand_t Con_AnySpaceAfterCommand;

	typedef void(__cdecl *ConDrawInput_DetailedDvarMatch_t)(const char *);
		extern ConDrawInput_DetailedDvarMatch_t ConDrawInput_DetailedDvarMatch;
	
	typedef void(__cdecl *ConDrawInput_DetailedCmdMatch_t)(const char *);
		extern ConDrawInput_DetailedCmdMatch_t ConDrawInput_DetailedCmdMatch;

	typedef void(__cdecl *ConDrawInput_DvarMatch_t)(const char *);
		extern ConDrawInput_DvarMatch_t ConDrawInput_DvarMatch;

	typedef void(__cdecl *ConDrawInput_CmdMatch_t)(const char *);
		extern ConDrawInput_CmdMatch_t ConDrawInput_CmdMatch;

	typedef void(*Con_DrawOutputScrollBar_t)(float x, float y, float width, float height); 
		extern Con_DrawOutputScrollBar_t Con_DrawOutputScrollBar;

	typedef void(*Con_DrawOutputText_t)(float x, float y);
		extern Con_DrawOutputText_t Con_DrawOutputText;

	typedef bool(*Con_IsAutoCompleteMatch_t)(char *a1, char *a2, int a3);
		extern Con_IsAutoCompleteMatch_t Con_IsAutoCompleteMatch;

	void Con_DrawMessageWindowOldToNew(DWORD* msgWindow /*esi*/, int localClientNum, int xPos, int yPos, int charHeight, int horzAlign, int vertAlign, int mode, Font_s* font, const float* color, int textStyle, float msgwndScale, int textAlignMode); // ASM

	void Cmd_ForEachXO(void(__cdecl *callback)(const char *));

	void AddBaseDrawConsoleTextCmd(int charCount /*eax*/, const float *colorFloat /*ecx*/, const char *textPool, int poolSize, int firstChar, Game::Font_s *font, float x, float y, float xScale, float yScale, int style); // ASM
	void ConDrawInput_Box(float *color, int lineHeightMulti); // ASM
	void ConDrawInput_TextAndOver(char *text); // ASM
	void ConDraw_Box(float *color, float x, float y, float width, float height); // ASM
	void Con_DrawAutoCompleteChoice(int a1, char *a2); // ASM

	char* Cmd_Argv(int argIndex); // ASM
	void Dvar_ForEachName(void(__cdecl *func)(const char *)); // ASM
	void Cmd_ForEach(void(__cdecl *func)(const char *)); // ASM
	
	// -----
	// ANIMS
	
	void BG_AnimScriptEvent(scriptAnimEventTypes_t event, Game::playerState_s *ps, int force); // ASM
	
	// ------
	// COMMON

	extern Game::playerState_s* ps_loc;

	extern DWORD* cmd_id;
	extern DWORD* cmd_argc;
	extern char*** cmd_argv;
	extern cmd_function_s** cmd_ptr;
	extern XZone* g_zones;
	extern XAssetEntry* g_assetEntryPool;
	extern unsigned short* db_hashTable;
	extern infoParm_t* infoParams;

	typedef void(*Cmd_ExecuteSingleCommand_t)(int controller, int a2, const char* cmd);
		extern Cmd_ExecuteSingleCommand_t Cmd_ExecuteSingleCommand;

	typedef void(*Com_Error_t)(int type, const char* message, ...);
		extern Com_Error_t Com_Error;

	typedef void(*Com_PrintMessage_t)(int, const char*, char);
		extern Com_PrintMessage_t Com_PrintMessage;

	typedef XAssetHeader(*DB_FindXAssetHeader_t)(XAssetType type, const char* name);
		extern DB_FindXAssetHeader_t DB_FindXAssetHeader;

	typedef void(*DB_EnumXAssets_FastFile_t)(XAssetType type, void(*)(XAssetHeader, void *), void* userdata, bool overrides);
		extern DB_EnumXAssets_FastFile_t DB_EnumXAssets_FastFile;

	typedef const char* (*DB_GetXAssetNameHandler_t)(XAssetHeader* asset);
		extern DB_GetXAssetNameHandler_t* DB_GetXAssetNameHandlers;

    typedef void(*DB_LoadXAssets_t)(XZoneInfo *zoneInfo, unsigned int zoneCount, int sync);
		extern DB_LoadXAssets_t DB_LoadXAssets;

	void Cbuf_AddText(const char *text /*eax*/, int localClientNum /*ecx*/);
	void Cmd_AddCommand(const char* name, void(*callback)(), cmd_function_s* data, char);
	const char* SL_ConvertToString(int idx);

	Game::PackedUnitVec Vec3PackUnitVec(const float *unitVec);
	void Vec3UnpackUnitVec(Game::PackedUnitVec in, const float *out);
}
