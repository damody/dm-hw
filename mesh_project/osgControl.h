#pragma once
#include "Tri_Mesh.h"
#include <osgViewer/Viewer>
#include <osgViewer/ViewerEventHandlers>
#include <osgViewer/api/win32/GraphicsWindowWin32>
#include <osgGA/TrackballManipulator>
#include <osgGA/KeySwitchMatrixManipulator>
#include <osgDB/DatabasePager>
#include <osgDB/Registry>
#include <osgDB/ReadFile>
#include <osgUtil/Optimizer>
#include <string>

class osgControl
{
public:
	osgControl(HWND hWnd) 
		:mhWnd(hWnd) 
	{
	}
	~osgControl(void);
	osg::ref_ptr<osg::Camera> mCamera;
private:
	bool mDone;
	std::string mModelName;
	HWND mhWnd;
	osgViewer::Viewer* mViewer;
	osg::ref_ptr<osg::Group> mRoot;
	osg::ref_ptr<osg::Geode> mModel;
	osg::ref_ptr<osgGA::TrackballManipulator> mTrackball;
	osg::ref_ptr<osgGA::KeySwitchMatrixManipulator> mKeyswitchManipulator;
public:
	void AddLine(osg::Vec3f& p, osg::Vec3f& q);
	void SetModel(Tri_Mesh* mesh);
	void Done(bool value) { mDone = value; }
	bool Done(void) { return mDone; }
	static void Render(void* ptr);
	osgViewer::Viewer* getViewer() { return mViewer; }
	void GetRay(float x, float y, osg::Vec3f& vPickRayOrig, osg::Vec3f& vPickRayDir);
	void InitOSG(std::string modelname)
	{
		// Store the name of the model to load
		mModelName = modelname;

		// Init different parts of OSG
		InitManipulators();
		InitSceneGraph();
		InitCameraConfig();
	}
	void PreFrameUpdate()
	{
		// Due any preframe updates in this routine
	}
	void PostFrameUpdate()
	{
		// Due any postframe updates in this routine
	}

	void osgControl::InitCameraConfig(void)
	{
		// Local Variable to hold window size data
		RECT rect;

		// Create the viewer for this window
		mViewer = new osgViewer::Viewer();

		// add the thread model handler
		mViewer->addEventHandler(new osgViewer::ThreadingHandler);

		// add the window size toggle handler
		mViewer->addEventHandler(new osgViewer::WindowSizeHandler);

		// add the stats handler
		mViewer->addEventHandler(new osgViewer::StatsHandler);

		// add the LOD Scale handler
		mViewer->addEventHandler(new osgViewer::LODScaleHandler);

		// add the screen capture handler
		mViewer->addEventHandler(new osgViewer::ScreenCaptureHandler);

		// Get the current window size
		::GetWindowRect(mhWnd, &rect);

		// Init the GraphicsContext Traits
		osg::ref_ptr<osg::GraphicsContext::Traits> traits = new osg::GraphicsContext::Traits;

		// Init the Windata Variable that holds the handle for the Window to display OSG in.
		osg::ref_ptr<osg::Referenced> windata = new osgViewer::GraphicsWindowWin32::WindowData(mhWnd);

		// Setup the traits parameters
		traits->x = 0;
		traits->y = 0;
		traits->width = rect.right - rect.left;
		traits->height = rect.bottom - rect.top;
		traits->windowDecoration = false;
		traits->doubleBuffer = true;
		traits->sharedContext = 0;
		traits->setInheritedWindowPixelFormat = true;
		traits->inheritedWindowData = windata;

		// Create the Graphics Context
		osg::GraphicsContext* gc = osg::GraphicsContext::createGraphicsContext(traits.get());

		// Init a new Camera (Master for this View)
		mCamera = new osg::Camera;

		// Assign Graphics Context to the Camera
		mCamera->setGraphicsContext(gc);

		// Set the viewport for the Camera
		mCamera->setViewport(new osg::Viewport(traits->x, traits->y, traits->width, traits->height));

		// Set projection matrix and camera attribtues
		mCamera->setClearMask(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
		mCamera->setClearColor(osg::Vec4f(0.2f, 0.2f, 0.4f, 1.0f));
		mCamera->setProjectionMatrixAsPerspective(
			30.0f, static_cast<double>(traits->width)/static_cast<double>(traits->height), 1.0, 1000.0);
		// Add the Camera to the Viewer
		//mViewer->addSlave(camera.get());
		mViewer->setCamera(mCamera.get());

		// Add the Camera Manipulator to the Viewer
		mViewer->setCameraManipulator(mKeyswitchManipulator.get());

		// Set the Scene Data
		mViewer->setSceneData(mRoot.get());

		// Realize the Viewer
		mViewer->realize();

		// Correct aspect ratio
		/*double fovy,aspectRatio,z1,z2;
		mViewer->getCamera()->getProjectionMatrixAsPerspective(fovy,aspectRatio,z1,z2);
		aspectRatio=double(traits->width)/double(traits->height);
		mViewer->getCamera()->setProjectionMatrixAsPerspective(fovy,aspectRatio,z1,z2);*/
	}
	void InitSceneGraph(void)
	{
		// Init the main Root Node/Group
		mRoot  = new osg::Group;

		/*
		// Load the Model from the model name
		mModel = osgDB::readNodeFile(m_ModelName);

		// Optimize the model
		osgUtil::Optimizer optimizer;
		optimizer.optimize(mModel.get());
		optimizer.reset();

		// Add the model to the scene
		mRoot->addChild(mModel.get());
		*/
	}
	void InitManipulators(void)
	{
		// Create a trackball manipulator
		mTrackball = new osgGA::TrackballManipulator();
		// Create a Manipulator Switcher
		mKeyswitchManipulator = new osgGA::KeySwitchMatrixManipulator;
		// Add our trackball manipulator to the switcher
		mKeyswitchManipulator->addMatrixManipulator( '1', "Trackball", mTrackball.get());
		// Init the switcher to the first manipulator (in this case the only manipulator)
		mKeyswitchManipulator->selectMatrixManipulator(0);  // Zero based index Value
	}
};
