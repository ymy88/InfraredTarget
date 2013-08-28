#include "StdAfx.h"

#include "Earth.h"
#include <osg/CullFace>

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
	}

	Group* group = new Group;
	group->addChild(earthNode);
	group->addChild(haloNode);

	return group;
}

Node* Earth::loadEarth()
{
	//Node* earthNode = osgDB::readNodeFile("./resources/Earth/globe.ive");
	Node* earthNode = osgDB::readNodeFile("../../Earth_resource/gansu.ive");
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
	Vec4Array* color = new Vec4Array;
	Vec3Array* vertex = new Vec3Array;
	Vec3Array* normal = new Vec3Array;

	for (float alpha = 0; alpha <= PI * 2; alpha += PI*0.01)
	{
		float innerX, innerY, outerX, outerY;
		innerX = HALO_INNER_RADIUS * cosf(alpha);
		innerY = HALO_INNER_RADIUS * sinf(alpha);
		outerX = HALO_OUTER_RADIUS * cosf(alpha);
		outerY = HALO_OUTER_RADIUS * sinf(alpha);

		vertex->push_back(Vec3(outerX, outerY, 0));
		vertex->push_back(Vec3(innerX, innerY, 0));

		color->push_back(Vec4(0, 0, 1, 0.05f));
		color->push_back(Vec4(0.8, 0.8, 1, 0.8f));

		Vec3 innernormal = Vec3(innerX, innerY,  HALO_INNER_RADIUS);
		Vec3 outernormal = Vec3(outerX, outerY,  HALO_OUTER_RADIUS);
		innernormal.normalize();
		outernormal.normalize();
		normal->push_back(innernormal);
		normal->push_back(outernormal);
	}

	color->push_back((*color)[0]);
	color->push_back((*color)[1]);
	vertex->push_back((*vertex)[0]);
	vertex->push_back((*vertex)[1]);
	normal->push_back((*normal)[0]);
	normal->push_back((*normal)[1]);

	Geometry* geom = new Geometry;
	geom->setVertexArray(vertex);
	geom->setColorArray(color);
	geom->setNormalArray(normal);
	geom->setColorBinding(Geometry::BIND_PER_VERTEX);
	geom->setNormalBinding(Geometry::BIND_PER_VERTEX);
	geom->addPrimitiveSet(new DrawArrays(GL_TRIANGLE_STRIP, 0, vertex->size()));

	Billboard* haloBillboard = new Billboard;
	haloBillboard->addDrawable(geom);
	haloBillboard->setNormal(Vec3(0, 0, 1));
	haloBillboard->setPosition(0, Vec3(0, 0, 0));
	haloBillboard->setMode(Billboard::POINT_ROT_EYE);

	StateSet* stateSet = new StateSet;
	stateSet->setMode(GL_BLEND, StateAttribute::ON);
	haloBillboard->setStateSet(stateSet);

	return haloBillboard;
}