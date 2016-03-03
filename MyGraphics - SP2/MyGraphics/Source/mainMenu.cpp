//#include "mainMenu.h"
//#include "GL\glew.h"
//#include "shader.hpp"
//#include "Mtx44.h"
//#include "MeshBuilder.h"
//#include "Utility.h"
//#include "LoadTGA.h"
//#include "Application.h"
//#include "SharedData.h"
//
//#include <sstream>
//#include <fstream>
//
//using std::string;
//using std::ifstream;
//
//ifstream readFile;
//
////char output to store read from text file
//string output;
//
//
//mainMenu::mainMenu()
//{
//	glClearColor(1.f, 0.f, 0.f, 0.f);
//	// Enable depth test
//	glEnable(GL_DEPTH_TEST);
//
//	// Enable culling
//	glEnable(GL_CULL_FACE);
//
//	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
//
//	// Enable blending
//	glEnable(GL_BLEND);
//	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//
//	// Generate a default VAO for now
//	glGenVertexArrays(1, &m_vertexArrayID);
//	glBindVertexArray(m_vertexArrayID);
//
//	Mtx44 projection;
//	projection.SetToPerspective(45.0f, 4.0f / 3.0f, 0.1f, 1000.0f);
//	projectionStack.LoadMatrix(projection);
//
//	// Load vertex and fragment shaders
//	m_programID = LoadShaders(
//		"Shader//Texture.vertexshader",
//		"Shader//Text.fragmentshader"
//		);
//	// Get a handle for our "MVP" uniform
//	m_parameters[U_MVP] = glGetUniformLocation(m_programID, "MVP");
//	m_parameters[U_MODELVIEW] = glGetUniformLocation(m_programID, "MV");
//	m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE] = glGetUniformLocation(m_programID, "MV_inverse_transpose");
//	m_parameters[U_MATERIAL_AMBIENT] = glGetUniformLocation(m_programID, "material.kAmbient");
//	m_parameters[U_MATERIAL_DIFFUSE] = glGetUniformLocation(m_programID, "material.kDiffuse");
//	m_parameters[U_MATERIAL_SPECULAR] = glGetUniformLocation(m_programID, "material.kSpecular");
//	m_parameters[U_MATERIAL_SHININESS] = glGetUniformLocation(m_programID, "material.kShininess");
//
//	m_parameters[U_COLOR_TEXTURE_ENABLED] = glGetUniformLocation(m_programID, "colorTextureEnabled");
//	m_parameters[U_COLOR_TEXTURE] = glGetUniformLocation(m_programID, "colorTexture");
//	m_parameters[U_TEXT_ENABLED] = glGetUniformLocation(m_programID, "textEnabled");
//	m_parameters[U_TEXT_COLOR] = glGetUniformLocation(m_programID, "textColor");
//
//	// Use our shader
//	glUseProgram(m_programID);
//
//	meshList[GEO_TEXT] = MeshBuilder::GenerateText("text", 16, 16);
//	meshList[GEO_TEXT]->textureID = LoadTGA("Image//ExportedFont1.tga");
//
//	meshList[GEO_BG] = MeshBuilder::GenerateQuad("background", Color(1, 1, 1), 1, 1);
//	meshList[GEO_BG]->textureID = LoadTGA("Image//bg.tga");
//
//	meshList[GEO_TEXTBOX] = MeshBuilder::GenerateQuad("Textbox for menu pages", Color(0, 0, 0), 1, 1);
//
//	meshList[GEO_MENUBAR] = MeshBuilder::GenerateQuad("menu bar", Color(1, 1, 1), 1, 1);
//	meshList[GEO_MENUBAR]->textureID = LoadTGA("Image//menubar.tga");
//
//	meshList[GEO_EXITBUTTON] = MeshBuilder::GenerateQuad("exit button", Color(1, 1, 1), 1, 1);
//	meshList[GEO_EXITBUTTON]->textureID = LoadTGA("Image//button.tga");
//	meshList[GEO_EXITBUTTONHOVER] = MeshBuilder::GenerateQuad("exit button hover", Color(0, 0, 0), 1, 1);
//	meshList[GEO_EXITBUTTONHOVER]->textureID = LoadTGA("Image//buttonhover.tga");
//	meshList[GEO_BUTTONSELECTED] = MeshBuilder::GenerateQuad("exit menu button select", Color(1, 1, 1), 1, 1);
//	meshList[GEO_BUTTONSELECTED]->textureID = LoadTGA("Image//button.tga");
//
//	meshList[GEO_BUTTON] = MeshBuilder::GenerateQuad(" menu button", Color(1, 1, 1), 1, 1);
//	meshList[GEO_BUTTON]->textureID = LoadTGA("Image//button.tga");
//	meshList[GEO_BUTTONHOVER] = MeshBuilder::GenerateQuad(" menu button hover", Color(1, 1, 1), 1, 1);
//	meshList[GEO_BUTTONHOVER]->textureID = LoadTGA("Image//buttonhover.tga");
//	meshList[GEO_BUTTONSELECTED] = MeshBuilder::GenerateQuad(" menu button select", Color(1, 1, 1), 1, 1);
//	meshList[GEO_BUTTONSELECTED]->textureID = LoadTGA("Image//button.tga");
//
//
//	meshList[GEO_PLAYBUTTON] = MeshBuilder::GenerateQuad("play button", Color(1, 1, 1), 1, 1);
//	meshList[GEO_PLAYBUTTON]->textureID = LoadTGA("Image//button.tga");
//	meshList[GEO_PLAYBUTTONHOVER] = MeshBuilder::GenerateQuad("play button hover", Color(1, 1, 1), 1, 1);
//	meshList[GEO_PLAYBUTTONHOVER]->textureID = LoadTGA("Image//buttonhover.tga");
//	meshList[GEO_PLAYBUTTONSELECTED] = MeshBuilder::GenerateQuad("play button select", Color(1, 1, 1), 1, 1);
//	meshList[GEO_PLAYBUTTONSELECTED]->textureID = LoadTGA("Image//button.tga");
//
//	objx = objy = 0;
//
//	buttonchk = 0;
//	state = M_MAIN;
//
//	elapsedTime = 0;
//	bufferTime = 1.5;
//
//	clickChk = onClicked = false;
//}
//
//mainMenu::~mainMenu()
//{
//
//}
//
//void mainMenu::Init()
//{
//	//MAINMENU_STATE state = M_MAIN;
//}
//
//void mainMenu::readTxtFile(string load)
//{
//	readFile.open(load);
//	int y = 0;
//	if (readFile.is_open())
//	{
//		if (instructions == true)
//		{
//			RenderBackgroundOnScreen(meshList[GEO_MENUBAR], Color(0, 0, 0), 45, 52, 35);
//			while (getline(readFile, output))
//			{
//				if (y == 0 || y == -1)
//				{
//					RenderTextOnScreen(meshList[GEO_TEXT], output, Color(1, 0, 1), 2, 18, y + 27);
//					y--;
//				}
//				else if (y == -3 || y == -7 || y == -11 || y == -15)
//				{
//					RenderTextOnScreen(meshList[GEO_TEXT], output, Color(0, 1, 0), 2, 18, y + 27);
//					y--;
//				}
//				else
//				{
//					RenderTextOnScreen(meshList[GEO_TEXT], output, Color(1, 0, 0), 2, 18, y + 27);
//					y--;
//				}
//			}
//			readFile.close();
//		}
//		if (credits == true)
//		{
//			RenderBackgroundOnScreen(meshList[GEO_MENUBAR], Color(0, 0, 0), 50, 41, 33);
//			while (getline(readFile, output))
//			{
//				if (y == 0)
//				{
//					RenderTextOnScreen(meshList[GEO_TEXT], output, Color(1, 0, 1), 2, 13, y + 27);
//					y--;
//				}
//				else if (y == -4 || y == -9 || y == -14 || y == -19)
//				{
//					RenderTextOnScreen(meshList[GEO_TEXT], output, Color(1, 1, 1), 2, 13, y + 27);
//					y--;
//				}
//				else
//				{
//					RenderTextOnScreen(meshList[GEO_TEXT], output, Color(1, 0, 0), 2, 13, y + 27);
//					y--;
//				}
//			}
//			readFile.close();
//		}
//	}
//	
//}
//
//void mainMenu::Update(double dt)
//{
//	//check if player is clicking in real time
//	if (Application::IsKeyPressed(VK_LBUTTON))
//	{
//		check = true;
//	}
//	else
//	{
//		check = false;
//	}
//
//	switch (state)
//	{
//	case M_MAIN:
//		elapsedTime += dt;
//		if (SharedData::GetInstance()->m_newX >= 668 && SharedData::GetInstance()->m_newX <= 1142
//			&& SharedData::GetInstance()->m_newY >= 407 && SharedData::GetInstance()->m_newY <= 460) {
//			if (Application::IsKeyPressed(VK_LBUTTON)) {
//				onClicked = true;
//				buttonchk = 1;
//			}
//			else if (onClicked && buttonchk == 1) {
//				clickChk = true;
//				onClicked = false;
//			}
//		}
//
//		//Instruction Button
//		if (SharedData::GetInstance()->m_newX >= 668 && SharedData::GetInstance()->m_newX <= 1142
//			&& SharedData::GetInstance()->m_newY >= 476 && SharedData::GetInstance()->m_newY <= 530) {
//			if (Application::IsKeyPressed(VK_LBUTTON))
//			{
//				onClicked = true;
//				buttonchk = 3;
//			}
//			else if (onClicked && buttonchk == 3) {
//				clickChk = true;
//				onClicked = false;
//			}
//		}
//
//		//Option Button
//		if (SharedData::GetInstance()->m_newX >= 668 && SharedData::GetInstance()->m_newX <= 1142
//			&& SharedData::GetInstance()->m_newY >= 545 && SharedData::GetInstance()->m_newY <= 598) {
//			if (Application::IsKeyPressed(VK_LBUTTON)) {
//				onClicked = true;
//				buttonchk = 4;
//			}
//			else if (onClicked && buttonchk == 4) {
//				clickChk = true;
//				onClicked = false;
//			}
//		}
//
//		//Credits Button
//		if (SharedData::GetInstance()->m_newX >= 668 && SharedData::GetInstance()->m_newX <= 1142
//			&& SharedData::GetInstance()->m_newY >= 615 && SharedData::GetInstance()->m_newY <= 670) {
//			if (Application::IsKeyPressed(VK_LBUTTON))
//			{
//				onClicked = true;
//				buttonchk = 5;
//			}
//			else if (onClicked && buttonchk == 5) {
//				clickChk = true;
//				onClicked = false;
//			}
//		}
//
//		//Exit Button
//		if (SharedData::GetInstance()->m_newX >= 668 && SharedData::GetInstance()->m_newX <= 1142
//			&& SharedData::GetInstance()->m_newY >= 685 && SharedData::GetInstance()->m_newY <= 736) {
//			if (Application::IsKeyPressed(VK_LBUTTON) && elapsedTime >= bufferTime)
//			{
//				onClicked = true;
//				buttonchk = 6;
//			}
//			else if (onClicked && buttonchk == 6) {
//				clickChk = true;
//				onClicked = false;
//			}
//		}
//
//		break;
//
//	case M_INSTRUCTION:
//		if (SharedData::GetInstance()->m_newX >= 1412 && SharedData::GetInstance()->m_newX <= 1895
//			&& SharedData::GetInstance()->m_newY >= 880 && SharedData::GetInstance()->m_newY <= 950) {
//			if (Application::IsKeyPressed(VK_LBUTTON) && check == true) {
//				state = M_MAIN;
//				elapsedTime = 0;
//				instructions = false;
//			}
//		}
//
//		break;
//
//	case M_OPTION:
//		if (SharedData::GetInstance()->m_newX >= 1412 && SharedData::GetInstance()->m_newX <= 1895
//			&& SharedData::GetInstance()->m_newY >= 880 && SharedData::GetInstance()->m_newY <= 950) {
//			if (Application::IsKeyPressed(VK_LBUTTON) && check == true){
//				state = M_MAIN;
//				elapsedTime = 0;
//				options = false;
//			}
//		}
//		break;
//
//	case M_CREDITS:
//		if (SharedData::GetInstance()->m_newX >= 1412 && SharedData::GetInstance()->m_newX <= 1895
//			&& SharedData::GetInstance()->m_newY >= 880 && SharedData::GetInstance()->m_newY <= 950) {
//			if (Application::IsKeyPressed(VK_LBUTTON) && check == true) {
//				state = M_MAIN;
//				elapsedTime = 0;
//				credits = false;
//			}
//		}
//		break;
//
//	}
//
//	UpdateButton(dt);
//
//	//Play
//	//if (Application::IsKeyPressed(VK_LBUTTON))
//}
//
//void mainMenu::UpdateButton(double dt)
//{
//	//check for which button has been click'ed'
//	//list for button reference on header
//	if (clickChk)
//	{
//		if (buttonchk == 1)
//		{
//			SharedData::GetInstance()->stateChange = true;
//			SharedData::GetInstance()->gameState = SharedData::G_GAME;
//		}
//
//		if (buttonchk == 3)
//		{
//			instructions = true;
//		}
//		else if (buttonchk == 4)
//		{
//			options = true;
//		}
//		else if (buttonchk == 5)
//		{
//			credits = true;
//		}
//		else if (buttonchk == 6)
//		{
//			SharedData::GetInstance()->gameState = SharedData::G_EXIT;
//		}
//
//	}
//
//	if (state == M_MAIN)
//	{
//		if (instructions == true)
//		{
//			state = M_INSTRUCTION;
//		}
//		if (options == true)
//		{
//			state = M_OPTION;
//		}
//		if (credits == true)
//		{
//			state = M_CREDITS;
//		}
//	}
//
//}
//
//void mainMenu::Render()
//{
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//	Mtx44 MVP;
//
//	modelStack.LoadIdentity();
//
//	//check current states and render/update based on state
//	switch (state)
//	{
//	case M_MAIN:MainMenuState();
//		break;
//	case M_INSTRUCTION:InstructionState();
//		break;
//	case M_OPTION:OptionsState();
//		break;
//	case M_CREDITS:CreditState();
//		break;
//	}
//
//}
//
//void mainMenu::RenderMesh(Mesh* mesh, bool enableLight)
//{
//	Mtx44 MVP, modelView, modelView_inverse_transpose;
//
//	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
//	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
//	modelView = viewStack.Top() * modelStack.Top();
//	glUniformMatrix4fv(m_parameters[U_MODELVIEW], 1, GL_FALSE, &modelView.a[0]);
//
//	if (enableLight)
//	{
//		glUniform1i(m_parameters[U_LIGHTENABLED], 1);
//		modelView_inverse_transpose = modelView.GetInverse().GetTranspose();
//		glUniformMatrix4fv(m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE], 1, GL_FALSE, &modelView_inverse_transpose.a[0]);
//
//		//load material
//		glUniform3fv(m_parameters[U_MATERIAL_AMBIENT], 1, &mesh->material.kAmbient.r);
//		glUniform3fv(m_parameters[U_MATERIAL_DIFFUSE], 1, &mesh->material.kDiffuse.r);
//		glUniform3fv(m_parameters[U_MATERIAL_SPECULAR], 1, &mesh->material.kSpecular.r);
//		glUniform1f(m_parameters[U_MATERIAL_SHININESS], mesh->material.kShininess);
//	}
//	else
//	{
//		glUniform1i(m_parameters[U_LIGHTENABLED], 0);
//	}
//
//	if (mesh->textureID > 0)
//	{
//		glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
//		glActiveTexture(GL_TEXTURE0);
//		glBindTexture(GL_TEXTURE_2D, mesh->textureID);
//		glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
//	}
//	else
//	{
//		glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 0);
//	}
//
//	mesh->Render();
//
//	if (mesh->textureID > 0)
//	{
//		glBindTexture(GL_TEXTURE_2D, 0);
//	}
//}
//
//void mainMenu::RenderButtonOnScreen(Mesh* mesh, Color color, float size, float borderX, float borderY)
//{
//	//if (!meshList[GEO_BUTTON] || !meshList[GEO_PLAYBUTTON]  || !meshList[GEO_EXITBUTTON] )//|| meshList[GEO_BUTTON]->textureID <= 0)  //error check
//	//return;
//
//	glDisable(GL_DEPTH_TEST);
//	Mtx44 ortho;
//	ortho.SetToOrtho(0, 80, 0, 60, -10, 10);    //size of screen UI
//	projectionStack.PushMatrix();
//	projectionStack.LoadMatrix(ortho);
//	viewStack.PushMatrix();
//	viewStack.LoadIdentity();   //no need camera for ortho mode
//	modelStack.PushMatrix();
//	modelStack.LoadIdentity();  //reset modelStack
//
//
//	modelStack.PushMatrix();
//	modelStack.Translate(borderX, borderY, 0);
//	modelStack.Scale(size, size / 6, size);
//	RenderMesh(mesh, false);
//	modelStack.PopMatrix();
//
//	projectionStack.PopMatrix();
//	viewStack.PopMatrix();
//	modelStack.PopMatrix();
//	glEnable(GL_DEPTH_TEST);
//}
//
//void mainMenu::RenderTitleOnScreen(Mesh* mesh, Color color, float size, float borderX, float borderY)
//{
//	//if (!meshList[GEO_BUTTON] || !meshList[GEO_PLAYBUTTON]  || !meshList[GEO_EXITBUTTON] )//|| meshList[GEO_BUTTON]->textureID <= 0)  //error check
//	//return;
//
//	glDisable(GL_DEPTH_TEST);
//	Mtx44 ortho;
//	ortho.SetToOrtho(0, 80, 0, 60, -10, 10);    //size of screen UI
//	projectionStack.PushMatrix();
//	projectionStack.LoadMatrix(ortho);
//	viewStack.PushMatrix();
//	viewStack.LoadIdentity();   //no need camera for ortho mode
//	modelStack.PushMatrix();
//	modelStack.LoadIdentity();  //reset modelStack
//
//
//	modelStack.PushMatrix();
//	modelStack.Translate(borderX, borderY, 0);
//	modelStack.Scale(size, size / 4, size);
//	RenderMesh(mesh, false);
//	modelStack.PopMatrix();
//
//	projectionStack.PopMatrix();
//	viewStack.PopMatrix();
//	modelStack.PopMatrix();
//	glEnable(GL_DEPTH_TEST);
//}
//
//void mainMenu::RenderBackgroundOnScreen(Mesh* mesh, Color color, float size, float borderX, float borderY)
//{
//	//if (!meshList[GEO_BUTTON] || !meshList[GEO_PLAYBUTTON]  || !meshList[GEO_EXITBUTTON] )//|| meshList[GEO_BUTTON]->textureID <= 0)  //error check
//	//return;
//
//	glDisable(GL_DEPTH_TEST);
//	Mtx44 ortho;
//	ortho.SetToOrtho(0, 80, 0, 60, -10, 10);    //size of screen UI
//	projectionStack.PushMatrix();
//	projectionStack.LoadMatrix(ortho);
//	viewStack.PushMatrix();
//	viewStack.LoadIdentity();   //no need camera for ortho mode
//	modelStack.PushMatrix();
//	modelStack.LoadIdentity();  //reset modelStack
//
//
//	modelStack.PushMatrix();
//	modelStack.Translate(borderX, borderY, 0);
//	modelStack.Scale(size, size, size);
//	RenderMesh(mesh, false);
//	modelStack.PopMatrix();
//
//	projectionStack.PopMatrix();
//	viewStack.PopMatrix();
//	modelStack.PopMatrix();
//	glEnable(GL_DEPTH_TEST);
//}
//
//void mainMenu::RenderText(Mesh* mesh, std::string text, Color color)
//{
//	if (!mesh || mesh->textureID <= 0)  //error check
//		return;
//
//	glDisable(GL_DEPTH_TEST);
//	glUniform1i(m_parameters[U_TEXT_ENABLED], 1);
//	glUniform3fv(m_parameters[U_TEXT_COLOR], 1, &color.r);
//	glUniform1i(m_parameters[U_LIGHTENABLED], 0);
//	glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
//	glActiveTexture(GL_TEXTURE0);
//	glBindTexture(GL_TEXTURE_2D, mesh->textureID);
//	glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
//
//	for (unsigned i = 0; i < text.length(); ++i) {
//		Mtx44 characterSpacing;
//		characterSpacing.SetToTranslation(i * 1.0f, 0, 0);  //1.f is the spacing of each character (can be changed)
//		Mtx44 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top() * characterSpacing;
//		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
//		mesh->Render((unsigned)text[i] * 6, 6);
//	}
//
//	glBindTexture(GL_TEXTURE_2D, 0);
//	glUniform1i(m_parameters[U_TEXT_ENABLED], 0);
//	glEnable(GL_DEPTH_TEST);
//}
//
//void mainMenu::RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y)
//{
//	if (!mesh || mesh->textureID <= 0)  //error check
//		return;
//
//	glDisable(GL_DEPTH_TEST);
//	Mtx44 ortho;
//	ortho.SetToOrtho(0, 80, 0, 60, -10, 10);    //size of screen UI
//	projectionStack.PushMatrix();
//	projectionStack.LoadMatrix(ortho);
//	viewStack.PushMatrix();
//	viewStack.LoadIdentity();   //no need camera for ortho mode
//	modelStack.PushMatrix();
//	modelStack.LoadIdentity();  //reset modelStack
//	modelStack.Scale(size, size, size);
//	modelStack.Translate(x, y, 0);
//
//	glUniform1i(m_parameters[U_TEXT_ENABLED], 1);
//	glUniform3fv(m_parameters[U_TEXT_COLOR], 1, &color.r);
//	glUniform1i(m_parameters[U_LIGHTENABLED], 0);
//	glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
//	glActiveTexture(GL_TEXTURE0);
//	glBindTexture(GL_TEXTURE_2D, mesh->textureID);
//	glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
//
//	for (unsigned i = 0; i < text.length(); ++i) {
//		Mtx44 characterSpacing;
//		characterSpacing.SetToTranslation(i * 0.6f + 0.5f, 0.5f, 0);  //1.f is the spacing of each character (can be changed)
//		Mtx44 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top() * characterSpacing;
//		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
//		mesh->Render((unsigned)text[i] * 6, 6);
//	}
//
//	glBindTexture(GL_TEXTURE_2D, 0);
//	glUniform1i(m_parameters[U_TEXT_ENABLED], 0);
//
//	projectionStack.PopMatrix();
//	viewStack.PopMatrix();
//	modelStack.PopMatrix();
//	glEnable(GL_DEPTH_TEST);
//}
//
//void mainMenu::MainMenuState()
//{
//
//	RenderBackgroundOnScreen(meshList[GEO_BG], Color(0, 0, 0), 80, 40, 30);
//	//Play Button
//	if (SharedData::GetInstance()->m_newX >= 668 && SharedData::GetInstance()->m_newX <= 1142
//		&& SharedData::GetInstance()->m_newY >= 407 && SharedData::GetInstance()->m_newY <= 460){
//		if (onClicked)
//		{
//			RenderButtonOnScreen(meshList[GEO_PLAYBUTTONSELECTED], Color(0, 0, 0), 20, 38, 35);
//			RenderTextOnScreen(meshList[GEO_TEXT], "Play", Color(1, 0, 1), 2, 17.8, 17);
//		}
//		else
//		{
//			RenderButtonOnScreen(meshList[GEO_PLAYBUTTONHOVER], Color(0, 0, 0), 20, 38, 35);
//			RenderTextOnScreen(meshList[GEO_TEXT], "Play", Color(1, 0, 1), 2, 17.8, 17);
//		}
//	}
//	else
//		RenderButtonOnScreen(meshList[GEO_PLAYBUTTON], Color(0, 0, 0), 20, 38, 35);
//	RenderTextOnScreen(meshList[GEO_TEXT], "Play", Color(1, 0, 1), 2, 17.8, 17);
//	
//	//Instruction Button
//	if (!clickChk && SharedData::GetInstance()->m_newX >= 668 && SharedData::GetInstance()->m_newX <= 1142
//		&& SharedData::GetInstance()->m_newY >= 476 && SharedData::GetInstance()->m_newY <= 530) {
//		if (onClicked)
//		{
//			RenderButtonOnScreen(meshList[GEO_BUTTONSELECTED], Color(0, 0, 0), 20, 38, 31);
//			RenderTextOnScreen(meshList[GEO_TEXT], "Instructions", Color(1, 0, 1), 2, 15.5, 15);
//		}
//		else
//		{
//			RenderButtonOnScreen(meshList[GEO_BUTTONHOVER], Color(0, 0, 0), 20, 38, 31);
//			RenderTextOnScreen(meshList[GEO_TEXT], "Instructions", Color(1, 0, 1), 2, 15.5, 15);
//		}
//	}
//	else
//		RenderButtonOnScreen(meshList[GEO_BUTTON], Color(0, 0, 0), 20, 38, 31);
//	RenderTextOnScreen(meshList[GEO_TEXT], "Instructions", Color(1, 0, 1), 2, 15.5, 15);
//	
//	//Option Button
//	if (!clickChk && SharedData::GetInstance()->m_newX >= 668 && SharedData::GetInstance()->m_newX <= 1142
//		&& SharedData::GetInstance()->m_newY >= 545 && SharedData::GetInstance()->m_newY <= 598) {
//		if (onClicked)
//		{
//			RenderButtonOnScreen(meshList[GEO_BUTTONSELECTED], Color(0, 0, 0), 20, 38, 27);
//			RenderTextOnScreen(meshList[GEO_TEXT], "Options", Color(1, 0, 1), 2, 17, 13);
//		}
//		else
//		{
//			RenderButtonOnScreen(meshList[GEO_BUTTONHOVER], Color(0, 0, 0), 20, 38, 27);
//			RenderTextOnScreen(meshList[GEO_TEXT], "Options", Color(1, 0, 1), 2, 17, 13);
//		}
//	}
//	else
//		RenderButtonOnScreen(meshList[GEO_BUTTON], Color(0, 0, 0), 20, 38, 27);
//	RenderTextOnScreen(meshList[GEO_TEXT], "Options", Color(1, 0, 1), 2, 17, 13);
//	
//	//Credit Button
//	if (!clickChk && SharedData::GetInstance()->m_newX >= 668 && SharedData::GetInstance()->m_newX <= 1142
//		&& SharedData::GetInstance()->m_newY >= 615 && SharedData::GetInstance()->m_newY <= 670) {
//		if (onClicked)
//		{
//			RenderButtonOnScreen(meshList[GEO_BUTTONSELECTED], Color(0, 0, 0), 20, 38, 23);
//			RenderTextOnScreen(meshList[GEO_TEXT], "Credits", Color(1, 0, 1), 2, 17, 11);
//		}
//		else
//		{
//			RenderButtonOnScreen(meshList[GEO_BUTTONHOVER], Color(0, 0, 0), 20, 38, 23);
//			RenderTextOnScreen(meshList[GEO_TEXT], "Credits", Color(1, 0, 1), 2, 17, 11);
//		}
//	}
//	else
//		RenderButtonOnScreen(meshList[GEO_BUTTON], Color(0, 0, 0), 20, 38, 23);
//	RenderTextOnScreen(meshList[GEO_TEXT], "Credits", Color(1, 0, 1), 2, 17, 11);
//
//	//Exit Button
//	if (!clickChk && SharedData::GetInstance()->m_newX >= 668 && SharedData::GetInstance()->m_newX <= 1142
//		&& SharedData::GetInstance()->m_newY >= 685 && SharedData::GetInstance()->m_newY <= 736) {
//		if (onClicked)
//		{
//			RenderButtonOnScreen(meshList[GEO_BUTTONSELECTED], Color(0, 0, 0), 20, 38, 19);
//			RenderTextOnScreen(meshList[GEO_TEXT], "Quit", Color(1, 0, 1), 2, 17.7, 9);
//		}
//		else
//		{
//			RenderButtonOnScreen(meshList[GEO_BUTTONHOVER], Color(0, 0, 0), 20, 38, 19);
//			RenderTextOnScreen(meshList[GEO_TEXT], "Quit", Color(1, 0, 1), 2, 17.7, 9);
//		}
//	}
//	else
//		RenderButtonOnScreen(meshList[GEO_BUTTON], Color(0, 0, 0), 20, 38, 19);
//	RenderTextOnScreen(meshList[GEO_TEXT], "Quit", Color(1, 0, 1), 2, 17.7, 9);
//	
//
//	RenderTextOnScreen(meshList[GEO_TEXT], " Le Space Game", Color(1, 0, 0), 3, 6, 17);
//
//	//mouse postion
//	RenderTextOnScreen(meshList[GEO_TEXT], "x pos : " + std::to_string(SharedData::GetInstance()->m_newX), Color(0, 0, 0), 2, 1, 2);
//	RenderTextOnScreen(meshList[GEO_TEXT], "y pos : " + std::to_string(SharedData::GetInstance()->m_newY), Color(0, 0, 0), 2, 1, 1);
//}
//
//void mainMenu::InstructionState()
//{
//	clickChk = false;
//	onClicked = false;
//	buttonchk = 0;
//
//	RenderBackgroundOnScreen(meshList[GEO_BG], Color(0, 0, 0), 80, 40, 40);
//
//	readTxtFile("Text//instructions.txt");
//
//	RenderTitleOnScreen(meshList[GEO_MENUBAR], Color(0, 0, 0), 23, 12.5, 57);
//	RenderTextOnScreen(meshList[GEO_TEXT], "INSTRUCTIONS :", Color(0, 1, 1), 2, 2, 28);
//
//	if(SharedData::GetInstance()->m_newX >= 1412 && SharedData::GetInstance()->m_newX <= 1895
//		&& SharedData::GetInstance()->m_newY >= 880 && SharedData::GetInstance()->m_newY <= 950){
//		if (onClicked)
//		{
//			RenderButtonOnScreen(meshList[GEO_EXITBUTTONSELECTED], Color(0, 0, 0), 20, 69.5, 7);
//			RenderTextOnScreen(meshList[GEO_TEXT], "Back to Main", Color(1, 0, 1), 2, 30.8, 3);
//		}
//		RenderButtonOnScreen(meshList[GEO_EXITBUTTONHOVER], Color(0, 0, 0), 20, 69.5, 7);
//		RenderTextOnScreen(meshList[GEO_TEXT], "Back to Main", Color(1, 0, 1), 2, 30.8, 3);
//	}
//	else
//		RenderButtonOnScreen(meshList[GEO_EXITBUTTON], Color(0, 0, 0), 20, 69.5, 7);
//	RenderTextOnScreen(meshList[GEO_TEXT], "Back to Main", Color(1, 0, 1), 2, 30.8, 3);
//
//}
//
//void mainMenu::OptionsState()
//{
//	clickChk = false;
//	onClicked = false;
//	buttonchk = 0;
//
//	RenderBackgroundOnScreen(meshList[GEO_BG], Color(0, 0, 0), 80, 40, 40);
//
//	RenderTitleOnScreen(meshList[GEO_MENUBAR], Color(0, 0, 0), 15, 9, 57);
//	RenderTextOnScreen(meshList[GEO_TEXT], "OPTIONS :", Color(0, 1, 1), 2, 2, 28);
//
//	if (SharedData::GetInstance()->m_newX >= 1412 && SharedData::GetInstance()->m_newX <= 1895
//		&& SharedData::GetInstance()->m_newY >= 880 && SharedData::GetInstance()->m_newY <= 950){
//		if (onClicked)
//		{
//			RenderButtonOnScreen(meshList[GEO_EXITBUTTONSELECTED], Color(0, 0, 0), 20, 69.5, 7);
//			RenderTextOnScreen(meshList[GEO_TEXT], "Back to Main", Color(1, 0, 1), 2, 30.8, 3);
//		}
//		RenderButtonOnScreen(meshList[GEO_EXITBUTTONHOVER], Color(0, 0, 0), 20, 69.5, 7);
//		RenderTextOnScreen(meshList[GEO_TEXT], "Back to Main", Color(1, 0, 1), 2, 30.8, 3);
//	}
//	else
//		RenderButtonOnScreen(meshList[GEO_EXITBUTTON], Color(0, 0, 0), 20, 69.5, 7);
//	RenderTextOnScreen(meshList[GEO_TEXT], "Back to Main", Color(1, 0, 1), 2, 30.8, 3);
//
//}
//
//void mainMenu::CreditState()
//{
//	clickChk = false;
//	onClicked = false;
//	buttonchk = 0;
//
//	RenderBackgroundOnScreen(meshList[GEO_BG], Color(0, 0, 0), 80, 40, 40);
//
//	readTxtFile("Text//credits.txt");
//
//	RenderTitleOnScreen(meshList[GEO_MENUBAR], Color(0, 0, 0), 15, 9, 57);
//	RenderTextOnScreen(meshList[GEO_TEXT], "CREDITS :", Color(0, 1, 1), 2, 2, 28);
//
//	if (SharedData::GetInstance()->m_newX >= 1412 && SharedData::GetInstance()->m_newX <= 1895
//		&& SharedData::GetInstance()->m_newY >= 880 && SharedData::GetInstance()->m_newY <= 950){
//		if (onClicked)
//		{
//			RenderButtonOnScreen(meshList[GEO_EXITBUTTONSELECTED], Color(0, 0, 0), 20, 69.5, 7);
//			RenderTextOnScreen(meshList[GEO_TEXT], "Back to Main", Color(1, 0, 1), 2, 30.8, 3);
//		}
//		RenderButtonOnScreen(meshList[GEO_EXITBUTTONHOVER], Color(0, 0, 0), 20, 69.5, 7);
//		RenderTextOnScreen(meshList[GEO_TEXT], "Back to Main", Color(1, 0, 1), 2, 30.8, 3);
//	}
//	else
//		RenderButtonOnScreen(meshList[GEO_EXITBUTTON], Color(0, 0, 0), 20, 69.5, 7);
//	RenderTextOnScreen(meshList[GEO_TEXT], "Back to Main", Color(1, 0, 1), 2, 30.8, 3);
//
//}
//
//void mainMenu::Exit()
//{
//	glDeleteVertexArrays(1, &m_vertexArrayID);
//	glDeleteProgram(m_programID);
//}

