#include "mainMenu.h"
#include "GL\glew.h"
#include "shader.hpp"
#include "Mtx44.h"
#include "MeshBuilder.h"
#include "Utility.h"
#include "LoadTGA.h"
#include "Application.h"
#include "SharedData.h"

mainMenu::mainMenu()
{
	glClearColor(1.f, 0.f, 0.f, 0.f);
	// Enable depth test
	glEnable(GL_DEPTH_TEST);

	// Enable culling
	glEnable(GL_CULL_FACE);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	// Enable blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Generate a default VAO for now
	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);

	Mtx44 projection;
	projection.SetToPerspective(45.0f, 4.0f / 3.0f, 0.1f, 1000.0f);
	projectionStack.LoadMatrix(projection);

	// Load vertex and fragment shaders
	m_programID = LoadShaders(
		"Shader//Texture.vertexshader",
		"Shader//Text.fragmentshader"
		);
	// Get a handle for our "MVP" uniform
	m_parameters[U_MVP] = glGetUniformLocation(m_programID, "MVP");
	m_parameters[U_MODELVIEW] = glGetUniformLocation(m_programID, "MV");
	m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE] = glGetUniformLocation(m_programID, "MV_inverse_transpose");
	m_parameters[U_MATERIAL_AMBIENT] = glGetUniformLocation(m_programID, "material.kAmbient");
	m_parameters[U_MATERIAL_DIFFUSE] = glGetUniformLocation(m_programID, "material.kDiffuse");
	m_parameters[U_MATERIAL_SPECULAR] = glGetUniformLocation(m_programID, "material.kSpecular");
	m_parameters[U_MATERIAL_SHININESS] = glGetUniformLocation(m_programID, "material.kShininess");

	m_parameters[U_COLOR_TEXTURE_ENABLED] = glGetUniformLocation(m_programID, "colorTextureEnabled");
	m_parameters[U_COLOR_TEXTURE] = glGetUniformLocation(m_programID, "colorTexture");
	m_parameters[U_TEXT_ENABLED] = glGetUniformLocation(m_programID, "textEnabled");
	m_parameters[U_TEXT_COLOR] = glGetUniformLocation(m_programID, "textColor");

	// Use our shader
	glUseProgram(m_programID);

	meshList[GEO_TEXT] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[GEO_TEXT]->textureID = LoadTGA("Image/ExportedFont1.tga");

	meshList[GEO_BG] = MeshBuilder::GenerateQuad("background", Color(1, 1, 1), 1, 1);
	meshList[GEO_BG]->textureID = LoadTGA("Image//bg.tga");

	meshList[GEO_BUTTON] = MeshBuilder::GenerateQuad("instructions menu button", Color(1, 1, 1), 10, 5);
	meshList[GEO_BUTTONHOVER] = MeshBuilder::GenerateQuad("instructions menu button hover", Color(0, 0, 0), 10, 5);
	meshList[GEO_BUTTONSELECTED] = MeshBuilder::GenerateQuad("instructions menu button select", Color(1, 1, 1), 10, 5);

	meshList[GEO_PLAYBUTTON] = MeshBuilder::GenerateQuad("play_btn", Color(1, 1, 1), 14, 14);
	meshList[GEO_PLAYBUTTONHOVER] = MeshBuilder::GenerateQuad("play_btnhover", Color(0, 0, 0), 14, 14);
	meshList[GEO_PLAYBUTTONSELECTED] = MeshBuilder::GenerateQuad("play_btnselect", Color(1, 1, 1), 14, 14);

	objx = objy = 0;

	buttonchk = 0;
	state = M_MAIN;

	elapsedTime = 0;
	bufferTime = 1.5;

	clickChk = onClicked = false;
}

mainMenu::~mainMenu()
{

}

void mainMenu::Init()
{
	//MAINMENU_STATE state = M_MAIN;
}

