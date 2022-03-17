#include <engine.h>

using namespace Tara;
using namespace glm;

class MeshExample : public EWindow {
public:
	MeshExample() : EWindow(800, 600, "Example Window", OpenGLVersion::Version4_6) {}
	void Start() override {
		EWindow::Start();

		EScene* scene = new EScene();

		EObject* cube = ObjectFactory3D::CreateMesh(CommomMesh::Cube);
		CTransformation* trans = cube->GetRelateComponent<CTransformation>();
		CMeshRenderer* meshr = cube->GetRelateComponent<CMeshRenderer>();

		Material* mat = new Material(CommonShader::Color);
		meshr->SetMaterial(mat);
		mat->SetVec3("color", vec3(1.0, 0.0, 0.0));

		m_scenes.push_back(scene);
	}
};

int main() {
	MeshExample* window = new MeshExample();
	window->Run();
	return 0;
}