#include "mainMenu.h"
#include "GL\glew.h"
#include "shader.hpp"
#include "Mtx44.h"
#include "MeshBuilder.h"
#include "Utility.h"
#include "LoadTGA.h"
#include "Application.h"
#include "SharedData.h"

#include <sstream>
#include <fstream>

using std::string;
using std::ifstream;

ifstream readFile;

//char output to store read from text file
string output;

/****************************************************************************/
/*!
\brief
Return a copy of a copy constructor


\return
Resulting in objects being initialised with parameters
*/
/****************************************************************************/
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
	meshList[GEO_TEXT]->textureID = LoadTGA("Image//ExportedFont1.tga");

	meshList[GEO_BG] = MeshBuilder::GenerateQuad("background", Color(1, 1, 1), 1, 1);
	meshList[GEO_BG]->textureID = LoadTGA("Image//bg.tga");

	meshList[GEO_TEXTBOX] = MeshBuilder::GenerateQuad("Textbox for menu pages", Color(0, 0, 0), 1, 1);

	meshList[GEO_MENUBAR] = MeshBuilder::GenerateQuad("menu bar", Color(1, 1, 1), 1, 1);
	meshList[GEO_MENUBAR]->textureID = LoadTGA("Image//menubar.tga");

	meshList[GEO_EXITBUTTON] = MeshBuilder::GenerateQuad("exit button", Color(1, 1, 1), 1, 1);
	meshList[GEO_EXITBUTTON]->textureID = LoadTGA("Image//button.tga");
	meshList[GEO_EXITBUTTONHOVER] = MeshBuilder::GenerateQuad("exit button hover", Color(0, 0, 0), 1, 1);
	meshList[GEO_EXITBUTTONHOVER]->textureID = LoadTGA("Image//buttonhover.tga");
	meshList[GEO_BUTTONSELECTED] = MeshBuilder::GenerateQuad("exit menu button select", Color(1, 1, 1), 1, 1);
	meshList[GEO_BUTTONSELECTED]->textureID = LoadTGA("Image//button.tga");

	meshList[GEO_BUTTON] = MeshBuilder::GenerateQuad(" menu button", Color(1, 1, 1), 1, 1);
	meshList[GEO_BUTTON]->textureID = LoadTGA("Image//button.tga");
	meshList[GEO_BUTTONHOVER] = MeshBuilder::GenerateQuad(" menu button hover", Color(1, 1, 1), 1, 1);
	meshList[GEO_BUTTONHOVER]->textureID = LoadTGA("Image//buttonhover.tga");
	meshList[GEO_BUTTONSELECTED] = MeshBuilder::GenerateQuad(" menu button select", Color(1, 1, 1), 1, 1);
	meshList[GEO_BUTTONSELECTED]->textureID = LoadTGA("Image//button.tga");


	meshList[GEO_PLAYBUTTON] = MeshBuilder::GenerateQuad("play button", Color(1, 1, 1), 1, 1);
	meshList[GEO_PLAYBUTTON]->textureID = LoadTGA("Image//button.tga");
	meshList[GEO_PLAYBUTTONHOVER] = MeshBuilder::GenerateQuad("play button hover", Color(1, 1, 1), 1, 1);
	meshList[GEO_PLAYBUTTONHOVER]->textureID = LoadTGA("Image//buttonhover.tga");
	meshList[GEO_PLAYBUTTONSELECTED] = MeshBuilder::GenerateQuad("play button select", Color(1, 1, 1), 1, 1);
	meshList[GEO_PLAYBUTTONSELECTED]->textureID = LoadTGA("Image//button.tga");

	objx = objy = 0;

	buttonchk = 0;
	state = M_MAIN;

	elapsedTime = 0;
	bufferTime = 1.5;

	clickChk = onClicked = false;
}