void mainMenu::Update(double dt)
{
	switch (state)
	{
	case M_MAIN:
		elapsedTime += dt;
		if (SharedData::GetInstance()->m_newX >= 668 && SharedData::GetInstance()->m_newX <= 1142
			&& SharedData::GetInstance()->m_newY >= 407 && SharedData::GetInstance()->m_newY <= 460) {
			if (Application::IsKeyPressed(VK_LBUTTON)) {
				onClicked = true;
				buttonchk = 1;
			}
			else if (onClicked && buttonchk == 1) {
				clickChk = true;
				onClicked = false;
			}
		}

		//Instruction Button
		if (!clickChk && SharedData::GetInstance()->m_newX >= 668 && SharedData::GetInstance()->m_newX <= 1142
			&& SharedData::GetInstance()->m_newY >= 476 && SharedData::GetInstance()->m_newY <= 530) {
			if (Application::IsKeyPressed(VK_LBUTTON))
			{
				onClicked = true;
				buttonchk = 3;
			}
			else if (onClicked && buttonchk == 3) {
				clickChk = true;
				onClicked = false;
			}
		}

		//Option Button
		if (!clickChk && SharedData::GetInstance()->m_newX >= 668 && SharedData::GetInstance()->m_newX <= 1142
			&& SharedData::GetInstance()->m_newY >= 545 && SharedData::GetInstance()->m_newY <= 598) {
			if (Application::IsKeyPressed(VK_LBUTTON)) {
				onClicked = true;
				buttonchk = 4;
			}
			else if (onClicked && buttonchk == 4) {
				clickChk = true;
				onClicked = false;
			}
		}

		//Credits Button
		if (!clickChk && SharedData::GetInstance()->m_newX >= 668 && SharedData::GetInstance()->m_newX <= 1142
			&& SharedData::GetInstance()->m_newY >= 615 && SharedData::GetInstance()->m_newY <= 670) {
			if (Application::IsKeyPressed(VK_LBUTTON))
			{
				onClicked = true;
				buttonchk = 5;
			}
			else if (onClicked && buttonchk == 5) {
				clickChk = true;
				onClicked = false;
			}
		}

		//Exit Button
		if (!clickChk && SharedData::GetInstance()->m_newX >= 668 && SharedData::GetInstance()->m_newX <= 1142
			&& SharedData::GetInstance()->m_newY >= 685 && SharedData::GetInstance()->m_newY <= 736) {
			if (Application::IsKeyPressed(VK_LBUTTON) && elapsedTime >= bufferTime)
			{
				onClicked = true;
				buttonchk = 6;
			}
			else if (onClicked && buttonchk == 6) {
				clickChk = true;
				onClicked = false;
			}
		}

		break;

	case M_INSTRUCTION:
		if (SharedData::GetInstance()->m_newX >= 0 && SharedData::GetInstance()->m_newX <= 290
			&& SharedData::GetInstance()->m_newY >= 815 && SharedData::GetInstance()->m_newY <= 910) {
			if (Application::IsKeyPressed(VK_LBUTTON)) {
				state = M_MAIN;
				elapsedTime = 0;
			}
		}

		break;

	case M_OPTION:
		if (SharedData::GetInstance()->m_newX >= 0 && SharedData::GetInstance()->m_newX <= 290
			&& SharedData::GetInstance()->m_newY >= 815 && SharedData::GetInstance()->m_newY <= 910) {
			if (Application::IsKeyPressed(VK_LBUTTON))
			{
				state = M_MAIN;
				elapsedTime = 0;
			}
		}
		break;

	case M_CREDITS:
		if (SharedData::GetInstance()->m_newX >= 0 && SharedData::GetInstance()->m_newX <= 290
			&& SharedData::GetInstance()->m_newY >= 815 && SharedData::GetInstance()->m_newY <= 910) {
			if (Application::IsKeyPressed(VK_LBUTTON)) {
				state = M_MAIN;
				elapsedTime = 0;
			}
		}
		break;

	}

	UpdateButton(dt);

	//Play
	//if (Application::IsKeyPressed(VK_LBUTTON))
}

