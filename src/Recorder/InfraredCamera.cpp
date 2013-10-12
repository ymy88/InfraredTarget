#include "StdAfx.h"
#include "InfraredCamera.h"
#include <GlobalConfig.h>
#include <Recorder.h>
#include <osg/Texture1D>

const string IMAGEPATH = "./resources/Missiles/Image";
//const string IMAGEPATH = "c:/Image";

const static int perm[256]= {151,160,137,91,90,15,
	131,13,201,95,96,53,194,233,7,225,140,36,103,30,69,142,8,99,37,240,21,10,23,
	190, 6,148,247,120,234,75,0,26,197,62,94,252,219,203,117,35,11,32,57,177,33,
	88,237,149,56,87,174,20,125,136,171,168, 68,175,74,165,71,134,139,48,27,166,
	77,146,158,231,83,111,229,122,60,211,133,230,220,105,92,41,55,46,245,40,244,
	102,143,54, 65,25,63,161, 1,216,80,73,209,76,132,187,208, 89,18,169,200,196,
	135,130,116,188,159,86,164,100,109,198,173,186, 3,64,52,217,226,250,124,123,
	5,202,38,147,118,126,255,82,85,212,207,206,59,227,47,16,58,17,182,189,28,42,
	223,183,170,213,119,248,152, 2,44,154,163, 70,221,153,101,155,167, 43,172,9,
	129,22,39,253, 19,98,108,110,79,113,224,232,178,185, 112,104,218,246,97,228,
	251,34,242,193,238,210,144,12,191,179,162,241, 81,51,145,235,249,14,239,107,
	49,192,214, 31,181,199,106,157,184, 84,204,176,115,121,50,45,127, 4,150,254,
	138,236,205,93,222,114,67,29,24,72,243,141,128,195,78,66,215,61,156,180};

const static int grad3[16][3] = {{0,1,1},{0,1,-1},{0,-1,1},{0,-1,-1},
	{1,0,1},{1,0,-1},{-1,0,1},{-1,0,-1},
	{1,1,0},{1,-1,0},{-1,1,0},{-1,-1,0}, // 12 cube edges
	{1,0,-1},{-1,0,-1},{0,-1,1},{0,1,1}}; // 4 more to make 16

const static int grad4[32][4]= {{0,1,1,1}, {0,1,1,-1}, {0,1,-1,1}, {0,1,-1,-1}, // 32 tesseract edges
	{0,-1,1,1}, {0,-1,1,-1}, {0,-1,-1,1}, {0,-1,-1,-1},
	{1,0,1,1}, {1,0,1,-1}, {1,0,-1,1}, {1,0,-1,-1},
	{-1,0,1,1}, {-1,0,1,-1}, {-1,0,-1,1}, {-1,0,-1,-1},
	{1,1,0,1}, {1,1,0,-1}, {1,-1,0,1}, {1,-1,0,-1},
	{-1,1,0,1}, {-1,1,0,-1}, {-1,-1,0,1}, {-1,-1,0,-1},
	{1,1,1,0}, {1,1,-1,0}, {1,-1,1,0}, {1,-1,-1,0},
	{-1,1,1,0}, {-1,1,-1,0}, {-1,-1,1,0}, {-1,-1,-1,0}};

const static unsigned char simplex4[][4] = {{0,64,128,192},{0,64,192,128},{0,0,0,0},
	{0,128,192,64},{0,0,0,0},{0,0,0,0},{0,0,0,0},{64,128,192,0},
	{0,128,64,192},{0,0,0,0},{0,192,64,128},{0,192,128,64},
	{0,0,0,0},{0,0,0,0},{0,0,0,0},{64,192,128,0},
	{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},
	{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},
	{64,128,0,192},{0,0,0,0},{64,192,0,128},{0,0,0,0},
	{0,0,0,0},{0,0,0,0},{128,192,0,64},{128,192,64,0},
	{64,0,128,192},{64,0,192,128},{0,0,0,0},{0,0,0,0},
	{0,0,0,0},{128,0,192,64},{0,0,0,0},{128,64,192,0},
	{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},
	{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},
	{128,0,64,192},{0,0,0,0},{0,0,0,0},{0,0,0,0},
	{192,0,64,128},{192,0,128,64},{0,0,0,0},{192,64,128,0},
	{128,64,0,192},{0,0,0,0},{0,0,0,0},{0,0,0,0},
	{192,64,0,128},{0,0,0,0},{192,128,0,64},{192,128,64,0}};

