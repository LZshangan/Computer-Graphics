#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_
#include <graphics.h>
#endif // !_GRAPHICS_H_

#ifndef _CONIO_H_
#define _CONIO_H_
#include <conio.h>
#endif // !_CONIO_H_

#include "../vector3.h"

#include<stdio.h>

/*
 * 4    ����׷��
 * 4-1  �����������ཻ����
 *
 * ��ʾ����׷�ٵĻ���ԭ��
 * ����������˳�����ɹ��ߡ������뼸��ͼ���ཻ���жϡ�
 *
 * ���л�����Windows��Visual Studio 2019
 * EasyX ͼ�ο�汾��20200520��beta��
 *
 * ****  �����������Ӧ���볢�������豸��  ****
 * ****  �����ֱ��������ȷ������Github�����������Ľ��������������ȷ��װEasyXͼ�ο⡣  ****
 *
 * Last Edit: 2020/06/22
 */

//���ζ���ĸ���
class Surface {
public:
    Surface() {}
    ~Surface() {}


    virtual bool hit(const Vector3& ve,
        const Vector3& vd,
        float t1,
        float t2,
        float& rec) = 0;
};

// ����ʵ������������������ࣻ�������ζ���һ��ɿ������������ε�ƴ�ӡ�

//��������ʵ������Ρ�
class Triangle : public Surface {
public:
    //�����ε���������
    Vector3 p1, p2, p3;
    //����������ϵ��������������ֵ�ֱ��ӦRGBͨ��
    Vector3 diffuse;

    Triangle() {}
    Triangle(Vector3 p1, Vector3 p2, Vector3 p3, Vector3 diffuse) 
    : p1(p1), p2(p2), p3(p3), diffuse(diffuse) {}

    /*
     �жϹ������������Ƿ��ཻ��

     @param //���߿ɱ�ʾΪve+t*vd
     @param Vector3& ve �����λ��
     @param Vector3& vd ���߷����ɽ���ָ�������
     @param float t1, t2 t�ķ�Χ
     @param float& rec �ô˱��������ཻʱt��ֵ

     @return bool �Ƿ��ཻ
     */
    virtual bool hit(const Vector3& ve,
        const Vector3& vd,
        float t1,
        float t2,
        float& rec) {
        //ʹ�ù������������󽻹�ʽ�ж�(�μ�������İ�79ҳ)��
        //Ϊ�����Ч��ʹ���˼����м������
        assert(t2 > t1);
        float a = p1.x - p2.x,
              b = p1.y - p2.y,
              c = p1.z - p2.z,
              d = p1.x - p3.x,
              e = p1.y - p3.y,
              f = p1.z - p3.z,
              g = vd.x,
              h = vd.y,
              i = vd.z,
              j = p1.x - ve.x,
              k = p1.y - ve.y,
              l = p1.z - ve.z;
        float ei_hf = e * i - h * f,
              gf_di = g * f - d * i,
              dh_eg = d * h - e * g,
              ak_jb = a * k - j * b,
              jc_al = j * c - a * l,
              bl_kc = b * l - k * c;
        float M = a * ei_hf + b * gf_di + c * dh_eg;
        
        float beta = (j * ei_hf + k * gf_di + l * dh_eg) / M,
             gamma = (i * ak_jb + h * jc_al + g * bl_kc) / M;
        rec       = (f * ak_jb + e * jc_al + d * bl_kc) / M;
        
        return (rec < t2 && rec > t1 
            && beta > 0 && gamma > 0 
            && beta + gamma < 1);
    }
};

/*
 init_fullscreen  ��ʼ���豸��Ļ
 
 ͨ��һϵ�в�������ȫ����ͼ���ڡ�
 */
void init_fullscreen() {
    int rW = GetSystemMetrics(SM_CXSCREEN); // ��Ļ��� ����
    int rH = GetSystemMetrics(SM_CYSCREEN); // ��Ļ�߶� ����
    initgraph(rW, rH);
    HWND hwnd = GetHWnd();//��ȡ���ھ�� ��easyxΪ��
    LONG l_WinStyle = GetWindowLong(hwnd, GWL_STYLE); // ��ȡ������Ϣ
    // ���ô�����Ϣ ��� ȡ�����������߿�
    SetWindowLong(hwnd, GWL_STYLE,
        (l_WinStyle | WS_POPUP | WS_MAXIMIZE) & ~WS_CAPTION & ~WS_THICKFRAME & ~WS_BORDER);
    //ֱ���޸Ĵ�����ʽ
    SetWindowPos(hwnd, HWND_TOP, 0, 0, rW, rH, 0);
}

int main() {
    init_fullscreen();

    _getch();
}