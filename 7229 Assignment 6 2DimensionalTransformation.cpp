/*
	Name: Khushi
	Roll no: 7229
	Assignment 6

*/
#include <GL/glut.h>
#include <bits/stdc++.h>
using namespace std;

#define w 500
#define h 500

void init()
{
    //glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-w / 2, w / 2, -h / 2, h / 2);
}

void setpixel(GLint x, GLint y)
{
    glColor3f(0.0, 0.0, 1.0);
    glPointSize(2.0);
    glBegin(GL_POINTS);
    glVertex2f(x, y);
    glEnd();
    glFlush();
}

float mati[30][2], mato[30][2];
int k = 0, c;

class Translation
{
    int transl[2][2];

public:
    int mul(float s[2][2])
    {
        int i, j, k;
        float sum;
        for (i = 0; i < c; i++)
        {
            for (j = 0; j < 2; j++)
            {
                sum = 0;
                for (k = 0; k < 2; k++)
                    sum = sum + mati[i][k] * s[k][j];
                mato[i][j] = sum;
            }
        }
        return mato[30][2];
    }

    void markPoints(float m[][2])
    {
        glColor3f(0.0, 1.0, 0.0);
        glBegin(GL_LINE_LOOP);
        for (int i = 0; i < c; i++)
            glVertex2f(m[i][0], m[i][1]);
        glEnd();
        glFlush();
    }

    void translationOfShape(float tx, float ty)
    {
        int i;
        for (i = 0; i < c; i++)
        {
            mato[i][0] = mati[i][0] + tx;
            mato[i][1] = mati[i][1] + ty;
        }
    }

    void shapeScaling()
    {
        float scale[2][2];
        int i;
        float sx, sy;
        cout << "\nScaling:\nEnter Sx factor::";
        cin >> sx;
        cout << "\nEnter Sy factor::";
        cin >> sy;
        scale[0][0] = sx;
        scale[0][1] = 0;
        scale[1][0] = 0;
        scale[1][1] = sy;
        mul(scale);
        markPoints(mato);
    }
    void rotationOfShape()
    {
        int rot;
        float angle, rota[2][2];
        cout << "\nRotation:\nEnter angle::";
        cin >> angle;
        angle = (3.14 * angle) / 180;
        cout << "In which Direction you want to rotate your Shape ? " << endl;
        cout << "1. Anti-Clockwise" << endl;
        cout << "2. Clockwise" << endl;
        cout << "Enter your choice::" << endl;
        cin >> rot;
        switch (rot)
        {
        case 1:
            rota[0][0] = cos(angle);
            rota[0][1] = sin(angle);
            rota[1][0] = -sin(angle);
            rota[1][1] = cos(angle);
            break;
        case 2:
            rota[0][0] = cos(angle);
            rota[0][1] = -sin(angle);
            rota[1][0] = sin(angle);
            rota[1][1] = cos(angle);
            break;

        default:
            cout << "\nInvalid Input!!!";
            system("pause");
            exit(0);
        }
        mul(rota);
    }
    void reflectionAboutAnAxis()
    {
        char axis;
        int i;
        cout << "\nEnter reflection axis (x or y) : ";
        cin >> axis;
        glBegin(GL_LINE_LOOP);
        if (axis == 'x' || axis == 'X')
        {
            for (i = 0; i < c; i++)
            {
                glVertex2i(round(mati[i][0]), round(mati[i][1] * -1));
            }
        }
        else if (axis == 'y' || axis == 'Y')
        {
            for (i = 0; i < c; i++)
            {
                glVertex2i(round(mati[i][0] * -1), round(mati[i][1]));
            }
        }
        glEnd();
    }

