/****************************************************************************
** Meta object code from reading C++ file 'MainWindow.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.7.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/MainWindow.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MainWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.7.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSMainWindowENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSMainWindowENDCLASS = QtMocHelpers::stringData(
    "MainWindow",
    "openFile",
    "",
    "saveFile",
    "cutVideo",
    "combineVideos",
    "togglePlayPause",
    "handleMediaStatusChanged",
    "QMediaPlayer::MediaStatus",
    "status",
    "addTextToVideo",
    "addTextOverlay",
    "handleFileSelected",
    "filePath",
    "addOverlayToVideo",
    "applyLightTheme",
    "applyGreenTheme",
    "applyBlueTheme",
    "applyDarkTheme",
    "applyPurpleNouncesTheme",
    "setupThemeMenu",
    "addVideosToTimeline",
    "applyCustomStyle",
    "updateProgressBar",
    "duration",
    "openSettings",
    "applySmoothTransition",
    "QWidget*",
    "widget",
    "startRect",
    "endRect",
    "applyModernStyle",
    "applyShadows",
    "openFilterSettings",
    "applyFilter",
    "filter"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSMainWindowENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      25,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,  164,    2, 0x08,    1 /* Private */,
       3,    0,  165,    2, 0x08,    2 /* Private */,
       4,    0,  166,    2, 0x08,    3 /* Private */,
       5,    0,  167,    2, 0x08,    4 /* Private */,
       6,    0,  168,    2, 0x08,    5 /* Private */,
       7,    1,  169,    2, 0x08,    6 /* Private */,
      10,    0,  172,    2, 0x08,    8 /* Private */,
      11,    0,  173,    2, 0x08,    9 /* Private */,
      12,    1,  174,    2, 0x08,   10 /* Private */,
      14,    0,  177,    2, 0x08,   12 /* Private */,
      15,    0,  178,    2, 0x08,   13 /* Private */,
      16,    0,  179,    2, 0x08,   14 /* Private */,
      17,    0,  180,    2, 0x08,   15 /* Private */,
      18,    0,  181,    2, 0x08,   16 /* Private */,
      19,    0,  182,    2, 0x08,   17 /* Private */,
      20,    0,  183,    2, 0x08,   18 /* Private */,
      21,    0,  184,    2, 0x08,   19 /* Private */,
      22,    0,  185,    2, 0x08,   20 /* Private */,
      23,    1,  186,    2, 0x08,   21 /* Private */,
      25,    0,  189,    2, 0x08,   23 /* Private */,
      26,    3,  190,    2, 0x08,   24 /* Private */,
      31,    0,  197,    2, 0x08,   28 /* Private */,
      32,    0,  198,    2, 0x08,   29 /* Private */,
      33,    0,  199,    2, 0x08,   30 /* Private */,
      34,    1,  200,    2, 0x08,   31 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   13,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::LongLong,   24,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 27, QMetaType::QRect, QMetaType::QRect,   28,   29,   30,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   35,

       0        // eod
};

Q_CONSTINIT const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_CLASSMainWindowENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSMainWindowENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSMainWindowENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<MainWindow, std::true_type>,
        // method 'openFile'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'saveFile'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'cutVideo'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'combineVideos'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'togglePlayPause'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'handleMediaStatusChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QMediaPlayer::MediaStatus, std::false_type>,
        // method 'addTextToVideo'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'addTextOverlay'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'handleFileSelected'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'addOverlayToVideo'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'applyLightTheme'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'applyGreenTheme'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'applyBlueTheme'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'applyDarkTheme'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'applyPurpleNouncesTheme'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'setupThemeMenu'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'addVideosToTimeline'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'applyCustomStyle'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'updateProgressBar'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<qint64, std::false_type>,
        // method 'openSettings'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'applySmoothTransition'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QWidget *, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QRect &, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QRect &, std::false_type>,
        // method 'applyModernStyle'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'applyShadows'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'openFilterSettings'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'applyFilter'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>
    >,
    nullptr
} };

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->openFile(); break;
        case 1: _t->saveFile(); break;
        case 2: _t->cutVideo(); break;
        case 3: _t->combineVideos(); break;
        case 4: _t->togglePlayPause(); break;
        case 5: _t->handleMediaStatusChanged((*reinterpret_cast< std::add_pointer_t<QMediaPlayer::MediaStatus>>(_a[1]))); break;
        case 6: _t->addTextToVideo(); break;
        case 7: _t->addTextOverlay(); break;
        case 8: _t->handleFileSelected((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 9: _t->addOverlayToVideo(); break;
        case 10: _t->applyLightTheme(); break;
        case 11: _t->applyGreenTheme(); break;
        case 12: _t->applyBlueTheme(); break;
        case 13: _t->applyDarkTheme(); break;
        case 14: _t->applyPurpleNouncesTheme(); break;
        case 15: _t->setupThemeMenu(); break;
        case 16: _t->addVideosToTimeline(); break;
        case 17: _t->applyCustomStyle(); break;
        case 18: _t->updateProgressBar((*reinterpret_cast< std::add_pointer_t<qint64>>(_a[1]))); break;
        case 19: _t->openSettings(); break;
        case 20: _t->applySmoothTransition((*reinterpret_cast< std::add_pointer_t<QWidget*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QRect>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QRect>>(_a[3]))); break;
        case 21: _t->applyModernStyle(); break;
        case 22: _t->applyShadows(); break;
        case 23: _t->openFilterSettings(); break;
        case 24: _t->applyFilter((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 20:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QWidget* >(); break;
            }
            break;
        }
    }
}

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSMainWindowENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 25)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 25;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 25)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 25;
    }
    return _id;
}
QT_WARNING_POP
