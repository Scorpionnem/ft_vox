/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Light.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 16:04:31 by mbatty            #+#    #+#             */
/*   Updated: 2026/01/07 21:36:30 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ShaderCache.hpp"
#include "MeshCache.hpp"

class	Light
{
	public:
		Light(MeshCache &mshc, ShaderCache &shdc) : _meshes(mshc), _shaders(shdc) {}
		~Light() {}

		void	create(Vec3 pos, Vec3 color)
		{
			_pos = pos;
			_color = color;
			_genMesh();
		}
		void	draw(Mat4 view, Mat4 proj, Vec3 camPos)
		{
			_shader->use();
			_shader->setMat4("uModel", Mat4(1));
			_shader->setMat4("uView", view);
			_shader->setMat4("uProjection", proj);
			_shader->setVec3("uCenter", _pos - camPos);
			_shader->setVec3("uColor", _color);

			_mesh->draw(_shader);
		}
		void	setUniforms(int id, std::shared_ptr<Shader> shader, Vec3 camPos)
		{
			(void)camPos;
			shader->setVec3("uLight[" + std::to_string(id) + "].pos", _pos - camPos);
			shader->setVec3("uLight[" + std::to_string(id) + "].color", _color);

			shader->setFloat("uLight[" + std::to_string(id) + "].contant", _constant);
			shader->setFloat("uLight[" + std::to_string(id) + "].linear", _linear);
			shader->setFloat("uLight[" + std::to_string(id) + "].quadratic", _quadratic);
		}
		void	setPos(Vec3 pos)
		{
			_pos = pos;
		}
	private:
		void	_genMesh()
		{
			const Mesh::Vertex	V1(Vec3(-0.5, 0.5, 0.5), Vec3(), Vec2());
			const Mesh::Vertex	V2(Vec3(0.5, 0.5, 0.5), Vec3(), Vec2());
			const Mesh::Vertex	V6(Vec3(0.5, -0.5, 0.5), Vec3(), Vec2());
			const Mesh::Vertex	V5(Vec3(-0.5, -0.5, 0.5), Vec3(), Vec2());
			Mesh::Face	face1;
			face1.v1 = V5;
			face1.v2 = V2;
			face1.v3 = V1;
			Mesh::Face	face2;
			face2.v1 = V5;
			face2.v2 = V6;
			face2.v3 = V2;

			_mesh = _meshes.gen();
			_shader = _shaders.get("assets/shaders/core/billboard");

			_mesh->addFace("default", face1);
			_mesh->addFace("default", face2);
			_mesh->upload();
		}
		MeshCache				&_meshes;
		ShaderCache				&_shaders;

		Vec3					_pos;
		Vec3					_color;
		float					_constant = 1.0f;
		float					_linear = 0.09f;
		float					_quadratic = 0.032f;

		std::shared_ptr<Shader>	_shader;
		std::shared_ptr<Mesh>	_mesh;
};
