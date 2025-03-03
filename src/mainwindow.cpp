#include "mainwindow.h"

#include "./ui_mainwindow.h"

#include "config.h"

#include "data/enclosure.h"

#include "data/device_graphics_item.h"

#include "BoxGraphicsScene.h"

#include "spdlog/spdlog.h"

#include "spdlog/sinks/qt_sinks.h"
#include "spdlog/sinks/rotating_file_sink.h"

#include <QMessageBox>
#include <QDesktopServices>
#include <QSettings>
#include <QFileDialog>
#include <QTextStream>
#include <QThread>
#include <QTimer>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QStandardPaths>
#include <QOperatingSystemVersion>

#include <filesystem>
#include <utility>
#include <fstream>
#include <sstream>


MainWindow::MainWindow(QWidget* parent)
	: QMainWindow(parent)
	, m_ui(new Ui::MainWindow)
{
	QCoreApplication::setApplicationName(PROJECT_NAME);
	QCoreApplication::setApplicationVersion(PROJECT_VER);
	m_ui->setupUi(this);

	auto const log_name{ "log.txt" };

	m_appdir = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
	std::filesystem::create_directory(m_appdir.toStdString());
	QString logdir = m_appdir + "/log/";
	std::filesystem::create_directory(logdir.toStdString());

	try
	{
		auto file{ std::string(logdir.toStdString() + log_name) };
		auto rotating = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(file, 1024 * 1024, 5, false);

		m_logger = std::make_shared<spdlog::logger>("box_design", rotating);
		m_logger->flush_on(spdlog::level::debug);
		m_logger->set_level(spdlog::level::debug);
		m_logger->set_pattern("[%D %H:%M:%S] [%L] %v");
		spdlog::register_logger(m_logger);
	}
	catch (std::exception& /*ex*/)
	{
		QMessageBox::warning(this, "Logger Failed", "Logger Failed To Start.");
	}

	setWindowTitle(windowTitle() + " v" + PROJECT_VER);

	m_settings = std::make_unique< QSettings>(m_appdir + "/settings.ini", QSettings::IniFormat);
	auto lastfolder{ m_settings->value("last_folder").toString() };

	m_boxScene = new BoxGraphicsScene(this);
	connect(m_boxScene, &BoxGraphicsScene::AddDevice, this, &MainWindow::OnAddDevice, Qt::QueuedConnection);

	//ui.graphicsView->setScene(&pageScene);
	m_ui->boxView->setScene(m_boxScene);// = new QGraphicsView(imageScene);

	m_ui->splitter->setStretchFactor(0, 1);
	m_ui->splitter->setStretchFactor(1, 5);

	m_templatedir = m_appdir + "/templates/";
	std::filesystem::create_directory(m_templatedir.toStdString());

	m_devicesdir = m_appdir + "/devices/";
	std::filesystem::create_directory(m_devicesdir.toStdString());

	//m_devicesItem = new QTreeWidgetItem(QStringList() << "Devices");
	//m_ui->listWidget->addItem(0, m_devicesItem);
	LoadDevices();
}

MainWindow::~MainWindow()
{
	delete m_ui;
}

void MainWindow::on_actionNew_triggered()
{
	QString openFileName =
		QFileDialog::getOpenFileName(this, "Open Template File", m_templatedir,
			"Box Design Template (*.jtp)");

	if (!openFileName.isEmpty())
	{
		try
		{
			nlohmann::json jsonData;
			std::ifstream inputFile(openFileName.toStdString());
			inputFile >> jsonData;
			m_enclosure = std::make_unique<Enclosure>(jsonData);
			m_boxScene->clear();
			//m_enclosure->Draw(m_boxScene);
			for (auto const& h : m_enclosure->holes)
			{
				drawPoint(*m_boxScene, h.x, h.y, h.diameter, QPen(Qt::black));
			}
			for (auto const& d : m_enclosure->devices)
			{
				drawPoint(*m_boxScene, d.x, d.y, 1, QPen(Qt::black));
			}
			for (auto const& l : m_enclosure->outline.lines)
			{
				drawLine(*m_boxScene, l.x1, l.y1, l.x2, l.y2, QPen(Qt::black));
			}
			UpdateStatus("Template Loaded: " + GetFileName(openFileName));
		}
		catch (std::exception& ex)
		{
			UpdateStatus("Error Loading Template: " + GetFileName(openFileName));
			m_logger->debug(ex.what());
		}
	}
}

void MainWindow::on_actionOpen_triggered() 
{

}

void MainWindow::on_actionSave_triggered()
{
	
}

void MainWindow::on_actionClose_triggered()
{
	close();
}

void MainWindow::on_actionAbout_triggered()
{
	QString text = QString("Box Design v%1<br>QT v%2<br><br>Icons by:")
		.arg(PROJECT_VER, QT_VERSION_STR) +
		QStringLiteral("<br><a href='http://www.famfamfam.com/lab/icons/silk/'>www.famfamfam.com</a>");
	//http://www.famfamfam.com/lab/icons/silk/
	QMessageBox::about(this, "About Box Design", text);
}

void MainWindow::on_actionOpen_Logs_triggered()
{
	QDesktopServices::openUrl(QUrl::fromLocalFile(m_appdir + "/log/"));
}

void MainWindow::UpdateStatus(QString const& message)
{
	m_ui->lb_Status->setText(message);
	m_logger->debug(message.toStdString());
}

void MainWindow::LogMessage(QString const& message, spdlog::level::level_enum llvl)
{
	m_logger->log(llvl, message.toStdString());
}

QString MainWindow::GetFileName(QString const& path) const
{
	if(path.isEmpty()) return QString();
	return QFileInfo( path ).fileName();
}

void MainWindow::LoadDevices()
{
	
	QDir dir(m_devicesdir);
	QFileInfoList devEntries = dir.entryInfoList(QDir::Files | QDir::NoDotAndDotDot | QDir::NoSymLinks);
	for (auto const& dev : devEntries)
	{
		auto const& name = dev.baseName();
		//m_ui->treeWidget->addItem(new QListWidgetItem(name));

		auto* newItem = new QListWidgetItem();
		newItem->setText(name);
		newItem->setData(Qt::UserRole, dev.filePath());
		//newItem->setText(1, value);
		//m_devicesItem->insertChild(0, newItem);

		//QString itemType = listWidgetItem->data(Qt::UserRole).toString();
		m_ui->listWidget->addItem(newItem);
		//m_ui->listWidget->addItem(name);
	}
}

void MainWindow::OnAddDevice(QString path, QPointF scenePos) 
{
	//m_boxScene->addItem()
}

void MainWindow::drawPoint(QGraphicsScene& scene, double x, double y, int radius , QPen pen)
{
	const QBrush blackbrush(Qt::black, Qt::SolidPattern);

	// y is negative due to graphics drawn from top left
	scene.addEllipse(x, -y - radius, radius, radius, pen, blackbrush);
}

void MainWindow::drawLine(QGraphicsScene& scene, double x1, double y1, double x2, double y2, QPen pen)
{
	// y is negative due to graphics drawn from top left

	scene.addLine(x1, -y1, x2, -y2, pen);
	
}