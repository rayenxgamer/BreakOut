#include <shader.h>


static GLint ReadAndCompile(const char* path, GLenum type)
{
    FILE *f;
    char *text;
    long len;

    f = fopen(path, "rb");
    if (f == NULL) {
        fprintf(stderr, "error loading shader at %s\n", path);
        exit(1);
    }

    fseek(f, 0, SEEK_END);
    len = ftell(f);
    assert(len > 0);
    fseek(f, 0, SEEK_SET);
    text = calloc(1, len);
    assert(text != NULL);
    fread(text, 1, len, f);
    assert(strlen(text) > 0);
    fclose(f);

    GLuint handle = glCreateShader(type);
    glShaderSource(handle,1, (const GLchar *const *) &text, (const GLint *) &len);
    glCompileShader(handle);

    GLint compiled;
    glGetShaderiv(handle, GL_COMPILE_STATUS, &compiled);

    // Check OpenGL logs if compilation failed
    if (compiled == 0) {
    }

    free(text);
    return handle;}

struct Shader CreateShader(const char* vs_path, const char* fs_path, size_t n, struct VertexAttr attributes[])
{
    struct Shader self;
    self.vs_handle = ReadAndCompile(vs_path, GL_VERTEX_SHADER);
    self.fs_handle = ReadAndCompile(fs_path, GL_FRAGMENT_SHADER);
    self.handle = glCreateProgram();

    glAttachShader(self.handle, self.vs_handle);
    glAttachShader(self.handle, self.fs_handle);

    for (size_t i = 0; i < n; i++) {
        glBindAttribLocation(self.handle, attributes[i].index, attributes[i].name);
    }

    glLinkProgram(self.handle);

    GLint linked;
    glGetProgramiv(self.handle, GL_LINK_STATUS, &linked);

    if (linked == 0) {
        char log[512];
        glGetProgramInfoLog(self.handle, 512, NULL, log);
        fprintf(stderr, "Program linking failed: %s\n", log);
        exit(EXIT_FAILURE);
    }

    return self;
}
void BindShader(struct Shader self)
{
    glUseProgram(self.handle);
}

void DeleteShader(struct Shader self)
{
    glDeleteProgram(self.handle);
    glDeleteShader(self.vs_handle);
    glDeleteShader(self.fs_handle);
}
void Shader_SetFloat(struct Shader self,const char* name, GLfloat num)
{
    glUniform1f(glGetUniformLocation(self.handle, name),num);
}

void Shader_SetBool(struct Shader self, const char* name, bool value)
{
    glUniform1i(glGetUniformLocation(self.handle, name),value);
}

void Shader_SetInt(struct Shader self, const char* name, GLint value)
{
    glUniform1i(glGetUniformLocation(self.handle, name),value);
}

void Shader_SetMat4(struct Shader self, const char* name,mat4 value)
{
    glUniformMatrix4fv(glGetUniformLocation(self.handle, name),1, GL_FALSE, &value[0][0]);
}
void Shader_SetVec3(struct Shader self,const char* name, const vec3 value)
{
    glUniform3fv(glGetUniformLocation(self.handle,name), 1, &value[0]);
}