/****************************************************************************/
/*!
\brief
Return a copy of a default destructor


\return
Resulting in objects being deleted
*/
/****************************************************************************/

mainMenu::~mainMenu()
{

}

/****************************************************************************/
/*!
\brief
Initialises the scene


\return
Resulting values/objects being initialised at the start of the scene
*/
/****************************************************************************/

void mainMenu::Init()
{

}

/****************************************************************************/
/*!
\brief
Read textfile and converting it to string

\param load - name of file to be read

\return
Resulting in string being returned
*/
/****************************************************************************/

void mainMenu::readTxtFile(string load)
{
	readFile.open(load);
	int y = 0;
	if (readFile.is_open())
	{
		if (instructions == true)
		{
			RenderBackgroundOnScreen(meshList[GEO_MENUBAR], Color(0, 0, 0), 45, 52, 35);
			while (getline(readFile, output))
			{
				if (y == 0 || y == -1)
				{
					RenderTextOnScreen(meshList[GEO_TEXT], output, Color(1, 0, 1), 2, 18, y + 27);
					y--;
				}
				else if (y == -3 || y == -7 || y == -11 || y == -15)
				{
					RenderTextOnScreen(meshList[GEO_TEXT], output, Color(0, 1, 0), 2, 18, y + 27);
					y--;
				}
				else
				{
					RenderTextOnScreen(meshList[GEO_TEXT], output, Color(1, 0, 0), 2, 18, y + 27);
					y--;
				}
			}
			readFile.close();
		}
		if (credits == true)
		{
			RenderBackgroundOnScreen(meshList[GEO_MENUBAR], Color(0, 0, 0), 50, 41, 33);
			while (getline(readFile, output))
			{
				if (y == 0)
				{
					RenderTextOnScreen(meshList[GEO_TEXT], output, Color(1, 0, 1), 2, 13, y + 27);
					y--;
				}
				else if (y == -4 || y == -9 || y == -14 || y == -19)
				{
					RenderTextOnScreen(meshList[GEO_TEXT], output, Color(1, 1, 1), 2, 13, y + 27);
					y--;
				}
				else
				{
					RenderTextOnScreen(meshList[GEO_TEXT], output, Color(1, 0, 0), 2, 13, y + 27);
					y--;
				}
			}
			readFile.close();
		}
	}

}

