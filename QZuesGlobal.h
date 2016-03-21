#ifndef QZUESGLOBAL_H
#define QZUESGLOBAL_H
/*!
*\class QZuesLabel
*\brief An extended Label Widget inherited from QLabel
*\details Provide more powerful functions
*\author Hu chunhua
*\version 1.0
*\date 2015-11-27 17:36:51
*\note modification:
*\date
*/
#include <QDebug>
#include <QFlags>
enum LabelType
{
	LABEL_TYPE_NORMAL = 0x00000000,
	LABEL_TYPE_AUTO_CUT = 0x00000001,
	LABEL_TYPE_MARQUEE = 0x00000010,
};

enum StackWidgetAnimationType
{
	STACK_WIDGET_ANIMATION_NORMAL = 0x00000000,
	STACK_WIDGET_ANIMATION_GRADIENT = 0x00000001,
	STACK_WIDGET_ANIMATION_SIZE = 0x00000010,
	STACK_WIDGET_ANIMATION_PATH = 0x00000100,//resolve
	STACK_WIDGET_ANIMATION_LEFT = 0x00001000,
	STACK_WIDGET_ANIMATION_RIGHT = 0x00010000,
	STACK_WIDGET_ANIMATION_TOP = 0x00100000,
	STACK_WIDGET_ANIMATION_DOWN = 0x01000000,
	STACK_WIDGET_ANIMATION_ALL = 0x11111111,
};
Q_DECLARE_FLAGS(StackWidgetAnimationTypes, StackWidgetAnimationType)
#endif//QZUESGLOBAL_H