void mainMenu::UpdateButton(double dt)
{
	//check for which button has been click'ed'
	//list for button reference on header
	if (clickChk)
	{
		if (buttonchk == 1)
		{
			SharedData::GetInstance()->stateChange = true;
			SharedData::GetInstance()->gameState = SharedData::G_GAME;
		}

		if (buttonchk == 3)
		{
			SharedData::GetInstance()->stateChange = true;
			state = M_INSTRUCTION;
		}
		else if (buttonchk == 4)
		{
			SharedData::GetInstance()->stateChange = true;
			state = M_OPTION;
		}
		else if (buttonchk == 5)
		{
			SharedData::GetInstance()->stateChange = true;
			state = M_CREDITS;
		}
		else if (buttonchk == 6)
		{
			SharedData::GetInstance()->gameState = SharedData::G_EXIT;
		}

	}

}

void mainMenu::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Mtx44 MVP;

	modelStack.LoadIdentity();

	//check current states and render/update based on state
	switch (state)
	{
	case M_MAIN:MainMenuState();
		break;
	case M_INSTRUCTION:InstructionState();
		break;
	case M_OPTION:OptionsState();
		break;
	case M_CREDITS:CreditState();
		break;
	}
}

void mainMenu::RenderMesh(Mesh* mesh, bool enableLight)
{
	Mtx44 MVP, modelView, modelView_inverse_transpose;

	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	modelView = viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MODELVIEW], 1, GL_FALSE, &modelView.a[0]);

	if (enableLight)
	{
		glUniform1i(m_parameters[U_LIGHTENABLED], 1);
		modelView_inverse_transpose = modelView.GetInverse().GetTranspose();
		glUniformMatrix4fv(m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE], 1, GL_FALSE, &modelView_inverse_transpose.a[0]);

		//load material
		glUniform3fv(m_parameters[U_MATERIAL_AMBIENT], 1, &mesh->material.kAmbient.r);
		glUniform3fv(m_parameters[U_MATERIAL_DIFFUSE], 1, &mesh->material.kDiffuse.r);
		glUniform3fv(m_parameters[U_MATERIAL_SPECULAR], 1, &mesh->material.kSpecular.r);
		glUniform1f(m_parameters[U_MATERIAL_SHININESS], mesh->material.kShininess);
	}
	else
	{
		glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	}

	if (mesh->textureID > 0)
	{
		glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, mesh->textureID);
		glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	}
	else
	{
		glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 0);
	}

	mesh->Render();

	if (mesh->textureID > 0)
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}

void mainMenu::RenderButtonOnScreen(Mesh* mesh, Color color, float size, float borderX, float borderY)
{
	//if (!meshList[GEO_BUTTON] || !meshList[GEO_PLAYBUTTON]  || !meshList[GEO_BUTTONRED] )//|| meshList[GEO_BUTTON]->textureID <= 0)  //error check
	//return;

	glDisable(GL_DEPTH_TEST);
	Mtx44 ortho;
	ortho.SetToOrtho(0, 80, 0, 60, -10, 10);    //size of screen UI
	projectionStack.PushMatrix();
	projectionStack.LoadMatrix(ortho);
	viewStack.PushMatrix();
	viewStack.LoadIdentity();   //no need camera for ortho mode
	modelStack.PushMatrix();
	modelStack.LoadIdentity();  //reset modelStack


	modelStack.PushMatrix();
	modelStack.Translate(borderX, borderY, 0);
	modelStack.Scale(size, size / 6, size);
	RenderMesh(mesh, false);
	modelStack.PopMatrix();

	projectionStack.PopMatrix();
	viewStack.PopMatrix();
	modelStack.PopMatrix();
	glEnable(GL_DEPTH_TEST);
}

