// #include <glimac/Text2D.hpp>

// using namespace glimac;
// unsigned int Text2DTextureID;
// unsigned int Text2DVertexBufferID;
// unsigned int Text2DUVBufferID;
// unsigned int Text2DShaderID;
// unsigned int Text2DUniformID;

// // GLuint loadDDS(const char * imagepath){

// // 	unsigned char header[124];

// // 	ifstream fp(imagepath);
 
// // 	/* try to open the file */ 
// // 	if (fp == NULL){
// // 		printf("%s could not be opened. Are you in the right directory ? Don't forget to read the FAQ !\n", imagepath); getchar(); 
// // 		return 0;
// // 	}
   
// // 	/* verify the type of file */ 
// // 	char filecode[4]; 
// // 	fread(filecode, 1, 4, fp); 
// // 	if (strncmp(filecode, "DDS ", 4) != 0) { 
// // 		fclose(fp); 
// // 		return 0; 
// // 	}
	
// // 	/* get the surface desc */ 
// // 	fread(&header, 124, 1, fp); 

// // 	unsigned int height      = *(unsigned int*)&(header[8 ]);
// // 	unsigned int width	     = *(unsigned int*)&(header[12]);
// // 	unsigned int linearSize	 = *(unsigned int*)&(header[16]);
// // 	unsigned int mipMapCount = *(unsigned int*)&(header[24]);
// // 	unsigned int fourCC      = *(unsigned int*)&(header[80]);

 
// // 	unsigned char * buffer;
// // 	unsigned int bufsize;
// // 	/* how big is it going to be including all mipmaps? */ 
// // 	bufsize = mipMapCount > 1 ? linearSize * 2 : linearSize; 
// // 	buffer = (unsigned char*)malloc(bufsize * sizeof(unsigned char)); 
// // 	fread(buffer, 1, bufsize, fp); 
// // 	/* close the file pointer */ 
// // 	fclose(fp);

// // 	unsigned int components  = (fourCC == FOURCC_DXT1) ? 3 : 4; 
// // 	unsigned int format;
// // 	switch(fourCC) 
// // 	{ 
// // 	case FOURCC_DXT1: 
// // 		format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT; 
// // 		break; 
// // 	case FOURCC_DXT3: 
// // 		format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT; 
// // 		break; 
// // 	case FOURCC_DXT5: 
// // 		format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT; 
// // 		break; 
// // 	default: 
// // 		free(buffer); 
// // 		return 0; 
// // 	}

// // 	// Create one OpenGL texture
// // 	GLuint textureID;
// // 	glGenTextures(1, &textureID);

// // 	// "Bind" the newly created texture : all future texture functions will modify this texture
// // 	glBindTexture(GL_TEXTURE_2D, textureID);
// // 	glPixelStorei(GL_UNPACK_ALIGNMENT,1);	
	
// // 	unsigned int blockSize = (format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT) ? 8 : 16; 
// // 	unsigned int offset = 0;

// // 	/* load the mipmaps */ 
// // 	for (unsigned int level = 0; level < mipMapCount && (width || height); ++level) 
// // 	{ 
// // 		unsigned int size = ((width+3)/4)*((height+3)/4)*blockSize; 
// // 		glCompressedTexImage2D(GL_TEXTURE_2D, level, format, width, height,  
// // 			0, size, buffer + offset); 
	 
// // 		offset += size; 
// // 		width  /= 2; 
// // 		height /= 2; 

// // 		// Deal with Non-Power-Of-Two textures. This code is not included in the webpage to reduce clutter.
// // 		if(width < 1) width = 1;
// // 		if(height < 1) height = 1;

// // 	} 

// // 	free(buffer); 

// // 	return textureID;


// // }

// void initText2D(const char * texturePath){

// 	// Initialize texture
// 	//Text2DTextureID = loadDDS(texturePath);

// 	std::unique_ptr<Image> textureImage = loadImage(texturePath);
//     if(textureImage != NULL) std::cout << "La texture de test est bien chargée !" << std::endl;
    