/****************************************************************************/
/*!
\brief
Updates scene

\param dt - real time

\return
Resulting in functions being updated
*/
/****************************************************************************/

void mainMenu::Update(double dt)
{
	//check if player is clicking in real time
	if (Application::IsKeyPressed(VK_LBUTTON))
	{
		check = true;
	}
	else
	{
		check = false;
	}

	switch (state)
	{
	case M_MAIN:
		elapsedTime += dt;
		if (SharedData::GetInstance()->m_newX >= Application::width * 0.3479 && SharedData::GetInstance()->m_newX <= Application::width * 0.5948
			&& SharedData::GetInstance()->m_newY >= Application::height * 0.383 && SharedData::GetInstance()->m_newY <= Application::height * 0.4331) {
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
		if (!clickChk && SharedData::GetInstance()->m_newX >= Application::width * 0.3479 && SharedData::GetInstance()->m_newX <= Application::width * 0.5948
			&& SharedData::GetInstance()->m_newY >= Application::height * 0.4482  && SharedData::GetInstance()->m_newY <= Application::height * 0.499) {
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

		//Credits Button
		if (!clickChk && SharedData::GetInstance()->m_newX >= Application::width * 0.3479 && SharedData::GetInstance()->m_newX <= Application::width * 0.5948
			&& SharedData::GetInstance()->m_newY >= Application::height * 0.5132 && SharedData::GetInstance()->m_newY <= Application::height * 0.5631) {
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
		if (!clickChk && SharedData::GetInstance()->m_newX >= Application::width * 0.3479 && SharedData::GetInstance()->m_newX <= Application::width * 0.5948
			&& SharedData::GetInstance()->m_newY >= Application::height * 0.579 && SharedData::GetInstance()->m_newY <= Application::height * 0.6308) {
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
		if (SharedData::GetInstance()->m_newX >= Application::width * 0.7354 && SharedData::GetInstance()->m_newX <= Application::width * 0.9869
			&& SharedData::GetInstance()->m_newY >= Application::height * 0.8286 && SharedData::GetInstance()->m_newY <= Application::height * 0.8945) {
			if (Application::IsKeyPressed(VK_LBUTTON) && check == true) {
				state = M_MAIN;
				elapsedTime = 0;
				instructions = false;
			}
		}

		break;

	case M_CREDITS:
		if (SharedData::GetInstance()->m_newX >= Application::width * 0.7354 && SharedData::GetInstance()->m_newX <= Application::width * 0.9869
			&& SharedData::GetInstance()->m_newY >= Application::height * 0.8286 && SharedData::GetInstance()->m_newY <= Application::height * 0.8945) {
			if (Application::IsKeyPressed(VK_LBUTTON) && check == true) {
				state = M_MAIN;
				elapsedTime = 0;
				credits = false;
			}
		}
		break;

	}

	UpdateButton(dt);

	//Play
	//if (Application::IsKeyPressed(VK_LBUTTON))
}

/****************************************************************************/
/*!
\brief
Updates button according to selection

\param dt - real time

\return
Resulting in different scenes being called accordingly
*/
/****************************************************************************/

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
			instructions = true;
		}
		else if (buttonchk == 4)
		{
			options = true;
		}
		else if (buttonchk == 5)
		{
			credits = true;
		}
		else if (buttonchk == 6)
		{
			SharedData::GetInstance()->gameState = SharedData::G_EXIT;
		}

	}

	if (state == M_MAIN)
	{
		if (instructions == true)
		{
			state = M_INSTRUCTION;
		}
		if (options == true)
		{
			state = M_OPTION;
		}
		if (credits == true)
		{
			state = M_CREDITS;
		}
	}

}

/****************************************************************************/
/*!
\brief
Renders the scene


\return
Resulting in objects being rendered in the scene
*/
/****************************************************************************/

void mainMenu::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Mtx44 MVP;

	modelStack.LoadIdentity();

	//check current states and render/update based on state
	RenderBackgroundOnScreen(meshList[GEO_BG], Color(0, 0, 0), 80, 40, 40);
	switch (state)
	{
	case M_MAIN:MainMenuState();
		break;
	case M_INSTRUCTION:InstructionState();
		break;
	case M_CREDITS:CreditState();
		break;
	}

}

