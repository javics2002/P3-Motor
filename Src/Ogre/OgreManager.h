#pragma once
#include "Utils/Singleton.h"
#include <unordered_map>
#include <string>

namespace Ogre {
	class Root;
	class RenderWindow;
	class FileSystemLayer;
	class SceneManager;
	class SceneNode;
	
	namespace RTShader {
		class ShaderGenerator;
	}
}

namespace me {

	class OgreWindow;
	class OgreCamera;
	class SGTechniqueResolverListener;

	class OgreManager : public Singleton<OgreManager> {
		friend Singleton<OgreManager>;
		OgreManager();

	private:
	protected:
		// Root de Ogre
		Ogre::Root* mRoot;
		//SceneManager de Ogre
		Ogre::SceneManager* mSM = nullptr;

		bool mFirstRun;

		std::string mResourceCfgPath;
		std::string mPluginCfgPath;
		std::string mOgreLogPath;
		std::string mOgreCfgPath;
		std::string mOgreResourcesPath;

		Ogre::FileSystemLayer* mFSLayer;
		Ogre::RTShader::ShaderGenerator* mShaderGenerator;
		SGTechniqueResolverListener* mMaterialMgrListener;

		/// TEMP (CARGA DE ASSETS)
		std::string mSolutionPath;


		OgreWindow* ogreWindow;

		std::unordered_map<std::string, OgreCamera*> mCameras;			//Pairs each cameras with its name

		void initRoot();
		void initWindow();
		void locateResources();
		void loadResources();
		bool initialiseRTShaderSystem();

		OgreCamera* getCamera(std::string name);

	public:
		OgreManager& operator=(const OgreManager& o) = delete;
		OgreManager(const OgreManager& o) = delete;
		~OgreManager() override;

		bool createCamera(std::string name, std::string parentName, int nearDist, int farDist, bool autoRadio, int zOrder);
		bool createCamera(std::string name, int nearDist, int farDist, bool autoRadio, int zOrder);
		void createNewLight(std::string name,int posX, int posY, int posZ, int dirX, int dirY, int dirZ );
		bool setCameraInfo(std::string name, int posX, int posY, int posZ, int lookX, int lookY, int lookZ);
		//void setCameraInfo(std::string name, Vector3 pos, Vector3 lookAt, float left, float top, float width, float height);
		bool setViewportDimension(std::string name, float left, float top, float width, float height);
		Ogre::SceneNode* createNode(std::string name);
		Ogre::SceneNode* createChildNode(std::string name,Ogre::SceneNode* parent);

		void scene1();

		void render();


	};

	/**
		This macro defines a compact way for using the singleton InputHandler, instead of
		writing InputHandler::instance()->method() we write ih().method()
	*/
	inline OgreManager& om() {
		return *OgreManager::instance();
	}

}