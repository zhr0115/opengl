#include <stdio.h>
#include <gl/glAll.h>

#define example1 0		//TRIANGLE
#define example2 0		//LINE_STRIP
#define example3 0		//CIRCLE
#define example4 0		//QUAD_STRIP
#define example5 0		//CUBE
#define example6 0		//Geometric transformation 2d
#define example7 0		//Geometric transformation 3d
#define example8 0		//Display mode 2d
#define example9 0		//Display mode 3d
#define example10 0		//Geometric representation 3d
#define example11 0		//Solar
#define example12 0		//Color cube
#define example13 1		//Bolt


// Define a constant for the value of PI
#define GL_PI 3.1415f

// Rotation amounts
static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;

#if example1
GLuint VBO;

/**
* 渲染回调函数
*/
static void RenderScenceCB() {
	// 清空颜色缓存
	glClear(GL_COLOR_BUFFER_BIT);

	// 开启顶点属性
	glEnableVertexAttribArray(0);
	// 绑定GL_ARRAY_BUFFER缓冲器
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// 告诉管线怎样解析bufer中的数据
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// 开始绘制几何图形(绘制一个三角形，三个顶点)
	glDrawArrays(GL_TRIANGLES, 0, 3);

	//  禁用顶点数据
	glDisableVertexAttribArray(0);

	// 交换前后缓存
	glutSwapBuffers();

	glFlush();
}

/**
* 创建顶点缓冲器
*/
static void CreateVertexBuffer()
{
	// 创建含有3个顶点的顶点数组
	Vector3f Vertices[3];
	// 三角形的三个顶点位置
	Vertices[0] = Vector3f(-1.0f, -1.0f, 0.0f);
	Vertices[1] = Vector3f(1.0f, -1.0f, 0.0f);
	Vertices[2] = Vector3f(0.0f, 1.0f, 0.0f);

	// 创建缓冲器
	glGenBuffers(1, &VBO);
	// 绑定GL_ARRAY_BUFFER缓冲器
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// 绑定顶点数据
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
}

/**
* 主函数
*/
int main(int argc, char ** argv) {

	// 初始化GLUT
	glutInit(&argc, argv);

	// 显示模式：双缓冲、RGBA
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

	// 窗口设置
	glutInitWindowSize(480, 320);      // 窗口尺寸
	glutInitWindowPosition(100, 100);  // 窗口位置
	glutCreateWindow("Tutorial 03");   // 窗口标题

									   // 开始渲染
	glutDisplayFunc(RenderScenceCB);

	// 缓存清空后的颜色值
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	// 检查GLEW是否就绪，必须要在GLUT初始化之后！
	GLenum res = glewInit();
	if (res != GLEW_OK) {
		fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
		return 1;
	}

	// 创建顶点缓冲器
	CreateVertexBuffer();

	// 通知开始GLUT的内部循环
	glutMainLoop();

	return 0;
}
#endif

#if example2
void SetupRC()
{
	glClearColor(1, 1, 1,0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0, 200, 0, 150);
}

void RenderScene()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1, 0, 0);

	const GLfloat Point1[] = { 180, 15 };
	const GLfloat Point2[] = { 10, 150 };
	const GLfloat Point3[] = { 10, 15 };

	glBegin(GL_LINE_STRIP);
	//glVertex2f(180, 15);
	//glVertex2f(10, 150);
	//glVertex2f(10, 15);
	glVertex2fv(Point1);
	glVertex2fv(Point2);
	glVertex2fv(Point3);
	glEnd();

	glFlush();
}

int main(int argc,char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowPosition(50, 100);
	glutInitWindowSize(400, 300);
	glutCreateWindow("example2");

	SetupRC();
	glutDisplayFunc(RenderScene);
	glutMainLoop();
}
#endif

#if example3

#if 0
class screenPt
{
public:
	screenPt() { x = y = 0; }
	void setCoords(GLint xCoordValue, GLint yCoordValue)
	{
		x = xCoordValue;
		y = yCoordValue;
	}
	GLint getx() const { return x; }
	GLint gety() const { return y; }
	void incrementx() { x++; }
	void decrementy() { y--; }
	GLint x, y;
protected:
private:
	//GLint x, y;
};

void setPixel(GLint xCoord, GLint yCoord)
{
	glBegin(GL_LINES);
	glVertex2i(xCoord, yCoord);
	glEnd();
}

void circlePlotPoints(GLint xc, GLint yc, screenPt circPt)
{
	setPixel(xc + circPt.getx(), yc + circPt.gety());
	setPixel(xc - circPt.getx(), yc + circPt.gety());
	setPixel(xc + circPt.getx(), yc - circPt.gety());
	setPixel(xc - circPt.getx(), yc - circPt.gety());
	setPixel(xc + circPt.gety(), yc + circPt.getx());
	setPixel(xc - circPt.gety(), yc + circPt.getx());
	setPixel(xc + circPt.gety(), yc - circPt.getx());
	setPixel(xc - circPt.gety(), yc - circPt.getx());
}