//     GLuint Text2DTextureID;
//     glGenTextures(1, &Text2DTextureID);
//     glBindTexture(GL_TEXTURE_2D, Text2DTextureID);
//     glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureImage->getWidth(), textureImage->getHeight(), 0, GL_RGBA, GL_FLOAT, textureImage->getPixels());

//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

//     glBindTexture(GL_TEXTURE_2D, 0);

// 	// Initialize VBO
// 	glGenBuffers(1, &Text2DVertexBufferID);
// 	glGenBuffers(1, &Text2DUVBufferID);

// 	// Initialize Shader
// 	Text2DShaderID = LoadShaders( "shaders/TextVertexShader.vs.glsl", "shaders/TextVertexShader.fs.glsl" );

// 	// Initialize uniforms' IDs
// 	Text2DUniformID = glGetUniformLocation( Text2DShaderID, "myTextureSampler" );

// }

// void printText2D(const char * text, int x, int y, int size){

// 	unsigned int length = strlen(text);

// 	// Fill buffers
// 	std::vector<glm::vec2> vertices;
// 	std::vector<glm::vec2> UVs;
// 	for ( unsigned int i=0 ; i<length ; i++ ){
		
// 		glm::vec2 vertex_up_left    = glm::vec2( x+i*size     , y+size );
// 		glm::vec2 vertex_up_right   = glm::vec2( x+i*size+size, y+size );
// 		glm::vec2 vertex_down_right = glm::vec2( x+i*size+size, y      );
// 		glm::vec2 vertex_down_left  = glm::vec2( x+i*size     , y      );

// 		vertices.push_back(vertex_up_left   );
// 		vertices.push_back(vertex_down_left );
// 		vertices.push_back(vertex_up_right  );

// 		vertices.push_back(vertex_down_right);
// 		vertices.push_back(vertex_up_right);
// 		vertices.push_back(vertex_down_left);

// 		char character = text[i];
// 		float uv_x = (character%16)/16.0f;
// 		float uv_y = (character/16)/16.0f;

// 		glm::vec2 uv_up_left    = glm::vec2( uv_x           , uv_y );
// 		glm::vec2 uv_up_right   = glm::vec2( uv_x+1.0f/16.0f, uv_y );
// 		glm::vec2 uv_down_right = glm::vec2( uv_x+1.0f/16.0f, (uv_y + 1.0f/16.0f) );
// 		glm::vec2 uv_down_left  = glm::vec2( uv_x           , (uv_y + 1.0f/16.0f) );
// 		UVs.push_back(uv_up_left   );
// 		UVs.push_back(uv_down_left );
// 		UVs.push_back(uv_up_right  );

// 		UVs.push_back(uv_down_right);
// 		UVs.push_back(uv_up_right);
// 		UVs.push_back(uv_down_left);
// 	}
// 	glBindBuffer(GL_ARRAY_BUFFER, Text2DVertexBufferID);
// 	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec2), &vertices[0], GL_STATIC_DRAW);
// 	glBindBuffer(GL_ARRAY_BUFFER, Text2DUVBufferID);
// 	glBufferData(GL_ARRAY_BUFFER, UVs.size() * sizeof(glm::vec2), &UVs[0], GL_STATIC_DRAW);

// 	// Bind shader
// 	glUseProgram(Text2DShaderID);

// 	// Bind texture
// 	glActiveTexture(GL_TEXTURE0);
// 	glBindTexture(GL_TEXTURE_2D, Text2DTextureID);
// 	// Set our "myTextureSampler" sampler to user Texture Unit 0
// 	glUniform1i(Text2DUniformID, 0);

// 	// 1rst attribute buffer : vertices
// 	glEnableVertexAttribArray(0);
// 	glBindBuffer(GL_ARRAY_BUFFER, Text2DVertexBufferID);
// 	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0 );