/****************************************************************************/
/*!
\brief
Render Meshes in the scene

\param mesh -		 Type of Mesh to be rendered
\param enableLight - Whether light is enabled or not

\return
Resulting in functions being returned
*/
/****************************************************************************/

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

/****************************************************************************/
/*!
\brief
Render Button Meshes on screen

\param mesh -		Type of Mesh to be rendered
\param color -		Color of button to be rendered
\param size -		Size of button to be rendered
\param borderX -	X location to be rendered at
\param borderY -	Y location to be rendered at

\return
Resulting in button being rendered on screen
*/
/****************************************************************************/

void mainMenu::RenderButtonOnScreen(Mesh* mesh, Color color, float size, float borderX, float borderY)
{
	//if (!meshList[GEO_BUTTON] || !meshList[GEO_PLAYBUTTON]  || !meshList[GEO_EXITBUTTON] )//|| meshList[GEO_BUTTON]->textureID <= 0)  //error check
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

/****************************************************************************/
/*!
\brief
Render Title Meshes on screen

\param mesh -		Type of Mesh to be rendered
\param color -		Color of button to be rendered
\param size -		Size of button to be rendered
\param borderX -	X location to be rendered at
\param borderY -	Y location to be rendered at

\return
Resulting in title being rendered on screen
*/
/****************************************************************************/

void mainMenu::RenderTitleOnScreen(Mesh* mesh, Color color, float size, float borderX, float borderY)
{
	//if (!meshList[GEO_BUTTON] || !meshList[GEO_PLAYBUTTON]  || !meshList[GEO_EXITBUTTON] )//|| meshList[GEO_BUTTON]->textureID <= 0)  //error check
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
	modelStack.Scale(size, size / 4, size);
	RenderMesh(mesh, false);
	modelStack.PopMatrix();

	projectionStack.PopMatrix();
	viewStack.PopMatrix();
	modelStack.PopMatrix();
	glEnable(GL_DEPTH_TEST);
}

/****************************************************************************/
/*!
\brief
Render Background Meshes on screen

\param mesh -		Type of Mesh to be rendered
\param color -		Color of button to be rendered
\param size -		Size of button to be rendered
\param borderX -	X location to be rendered at
\param borderY -	Y location to be rendered at

\return
Resulting in background being rendered on screen
*/
/****************************************************************************/

void mainMenu::RenderBackgroundOnScreen(Mesh* mesh, Color color, float size, float borderX, float borderY)
{
	//if (!meshList[GEO_BUTTON] || !meshList[GEO_PLAYBUTTON]  || !meshList[GEO_EXITBUTTON] )//|| meshList[GEO_BUTTON]->textureID <= 0)  //error check
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

/****************************************************************************/
/*!
\brief
Render Text in the scene

\param mesh -	Type of Mesh to be rendered
\param text -	Text to be rendered
\param color -	Color of button to be rendered

\return
Resulting in text being rendered
*/
/****************************************************************************/

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

/****************************************************************************/
/*!
\brief
Render Text Meshes on screen

\param mesh -		Type of Mesh to be rendered
\param text -		Text to be rendered
\param color -		Color of button to be rendered
\param size -		Size of button to be rendered
\param x -			X location to be rendered at
\param y -			Y location to be rendered at

\return
Resulting in text being rendered on screen
*/
/****************************************************************************/

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
		characterSpacing.SetToTranslation(i * 0.6f + 0.5f, 0.5f, 0);  //1.f is the spacing of each character (can be changed)
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

/****************************************************************************/
/*!
\brief
Render Main Menu state


\return
Resulting in main menu being rendered
*/
/****************************************************************************/

void mainMenu::MainMenuState()
{
	//Play Button
	if (SharedData::GetInstance()->m_newX >= Application::width * 0.3479 && SharedData::GetInstance()->m_newX <= Application::width * 0.5948
		&& SharedData::GetInstance()->m_newY >= Application::height * 0.383 && SharedData::GetInstance()->m_newY <= Application::height * 0.4331){
		RenderButtonOnScreen(meshList[GEO_PLAYBUTTONHOVER], Color(0, 0, 0), 20, 38, 35);
		RenderTextOnScreen(meshList[GEO_TEXT], "Play", Color(1, 0, 1), 2, 17.8, 17);
	}
	else{
		RenderButtonOnScreen(meshList[GEO_PLAYBUTTON], Color(0, 0, 0), 20, 38, 35);
		RenderTextOnScreen(meshList[GEO_TEXT], "Play", Color(1, 0, 1), 2, 17.8, 17);
	}

	//Instruction Button
	if (!clickChk && SharedData::GetInstance()->m_newX >= Application::width * 0.3479 && SharedData::GetInstance()->m_newX <= Application::width * 0.5948
		&& SharedData::GetInstance()->m_newY >= Application::height * 0.4482  && SharedData::GetInstance()->m_newY <= Application::height * 0.499) {
			{
				RenderButtonOnScreen(meshList[GEO_BUTTONHOVER], Color(0, 0, 0), 20, 38, 31);
				RenderTextOnScreen(meshList[GEO_TEXT], "Instructions", Color(1, 0, 1), 2, 15.5, 15);
			}
	}
	else{
		RenderButtonOnScreen(meshList[GEO_BUTTON], Color(0, 0, 0), 20, 38, 31);
		RenderTextOnScreen(meshList[GEO_TEXT], "Instructions", Color(1, 0, 1), 2, 15.5, 15);
	}

	//Credit Button
	if (!clickChk && SharedData::GetInstance()->m_newX >= Application::width * 0.3479 && SharedData::GetInstance()->m_newX <= Application::width * 0.5948
		&& SharedData::GetInstance()->m_newY >= Application::height * 0.5132 && SharedData::GetInstance()->m_newY <= Application::height * 0.5631) {
			{
				RenderButtonOnScreen(meshList[GEO_BUTTONHOVER], Color(0, 0, 0), 20, 38, 27);
				RenderTextOnScreen(meshList[GEO_TEXT], "Credits", Color(1, 0, 1), 2, 17, 13);
			}
	}
	else{
		RenderButtonOnScreen(meshList[GEO_BUTTON], Color(0, 0, 0), 20, 38, 27);
		RenderTextOnScreen(meshList[GEO_TEXT], "Credits", Color(1, 0, 1), 2, 17, 13);
	}
	//Exit Button
	if (!clickChk && SharedData::GetInstance()->m_newX >= Application::width * 0.3479 && SharedData::GetInstance()->m_newX <= Application::width * 0.5948
		&& SharedData::GetInstance()->m_newY >= Application::height * 0.579 && SharedData::GetInstance()->m_newY <= Application::height * 0.6308) {
			{
				RenderButtonOnScreen(meshList[GEO_BUTTONHOVER], Color(0, 0, 0), 20, 38, 23);
				RenderTextOnScreen(meshList[GEO_TEXT], "Quit", Color(1, 0, 1), 2, 17.7, 11);
			}
	}
	else{
		RenderButtonOnScreen(meshList[GEO_BUTTON], Color(0, 0, 0), 20, 38, 23);
		RenderTextOnScreen(meshList[GEO_TEXT], "Quit", Color(1, 0, 1), 2, 17.7, 11);
	}

	RenderTextOnScreen(meshList[GEO_TEXT], " Le Space Invaderz", Color(0.8, 0.3, 0), 3, 6, 17);

	int x, y;
	Application::GetScreenSize(x, y);
}

/****************************************************************************/
/*!
\brief
Render Instructions Menu state


\return
Resulting in Instructions menu being rendered
*/
/****************************************************************************/

void mainMenu::InstructionState()
{
	clickChk = false;
	onClicked = false;
	buttonchk = 0;

	readTxtFile("Text//instructions.txt");

	RenderTitleOnScreen(meshList[GEO_MENUBAR], Color(0, 0, 0), 23, 12.5, 57);
	RenderTextOnScreen(meshList[GEO_TEXT], "INSTRUCTIONS :", Color(0, 1, 1), 2, 2, 28);

	if (SharedData::GetInstance()->m_newX >= Application::width * 0.7354 && SharedData::GetInstance()->m_newX <= Application::width * 0.9869
		&& SharedData::GetInstance()->m_newY >= Application::height * 0.8286 && SharedData::GetInstance()->m_newY <= Application::height * 0.8945){
		RenderButtonOnScreen(meshList[GEO_EXITBUTTONHOVER], Color(0, 0, 0), 20, 69.5, 7);
		RenderTextOnScreen(meshList[GEO_TEXT], "Back to Main", Color(1, 0, 1), 2, 30.8, 3);
	}
	else
		RenderButtonOnScreen(meshList[GEO_EXITBUTTON], Color(0, 0, 0), 20, 69.5, 7);
	RenderTextOnScreen(meshList[GEO_TEXT], "Back to Main", Color(1, 0, 1), 2, 30.8, 3);
<<<<<<< 5496926e8ebdb65c2951e20a3bdd98c2a3b6ad96

}

/****************************************************************************/
/*!
\brief
Render Credits Menu state

=======
>>>>>>> 4ab91ee0b093873e988d7754e88d6eaf30295ff2

\return
Resulting in Credits menu being rendered
*/
/****************************************************************************/

void mainMenu::CreditState()
{
	clickChk = false;
	onClicked = false;
	buttonchk = 0;

	readTxtFile("Text//credits.txt");

	RenderTitleOnScreen(meshList[GEO_MENUBAR], Color(0, 0, 0), 15, 9, 57);
	RenderTextOnScreen(meshList[GEO_TEXT], "CREDITS :", Color(0, 1, 1), 2, 2, 28);

	if (SharedData::GetInstance()->m_newX >= Application::width * 0.7354 && SharedData::GetInstance()->m_newX <= Application::width * 0.9869
		&& SharedData::GetInstance()->m_newY >= Application::height * 0.8286 && SharedData::GetInstance()->m_newY <= Application::height * 0.8945){
		RenderButtonOnScreen(meshList[GEO_EXITBUTTONHOVER], Color(0, 0, 0), 20, 69.5, 7);
		RenderTextOnScreen(meshList[GEO_TEXT], "Back to Main", Color(1, 0, 1), 2, 30.8, 3);
	}
	else
		RenderButtonOnScreen(meshList[GEO_EXITBUTTON], Color(0, 0, 0), 20, 69.5, 7);
	RenderTextOnScreen(meshList[GEO_TEXT], "Back to Main", Color(1, 0, 1), 2, 30.8, 3);

}

/****************************************************************************/
/*!
\brief
Exits the program


\return
Resulting in program being exited
*/
/****************************************************************************/

void mainMenu::Exit()
{
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
}