void circleMidPoint(GLint xc, GLint yc, GLint radius)
{
	screenPt circPt;

	GLint p = 1 - radius;

	circPt.setCoords(0, radius);

	circlePlotPoints(xc, yc, circPt);
	while (circPt.getx() < circPt.gety())
	{
		circPt.incrementx();
		if (p < 0)
			p += 2 * circPt.getx() + 1;
		else
		{
			circPt.decrementy();
			p += 2 * (circPt.getx() - circPt.gety()) + 1;
		}
		circlePlotPoints(xc, yc, circPt);
	}
}

void lineSegment(screenPt pt1, screenPt pt2)
{
	glBegin(GL_LINES);
	glVertex2i(pt1.getx(), pt1.gety());
	glVertex2i(pt2.getx(), pt2.gety());
	glEnd();
}

void drawCurve(GLint curveNum)
{
	const GLdouble twoPi = 6.283185;
	const GLint a = 175, b = 60;

	GLfloat r, theta, dtheta = 1.0 / float(a);
	GLint x0 = 200, y0 = 250;
	screenPt curvePt[2];

	curvePt[0].x = x0;
	curvePt[0].y = y0;

	glColor3f(1, 1, 1);

	switch (curveNum)
	{
	case 1:
		curvePt[0].x += a + b;
		break;
	case 2:
		curvePt[0].x += a + a;
		break;
	default:
		break;
	}

	theta = dtheta;
	while (theta<twoPi)
	{
		switch (curveNum)
		{
		case 1:
			r = a*cos(theta) + b;
			break;
		default:
			break;
		}

		curvePt[1].x = x0 + r*cos(theta);
		curvePt[1].y = y0 + r*sin(theta);
		lineSegment(curvePt[0], curvePt[1]);
		curvePt[0] = curvePt[1];
		theta += dtheta;
	}
}

void Init()
{
	glClearColor(1, 1, 1, 1);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 600, 0, 500);
}

void Plot()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1, 0, 0);

	//const GLfloat point[] = { 100,100 };
	//const GLfloat r = 50;
	//circleMidPoint(point[0], point[1], r);

	drawCurve(1);

	glBegin(GL_TRIANGLES);
	glVertex2i(10, 100);
	glVertex2i(100, 100);
	glVertex2i(50, 200);
	glEnd();

	glFlush();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(600, 500);
	glutCreateWindow("circle");

	Init();
	glutDisplayFunc(Plot);
	glutMainLoop();
}
#endif

#if 1 
class screenPt
{
public:
	screenPt() { x = y = 0; }
	void setCoords(GLint xCoordValue, GLint yCoordValue)
	{
		x = xCoordValue;
		y = yCoordValue;
	}
	GLint getx() const { return x; }
	GLint gety() const { return y; }
	void incrementx() { x++; }
	void decrementy() { y--; }
protected:
private:
	GLint x, y;
};

void setPixel(GLint xCoord, GLint yCoord,GLint xCoord1,GLint yCoord1)
{
	glBegin(GL_LINES);
	glVertex2i(xCoord, yCoord);
	glVertex2i(xCoord1, yCoord1);
	glEnd();
}

void circlePlotPoints(GLint xc, GLint yc, screenPt circPt,screenPt circPt1)
{
	setPixel(xc + circPt.getx(), yc + circPt.gety(), xc + circPt1.getx(), yc + circPt1.gety());
	setPixel(xc - circPt.getx(), yc + circPt.gety(), xc - circPt1.getx(), yc + circPt1.gety());
	setPixel(xc + circPt.getx(), yc - circPt.gety(), xc + circPt1.getx(), yc - circPt1.gety());
	setPixel(xc - circPt.getx(), yc - circPt.gety(), xc - circPt1.getx(), yc - circPt1.gety());
	setPixel(xc + circPt.gety(), yc + circPt.getx(), xc + circPt1.gety(), yc + circPt1.getx());
	setPixel(xc - circPt.gety(), yc + circPt.getx(), xc - circPt1.gety(), yc + circPt1.getx());
	setPixel(xc + circPt.gety(), yc - circPt.getx(), xc + circPt1.gety(), yc - circPt1.getx());
	setPixel(xc - circPt.gety(), yc - circPt.getx(), xc - circPt1.gety(), yc - circPt1.getx());
}

void circleMidPoint(GLint xc, GLint yc, GLint radius)
{
	screenPt circPt;
	screenPt circPt1;

	GLint p = 1 - radius;

	circPt.setCoords(0, radius);
	circPt1.setCoords(0, radius);

	//circlePlotPoints(xc, yc, circPt);
	while (circPt1.getx() < circPt1.gety())
	{
		circPt1.incrementx();
		if (p < 0)
			p += 2 * circPt1.getx() + 1;
		else
		{
			circPt1.decrementy();
			p += 2 * (circPt1.getx() - circPt1.gety()) + 1;
		}
		circlePlotPoints(xc, yc, circPt,circPt1);
		circPt = circPt1;
	}
}

void SetupRC()
{
	glClearColor(1, 1, 1, 0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0, 200, 0, 200);
}

