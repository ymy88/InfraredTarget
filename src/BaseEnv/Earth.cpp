#include "StdAfx.h"

#include "Earth.h"
#include "MySphereDrawable.h"
#include <osg/CullFace>
#include <osg/ShapeDrawable>

Node* Earth::createEarth()
{
	Node* earthNode = loadEarth();
	Node* haloNode = createHalo();

	if (earthNode && haloNode)
	{
		earthNode->getOrCreateStateSet()->setMode(GL_NORMALIZE, StateAttribute::ON);

		earthNode->getOrCreateStateSet()->setRenderBinDetails(0, "RenderBin");
		haloNode->getOrCreateStateSet()->setRenderBinDetails(1, "RenderBin");

		osg::CullFace* cullFace = new osg::CullFace(CullFace::BACK);
		earthNode->getOrCreateStateSet()->setAttributeAndModes(cullFace);
		haloNode->getOrCreateStateSet()->setAttributeAndModes(cullFace);
	}

	Group* group = new Group;
	group->addChild(earthNode);
	group->addChild(haloNode);
	group->getOrCreateStateSet()->setMode(GL_BLEND, StateAttribute::ON);

	return group;
}

Node* Earth::loadEarth()
{
	//Node* earthNode = osgDB::readNodeFile("./resources/Earth/globe.ive");
	Node* earthNode = osgDB::readNodeFile("../../Earth_resource/globe.ive");
	if (!earthNode)
	{
		return NULL;
	}

	float radius = earthNode->getBound().radius();
	Vec3 center = earthNode->getBound().center();

	float scale = EARTH_R / radius * 1.7281;

	MatrixTransform* trans = new MatrixTransform;
	Matrixd mat1, mat2, mat3;
	mat1.makeTranslate(-center);
	mat2.makeScale(scale, scale, scale);
	mat3.makeRotate(-PI_2, Vec3(1, 0, 0));
	trans->setMatrix(mat1 * mat2 * mat3);
	trans->addChild(earthNode);

	return trans;
}

Node* Earth::createHalo()
{
	osg::Geode* geode = new osg::Geode;
	geode->addDrawable(new MySphereDrawable(new osg::Sphere(osg::Vec3(0.0f,0.0f,0.0f), HALO_OUTER_RADIUS)));
	_haloProgram = new Program;
	_haloVertObj = new Shader(Shader::VERTEX);
	_haloFragObj = new Shader(Shader::FRAGMENT);
	_haloProgram->addShader(_haloVertObj);
	_haloProgram->addShader(_haloFragObj);
	geode->getOrCreateStateSet()->setAttributeAndModes(_haloProgram, StateAttribute::ON);

	_haloVertObj->loadShaderSourceFromFile("./resources/BaseEnv/Halo.vert");
	_haloFragObj->loadShaderSourceFromFile("./resources/BaseEnv/Halo.frag");

	return geode;
}