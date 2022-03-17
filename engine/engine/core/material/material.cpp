#include "material.h"
// Include std library
#include <functional>

// Include third party library
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/matrix.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

// Include tara library
#include "../shader/shader.h"
#include "../texture/texture.h"

#pragma region Implement Macro
#define MATERIAL_UNIFORM_BLOCK_SETTER_IMPLE(name, type)\
	void MaterialUniformBlock::Set##name (const char* varName, type v, const int index) {\
		if (m_data.count(varName)) {\
			ShaderUniformContent* slot = &m_data[varName][index];\
			glBindBuffer(GL_UNIFORM_BUFFER, m_blockID);\
			glBufferSubData(GL_UNIFORM_BUFFER, slot->Location, slot->Size, &v);\
			glBindBuffer(GL_UNIFORM_BUFFER, 0);\
		}\
	}\

#define MATERIAL_UNIFORM_BLOCK_SETTER_GLM_IMPLE(name, type)\
	void MaterialUniformBlock::Set##name (const char* varName, type v, const int index) {\
		if (m_data.count(varName) > 0) {\
			ShaderUniformContent* slot = &m_data[varName][index];\
			glBindBuffer(GL_UNIFORM_BUFFER, m_blockID);\
			glBufferSubData(GL_UNIFORM_BUFFER, slot->Location, slot->Size, glm::value_ptr(v));\
			glBindBuffer(GL_UNIFORM_BUFFER, 0);\
		}\
	}\

#define MATERIAL_UNIFORM_BLOCK_GETTER_IMPLE(name, type)\
	const type MaterialUniformBlock::Get##name (const char* varName, const int index) {\
		return type ();\
	}\

#define MATERIAL_FUNCTION_SETTER_IMPLE(name, type)\
	void Material::Set##name (const char* fullname, type v, const int32_t index) {\
		std::pair<std::string, std::string> detail = GetUniformNameDetail(fullname);\
		Set##name(detail.first.c_str(), detail.second.c_str(), v, index);\
	}\
	void Material::Set##name (const char* blockname, const char* varName, type v, const int32_t index) {\
		if (m_blocks.count(blockname)) {\
			m_blocks.at(blockname)->Set##name (varName, v, index);\
		}\
	}\

#define MATERIAL_FUNCTION_GETTER_IMPLE(name, type)\
	const type Material::Get##name (const char* fullname, const int32_t index) {\
		std::pair<std::string, std::string> detail = GetUniformNameDetail(fullname);\
		return Get##name(detail.first.c_str(), detail.second.c_str(), index);\
	}\
	const type Material::Get##name (const char* blockname, const char* varName, const int32_t index) {\
		if (m_blocks.count(blockname)) {\
			m_blocks.at(blockname)->Get##name (varName, index);\
		}\
		return type ();\
	}\

#pragma endregion