void mainMenu::RenderBackgroundOnScreen(Mesh* mesh, Color color, float size, float borderX, float borderY)
{
	//if (!meshList[GEO_BUTTON] || !meshList[GEO_PLAYBUTTON]  || !meshList[GEO_BUTTONRED] )//|| meshList[GEO_BUTTON]->textureID <= 0)  //error check
	//return;

	glDisable(GL_DEPTH_TEST);
	Mtx44 ortho;
	ortho.SetToOrtho(0, 80, 0, 60, -10, 10);    //size of screen UI
	projectionStack.PushMatrix();
	projectionStack.LoadMatrix(ortho);
	viewStack.PushMatrix();
	viewStack.LoadIdentity();   //no need camera for ortho mode
	modelStack.PushMatrix();
	modelStack.LoadIdentity();  //reset modelStack


	modelStack.PushMatrix();
	modelStack.Translate(borderX, borderY, 0);
	modelStack.Scale(size, size, size);
	RenderMesh(mesh, false);
	modelStack.PopMatrix();

	projectionStack.PopMatrix();
	viewStack.PopMatrix();
	modelStack.PopMatrix();
	glEnable(GL_DEPTH_TEST);
}

void mainMenu::RenderText(Mesh* mesh, std::string text, Color color)
{
	if (!mesh || mesh->textureID <= 0)  //error check
		return;

	glDisable(GL_DEPTH_TEST);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 1);
	glUniform3fv(m_parameters[U_TEXT_COLOR], 1, &color.r);
	glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mesh->textureID);
	glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);

	for (unsigned i = 0; i < text.length(); ++i) {
		Mtx44 characterSpacing;
		characterSpacing.SetToTranslation(i * 1.0f, 0, 0);  //1.f is the spacing of each character (can be changed)
		Mtx44 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top() * characterSpacing;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
		mesh->Render((unsigned)text[i] * 6, 6);
	}

	glBindTexture(GL_TEXTURE_2D, 0);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 0);
	glEnable(GL_DEPTH_TEST);
}

void mainMenu::RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y)
{
	if (!mesh || mesh->textureID <= 0)  //error check
		return;

	glDisable(GL_DEPTH_TEST);
	Mtx44 ortho;
	ortho.SetToOrtho(0, 80, 0, 60, -10, 10);    //size of screen UI
	projectionStack.PushMatrix();
	projectionStack.LoadMatrix(ortho);
	viewStack.PushMatrix();
	viewStack.LoadIdentity();   //no need camera for ortho mode
	modelStack.PushMatrix();
	modelStack.LoadIdentity();  //reset modelStack
	modelStack.Scale(size, size, size);
	modelStack.Translate(x, y, 0);

	glUniform1i(m_parameters[U_TEXT_ENABLED], 1);
	glUniform3fv(m_parameters[U_TEXT_COLOR], 1, &color.r);
	glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mesh->textureID);
	glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);

	for (unsigned i = 0; i < text.length(); ++i) {
		Mtx44 characterSpacing;
		characterSpacing.SetToTranslation(i * 0.8f + 0.5f, 0.5f, 0);  //1.f is the spacing of each character (can be changed)
		Mtx44 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top() * characterSpacing;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
		mesh->Render((unsigned)text[i] * 6, 6);
	}

	glBindTexture(GL_TEXTURE_2D, 0);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 0);

	projectionStack.PopMatrix();
	viewStack.PopMatrix();
	modelStack.PopMatrix();
	glEnable(GL_DEPTH_TEST);
}

