#include <future>
#include <fstream>
#include <vector>
#include <string>

std::vector<std::future<void>> m_Futures;

static std::mutex s_MeshesMutex;

static void LoadMesh(std::vector<Ref<Mesh>> *meshed, std::string filepath)
{
    auto mesh = Mesh::Load(filepath);

    std::lock_guard<std::mutex> lock(s_MeshesMutex);
    meshes.push_back(mesh);
}

void EditLayer::LoadMeshes()
{
    std::ifstream stream("src/Models.txt");
    std::string line;
    std::vector<std::string> meshFilepaths;
    while (std::getline(stream, line))
    {
        meshFilepaths.push_back(line);
    }
    for (const auto &file : meshFilepaths)
    {
        m_Meshes.pushback(mesh::Load(file));
    }
    for (const auto &file : meshFilepaths)
    {
        m_Futures.push_back(std::async(std::launch::async, LoadMesh, m_Meshes, file));
    }
}