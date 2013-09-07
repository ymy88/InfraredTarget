#include "StdAfx.h"
#include "MySphereDrawable.h"

class MyDrawShapeVisitor;

class MyDrawShapeVisitor : public ConstShapeVisitor
{
public:
	MyDrawShapeVisitor(State& state,const TessellationHints* hints):
	  _state(state), _hints(hints)
	  {
#if 0
		  if (hints)
		  {
			  OSG_NOTICE<<"Warning: TessellationHints ignored in present osg::ShapeDrawable implementation."<<std::endl;
		  }
#endif   
	  }

	  virtual void apply(const Sphere&);

	  State&                      _state;
	  const TessellationHints*    _hints;


	enum SphereHalf { SphereTopHalf, SphereBottomHalf };

	void drawHalfSphere(unsigned int numSegments, unsigned int numRows, float radius, SphereHalf which, float zOffset = 0.0f);
};

void MyDrawShapeVisitor::drawHalfSphere(unsigned int numSegments, unsigned int numRows, float radius, SphereHalf which, float zOffset)
{
	float lDelta = osg::PI/(float)numRows;
	float vDelta = 1.0f/(float)numRows;

	bool top = (which==SphereTopHalf);

	bool drawFrontFace = _hints ? _hints->getCreateFrontFace() : true;
	bool drawBackFace = _hints ? _hints->getCreateBackFace() : false;

	float angleDelta = osg::PI*2.0f/(float)numSegments;
	float texCoordHorzDelta = 1.0f/(float)numSegments;

	float lBase=-osg::PI*0.5f + (top?(lDelta*(numRows/2)):0.0f);
	float rBase=(top?(cosf(lBase)*radius):0.0f);
	float zBase=(top?(sinf(lBase)*radius):-radius);
	float vBase=(top?(vDelta*(numRows/2)):0.0f);
	float nzBase=(top?(sinf(lBase)):-1.0f);
	float nRatioBase=(top?(cosf(lBase)):0.0f);

	unsigned int rowbegin = top?numRows/2:0;
	unsigned int rowend   = top?numRows:numRows/2;

	GLBeginEndAdapter& gl = _state.getGLBeginEndAdapter();

	for(unsigned int rowi=rowbegin; rowi<rowend; ++rowi)
	{

		float lTop = lBase+lDelta;
		float rTop = cosf(lTop)*radius;
		float zTop = sinf(lTop)*radius;
		float vTop = vBase+vDelta;
		float nzTop= sinf(lTop);
		float nRatioTop= cosf(lTop);

		gl.Begin(GL_QUAD_STRIP);

		float angle = 0.0f;
		float texCoord = 0.0f;

		// The only difference between the font & back face loops is that the
		//  normals are inverted and the order of the vertex pairs is reversed.
		//  The code is mostly duplicated in order to hoist the back/front face 
		//  test out of the loop for efficiency

		if (drawFrontFace) {
			for(unsigned int topi=0; topi<numSegments;
				++topi,angle+=angleDelta,texCoord+=texCoordHorzDelta)
			{

				float c = cosf(angle);
				float s = sinf(angle);

				gl.Normal3f(c*nRatioTop,s*nRatioTop,nzTop);

				gl.TexCoord2f(texCoord,vTop);
				gl.Vertex3f(c*rTop,s*rTop,zTop+zOffset);

				gl.Normal3f(c*nRatioBase,s*nRatioBase,nzBase);

				gl.TexCoord2f(texCoord,vBase);
				gl.Vertex3f(c*rBase,s*rBase,zBase+zOffset);

			}

			// do last point by hand to ensure no round off errors.
			gl.Normal3f(nRatioTop,0.0f,nzTop);

			gl.TexCoord2f(1.0f,vTop);
			gl.Vertex3f(rTop,0.0f,zTop+zOffset);

			gl.Normal3f(nRatioBase,0.0f,nzBase);

			gl.TexCoord2f(1.0f,vBase);
			gl.Vertex3f(rBase,0.0f,zBase+zOffset);
		}

		if (drawBackFace) {
			for(unsigned int topi=0; topi<numSegments;
				++topi,angle+=angleDelta,texCoord+=texCoordHorzDelta)
			{

				float c = cosf(angle);
				float s = sinf(angle);

				gl.Normal3f(-c*nRatioBase,-s*nRatioBase,-nzBase);

				gl.TexCoord2f(texCoord,vBase);
				gl.Vertex3f(c*rBase,s*rBase,zBase+zOffset);

				gl.Normal3f(-c*nRatioTop,-s*nRatioTop,-nzTop);

				gl.TexCoord2f(texCoord,vTop);
				gl.Vertex3f(c*rTop,s*rTop,zTop+zOffset);
			}

			// do last point by hand to ensure no round off errors.
			gl.Normal3f(-nRatioBase,0.0f,-nzBase);

			gl.TexCoord2f(1.0f,vBase);
			gl.Vertex3f(rBase,0.0f,zBase+zOffset);

			gl.Normal3f(-nRatioTop,0.0f,-nzTop);

			gl.TexCoord2f(1.0f,vTop);
			gl.Vertex3f(rTop,0.0f,zTop+zOffset);

		}

		gl.End();

		lBase=lTop;
		rBase=rTop;
		zBase=zTop;
		vBase=vTop;
		nzBase=nzTop;
		nRatioBase=nRatioTop;

	}
}

