#ifndef PATH2DVIEWPLUGIN_HPP
#define PATH2DVIEWPLUGIN_HPP

#include <QtGui>
#include <QtDesigner/QDesignerCustomWidgetInterface>

class Path2dViewPlugin : public QObject, public QDesignerCustomWidgetInterface
{
    Q_OBJECT
    Q_INTERFACES(QDesignerCustomWidgetInterface)

public:
    Path2dViewPlugin(QObject *parent = 0);
    virtual ~Path2dViewPlugin();

    bool isContainer() const;
    bool isInitialized() const;
    QIcon icon() const;
    QString domXml() const;
    QString group() const;
    QString includeFile() const;
    QString name() const;
    QString toolTip() const;
    QString whatsThis() const;
    QWidget* createWidget(QWidget *parent);
    void initialize(QDesignerFormEditorInterface *core);

private:
    bool initialized; 
};

#endif /* PATH2DVIEWPLUGIN_HPP */  