namespace Tara {
	struct UniformStructData
	{
		UniformStructData(std::string n, int32_t loc, size_t si) : name(n), location(loc), size(si){}
		std::string name;
		int32_t location;
		size_t size;
	};
	/*
		Summary:
			This will prevent material create buildin uniform block to use.
			Register the name of the uniform block prevent this action.
	*/
	const std::vector<std::string> ignoreUniformBlock = {
		"Utility",
		"ModelMatrix",
		"LightingData"
	};
	std::pair<int32_t, Texture2D*> Material::lastUseTexture = std::pair<int32_t, Texture2D*>(-1, nullptr);
	const std::map<MaterialBlendMode, int32_t> blendMap = {
		{MaterialBlendMode::Zero, GL_ZERO},
		{MaterialBlendMode::One, GL_ONE},
		{MaterialBlendMode::Src_Color, GL_SRC_COLOR},
		{MaterialBlendMode::One_Minus_Src_Color, GL_ONE_MINUS_SRC_COLOR},
		{MaterialBlendMode::Dst_Color, GL_DST_COLOR},
		{MaterialBlendMode::One_Minus_Dst_Color, GL_ONE_MINUS_DST_COLOR},
		{MaterialBlendMode::Src_Alpha, GL_SRC_ALPHA},
		{MaterialBlendMode::One_Minus_Src_Alpha, GL_ONE_MINUS_SRC_ALPHA},
		{MaterialBlendMode::Dst_Alpha, GL_DST_ALPHA},
		{MaterialBlendMode::One_Minus_Dst_Alpha, GL_ONE_MINUS_DST_ALPHA},
		{MaterialBlendMode::Const_Color, GL_CONSTANT_COLOR},
		{MaterialBlendMode::One_Minus_Const_Color, GL_ONE_MINUS_CONSTANT_COLOR},
		{MaterialBlendMode::Const_Alpha, GL_CONSTANT_ALPHA},
		{MaterialBlendMode::One_Minus_Const_Alpha, GL_ONE_MINUS_CONSTANT_ALPHA},
	};

#pragma region MaterialUniformBlock
	MaterialUniformBlock::MaterialUniformBlock() {
		glGenBuffers(1, &m_blockID);
	}
	MaterialUniformBlock::MaterialUniformBlock(ShaderUniformBlockInformation& blockInformation)
	{
		glGenBuffers(1, &m_blockID);
		m_blockInformation = blockInformation;
		glBindBuffer(GL_UNIFORM_BUFFER, m_blockID);
		glBufferData(GL_UNIFORM_BUFFER, m_blockInformation.Size, NULL, GL_STATIC_DRAW);
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
		for (auto con : m_blockInformation.Content) {
			std::vector<ShaderUniformContent>* data = new std::vector<ShaderUniformContent>();
			data->push_back(con);
			m_data[con.VariableName] = *data;
			TARA_DEBUG("Declara uni content, name: %s, size: %zu, offset: %i", con.VariableName.c_str(), con.Size, con.Location);
			glBindBuffer(GL_UNIFORM_BUFFER, m_blockID);
			glBufferSubData(GL_UNIFORM_BUFFER, con.Location, con.Size, malloc(con.Size));
			glBindBuffer(GL_UNIFORM_BUFFER, 0);
		}
	}
	MaterialUniformBlock::~MaterialUniformBlock()
	{
		TARA_DEBUG_LEVEL("Uniform block destroy! %s", 1, m_blockInformation.BlockName.c_str());
		glDeleteBuffers(1, &m_blockID);
	}

	void MaterialUniformBlock::Update(ShaderUniformBlockInformation updateInfo)
	{
		// Do update apply

		// After done
		m_blockInformation = updateInfo;
	}
	void MaterialUniformBlock::SetToDefault() {

	}

	void MaterialUniformBlock::SetData(const char* varName, void* v, const int index) {
		if (m_data.count(varName)) {
			ShaderUniformContent* slot = &m_data[varName][index];
			glBindBuffer(GL_UNIFORM_BUFFER, m_blockID);
			glBufferSubData(GL_UNIFORM_BUFFER, slot->Location, slot->Size, &v);
			glBindBuffer(GL_UNIFORM_BUFFER, 0);
		}
	}
	MATERIAL_UNIFORM_BLOCK_SETTER_IMPLE(Bool, bool);
	MATERIAL_UNIFORM_BLOCK_SETTER_IMPLE(Int, int32_t);
	MATERIAL_UNIFORM_BLOCK_SETTER_IMPLE(Float, float_t);
	MATERIAL_UNIFORM_BLOCK_SETTER_GLM_IMPLE(Vec2, glm::vec2);
	MATERIAL_UNIFORM_BLOCK_SETTER_GLM_IMPLE(Vec3, glm::vec3);
	MATERIAL_UNIFORM_BLOCK_SETTER_GLM_IMPLE(Vec4, glm::vec4);
	MATERIAL_UNIFORM_BLOCK_SETTER_GLM_IMPLE(Mat3, glm::mat3);
	MATERIAL_UNIFORM_BLOCK_SETTER_GLM_IMPLE(Mat4, glm::mat4);

