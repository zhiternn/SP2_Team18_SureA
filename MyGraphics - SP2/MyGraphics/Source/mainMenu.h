#include "Scene.h"
#include "Mesh.h"
#include "Mtx44.h"
#include "MatrixStack.h"
#include "Light.h"
#include "Material.h"

#ifndef MAIN_MENU_H
#define MAIN_MENU_H

using std::string;

class mainMenu : public Scene
{
	enum MAINMENU_STATE
	{
		M_MAIN = 0,
		M_PLAY,
		M_OPTION,
		M_INSTRUCTION,
		M_CREDITS,
		M_EXIT,

		M_TOTAL
	};

	enum GEOMETRY_MENU
	{
		GEO_BG,
		GEO_TEXT,
		GEO_TEXTBOX,
		GEO_MENUBAR,

		GEO_BUTTON,
		GEO_BUTTONHOVER, 
		GEO_BUTTONSELECTED,

		GEO_PLAYBUTTON, 
		GEO_PLAYBUTTONHOVER, 
		GEO_PLAYBUTTONSELECTED,

		GEO_EXITBUTTON, 
		GEO_EXITBUTTONHOVER, 
		GEO_EXITBUTTONSELECTED,

		GEO_TOTAL
	};

	enum UNIFORM_TYPE
	{
		U_MVP = 0, // MVP = MODEL VIEW PROJECTION
		U_MODELVIEW,
		U_MODELVIEW_INVERSE_TRANSPOSE,
		U_MATERIAL_AMBIENT,
		U_MATERIAL_DIFFUSE,
		U_MATERIAL_SPECULAR,
		U_MATERIAL_SHININESS,

		U_LIGHT0_POSITION,
		U_LIGHT0_COLOR,
		U_LIGHT0_POWER,
		U_LIGHT0_KC,
		U_LIGHT0_KL,
		U_LIGHT0_KQ,
		U_LIGHT0_TYPE,
		U_LIGHT0_SPOTDIRECTION,
		U_LIGHT0_COSCUTOFF,
		U_LIGHT0_COSINNER,
		U_LIGHT0_EXPONENT,

		U_LIGHTENABLED,
		U_NUMLIGHTS,
		U_COLOR_TEXTURE_ENABLED,
		U_COLOR_TEXTURE,
		U_TEXT_ENABLED,
		U_TEXT_COLOR,

		U_TOTAL
	};

public:
	mainMenu();
	~mainMenu();

	void Init();
	void Update(double dt);
	void Render();
	void Exit();

	unsigned m_vertexArrayID;
	unsigned m_programID;
	unsigned m_parameters[U_TOTAL];
	Mesh *meshList[GEO_TOTAL];

	MS modelStack, viewStack, projectionStack;
	void RenderMesh(Mesh *mesh, bool enableLight);
	void RenderText(Mesh* mesh, std::string text, Color color);
	void RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x = 0.f, float y = 0.f);
	void RenderButtonOnScreen(Mesh* mesh, Color color, float size, float borderX, float borderY);
	void RenderTitleOnScreen(Mesh* mesh, Color color, float size, float borderX, float borderY);
	void RenderBackgroundOnScreen(Mesh* mesh, Color color, float size, float borderX, float borderY);
	void UpdateButton(double dt);
	void readTxtFile(string load);
	
	//game states
	void MainMenuState();
	void InstructionState();
	void OptionsState();
	void CreditState();

	//check if button is clicked
	bool clickChk;
	bool onClicked;
	bool check;

	//bool to check if what page is active
	bool instructions;
	bool options;
	bool credits;

	//check if player is overclicking
	double bufferTime;
	double elapsedTime;

	//check what state is the program suppose to be in
	int buttonchk;

	MAINMENU_STATE state;


	float objx, objy;
};
#endif