#pragma once

#include "spdlog/spdlog.h"
#include "spdlog/common.h"

#include <QMainWindow>
#include <QSettings>
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <QTreeWidgetItem>

#include <memory>
#include <filesystem>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }

class QListWidgetItem;
class QListWidget;
class QTableWidget;
QT_END_NAMESPACE

struct Enclosure;
struct BoxGraphicsScene;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public Q_SLOTS:

    void on_actionNew_triggered();
    void on_actionOpen_triggered();
    void on_actionSave_triggered();
    void on_actionClose_triggered();
    void on_actionAbout_triggered();
    void on_actionOpen_Logs_triggered();

    void UpdateStatus(QString const& message);

    void LogMessage(QString const& message , spdlog::level::level_enum llvl = spdlog::level::level_enum::debug);

private:

    QString GetFileName(QString const& path) const;
    void drawPoint(QGraphicsScene& scene, double x, double y, int, QPen pen);
    void drawLine(QGraphicsScene& scene, double x1, double y1, double x2, double y2, QPen pen);
    void LoadDevices();

    Ui::MainWindow *m_ui;
    std::shared_ptr<spdlog::logger> m_logger{ nullptr };
    std::unique_ptr<QSettings> m_settings{ nullptr };
    QString m_appdir;
    QString m_templatedir;
    QString m_devicesdir;

    QTreeWidgetItem* m_devicesItem{ nullptr };

    BoxGraphicsScene* m_boxScene;

    std::vector< std::unique_ptr<QGraphicsItem> > m_boxItems;

    std::unique_ptr <Enclosure> m_enclosure;
};

