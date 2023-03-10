#pragma once
#ifndef __OGRE_OGREMESH
#define __OGRE_OGREMESH

#include <string>
#include <OgreVector3.h>

namespace Ogre {
	class SceneNode;
	class Quaternion;
}

namespace me {

	//Class to create renderizable object with mesh
	class OgreMesh
	{

	private:
	protected:
		//Reference to Ogre::SceneNode for renderize
		Ogre::SceneNode* mNode;
		//Reference to Ogre::Entity for renderize
		Ogre::Entity* mEntity;
		//Name of mesh that used
		std::string mMeshName;
		std::string mMaterialName;
		std::string mName;
		


	public:
		/**
		Assign information and create Ogre::Entity with the given mesh and attach to mNode
		@param node: mNode for attach Ogre::Entity created
		@param meshName: name of resource (type mesh) that we used for create Ogre::Entity. 
		Must be writted in resource.cfg (.mesh inside Zip or FileSystem)
		*/
		OgreMesh(Ogre::SceneNode* node,std::string meshName);
		~OgreMesh();
		//Set position, rotation and scale of mNode
		void setTransform(const Ogre::Vector3f &pos, const Ogre::Vector3f &scale, const Ogre::Quaternion &rot);
		void setPosition(const Ogre::Vector3f &pos);
		void setScale(const Ogre::Vector3f &scale);
		void setRotation(Ogre::Quaternion rot);

		/**
		Assign material name to entity
		@param materialName: name of material that we used 
		Must be writted in MaterialResource.material
		*/
		void setMaterial(std::string materialName);
		

	};

}
#endif