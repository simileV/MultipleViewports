#include "Setup_texShaders.h"

void proInit()
{
	myAbj.allPro.push_back({ "pTri", glCreateProg("triV.glsl", "", "triF.glsl") });
}

GLuint glCreateProg(string vIn, string gIn, string fIn)
{
	auto pathGLSL = "./shaders/";

	auto vTemp = pathGLSL + vIn;
	const auto *vFile = vTemp.c_str();

	auto gTemp = pathGLSL + gIn;
	const auto *gFile = gTemp.c_str();

	auto fTemp = pathGLSL + fIn;
	const auto *fFile = fTemp.c_str();

	//
	auto proC = glCreateProgram();
	GLuint shaderV, shaderG, shaderF;

	if (vFile)
	{
		shaderV = glCreateShaderStage(vFile, GL_VERTEX_SHADER);

		if (!shaderV)
			return 0;

		glAttachShader(proC, shaderV);
	}

	if (gIn != "")
	{
		shaderG = glCreateShaderStage(gFile, GL_GEOMETRY_SHADER);

		if (!shaderG)
			return 0;

		glAttachShader(proC, shaderG);
	}

	if (fFile)
	{
		shaderF = glCreateShaderStage(fFile, GL_FRAGMENT_SHADER);

		if (!shaderF)
			return 0;

		glAttachShader(proC, shaderF);
	}

	glLinkProgram(proC);
	auto link_ok = GL_FALSE;
	glGetProgramiv(proC, GL_LINK_STATUS, &link_ok);

	if (!link_ok)
	{
		fprintf(stderr, "glLinkProgram:");
		glShaderError(proC);
		glDeleteProgram(proC);
		return 0;
	}

	glDetachShader(proC, shaderV);
	glDeleteShader(shaderV);

	if (gIn != "")
	{
		glDetachShader(proC, shaderG);
		glDeleteShader(shaderG);
	}

	glDetachShader(proC, shaderF);
	glDeleteShader(shaderF);

	return proC;
}

GLuint glCreateShaderStage(const char *file, GLenum type)
{
	const auto *source = glShaderRead(file);

	if (source == 0)
	{
		fprintf(stderr, "Error opening %s: ", file);
		perror("");

		return 0;
	}

	auto shader = glCreateShader(type);
	glShaderSource(shader, 1, &source, 0);

	free((void*)source);

	//static char* incPaths[] = { "/" };
	//glCompileShaderIncludeARB(shader, 1, incPaths, NULL);
	glCompileShader(shader);

	auto compile_ok = GL_FALSE;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compile_ok);

	if (compile_ok == GL_FALSE) // error here
	{
		fprintf(stderr, "%s:", file);
		glShaderError(shader);
		glDeleteShader(shader);

		return 0;
	}

	return shader;
}

char* glShaderRead(const char *file)
{
	auto *input = fopen(file, "rb");

	if (!input)
	{
		string unloadedShader = string(file);
		cout << "input prob in glShaderRead() for " << unloadedShader << endl;
		return 0;
	}

	if (fseek(input, 0, SEEK_END) == -1)
		return 0;

	auto size = ftell(input);

	if (size == -1)
		return 0;

	if (fseek(input, 0, SEEK_SET) == -1)
		return 0;

	auto *content = (char*)malloc((size_t)size + 1);

	if (content == 0)
		return 0;

	if (!(fread(content, 1, (size_t)size, input)) || ferror(input))
	{
		cout << "error reading shader" << endl;
		free(content);

		return 0;
	}

	fclose(input);
	content[size] = '\0';

	return content;
}

void glShaderError(GLuint object)
{
	auto log_length = 0;

	if (glIsShader(object))
		glGetShaderiv(object, GL_INFO_LOG_LENGTH, &log_length);

	else if (glIsProgram(object))
		glGetProgramiv(object, GL_INFO_LOG_LENGTH, &log_length);

	else
	{
		fprintf(stderr, "printlog: Not a shader or a program\n");

		return;
	}

	auto *log = (char*)malloc(log_length);

	if (glIsShader(object))
		glGetShaderInfoLog(object, log_length, 0, log);

	else if (glIsProgram(object))
		glGetProgramInfoLog(object, log_length, 0, log);

	fprintf(stderr, "%s", log);
	free(log);
}

void glUseProgram2(string name)
{
	bool found = 0;

	for (auto &i : myAbj.allPro)
	{
		if (i.name == name)
		{
			myAbj.pro = i.pro;
			found = 1;
		}
	}

	if (!found)
		cout << "couldn't find pro for : " << name << endl;

	glUseProgram(myAbj.pro);
	myAbj.proN = name;
}