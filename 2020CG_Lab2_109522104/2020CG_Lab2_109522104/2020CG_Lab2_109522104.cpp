using namespace std;
#include<iostream>
#include<gl/GLUT.H>
#include<string>
#include <fstream>

void Initial(void)
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, 800.0, 0.0, 600.0);
	
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();
}

void drawDot(int x, int y) {
	glPointSize(5.0f);
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_POINTS);
	glVertex2f(x, y);
	glEnd();
	glFlush();
	cout << "dot on " << x << ", " << y << endl;
}

ifstream input;

void myDisplay(void) { 
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();

	string c = "";
	while (input >> c) {
		if (c == "#") {
			cout << c << " ";
			getline(input, c);
			cout << c << endl;
			//break;
		}
		else if (c == "reset") {
			cout << c << endl;
			//break;
		}
		else if (c == "scale") {
			float a, b = 0;
			input >> a >> b;
			drawDot((int)floor(a), (int)floor(b));
			cout << c << " " << a << " " << b << endl;
			//break;
		}
		else if (c == "rotate") {
			float theta = 0;
			input >> theta;
			cout << c << " " << theta << endl;
			//break;
		}
		else if (c == "translate") {
			float x, y = 0;
			input >> x >> y;
			cout << c << " " << x << " " << y << endl;
			//break;
		}
		else if (c == "square") {
			cout << c << endl;
			//break;
		}
		else if (c == "triangle") {
			cout << c << endl;
			//break;
		}
		else if (c == "view") {
			float wxl, wxr, wyb, wyt, vxl, vxr, vyb, vyt = 0;
			input >> wxl >> wxr >> wyb >> wyt >> vxl >> vxr >> vyb >> vyt;
			cout << c << endl;
			// system("pause");
			//break;
		}
		else if (c == "clearData") {
			cout << c << endl;
			//break;
		}
		else if (c == "clearScreen") {
			cout << c << endl;
			//break;
		}
		else if (c == "end") {
			cout << c << endl;
			system("pause");
			glutDestroyWindow(glutCreateWindow("2020CG_Lab2_109522104"));
			exit(0);
			//break;
		}
		else {
			cout << "unexpected token " << c << endl;
			//break;
		}
	}
	
	// system("pause");	
}

bool lflag = false, pflag = false, oflag = false;
int X0 = 0, Y0 = 0, X1 = 0, Y1 = 0, X2 = 0, Y2 = 0;


void drawLine(float x1, float y1, float x2, float y2) {
	cout << "you made it to drawLine.\n";
	float m = (float)(y2 - y1) / (x2 - x1);
	float a = y2 - y1;
	float b = x1 - x2;
	float dint = a + b / 2;
	float d = dint;
	float incE = a;
	float incNE = a + b;

	cout << m << endl;
	glBegin(GL_POINTS);
	// glVertex2f(x1, glutGet(GLUT_WINDOW_HEIGHT) - y1);

	if (m<1 && m > -1) {
		while (x1 < x2) {
			glVertex2f(x1, y1 + 0.5);
			x1++;
			y1 += m;
		}
		while (x1 >= x2) {
			glVertex2f(x1, y1 - 0.5);
			x1--;
			y1 -= m;
		}
	}

	else {
		float mnew = (float)(x2 - x1) / (y2 - y1);
		cout << mnew << endl;
		while (y1 < y2) {
			glVertex2f(floor(x1 + 0.5), y1);
			y1++;
			x1 += mnew;
		}
		while (y1 >= y2) {
			glVertex2f(floor(x1 - 0.5), y1);
			y1--;
			x1 -= mnew;
		}
	}
	glEnd();
	glFlush();
}

int main(int argc, char * argv[])
{
	system("pause");
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 600);
	glutCreateWindow("2020CG_Lab2_109522104");
	// Initial();

	if (argc < 2) {
		cout << "Please use command line to enter input file name." << endl;
		return 0;
	}

	input.open(argv[1]);
	if (input.is_open())
	{
		glutDisplayFunc(myDisplay);
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glutMainLoop();
		input.close();
	}
	else cout << "Unable to open file";


	return 0;
}