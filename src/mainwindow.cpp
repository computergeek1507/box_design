#include "mainwindow.h"

#include "./ui_mainwindow.h"

#include "config.h"

#include <QMessageBox>
#include <QDesktopServices>
#include <QSettings>
#include <QFileDialog>
#include <QTextStream>
#include <QListWidget>
#include <QListWidgetItem>
#include <QTableWidget>
#include <QThread>
#include <QInputDialog>
#include <QCommandLineParser>
#include <QTimer>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QStandardPaths>
#include <QOperatingSystemVersion>

#include "spdlog/spdlog.h"

#include "spdlog/sinks/qt_sinks.h"
#include "spdlog/sinks/rotating_file_sink.h"

#include <filesystem>
#include <utility>


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

		m_logger = std::make_shared<spdlog::logger>("scottplayer", rotating);
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

}

MainWindow::~MainWindow()
{
	delete m_ui;
}

void MainWindow::on_actionSet_Show_Folder_triggered()
{
	QFileDialog dialog;
	dialog.setFileMode(QFileDialog::Directory);
	dialog.setOption(QFileDialog::ShowDirsOnly);
	auto lastfolder{ m_settings->value("last_folder",QStandardPaths::writableLocation(QStandardPaths::DesktopLocation)).toString() };

	QString const folder = dialog.getExistingDirectory(this, "Select xLight Show Folder", lastfolder, QFileDialog::ShowDirsOnly);
	if (!folder.isEmpty() && QDir(folder).exists())
	{
		
	}
}

void MainWindow::on_actionSave_triggered()
{
	
}

void MainWindow::on_actionStop_Sequence_triggered()
{

}

void MainWindow::on_actionClose_triggered()
{
	close();
}

void MainWindow::on_actionMultisync_triggered()
{

}

void MainWindow::on_actionAbout_triggered()
{
	QString text = QString("Scott Player v%1<br>QT v%2<br><br>Icons by:")
		.arg(PROJECT_VER, QT_VERSION_STR) +
		QStringLiteral("<br><a href='http://www.famfamfam.com/lab/icons/silk/'>www.famfamfam.com</a>");
	//http://www.famfamfam.com/lab/icons/silk/
	QMessageBox::about(this, "About Scott Player", text);
}

void MainWindow::on_actionOpen_Logs_triggered()
{
	QDesktopServices::openUrl(QUrl::fromLocalFile(m_appdir + "/log/"));
}

void MainWindow::on_pb_addPlaylist_clicked()
{
	bool ok;
	QString text = QInputDialog::getText(this, "PlayList Name",
		"PlayList Name", QLineEdit::Normal,
		"Main", &ok);
	if (ok && !text.isEmpty())
	{
		
	}
}

void MainWindow::on_pb_deletePlaylist_clicked()
{
	
	RefreshAddPlaylistButtons();
}

void MainWindow::on_pb_addSequence_clicked()
{
	QString const fseqFile = QFileDialog::getOpenFileName(this, "Select FSEQ File", m_settings->value("last_fseq").toString(), tr("FSEQ Files (*.fseq);;All Files (*.*)"));
	if (!fseqFile.isEmpty())
	{
		
	}
}

void MainWindow::on_pb_removeSequence_clicked()
{
	
}

void MainWindow::on_pb_moveUp_clicked()
{
	
}

void MainWindow::on_pb_moveDown_clicked()
{
	
}

void MainWindow::on_pb_playSequence_clicked()
{
	
}

void MainWindow::on_pb_stopSequence_clicked()
{
	
}

void MainWindow::on_pb_addSchedule_clicked()
{
	
}

void MainWindow::on_pb_editSchedule_clicked()
{
	if(-1 == m_ui->tw_schedules->currentRow())
	{
		return;
	}
	auto row = m_ui->tw_schedules->currentRow();
	
}

void MainWindow::on_pb_deleteSchedule_clicked()
{
	
}

void MainWindow::on_pb_sch_moveUp_clicked()
{
	
}

void MainWindow::on_pb_sch_moveDown_clicked()
{
	
}

void MainWindow::on_tw_playlists_cellDoubleClicked(int row, int column) 
{
	
}

void MainWindow::on_tw_schedules_cellDoubleClicked(int row, int column)
{
	
}

void MainWindow::on_tw_controllers_cellDoubleClicked(int row, int column)
{
	
}

void MainWindow::AddController_Received(bool enabled, QString const& type, QString const& ip, QString const& channel)
{
	
}

void MainWindow::SelectSequence(int index) 
{
	m_ui->tw_playlists->selectRow(index);
}

void MainWindow::on_cb_playlists_currentIndexChanged( int index )
{
	RedrawPlaylist(index);
}

void MainWindow::RedrawPlaylist(int index)
{
	
}

void MainWindow::RedrawSchedule()
{
	
}

void MainWindow::ClearListData()
{
	while (m_ui->tw_controllers->rowCount() != 0)
	{
		m_ui->tw_controllers->removeRow(0);
	}
}

void MainWindow::AddPlaylist(QString const& Playlist, int index)
{
	m_ui->cb_playlists->addItem(Playlist, index);
	RefreshAddPlaylistButtons();
}

void MainWindow::UpdateStatus(QString const& message)
{
	m_ui->lb_Status->setText(message);
	m_logger->debug(message.toStdString());
}

void MainWindow::UpdatePlayback(QString const& sequenceName, int elapsedMS, int durationMS)
{
	m_ui->lb_Status->setText(QString("Playing %1 %2/%3").arg(sequenceName).arg(FormatTime(elapsedMS)).arg(FormatTime(durationMS)));
}

void MainWindow::LogMessage(QString const& message, spdlog::level::level_enum llvl)
{
	m_logger->log(llvl, message.toStdString());
}

QString MainWindow::FormatTime(int ticksMS) const
{
	return QTime::fromMSecsSinceStartOfDay( ticksMS ).toString("mm:ss");
}

QString MainWindow::GetFileName(QString const& path) const
{
	if(path.isEmpty()) return QString();
	return QFileInfo( path ).fileName();
}

void MainWindow::RefreshAddPlaylistButtons()
{
	
}

void MainWindow::RefreshPlaylistButtons(int count)
{
	
}

void MainWindow::RefreshScheduleButtons()
{
	
}