void RenderScene()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1, 0, 0);

	const GLfloat point[] = { 100,100 };
	const GLfloat r = 50;

	circleMidPoint(point[0], point[1], r);

	glFlush();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowPosition(50, 100);
	glutInitWindowSize(400, 300);
	glutCreateWindow("circle");

	SetupRC();
	glutDisplayFunc(RenderScene);
	glutMainLoop();
}
#endif

#endif

#if example4
void SetupRC()
{
	glClearColor(1, 1, 1, 0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0, 200, 0, 150);
}

void RenderScene()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1, 0, 0);

	const GLint p1[] = { 100,110 };
	const GLint p2[] = { 100,100 };
	const GLint p3[] = { 110,100 };
	const GLint p4[] = { 110,105 };
	//const GLint p1[] = { 50,120 };
	//const GLint p2[] = { 50,50 };
	//const GLint p3[] = { 150,50 };
	//const GLint p4[] = { 150,130 };
	const GLint p5[] = { 120,105 };
	const GLint p6[] = { 120,101 };
	const GLint p7[] = { 130,90 };
	const GLint p8[] = { 130,120 };

	glBegin(GL_QUAD_STRIP);
	//glVertex2iv(p1);
	//glVertex2iv(p2);
	////glColor3f(0, 1, 0);
	//glVertex2iv(p3);
	//glVertex2iv(p4);
	//glVertex2iv(p5);
	//glVertex2iv(p6);
	//glVertex2iv(p7);
	//glVertex2iv(p8);
	//需要逆时针
	glVertex2iv(p1);
	glVertex2iv(p2);
	glColor3f(0, 1, 0);
	glVertex2iv(p4);
	glVertex2iv(p3);
	glVertex2iv(p5);
	glVertex2iv(p6);
	glVertex2iv(p8);
	glVertex2iv(p7);

	glEnd();

	glFlush();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowPosition(50, 100);
	glutInitWindowSize(400, 300);
	glutCreateWindow("Quad");

	SetupRC();
	glutDisplayFunc(RenderScene);
	glutMainLoop();
}
#endif

#if example5

GLint point[8][3] = { { 0,0,0 },{ 0,1,0 },{ 1,0,0 },{ 1,1,0 },{ 0,0,1 },{ 0,1,1 },{ 1,0,1 },{ 1,1,1 } };

typedef GLint vertex3[3];
vertex3 pt[8] = { { 0,0,0 },{ 0,1,0 },{ 1,0,0 },{ 1,1,0 },{ 0,0,1 },{ 0,1,1 },{ 1,0,1 },{ 1,1,1 } };

void SetupRC()
{
	glClearColor(1, 1, 1, 0);
	glMatrixMode(GL_MODELVIEW);
	glRotated(10, 1, 1, 1);
	//glMatrixMode(GL_PROJECTION);
	gluOrtho2D(-5, 5, -5, 5);
}

void quad(GLint n1, GLint n2, GLint n3, GLint n4)
{
	glBegin(GL_QUADS);
	glVertex3iv(pt[n1]);
	glVertex3iv(pt[n2]);
	glVertex3iv(pt[n3]);
	glVertex3iv(pt[n4]);
	glEnd();
}

void cube()
{
	quad(6, 2, 3, 7);
	quad(5, 1, 0, 4);
	quad(7, 3, 1, 5);
	quad(4, 0, 2, 6);
	quad(2, 0, 1, 3);
	quad(7, 5, 4, 6);
}

void RenderScene()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1, 0, 0);

	//cube();
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_INT, 0, pt);
	GLubyte vertIndex[] = { 6,2,3,7,5,1,0,4,7,3,1,5,4,0,2,6,2,0,1,3,7,5,4,6 };
	glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, vertIndex);

	glFlush();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowPosition(50, 100);
	glutInitWindowSize(400, 300);
	glutCreateWindow("cube");

	SetupRC();
	glutDisplayFunc(RenderScene);
	glutMainLoop();
}
#endif

#if example6
class wcPt2D
{
public:
	GLfloat x, y;
protected:
private:
};

void translatePolygon(wcPt2D *verts, GLint nVerts, GLfloat tx, GLfloat ty)
{
	GLint k;

	for (k = 0; k < nVerts; k++)
	{
		verts[k].x += tx;
		verts[k].y += ty;
	}
	glBegin(GL_POLYGON);
		for (k = 0; k < nVerts; k++)
		{
			glVertex2f(verts[k].x, verts[k].y);
		}
	glEnd();
}

void rotatePolygon(wcPt2D *verts, GLint nVerts, wcPt2D pivPt, GLdouble theta)
{
	wcPt2D vertsRot[3];
	GLint k;

	for (k = 0; k < nVerts; k++)
	{
		vertsRot[k].x = pivPt.x + (verts[k].x - pivPt.x)*cos(theta) - (verts[k].y - pivPt.y)*sin(theta);
		vertsRot[k].y = pivPt.y + (verts[k].x - pivPt.x)*sin(theta) + (verts[k].y - pivPt.y)*cos(theta);
	}

	glBegin(GL_POLYGON);
	for (k = 0; k < nVerts; k++)
	{
		glVertex2f(vertsRot[k].x, vertsRot[k].y);
	}
	glEnd();
}

