/****************************************************************************
*                                                                           *
*   Nite 1.3 - Point Viewer                                                 *
*                                                                           *
*   Author:     Oz Magal                                                    *
*                                                                           *
****************************************************************************/

/****************************************************************************
*                                                                           *
*   Nite 1.3	                                                            *
*   Copyright (C) 2006 PrimeSense Ltd. All Rights Reserved.                 *
*                                                                           *
*   This file has been provided pursuant to a License Agreement containing  *
*   restrictions on its use. This data contains valuable trade secrets      *
*   and proprietary information of PrimeSense Ltd. and is protected by law. *
*                                                                           *
****************************************************************************/

#ifndef XNV_POINT_DRAWER_H_
#define XNV_POINT_DRAWER_H_

#include <map>
#include <list>
#include <XnCppWrapper.h>
#include <XnVPointControl.h>

typedef enum
{
	IN_SESSION,
	NOT_IN_SESSION,
	QUICK_REFOCUS
} SessionState;

void PrintSessionState(SessionState eState);
/**
 * This is a point control, which stores the history of every point
 * It can draw all the points as well as the depth map.
 */
class XnVPointDrawer : public XnVPointControl
{
public:
	XnVPointDrawer(XnUInt32 nHistorySize, xn::DepthGenerator depthGenerator);
	virtual ~XnVPointDrawer();

	/**
	 * Handle a new message.
	 * Calls other callbacks for each point, then draw the depth map (if needed) and the points
	 */
	void Update(XnVMessage* pMessage);

	/**
	 * Handle creation of a new point
	 */
	void OnPointCreate(const XnVHandPointContext* cxt);
	/**
	 * Handle new position of an existing point
	 */
	void OnPointUpdate(const XnVHandPointContext* cxt);
	/**
	 * Handle destruction of an existing point
	 */
	void OnPointDestroy(XnUInt32 nID);

	/**
	 * Draw the points, each with its own color.
	 */
	void Draw() const;

	/**
	 * Change mode - should draw the depth map?
	 */
	void SetDepthMap(XnBool bDrawDM);
	/**
	 * Change mode - print out the frame id
	 */
	void SetFrameID(XnBool bFrameID);

	//���ڵ���һ�ε��ж�
	BOOL xBool;
	BOOL yBool;
	BOOL zBool;

	//���Ź���
	int m_ptSum;//ʶ�𵽵����еĵ�
	int m_ptNum;//Ŀǰ���ڵ����е�
	POINT point1;//˫�ֵĵ�1
	POINT point2;//˫�ֵĵ�2
	int PreDist;//ǰ���ּ����

	//�и��
    int m_ptMidX;//���ĵ�x����
	BOOL m_bPtMidX;
	BOOL m_bJudge;//�����곬��ĳ���̶���ֵ�������һ��

	//�ƶ�����
	BOOL m_bSubtract;//��һ�ν���OnPointUpdate�����Ǹ���ǰ�㸳ֵ�Ŀ��Ʊ���
	float m_prePoint[3];//�����ǰ�������ֵ
	int subtract[3];//��ǰ�����뵱ǰ����Ĳ�ֵ

	//PPT��ʾ
	bool m_bSelect;//���ڻ�ȡ��ʼ��x��y��z����
    POINT m_ptStart;//��ʼ�㣺������Ϊ���¾�����жϱ�׼
	BOOL m_bYDis;
	BOOL m_bXDis;
	BOOL m_bZDis;
	BOOL m_bUpToDown;
	BOOL m_bRightToLeft;
	double m_zOrigin;

	//��ת����
	int m_ptSumRotate;//ʶ�𵽵����еĵ�
	int m_ptNumRotate;//Ŀǰ���ڵ����е�
	double m_preAngle;
	double m_point1RotateX;//˫�ֵĵ�1
	double m_point1RotateY;
	double m_point2RotateX;//˫�ֵĵ�2
	double m_point2RotateY;
	BOOL m_bJudgeRotate;
	BOOL m_bSelectLR;
	//*********************************************************
	//���Ϻ���


protected:
	// Number of previous position to store for each hand
	XnUInt32 m_nHistorySize;
	// previous positions per hand
	std::map<XnUInt32, std::list<XnPoint3D> > m_History;
	// Source of the depth map
	xn::DepthGenerator m_DepthGenerator;
	XnFloat* m_pfPositionBuffer;

	XnBool m_bDrawDM;
	XnBool m_bFrameID;
};

#endif
