/****************************************************************************
//   mtafsir Copyright (C) 2012 yahia nouah <yahiaui@gmail.com>
//
//      This program comes with ABSOLUTELY NO WARRANTY; for details type `show w'.
//      This is free software, and you are welcome to redistribute it
//      under certain conditions; type `show c' for details.
//
//  The hypothetical commands `show w' and `show c' should show the appropriate
//  parts of the General Public License.  Of course, your program's commands
//  might be different; for a GUI interface, you would use an "about box".
//
//    You should also get your employer (if you work as a programmer) or school,
//  if any, to sign a "copyright disclaimer" for the program, if necessary.
//  For more information on this, and how to apply and follow the GNU GPL, see
//  <http://www.gnu.org/licenses/>.
//
//    The GNU General Public License does not permit incorporating your program
//  into proprietary programs.  If your program is a subroutine library, you
//  may consider it more useful to permit linking proprietary applications with
//  the library.  If this is what you want to do, use the GNU Lesser General
//  Public License instead of this License.  But first, please read
//  <http://www.gnu.org/philosophy/why-not-lgpl.html>.
// ----------------------------------------------------------
** If you have questions regarding the use of this file, please contact
** yahia nouah (yahiaui@gmail.com)
** $mtafsir_END_LICENSE$
**
****************************************************************************/

#include "buttoncolor.h"
#include <QColorDialog>
#include <QPainter>
#include <QDebug>
ButtonColor::ButtonColor(QColor color,QWidget *parent) :
        QPushButton(parent)
{
        setIconSize(QSize(32,16));
          setMaximumSize(QSize(48,26));
         setMinimumSize(QSize(40,26));
        connect(this,SIGNAL(clicked()),this,SLOT(getColor()));
        setColor( color);
}


void ButtonColor::setColor(QColor color)
{

     m_color=color;
     QPixmap pix(32,16);
     pix.fill(Qt::transparent);
QPainter p;

p.begin(&pix);

p.fillRect(pix.rect(),m_color);
p.setPen(this->palette().shadow().color());
p.drawRect(pix.rect());
p.setPen(this->palette().light().color());
p.drawRect(-1,-1,32,16);
    // pix.fill(m_color);
     this->setIcon(pix);
}

void ButtonColor::getColor()
{
        QColor color=QColorDialog::getColor(m_color,this,"Get Color");

        if(color.isValid()){
            setColor(color);
            emit colorChanged() ;
        }

}