void scalePolygon(wcPt2D *verts, GLint nVerts, wcPt2D fixedPt, GLfloat sx, GLfloat sy)
{
	wcPt2D vertsNew[3];
	GLint k;

	for (k = 0; k < nVerts; k++)
	{
		vertsNew[k].x = verts[k].x*sx + fixedPt.x*(1 - sx);
		vertsNew[k].y = verts[k].y*sy + fixedPt.y*(1 - sy);
	}

	glBegin(GL_POLYGON);
	for (k = 0; k < nVerts; k++)
	{
		glVertex2f(vertsNew[k].x, vertsNew[k].y);
	}
	glEnd();
}

void SetupRC()
{
	glClearColor(1, 1, 1, 0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0, 225, 0, 225);
}
 
void RenderScene()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1, 0, 0);

	wcPt2D v[3] = { {10,10},{100,100},{10,100} };

	//translatePolygon(v, 3, -10, -10);
	//wcPt2D pivotPot = { 10,10 };
	//rotatePolygon(v, 3, pivotPot, -10/180.0*3.14);
	wcPt2D fixedPt = { 10,10 };
	scalePolygon(v, 3, fixedPt, 2, 1.5);

	glFlush();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowPosition(50, 100);
	glutInitWindowSize(600, 600);
	glutCreateWindow("translation2d");

	SetupRC();
	glutDisplayFunc(RenderScene);
	glutMainLoop();
}
#endif

#if example7
class wcPt3D 
{
public:
	GLfloat x, y, z;
};

typedef GLfloat Matrix4x4[4][4];

Matrix4x4 matComposite;

void matrix4x4SetIdentity(Matrix4x4 matIdent4x4)
{
	GLint row, col;
	for (row = 0; row < 4; row++)
	{
		for (col = 0; col < 4; col++)
		{
			matIdent4x4[row][col] = (row == col);
		}
	}
}

void matrix4x4PreMultiply(Matrix4x4 m1, Matrix4x4 m2)
{
	GLint row, col;
	Matrix4x4 matTemp;

	for (row = 0; row < 4; row++)
	{
		for (col = 0; col < 4; col++)
		{
			matTemp[row][col] = m1[row][0] * m2[0][col] + m1[row][1] * m2[1][col] + m1[row][2] * m2[2][col] + m1[row][3] * m2[3][col];
		}
	}

	for (row = 0; row < 4; row++)
	{
		for (col = 0; col < 4; col++)
		{
			m2[row][col] = matTemp[row][col];
		}
	}
}

void translate3D(GLfloat tx, GLfloat ty, GLfloat tz)
{
	Matrix4x4 matTrans3D;
	matrix4x4SetIdentity(matTrans3D);

	matTrans3D[0][3] = tx;
	matTrans3D[1][3] = ty;
	matTrans3D[2][3] = tz;

	matrix4x4PreMultiply(matTrans3D, matComposite);
}

void rotate3D(wcPt3D p1, wcPt3D p2, GLfloat radianAngle)
{
	Matrix4x4 matTemp;
	GLfloat axisVertLength = sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2) + pow(p2.z - p1.z, 2));
	GLfloat cosA = cos(radianAngle);
	GLfloat oneC = 1 - cosA;
	GLfloat sinA = sin(radianAngle);
	GLfloat ux = (p2.x - p1.x) / axisVertLength;
	GLfloat uy = (p2.y - p1.y) / axisVertLength;
	GLfloat uz = (p2.z - p1.z) / axisVertLength;

	translate3D(-p1.x, -p1.y, -p1.z);
	matrix4x4SetIdentity(matTemp);

	matTemp[0][0] = ux*ux*oneC + cosA;
	matTemp[0][1] = ux*uy*oneC - uz* sinA;
	matTemp[0][2] = ux*uz*oneC + uy*sinA;
	matTemp[1][0] = uy*ux*oneC + uz*sinA;
	matTemp[1][1] = uy*uy*oneC + cosA;
	matTemp[1][2] = uy*uz*oneC - ux*sinA;
	matTemp[2][0] = uz*ux*oneC - uy*sinA;
	matTemp[2][1] = uz*uy*oneC + ux*sinA;
	matTemp[2][2] = uz*uz*oneC + cosA;

	matrix4x4PreMultiply(matTemp, matComposite);
	translate3D(p1.x, p1.y, p1.z);
}

void scale3D(GLfloat sx, GLfloat sy, GLfloat sz,wcPt3D fixedPt)
{
	Matrix4x4 matScale3D;
	matrix4x4SetIdentity(matScale3D);

	matScale3D[0][0] = sx;
	matScale3D[0][3] = (1 - sx)*fixedPt.x;
	matScale3D[1][1] = sy;
	matScale3D[1][3] = (1 - sy)*fixedPt.y;
	matScale3D[2][2] = sz;
	matScale3D[2][3] = (1 - sz)*fixedPt.z;

	matrix4x4PreMultiply(matScale3D, matComposite);
}