void mainMenu::MainMenuState()
{

	RenderBackgroundOnScreen(meshList[GEO_BG], Color(0, 0, 0), 80, 40, 40);
	//Play Button
	if (SharedData::GetInstance()->m_newX >= 668 && SharedData::GetInstance()->m_newX <= 1142
		&& SharedData::GetInstance()->m_newY >= 407 && SharedData::GetInstance()->m_newY <= 460){
		if (onClicked)
		{
			RenderButtonOnScreen(meshList[GEO_PLAYBUTTONSELECTED], Color(0, 0, 0), 20, 38, 35);
			RenderTextOnScreen(meshList[GEO_TEXT], "Play", Color(0, 0, 1), 2, 17.3, 17);
		}
		else
		{
			RenderButtonOnScreen(meshList[GEO_PLAYBUTTONHOVER], Color(0, 0, 0), 20, 38, 35);
			RenderTextOnScreen(meshList[GEO_TEXT], "Play", Color(0, 0, 1), 2, 17.3, 17);
		}
	}
	else
		RenderButtonOnScreen(meshList[GEO_PLAYBUTTON], Color(0, 0, 0), 20, 38, 35);
		RenderTextOnScreen(meshList[GEO_TEXT], "Play", Color(0, 0, 1), 2, 17.3, 17);
	
	//Instruction Button
	if (!clickChk && SharedData::GetInstance()->m_newX >= 668 && SharedData::GetInstance()->m_newX <= 1142
		&& SharedData::GetInstance()->m_newY >= 476 && SharedData::GetInstance()->m_newY <= 530) {
		if (onClicked)
		{
			RenderButtonOnScreen(meshList[GEO_BUTTONSELECTED], Color(0, 0, 0), 20, 38, 31);
			RenderTextOnScreen(meshList[GEO_TEXT], "Instructions", Color(0, 0, 1), 2, 14.3, 15);
		}
		else
		{
			RenderButtonOnScreen(meshList[GEO_BUTTONHOVER], Color(0, 0, 0), 20, 38, 31);
			RenderTextOnScreen(meshList[GEO_TEXT], "Instructions", Color(0, 0, 1), 2, 14.3, 15);
		}
	}
	else
		RenderButtonOnScreen(meshList[GEO_BUTTON], Color(0, 0, 0), 20, 38, 31);
		RenderTextOnScreen(meshList[GEO_TEXT], "Instructions", Color(0, 0, 1), 2, 14.3, 15);
	
	//Option Button
	if (!clickChk && SharedData::GetInstance()->m_newX >= 668 && SharedData::GetInstance()->m_newX <= 1142
		&& SharedData::GetInstance()->m_newY >= 545 && SharedData::GetInstance()->m_newY <= 598) {
		if (onClicked)
		{
			RenderButtonOnScreen(meshList[GEO_BUTTONSELECTED], Color(0, 0, 0), 20, 38, 27);
			RenderTextOnScreen(meshList[GEO_TEXT], "Options", Color(0, 0, 1), 2, 16.3, 13);
		}
		else
		{
			RenderButtonOnScreen(meshList[GEO_BUTTONHOVER], Color(0, 0, 0), 20, 38, 27);
			RenderTextOnScreen(meshList[GEO_TEXT], "Options", Color(0, 0, 1), 2, 16.3, 13);
		}
	}
	else
		RenderButtonOnScreen(meshList[GEO_BUTTON], Color(0, 0, 0), 20, 38, 27);
		RenderTextOnScreen(meshList[GEO_TEXT], "Options", Color(0, 0, 1), 2, 16.3, 13);
	
	//Credit Button
	if (!clickChk && SharedData::GetInstance()->m_newX >= 668 && SharedData::GetInstance()->m_newX <= 1142
		&& SharedData::GetInstance()->m_newY >= 615 && SharedData::GetInstance()->m_newY <= 670) {
		if (onClicked)
		{
			RenderButtonOnScreen(meshList[GEO_BUTTONSELECTED], Color(0, 0, 0), 20, 38, 23);
			RenderTextOnScreen(meshList[GEO_TEXT], "Credits", Color(0, 0, 1), 2, 16.3, 11);
		}
		else
		{
			RenderButtonOnScreen(meshList[GEO_BUTTONHOVER], Color(0, 0, 0), 20, 38, 23);
			RenderTextOnScreen(meshList[GEO_TEXT], "Credits", Color(0, 0, 1), 2, 16.3, 11);
		}
	}
	else
		RenderButtonOnScreen(meshList[GEO_BUTTON], Color(0, 0, 0), 20, 38, 23);
		RenderTextOnScreen(meshList[GEO_TEXT], "Credits", Color(0, 0, 1), 2, 16.3, 11);

	//Exit Button
	if (!clickChk && SharedData::GetInstance()->m_newX >= 668 && SharedData::GetInstance()->m_newX <= 1142
		&& SharedData::GetInstance()->m_newY >= 685 && SharedData::GetInstance()->m_newY <= 736) {
		if (onClicked)
		{
			RenderButtonOnScreen(meshList[GEO_BUTTONSELECTED], Color(0, 0, 0), 20, 38, 19);
			RenderTextOnScreen(meshList[GEO_TEXT], "Quit", Color(0, 0, 1), 2, 17.3, 9);
		}
		else
		{
			RenderButtonOnScreen(meshList[GEO_BUTTONHOVER], Color(0, 0, 0), 20, 38, 19);
			RenderTextOnScreen(meshList[GEO_TEXT], "Quit", Color(0, 0, 1), 2, 17.3, 9);
		}
	}
	else
		RenderButtonOnScreen(meshList[GEO_BUTTON], Color(0, 0, 0), 20, 38, 19);
		RenderTextOnScreen(meshList[GEO_TEXT], "Quit", Color(0, 0, 1), 2, 17.3, 9);
	

	RenderTextOnScreen(meshList[GEO_TEXT], " Le Space Game", Color(0, 0, 0), 3, 6, 17);

	//mouse postion
	RenderTextOnScreen(meshList[GEO_TEXT], "x pos : " + std::to_string(SharedData::GetInstance()->m_newX), Color(0, 0, 0), 2, 1, 2);
	RenderTextOnScreen(meshList[GEO_TEXT], "y pos : " + std::to_string(SharedData::GetInstance()->m_newY), Color(0, 0, 0), 2, 1, 1);
}

