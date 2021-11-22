#include "Texture.h"

Texture::Texture() {
	textureID = 0;
	width = 0;
	height = 0;
	bitDepth = 0;
	fileLocation = NULL;
}

Texture::Texture(char* fileName) {
	textureID = 0;
	width = 0;
	height = 0;
	bitDepth = 0;
	fileLocation = fileName;
}

void Texture::loadTexture() {
	unsigned char* texData = stbi_load(fileLocation, &width, &height, &bitDepth, 0);
	if (!texData) {
		printf("Erro ao carregar a imagem %s", fileLocation);
	}

	glGenTextures(1, &textureID); //Gera um endere�o de textura na mem�ria
	glBindTexture(GL_TEXTURE_2D, textureID); //Bind do tamanho do endere�o na mem�ria

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // Eixo X
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // Eixo Y

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //Filtro para curta dist�ncia
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //Filtro para longa dist�ncia

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData); //Carrega a imagem na mem�ria
	glGenerateMipmap(GL_TEXTURE_2D); //Criando um MipMap

	glBindTexture(GL_TEXTURE_2D, 0); //Remove o endere�o do apontamento de mem�ria
	stbi_image_free(texData); //Libera espa�o na mem�ria ram
}

void Texture::useTexture() {
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID);
}

void Texture::clearTexture() {
	glDeleteTextures(1, &textureID);
}

Texture::~Texture() {
	Texture::clearTexture();
	textureID = 0;
	width = 0;
	height = 0;
	bitDepth = 0;
	fileLocation = NULL;
}