GLfloat point[8][3] = { { 0,0,0 },{ 0,1,0 },{ 1,0,0 },{ 1,1,0 },{ 0,0,1 },{ 0,1,1 },{ 1,0,1 },{ 1,1,1 } };

typedef GLfloat vertex3[3];
vertex3 pt[8] = { { 0,0,0 },{ 0,1,0 },{ 1,0,0 },{ 1,1,0 },{ 0,0,1 },{ 0,1,1 },{ 1,0,1 },{ 1,1,1 } };

void SetupRC()
{
	glClearColor(1, 1, 1, 0);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	gluOrtho2D(-5, 15, -5, 15);
}

void matrixMultPoint(Matrix4x4 mat, vertex3 pt)
{
	GLint row, col;
	vertex3 temppt;

	for (row = 0; row < 3; row++)
	{
		temppt[row] = 0;
		for (col = 0; col < 3; col++)
		{
			temppt[row] += mat[row][col] * pt[col];
		}
		temppt[row] += mat[row][4];
	}

	for (row = 0; row < 3; row++)
	{
		pt[row] = temppt[row];
	}
}

void RenderScene()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1, 0, 0);

	//glEnableClientState(GL_VERTEX_ARRAY);
	//glVertexPointer(3, GL_INT, 0, pt);
	//GLubyte vertIndex[] = { 6,2,3,7,5,1,0,4,7,3,1,5,4,0,2,6,2,0,1,3,7,5,4,6 };
	//glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, vertIndex);

	matrix4x4SetIdentity(matComposite);

	wcPt3D p1 = { 1,1,1 };
	wcPt3D p2 = { 0,0,1 };
	rotate3D(p1, p2, 3.14 * 10 / 180);
	scale3D(1, 2, 3, p1);

	for (GLint i = 0; i < 8; i++)
	{
		matrixMultPoint(matComposite, pt[i]);
	}

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, pt);
	GLubyte vertIndex[] = { 6,2,3,7,5,1,0,4,7,3,1,5,4,0,2,6,2,0,1,3,7,5,4,6 };
	glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, vertIndex);

	glFlush();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowPosition(50, 100);
	glutInitWindowSize(800, 600);
	glutCreateWindow("geometric transformation 3d");

	SetupRC();
	glutDisplayFunc(RenderScene);

	GLint index = glutGetWindow();
	glutMainLoop();
}
#endif

#if example8
class wcPt2D
{
public:
	GLfloat x, y;
protected:
private:
};

void SetupRC()
{
	glClearColor(1, 1, 1, 0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(-100, 100, -100, 100);
	glMatrixMode(GL_MODELVIEW);
}

void triangle(wcPt2D *verts)
{
	glBegin(GL_TRIANGLES);

	for (GLint i = 0; i < 3; i++)
	{
		glVertex2f(verts[i].x, verts[i].y);
	}
	glEnd();
}

void RenderScene()
{
	wcPt2D verts[3] = { {-50,-25},{50,-25 },{0,50} };

	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1, 0, 0);

	glViewport(0, 0, 300, 300);
	triangle(verts);

	glColor3f(0, 0, 1);
	glViewport(300, 0, 300, 300);
	glRotatef(90, 0, 0, 1);
	triangle(verts);

	glFlush();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(600, 300);
	glutCreateWindow("Display mode");
	//glutFullScreen();

	SetupRC();
	glutDisplayFunc(RenderScene);

	glutMainLoop();
}
#endif

#if example9
GLint winWidth = 600, winHeight = 600;
GLfloat x0 = 100, y_0 = 50, z0 = 50;		//Viewing-coordinate origin
GLfloat xref = 50, yref = 50, zref = 0;	//Look-at point
GLfloat Vx = 0, Vy = 1, Vz = 0;			//View-up vector
GLfloat xwMin = -40, ywMin = -60, xwMax = 40, ywMax = 60, dNear = 25, dFar = 125;		//clipping space

void SetupRC()
{
	glClearColor(1, 1, 1, 0);
	glMatrixMode(GL_MODELVIEW);
	gluLookAt(x0, y_0, z0, xref, yref, zref, Vx, Vy, Vz);

	glMatrixMode(GL_PROJECTION);
	glFrustum(xwMin, xwMax, ywMin, ywMax, dNear, dFar);
}

void RenderScene()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0, 1, 0);

	glPolygonMode(GL_FRONT, GL_FILL);
	glPolygonMode(GL_BACK, GL_LINE);

	glBegin(GL_QUADS);
	glVertex3f(0, 0, 0);
	glVertex3f(100, 0, 0);
	glVertex3f(100, 100, 0);
	glVertex3f(0, 100, 0);
	glEnd();

	glFlush();
}

void ChangeSize(GLint newWidth, GLint newHeight)
{
	glViewport(0, 0, newWidth, newHeight);

	winWidth = newWidth;
	winHeight = newHeight;
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowPosition(50, 100);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("Display mode 3d");

	SetupRC();
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);
	glutMainLoop();
}
#endif