static Texture2D* createPermTexture()
{
	Image* image = new Image;
	image->allocateImage(512, 512, 1, GL_RGBA, GL_UNSIGNED_BYTE);
	image->setInternalTextureFormat(GL_RGBA);
	char* pixels = (char*)image->data();
	for (int i = 0; i < 512; ++i)
	{
		for (int j = 0; j < 512; ++j)
		{
			int offset = (i * 512 + j) * 4;
			unsigned char value = perm[(j + perm[i]) & 0xff];
			pixels[offset]   = grad3[value & 0x0f][0] * 64 + 64;	// Gradient x
			pixels[offset+1] = grad3[value & 0x0f][1] * 64 + 64;	// Gradient y
			pixels[offset+2] = grad3[value & 0x0f][2] * 64 + 64;	// Gradient z
			pixels[offset+3] = value;								// permuted index
		}
	}

	Texture2D* tex = new Texture2D(image);
	tex->setFilter( Texture2D::MIN_FILTER, Texture2D::NEAREST );
	tex->setFilter( Texture2D::MAG_FILTER, Texture2D::NEAREST );
	return tex;
}

static Texture1D* createSimplexTexture()
{
	Image* image = new Image;
	image->allocateImage(64, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE);
	image->setInternalTextureFormat(GL_RGBA);
	unsigned char* pixels = image->data();
	memcpy(pixels, &simplex4[0][0], sizeof(simplex4));

	Texture1D* tex = new Texture1D(image);
	tex->setFilter( Texture1D::MIN_FILTER, Texture1D::NEAREST );
	tex->setFilter( Texture1D::MAG_FILTER, Texture1D::NEAREST );
	return tex;
}

static Texture2D* createGradTexture()
{
	Image* image = new Image;
	image->allocateImage(512, 512, 1, GL_RGBA, GL_UNSIGNED_BYTE);
	image->setInternalTextureFormat(GL_RGBA);
	char* pixels = (char*)image->data();
	for (int i = 0; i < 512; ++i)
	{
		for (int j = 0; j < 512; ++j)
		{
			int offset = (i * 512 + j) * 4;
			unsigned char value = perm[(j + perm[i]) & 0xff];
			pixels[offset]   = grad4[value & 0x1f][0] * 64 + 64;	// Gradient x
			pixels[offset+1] = grad4[value & 0x1f][1] * 64 + 64;	// Gradient y
			pixels[offset+2] = grad4[value & 0x1f][2] * 64 + 64;	// Gradient z
			pixels[offset+3] = grad4[value & 0x1f][3] * 64 + 64;	// Gradient z
		}
	}
	Texture2D* tex = new Texture2D(image);
	tex->setFilter( Texture2D::MIN_FILTER, Texture2D::NEAREST );
	tex->setFilter( Texture2D::MAG_FILTER, Texture2D::NEAREST );
	return tex;
}

void MakeImageReal::operator()( osg::RenderInfo& renderInfo ) const
{
	InfraredCamera* camera = dynamic_cast<InfraredCamera*>(renderInfo.getCurrentCamera());
	Image* image = camera->_image;
	//for (unsigned int i = 0; i < camera->_blindSpots.size(); ++i)
	//{
	//	Vec2s& blindSpot = camera->_blindSpots[i];
	//	(*(image->data(blindSpot.x(), blindSpot.y()))) = (unsigned char)255;
	//}

	if (!isEnd && shouldSaveImage)
	{
		sprintf((char*)path, "%s/Image%05d.jpg", IMAGEPATH.c_str(), frame);
		osgDB::writeImageFile(*image, path);
	}
}


