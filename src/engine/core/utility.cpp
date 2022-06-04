#include "utility.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <backward.hpp>
#include <archive.h>
#include <archive_entry.h>
#include "mesh/mesh.h"
#include "texture/texture.h"

namespace Tara {
	class ZipContent {
	public:
		ZipContent(void* _data, size_t _size) : data(_data), size(_size) { }
		~ZipContent() { 
			delete data;
		}
		void* data;
		size_t size;
	};

	namespace Utility {
		Argument* Argument::m_Singleton = nullptr;

		Argument& Argument::Singleton()
		{
			if (m_Singleton == nullptr) m_Singleton = new Argument();
			return *m_Singleton;
		}
		void Argument::Register(int count, char** argv)
		{
			for (int i = 0; i < count; i++) {
				std::string s = argv[i];
				if (s == "--debug") {
					debugMode = true;
				}
				else if (s == "--log") {
					recordAllLog = true;
				}
			}
		}

		std::string File::LoadFromFile(std::filesystem::path filename)
		{
			if (!exists(filename)) {
				return "";
			}
			std::string line = "", text = "";
			std::ifstream in(filename);
			if (!in.good()) {
				TARA_ERROR_LEVEL("File does not exist: %s", 2, filename.string().c_str());
				return "";
			}
			while (std::getline(in, line))
			{
				text += line + "\n";
			}
			return text;
		}

		bool File::Exist(std::filesystem::path filename)
		{
			return exists(filename);
		}

		void Debug::PrintTrace() {
			backward::StackTrace st; st.load_here(32);
			backward::Printer p;
			p.object = true;
			p.color_mode = backward::ColorMode::always;
			p.address = true;
			p.print(st);
		}

		std::string Debug::CurrentTimeString()
		{
			time_t rawtime;
			struct tm* timeinfo;
			char buffer[80];

			time(&rawtime);
			timeinfo = localtime(&rawtime);

			strftime(buffer, sizeof(buffer), "%d-%m-%Y %H:%M:%S", timeinfo);
			std::string str(buffer);

			return str;
		}
		void String::RemoveString(std::string& main, std::string find)
		{
			size_t pos = std::string::npos;
			// Search for the substring in string in a loop untill nothing is found
			while ((pos = main.find(find)) != std::string::npos)
			{
				// If found then erase it from string
				main.erase(pos, find.length());
			}
		}
		std::string String::Replace(std::string& main, std::string from, std::string to)
		{
			if (from.empty())
				return main;
			size_t start_pos = 0;
			while ((start_pos = main.find(from, start_pos)) != std::string::npos) {
				main.replace(start_pos, from.length(), to);
				start_pos += to.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
			}
			return main;
		}
		std::string String::Join(std::vector<std::string>& main, std::string separator)
		{
			std::string buffer = "";
			size_t count = 0;
			for (auto& i : main) {
				buffer += i;
				count++;
				if (count < main.size()) {
					buffer += separator;
				}
			}
			return buffer;
		}
		std::string String::ToLowercase(std::string main)
		{
			std::string buffer = main;
			std::transform(buffer.begin(), buffer.end(), buffer.begin(),
				[](unsigned char c) { return std::tolower(c); });
			return buffer;
		}
		std::string String::ToUppercase(std::string main)
		{
			std::string buffer = main;
			std::transform(buffer.begin(), buffer.end(), buffer.begin(),
				[](unsigned char c) { return std::toupper(c); });
			return buffer;
		}
		std::vector<std::string> String::Split(std::string main, std::string d)
		{
			std::vector<std::string> result = std::vector<std::string>();
			size_t pos = 0;
			while ((pos = main.find(d)) != std::string::npos) {
				std::string t = main.substr(0, pos);
				result.push_back(t);
				main.erase(0, pos + d.length());
			}
			result.push_back(main);
			return result;
		}
		nlohmann::json Json::ReadJson(const char* filename)
		{
			nlohmann::json jsonRoot;
			if (!std::filesystem::exists(filename)) return jsonRoot;
			std::ifstream st(filename);
			if (st.good()) {
				st >> jsonRoot;
			}
			st.close();
			return jsonRoot;
		}
		nlohmann::json Json::ReadJsonString(const char* data)
		{
			try {
				nlohmann::json j = nlohmann::json::parse(data);
				return j;
			}
			catch (nlohmann::json::parse_error& ex) {
				Utility::Debug::PrintTrace();
				TARA_RUNTIME_ERROR(ex.what());
				return nlohmann::json({});
			}
		}
		nlohmann::json Json::ReadBson(const char* filename)
		{
			if (!std::filesystem::exists(filename)) return nlohmann::json();
			std::ifstream st(filename, std::ios::in | std::ios::binary);
			std::vector<uint8_t> data((std::istreambuf_iterator<char>(st)), std::istreambuf_iterator<char>());
			st.close();
			return nlohmann::json::from_bson(data);
		}
		std::string Json::SaveJson(const char* dest, nlohmann::json& json, bool beautiful)
		{
			std::string buffer = ToJson(json, beautiful);
			if (std::filesystem::exists(dest)) remove(dest);
			std::ofstream st(dest);
			st << buffer;
			st.close();
			return buffer;
		}
		std::vector<uint8_t> Json::SaveBson(const char* dest, nlohmann::json& json)
		{
			std::vector<uint8_t> buffer = ToBson(json);
			if (std::filesystem::exists(dest)) remove(dest);
			std::ofstream st(dest, std::ios::binary);
			for (auto i : buffer) {
				st << i;
			}
			st.close();
			return buffer;
		}
		std::string Json::ToJson(nlohmann::json& json, bool beautiful)
		{
			return beautiful ? json.dump(4) : json.dump();
		}
		std::vector<std::uint8_t> Json::ToBson(nlohmann::json& json)
		{
			std::vector<std::uint8_t> bson = nlohmann::json::to_bson(json);
			return bson;
		}