	MATERIAL_UNIFORM_BLOCK_GETTER_IMPLE(Bool, bool);
	MATERIAL_UNIFORM_BLOCK_GETTER_IMPLE(Int, int32_t);
	MATERIAL_UNIFORM_BLOCK_GETTER_IMPLE(Float, float_t);
	MATERIAL_UNIFORM_BLOCK_GETTER_IMPLE(Vec2, glm::vec2);
	MATERIAL_UNIFORM_BLOCK_GETTER_IMPLE(Vec3, glm::vec3);
	MATERIAL_UNIFORM_BLOCK_GETTER_IMPLE(Vec4, glm::vec4);
	MATERIAL_UNIFORM_BLOCK_GETTER_IMPLE(Mat3, glm::mat3);
	MATERIAL_UNIFORM_BLOCK_GETTER_IMPLE(Mat4, glm::mat4);

	uint32_t MaterialUniformBlock::BlockID()
	{
		return m_blockID;
	}
	uint32_t MaterialUniformBlock::Index()
	{
		return m_blockInformation.Index;
	}
	size_t MaterialUniformBlock::Size()
	{
		return m_blockInformation.Size;
	}
#pragma endregion

#pragma region Material
	Material::Material(Shader& _shader)
	{
		TARA_DEBUG_LEVEL("Material created!", 1);
		TARA_DEBUG_LEVEL("\tMaterial use shader: %s", 1, _shader.Name.c_str());
		m_shader = &_shader;
		Name = m_shader->Name + " Mat";
		TARA_DEBUG_LEVEL("\tMaterial callback register!", 1);
		_shader.RegisterUpdateEvent(this, std::bind(&Material::ShaderUpdateCallback, this));
		TARA_DEBUG_LEVEL("\tAdding material to pool!", 1);
		GetAssetPool().Add(this);
	}
	Material::Material(bool buildin, Shader& _shader) : Material(_shader)
	{
		m_buildIn = buildin;
	}
	Material::~Material()
	{
		TARA_DEBUG_LEVEL("Material destroy! %s", 1, Name.c_str());
		if (m_shader != nullptr) m_shader->UnRegisterUpdateEvent(this);
		std::vector<MaterialUniformBlock*> re = std::vector<MaterialUniformBlock*>();
		for (auto a : m_blocks) {
			if(a.second) re.push_back(a.second);
		}
		m_blocks.clear();
		TARA_DEBUG_LEVEL("\tStart destroy uniform blocks! %s", 1, Name.c_str());
		for (auto a : re) {
			delete a;
		}
		delete m_shader;
	}
	AssetPool<Material>& Material::GetAssetPool()
	{
		return *m_materialPool;
	}
	void Material::MaterialInitialization() {
		if (!m_globalBlocks.count("ModelMatrix")) {
			ShaderUniformBlockInformation ModelMatrix = ShaderUniformBlockInformation();
			ModelMatrix.Content = std::vector<ShaderUniformContent>();
			ModelMatrix.BlockName = "ModelMatrix";
			ModelMatrix.Size = sizeof(glm::mat4) * 2;
			ModelMatrix.Index = 0;

			std::vector<UniformStructData> data = {
				UniformStructData("view", 0, sizeof(glm::mat4)),
				UniformStructData("projection", sizeof(glm::mat4), sizeof(glm::mat4)),
			};
			for (int32_t i = 0; i < data.size(); i++) {
				ShaderUniformContent info = ShaderUniformContent();
				info.Name = "ModelMatrix.";
				info.Name += data[i].name;
				info.Type = ShaderUniformType::Mat4;
				info.TypeName = "mat4";
				info.VariableName = data[i].name;
				info.Location = data[i].location;
				info.Size = data[i].size;
				ModelMatrix.Content.push_back(info);
			}
			MaterialUniformBlock* buffer = new MaterialUniformBlock(ModelMatrix);
			m_globalBlocks["ModelMatrix"] = buffer;
		}
		if (!m_globalBlocks.count("Utility")) {
			ShaderUniformBlockInformation Utility = ShaderUniformBlockInformation();
			Utility.Content = std::vector<ShaderUniformContent>();
			Utility.BlockName = "Utility";
			Utility.Size = sizeof(float) * 2;
			Utility.Index = 1;
			const char* n[2] = { "delta", "time" };
			for (int32_t i = 0; i < 2; i++) {
				ShaderUniformContent info = ShaderUniformContent();
				info.Name = "Utility.";
				info.Name += n[i];
				info.Type = ShaderUniformType::Float;
				info.TypeName = "float";
				info.VariableName = n[i];
				info.Location = i * sizeof(float);
				info.Size = sizeof(float);
				Utility.Content.push_back(info);
			}
			MaterialUniformBlock* buffer = new MaterialUniformBlock(Utility);
			m_globalBlocks["Utility"] = buffer;
		}
		if (!m_globalBlocks.count("LightingData")) {
			ShaderUniformBlockInformation LightData = ShaderUniformBlockInformation();
			LightData.Content = std::vector<ShaderUniformContent>();
			LightData.BlockName = "LightingData";
			LightData.Size = 288;
			LightData.Index = 2;
			std::vector<UniformStructData> data = {
				UniformStructData("ambient", 12, 16),
				UniformStructData("eye", 0, 12),

				UniformStructData("light[0].lightType", 32, 4),
				UniformStructData("light[0].position", 48, 12),
				UniformStructData("light[0].color", 64, 16),
				UniformStructData("light[0].direction", 80, 12),

				UniformStructData("light[1].lightType", 96, 4),
				UniformStructData("light[1].position", 112, 12),
				UniformStructData("light[1].color", 128, 16),
				UniformStructData("light[1].direction", 144, 12),

				UniformStructData("light[2].lightType", 160, 4),
				UniformStructData("light[2].position", 176, 12),
				UniformStructData("light[2].color", 192, 16),
				UniformStructData("light[2].direction", 208, 12),
				
				UniformStructData("light[3].lightType", 224, 4),
				UniformStructData("light[3].position", 240, 12),
				UniformStructData("light[3].color", 256, 16),
				UniformStructData("light[3].direction", 272, 12),
			};
			for (int32_t i = 0; i < data.size(); i++) {
				ShaderUniformContent info = ShaderUniformContent();
				info.VariableName = data[i].name;
				info.Name = "LightingData.";
				info.Name += data[i].name;
				info.Location = data[i].location;
				info.Size = data[i].size;
				LightData.Content.push_back(info);
			}
			MaterialUniformBlock* buffer = new MaterialUniformBlock(LightData);
			m_globalBlocks["LightingData"] = buffer;
		}
		if (!m_globalBlocks.count("LightMatrix")) {
			ShaderUniformBlockInformation LightMatrix = ShaderUniformBlockInformation();
			LightMatrix.Content = std::vector<ShaderUniformContent>();
			LightMatrix.BlockName = "LightMatrix";
			LightMatrix.Size = 320;
			LightMatrix.Index = 3;

			std::vector<UniformStructData> data = {
				UniformStructData("lightMat[0].lightPos", 64, 12),
				UniformStructData("lightMat[0].lightSpaceMatrix", 0, 64),
				UniformStructData("lightMat[1].lightPos", 144, 12),
				UniformStructData("lightMat[1].lightSpaceMatrix", 80, 64),
				UniformStructData("lightMat[2].lightPos", 224, 12),
				UniformStructData("lightMat[2].lightSpaceMatrix", 160, 64),
				UniformStructData("lightMat[3].lightPos", 304, 12),
				UniformStructData("lightMat[3].lightSpaceMatrix", 240, 64),
			};
			for (int32_t i = 0; i < data.size(); i++) {
				ShaderUniformContent info = ShaderUniformContent();
				info.Name = "LightMatrix.";
				info.Name += data[i].name;
				info.VariableName = data[i].name;
				info.Location = data[i].location;
				info.Size = data[i].size;
				LightMatrix.Content.push_back(info);
			}
			MaterialUniformBlock* buffer = new MaterialUniformBlock(LightMatrix);
			m_globalBlocks["LightMatrix"] = buffer;
		}
	}
	Material& Material::Clone()
	{
		Material& m = *new Material(*this);
		m.m_buildIn = false;
		return m;
	}
	void Material::Use()
	{
		if (m_shader == nullptr) {
			m_shader = CommomMaterial.at(CommomMaterialType::Error)->m_shader;
			TARA_ERROR_LEVEL("Material has no shader binding: %s.", 4, Name.c_str());
			return;
		}
		if (!m_shader->Good()) {
			switch (m_shader->CompileState()) {
			case ShaderCompileStage::None:
			case ShaderCompileStage::Failed:
				TARA_ERROR_LEVEL("Material cannot use uncompile shader: %s, %s.", 4, Name.c_str(), m_shader->Name.c_str());
				m_shader = CommomMaterial.at(CommomMaterialType::Error)->m_shader;
				return;
			case ShaderCompileStage::Compiling:
				TARA_ERROR_LEVEL("Material binding with shader which is compiling right now: %s, %s.", 4, Name.c_str(), m_shader->Name.c_str());
				return;
			}
		}

		if (m_config.UseBlend) {
			glEnable(GL_BLEND);
			glBlendFuncSeparate(blendMap.at(m_config.BlendSrc),
				blendMap.at(m_config.BlendDst),
				blendMap.at(m_config.BlendAlphaSrc),
				blendMap.at(m_config.BlendAlphaDst));
		}
		else {
			glDisable(GL_BLEND);
		}

		m_shader->Use();
		MaterialUniformBlock* UUB = m_globalBlocks.at("Utility");
		MaterialUniformBlock* MUB = m_globalBlocks.at("ModelMatrix");
		MaterialUniformBlock* LUB = m_globalBlocks.at("LightingData");
		MaterialUniformBlock* LMB = m_globalBlocks.at("LightMatrix");

		glBindBufferRange(GL_UNIFORM_BUFFER, 0, UUB->BlockID(), 0, UUB->Size());
		switch (m_config.Domain)
		{
		case Tara::MaterialDomain::Surface:
			// ModelMatrix use at position 0
			glBindBufferRange(GL_UNIFORM_BUFFER, 1, MUB->BlockID(), 0, MUB->Size());
			break;
		case Tara::MaterialDomain::PostProcessing:
			break;
		default:
			break;
		}

		switch (m_config.Shaded)
		{
		case Tara::MaterialShadedMode::Unlit:
			break;
		case Tara::MaterialShadedMode::Lit:
			glBindBufferRange(GL_UNIFORM_BUFFER, 2, LMB->BlockID(), 0, LMB->Size());
			glBindBufferRange(GL_UNIFORM_BUFFER, 3, LUB->BlockID(), 0, LUB->Size());
			break;
		default:
			break;
		}

		uint32_t initalValue = m_useBuildinBufferIndex;
		for (auto bl : m_blocks) {
			glBindBufferRange(GL_UNIFORM_BUFFER, initalValue, bl.second->BlockID(), 0, bl.second->Size());
			initalValue++;
		}

		int32_t tex2DCount = m_config.Shaded == Tara::MaterialShadedMode::Lit ? 4 : 0;
		int32_t texCubeCount = m_config.Shaded == Tara::MaterialShadedMode::Lit ? 1 : 0;
		for (auto& it = m_TextureBind.begin(); it != m_TextureBind.end(); it++) {
			std::pair<std::string, std::pair<ShaderUniformType, uint32_t>> buffer = *it;
			int32_t loc = glGetUniformLocation(m_shader->program, it->first.c_str());
			if (loc >= 0) {
				switch (buffer.second.first)
				{
				case ShaderUniformType::Texture2D:
					glUniform1i(loc, tex2DCount);
					UniformTexture2D(it->first.c_str(), it->second.second, tex2DCount);
					tex2DCount++;
					break;
				case ShaderUniformType::TextureCube:
					UniformTextureCube(it->first.c_str(), it->second.second, texCubeCount);
					texCubeCount++;
					break;
				}
			}
		}
	}
	void Material::Unuse()
	{
		m_shader->Unuse();
		glDisable(GL_BLEND);
	}
	Shader& Material::GetShader()
	{
		if (!m_shader) m_shader = CommomMaterial.at(CommomMaterialType::Error)->m_shader;
		return *m_shader;
	}
	MaterialConfig& Material::Config() {
		return m_configbuffer;
	}
	void Material::Apply()
	{	
		m_config = m_configbuffer;
		glUniformBlockBinding(GL_UNIFORM_BUFFER, m_shader->GetUniformBlockIndex("Utility"), 0);

		switch (m_config.Domain)
		{
		case Tara::MaterialDomain::Surface:
			// ModelMatrix use at position 0
			glUniformBlockBinding(GL_UNIFORM_BUFFER, m_shader->GetUniformBlockIndex("ModelMatrix"), 1);
			break;
		case Tara::MaterialDomain::PostProcessing:
			break;
		default:
			break;
		}

		switch (m_config.Shaded)
		{
		case Tara::MaterialShadedMode::Unlit:
			break;
		case Tara::MaterialShadedMode::Lit:
			// LightingData use at position 1
			glUniformBlockBinding(GL_UNIFORM_BUFFER, m_shader->GetUniformBlockIndex("LightMatrix"), 2);
			glUniformBlockBinding(GL_UNIFORM_BUFFER, m_shader->GetUniformBlockIndex("LightingData"), 3);
			break;
		default:
			break;
		}

		// Start index from.
		uint32_t initalValue = m_useBuildinBufferIndex;
		for (auto b : m_blocks) {
			glUniformBlockBinding(m_shader->program, b.second->Index(), initalValue);
			initalValue++;
		}
	}
	void Material::GUI()
	{

	}