InfraredCamera::InfraredCamera(void) : CameraBase(NULL, false)
{
	setClearColor(Vec4(0, 0, 0, 1));
	setClearMask(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	setViewport( 0, 0, INFRARED_VIEW_WIDTH, INFRARED_VIEW_HEIGHT );
	setReferenceFrame( Camera::ABSOLUTE_RF );
	setRenderOrder( Camera::PRE_RENDER );
	setCullingMode(NO_CULLING);

	Recorder::inst()->addRecordable(this);

	srand((unsigned)time(NULL));

	_makeImageRealCallback = new MakeImageReal;
	this->setPostDrawCallback(_makeImageRealCallback);

	//_image = new Image;
	_texture = new Texture2D;
	_texture->setTextureSize(512, 512);
	_texture->setInternalFormat(GL_LUMINANCE);
	_texture->setFilter( Texture2D::MIN_FILTER, Texture2D::LINEAR );
	_texture->setFilter( Texture2D::MAG_FILTER, Texture2D::LINEAR );
	this->attach(Camera::COLOR_BUFFER, _texture);

	this->setComputeNearFarMode(DO_NOT_COMPUTE_NEAR_FAR);

	const int size = 512;
	_geom = osg::createTexturedQuadGeometry(Vec3d(0, 0, 0), Vec3d(size, 0, 0), Vec3d(0, size, 0));
	_geom->getOrCreateStateSet()->setMode(GL_BLEND, StateAttribute::ON);
	_geom->getOrCreateStateSet()->setTextureAttributeAndModes(0, _texture);

	Texture2D* texPerm = createPermTexture();
	Texture1D* texSimplex = createSimplexTexture();
	Texture2D* texGrad = createGradTexture();
	_geom->getOrCreateStateSet()->setTextureAttributeAndModes(1, texPerm);
	_geom->getOrCreateStateSet()->setTextureAttributeAndModes(2, texSimplex);
	_geom->getOrCreateStateSet()->setTextureAttributeAndModes(3, texGrad);

	Geode* geode = new Geode;
	geode->addDrawable(_geom);

	_program = new Program;
	_vertObj = new Shader(Shader::VERTEX);
	_fragObj = new Shader(Shader::FRAGMENT);
	_program->addShader(_vertObj);
	_program->addShader(_fragObj);
	_geom->getOrCreateStateSet()->setAttributeAndModes(_program, StateAttribute::ON);
	_geom->getOrCreateStateSet()->addUniform(new Uniform("texTarget", 0));
	_geom->getOrCreateStateSet()->addUniform(new Uniform("texPerm", 1));
	_geom->getOrCreateStateSet()->addUniform(new Uniform("texSimplex", 2));
	_geom->getOrCreateStateSet()->addUniform(new Uniform("texGrad", 3));
	_geom->getOrCreateStateSet()->addUniform(new Uniform("frame", 0.0f));

	_vertObj->loadShaderSourceFromFile("./resources/camera.vert");
	_fragObj->loadShaderSourceFromFile("./resources/camera.frag");
}

InfraredCamera::~InfraredCamera(void)
{
}

void InfraredCamera::getReady( const Situation& situation, unsigned int& begFrame, unsigned int& endFrame )
{
	int resolution = situation.infrared.resolution;
	double angle = situation.infrared.cameraAngle;
	float blindRate = situation.infrared.blindRate;
	_makeImageRealCallback->shouldSaveImage = situation.other.saveToFile;

	// handle texture

	//_image->allocateImage(resolution, resolution, 1, GL_RGBA, GL_FLOAT);
	//_image->setInternalTextureFormat(GL_RGBA);
	//Recorder::inst()->setInfraredTexture(_image);

	// handle camera property

	_cameraController.adjustCamera(resolution, resolution, 1);
	this->setProjectionMatrixAsPerspective(DegreesToRadians(angle), 1.0, 0.1, 1e6);


	// handle blind spots

	_blindSpots.clear();
	int totalCount = resolution * resolution;
	int blindCount = totalCount * blindRate / 100;
	for (int i = 0; i < blindCount; ++i)
	{
		int x = (int)(1.0 * rand() / RAND_MAX * (resolution-1));
		int y = (int)(1.0 * rand() / RAND_MAX * (resolution-1));
		_blindSpots.push_back(Vec2s(x, y));
	}

	begFrame = 0;
	endFrame = 1;

	// handle callback

	_makeImageRealCallback->isEnd = false;

	// handle image directory
	if (situation.other.saveToFile)
	{
		boost::filesystem::path imagePath(stringToWString(IMAGEPATH));
		if (exists(imagePath))
		{
			boost::filesystem::remove_all(imagePath);
		}
		boost::filesystem::create_directory(imagePath);
	}
}

void InfraredCamera::gotoFrame(unsigned int frame)
{
	_makeImageRealCallback->frame = frame;
	_makeImageRealCallback->isEnd = false;

	const StateSet::RefUniformPair* uniformPair = _geom->getOrCreateStateSet()->getUniformPair("frame");
	Uniform* uniform = uniformPair->first.get();
	uniform->set((float)frame);
}

void InfraredCamera::end()
{
	_makeImageRealCallback->isEnd = true;
}