    void shearing()
    {
        char axis;
        int i, shearingX, shearingY;
        cout << "\nEnter shearing axis (x or y) : ";
        cin >> axis;
        glColor3f(0.0, 1.0, 0.0);
        glBegin(GL_LINE_LOOP);
        if (axis == 'x' || axis == 'x')
        {
            cout << "\nEnter shearing factor for x:";
            cin >> shearingX;
            glVertex2i(mati[0][0], mati[0][1]);
            glVertex2i(mati[1][0] + shearingX, mati[1][1]);
            glVertex2i(mati[2][0] + shearingX, mati[2][1]);
            glVertex2i(mati[3][0], mati[3][1]);
        }
        else if (axis == 'y' || axis == 'y')
        {
            cout << "\nEnter shearing factor for y:";
            cin >> shearingY;
            glVertex2i(mati[0][0], mati[0][1]);
            glVertex2i(mati[1][0], mati[1][1]);
            glVertex2i(mati[2][0], mati[2][1] + shearingY);
            glVertex2i(mati[3][0], mati[3][1] + shearingY);
        }
        //}
        glEnd();
    }
} t;

void menu(int c)
{
    float tx, ty;
    if (c == 1)
    {
        cout << "\n You have selected Translation" << endl;
        cout << "Enter X Factor for Translastion :=>:";
        cin >> tx;
        cout << "\nEnter X Factor for Translastion :=>: ";
        cin >> ty;
        t.translationOfShape(tx, ty);
        t.markPoints(mato);
        cout << "Viola! Tranlation Completed Successfully\n";
    }

    else if (c == 2)
    {
        cout << "\n You have selected Scaling" << endl;

        t.shapeScaling();
        cout << "Viola! Scaling Completed Successfully\n";
    }
    else if (c == 3)
    {
        cout << "\n You have selected Rotation" << endl;
        t.rotationOfShape();
        t.markPoints(mato);
        cout << "Viola! Rotation Completed Successfully\n";
    }
    else if (c == 4)
    {
        cout << "\n You have selected Reflection" << endl;

        t.reflectionAboutAnAxis();
        t.markPoints(mati);
        cout << "Viola! Reflection Completed Successfully\n";
    }
    else if (c == 5)
    {
        cout << "\n You have selected Shearing" << endl;

        t.shearing();
        t.markPoints(mato);
        cout << "Viola! Shearing Completed Successfully\n";
    }
    else if (c == 6)
    {
        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT);
        glFlush();
    }
    else if (c == 7)
    {
        exit(1);
    }
    else
    {
        cout << "\nInvalid option. Try again.";
    }
}

void keyboard(unsigned char key, int x, int y)
{
    if (key == 27)
        exit(0);

    if (key == 108 || key == 76)
    {
        glColor3f(0.0, 0.0, 1.0);
        glBegin(GL_LINE_LOOP);
        for (int i = 0; i < k; i++)
            glVertex2f(mati[i][0], mati[i][1]);
        glEnd();
        c = k;
        k = 0;
        glFlush();
    }
}

void mouse(int button, int state, int x, int y)
{
    int x1, y1, p;
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        mati[k][0] = (float)(x - 250);
        mati[k][1] = (float)(250 - y);
        glColor3f(1.0, 1.0, 1.0);
        glPointSize(3.0);
        glBegin(GL_POINTS);
        glVertex2f(mati[k][0], mati[k][1]);
        glEnd();
        k++;
        glFlush();
    }
    glutCreateMenu(menu);
    glutAddMenuEntry("TRANSLATION", 1);
    glutAddMenuEntry("SCALING", 2);
    glutAddMenuEntry("ROTATION", 3);
    glutAddMenuEntry("REFLECTION", 4);
    glutAddMenuEntry("SHEARING", 5);
    glutAddMenuEntry("CLEAR", 6);
    glutAddMenuEntry("EXIT", 7);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(w, h);
    glutCreateWindow("2 Dimensional Transformation");
    cout << "----------------------------------------------------------------" << endl;
    cout << "-----------------Use Mouse to Draw the polygon------------------" << endl;
    cout << "-------Use 'l' or 'L' to make polygon on graphics window--------" << endl;
    cout << "-----Use right mouse button to get 2D transformations menu------" << endl;
    cout << "----------------------------------------------------------------";
    glutDisplayFunc(init);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutMainLoop();

    return 0;
}