		Zip* Zip::OpenZip(const char* filename)
		{
			Zip* zip = new Zip();
			zip->OpenZipFile(filename);
			return zip;
		}
		bool Zip::FileExist(std::string filename)
		{
			return contents.count(filename);
		}
		bool Zip::DirectroyExist(std::string dir)
		{
			for (auto i : contents) {
				if (i.first.find(dir) != std::string::npos) {
					return true;
				}
			}
			return false;
		}
		std::vector<std::string> Zip::GetDirectories(std::string dir)
		{
			std::vector<std::string> result = std::vector<std::string>();
			for (auto& i : contents) {
				if (i.first.rfind(dir.c_str(), 0) == 0) {
					result.push_back(i.first);
				}
			}
			return result;
		}
		std::vector<std::string> Zip::GetFiles(std::string dir)
		{
			std::vector<std::string> result = std::vector<std::string>();
			for (auto& i : contents) {
				if (i.first.rfind(dir.c_str(), 0) == 0) {
					result.push_back(i.first);
				}
			}
			return result;
		}
		std::vector<char> Zip::GetFileData_Char(std::string filename)
		{
			if (!FileExist(filename)) return std::vector<char>();
			ZipContent* c = contents.at(filename);
			std::vector<char> i = std::vector<char>();
			i.assign((char*)c->data, (char*)c->data + c->size);
			return i;
		}
		std::vector<uint8_t> Zip::GetFileData_UChar(std::string filename)
		{
			if (!FileExist(filename)) return std::vector<unsigned char>();
			ZipContent* c = contents.at(filename);
			std::vector<uint8_t> i = std::vector<uint8_t>();
			i.assign((uint8_t*)c->data, (uint8_t*)c->data + c->size);
			return i;
		}
		std::string Zip::GetFileData_String(std::string filename)
		{
			std::vector<char> d = GetFileData_Char(filename);
			return std::string(d.begin(), d.end());
		}
		void* Zip::GetFileData_Void(std::string filename)
		{
			if (!FileExist(filename)) return nullptr;
			ZipContent* c = contents.at(filename);
			return c->data;
		}
		size_t Zip::GetFileData_Size(std::string filename)
		{
			if (!FileExist(filename)) return 0;
			ZipContent* c = contents.at(filename);
			return c->size;
		}
		Mesh* Zip::GetMesh(std::string filename)
		{
			if (!FileExist(filename)) return nullptr;
			const void* data = GetFileData_Void(filename);
			size_t size = GetFileData_Size(filename);
			return Mesh::ImportFromMemory(data, size);
		}
		Texture2D* Zip::GetTexture(std::string filename)
		{
			if (!FileExist(filename)) return nullptr;
			const void* data = GetFileData_Void(filename);
			size_t size = GetFileData_Size(filename);
			return Texture2D::ImportFromMemory(data, size);
		}
		void Zip::UnzipContent(std::string dest, std::string dir)
		{
			if (dir.size() != 0 && !DirectroyExist(dir)) return;
		}
		Zip::Zip()
		{

		}
		Zip::~Zip()
		{
			for (auto i : contents) {
				delete i.second;
			}
		}
		void Zip::OpenZipFile(const char* filename)
		{
			struct archive* a;
			struct archive_entry* entry;
			int r;

			a = archive_read_new();
			archive_read_support_filter_all(a);
			archive_read_support_format_all(a);
			archive_read_support_compression_all(a);
			r = archive_read_open_filename(a, filename, 10240); // Note 1
			while (archive_read_next_header(a, &entry) == ARCHIVE_OK) {
				const char* filename = archive_entry_pathname(entry);
				size_t size = archive_entry_size(entry);
				if (size > 0) {
					const void* data;
					la_int64_t offset = 0;

					size_t total = 0;
					char* d = (char*)malloc(1);
					while (archive_read_data_block(a, &data, &size, &offset) != ARCHIVE_EOF) {
						size_t pre = total;
						total += size;
						char* vd = (char*)malloc(size);
						memcpy_s(vd, size, data, size);

						d = (char*)realloc(d, total);
						memcpy(&d[pre], vd, size);
					}
					TARA_DEBUG("%s %zu %zu", filename, total, offset);
					std::string filetarget = filename;
					Utility::String::RemoveString(filetarget, "resources/");
					ZipContent* zc = new ZipContent(d, total);
					contents[filetarget] = zc;
				}
			}
			r = archive_read_free(a);  // Note 3
			for (auto i : contents) {
				TARA_DEBUG_LEVEL("Zip content: %s, %zu", 2, i.first.c_str(), i.second->size);
			}
		}
}
}