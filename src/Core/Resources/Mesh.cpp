/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mesh.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 15:32:26 by mbatty            #+#    #+#             */
/*   Updated: 2026/01/13 13:06:21 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Mesh.hpp"

void	Mesh::draw(std::shared_ptr<Shader> shader)
{
	if (_triangleCount == 0)
		return ;

	shader->use();

	for (auto &pair : _materialGroups)
	{
		MaterialGroup	&mtl = pair.second;

		mtl.material.texture = _txm.get("assets/atlas.png");
		if (mtl.material.texture)
		{
			shader->setInt("tex", 0);
			shader->setInt("uMaterial.hasDiffuseTex", 1);
			mtl.material.texture->bind(0);
		}
		else
			shader->setInt("uMaterial.hasDiffuseTex", 0);

		shader->setFloat("uMaterial.opacity", mtl.material.opacity);
		shader->setFloat("uMaterial.shininess", mtl.material.shininess);
		shader->setVec3("uMaterial.ambient", mtl.material.ambient);
		shader->setVec3("uMaterial.diffuse", mtl.material.diffuse);
		shader->setVec3("uMaterial.specular", mtl.material.specular);

		glBindVertexArray(mtl.VAO);
		glDrawArrays(GL_TRIANGLES, 0, mtl.verticesSize);
	}
}

void	Mesh::load(const std::string &path)
{
	std::ifstream	file(path);
	if (!file.is_open())
		throw (std::runtime_error("Failed to open " + path));

	std::string	directory = path.substr(0, path.find_last_of("/"));
	if (path.find_last_of("/") == path.npos)
		directory = "";

	MaterialGroup	*currentMtlGroup = &_materialGroups["default"];

	std::string	line;
	while (std::getline(file, line))
	{
		_lineNumber++;

		line = _preprocessLine(line);
		if (line.empty())
			continue ;

		std::istringstream	iss(line);

		std::string	identifier;

		if (!(iss >> identifier))
			throw std::runtime_error("Failed to get identifier at line " + std::to_string(_lineNumber));

		if (identifier == "v")
			_positionVertices.push_back(_parseVec3(iss));
		else if (identifier == "vn")
			_normalVertices.push_back(_parseVec3(iss));
		else if (identifier == "vt")
			_textureVertices.push_back(_parseVec2(iss));
		else if (identifier == "f")
			_parseFace(currentMtlGroup, iss);
		else if (identifier == "mtllib")
		{
			std::string mtlLibPath = directory + (directory.size() ? "/" : "") + line.substr(identifier.size() + 1);
			_parseMtlLib(mtlLibPath);
		}
		else if (identifier == "usemtl")
		{
			std::string mtlName = line.substr(identifier.size() + 1);
			currentMtlGroup = &_materialGroups[mtlName];
		}
		else
			{}
	}
}

void	Mesh::upload()
{
	if (_triangleCount == 0)
		return ;

	if (uploaded)
		unlink();
	uploaded = true;
	for (auto &pair : _materialGroups)
	{
		MaterialGroup	&mtl = pair.second;

		glGenVertexArrays(1, &mtl.VAO);
		glGenBuffers(1, &mtl.VBO);

		glBindVertexArray(mtl.VAO);

		glBindBuffer(GL_ARRAY_BUFFER, mtl.VBO);
		glBufferData(GL_ARRAY_BUFFER, mtl.vertices.size() * sizeof(Vertex), mtl.vertices.data(), GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, pos));
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
		glEnableVertexAttribArray(1);

		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));
		glEnableVertexAttribArray(2);

		glBindVertexArray(0);

		mtl.verticesSize = mtl.vertices.size();
		mtl.vertices.clear();
		mtl.vertices.shrink_to_fit();
	}
}

void	Mesh::_parseFace(MaterialGroup *mtlGroup, std::istringstream &iss)
{
	std::string	token;
	std::vector<FaceVertex>	faceVertices;

	while (iss >> token)
	{
		std::istringstream	iss2(token);

		std::string	positionStr, textureStr, normalStr;

		std::getline(iss2, positionStr, '/');
		std::getline(iss2, textureStr, '/');
		iss2 >> normalStr;

		if (positionStr.empty())
			throw std::runtime_error("No position in face at line " + std::to_string(_lineNumber));

		int	positionVert, textureVert = -1, normalVert = -1;

		try {
			positionVert = std::stoi(positionStr) - 1;
			if (!textureStr.empty())
				textureVert = std::stoi(textureStr) - 1;
			if (!normalStr.empty())
				normalVert = std::stoi(normalStr) - 1;
		} catch (const std::exception &e) {
			throw std::runtime_error("Invalid index format in face at line " + std::to_string(_lineNumber));
		}

		faceVertices.push_back(FaceVertex(positionVert, textureVert, normalVert));
	}

	if (faceVertices.size() < 3)
		throw std::runtime_error("Face with less than 3 vertices at line " + std::to_string(_lineNumber));

	for (size_t i = 1; i + 1 < faceVertices.size(); ++i)
	{
		_triangleCount++;

		Face	face;

		FaceVertex	fv1 = faceVertices[0];
		FaceVertex	fv2 = faceVertices[i];
		FaceVertex	fv3 = faceVertices[i + 1];

		if (fv1.pos < 0 || fv2.pos < 0 || fv3.pos < 0)
			throw std::runtime_error("Invalid pos index in face at line " + std::to_string(_lineNumber));
		if (fv1.pos > (int)_positionVertices.size() - 1 || fv2.pos > (int)_positionVertices.size() - 1 || fv3.pos > (int)_positionVertices.size() - 1)
			throw std::runtime_error("Invalid pos index in face at line " + std::to_string(_lineNumber));
		face.v1.pos = _positionVertices[fv1.pos];
		face.v2.pos = _positionVertices[fv2.pos];
		face.v3.pos = _positionVertices[fv3.pos];

		if (fv1.uv >= 0 || fv2.uv >= 0 || fv3.uv >= 0)
		{
			if (fv1.uv > (int)_textureVertices.size() - 1 || fv2.uv > (int)_textureVertices.size() - 1 || fv3.uv > (int)_textureVertices.size() - 1)
				throw std::runtime_error("Invalid uv index in face at line " + std::to_string(_lineNumber));
			face.v1.uv = _textureVertices[fv1.uv];
			face.v2.uv = _textureVertices[fv2.uv];
			face.v3.uv = _textureVertices[fv3.uv];
		}

		if (fv1.normal >= 0 || fv2.normal >= 0 || fv3.normal >= 0)
		{
			if (fv1.normal > (int)_normalVertices.size() - 1 || fv2.normal > (int)_normalVertices.size() - 1 || fv3.normal > (int)_normalVertices.size() - 1)
				throw std::runtime_error("Invalid normal index in face at line " + std::to_string(_lineNumber));
			face.v1.normal = _normalVertices[fv1.normal];
			face.v2.normal = _normalVertices[fv2.normal];
			face.v3.normal = _normalVertices[fv3.normal];
		}

		mtlGroup->vertices.push_back(face.v1);
		mtlGroup->vertices.push_back(face.v2);
		mtlGroup->vertices.push_back(face.v3);
	}
}

void	Mesh::_parseMtlLib(const std::string &path)
{
	std::ifstream	file(path);
	if (!file.is_open())
		throw (std::runtime_error("Failed to open " + path));

	Material	*currentMaterial = &_materialGroups["default"].material;

	std::string	line;
	uint32_t	lineNumber = 0;
	while (std::getline(file, line))
	{
		_lineNumber++;

		line = _preprocessLine(line);
		if (line.empty())
			continue ;

		std::istringstream	iss(line);

		std::string	identifier;

		if (!(iss >> identifier))
			throw std::runtime_error("Failed to get identifier at line " + std::to_string(lineNumber));

		if (identifier == "Ka")
			currentMaterial->ambient = _parseVec3(iss);
		else if (identifier == "Kd")
			currentMaterial->diffuse = _parseVec3(iss);
		else if (identifier == "Ks")
			currentMaterial->specular= _parseVec3(iss);
		else if (identifier == "Ns")
			currentMaterial->shininess = _parseFloat(iss);
		else if (identifier == "d" || identifier == "Tr")
			currentMaterial->opacity = _parseFloat(iss);
		else if (identifier == "newmtl")
		{
			std::string mtlName = line.substr(identifier.size() + 1);
			currentMaterial = &_materialGroups[mtlName].material;
		}
		else if (identifier == "map_Kd")
		{
			std::string	directory = path.substr(0, path.find_last_of("/"));
			if (path.find_last_of("/") == path.npos)
				directory = "";

			std::string texPath = directory + (directory.size() ? "/" : "") + line.substr(identifier.size() + 1);

			currentMaterial->texture = _txm.get(texPath);
		}
		else
			{}
	}
}

Vec3	Mesh::_parseVec3(std::istringstream &iss)
{
	double	x, y, z;

	if (!(iss >> x >> y >> z))
		throw std::runtime_error("Failed to get vec3 at line " + std::to_string(_lineNumber));

	return (Vec3(x, y, z));
}

Vec2	Mesh::_parseVec2(std::istringstream &iss)
{
	double	x, y;

	if (!(iss >> x >> y))
		throw std::runtime_error("Failed to get vec2 at line " + std::to_string(_lineNumber));

	return (Vec2(x, y));
}

float	Mesh::_parseFloat(std::istringstream &iss)
{
	double	val;

	if (!(iss >> val))
		throw std::runtime_error("Failed to get float at line " + std::to_string(_lineNumber));

	return (val);
}

int	is_whitespace(char c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

std::string	Mesh::_preprocessLine(const std::string &line)
{
	std::string	res;

	res = line.substr(0, line.find('#'));
	res = res.substr(0, res.find('\r'));
	return (res);
}
