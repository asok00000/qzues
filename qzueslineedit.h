#ifndef QZUESLINEEDIT_H
#define QZUESLINEEDIT_H

#include <QLineEdit>
#include <QString>
/*!
*\class QZuesLineEdit
*\brief An extended Line Edit Widget inherited from QLineEdit
*\details Provide more powerful functions
*\author Hu chunhua
*\version 1.0
*\date 2015-11-30 13:37:51
*\note modification:
*\date
*/
class QZuesLineEdit : public QLineEdit
{
	Q_OBJECT
		Q_PROPERTY(bool m_isContentChanged READ getContentChanged WRITE setContentChanged NOTIFY signalContentChanged)
public:
	QZuesLineEdit(QWidget *parent);
	~QZuesLineEdit();
	bool getContentChanged() const;
	void setContentChanged(bool val);
	void setText(const QString &content);
	/*!
	*\fn reset
	*\brief reset the line edit content to the first set value
	*/
	void reset();
signals:
	void signalContentChanged(bool isChanged);
private:
	QString m_originContent;
	bool m_isContentChanged;
	bool m_isFirstSet;
};

#endif // QZUESLINEEDIT_H
