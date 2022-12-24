#include <gfx/Window.h>
#include <gfx/Resource.h>

GLFWwindow * Window::m_window = nullptr;

uint32_t Window::m_width = 800, Window::m_height = 600;
float Window::m_mouse_x = 0, Window::m_mouse_y = 0;


double Window::m_delta_time = 0, Window::m_last_time = 0;

std::queue<Keyboard> Window::keys = std::queue<Keyboard>();
std::queue<Mouse> Window::mouse = std::queue<Mouse>();

Window::Window() {}

Window::~Window() {
	glfwTerminate();
}

Window & Window::getInstance() {
    static Window new_window;
    return new_window;
}

void Window::create(const char * name, uint32_t width, uint32_t height) {
    glfwInit();
	glfwInit();
	glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed

	Window::m_width = width;
	Window::m_height = height;
    m_window = glfwCreateWindow(width, height, name, NULL, NULL);

	ASSERT_CB(m_window, glfwTerminate(), "WINDOW::Failed to create GLFW window");
    
	glfwMakeContextCurrent(m_window);

	ASSERT(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress), "WINDOW::Failed to initialize GLAD");

    glViewport(0, 0, width, height);

	glfwSetFramebufferSizeCallback(m_window, _handle_resize);
	glfwSetKeyCallback(m_window, _handle_key);
	glfwSetCursorPosCallback(m_window, _handle_mouse_pos);
	glfwSetMouseButtonCallback(m_window, _handle_mouse_key);

	glfwSwapInterval(5);
}

void Window::loop(void (*init)(void), void (*render)(void), void (*destroy)(void)) {
	ASSERT(init && render && destroy, "WINDOW::Functions are not intialized");

	init();

    Resource::useShader("basic").setUniform("projection", glm::ortho(0.0f, float(Window::m_width), 0.0f, float(Window::m_height)));
    Resource::useShader("text").setUniform("projection", glm::ortho(0.0f, float(Window::m_width), 0.0f, float(Window::m_height)));

	GLCall(glEnable(GL_CULL_FACE));
	GLCall(glEnable(GL_BLEND));
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    while(!glfwWindowShouldClose(m_window)){
		GLCall(glClearColor(0.18823f, 0.039215f, 0.141176f, 1.0f));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));

		float current_time = glfwGetTime();
		Window::m_delta_time = current_time - Window::m_last_time;
		Window::m_last_time = current_time;

		render();

		GLCall(glfwSwapBuffers(m_window));

		Window::keys = std::queue<Keyboard>();
		// Window::mouse = std::queue<Mouse>();
		GLCall(glfwPollEvents());
	    
		GLClearError();
	}

	destroy();
}

void Window::_handle_resize(GLFWwindow* window, int width, int height) {
	Window::m_width = width;
	Window::m_height = height;
    glViewport(0, 0, width, height);
    Resource::useShader("basic").setUniform("projection", glm::ortho(0.0f, float(width), 0.0f, float(height)));
    Resource::useShader("text").setUniform("projection", glm::ortho(0.0f, float(width), 0.0f, float(height)));
}

void Window::_handle_key(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key== GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(Window::m_window, true);

	keys.push({key, scancode, action, mods});
}

void Window::_handle_mouse_key(GLFWwindow* handle, int button, int action, int mods) {

	mouse.push({button, action, mods, Window::m_mouse_x, Window::m_mouse_y, 0, 0});
	// if(mouse.empty()) {	
	// } else {
	// 	auto last = mouse.front();

	// 	last.key = button;
	// 	last.action = action;
	// 	last.mods = mods;
	// 	last.x = Window::m_mouse_x;
	// 	last.y = Window::m_mouse_y;
	// 	mouse.push(last);
	// }
}

void Window::_handle_mouse_pos(GLFWwindow* handle, double x, double y) {
	Window::m_mouse_x = x, Window::m_mouse_y = y;

	// if(mouse.empty()) {
	// 	mouse.push({0, 0, 0, x, y, 0, 0});
	// } else {
	// 	auto last = mouse.front();

	// 	last.dx = x - last.x;
	// 	last.dy = y - last.y;

	// 	last.x = x;
	// 	last.y = y;

	// 	mouse.push(last);
	// }
}
