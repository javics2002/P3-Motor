/*
-----------------------------------------------------------------------------
This source file is part of OGRE
(Object-oriented Graphics Rendering Engine)
For the latest info, see http://www.ogre3d.org/

Copyright (c) 2000-2014 Torus Knot Software Ltd

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
-----------------------------------------------------------------------------
*/

#ifndef PCZONE_FACTORY_H
#define PCZONE_FACTORY_H

#include "OgrePCZPrerequisites.h"
#include "OgreSingleton.h"
#include "OgreIteratorWrapper.h"

namespace Ogre
{
    class PCZSceneManager;
    class PCZone;

    /// Factory for PCZones
    class _OgrePCZPluginExport PCZoneFactory : public SceneCtlAllocatedObject
    {
    public:
        PCZoneFactory(const String & typeName);
        virtual ~PCZoneFactory();
        virtual bool supportsPCZoneType(const String& zoneType) = 0;
        virtual PCZone* createPCZone(PCZSceneManager * pczsm, const String& zoneName) = 0;
        const String& getFactoryTypeName() const { return mFactoryTypeName; }
        /// Factory type name
        String mFactoryTypeName;
    };

    // Factory for default zone
    class _OgrePCZPluginExport DefaultZoneFactory : public PCZoneFactory
    {
    public:
        DefaultZoneFactory();
        virtual ~DefaultZoneFactory();
        bool supportsPCZoneType(const String& zoneType) override;
        PCZone* createPCZone(PCZSceneManager * pczsm, const String& zoneName) override;
    };

    // PCZoneFactory manager class
    class _OgrePCZPluginExport PCZoneFactoryManager : public Singleton<PCZoneFactoryManager>, public SceneCtlAllocatedObject
    {
    public:
        PCZoneFactoryManager(); 
        ~PCZoneFactoryManager();
        void registerPCZoneFactory(PCZoneFactory* factory);
        void unregisterPCZoneFactory(PCZoneFactory* factory);
        PCZone* createPCZone(PCZSceneManager * pczsm,
                             const String& zoneType, 
                             const String& zoneName);
        /// @copydoc Singleton::getSingleton()
        static PCZoneFactoryManager& getSingleton(void);
        /// @copydoc Singleton::getSingleton()
        static PCZoneFactoryManager* getSingletonPtr(void);
        /* PCZoneFactory Iterator - for querying what types of PCZone
        factories are available */
        typedef std::map<String, PCZoneFactory*> PCZoneFactoryMap;
        typedef MapIterator<PCZoneFactoryMap> PCZoneFactoryIterator;
        /** Return an iterator over the PCZone factories currently registered */
        PCZoneFactoryIterator getPCZoneFactoryIterator(void);

    protected:
        PCZoneFactoryMap mPCZoneFactories;
        DefaultZoneFactory mDefaultFactory;
    };
}

#endif
