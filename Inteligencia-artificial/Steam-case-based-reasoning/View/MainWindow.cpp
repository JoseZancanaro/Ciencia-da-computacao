#include "MainWindow.hpp"
#include "ui_MainWindow.h"

#include <QMessageBox>

namespace detail {

auto makeTableWidgetItem(std::string const& text) -> QTableWidgetItem* {
    return new QTableWidgetItem(QString::fromStdString(text));
}

auto makeTableWidgetItem(bool flag) -> QTableWidgetItem* {
    if (flag) {
        return new QTableWidgetItem(QString("true"));
    }
    else {
        return new QTableWidgetItem(QString("false"));
    }
}

auto makeTableWidgetItem(std::size_t number) -> QTableWidgetItem* {
    return new QTableWidgetItem(QString::number(number));
}

auto makeTableWidgetItem(double number) -> QTableWidgetItem* {
    return new QTableWidgetItem(QString::number(number));
}

}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
      , ui(new Ui::MainWindow)
{
    this->ui->setupUi(this);
    this->setupLineEdits();

    connect(ui->btnInspect, SIGNAL(clicked(bool)), this, SLOT(dispatchInspect()));
    connect(ui->actionReload, SIGNAL(triggered(bool)), this, SLOT(dispatchReload()));

    this->gq = {
        gamequery::readCollection(MainWindow::collectionLocation),
        gamequery::readBaseConfiguration(MainWindow::storageLocation)
    };

    auto input = gq.collection.front();
    auto result = gamequery::calculateAll(this->gq, input);

    std::cout << result.size() << std::endl;

    this->refreshList(result);
}

void MainWindow::dispatchInspect() {
    try {
        auto result = gamequery::calculateAll(this->gq, this->getGameData());
        this->refreshList(result);
    } catch (std::exception const& e) {
        QMessageBox::warning(this, "Parece-me que não foi...", "Algo errado não está certo.");
    }
}

void MainWindow::dispatchReload() {
    this->gq.base = gamequery::readBaseConfiguration(MainWindow::storageLocation);
}

void MainWindow::setupLineEdits() const {
    this->ui->txtDeveloper->setText("Indiferente");
    this->ui->txtPublisher->setText("Indiferente");
    this->ui->txtPlatform->setText("Indiferente");
    this->ui->txtRequiredAge->setText("Indiferente");
    this->ui->txtResource->setText("Indiferente");
    this->ui->txtGenre->setText("Indiferente");
    this->ui->txtTag->setText("Indiferente");
    this->ui->txtAchievements->setText("Indiferente");
    this->ui->txtPositiveRating->setText("Indiferente");
    this->ui->txtNegativeRating->setText("Indiferente");
    this->ui->txtAveragePlaytime->setText("Indiferente");
    this->ui->txtOwners->setText("Indiferente");
    this->ui->txtPrice->setText("Indiferente");
}

void MainWindow::refreshList(gamequery::GameDataSimilarityCollection const& gdsc) const {
    this->ui->tableWidget->reset();
    this->ui->tableWidget->setRowCount(0);

    for (auto const& [ data, similarity ]: gdsc) {
        auto rowCount = this->ui->tableWidget->rowCount();
        this->ui->tableWidget->insertRow(rowCount);

        std::array columns {
            detail::makeTableWidgetItem(similarity),
            detail::makeTableWidgetItem(data.appId),
            detail::makeTableWidgetItem(data.name),
            detail::makeTableWidgetItem(data.releaseDate),
            detail::makeTableWidgetItem(data.publisher),
            detail::makeTableWidgetItem(data.platform.front()),
            detail::makeTableWidgetItem(data.requiredAge),
            detail::makeTableWidgetItem(data.resource.front()),
            detail::makeTableWidgetItem(data.genre.front()),
            detail::makeTableWidgetItem(data.tag.front()),
            detail::makeTableWidgetItem(data.achievements),
            detail::makeTableWidgetItem(data.positiveRating),
            detail::makeTableWidgetItem(data.negativeRating),
            detail::makeTableWidgetItem(data.averagePlaytime),
            detail::makeTableWidgetItem(data.owners),
            detail::makeTableWidgetItem(data.price),
        };

        auto columnCount = 0;
        for (auto const& column : columns) {
            this->ui->tableWidget->setItem(rowCount, columnCount++, column);
        }
    }
}

gamequery::GameData MainWindow::getGameData() const {
    return {
        "arbitrary",
        "arbitrary",
        "arbitrary",
        this->ui->txtDeveloper->text().toStdString(),
        this->ui->txtPublisher->text().toStdString(),
        { this->ui->txtPlatform->text().toStdString() },
        this->ui->txtRequiredAge->text().toStdString(),
        { this->ui->txtResource->text().toStdString() },
        { this->ui->txtGenre->text().toStdString() },
        { this->ui->txtTag->text().toStdString() },
        this->ui->txtAchievements->text().toStdString(),
        this->ui->txtPositiveRating->text().toStdString(),
        this->ui->txtNegativeRating->text().toStdString(),
        this->ui->txtAveragePlaytime->text().toStdString(),
        this->ui->txtOwners->text().toStdString(),
        this->ui->txtPrice->text().toStdString(),
    };
};

MainWindow::~MainWindow()
{
    delete ui;
}