#if example10
void SetupRC()
{
	//材质反光性设置
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };  //镜面反射参数
	GLfloat mat_shininess[] = { 50.0 };               //高光指数
	GLfloat light_position[] = { 10.0, 10.0, 1.0, 0.0 };
	GLfloat white_light[] = { 1.0, 1.0, 1.0, 1.0 };   //灯位置(1,1,1), 最后1-开关
	GLfloat Light_Model_Ambient[] = { 1, 1, 1, 1.0 }; //环境光参数

	glClearColor(1, 1, 1, 1);  //背景色
	glShadeModel(GL_SMOOTH);           //多变性填充模式

									   //材质属性
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

	//灯光设置
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);   //散射光属性
	glLightfv(GL_LIGHT0, GL_SPECULAR, white_light);  //镜面反射光
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, Light_Model_Ambient);  //环境光参数

	glEnable(GL_LIGHTING);   //开关:使用光
	glEnable(GL_LIGHT0);     //打开0#灯
	glEnable(GL_DEPTH_TEST); //打开深度测试

}

void RenderScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(0, 1, 0);

	//glutSolidTeapot(0.5);

	//gluLookAt(-2,-2, -2, 0, 0, 0, 0, 1, 0);

	glPolygonMode(GL_FRONT, GL_FILL);
	//glPolygonMode(GL_BACK, GL_LINE);

	glScalef(1.5, 2, 1);
	glutWireCube(1);
	glutSolidCube(1);

	glScalef(0.8, 0.5, 0.8);
	glTranslatef(-6, -5, 0);
	glutSolidDodecahedron();

	glTranslatef(8.6, 8.6, 2);
	glutSolidTetrahedron();

	glTranslatef(-3, -1, 0);
	glutSolidOctahedron();

	glScalef(0.8, 0.8, 1);
	glTranslatef(4.3, -2, 0.5);
	glutSolidIcosahedron();

	glCullFace(GL_BACK);

	glFlush();
}

void ChangeSize(GLint w, GLint h)
{
	GLfloat nRange = 10.0f;

	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (h == 0)
		h = 1;
	if (w <= h)
	{
		glOrtho(-nRange, nRange, -nRange * (GLfloat)h / (GLfloat)w, nRange * (GLfloat)h / (GLfloat)w, -nRange, nRange);
	}
	else
	{
		glOrtho(-nRange * (GLfloat)h / (GLfloat)w, nRange * (GLfloat)h / (GLfloat)w, -nRange, nRange, -nRange, nRange);
	}

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void SpecialKeys(int key, int x, int y)
{
	if (key == GLUT_KEY_UP)
		xRot -= 5.0f;

	if (key == GLUT_KEY_DOWN)
		xRot += 5.0f;

	if (key == GLUT_KEY_LEFT)
		yRot -= 5.0f;

	if (key == GLUT_KEY_RIGHT)
		yRot += 5.0f;

	if (key > 356.0f)
		xRot = 0.0f;

	if (key < -1.0f)
		xRot = 355.0f;

	if (key > 356.0f)
		yRot = 0.0f;

	if (key < -1.0f)
		yRot = 355.0f;

	// Refresh the Window
	glutPostRedisplay();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Display mode 3d");

	SetupRC();
	glutSpecialFunc(SpecialKeys);
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);
	glutMainLoop();
}
#endif

#if example11

// Lighting values
GLfloat  whiteLight[] = { 0.2f, 0.2f, 0.2f, 1.0f };
GLfloat  sourceLight[] = { 0.8f, 0.8f, 0.8f, 1.0f };
GLfloat	 lightPos[] = { 0.0f, 0.0f, 0.0f, 1.0f };

void SetupRC()
{
	// Light values and coordinates
	glEnable(GL_DEPTH_TEST);	// Hidden surface removal
	glFrontFace(GL_CCW);		// Counter clock-wise polygons face out
	glEnable(GL_CULL_FACE);		// Do not calculate inside of jet

								// Enable lighting
	glEnable(GL_LIGHTING);

	// Setup and enable light 0
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, whiteLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, sourceLight);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	glEnable(GL_LIGHT0);

	// Enable color tracking
	glEnable(GL_COLOR_MATERIAL);

	// Set Material properties to follow glColor values
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	// Black blue background
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void TimerFunc(int value)
{
	glutPostRedisplay();
	glutTimerFunc(100, TimerFunc, 1);
}

void RenderScene()
{
	static float fMoonRot = 0.0f;
	static float fEarthRot = 0.0f;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

	glTranslatef(0.0f, 0.0f, -300.0f);
	glColor3f(1, 0, 0);
	glutSolidSphere(15.0f, 15, 15);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

	glRotatef(fEarthRot, 0.0f, 1.0f, 0.0f);

	glColor3f(0, 0, 1);
	glTranslatef(105.f, 0.0f, 0.0f);
	glutSolidSphere(12.0f, 15, 15);

	glColor3f(1, 1, 1);
	glRotatef(fMoonRot, 0.0f, 1.0f, 0.0f);
	glTranslatef(30.0f, 0.0f, 0.0f);

	fMoonRot += 15.0f;
	if (fMoonRot>360.0f)
	{
		fMoonRot -= 360.0f;
	}
	glutSolidSphere(6.0f, 15, 15);

	glPopMatrix();

	fEarthRot += 5.0f;
	if (fEarthRot>360.0f)
	{
		fEarthRot -= 360.0f;
	}

	glutSwapBuffers();
}

