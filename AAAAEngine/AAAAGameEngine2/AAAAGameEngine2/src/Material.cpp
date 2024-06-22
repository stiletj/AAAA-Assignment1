#include "Material.h"

Material::Material()
{
	m_ambientColour = { 1.0f, 1.0f, 1.0f };
	m_diffuseColour = { 0.8f, 0.8f, 0.8f };
	m_specularColour = { 0.5f, 0.5f, 0.5f };
	m_specularExponent = 250.f;

	m_textureFile = "NA";
}

Material::Material(std::string inputFile)
{
	readMTLFile(inputFile);
}

Material::~Material()
{
}

const glm::vec3 Material::GetAmbient() const
{
	return m_ambientColour;
}

void Material::SetAmbient(glm::vec3 ambient)
{
	m_ambientColour.x = ambient.x;
	m_ambientColour.y = ambient.y;
	m_ambientColour.z = ambient.z;
}

const glm::vec3 Material::GetSpecular() const
{
	return m_specularColour;
}

void Material::SetSpecular(glm::vec3 specular)
{
	m_specularColour.x = specular.x;
	m_specularColour.y = specular.y;
	m_specularColour.z = specular.z;
}

const float Material::GetSpecularExponent() const
{
	return m_specularExponent;
}

void Material::SetSpecularExponent(float exp)
{
	m_specularExponent = exp;
}

void Material::SetTextureFile(std::string filePath)
{
	m_textureFile = filePath;
}

const glm::vec3 Material::GetDiffuse() const
{
	return m_diffuseColour;
}

void Material::SetDiffuse(glm::vec3 diffuse)
{
	m_diffuseColour = diffuse;
}

const std::string Material::GetName() const
{
	return m_materialName;
}

void Material::SetName(std::string name)
{
	m_materialName = name;
}

const std::string Material::GetTexture() const
{
	return m_textureFile;
}

std::vector<Material> readMTLFile(std::string inputFile)
{
	bool isEmpty = true;

	std::vector<Material> mats;

	std::ifstream infile;
	infile.open(inputFile);
	if (!infile.is_open())
	{
		std::cout << "Error: Couldn't open file : " << inputFile << std::endl;
		return mats;
	}

	std::string line;

	while (std::getline(infile, line))
	{
		std::stringstream lineStream(line);

		std::string character;
		std::getline(lineStream, character, ' ');

		if (character == ("#"))
		{
			continue;
		}
		else if (character == "Ka")
		{
			std::string Ka[3];

			std::getline(lineStream, Ka[0], ' ');
			std::getline(lineStream, Ka[1], ' ');
			std::getline(lineStream, Ka[2]);

			mats[mats.size() - 1].SetAmbient({ std::stof(Ka[0]), std::stof(Ka[1]), std::stof(Ka[2]) });
		}
		else if (character == "Kd")
		{
			std::string Kd[3];

			std::getline(lineStream, Kd[0], ' ');
			std::getline(lineStream, Kd[1], ' ');
			std::getline(lineStream, Kd[2]);

			mats[mats.size() - 1].SetDiffuse({ std::stof(Kd[0]), std::stof(Kd[1]), std::stof(Kd[2]) });

			mats[mats.size() - 1].SetTextureFile("NA");

			isEmpty = false;
		}
		else if (character == "Ks")
		{
			std::string Ks[3];

			std::getline(lineStream, Ks[0], ' ');
			std::getline(lineStream, Ks[1], ' ');
			std::getline(lineStream, Ks[2]);

			mats[mats.size() - 1].SetSpecular({ std::stof(Ks[0]), std::stof(Ks[1]), std::stof(Ks[2]) });
		}
		else if (character == "map_Kd")
		{
			std::string directory;

			while (std::getline(lineStream, directory, '/'))
			{
				if (directory.find(".png") != std::string::npos)
				{
					break;
				}
			}

			mats[mats.size() - 1].SetTextureFile("resources/textures/" + directory);

			mats[mats.size() - 1].SetDiffuse({ 1.0f, 1.0f , 1.0f });

			isEmpty = false;
		}
		else if (character == "Ns")
		{
			std::string specExp;

			std::getline(lineStream, specExp);

			mats[mats.size() - 1].SetSpecularExponent(std::stof(specExp));
		}
		else if (character == "newmtl")
		{
			Material newMat;
			std::string name;

			std::getline(lineStream, name);

			newMat.SetName(name);

			mats.push_back(newMat);
		}
		else
		{
			continue;
		}
	}

	if (isEmpty)
	{
		Material mtl;
		mats.push_back(mtl);
	}

	return mats;
}