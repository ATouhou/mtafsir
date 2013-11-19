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

#include <QApplication>
#include "mainwindow.h"
#include "database.h"
#include <QTextCodec>
#include <QTranslator>
#include <QLibraryInfo>
#include <QDebug>
#include <QFontDatabase>
#include <QDir>

int main(int argc, char *argv[])
{
        QApplication a(argc, argv);
        a.setApplicationName("QuranMufasir");
        a.setApplicationVersion("0.1");
        a.setOrganizationName("abouzakaria");
        a.setWindowIcon(QIcon::fromTheme("mtafsir",QIcon(":/images/mtafsir.png")));
        QString txt=QString(QObject::trUtf8(
                                    "QuranMufasir The electronic Holly Quran tefsir Version : %1 \n"
                                    "طريقة الاستعمال: mtafsir [options]\n"
                                    "الخيارات:\n"
                                    "-h,--help                             أظهر المساعدة حول الخيارات.\n"
                                    "-l,--list                             قائمة بجميع التفاسير المتاحة .\n"
                                    "-n,--number  <int sura>               عدد الايات في السورة .\n"
                                    "-t,--translat  <int sura> <int aya> <string tefsir> \n"
                                    "                                      جلب التفسير للسورة والاية من التفسير المحدد\n"
                                    "-a,--aya   <int sura> <int aya>       جلب الاية المحددة من السورة المحددة .\n"
                                    "-f,--find   <string>                  بحث في القرءان عن نص محدد.\n"
                                    "مثال:\n"
                                     " السورة الخامسة الاية السادسة تفسير السعدي: 'mtafsir -t 5 6 sa3dy.db'.\n"
                                    )).arg(a.applicationVersion());


        //---cmd------
        const QStringList args = QCoreApplication::arguments();
        QString   goPos1 ;
        if (args.count() >1) {
                goPos1 = args.at(1);
                Database d;
                if (args.count() ==2){

                        if (goPos1.toLower()==("--list")||goPos1.toLower()==("-l"))
                                d.cmdGetTafsirName();

                        if (goPos1.toLower()==("-h")||goPos1.toLower()==("--help"))
                                qDebug()<<txt;

                }
                if (args.count() ==3){

                        if (goPos1.toLower()==("-n")||goPos1.toLower()==("--number"))
                                d.cmdGetAyatNumber(args.at(2).toInt(),true);

                        if (goPos1.toLower()==("-f")||goPos1.toLower()==("--find"))
                                d.cmdSearchInQuran(args.at(2));

                }
                if (args.count() ==4){

                        if (goPos1.toLower()==("-a")||goPos1.toLower()==("--aya"))
                                d.cmdGetAyat(args.at(2).toInt(),args.at(3).toInt());

                }
                if (args.count() ==5){

                        if (goPos1.toLower()==("-t")||goPos1.toLower()==("--translat"))
                                d.cmdGetTranslation(args.at(2).toInt(),args.at(3).toInt(),args.at(4));

                }
                return 0;
        }
        QString translatorFileName = QLatin1String("qt_ar");
        // translatorFileName += QLocale::system().name();
        QTranslator *translatorsys = new QTranslator(&a);
        if (translatorsys->load(translatorFileName, QLibraryInfo::location(QLibraryInfo::TranslationsPath)))
                a.installTranslator(translatorsys);
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
        //-------مجلد البرنامج--------
        QDir appDir(qApp->applicationDirPath());

        appDir.cdUp();
        QString appPath=  appDir.absolutePath()+"/share/mtafsir";

        QFontDatabase::addApplicationFont(appPath+"/ARABSQ.TTF");
         QFontDatabase::addApplicationFont(appPath+"/amiri-quran.ttf");
         QFontDatabase::addApplicationFont(appPath+"/trado.ttf");

        MainWindow w;
        w.show();
        
        return a.exec();
}