	void Material::SetTexture2D(const char* name, Texture2D* v) { 
		if (v != nullptr) m_TextureBind[name] = std::pair<ShaderUniformType, uint32_t>(ShaderUniformType::Texture2D, v->m_textureID);
		else RemoveTexture(name);
	}
	void Material::SetTexture2D(const char* name, uint32_t v) {
		if (v >= 0) m_TextureBind[name] = std::pair<ShaderUniformType, uint32_t>(ShaderUniformType::Texture2D, v);
		else RemoveTexture(name);
	}
	void Material::SetTextureCube(const char* name, TextureCube* v) {
		if (v != nullptr) m_TextureBind[name] = std::pair<ShaderUniformType, uint32_t>(ShaderUniformType::TextureCube, v->m_textureID);
		else RemoveTexture(name);
	}
	void Material::SetTextureCube(const char* name, uint32_t v) {
		if (v >= 0) m_TextureBind[name] = std::pair<ShaderUniformType, uint32_t>(ShaderUniformType::TextureCube, v);
		else RemoveTexture(name);
	}
	void Material::RemoveTexture(const char* name) { 
		if (m_TextureBind.count(name)) m_TextureBind.erase(m_TextureBind.find(name), m_TextureBind.end());
	}

	MATERIAL_FUNCTION_SETTER_IMPLE(Bool, bool);
	MATERIAL_FUNCTION_SETTER_IMPLE(Int, int);
	MATERIAL_FUNCTION_SETTER_IMPLE(Float, float);
	MATERIAL_FUNCTION_SETTER_IMPLE(Vec2, glm::vec2);
	MATERIAL_FUNCTION_SETTER_IMPLE(Vec3, glm::vec3);
	MATERIAL_FUNCTION_SETTER_IMPLE(Vec4, glm::vec4);
	MATERIAL_FUNCTION_SETTER_IMPLE(Mat3, glm::mat3);
	MATERIAL_FUNCTION_SETTER_IMPLE(Mat4, glm::mat4);