void ChangeSize(GLint w, GLint h)
{
	GLfloat fAspect;

	glViewport(0, 0, w, h);

	if (h == 0)
		h = 1;

	fAspect = (GLfloat)w / (GLfloat)h;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(45.0f, fAspect, 1.0, 425.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Earth/Moon/Sun System");
	glutReshapeFunc(ChangeSize);
	glutDisplayFunc(RenderScene);
	glutTimerFunc(250, TimerFunc, 1);
	SetupRC();
	glutMainLoop();

	return 0;
}
#endif

#if example12
// Called to draw scene
void RenderScene(void)
{
	// Clear the window with current clearing color
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();

	glRotatef(xRot, 1.0f, 0.0f, 0.0f);
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);

	glShadeModel(GL_SMOOTH);

	// Draw six quads
	glBegin(GL_QUADS);
	// Front Face
	// White
	glColor3ub((GLubyte)255, (GLubyte)255, (GLubyte)255);
	glVertex3f(50.0f, 50.0f, 50.0f);

	// Yellow
	glColor3ub((GLubyte)255, (GLubyte)255, (GLubyte)0);
	glVertex3f(50.0f, -50.0f, 50.0f);

	// Red
	glColor3ub((GLubyte)255, (GLubyte)0, (GLubyte)0);
	glVertex3f(-50.0f, -50.0f, 50.0f);

	// Magenta
	glColor3ub((GLubyte)255, (GLubyte)0, (GLubyte)255);
	glVertex3f(-50.0f, 50.0f, 50.0f);


	// Back Face
	// Cyan
	glColor3f(0.0f, 1.0f, 1.0f);
	glVertex3f(50.0f, 50.0f, -50.0f);

	// Green
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(50.0f, -50.0f, -50.0f);

	// Black
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex3f(-50.0f, -50.0f, -50.0f);

	// Blue
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(-50.0f, 50.0f, -50.0f);

	// Top Face
	// Cyan
	glColor3f(0.0f, 1.0f, 1.0f);
	glVertex3f(50.0f, 50.0f, -50.0f);

	// White
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(50.0f, 50.0f, 50.0f);

	// Magenta
	glColor3f(1.0f, 0.0f, 1.0f);
	glVertex3f(-50.0f, 50.0f, 50.0f);

	// Blue
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(-50.0f, 50.0f, -50.0f);

	// Bottom Face
	// Green
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(50.0f, -50.0f, -50.0f);

	// Yellow
	glColor3f(1.0f, 1.0f, 0.0f);
	glVertex3f(50.0f, -50.0f, 50.0f);

	// Red
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(-50.0f, -50.0f, 50.0f);

	// Black
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex3f(-50.0f, -50.0f, -50.0f);

	// Left face
	// White
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(50.0f, 50.0f, 50.0f);

	// Cyan
	glColor3f(0.0f, 1.0f, 1.0f);
	glVertex3f(50.0f, 50.0f, -50.0f);

	// Green
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(50.0f, -50.0f, -50.0f);

	// Yellow
	glColor3f(1.0f, 1.0f, 0.0f);
	glVertex3f(50.0f, -50.0f, 50.0f);

	// Right face
	// Magenta
	glColor3f(1.0f, 0.0f, 1.0f);
	glVertex3f(-50.0f, 50.0f, 50.0f);

	// Blue
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(-50.0f, 50.0f, -50.0f);

	// Black
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex3f(-50.0f, -50.0f, -50.0f);

	// Red
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(-50.0f, -50.0f, 50.0f);
	glEnd();

	glPopMatrix();

	// Show the graphics
	glutSwapBuffers();
	}

// This function does any needed initialization on the rendering
// context. 
void SetupRC()
{
	// Black background
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_DITHER);
	glShadeModel(GL_SMOOTH);
}

/////////////////////////////////////////////////
// Get Arrow Keys
void SpecialKeys(int key, int x, int y)
{
	if (key == GLUT_KEY_UP)
		xRot -= 5.0f;

	if (key == GLUT_KEY_DOWN)
		xRot += 5.0f;

	if (key == GLUT_KEY_LEFT)
		yRot -= 5.0f;

	if (key == GLUT_KEY_RIGHT)
		yRot += 5.0f;

	if (key > 356.0f)
		xRot = 0.0f;

	if (key < -1.0f)
		xRot = 355.0f;

	if (key > 356.0f)
		yRot = 0.0f;

	if (key < -1.0f)
		yRot = 355.0f;

	// Refresh the Window
	glutPostRedisplay();
}