void MyDrawShapeVisitor::apply( const Sphere& sphere )
{
	GLBeginEndAdapter& gl = _state.getGLBeginEndAdapter();

	gl.PushMatrix();

	gl.Translated(sphere.getCenter().x(),sphere.getCenter().y(),sphere.getCenter().z());

	bool drawFrontFace = _hints ? _hints->getCreateFrontFace() : true;
	bool drawBackFace = _hints ? _hints->getCreateBackFace() : false;

	//////////////////////////////////////////
	// Control the smoothness of sphere
	//
	unsigned int numSegments = 150;
	unsigned int numRows = 75;
	/////////////////////////////////////////////


	float ratio = (_hints ? _hints->getDetailRatio() : 1.0f);
	if (ratio > 0.0f && ratio != 1.0f) {
		numRows = (unsigned int) (numRows * ratio);
		numSegments = (unsigned int) (numSegments * ratio);
	}

	float lDelta = osg::PI/(float)numRows;
	float vDelta = 1.0f/(float)numRows;

	float angleDelta = osg::PI*2.0f/(float)numSegments;
	float texCoordHorzDelta = 1.0f/(float)numSegments;

	gl.Begin(GL_QUAD_STRIP);

	if (drawBackFace)
	{
		float lBase=-osg::PI*0.5f;
		float rBase=0.0f;
		float zBase=-sphere.getRadius();
		float vBase=0.0f;
		float nzBase=-1.0f;
		float nRatioBase=0.0f;

		for(unsigned int rowi=0; rowi<numRows; ++rowi)
		{

			float lTop = lBase+lDelta;
			float rTop = cosf(lTop)*sphere.getRadius();
			float zTop = sinf(lTop)*sphere.getRadius();
			float vTop = vBase+vDelta;
			float nzTop= sinf(lTop);
			float nRatioTop= cosf(lTop);

			gl.Begin(GL_QUAD_STRIP);

			float angle = 0.0f;
			float texCoord = 0.0f;

			for(unsigned int topi=0; topi<numSegments;
				++topi,angle+=angleDelta,texCoord+=texCoordHorzDelta)
			{

				float c = cosf(angle);
				float s = sinf(angle);

				gl.Normal3f(-c*nRatioBase,-s*nRatioBase,-nzBase);

				gl.TexCoord2f(texCoord,vBase);
				gl.Vertex3f(c*rBase,s*rBase,zBase);

				gl.Normal3f(-c*nRatioTop,-s*nRatioTop,-nzTop);

				gl.TexCoord2f(texCoord,vTop);
				gl.Vertex3f(c*rTop,s*rTop,zTop);


			}


			// do last point by hand to ensure no round off errors.
			gl.Normal3f(-nRatioBase,0.0f,-nzBase);

			gl.TexCoord2f(1.0f,vBase);
			gl.Vertex3f(rBase,0.0f,zBase);

			gl.Normal3f(-nRatioTop,0.0f,-nzTop);

			gl.TexCoord2f(1.0f,vTop);
			gl.Vertex3f(rTop,0.0f,zTop);

			gl.End();


			lBase=lTop;
			rBase=rTop;
			zBase=zTop;
			vBase=vTop;
			nzBase=nzTop;
			nRatioBase=nRatioTop;

		}
	}


	if (drawFrontFace)
	{
		float lBase=-osg::PI*0.5f;
		float rBase=0.0f;
		float zBase=-sphere.getRadius();
		float vBase=0.0f;
		float nzBase=-1.0f;
		float nRatioBase=0.0f;

		for(unsigned int rowi=0; rowi<numRows; ++rowi)
		{

			float lTop = lBase+lDelta;
			float rTop = cosf(lTop)*sphere.getRadius();
			float zTop = sinf(lTop)*sphere.getRadius();
			float vTop = vBase+vDelta;
			float nzTop= sinf(lTop);
			float nRatioTop= cosf(lTop);

			gl.Begin(GL_QUAD_STRIP);

			float angle = 0.0f;
			float texCoord = 0.0f;

			for(unsigned int topi=0; topi<numSegments;
				++topi,angle+=angleDelta,texCoord+=texCoordHorzDelta)
			{

				float c = cosf(angle);
				float s = sinf(angle);

				gl.Normal3f(c*nRatioTop,s*nRatioTop,nzTop);

				gl.TexCoord2f(texCoord,vTop);
				gl.Vertex3f(c*rTop,s*rTop,zTop);

				gl.Normal3f(c*nRatioBase,s*nRatioBase,nzBase);

				gl.TexCoord2f(texCoord,vBase);
				gl.Vertex3f(c*rBase,s*rBase,zBase);

			}

			// do last point by hand to ensure no round off errors.
			gl.Normal3f(nRatioTop,0.0f,nzTop);

			gl.TexCoord2f(1.0f,vTop);
			gl.Vertex3f(rTop,0.0f,zTop);

			gl.Normal3f(nRatioBase,0.0f,nzBase);

			gl.TexCoord2f(1.0f,vBase);
			gl.Vertex3f(rBase,0.0f,zBase);

			gl.End();


			lBase=lTop;
			rBase=rTop;
			zBase=zTop;
			vBase=vTop;
			nzBase=nzTop;
			nRatioBase=nRatioTop;

		}
	}

	gl.PopMatrix();
}

void MySphereDrawable::drawImplementation(RenderInfo& renderInfo) const
{
	osg::State& state = *renderInfo.getState();
	GLBeginEndAdapter& gl = state.getGLBeginEndAdapter();

	if (_shape.valid())
	{
		gl.Color4fv(_color.ptr());

		MyDrawShapeVisitor dsv(state,_tessellationHints.get());

		_shape->accept(dsv);
	}
}