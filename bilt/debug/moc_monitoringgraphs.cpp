/****************************************************************************
** Meta object code from reading C++ file 'monitoringgraphs.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../monitoringgraphs.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'monitoringgraphs.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MonitoringGraphs_t {
    QByteArrayData data[12];
    char stringdata0[110];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MonitoringGraphs_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MonitoringGraphs_t qt_meta_stringdata_MonitoringGraphs = {
    {
QT_MOC_LITERAL(0, 0, 16), // "MonitoringGraphs"
QT_MOC_LITERAL(1, 17, 14), // "needT50ToGraph"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 6), // "ch_num"
QT_MOC_LITERAL(4, 40, 6), // "wr_num"
QT_MOC_LITERAL(5, 47, 1), // "i"
QT_MOC_LITERAL(6, 49, 5), // "runMG"
QT_MOC_LITERAL(7, 55, 12), // "QCustomPlot*"
QT_MOC_LITERAL(8, 68, 10), // "customPlot"
QT_MOC_LITERAL(9, 79, 10), // "QComboBox*"
QT_MOC_LITERAL(10, 90, 8), // "ComboBox"
QT_MOC_LITERAL(11, 99, 10) // "ComboBox_2"

    },
    "MonitoringGraphs\0needT50ToGraph\0\0"
    "ch_num\0wr_num\0i\0runMG\0QCustomPlot*\0"
    "customPlot\0QComboBox*\0ComboBox\0"
    "ComboBox_2"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MonitoringGraphs[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    3,   24,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    3,   31,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Double, QMetaType::Int, QMetaType::Int, QMetaType::Int,    3,    4,    5,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 7, 0x80000000 | 9, 0x80000000 | 9,    8,   10,   11,

       0        // eod
};

void MonitoringGraphs::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MonitoringGraphs *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: { double _r = _t->needT50ToGraph((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = std::move(_r); }  break;
        case 1: _t->runMG((*reinterpret_cast< QCustomPlot*(*)>(_a[1])),(*reinterpret_cast< QComboBox*(*)>(_a[2])),(*reinterpret_cast< QComboBox*(*)>(_a[3]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 2:
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QComboBox* >(); break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QCustomPlot* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = double (MonitoringGraphs::*)(int , int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MonitoringGraphs::needT50ToGraph)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MonitoringGraphs::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_MonitoringGraphs.data,
    qt_meta_data_MonitoringGraphs,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MonitoringGraphs::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MonitoringGraphs::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MonitoringGraphs.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int MonitoringGraphs::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
double MonitoringGraphs::needT50ToGraph(int _t1, int _t2, int _t3)
{
    double _t0{};
    void *_a[] = { const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t0))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
    return _t0;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