	MATERIAL_FUNCTION_GETTER_IMPLE(Bool, bool);
	MATERIAL_FUNCTION_GETTER_IMPLE(Int, int);
	MATERIAL_FUNCTION_GETTER_IMPLE(Float, float);
	MATERIAL_FUNCTION_GETTER_IMPLE(Vec2, glm::vec2);
	MATERIAL_FUNCTION_GETTER_IMPLE(Vec3, glm::vec3);
	MATERIAL_FUNCTION_GETTER_IMPLE(Vec4, glm::vec4);
	MATERIAL_FUNCTION_GETTER_IMPLE(Mat3, glm::mat3);
	MATERIAL_FUNCTION_GETTER_IMPLE(Mat4, glm::mat4);

	uint32_t Material::GetTexture(const char* name) { return m_TextureBind.at(name).second; }

	void Material::RegisterCommom(CommomMaterialType type, Shader* shader)
	{
		if (shader) CommomMaterial.emplace(type, new Material(*shader));
	}

	void Material::UniformTexture2D(const char* location, Texture2D& v, int32_t binding)
	{
		int32_t index = glGetUniformLocation(m_shader->program, location);
		if (index != -1) UniformTexture2D(location, v.m_textureID, binding);
	}
	void Material::UniformTexture2D(const char* location, const uint32_t v, int32_t binding)
	{
		if (v == -1) return;
		int32_t index = glGetUniformLocation(m_shader->program, location);
		glActiveTexture(GL_TEXTURE0 + binding);
		glBindTexture(GL_TEXTURE_2D, v);
	}
	void Material::UniformTextureCube(const char* location, TextureCube& v, int32_t binding)
	{
		int32_t index = glGetUniformLocation(m_shader->program, location);
		if (index != -1) UniformTextureCube(location, v.m_textureID, binding);
	}
	void Material::UniformTextureCube(const char* location, const uint32_t v, int32_t binding)
	{
		if (v == -1) return;
		int32_t index = glGetUniformLocation(m_shader->program, location);
		glActiveTexture(GL_TEXTURE0 + binding);
		glBindTexture(GL_TEXTURE_CUBE_MAP, v);
	}
	void Material::PrintUniformLocations()
	{
		m_shader->PrintUniform();
	}
	void Material::CleanUniform()
	{
		m_TextureBind = std::map<std::string, std::pair<ShaderUniformType, uint32_t>>();
		for (auto b : m_blocks) {
			b.second->SetToDefault();
		}
	}
	void Material::ShaderUpdateCallback()
	{
		if (!m_shader) return;
		TARA_DEBUG_LEVEL("Update material uniform block: %s", 1, Name.c_str());
		ShaderUniformInformation sui = m_shader->Uniforms();
		int32_t ignore = 0;
		std::vector<const char*> have = std::vector<const char*>();
		// Adding or update
		for (auto j : sui.BlockData) {
			bool shouldSkip = false;
			for (auto ig : ignoreUniformBlock) {
				if (ig == j.BlockName) {
					shouldSkip = true;
					break;
				}
			}
			if (shouldSkip) {
				ignore++;
				continue;
			}
			if (m_blocks.count(j.BlockName.c_str())) {
				// Block exist
				m_blocks.at(j.BlockName.c_str())->Update(j);
			}
			else {
				MaterialUniformBlock* buffer = new MaterialUniformBlock(j);
				m_blocks.emplace(j.BlockName.c_str(), buffer);
			}
			have.push_back(j.BlockName.c_str());
		}
		if (m_blocks.size() == sui.BlockData.size() - ignore) {
			Apply();
			return;
		}
		std::vector<std::string> remove = std::vector<std::string>();
		// Search the block that should be remove
		for (auto i : m_blocks) {
			auto it = std::find(have.begin(), have.end(), i.first);
			if (it == have.end()) {
				remove.push_back(i.first);
			}
		}
		// Remove it by key one by one
		for (auto i : remove) {
			m_blocks.erase(m_blocks.find(i));
		}
		Apply();
	}
	std::pair<std::string, std::string> Material::GetUniformNameDetail(const char* fullname)
	{
		std::string t = fullname;
		size_t pos = t.find('.');
		if (pos == std::string::npos) return std::pair<const char*, const char*>(fullname, "");
		std::string blockName = t.substr(0, pos);
		std::string variableName = t.substr(pos + 1);
		TARA_DEBUG("GetUniformNameDetail: '%s' '%s'", blockName.c_str(), variableName.c_str());
		return { blockName.c_str(), variableName.c_str() };
	}
#pragma endregion
};