void mainMenu::InstructionState()
{
	clickChk = false;
	onClicked = false;
	buttonchk = 0;

	RenderButtonOnScreen(meshList[GEO_PLAYBUTTONSELECTED], Color(0, 0, 0), 3, 38, 27);

	if (SharedData::GetInstance()->m_newX >= 0 && SharedData::GetInstance()->m_newX <= 290
		&& SharedData::GetInstance()->m_newY >= 815 && SharedData::GetInstance()->m_newY <= 910)
	{
		//return
		RenderButtonOnScreen(meshList[GEO_BUTTONREDHOVER],  Color(0, 0, 0), 2, 5, 12);
	}
	else
		RenderButtonOnScreen(meshList[GEO_BUTTONRED], Color(0, 0, 0), 2, 5, 12);

}

void mainMenu::OptionsState()
{
	clickChk = false;
	onClicked = false;
	buttonchk = 0;

	RenderButtonOnScreen(meshList[GEO_PLAYBUTTONSELECTED], Color(0, 0, 0), 3, 38, 27);
	if (SharedData::GetInstance()->m_newX >= 0 && SharedData::GetInstance()->m_newX <= 290
		&& SharedData::GetInstance()->m_newY >= 815 && SharedData::GetInstance()->m_newY <= 910)
	{
		//return
		RenderButtonOnScreen(meshList[GEO_BUTTONREDHOVER], Color(0, 0, 0), 2, 5, 12);
	}
	else
		RenderButtonOnScreen(meshList[GEO_BUTTONRED], Color(0, 0, 0), 2, 5, 12);

}

void mainMenu::CreditState()
{
	clickChk = false;
	onClicked = false;
	buttonchk = 0;

	RenderButtonOnScreen(meshList[GEO_PLAYBUTTONSELECTED], Color(0, 0, 0), 3, 38, 27);
	if (SharedData::GetInstance()->m_newX >= 0 && SharedData::GetInstance()->m_newX <= 290
		&& SharedData::GetInstance()->m_newY >= 815 && SharedData::GetInstance()->m_newY <= 910)
	{
		//return
		RenderButtonOnScreen(meshList[GEO_BUTTONREDHOVER],  Color(0, 0, 0), 2, 5, 12);
	}
	else
		RenderButtonOnScreen(meshList[GEO_BUTTONRED],  Color(0, 0, 0), 2, 5, 12);

}

void mainMenu::Exit()
{
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
}