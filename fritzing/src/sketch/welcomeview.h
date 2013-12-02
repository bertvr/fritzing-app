/*******************************************************************

Part of the Fritzing project - http://fritzing.org
Copyright (c) 2007-2012 Fachhochschule Potsdam - http://fh-potsdam.de

Fritzing is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Fritzing is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Fritzing.  If not, see <http://www.gnu.org/licenses/>.

********************************************************************

$Revision: 6483 $:
$Author: irascibl@gmail.com $:
$Date: 2012-09-26 15:45:37 +0200 (Mi, 26. Sep 2012) $

********************************************************************/



#ifndef WELCOMEVIEW_H
#define WELCOMEVIEW_H

#include <QFrame>
#include <QLabel>
#include <QList>
#include <QWidget>
#include <QNetworkReply>
#include <QDomDocument>
#include <QDragEnterEvent>
#include <QListWidget>
#include <QPainter>
#include <QAbstractItemDelegate>

class BlogListWidget : public QListWidget 
{
    Q_OBJECT
    Q_PROPERTY(QColor dateTextColor READ dateTextColor WRITE setDateTextColor DESIGNABLE true)
    Q_PROPERTY(QString dateTextFontFamily READ dateTextFontFamily WRITE setDateTextFontFamily DESIGNABLE true)
    Q_PROPERTY(QString dateTextFontSize READ dateTextFontSize WRITE setDateTextFontSize DESIGNABLE true)

    Q_PROPERTY(QColor titleTextColor READ titleTextColor WRITE setTitleTextColor DESIGNABLE true)
    Q_PROPERTY(QString titleTextFontFamily READ titleTextFontFamily WRITE setTitleTextFontFamily DESIGNABLE true)
    Q_PROPERTY(QString titleTextFontSize READ titleTextFontSize WRITE setTitleTextFontSize DESIGNABLE true)

    Q_PROPERTY(QColor introTextColor READ introTextColor WRITE setIntroTextColor DESIGNABLE true)
    Q_PROPERTY(QString introTextFontFamily READ introTextFontFamily WRITE setIntroTextFontFamily DESIGNABLE true)
    Q_PROPERTY(QString introTextFontSize READ introTextFontSize WRITE setIntroTextFontSize DESIGNABLE true)

public:
    BlogListWidget(QWidget * parent = 0);
    ~BlogListWidget();

    QColor dateTextColor() const;
    void setDateTextColor(QColor);
    QString dateTextFontFamily() const;
    void setDateTextFontFamily(QString);
    QString dateTextFontSize() const;
    void setDateTextFontSize(QString);

    QColor titleTextColor() const;
    void setTitleTextColor(QColor);
    QString titleTextFontFamily() const;
    void setTitleTextFontFamily(QString);
    QString titleTextFontSize() const;
    void setTitleTextFontSize(QString);

    QColor introTextColor() const;
    void setIntroTextColor(QColor);
    QString introTextFontFamily() const;
    void setIntroTextFontFamily(QString);
    QString introTextFontSize() const;
    void setIntroTextFontSize(QString);

protected:
    QColor m_dateTextColor;
    QString m_dateTextFontFamily;
    QString m_dateTextFontSize;

    QColor m_titleTextColor;
    QString m_titleTextFontFamily;
    QString m_titleTextFontSize;

    QColor m_introTextColor;
    QString m_introTextFontFamily;
    QString m_introTextFontSize;
};
 
class WelcomeView : public QFrame
{
Q_OBJECT

public:
	WelcomeView(QWidget * parent = 0);
	~WelcomeView();

	void showEvent(QShowEvent * event);
    void dragEnterEvent(QDragEnterEvent *event);
	void updateRecent();

protected:
	void initLayout();
	QWidget * initRecent();
	QWidget * initBlog();
	QWidget * initShop();
	QWidget * initTip();
	void readBlog(const QDomDocument &);
    QWidget * makeRecentItem(const QString & objectName, const QString & iconText, const QString & textText, QLabel * & icon, QLabel * & text);
    void getNextBlogImage(int ix);

signals:
	void newSketch();
	void openSketch();
	void recentSketch(const QString & filename, const QString & actionText);

protected slots:
	void clickRecent(const QString &);
    void gotBlogSnippet(QNetworkReply *);
    void gotBlogImage(QNetworkReply *);
	void clickBlog(const QString &);
    void recentItemClicked(QListWidgetItem *);
    void blogItemClicked(QListWidgetItem *);
    void nextTip();

protected:
    BlogListWidget * m_blogListWidget;
    QLabel * m_tip;
    QListWidget * m_recentListWidget;
    QFrame * m_fabContentFrame;
    QFrame * m_fabFooterFrame;
    QFrame * m_shopContentFrame;
    QFrame * m_shopFooterFrame;
    QStringList m_blogImageRequestList;
};

class BlogListDelegate : public QAbstractItemDelegate
{
	public:
		BlogListDelegate(QObject *parent = 0);
		virtual ~BlogListDelegate(); 

		void paint ( QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index ) const;
		QSize sizeHint ( const QStyleOptionViewItem & option, const QModelIndex & index ) const;
};

#endif
