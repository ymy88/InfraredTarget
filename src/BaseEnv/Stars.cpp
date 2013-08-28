#include "StdAfx.h"
#include "Stars.h"

using namespace boost::property_tree;


Node* Stars::createStars()
{
	wptree xml;
	readXML("./resources/BaseEnv/stars.xml", xml);
	
	Geometry* geom = createGeom();
	
	double brightness[51] = {0};
	double mul = 1.0 / pow(1.5, 0.1); 
	brightness[0] = 255;
	for (int i = 1; i <= 50; ++i)
	{
		brightness[i] = brightness[i-1] * mul;
	}
	
	BOOST_FOREACH(wptree::value_type v, xml.get_child(L"stars"))
	{
		double lon = v.second.get<double>(L"<xmlattr>.lon");
		double lat = v.second.get<double>(L"<xmlattr>.lat");
		double bri = v.second.get<double>(L"<xmlattr>.bri");
		
		double x, y, z;
		SceneCenter::inst()->LLAToXYZ(lon, lat, EARTH_R*10, x, y, z);
		
		int index = (int)(bri * 10) - 10;
		index = index < 0 ? 0 : index;
		double c = brightness[index];
		c /= 255.0;
		
		g_vertices->push_back(Vec3d(x, y, z));
		g_normals->push_back(Vec3d(-x, -y, -z));
		g_colors->push_back(Vec4d(c, c, c, 1));
	}
	
	g_drawArrays->setCount(g_vertices->size());
	
	Geode* geode = new Geode;
	geode->addDrawable(geom);
	geode->setComputeBoundingSphereCallback(new Node::ComputeBoundingSphereCallback);
	geode->getOrCreateStateSet()->setMode(GL_LIGHTING, StateAttribute::OFF);
	return geode;
}

Geometry* Stars::createGeom()
{
	Geometry* geom = new Geometry;
	g_vertices = new Vec3dArray;
	g_colors = new Vec4dArray;
	g_normals = new Vec3dArray;
	
	geom->setVertexArray(g_vertices);
	geom->setColorArray(g_colors);
	geom->setNormalArray(g_normals);
	
	geom->setColorBinding(Geometry::BIND_PER_VERTEX);
	geom->setNormalBinding(Geometry::BIND_PER_VERTEX);
	
	g_drawArrays = new DrawArrays(GL_POINTS, 0, 0);
	
	geom->addPrimitiveSet(g_drawArrays);
	
	return geom;
}
