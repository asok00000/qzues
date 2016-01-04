#include "qzueslineedit.h"

QZuesLineEdit::QZuesLineEdit(QWidget *parent)
	: QLineEdit(parent), m_isContentChanged(false), m_originContent(""), m_isFirstSet(true)
{

}

QZuesLineEdit::~QZuesLineEdit()
{

}

bool QZuesLineEdit::getContentChanged() const
{
	return m_isContentChanged;
}

void QZuesLineEdit::setContentChanged(bool val)
{
	m_isContentChanged = val;
}

void QZuesLineEdit::setText(const QString &content)
{
	if (m_isFirstSet)
	{
		m_isFirstSet = false;
		m_originContent = content;
	}
	else
	{
		if (m_originContent != content)
		{
			if (!m_isContentChanged)
			{
				setContentChanged(true);
			}
		}
		else
		{
			if (m_isContentChanged)
			{
				setContentChanged(false);
			}
		}
	}
	QLineEdit::setText(content);
}

void QZuesLineEdit::reset()
{
	QLineEdit::setText(m_originContent);
}
