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

	//用于单击一次的判断
	BOOL xBool;
	BOOL yBool;
	BOOL zBool;

	//缩放功能
	int m_ptSum;//识别到的所有的点
	int m_ptNum;//目前存在的所有点
	POINT point1;//双手的点1
	POINT point2;//双手的点2
	int PreDist;//前两手间距离

	//切割功能
    int m_ptMidX;//中心点x坐标
	BOOL m_bPtMidX;
	BOOL m_bJudge;//让坐标超过某个固定数值后仅触发一次

	//移动功能
	BOOL m_bSubtract;//第一次进入OnPointUpdate函数是给先前点赋值的控制变量
	float m_prePoint[3];//存放先前点的坐标值
	int subtract[3];//先前坐标与当前坐标的差值

	//PPT演示
	bool m_bSelect;//用于获取初始的x、y、z坐标
    POINT m_ptStart;//初始点：用于作为上下距离的判断标准
	BOOL m_bYDis;
	BOOL m_bXDis;
	BOOL m_bZDis;
	BOOL m_bUpToDown;
	BOOL m_bRightToLeft;
	double m_zOrigin;

	//旋转功能
	int m_ptSumRotate;//识别到的所有的点
	int m_ptNumRotate;//目前存在的所有点
	double m_preAngle;
	double m_point1RotateX;//双手的点1
	double m_point1RotateY;
	double m_point2RotateX;//双手的点2
	double m_point2RotateY;
	BOOL m_bJudgeRotate;
	BOOL m_bSelectLR;
	//*********************************************************
	//整合后功能


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
