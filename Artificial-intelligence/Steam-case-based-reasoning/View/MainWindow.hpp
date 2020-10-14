#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>

#include "Model/Domain.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void dispatchInspect();
    void dispatchReload();

private:
    void setupLineEdits() const;
    void refreshList(gamequery::GameDataSimilarityCollection const& gdsc) const;

    gamequery::GameData getGameData() const;

    Ui::MainWindow *ui;

    gamequery::GameQuery gq;

    static constexpr auto storageLocation = "../GamesQuery/Model/dataset/store/";
    static constexpr auto collectionLocation = "../GamesQuery/Model/dataset/steam.csv";
};
#endif // MAINWINDOW_HPP
