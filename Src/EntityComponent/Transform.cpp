#include "Transform.h"
#include <iostream>

me::Transform::Transform()
{
	// Initialize position, rotation and scale vectors
	mPosition = new Vector3(0.0, 0.0, 0.0);
	mRotation = Ogre::Quaternion::IDENTITY;
	mScale = new Vector3(1.0, 1.0, 1.0);

	// Set parent to null
	mParent = nullptr;

#ifdef _DEBUG
	std::cout << " > Component ( Transform ) created." << std::endl;
#endif
}

me::Transform::~Transform()
{
#ifdef _DEBUG
	std::cout << " >>> Component ( Transform ) deleted..." << std::endl;
#endif
}

void me::Transform::update()
{

}

me::Vector3 me::Transform::getPosition()
{
	return mPosition;
}

Ogre::Quaternion me::Transform::getRotation()
{
	return mRotation;
}

btQuaternion me::Transform::getRotationInBullet()
{
	return btQuaternion(mRotation.x, mRotation.y, mRotation.z, mRotation.w);
}

me::Vector3 me::Transform::getScale()
{
	return mScale;
}

void me::Transform::setPosition(Vector3 newPosition)
{
	mPosition = newPosition;
}

void me::Transform::setRotation(Ogre::Quaternion newRotation)
{
	mRotation = newRotation;
}

void me::Transform::setScale(Vector3 newScale)
{
	mScale = newScale;
}

void me::Transform::translate(Vector3 translation)
{
	mPosition += translation;
}

void me::Transform::rotate(int degrees, AxisRotations axis)
{

	Ogre::Vector3 v;

	switch (axis)
	{
	case me::AXIS_ROTATIONS_X:
		v = Ogre::Vector3::UNIT_X;
		break;
	case me::AXIS_ROTATIONS_Y:
		v = Ogre::Vector3::UNIT_Y;
		break;
	case me::AXIS_ROTATIONS_Z:
		v = Ogre::Vector3::UNIT_Z;
		break;
	}

	mRotation = Ogre::Quaternion(Ogre::Degree(degrees), v);

}

void me::Transform::scaleF(float scaleF)
{
	mScale *= scaleF;
}

int me::Transform::childCount()
{
	return mChildren.size();
}

void me::Transform::addChild(Transform* child)
{
	mChildren.push_back(child);
}

void me::Transform::removeChild(Transform* child)
{
	mChildren.remove(child);
}

me::Transform* me::Transform::getChild(int index)
{
	if (index > mChildren.size() || index < 0 || mChildren.empty())
		return nullptr;

	auto it = mChildren.begin();
	for (int i = 0; i < index; i++)
		it++;

	return *it;
}

me::Transform* me::Transform::getParent()
{
	return mParent;
}