// 	// 2nd attribute buffer : UVs
// 	glEnableVertexAttribArray(1);
// 	glBindBuffer(GL_ARRAY_BUFFER, Text2DUVBufferID);
// 	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0 );

// 	glEnable(GL_BLEND);
// 	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

// 	// Draw call
// 	glDrawArrays(GL_TRIANGLES, 0, vertices.size() );

// 	glDisable(GL_BLEND);

// 	glDisableVertexAttribArray(0);
// 	glDisableVertexAttribArray(1);

// }

// void cleanupText2D(){

// 	// Delete buffers
// 	glDeleteBuffers(1, &Text2DVertexBufferID);
// 	glDeleteBuffers(1, &Text2DUVBufferID);

// 	// Delete texture
// 	glDeleteTextures(1, &Text2DTextureID);

// 	// Delete shader
// 	glDeleteProgram(Text2DShaderID);
// }

// GLuint LoadShaders(const char * vertex_file_path,const char * fragment_file_path){

// 	// Create the shaders
// 	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
// 	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

// 	// Read the Vertex Shader code from the file
// 	std::string VertexShaderCode;
// 	std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
// 	if(VertexShaderStream.is_open()){
// 		std::string Line = "";
// 		while(getline(VertexShaderStream, Line))
// 			VertexShaderCode += "\n" + Line;
// 		VertexShaderStream.close();
// 	}else{
// 		printf("Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n", vertex_file_path);
// 		getchar();
// 		return 0;
// 	}

// 	// Read the Fragment Shader code from the file
// 	std::string FragmentShaderCode;
// 	std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
// 	if(FragmentShaderStream.is_open()){
// 		std::string Line = "";
// 		while(getline(FragmentShaderStream, Line))
// 			FragmentShaderCode += "\n" + Line;
// 		FragmentShaderStream.close();
// 	}

// 	GLint Result = GL_FALSE;
// 	int InfoLogLength;


// 	// Compile Vertex Shader
// 	printf("Compiling shader : %s\n", vertex_file_path);
// 	char const * VertexSourcePointer = VertexShaderCode.c_str();
// 	glShaderSource(VertexShaderID, 1, &VertexSourcePointer , NULL);
// 	glCompileShader(VertexShaderID);

// 	// Check Vertex Shader
// 	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
// 	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
// 	if ( InfoLogLength > 0 ){
// 		std::vector<char> VertexShaderErrorMessage(InfoLogLength+1);
// 		glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
// 		printf("%s\n", &VertexShaderErrorMessage[0]);
// 	}



// 	// Compile Fragment Shader
// 	printf("Compiling shader : %s\n", fragment_file_path);
// 	char const * FragmentSourcePointer = FragmentShaderCode.c_str();
// 	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer , NULL);
// 	glCompileShader(FragmentShaderID);

// 	// Check Fragment Shader
// 	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
// 	glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
// 	if ( InfoLogLength > 0 ){
// 		std::vector<char> FragmentShaderErrorMessage(InfoLogLength+1);
// 		glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
// 		printf("%s\n", &FragmentShaderErrorMessage[0]);
// 	}



// 	// Link the program
// 	printf("Linking program\n");
// 	GLuint ProgramID = glCreateProgram();
// 	glAttachShader(ProgramID, VertexShaderID);
// 	glAttachShader(ProgramID, FragmentShaderID);
// 	glLinkProgram(ProgramID);

// 	// Check the program
// 	glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
// 	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
// 	if ( InfoLogLength > 0 ){
// 		std::vector<char> ProgramErrorMessage(InfoLogLength+1);
// 		glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
// 		printf("%s\n", &ProgramErrorMessage[0]);
// 	}

	
// 	glDetachShader(ProgramID, VertexShaderID);
// 	glDetachShader(ProgramID, FragmentShaderID);
	
// 	glDeleteShader(VertexShaderID);
// 	glDeleteShader(FragmentShaderID);

// 	return ProgramID;
// }