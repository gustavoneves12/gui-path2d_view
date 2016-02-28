#include "Path2dViewPlugin.hpp"
#include "Path2dView.hpp"

Q_EXPORT_PLUGIN2(Path2dView, Path2dViewPlugin)

Path2dViewPlugin::Path2dViewPlugin(QObject *parent)
    : QObject(parent)
{
    initialized = false;
}

Path2dViewPlugin::~Path2dViewPlugin()
{
}

bool Path2dViewPlugin::isContainer() const
{
    return false;
}

bool Path2dViewPlugin::isInitialized() const
{
    return initialized;
}

QIcon Path2dViewPlugin::icon() const
{
    return QIcon("");
}

QString Path2dViewPlugin::domXml() const
{
        return "<ui language=\"c++\">\n"
            " <widget class=\"Path2dView\" name=\"path2dview\">\n"
            "  <property name=\"geometry\">\n"
            "   <rect>\n"
            "    <x>0</x>\n"
            "    <y>0</y>\n"
            "     <width>300</width>\n"
            "     <height>120</height>\n"
            "   </rect>\n"
            "  </property>\n"
            " </widget>\n"
            "</ui>\n";
}

QString Path2dViewPlugin::group() const {
    return "Rock-Robotics";
}

QString Path2dViewPlugin::includeFile() const {
    return "Path2dView/Path2dView.hpp";
}

QString Path2dViewPlugin::name() const {
    return "Path2dView";
}

QString Path2dViewPlugin::toolTip() const {
    return whatsThis();
}

QString Path2dViewPlugin::whatsThis() const
{
    return "";
}

QWidget* Path2dViewPlugin::createWidget(QWidget *parent)
{
    return new Path2dView(parent);
}

void Path2dViewPlugin::initialize(QDesignerFormEditorInterface *core)
{
     if (initialized)
         return;
     initialized = true;
}