void ChangeSize(int w, int h)
{
	GLfloat fAspect;

	// Prevent a divide by zero
	if (h == 0)
		h = 1;

	// Set Viewport to window dimensions
	glViewport(0, 0, w, h);

	// Reset coordinate system
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	fAspect = (GLfloat)w / (GLfloat)h;
	gluPerspective(35.0f, fAspect, 1.0f, 1000.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -400.0f);
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutCreateWindow("RGB Cube");
	glutReshapeFunc(ChangeSize);
	glutSpecialFunc(SpecialKeys);
	glutDisplayFunc(RenderScene);
	SetupRC();
	glutMainLoop();

	return 0;
}

#endif

#if example13
void SetupRC()
{
	GLfloat  ambientLight[] = { 0.4f, 0.4f, 0.4f, 1.0f };
	GLfloat  diffuseLight[] = { 0.7f, 0.7f, 0.7f, 1.0f };
	GLfloat  specular[] = { 0.9f,0.9f,0.9f,1.0f };
	GLfloat	 lightPos[] = { -50.0f, 200.0f, 200.0f, 1.0f };
	GLfloat  specref[] = { 0.6f,0.6f,0.6f,1.0f };

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_LIGHTING);

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	glEnable(GL_LIGHT0);

	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	glMaterialfv(GL_FRONT, GL_SPECULAR, specref);
	glMateriali(GL_FRONT, GL_SHININESS, 64);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void RenderHead(GLfloat diamter, GLfloat height)
{
	GLfloat x, y, angle;
	GLfloat normal[3], corners[4][3];
	GLfloat step = GL_PI / 3;

	glColor3f(0.0f, 0.0f, 0.7f);

	glBegin(GL_TRIANGLE_FAN);
	glNormal3f(0.0f, 0.0f, 1.0f);

	glVertex3f(0.0f, 0.0f, height / 2);

	for (angle = 2 * GL_PI; angle >= 0; angle -= step)
	{
		x = diamter*sin(angle);
		y = diamter*cos(angle);
		glVertex3f(x, y, height / 2);
	}
	glVertex3f(0.0f, diamter, height / 2);
	glEnd();

	glBegin(GL_TRIANGLE_FAN);
	glNormal3f(0.0f, 0.0f, -1.0f);

	glVertex3f(0.0f, 0.0f, -height / 2);

	for (angle = 0; angle <= 2 * GL_PI; angle += step)
	{
		x = diamter*sin(angle);
		y = diamter*cos(angle);
		glVertex3f(x, y, -height / 2);
	}
	glVertex3f(0.0f, diamter, -height / 2);
	glEnd();

	glBegin(GL_QUADS);
	for (angle = 0; angle < 2 * GL_PI; angle += step)
	{
		x = diamter*sin(angle);
		y = diamter*cos(angle);

		corners[0][0] = x;
		corners[0][1] = y;
		corners[0][2] = -height / 2;

		corners[1][0] = x;
		corners[1][1] = y;
		corners[1][2] = height / 2;

		x = diamter*sin(angle + step);
		y = diamter*cos(angle + step);

		if (angle + step < 2 * GL_PI)
		{
			corners[3][0] = x;
			corners[3][1] = y;
			corners[3][2] = -height / 2;

			corners[2][0] = x;
			corners[2][1] = y;
			corners[2][2] = height / 2;
		}
		else
		{
			corners[3][0] = 0;
			corners[3][1] = diamter;
			corners[3][2] = -height / 2;

			corners[2][0] = 0;
			corners[2][1] = diamter;
			corners[2][2] = height / 2;
		}

		//calcNormal(corner, normal);
		glNormal3fv(normal);
}

void RenderScene()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	glRotatef(xRot, 1.0f, 0.0f, 0.0f);
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);



	glPopMatrix();

	glutSwapBuffers();
}

void SpecialKeys(int key, int x, int y)
{
	if (key == GLUT_KEY_UP)
		xRot -= 5.0f;

	if (key == GLUT_KEY_DOWN)
		xRot += 5.0f;

	if (key == GLUT_KEY_LEFT)
		yRot -= 5.0f;

	if (key == GLUT_KEY_RIGHT)
		yRot += 5.0f;

	if (key > 356.0f)
		xRot = 0.0f;

	if (key < -1.0f)
		xRot = 355.0f;

	if (key > 356.0f)
		yRot = 0.0f;

	if (key < -1.0f)
		yRot = 355.0f;

	// Refresh the Window
	glutPostRedisplay();
}

void ChangeSize(int w, int h)
{
	GLfloat fAspect;

	// Prevent a divide by zero
	if (h == 0)
		h = 1;

	// Set Viewport to window dimensions
	glViewport(0, 0, w, h);

	// Reset coordinate system
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	fAspect = (GLfloat)w / (GLfloat)h;
	gluPerspective(35.0f, fAspect, 1.0f, 1000.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -400.0f);
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutCreateWindow("RGB Cube");
	glutReshapeFunc(ChangeSize);
	glutSpecialFunc(SpecialKeys);
	glutDisplayFunc(RenderScene);
	SetupRC();
	glutMainLoop();

	return 0;
}
#endif