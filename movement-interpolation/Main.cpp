#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_glfw.h"
#include "ImGui/imgui_impl_opengl2.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stdio.h>
#include <memory>
#include <iostream>

#include "Engine/Constnants/WindowConstants.h"
#include "Engine/Engine.h"

//
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void process_input(GLFWwindow* window);

// camera
float last_x = WindowConstants::WIDTH / 2.0f;
float last_y = WindowConstants::HEIGHT / 2.0f;

bool mouse_right_button_down = false;
bool first_mouse = true;

// timing
float delta_time = 0.0f;
float last_frame = 0.0f;

bool show_demo_window = false;

std::shared_ptr<Engine> engine;

int main()
{
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();

	// glfw window creation
	// --------------------
	GLFWwindow* window = glfwCreateWindow(WindowConstants::WIDTH, WindowConstants::HEIGHT, "movement interpolation", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window); 
	glfwSwapInterval(1); // Enable vsync

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);

	// init ImGui
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	ImGui::StyleColorsDark();

	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL2_Init();

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// configure global opengl state
	// -----------------------------
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.635f, 0.682f, 0.6f, 1.0f);
	glEnable(GL_PROGRAM_POINT_SIZE);
	glEnable(GL_SCISSOR_TEST);
	glLineWidth(5);
	glEnable(GL_BLEND); //Enable blending.
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); //Set blending function.

	//init
	engine = std::make_shared<Engine>();

	// render loop
	// -----------
	//
	while (!glfwWindowShouldClose(window))
	{
		// per-frame time logic
		// --------------------
		float currentFrame = glfwGetTime();
		delta_time = currentFrame - last_frame;
		last_frame = currentFrame;

		engine->Update(delta_time);

		glfwPollEvents();

		// render
		// ------
		glScissor(0, 0, WindowConstants::WIDTH, WindowConstants::HEIGHT / 2.0);
		glViewport(0, 0, WindowConstants::WIDTH, WindowConstants::HEIGHT / 2.0f);
		glClearColor(0.635f, 0.682f, 0.6f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		engine->Render(EULER);

		glScissor(0, WindowConstants::HEIGHT / 2, WindowConstants::WIDTH, WindowConstants::HEIGHT / 2.0f);
		glViewport(0, WindowConstants::HEIGHT / 2, WindowConstants::WIDTH, WindowConstants::HEIGHT / 2.0f);
		glClearColor(0.735f, 0.782f, 0.6f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		engine->Render(QUATERNION);

		ImGui_ImplOpenGL2_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		// input
		// -----
		if ((!ImGui::IsRootWindowOrAnyChildFocused() && !ImGui::IsAnyItemActive()))
			process_input(window);

		if (show_demo_window)
			ImGui::ShowDemoWindow();

		// ImGui Rendering
		engine->RenderGui();
		
		ImGui::Render();
		ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());

		glfwMakeContextCurrent(window);
		glfwSwapBuffers(window);
	}

	ImGui_ImplOpenGL2_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();

	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void process_input(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		engine->GetCamera()->ProcessKeyboard(FORWARD, delta_time);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		engine->GetCamera()->ProcessKeyboard(BACKWARD, delta_time);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		engine->GetCamera()->ProcessKeyboard(LEFT, delta_time);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		engine->GetCamera()->ProcessKeyboard(RIGHT, delta_time);
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		engine->GetCamera()->ProcessKeyboard(DOWN, delta_time);
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		engine->GetCamera()->ProcessKeyboard(UP, delta_time);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);

	WindowConstants::WIDTH = width;
	WindowConstants::HEIGHT = height;
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (first_mouse)
	{
		last_x = xpos;
		last_y = ypos;
		first_mouse = false;
	}

	float xoffset = xpos - last_x;
	float yoffset = last_y - ypos; // reversed since y-coordinates go from bottom to top

	last_x = xpos;
	last_y = ypos;

	if (!mouse_right_button_down)
		return;

	engine->GetCamera()->ProcessMouseMovement(xoffset, yoffset);
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_RIGHT)
	{
		if (action == GLFW_PRESS)
			mouse_right_button_down = true;
		else if (action == GLFW_RELEASE)
			mouse_right_button_down = false;
	}
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	engine->GetCamera()->ProcessMouseScroll(yoffset);
}
